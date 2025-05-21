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
}APP1_App1Main_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void APP1_Init(APP1_App1Main_t *this,SBRO_Router_t *router,ABOS_sem_handle_t *semaphoreStart,ABOS_sem_handle_t *semaphoreEnd);

/* end */
#endif /* APP1_App1Main_H */

