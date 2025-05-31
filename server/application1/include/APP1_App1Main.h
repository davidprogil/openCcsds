/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef APP1_App1Main_H
#define APP1_App1Main_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>        // Common project-wide typedefs
#include <configuration.h>  // System or module-specific configuration constants
#include <ABOS_Osal.h>      // OS abstraction layer: threads, semaphores, etc.
#include <SBRO_Router.h>    // Packet routing and publish/subscribe interfaces

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
// Main structure for APP1 application logic and runtime context
typedef struct _APP1_App1Main_t_
{
	// Handle for the APP1 main execution thread
	ABOS_thread_handle_t threadHandleExecute;

	// Semaphores to synchronize execution with the system scheduler
	ABOS_sem_handle_t *semaphoreStart;  // Signals when to start execution
	ABOS_sem_handle_t *semaphoreEnd;    // Signals when execution is complete

	/*------------------- Status ----------------------*/

	// Counters for telemetry and debugging
	uint16_t sentPacketsNo;       // Number of packets sent
	uint16_t receivedPacketsNo;   // Number of packets received
	uint16_t rejectedPacketsNo;   // Number of packets rejected (e.g. due to full queue)

	// Execution control flag
	bool_t isRunAgain;            // When false, terminates main thread loop

	/*----------- Data Exchange (Router + Queue) -------*/

	// Pointer to the shared packet router (SBRO)
	SBRO_Router_t *router;

	// Lock-free queue to buffer incoming packets
	LFQ_Queue_t packetQueue;

	// Underlying storage for the packet queue
	uint8_t packetQueueBuffer[APP1_QUEUE_NB];

	// Mutex to protect access to the packet queue
	ABOS_mutex_t packetQueueMutex;

}APP1_App1Main_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
/**
 * @brief Initializes the APP1 module with synchronization and communication resources.
 *
 * @param this Pointer to the APP1 context structure
 * @param router Pointer to the shared router instance
 * @param semaphoreStart Pointer to the start semaphore (provided by scheduler)
 * @param semaphoreEnd Pointer to the end semaphore (provided by scheduler)
 */
void APP1_Init(APP1_App1Main_t *this, SBRO_Router_t *router, ABOS_sem_handle_t *semaphoreStart, ABOS_sem_handle_t *semaphoreEnd);

/**
 * @brief Stops APP1 execution (sets the run flag to false).
 *
 * @param this Pointer to the APP1 context structure
 */
void APP1_Stop(APP1_App1Main_t *this);

/* end */
#endif /* APP1_App1Main_H */

