/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <PRO1_Proc1Main.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
//TODO put in configuration?
#define PRO1_THREAD_STACK_SIZE (0)
#define PRO1_THREAD_PRIORITY (0)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void PRO1_Execute(PRO1_Proc1Main_t *this);
ABST_DEFINE_TASK(PRO1_ExecuteThread);

/* public functions -----------------------------------------------------------*/
void PRO1_Init(PRO1_Proc1Main_t *this,ABST_sem_handle_t *semaphoreStart,ABST_sem_handle_t *semaphoreEnd)
{
	printf("PRO1_Init\n");
	this->semaphoreStart=semaphoreStart;
	this->semaphoreEnd=semaphoreEnd;

	//start task
	ABST_ThreadCreate(
			PRO1_ExecuteThread, /* function */
			(int8_t *)"MAESTRO_EXEC", /* name */
			PRO1_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			PRO1_THREAD_PRIORITY, /* priority */
			&this->threadHandleExecute); /* handler */
}



/* local functions ------------------------------------------------------------*/
void PRO1_Execute(PRO1_Proc1Main_t *this)
{
	printf("PRO1_Execute\n");
	//TODO do something
}

ABST_DEFINE_TASK(PRO1_ExecuteThread)
{
	PRO1_Proc1Main_t *this=(PRO1_Proc1Main_t*)param;
	while(1)//TODO is run again?
	{
		ABST_SemaphoreWait(this->semaphoreStart,ABST_TASK_MAX_DELAY);
		PRO1_Execute(this);
		ABST_SemaphorePost(this->semaphoreEnd);
	}
}



/* end */
