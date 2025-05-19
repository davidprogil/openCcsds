/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef CMAS_Maestro_H
#define CMAS_Maestro_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <ABST_Osal.h>
#include <PRO1_Proc1Main.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define CMAS_PROCESSES_NO (1)
#define CMAS_PROCESSES_SEMAPHORES_NO (2*CMAS_PROCESSES_NO)

/* types------------------------------------------------------------------------*/
typedef struct _CMAS_Maestro_t_
{
	//synchronisation
	ABST_thread_handle_t threadHandleMaestro;
	ABST_thread_handle_t threadHandleExecute;
	ABST_sem_handle_t semaphoreMaestro;
	ABST_sem_handle_t semaphoreExecute;
	ABST_sem_handle_t semaphores[CMAS_PROCESSES_SEMAPHORES_NO];

	//status
	bool_t isRunAgain;
	uint32_t upTime;
	uint32_t overrunsCounter[CMAS_PROCESSES_SEMAPHORES_NO];
	uint32_t consecutiveOverrunsCounter[CMAS_PROCESSES_SEMAPHORES_NO];

	//sub elements
	PRO1_Proc1Main_t proc1;
}CMAS_Maestro_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void CMAS_Init(CMAS_Maestro_t *this);
void CMAS_Start(CMAS_Maestro_t *this);


/* end */
#endif /* CMAS_Maestro_H */

