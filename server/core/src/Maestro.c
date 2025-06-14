/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* application includes--------------------------------------------------------*/
#include <CORE_Maestro.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
/* none */

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
uint32_t appsTimesStart[CMAS_MAESTRO_APPS_NO]={
		SWBUS_TIME_START_MS,
		APP1_TIME_START_MS};
uint32_t appsTimesLength[CMAS_MAESTRO_APPS_NO]={
		SWBUS_TIME_LENGTH_MS,
		APP1_TIME_LENGTH_MS};

/* local prototypes -----------------------------------------------------------*/
void CMAS_Execute(CMAS_Maestro_t *this);
ABOS_DEFINE_TASK(CMAS_MaestroThread);
ABOS_DEFINE_TASK(CMAS_ExecuteThread);

/* public functions -----------------------------------------------------------*/
void CMAS_Init(CMAS_Maestro_t *this)
{
	printf("CMAS_Init\n");
	int8_t semaphoreCreation=ABOS_MUTEX_OK;
	//status
	memset(this,0,sizeof(CMAS_Maestro_t));
	this->isRunAgain=M_FALSE;
	this->upTime=0;

	//syncrhonization
	if (ABOS_MUTEX_OK != ABOS_BinSemaphoreCreate(&this->semaphoreExecute))
	{
		semaphoreCreation|=ABOS_SEMAPHORE_ERROR;
		printf("ERROR CMAS_Init  semaphoreExecute semaphore not created.\n");
	}
	else
	{
		ABOS_SemaphoreWait(&this->semaphoreExecute,ABOS_TASK_MAX_DELAY);// why two? it seems by default semapthore is green at creation
	}
	if (ABOS_MUTEX_OK != ABOS_BinSemaphoreCreate(&this->semaphoreMaestro))
	{
		semaphoreCreation|=ABOS_SEMAPHORE_ERROR;
		printf("ERROR CMAS_Init  semaphoreExecute semaphore not created.\n");
	}
	else
	{
		ABOS_SemaphoreWait(&this->semaphoreMaestro,ABOS_TASK_MAX_DELAY);// why two? it seems by default semapthore is green at creation
	}
	/* semaphores for processes */
	for (uint32_t semaphoreIx=0;semaphoreIx<CMAS_PROCESSES_SEMAPHORES_NO;semaphoreIx++)
	{
		if (ABOS_MUTEX_OK != ABOS_BinSemaphoreCreate(&this->semaphores[semaphoreIx]))
		{
			semaphoreCreation|=ABOS_SEMAPHORE_ERROR;
			printf("ERROR semaphore not created.\n");
		}
		else
		{
			//printf("created semaphore %d %p\n",semaphoreIx,&this->semaphores[semaphoreIx]);
			ABOS_SemaphoreWait(&this->semaphores[semaphoreIx],100);// why two? it seems by default semapthore is green at creation
		}

		this->overrunsCounter[semaphoreIx]=0;
		this->consecutiveOverrunsCounter[semaphoreIx]=0;
	}

	/* verify semaphore creation */
	if (ABOS_MUTEX_OK != semaphoreCreation)
	{
		printf("ERROR CMAS_Init semaphore not created.\n");
		this->isRunAgain=M_FALSE;
	}
	else
	{
		//Initialise sub elements
		//note, order of initialization must be the same as in configuration file when the scheduling is defined
		// and when appsTimesStart and appsTimesLength is assigned
		uint16_t sIx=0;
		SBRO_Init(&this->swBus,&this->semaphores[sIx],&this->semaphores[sIx+1]);
		sIx+=2;
		APP1_Init(&this->proc1,&this->swBus,&this->semaphores[sIx],&this->semaphores[sIx+1]);
		sIx+=2;

		this->isRunAgain=M_TRUE;
		/* create threads */
		ABOS_ThreadCreate(
				CMAS_MaestroThread, /* function */
				(int8_t *)"MAESTRO", /* name */
				MAESTRO_THREAD_STACK_SIZE, /* stack depth */
				(void *)this, /* parameters */
				MAESTRO_THREAD_PRIORITY, /* priority */
				&this->threadHandleMaestro); /* handler */

		ABOS_ThreadCreate(
				CMAS_ExecuteThread, /* function */
				(int8_t *)"MAESTRO_EXEC", /* name */
				EXECUTE_THREAD_STACK_SIZE, /* stack depth */
				(void *)this, /* parameters */
				EXECUTE_THREAD_PRIORITY, /* priority */
				&this->threadHandleExecute); /* handler */

	}
}

