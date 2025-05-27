/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* application includes--------------------------------------------------------*/
#include <ABDL_DataLink.h>

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
void ABDL_InitSocket(ABDL_Socket_t *this,const char *addressTxt,uint16_t port);
void ABDL_SendDirect(ABDL_DataLink_t *this,uint8_t *dataOut,uint16_t dataOutNb);
ABOS_DEFINE_TASK(ABDL_ReceiveThread);
ABOS_DEFINE_TASK(ABDL_SendThread);

/* public functions -----------------------------------------------------------*/
void ABDL_Init(ABDL_DataLink_t *this,bool_t isServer)
{
	printf("ABDL_Init\n");
	uint16_t receivePort=ABDL_SERVER_PORT;
	uint16_t sendPort=ABDL_CLIENT_PORT;
	if (isServer==M_FALSE)
	{
		receivePort=4164;
		sendPort=4163;
	}
	ABDL_InitSocket(&this->receiveSocket,"127.0.0.1",receivePort);
	if (bind(this->receiveSocket.sockfd, (struct sockaddr*)&this->receiveSocket.servaddr, sizeof(this->receiveSocket.servaddr))==ERROR)
	{
		printf("warning: ABDL_Init could not bind receive socket on port %d\n",receivePort);
	}
	ABDL_InitSocket(&this->sendSocket,"127.0.0.1",sendPort);

	this->isRunAgain=M_TRUE;

	//received queue
	LFQ_Init(&this->receiveQueue,this->receiveQueueBuffer,ABDL_RECEIVE_QUEUE_NB);
	ABOS_MutexCreate(&this->receiveQueueMutex);

	//start receive task
	ABOS_ThreadCreate(
			ABDL_ReceiveThread, /* function */
			(int8_t *)"ABDL_R_EXEC", /* name */
			ABDL_RECEIVE_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			ABDL_RECEIVE_THREAD_PRIORITY, /* priority */
			&this->threadReceive); /* handler */

	//send queue
	LFQ_Init(&this->sendQueue,this->sendQueueBuffer,ABDL_SEND_QUEUE_NB);
	ABOS_MutexCreate(&this->sendQueueMutex);

	//start receive task
	ABOS_ThreadCreate(
			ABDL_SendThread, /* function */
			(int8_t *)"ABDLS_EXEC", /* name */
			ABDL_SEND_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			ABDL_SEND_THREAD_PRIORITY, /* priority */
			&this->threadSend); /* handler */
}

void ABDL_Stop(ABDL_DataLink_t *this)
{
	this->isRunAgain=M_FALSE;
}

void ABDL_Send(ABDL_DataLink_t *this,uint8_t *dataOut,uint16_t dataOutNb)
{
	ABOS_MutexLock(&this->sendQueueMutex,ABOS_TASK_MAX_DELAY);
	if (LFQ_QueueAdd(&this->sendQueue,dataOut,dataOutNb)==M_TRUE)
	{
		printf("warning: ABDL_Send packet rejected\n");
		this->sendSocket.receivedRejectedNo++;
	}
	ABOS_MutexUnlock(&this->sendQueueMutex);
}


bool_t ABDL_GetOnePacket(ABDL_DataLink_t *this,uint8_t *dataIn,uint16_t *dataInNb)
{
	bool_t isData=M_FALSE;
	ABOS_MutexLock(&this->receiveQueueMutex,ABOS_TASK_MAX_DELAY);
	if (LFQ_QueueGet(&this->receiveQueue,dataIn,dataInNb))
	{
		isData=M_TRUE;
	}
	ABOS_MutexUnlock(&this->receiveQueueMutex);

	return isData;
}



/* local functions ------------------------------------------------------------*/
ABOS_DEFINE_TASK(ABDL_SendThread)
{
	ABDL_DataLink_t *this=(ABDL_DataLink_t*)param;
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];
	uint16_t packetSize;
	while(this->isRunAgain==M_TRUE)
	{
		ABOS_MutexLock(&this->sendQueueMutex,ABOS_TASK_MAX_DELAY);
		if (LFQ_QueueGet(&this->sendQueue,packetBuffer,&packetSize))
		{
			ABDL_SendDirect(this,packetBuffer,packetSize);
		}
		ABOS_MutexUnlock(&this->sendQueueMutex);

		ABOS_Sleep(ABDL_SEND_THREAD_MS);
	}
	return ABOS_TASK_RETURN;
}

ABOS_DEFINE_TASK(ABDL_ReceiveThread)
{
	int32_t n=ERROR;
	uint32_t len;
	ABDL_DataLink_t *this=(ABDL_DataLink_t*)param;
	uint8_t buffer[SBRO_PACKET_MAX_NB];
	while(this->isRunAgain==M_TRUE)
	{
		len = sizeof(this->receiveSocket.cliaddr);
		n = recvfrom(this->receiveSocket.sockfd, buffer, sizeof(buffer),
				0, (struct sockaddr*)&this->receiveSocket.cliaddr,&len); //receive message from server
		if (n!=0)
		{
			printf("ABDL_ReceiveThread received packet %d bytes\n",n);
			/* add packet to queue */
			ABOS_MutexLock(&this->receiveQueueMutex,ABOS_TASK_MAX_DELAY);
			if (LFQ_QueueAdd(&this->receiveQueue,buffer,n)==M_TRUE)
			{
				printf("warning: ABDL_ReceiveThread packet rejected\n");
				this->receiveSocket.receivedRejectedNo++;
			}
			ABOS_MutexUnlock(&this->receiveQueueMutex);
		}
		ABOS_Sleep(ABDL_RECEIVE_THREAD_MS);
	}
	return ABOS_TASK_RETURN;
}

void ABDL_InitSocket(ABDL_Socket_t *this,const char *addressTxt,uint16_t port)
{
	this->receivedRejectedNo=0;
	this->receivedNo=0;
	this->sentNo=0;
	strcpy(this->addressText,addressTxt);
	this->port=port;

	//actual socket initialization
	memset(&this->servaddr, 0, sizeof(this->servaddr));
	memset(&this->cliaddr, 0, sizeof(this->cliaddr));
	if ( (this->sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		printf("error: NURD_InitConnection: socket creation failed\n");
	}
	else
	{
		this->servaddr.sin_family    = AF_INET; // IPv4
		this->servaddr.sin_addr.s_addr = inet_addr(addressTxt);
		this->servaddr.sin_port = htons(this->port);

		this->client_addr_len = sizeof(struct sockaddr_in);
	}
}

void ABDL_SendDirect(ABDL_DataLink_t *this,uint8_t *dataOut,uint16_t dataOutNb)
{
	uint16_t n=sendto(this->sendSocket.sockfd, (const char *)dataOut, dataOutNb,
			MSG_CONFIRM, (const struct sockaddr *) &this->sendSocket.servaddr,
			sizeof(this->sendSocket.servaddr));
	if (n>0)
	{
		this->sendSocket.sentNo++;
	}
	else
	{
		printf("ERROR: ABDL_Send sending data\n");
	}
}

/* end */
