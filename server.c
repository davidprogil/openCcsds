
/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <ABOS_Osal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/* application includes--------------------------------------------------------*/
#include <CORE_Maestro.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define MAIN_INFINITE_CYCLE_PERIOD_MS (1000)
//TODO move to configuration
#define GROUND_APID (0)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
CMAS_Maestro_t maestro;
ABOS_Osal_t osal;
uint16_t sequenceCount=0;
/* local prototypes -----------------------------------------------------------*/
/* none */


/* public functions -----------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("SERVER\n");

	//road map:
	// x server folder
	// x maestro template and init integrated
	// x OSAL integrated
	// x maestro running each 1 sec
	// x application1 template and init integrated
	// x maestro scheduling application1
	// - server sends commands to application
	// - application responds back
	// - exchange data through sockets
	// - address TODOs
	// - documentation


	//hardware initialization
	//not applicable in standard linux pc

	//checks
	printf("size of CCSDS_PrimaryHeader_t: %ld\n",sizeof(CCSDS_PrimaryHeader_t));

	//library initializations
	//TODO

	//abstraction initialization
	ABOS_Init(&osal);

	//Maestro Initialization and wait
	CMAS_Init(&maestro);
	ABOS_Sleep(100);

	//maestro start
	CMAS_Start(&maestro);

	//other starts
	//TODO

	//Infinite Cycle
	while (maestro.isRunAgain==M_TRUE)
	{
		//wait
		ABOS_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
		printf("server %d\n",maestro.upTime);
		//TODO debug create and send packet
		if ((maestro.upTime==3)||(maestro.upTime==6))
		{
			uint8_t dummyDataToSend[2] = {sequenceCount+3,sequenceCount+4};
			uint8_t packetBuffer[sizeof(CCSDS_PrimaryHeader_t)+sizeof(dummyDataToSend)];
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

				printf("SERVER: sending this packet:\n");
				CCSDS_PrintPacket((CCSDS_Packet_t*) packetBuffer);
				//send the packet
				SBRO_Publish(&maestro.swBus,packetBuffer,sizeof(packetBuffer));
				//increment counter of sent packets, note, in CCSDS standard this counter is to be maintained for each PID
				sequenceCount++;
			}
			else
			{
				printf("warning: main, error creating packet\n");
			}
		}

		//TODO debug exit
		if (maestro.upTime>=10)
		{
			//TODO stop signal instead
			maestro.isRunAgain=M_FALSE;
		}
	}
	//wait for all tasks to stop hopefully
	ABOS_Sleep(1000);
	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





