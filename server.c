
/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
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
	// x server sends commands to application
	// x configuration file
	// x client/server separation
	// x data link abstraction
	// x - application responds back
	// x -handle TM PID
	// x - make SendDirect private
	// x - client handles response
	// x - APID 0 is reserved for spacecraft time packets
	// x - address TODOs
	// x - mechanism to safely stop threads
	// - documentation
	// - template
	// - intro
	// - architecture static
	// - architecture dynamic
	// - integration example PPC
	// - add application


	//hardware initialization
	//not applicable in standard linux pc

	//checks
	printf("size of CCSDS_PrimaryHeader_t: %ld\n",sizeof(CCSDS_PrimaryHeader_t));

	//library initializations
	//NA

	//abstraction initialization
	ABOS_Init(&osal);

	//Maestro Initialization and wait
	CMAS_Init(&maestro);
	ABOS_Sleep(100);

	//maestro start
	CMAS_Start(&maestro);

	//other starts
	//NA

	//Infinite Cycle
	while (maestro.isRunAgain==M_TRUE)
	{
		//wait
		ABOS_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
	}
	//wait for all tasks to stop hopefully
	ABOS_Sleep(1000);
	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





