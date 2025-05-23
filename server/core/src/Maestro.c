/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
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

//syncronisation definitions
#define SWBUS_INDEX (0)
#define SWBUS_SEM_START_INDEX (SWBUS_INDEX*2)
#define SWBUS_SEM_END_INDEX (SWBUS_SEM_START_INDEX+1)

#define PROCESS1_INDEX (1)
#define PROCESS1_SEM_START_INDEX (PROCESS1_INDEX*2)
#define PROCESS1_SEM_END_INDEX (PROCESS1_SEM_START_INDEX+1)



/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

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

	/* create mutex for syncFileManagerIO */
	if (ABOS_MUTEX_OK != semaphoreCreation)
	{
		//TODO do something else
		printf("ERROR CMAS_Init semaphore not created.\n");
		//this->runAgain=M_FALSE;
	}
	else
	{

		//Initialise sub elements
		SBRO_Init(&this->swBus,&this->semaphores[SWBUS_SEM_START_INDEX],&this->semaphores[SWBUS_SEM_END_INDEX]);
		APP1_Init(&this->proc1,&this->swBus,&this->semaphores[PROCESS1_SEM_START_INDEX],&this->semaphores[PROCESS1_SEM_END_INDEX]);

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

/* local functions ------------------------------------------------------------*/
void CMAS_Execute(CMAS_Maestro_t *this)
{
	//printf("CMAS_Execute\n");
	uint16_t timeWaited=0;
	int8_t waitResult;

	//run the processes in their slot
	//swbus
	/* wait for start of task */
	ABOS_Sleep(SWBUS_WAIT_BEFORE_MS-timeWaited);
	timeWaited+=SWBUS_WAIT_BEFORE_MS;

	/* unfreeze it */
	ABOS_SemaphoreWait(&this->semaphores[SWBUS_SEM_END_INDEX],0);//get last one if any
	ABOS_SemaphorePost(&this->semaphores[SWBUS_SEM_START_INDEX]);

	/* wait for end of task*/
	ABOS_Sleep(SWBUS_TIME_LENGTH_MS);
	timeWaited+=SWBUS_TIME_LENGTH_MS;
	waitResult=ABOS_SemaphoreWait(&this->semaphores[SWBUS_SEM_END_INDEX],0);

	/* check if it met result */
	if (ABOS_SEMAPHORE_OK!=waitResult)
	{
		//printf("CMAS_Execute 6\n");
		printf("* * * Commander Task Problem * * * %p %p\r\n",&this->semaphores[SWBUS_SEM_START_INDEX],&this->semaphores[SWBUS_SEM_END_INDEX]);//TODO remove
		/*monitored*/
		this->overrunsCounter[SWBUS_INDEX]++;
		/*monitored*/
		this->consecutiveOverrunsCounter[SWBUS_INDEX]++;
		/* if over threshold: raise alarm, wait and reboot */
		if (this->consecutiveOverrunsCounter[SWBUS_INDEX]==5)//TODO put in configuration
		{
			printf("Reboot\n");
			/* reboot */
			this->isRunAgain=M_FALSE;

		}
	}
	else
	{
		//printf("CMAS_Execute 7\n");
		this->consecutiveOverrunsCounter[SWBUS_INDEX]=0;
	}
	//end of swbus

	//process1
	/* wait for start of task */
	ABOS_Sleep(PROCESS1_WAIT_BEFORE_MS-timeWaited);

	timeWaited+=PROCESS1_WAIT_BEFORE_MS;
	/* unfreeze it */
	ABOS_SemaphoreWait(&this->semaphores[PROCESS1_SEM_END_INDEX],0);//get last one if any
	ABOS_SemaphorePost(&this->semaphores[PROCESS1_SEM_START_INDEX]);

	/* wait for end of task*/
	ABOS_Sleep(PROCESS1_TIME_LENGTH_MS);
	timeWaited+=PROCESS1_TIME_LENGTH_MS;
	waitResult=ABOS_SemaphoreWait(&this->semaphores[PROCESS1_SEM_END_INDEX],0);

	/* check if it met result */
	if (ABOS_SEMAPHORE_OK!=waitResult)
	{
		printf("* * * Commander Task Problem * * * %p %p\r\n",&this->semaphores[PROCESS1_SEM_START_INDEX],&this->semaphores[PROCESS1_SEM_END_INDEX]);
		/*monitored*/
		this->overrunsCounter[PROCESS1_INDEX]++;
		/*monitored*/
		this->consecutiveOverrunsCounter[PROCESS1_INDEX]++;
		/* if over threshold: raise alarm, wait and reboot */
		if (this->consecutiveOverrunsCounter[PROCESS1_INDEX]==5)//TODO magic number
		{
			printf("Reboot\n");
			/* reboot */
			this->isRunAgain=M_FALSE;

		}
	}
	else
	{
		//printf("CMAS_Execute 14\n");
		this->consecutiveOverrunsCounter[PROCESS1_INDEX]=0;
	}
	//end of process1

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
