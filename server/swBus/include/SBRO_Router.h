/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef SBRO_Router_H
#define SBRO_Router_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <ABOS_Osal.h>
#include <LIB_Queue.h>

/* component includes----------------------------------------------------------*/
#include <SBCC_CcsdsUtils.h>

/* macros-----------------------------------------------------------------------*/
#define SBRO_SUBSCRIBERS_MAX_NO (6) //TODO move to configuration
#define SBRO_QUEUE_NB (2000) //TODO move to configuration
#define SBRO_PACKET_MAX_NB (256) //TODO move to configuration

/* types------------------------------------------------------------------------*/
typedef void(SBRO_DataHandlerFunction_t)(void *handlingObject, uint8_t *inData,uint32_t inDataNb);

typedef struct _SBRO_Subscriber_t_
{
	uint32_t apid;
	void *handlingObject;
	SBRO_DataHandlerFunction_t *dataHandler;

}SBRO_Subscriber_t;

typedef struct _SBRO_Router_t_
{
	//synchronisation
	ABOS_thread_handle_t threadHandleExecute;
	ABOS_sem_handle_t *semaphoreStart;
	ABOS_sem_handle_t *semaphoreEnd;

	//counters
	uint32_t rejectedPacketsNo;
	uint32_t subscriberNotFoundNo;

	//queue
	LFQ_Queue_t packetQueue;
	uint8_t packetQueueBuffer[SBRO_QUEUE_NB];
	ABOS_mutex_t packetQueueMutex;

	//subscribers management
	SBRO_Subscriber_t subscribers[SBRO_SUBSCRIBERS_MAX_NO];
	uint32_t subscribersNo;

}SBRO_Router_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void SBRO_Init(SBRO_Router_t *this,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd);
void SBRO_Publish(SBRO_Router_t *this,uint8_t *inData,uint32_t inDataNb);
void SBRO_Subscribe(SBRO_Router_t *this,uint32_t apid,void *handlingObject,SBRO_DataHandlerFunction_t *dataHandler);


/* end */
#endif /* SBRO_Router_H */

