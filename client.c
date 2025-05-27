
/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* application includes--------------------------------------------------------*/
#include <configuration.h>
#include <ABOS_Osal.h>
#include <ABDL_DataLink.h>
#include <SBCC_CcsdsUtils.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define MAIN_INFINITE_CYCLE_PERIOD_MS (1000)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
ABOS_Osal_t osal;
ABDL_DataLink_t dataLink;
uint16_t sequenceCount=0;
bool_t isRunAgain=M_TRUE;
uint32_t upTime=0;

/* local prototypes -----------------------------------------------------------*/
/* none */


/* public functions -----------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("CLIENT\n");

	//hardware initialization
	//not applicable in standard linux pc

	//checks
	printf("size of CCSDS_PrimaryHeader_t: %ld\n",sizeof(CCSDS_PrimaryHeader_t));

	//library initializations
	//TODO

	//abstraction initialization
	ABOS_Init(&osal);
	ABDL_Init(&dataLink,M_FALSE);

	//other starts
	//TODO

	//Infinite Cycle
	uint8_t packetBuffer[SBRO_PACKET_MAX_NB];
	uint16_t receivedNb;
	while (isRunAgain==M_TRUE)
	{

		printf("client %d\n",upTime);

		//send packets
		if ((upTime>0)&&(upTime%5==0))
		{
			printf("time to send packet\n");
			uint8_t dummyDataToSend[2] = {sequenceCount+3,sequenceCount+4};

			//printf("size of packet to send: %ld\n",sizeof(packetBuffer));

			if (CCSDS_CreatePacket(
					packetBuffer, //target
					sizeof(packetBuffer), //targetNb
					M_TRUE, //isTc
					M_FALSE, //hasSecondaryHeader,
					APP1_APID,//apid,
					sequenceCount,
					sizeof(dummyDataToSend),
					dummyDataToSend) ==M_FALSE)
			{

				CCSDS_PrintPacket((CCSDS_Packet_t*) packetBuffer);

				//send the packet
				ABDL_Send(&dataLink,packetBuffer,sizeof(CCSDS_PrimaryHeader_t)+sizeof(dummyDataToSend));

				//increment counter of sent packets, note, in CCSDS standard this counter is to be maintained for each PID
				sequenceCount++;
			}
			else
			{
				printf("warning: main, error creating packet\n");
			}
		}
		//receive packets
		if (ABDL_GetOnePacket(&dataLink,packetBuffer,&receivedNb))
		{
			CCSDS_PrintPacket((CCSDS_Packet_t*) packetBuffer);
		}

		//wait
		ABOS_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
		upTime++;

	}
	//wait for all tasks to stop hopefully
	ABOS_Sleep(1000);
	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





