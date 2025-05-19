
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
/* none */

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

	//Maestro Initialization
	CMAS_Init(&maestro);
	//wait
	ABST_Sleep(100);

	//other starts
	//TODO

	//Infinite Cycle
	//unblock maestro
	//TODO
	//wait
	//TODO

	printf("END\n");
	return EXIT_SUCCESS;
}
/* local functions ------------------------------------------------------------*/
/* none */



/* end */





