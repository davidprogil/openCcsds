/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef ABDL_DataLink_H
#define ABDL_DataLink_H

/* system includes-------------------------------------------------------------*/
#include <arpa/inet.h>
#include <netinet/in.h>


/* application includes--------------------------------------------------------*/
#include <myTypes.h>
#include <configuration.h>
#include <LIB_Queue.h>

/* component includes----------------------------------------------------------*/
#include <ABOS_Osal.h>

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/

typedef struct _ABDL_Socket_t_
{
	//config
	//ip
	shortText_t addressText;
	in_addr_t address;
	//port
	uint16_t port;
	//socket specific
	int sockfd;
	struct sockaddr_in servaddr;
	struct sockaddr_in cliaddr;
	socklen_t client_addr_len;
	//status
	uint32_t receivedNo;
	uint32_t sentNo;
	uint32_t receivedRejectedNo;

}ABDL_Socket_t;

typedef struct _ABDL_DataLink_t_
{
	ABDL_Socket_t socket;
	//synchronisation
	ABOS_thread_handle_t threadSend;

	//receive
	bool_t isRunAgain;
	ABOS_thread_handle_t threadReceive;
	//receive queue
	LFQ_Queue_t receiveQueue;
	uint8_t receiveQueueBuffer[ABDL_RECEIVE_QUEUE_NB];
	ABOS_mutex_t receiveQueueMutex;

}ABDL_DataLink_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void ABDL_Init(ABDL_DataLink_t *this);
void ABDL_SetServer(ABDL_DataLink_t *this);
void ABDL_Send(ABDL_DataLink_t *this,uint8_t *dataOut,uint16_t dataOutNb);



/* end */
#endif /* ABDL_DataLink_H */

