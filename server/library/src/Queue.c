/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* application includes--------------------------------------------------------*/
#include <LIB_Queue.h>

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
bool_t LFQ_QueueWillBeFull(LFQ_Queue_t *this,void *element,uint32_t elementSize);
void* LFQ_Write(LFQ_Queue_t *this,uint8_t *source,uint32_t size);
void LFQ_Read(LFQ_Queue_t *this,uint8_t *target,uint32_t size);
/* public functions -----------------------------------------------------------*/
void LFQ_Init(LFQ_Queue_t *this,void *bufferPtr,uint32_t maxBufferSize)
{
	memset(this,0,sizeof(LFQ_Queue_t));
	this->noElements=0;
	this->elementsPointer[0]=NULL;
	this->elementSize[0]=0;
	this->buffer=bufferPtr;
	this->maxDataSize=maxBufferSize;
	this->currentDataSize=0;
	this->writeIx=0;
	this->writeBufferIx=0;
	this->readIx=0;
	this->readBufferIx=0;
}

bool_t LFQ_WillBeFull(LFQ_Queue_t *this,void *element,uint32_t elementSize)
{
	bool_t willBeFull=M_FALSE;
	if (this->noElements>=FIFO_QUEUE_ELEMENT_MAX_NO)
	{
		willBeFull=M_TRUE;
	}
	else if (this->currentDataSize+elementSize>this->maxDataSize)
	{
		willBeFull=M_TRUE;
	}
	return willBeFull;
}

uint16_t LFQ_GetNoQueuedElements(LFQ_Queue_t *this)
{
	return this->writeIx-this->readIx;
}

bool_t LFQ_QueueAdd(LFQ_Queue_t *this,void *element,uint32_t elementSize)
{
	bool_t isFull=M_FALSE;
	if (!LFQ_WillBeFull(this,element,elementSize))
	{
		this->elementSize[this->writeIx%FIFO_QUEUE_ELEMENT_MAX_NO]=elementSize;
		this->elementsPointer[this->writeIx%FIFO_QUEUE_ELEMENT_MAX_NO]=LFQ_Write(this,(uint8_t*)element,elementSize);
		this->currentDataSize+=elementSize;
		this->writeIx++;
		this->noElements++;
	}
	else
	{
		isFull=M_TRUE;
	}
	return isFull;
}

bool_t  LFQ_QueueGet(LFQ_Queue_t *this,void *target,uint16_t *dataSize)
{
	bool_t isPacket=M_FALSE;
	uint32_t elementSize=0;
	if (this->noElements>0)
	{
		elementSize=this->elementSize[this->readIx%FIFO_QUEUE_ELEMENT_MAX_NO];
		if (target!=NULL)
		{
			LFQ_Read(this,(uint8_t*)target,elementSize);
		}
		*dataSize=elementSize;
		/* take element out*/
		this->noElements--;
		this->readIx++;
		this->currentDataSize-=elementSize;
		isPacket=M_TRUE;
	}
	return isPacket;
}

/* local functions ------------------------------------------------------------*/
void* LFQ_Write(LFQ_Queue_t *this,uint8_t *source,uint32_t size)
{
	uint32_t bIx=0;
	for (bIx=0;bIx<size;bIx++)
	{
		this->buffer[this->writeBufferIx++]=source[bIx];
		if (this->writeBufferIx==this->maxDataSize)
		{
			this->writeBufferIx=0;
		}
	}
	return &this->buffer[this->writeBufferIx];
}

void LFQ_Read(LFQ_Queue_t *this,uint8_t *target,uint32_t size)
{
	uint32_t bIx=0;
	for (bIx=0;bIx<size;bIx++)
	{
		target[bIx]=this->buffer[this->readBufferIx++];
		if (this->readBufferIx==this->maxDataSize)
		{
			this->readBufferIx=0;
		}
	}
}

/* end */
