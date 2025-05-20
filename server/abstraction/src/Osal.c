/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <ABOS_Osal.h>
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/

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
/* none */

/* public functions -----------------------------------------------------------*/
void ABOS_Init(ABOS_Osal_t *this)
{
	printf("ABOS_Init\n");
}

void ABOS_Execute(ABOS_Osal_t *this)
{
	printf("ABOS_Execute\n");
}

int8_t ABOS_ThreadCreate(ABOS_thread_return_t taskFunctionPointer, int8_t * taskName, uint16_t taskStackSize, void * parameters, uint16_t taskPriority,   ABOS_thread_handle_t * taskHandler)
{
	int8_t status=ABOS_ERR_NONE;

	//TODO use priority
	pthread_create(taskHandler,NULL,taskFunctionPointer,parameters);

	return status;
}


int8_t ABOS_MutexCreate(ABOS_mutex_t *lock)
{
	int8_t status = pthread_mutex_init(lock,NULL);
	return status;
}


int8_t ABOS_MutexLock(ABOS_mutex_t *lock, uint32_t timeout)
{
	//printf("ABOS_MutexLock %p\n",lock);
	int8_t status = pthread_mutex_lock(lock);
	return status;
}

int8_t ABOS_MutexUnlock(ABOS_mutex_t *lock)
{
	//printf("ABOS_MutexUnlock %p\n",lock);
	int8_t status = pthread_mutex_unlock(lock);
	return status;
}


int8_t ABOS_BinSemaphoreCreate(ABOS_sem_handle_t *sem)
{
	int8_t status = sem_init(sem,1,1);
	return status;
}

//TODO remove #include <errno.h>


int8_t ABOS_SemaphoreWait(ABOS_sem_handle_t *sem, uint32_t timeoutMs)
{
	uint32_t secondsMs=(timeoutMs%1000);
	uint32_t seconds=(timeoutMs-secondsMs)/1000;

	struct timespec ts;
	ts.tv_sec=time(NULL)+seconds;
	ts.tv_nsec=secondsMs*1000000;
	int8_t status = sem_timedwait(sem,&ts);

	return status;
}


int8_t ABOS_SemaphorePost(ABOS_sem_handle_t *sem)
{
	int8_t status = sem_post(sem);
	return status;
}

void ABOS_Sleep(uint32_t milliseconds)
{
	usleep(milliseconds*1000);
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
