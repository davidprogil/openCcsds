/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef CMAS_Maestro_H
#define CMAS_Maestro_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <ABOS_Osal.h>
#include <SBRO_Router.h>
#include <APP1_App1Main.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define CMAS_PROCESSES_SEMAPHORES_NO (2*CMAS_MAESTRO_APPS_NO)

/* types------------------------------------------------------------------------*/
typedef struct _CMAS_Maestro_t_
{
	//synchronisation
	ABOS_thread_handle_t threadHandleMaestro;
	ABOS_thread_handle_t threadHandleExecute;
	ABOS_sem_handle_t semaphoreMaestro;
	ABOS_sem_handle_t semaphoreExecute;
	ABOS_sem_handle_t semaphores[CMAS_PROCESSES_SEMAPHORES_NO];

	//status
	bool_t isRunAgain;
	uint32_t upTime;
	uint32_t overrunsCounter[CMAS_PROCESSES_SEMAPHORES_NO];
	uint32_t consecutiveOverrunsCounter[CMAS_PROCESSES_SEMAPHORES_NO];

	//sub elements
	SBRO_Router_t swBus;
	APP1_App1Main_t proc1;
}CMAS_Maestro_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void CMAS_Init(CMAS_Maestro_t *this);
void CMAS_Start(CMAS_Maestro_t *this);
void CMAS_Stop(CMAS_Maestro_t *this);


/* end */
#endif /* CMAS_Maestro_H */

