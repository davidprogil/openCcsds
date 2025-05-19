
/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

/* application includes--------------------------------------------------------*/
#include <ABST_Osal.h>
#include <CORE_Maestro.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define MAIN_INFINITE_CYCLE_PERIOD_MS (2000)

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
CMAS_Maestro_t maestro;
ABST_Osal_t osal;

/* local prototypes -----------------------------------------------------------*/
/* none */


/* public functions -----------------------------------------------------------*/
int main(int argc, char *argv[])
{
	printf("SERVER\n");

	//road map:
	// x server folder
	// x maestro template and init integrated
	// - OSAL integrated
	// - maestro running each 1 sec
	// - application1 template and init integrated
	// - maestro scheduling application1

	//hardware initialization
	//not applicable in standard linux pc

	//library initalizations
	//TODO

	//abstraction initialization
	ABST_Init(&osal);

	//Maestro Initialization and wait
	CMAS_Init(&maestro);
	ABST_Sleep(100);

	//maestro start
	CMAS_Start(&maestro);

	//other starts
	//TODO

	//Infinite Cycle
	//unblock maestro
	//TODO

	while (maestro.isRunAgain==M_TRUE)
	{
		//wait
		ABST_Sleep(MAIN_INFINITE_CYCLE_PERIOD_MS);
	}

	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





