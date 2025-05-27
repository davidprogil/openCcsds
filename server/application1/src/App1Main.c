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
/* none */


/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
void APP1_Execute(APP1_App1Main_t *this);
ABOS_DEFINE_TASK(APP1_ExecuteThread);
void APP1_DataHandler(void *handlingObject, uint8_t *inData,uint32_t inDataNb);

/* public functions -----------------------------------------------------------*/
void APP1_Init(APP1_App1Main_t *this,SBRO_Router_t *router,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd)
{
	printf("APP1_Init\n");
	this->semaphoreStart=semaphoreStart;
	this->semaphoreEnd=semaphoreEnd;

	//status
	this->sentPacketsNo=0;
	this->receivedPacketsNo=0;
	this->rejectedPacketsNo=0;
	this->isRunAgain=M_TRUE;

	//packet queue
	LFQ_Init(&this->packetQueue,this->packetQueueBuffer,APP1_QUEUE_NB);
	ABOS_MutexCreate(&this->packetQueueMutex);
	this->router=router;

	//subscribe
	SBRO_Subscribe(this->router,APP1_APID,this,*APP1_DataHandler);

	//start task
	ABOS_ThreadCreate(
			APP1_ExecuteThread, /* function */
			(int8_t *)"APP1_EXEC", /* name */
			APP1_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			APP1_THREAD_PRIORITY, /* priority */
			&this->threadHandleExecute); /* handler */
}

void APP1_Stop(APP1_App1Main_t *this)
{
	this->isRunAgain=M_FALSE;
}


/* local functions ------------------------------------------------------------*/
void APP1_Execute(APP1_App1Main_t *this)
{
	//printf("APP1_Execute\n");
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];
	uint16_t packetSize;
	CCSDS_Packet_t *packet;
	uint8_t *packetData;
	uint8_t temp;
	uint16_t processedTcNo=0;
	//get packets from the queue
	ABOS_MutexLock(&this->packetQueueMutex,ABOS_TASK_MAX_DELAY);
	while ((LFQ_QueueGet(&this->packetQueue,packetBuffer,&packetSize))&&(processedTcNo<APP1_TC_MAX_NB))
	{
		printf("APP1_DataHandler received packet:\n");
		packet=(CCSDS_Packet_t*)packetBuffer;
		CCSDS_PrintPacket(packet);

		//invert the data and send the response
		packetData=&packet->data;
		temp=packetData[1];
		packetData[1]=packetData[0];
		packetData[0]=temp;
		//change to TM
		packet->primaryHeader.packetType=CCSDS_PRIMARY_HEADER_IS_TM;

		printf("APP1_DataHandler sending response:\n");
		CCSDS_PrintPacket(packet);
		//send
		SBRO_Publish(this->router,packetBuffer,packetSize);
		processedTcNo++;
	}
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

void APP1_DataHandler(void *handlingObject, uint8_t *inData,uint32_t inDataNb)
{
	APP1_App1Main_t *this=(APP1_App1Main_t*)handlingObject;
	ABOS_MutexLock(&this->packetQueueMutex,ABOS_TASK_MAX_DELAY);
	if (LFQ_QueueAdd(&this->packetQueue,inData,inDataNb)==M_TRUE)
	{
		printf("warning: SBRO_Publish packet rejected\n");
		this->rejectedPacketsNo++;
	}
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

ABOS_DEFINE_TASK(APP1_ExecuteThread)
{
	APP1_App1Main_t *this=(APP1_App1Main_t*)param;
	while(this->isRunAgain==M_TRUE)
	{
		ABOS_SemaphoreWait(this->semaphoreStart,ABOS_TASK_MAX_DELAY);
		APP1_Execute(this);
		ABOS_SemaphorePost(this->semaphoreEnd);
	}
	return ABOS_TASK_RETURN;
}



/* end */
