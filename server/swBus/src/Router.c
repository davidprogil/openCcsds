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
/* none */

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
uint32_t GetSubscriberForPid(SBRO_Router_t *this,uint16_t apid);

/* public functions -----------------------------------------------------------*/
void SBRO_Init(SBRO_Router_t *this,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd)
{
	printf("SBRO_Init\n");
	//synchronisation
	this->semaphoreStart=semaphoreStart;
	this->semaphoreEnd=semaphoreEnd;

	//status
	this->rejectedPacketsNo=0;
	this->subscriberNotFoundNo=0;

	//packet queue
	LFQ_Init(&this->packetQueue,this->packetQueueBuffer,SBRO_QUEUE_NB);
	ABOS_MutexCreate(&this->packetQueueMutex);

	//subscriber list
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

	ABDL_Init(&this->dataLink);
	ABDL_SetServer(&this->dataLink);
}

void SBRO_Publish(SBRO_Router_t *this,uint8_t *inData,uint32_t inDataNb)
{
	/* add packet to queue */
	ABOS_MutexLock(&this->packetQueueMutex,ABOS_TASK_MAX_DELAY);
	if (LFQ_QueueAdd(&this->packetQueue,inData,inDataNb)==M_TRUE)
	{
		printf("warning: SBRO_Publish packet rejected\n");
		this->rejectedPacketsNo++;
	}
	ABOS_MutexUnlock(&this->packetQueueMutex);
}
void SBRO_Subscribe(SBRO_Router_t *this,uint32_t apid,void *handlingObject,SBRO_DataHandlerFunction_t *dataHandler)
{
	this->subscribers[this->subscribersNo].apid=apid;
	this->subscribers[this->subscribersNo].handlingObject=handlingObject;
	this->subscribers[this->subscribersNo].dataHandler=dataHandler;
	this->subscribersNo++;
}


/* local functions ------------------------------------------------------------*/
void SBRO_Execute(SBRO_Router_t *this)
{
	//printf("SBRO_Execute\n");
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];
	uint16_t packetSize;
	CCSDS_Packet_t *packet;
	uint16_t subscriberIx;

	//get packets from the datalink and publish them
	ABOS_MutexLock(&this->dataLink.receiveQueueMutex,ABOS_TASK_MAX_DELAY);
	while(LFQ_QueueGet(&this->dataLink.receiveQueue,packetBuffer,&packetSize))
	{
		SBRO_Publish(this,packetBuffer,packetSize);
	}
	ABOS_MutexUnlock(&this->dataLink.receiveQueueMutex);

	//TODO this queue is redundant

	//get packets from the queue and call adequate subscriber
	ABOS_MutexLock(&this->packetQueueMutex,ABOS_TASK_MAX_DELAY);
	while(LFQ_QueueGet(&this->packetQueue,packetBuffer,&packetSize))
	{
		packet=(CCSDS_Packet_t*)packetBuffer;
		printf("received packet for apid: %d\n",packet->primaryHeader.apid);
		subscriberIx=GetSubscriberForPid(this,packet->primaryHeader.apid);
		if (subscriberIx!=UINT32_MAX)
		{
			//call subscriber
			this->subscribers[subscriberIx].dataHandler(
					this->subscribers[subscriberIx].handlingObject,
					packetBuffer,
					packetSize);
		}
		else
		{
			printf("warning: SBRO_Execute subscriber not found for apid %d\n",packet->primaryHeader.apid);
			this->subscriberNotFoundNo++;
		}
	}
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

void SBRO_InitSubscriber(SBRO_Subscriber_t *this)
{
	this->apid=UINT32_MAX;
	this->dataHandler=NULL;
	this->handlingObject=NULL;
}

uint32_t GetSubscriberForPid(SBRO_Router_t *this,uint16_t apid)
{
	uint32_t subscriberIx=UINT32_MAX;

	for (uint32_t sIx=0;sIx<SBRO_SUBSCRIBERS_MAX_NO;sIx++)
	{
		if (this->subscribers[sIx].apid==apid)
		{
			subscriberIx=sIx;
			break;
		}
	}


	return subscriberIx;
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
