/*******************************************************************************/
/* Copyright David Gil 1998-2025                                              */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef ABOS_Osal_H
#define ABOS_Osal_H

/* system includes-------------------------------------------------------------*/
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define ABOS_DEFINE_TASK(x) ABOS_thread_return_t (x)(void* param)
#define ABOS_MUTEX_OK (0)
#define ABOS_MUTEX_ERROR (-1)
#define ABOS_SEMAPHORE_OK (0)
#define ABOS_ERR_NONE (0)
#define ABOS_SEMAPHORE_ERROR (-1)
#define ABOS_TASK_RETURN (NULL)
#define ABOS_TASK_MAX_DELAY (UINT32_MAX)


/* types------------------------------------------------------------------------*/
typedef struct _ABOS_Osal_t_
{

}ABOS_Osal_t;

typedef sem_t ABOS_sem_handle_t;
typedef pthread_mutex_t ABOS_mutex_t;
typedef pthread_t ABOS_thread_handle_t;
typedef void* ABOS_thread_return_t;

typedef enum
{
	ABOS_COUNTER_ID_SYRLINKS_WRAPPER=0,
	ABOS_COUNTER_ID_NB
}ABOS_CounterId_t;

typedef struct _ABOS_TimeCuc_t{
	uint32_t seconds;
	uint16_t subSeconds;
} ABOS_TimeCuc_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void ABOS_Init(ABOS_Osal_t *this);
void ABOS_Execute(ABOS_Osal_t *this);

int8_t ABOS_ThreadCreate(ABOS_thread_return_t taskFunctionPointer, int8_t * taskName, uint16_t taskStackSize, void * parameters, uint16_t taskPriority,   ABOS_thread_handle_t * taskHandler);
int8_t ABOS_MutexCreate(ABOS_mutex_t *lock);
int8_t ABOS_MutexLock(ABOS_mutex_t *lock, uint32_t timeout);
int8_t ABOS_MutexUnlock(ABOS_mutex_t *lock);
int8_t ABOS_BinSemaphoreCreate(ABOS_sem_handle_t *sem);
int8_t ABOS_SemaphorePost(ABOS_sem_handle_t *sem);
int8_t ABOS_SemaphoreWait(ABOS_sem_handle_t *sem, uint32_t timeoutMs);

void ABOS_Sleep(uint32_t milliseconds);

/* end */
#endif /* ABOS_Osal_H */

