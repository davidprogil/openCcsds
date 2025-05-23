/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/* system includes-------------------------------------------------------------*/
#include<stdlib.h>

/* application includes--------------------------------------------------------*/
/* none */

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
//APID
#define GROUND_APID (0)
#define APP1_APID (1)

#define APP1_QUEUE_NB (SBRO_PACKET_MAX_NB*4)

//thread configuration
#define MAESTRO_THREAD_STACK_SIZE (0)
#define MAESTRO_THREAD_PRIORITY (0)
#define EXECUTE_THREAD_STACK_SIZE (0)
#define EXECUTE_THREAD_PRIORITY (0)

#define APP1_THREAD_STACK_SIZE (0)
#define APP1_THREAD_PRIORITY (0)

#define SBRO_THREAD_STACK_SIZE (0)
#define SBRO_THREAD_PRIORITY (0)

//scheduling of apps
#define ABOS_MAESTRO_PERIOD_MS (1000)
#define SWBUS_WAIT_BEFORE_MS (10)
#define SWBUS_TIME_LENGTH_MS (90)
#define PROCESS1_WAIT_BEFORE_MS (110)
#define PROCESS1_TIME_LENGTH_MS (100)

//SW BUS Configuration
#define SBRO_SUBSCRIBERS_MAX_NO (6) //TODO move to configuration
#define SBRO_QUEUE_NB (2000) //TODO move to configuration
#define SBRO_PACKET_MAX_NB (256) //TODO move to configuration


/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
/* none */


/* end */
#endif /* CONFIGURATION_H */
