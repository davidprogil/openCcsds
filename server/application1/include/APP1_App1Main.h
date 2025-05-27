/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef APP1_App1Main_H
#define APP1_App1Main_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <configuration.h>
#include <ABOS_Osal.h>
#include <SBRO_Router.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
typedef struct _APP1_App1Main_t_
{
	//synchronisation
	ABOS_thread_handle_t threadHandleExecute;
	ABOS_sem_handle_t *semaphoreStart;
	ABOS_sem_handle_t *semaphoreEnd;

	//status
	uint16_t sentPacketsNo;
	uint16_t receivedPacketsNo;
	uint16_t rejectedPacketsNo;
	bool_t isRunAgain;

	//queue and data exchange
	SBRO_Router_t *router;
	LFQ_Queue_t packetQueue;
	uint8_t packetQueueBuffer[APP1_QUEUE_NB];
	ABOS_mutex_t packetQueueMutex;

}APP1_App1Main_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void APP1_Init(APP1_App1Main_t *this,SBRO_Router_t *router,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd);
void APP1_Stop(APP1_App1Main_t *this);

/* end */
#endif /* APP1_App1Main_H */

