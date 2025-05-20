/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <SBRO_Router.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
//TODO put in configuration?
#define SBRO_THREAD_STACK_SIZE (0)
#define SBRO_THREAD_PRIORITY (0)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void SBRO_Execute(SBRO_Router_t *this);
ABOS_DEFINE_TASK(SBRO_ExecuteThread);
void SBRO_InitSubscriber(SBRO_Subscriber_t *subscriber);

/* public functions -----------------------------------------------------------*/
void SBRO_Init(SBRO_Router_t *this,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd)
{
	printf("SBRO_Init\n");
	this->semaphoreStart=semaphoreStart;
	this->semaphoreEnd=semaphoreEnd;

	this->subscribersNo=0;
	for (uint32_t sIx=0;sIx<SBRO_SUBSCRIBERS_MAX_NO;sIx++)
	{
		SBRO_InitSubscriber(&this->subscribers[sIx]);
	}

	ABOS_ThreadCreate(
			SBRO_ExecuteThread, /* function */
			(int8_t *)"SBRO_EXEC", /* name */
			SBRO_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			SBRO_THREAD_PRIORITY, /* priority */
			&this->threadHandleExecute); /* handler */
}

void SBRO_Publish(SBRO_Router_t *this,uint8_t *inData,uint32_t inDataNb)
{
	/* add packet to queue */
	//TODO
}
void SBRO_Subscribe(SBRO_Router_t *this,uint32_t apid,void *handlingObject,SBRO_DataHandlerFunction_t *dataHandler)
{

}


/* local functions ------------------------------------------------------------*/
void SBRO_Execute(SBRO_Router_t *this)
{
	printf("SBRO_Execute\n");
}

void SBRO_InitSubscriber(SBRO_Subscriber_t *this)
{
	this->apid=UINT32_MAX;
	this->dataHandler=NULL;
	this->handlingObject=NULL;
}

ABOS_DEFINE_TASK(SBRO_ExecuteThread)
{
	SBRO_Router_t *this=(SBRO_Router_t*)param;
	while(1)//TODO is run again?
	{
		ABOS_SemaphoreWait(this->semaphoreStart,ABOS_TASK_MAX_DELAY);
		SBRO_Execute(this);
		ABOS_SemaphorePost(this->semaphoreEnd);
	}
	return ABOS_TASK_RETURN;
}
/* end */
