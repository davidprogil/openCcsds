/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef PRO1_Proc1Main_H
#define PRO1_Proc1Main_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <ABST_Osal.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
typedef struct _PRO1_Proc1Main_t_
{
	//synchronisation
	ABST_thread_handle_t threadHandleExecute;
	ABST_sem_handle_t *semaphoreStart;
	ABST_sem_handle_t *semaphoreEnd;
}PRO1_Proc1Main_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void PRO1_Init(PRO1_Proc1Main_t *this,ABST_sem_handle_t *semaphoreStart,ABST_sem_handle_t *semaphoreEnd);

/* end */
#endif /* PRO1_Proc1Main_H */

