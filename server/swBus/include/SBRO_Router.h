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

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define SBRO_SUBSCRIBERS_MAX_NO (6)

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

	//queue
	//TODO

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

