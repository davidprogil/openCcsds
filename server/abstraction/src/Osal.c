/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <ABST_Osal.h>

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
void ABST_Init(ABST_Osal_t *this)
{
	printf("ABST_Init\n");
}

void ABST_Execute(ABST_Osal_t *this)
{
	printf("ABST_Execute\n");
}

int8_t ABST_ThreadCreate(ABST_thread_return_t taskFunctionPointer, int8_t * taskName, uint16_t taskStackSize, void * parameters, uint16_t taskPriority,   ABST_thread_handle_t * taskHandler)
{
	int8_t status=ABST_ERR_NONE;

	//TODO use priority
	pthread_create(taskHandler,NULL,taskFunctionPointer,parameters);

	return status;
}


int8_t ABST_MutexCreate(ABST_mutex_t *lock)
{
	int8_t status = pthread_mutex_init(lock,NULL);
	return status;
}


int8_t ABST_MutexLock(ABST_mutex_t *lock, uint32_t timeout)
{
	//printf("ABST_MutexLock %p\n",lock);
	int8_t status = pthread_mutex_lock(lock);
	return status;
}

int8_t ABST_MutexUnlock(ABST_mutex_t *lock)
{
	//printf("ABST_MutexUnlock %p\n",lock);
	int8_t status = pthread_mutex_unlock(lock);
	return status;
}


int8_t ABST_BinSemaphoreCreate(ABST_sem_handle_t *sem)
{
	int8_t status = sem_init(sem,1,1);
	return status;
}

//TODO remove #include <errno.h>


int8_t ABST_SemaphoreWait(ABST_sem_handle_t *sem, uint32_t timeoutMs)
{
	uint32_t secondsMs=(timeoutMs%1000);
	uint32_t seconds=(timeoutMs-secondsMs)/1000;

	struct timespec ts;
	ts.tv_sec=time(NULL)+seconds;
	ts.tv_nsec=secondsMs*1000000;
	int8_t status = sem_timedwait(sem,&ts);

	return status;
}


int8_t ABST_SemaphorePost(ABST_sem_handle_t *sem)
{
	int8_t status = sem_post(sem);
	return status;
}

void ABST_Sleep(uint32_t milliseconds)
{
	usleep(milliseconds*1000);
}

/* local functions ------------------------------------------------------------*/
/* none */

/* end */
