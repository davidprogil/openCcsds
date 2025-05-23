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
void ABDL_Execute(ABDL_DataLink_t *this);
void ABDL_InitSocket(ABDL_Socket_t *this,const char *addressTxt,uint16_t port);
ABOS_DEFINE_TASK(ABDL_ReceiveThread);

/* public functions -----------------------------------------------------------*/
void ABDL_Init(ABDL_DataLink_t *this)
{
	printf("ABDL_Init\n");
	ABDL_InitSocket(&this->socket,"127.0.0.1",4163);//TODO replace by defines in configuration

	this->isRunAgain=M_TRUE;

	//received queue
	LFQ_Init(&this->receiveQueue,this->receiveQueueBuffer,ABDL_RECEIVE_QUEUE_NB);
	ABOS_MutexCreate(&this->receiveQueueMutex);

	//start task
	ABOS_ThreadCreate(
			ABDL_ReceiveThread, /* function */
			(int8_t *)"ABDL_R_EXEC", /* name */
			ABDL_RECEIVE_THREAD_STACK_SIZE, /* stack depth */
			(void *)this, /* parameters */
			ABDL_RECEIVE_THREAD_PRIORITY, /* priority */
			&this->threadReceive); /* handler */
}

void ABDL_SetServer(ABDL_DataLink_t *this)
{
	bind(this->socket.sockfd, (struct sockaddr*)&this->socket.servaddr, sizeof(this->socket.servaddr));
}

void ABDL_Send(ABDL_DataLink_t *this,uint8_t *dataOut,uint16_t dataOutNb)
{
	uint16_t n=sendto(this->socket.sockfd, (const char *)dataOut, dataOutNb,
			MSG_CONFIRM, (const struct sockaddr *) &this->socket.servaddr,
			sizeof(this->socket.servaddr));
	if (n>0)
	{
		this->socket.sentNo++;
	}
	else
	{
		printf("ERROR: ABDL_Send sending data\n");
	}
}



/* local functions ------------------------------------------------------------*/
void ABDL_Execute(ABDL_DataLink_t *this)
{
	printf("ABDL_Execute\n");
}

ABOS_DEFINE_TASK(ABDL_ReceiveThread)
{
	int32_t n=ERROR;
	uint32_t len;
	ABDL_DataLink_t *this=(ABDL_DataLink_t*)param;
	uint8_t buffer[SBRO_PACKET_MAX_NB];
	while(this->isRunAgain==M_TRUE)
	{
		len = sizeof(this->socket.cliaddr);
		n = recvfrom(this->socket.sockfd, buffer, sizeof(buffer),
				0, (struct sockaddr*)&this->socket.cliaddr,&len); //receive message from server
		if (n!=0)
		{
			printf("ABDL_ReceiveThread received packet %d bytes\n",n);
			/* add packet to queue */
			ABOS_MutexLock(&this->receiveQueueMutex,ABOS_TASK_MAX_DELAY);
			if (LFQ_QueueAdd(&this->receiveQueue,buffer,n)==M_TRUE)
			{
				printf("warning: ABDL_ReceiveThread packet rejected\n");
				this->socket.receivedRejectedNo++;
			}
			ABOS_MutexUnlock(&this->receiveQueueMutex);
		}
		ABOS_Sleep(10);//TODO replace by macro
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
		printf("error: NURD_InitConnection: socket creation failed");//TODO
	}
	else
	{
		this->servaddr.sin_family    = AF_INET; // IPv4
		this->servaddr.sin_addr.s_addr = inet_addr(addressTxt);
		this->servaddr.sin_port = htons(this->port);

		this->client_addr_len = sizeof(struct sockaddr_in);
	}
}

/* end */
