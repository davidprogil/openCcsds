/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef LFQ_Queue_H
#define LFQ_Queue_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define FIFO_QUEUE_ELEMENT_MAX_NO 	(80)

/* types------------------------------------------------------------------------*/
typedef struct _LFQ_Queue_t_
{
	/* configuration */
		uint8_t *buffer;
		void *elementsPointer[FIFO_QUEUE_ELEMENT_MAX_NO];
		uint32_t elementSize[FIFO_QUEUE_ELEMENT_MAX_NO];
		uint32_t maxDataSize;

		/* state */
		uint32_t currentDataSize;
		uint16_t noElements;
		uint32_t writeIx;
		uint32_t readIx;

		uint32_t writeBufferIx;
		uint32_t readBufferIx;
}LFQ_Queue_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void LFQ_Init(LFQ_Queue_t *this,void *bufferPtr,uint32_t maxBufferSize);
uint16_t LFQ_GetNoQueuedElements(LFQ_Queue_t *this);
bool_t LFQ_QueueAdd(LFQ_Queue_t *this,void *element,uint32_t elementSize);
bool_t  LFQ_QueueGet(LFQ_Queue_t *this,void *target,uint16_t *dataSize);

/* end */
#endif /* LFQ_Queue_H */

