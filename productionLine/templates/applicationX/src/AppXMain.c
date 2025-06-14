/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <APPX_AppXMain.h>

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
// Main execution function for processing
void APPX_Execute(APPX_AppXMain_t *this);

// Thread definition macro for APPX execution
ABOS_DEFINE_TASK(APPX_ExecuteThread);

// Function called when a packet is received for this application
void APPX_DataHandler(void *handlingObject, uint8_t *inData,uint32_t inDataNb);

/* public functions -----------------------------------------------------------*/
// Initializes the APPX application
void APPX_Init(APPX_AppXMain_t *this, SBRO_Router_t *router,
		ABOS_sem_handle_t *semaphoreStart, ABOS_sem_handle_t *semaphoreEnd)
{
	printf("APPX_Init\n");

	// Store semaphore handles
	this->semaphoreStart = semaphoreStart;
	this->semaphoreEnd = semaphoreEnd;

	// Initialize application status
	this->sentPacketsNo = 0;
	this->receivedPacketsNo = 0;
	this->rejectedPacketsNo = 0;
	this->isRunAgain = M_TRUE;

	// Initialize packet queue
	LFQ_Init(&this->packetQueue, this->packetQueueBuffer, APPX_QUEUE_NB);
	ABOS_MutexCreate(&this->packetQueueMutex);
	this->router = router;

	// Subscribe to receive packets for this application's APID
	SBRO_Subscribe(this->router, APPX_APID, this, *APPX_DataHandler);

	// Create and start execution thread
	ABOS_ThreadCreate(
			APPX_ExecuteThread,              // Thread function
			(int8_t *)"APPX_EXEC",           // Thread name
			APPX_THREAD_STACK_SIZE,          // Stack size
			(void *)this,                    // Thread argument
			APPX_THREAD_PRIORITY,            // Priority
			&this->threadHandleExecute       // Thread handle
	);
}

// Stops the application by exiting the execution loop
void APPX_Stop(APPX_AppXMain_t *this)
{
	this->isRunAgain = M_FALSE;
}


/* local functions -----------------------------------------------------------*/
// Main execution function for APPX
// Processes all telecommands in the queue and sends back a response
void APPX_Execute(APPX_AppXMain_t *this)
{
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];  // Temporary buffer for one packet
	uint16_t packetSize;
	CCSDS_Packet_t *packet;
	uint8_t *packetData;
	uint16_t processedTcNo = 0;

	// Lock the queue for safe access
	ABOS_MutexLock(&this->packetQueueMutex, ABOS_TASK_MAX_DELAY);

	// Process packets in the queue (up to a max number)
	while ((LFQ_QueueGet(&this->packetQueue, packetBuffer, &packetSize)) &&
			(processedTcNo < APPX_TC_MAX_NB))
	{
		printf("APPX_DataHandler received packet:\n");

		packet = (CCSDS_Packet_t *)packetBuffer;
		CCSDS_PrintPacket(packet);

		if (packetSize >= sizeof(CCSDS_PrimaryHeader_t) + 2)
		{
			// Simple transformation: multiply data by 2
			packetData = &packet->data;
			packetData[0] *=2;
			packetData[1] *=2;
		}

		// Modify packet to be telemetry instead of telecommand
		packet->primaryHeader.packetType = CCSDS_PRIMARY_HEADER_IS_TM;

		printf("APPX_DataHandler sending response:\n");
		CCSDS_PrintPacket(packet);

		// Publish response packet back to the router
		SBRO_Publish(this->router, packetBuffer, packetSize);

		processedTcNo++;
	}

	// Unlock queue after processing
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

// Called when a packet for APPX is received by the router
void APPX_DataHandler(void *handlingObject, uint8_t *inData, uint32_t inDataNb)
{
	APPX_AppXMain_t *this = (APPX_AppXMain_t *)handlingObject;

	// Lock the queue to safely enqueue the incoming packet
	ABOS_MutexLock(&this->packetQueueMutex, ABOS_TASK_MAX_DELAY);

	// Add received packet to the processing queue
	if (LFQ_QueueAdd(&this->packetQueue, inData, inDataNb) == M_TRUE)
	{
		// Log if packet was rejected (queue full)
		printf("warning: APPX_DataHandler packet rejected\n");
		this->rejectedPacketsNo++;
	}
	//unlock the queue
	ABOS_MutexUnlock(&this->packetQueueMutex);
}

// Execution thread for APPX
// Waits for the start semaphore, processes packets, then signals completion
ABOS_DEFINE_TASK(APPX_ExecuteThread)
{
	APPX_AppXMain_t *this = (APPX_AppXMain_t *)param;

	while (this->isRunAgain == M_TRUE)
	{
		// Wait until orchestrator gives go-ahead
		ABOS_SemaphoreWait(this->semaphoreStart, ABOS_TASK_MAX_DELAY);

		// Run one cycle of the application
		APPX_Execute(this);

		// Notify orchestrator that processing is complete
		ABOS_SemaphorePost(this->semaphoreEnd);
	}

	return ABOS_TASK_RETURN;
}



/* end */