void CMAS_Start(CMAS_Maestro_t *this)
{
	ABOS_SemaphorePost(&this->semaphoreMaestro);
}
void CMAS_Stop(CMAS_Maestro_t *this)
{
	this->isRunAgain=M_FALSE;
	SBRO_Stop(&this->swBus);
	APP1_Stop(&this->proc1);
}

/* local functions ------------------------------------------------------------*/
void CMAS_Execute(CMAS_Maestro_t *this)
{
	//printf("CMAS_Execute\n");
	uint16_t timeWaited=0;
	uint16_t timeToWait;
	int8_t waitResult;

	//run the processes in their slot
	for (uint16_t appIx=0;appIx<CMAS_MAESTRO_APPS_NO;appIx++)
	{
		/* wait for start of task */
		timeToWait=appsTimesStart[appIx]-timeWaited;
		ABOS_Sleep(timeToWait);
		timeWaited+=timeToWait;
		/* unfreeze it */
		ABOS_SemaphoreWait(&this->semaphores[appIx*2+1],0);//get last one if any
		ABOS_SemaphorePost(&this->semaphores[appIx*2]);

		/* wait for end of task*/
		ABOS_Sleep(appsTimesLength[appIx]);
		timeWaited+=appsTimesLength[appIx];
		waitResult=ABOS_SemaphoreWait(&this->semaphores[appIx*2+1],0);
		/* check if it met result */
		if (ABOS_SEMAPHORE_OK!=waitResult)
		{
			//printf("CMAS_Execute 6\n");
			printf("* * * Commander Task Problem * * * %p %p\r\n",&this->semaphores[appIx*2],&this->semaphores[appIx*2+1]);
			/*monitored*/
			this->overrunsCounter[appIx]++;
			/*monitored*/
			this->consecutiveOverrunsCounter[appIx]++;
			/* if over threshold: raise alarm, wait and reboot */
			if (this->consecutiveOverrunsCounter[appIx]==CMAS_OVERRUNS_MAX_NO)
			{
				printf("Reboot\n");
				/* reboot */
				this->isRunAgain=M_FALSE;
			}
		}
		else
		{
			//printf("CMAS_Execute 7\n");
			this->consecutiveOverrunsCounter[appIx]=0;
		}
	}
}

ABOS_DEFINE_TASK(CMAS_MaestroThread)
{
	CMAS_Maestro_t *this=(CMAS_Maestro_t*)param;
	ABOS_SemaphoreWait(&this->semaphoreMaestro,ABOS_TASK_MAX_DELAY);
	while (this->isRunAgain==M_TRUE)
	{
		printf("debug: CMAS_MaestroThread %d\n",this->upTime);

		//unlblock CMAS_ExecuteThread
		ABOS_SemaphorePost(&this->semaphoreExecute);

		ABOS_Sleep(ABOS_MAESTRO_PERIOD_MS);
		this->upTime++;
	}
	return ABOS_TASK_RETURN;
}

ABOS_DEFINE_TASK(CMAS_ExecuteThread)
{
	CMAS_Maestro_t *this=(CMAS_Maestro_t*)param;

	while (this->isRunAgain==M_TRUE)
	{
		//wait for unblock
		ABOS_SemaphoreWait(&this->semaphoreExecute,ABOS_TASK_MAX_DELAY);
		CMAS_Execute(this);
	}
	return ABOS_TASK_RETURN;
}

/* end */
