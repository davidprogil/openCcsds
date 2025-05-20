/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <APP1_App1Main.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
//TODO put in configuration?
#define APP1_THREAD_STACK_SIZE (0)
#define APP1_THREAD_PRIORITY (0)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void APP1_Execute(APP1_App1Main_t *this);
ABOS_DEFINE_TASK(APP1_ExecuteThread);

/* public functions -----------------------------------------------------------*/
void APP1_Init(APP1_App1Main_t *this,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd)
{
	printf("APP1_Init\n");
	this->semaphoreStart=semaphoreStart;
	this->semaphoreEnd=semaphoreEnd;

	//start task
	ABOS_ThreadCreate(
			APP1_ExecuteThread, /* function */
			(int8_t *)"MAESTRO_EXEC", /* name */
			APP1_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			APP1_THREAD_PRIORITY, /* priority */
			&this->threadHandleExecute); /* handler */
}



/* local functions ------------------------------------------------------------*/
void APP1_Execute(APP1_App1Main_t *this)
{
	printf("APP1_Execute\n");
	//TODO do something
}

ABOS_DEFINE_TASK(APP1_ExecuteThread)
{
	APP1_App1Main_t *this=(APP1_App1Main_t*)param;
	while(1)//TODO is run again?
	{
		ABOS_SemaphoreWait(this->semaphoreStart,ABOS_TASK_MAX_DELAY);
		APP1_Execute(this);
		ABOS_SemaphorePost(this->semaphoreEnd);
	}
}



/* end */
