/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef ABST_Osal_H
#define ABST_Osal_H

/* system includes-------------------------------------------------------------*/
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define ABST_DEFINE_TASK(x) ABST_thread_return_t (x)(void* param)
#define ABST_MUTEX_OK (0)
#define ABST_MUTEX_ERROR (-1)
#define ABST_SEMAPHORE_OK (0)
#define ABST_ERR_NONE (0)
#define ABST_SEMAPHORE_ERROR (-1)
#define ABST_TASK_RETURN (NULL)
#define ABST_TASK_MAX_DELAY (UINT32_MAX)


/* types------------------------------------------------------------------------*/
typedef struct _ABST_Osal_t_
{

}ABST_Osal_t;

typedef sem_t ABST_sem_handle_t;
typedef pthread_mutex_t ABST_mutex_t;
typedef pthread_t ABST_thread_handle_t;
typedef void* ABST_thread_return_t;

typedef enum
{
	ABST_COUNTER_ID_SYRLINKS_WRAPPER=0,
	ABST_COUNTER_ID_NB
}ABST_CounterId_t;

typedef struct _ABST_TimeCuc_t{
	uint32_t seconds;
	uint16_t subSeconds;
} ABST_TimeCuc_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void ABST_Init(ABST_Osal_t *this);
void ABST_Execute(ABST_Osal_t *this);

int8_t ABST_ThreadCreate(ABST_thread_return_t taskFunctionPointer, int8_t * taskName, uint16_t taskStackSize, void * parameters, uint16_t taskPriority,   ABST_thread_handle_t * taskHandler);
int8_t ABST_MutexCreate(ABST_mutex_t *lock);
int8_t ABST_MutexLock(ABST_mutex_t *lock, uint32_t timeout);
int8_t ABST_MutexUnlock(ABST_mutex_t *lock);
int8_t ABST_BinSemaphoreCreate(ABST_sem_handle_t *sem);
int8_t ABST_SemaphorePost(ABST_sem_handle_t *sem);
int8_t ABST_SemaphoreWait(ABST_sem_handle_t *sem, uint32_t timeoutMs);

void ABST_Sleep(uint32_t milliseconds);

/* end */
#endif /* ABST_Osal_H */

