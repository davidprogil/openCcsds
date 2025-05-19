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
#define ABST_MAESTRO_PERIOD_MS (1000)
//TODO put in configuration?
#define MAESTRO_THREAD_STACK_SIZE (0)
#define MAESTRO_THREAD_PRIORITY (0)
#define EXECUTE_THREAD_STACK_SIZE (0)
#define EXECUTE_THREAD_PRIORITY (0)

//syncronisation definitions
#define PROCESS1_INDEX (0)
#define PROCESS1_SEM_START_INDEX (PROCESS1_INDEX*2)
#define PROCESS1_SEM_END_INDEX (PROCESS1_SEM_START_INDEX+1)

#define PROCESS1_WAIT_BEFORE_MS (10)
#define PROCESS1_TIME_LENGTH_MS (100)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void CMAS_Execute(CMAS_Maestro_t *this);
ABST_DEFINE_TASK(CMAS_MaestroThread);
ABST_DEFINE_TASK(CMAS_ExecuteThread);

/* public functions -----------------------------------------------------------*/
void CMAS_Init(CMAS_Maestro_t *this)
{
	printf("CMAS_Init\n");
	int8_t semaphoreCreation=ABST_MUTEX_OK;

	//status
	memset(this,0,sizeof(CMAS_Maestro_t));
	this->isRunAgain=M_FALSE;
	this->upTime=0;

	//syncrhonization
	if (ABST_MUTEX_OK != ABST_BinSemaphoreCreate(&this->semaphoreExecute))
	{
		semaphoreCreation|=ABST_SEMAPHORE_ERROR;
		printf("ERROR CMAS_Init  semaphoreExecute semaphore not created.\n");
	}
	else
	{
		ABST_SemaphoreWait(&this->semaphoreExecute,ABST_TASK_MAX_DELAY);//TODO why two? it seems by default semapthore is green at creation
	}
	if (ABST_MUTEX_OK != ABST_BinSemaphoreCreate(&this->semaphoreMaestro))
	{
		semaphoreCreation|=ABST_SEMAPHORE_ERROR;
		printf("ERROR CMAS_Init  semaphoreExecute semaphore not created.\n");
	}
	else
	{
		ABST_SemaphoreWait(&this->semaphoreMaestro,ABST_TASK_MAX_DELAY);//TODO why two? it seems by default semapthore is green at creation
	}
	/* semaphores for processes */
	for (uint32_t semaphoreIx=0;semaphoreIx<CMAS_PROCESSES_SEMAPHORES_NO;semaphoreIx++)
	{
		if (ABST_MUTEX_OK != ABST_BinSemaphoreCreate(&this->semaphores[semaphoreIx]))
		{
			semaphoreCreation|=ABST_SEMAPHORE_ERROR;
			printf("ERROR semaphore not created.\n");
		}
		else
		{
			//printf("created semaphore %d %p\n",semaphoreIx,&this->semaphores[semaphoreIx]);
			ABST_SemaphoreWait(&this->semaphores[semaphoreIx],100);//TODO why two? it seems by default semapthore is green at creation
		}

		this->overrunsCounter[semaphoreIx]=0;
		this->consecutiveOverrunsCounter[semaphoreIx]=0;
	}

	/* create mutex for syncFileManagerIO */
	if (ABST_MUTEX_OK != semaphoreCreation)
	{
		/* TODO: log this information
		 * TODO: raise an alarm
		 * TODO think error handling strategy csp_log_error("Failed to create connection lock");
		 */
		printf("ERROR CMAS_Init semaphore not created.\n");
		//this->runAgain=M_FALSE;
	}
	else
	{

		//Initialise sub elements
		PRO1_Init(&this->proc1,&this->semaphores[PROCESS1_SEM_START_INDEX],&this->semaphores[PROCESS1_SEM_END_INDEX]);

		this->isRunAgain=M_TRUE;
		/* create threads */
		ABST_ThreadCreate(
				CMAS_MaestroThread, /* function */
				(int8_t *)"MAESTRO", /* name */
				MAESTRO_THREAD_STACK_SIZE, /* stack depth */
				(void *)this, /* parameters */
				MAESTRO_THREAD_PRIORITY, /* priority */
				&this->threadHandleMaestro); /* handler */

		ABST_ThreadCreate(
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
	ABST_SemaphorePost(&this->semaphoreMaestro);
}

/* local functions ------------------------------------------------------------*/
void CMAS_Execute(CMAS_Maestro_t *this)
{
	//printf("CMAS_Execute\n");
	uint16_t timeWaited=0;
	int8_t waitResult;

	//run the processes in their slot
	//process1
	/* wait for start of task */
	ABST_Sleep(PROCESS1_WAIT_BEFORE_MS-timeWaited);
	timeWaited+=PROCESS1_WAIT_BEFORE_MS;
	/* unfreeze it */
	ABST_SemaphoreWait(&this->semaphores[PROCESS1_SEM_END_INDEX],0);//get last one if any
	ABST_SemaphorePost(&this->semaphores[PROCESS1_SEM_START_INDEX]);
	/* wait for end of task*/
	//printf("FHW_Task 3\n");//TODO remove
	ABST_Sleep(PROCESS1_TIME_LENGTH_MS);
	timeWaited+=PROCESS1_TIME_LENGTH_MS;
	waitResult=ABST_SemaphoreWait(&this->semaphores[PROCESS1_SEM_END_INDEX],0);
	//printf("FHW_Task 4\n");//TODO remove
	/* check if it met result */
	if (ABST_SEMAPHORE_OK!=waitResult)
	{
		printf("* * * Commander Task Problem * * * %p %p\r\n",&this->semaphores[PROCESS1_SEM_START_INDEX],&this->semaphores[PROCESS1_SEM_END_INDEX]);//TODO remove
		/*monitored*/
		this->overrunsCounter[PROCESS1_INDEX]++;
		/*monitored*/
		this->consecutiveOverrunsCounter[PROCESS1_INDEX]++;
		/* if over threshold: raise alarm, wait and reboot */
		if (this->consecutiveOverrunsCounter[PROCESS1_INDEX]==5)//TODO magic number
		{
			/* TODO add observable enable */
			/* TODO make threshold observables */
			printf("Reboot\n");//TODO remove
			/* reboot */
			this->isRunAgain=M_FALSE;

		}
	}
	else
	{
		this->consecutiveOverrunsCounter[PROCESS1_INDEX]=0;
	}
	//end of process1

}

ABST_DEFINE_TASK(CMAS_MaestroThread)
{
	CMAS_Maestro_t *this=(CMAS_Maestro_t*)param;
	ABST_SemaphoreWait(&this->semaphoreMaestro,ABST_TASK_MAX_DELAY);
	while (this->isRunAgain==M_TRUE)
	{
		printf("debug: CMAS_MaestroThread %d\n",this->upTime);

		//unlblock CMAS_ExecuteThread
		ABST_SemaphorePost(&this->semaphoreExecute);

		ABST_Sleep(ABST_MAESTRO_PERIOD_MS);
		this->upTime++;
	}
	return ABST_TASK_RETURN;
}

ABST_DEFINE_TASK(CMAS_ExecuteThread)
{
	CMAS_Maestro_t *this=(CMAS_Maestro_t*)param;

	while (this->isRunAgain==M_TRUE)
	{
		//wait for unblock
		ABST_SemaphoreWait(&this->semaphoreExecute,ABST_TASK_MAX_DELAY);

		CMAS_Execute(this);
	}
	return ABST_TASK_RETURN;
}

/* end */
