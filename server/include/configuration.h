/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
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
#define GROUND_APID (10)
#define APP1_APID (1)

//Maestro
#define CMAS_OVERRUNS_MAX_NO (5)

//thread configuration
#define MAESTRO_THREAD_STACK_SIZE (0)
#define MAESTRO_THREAD_PRIORITY (0)
#define EXECUTE_THREAD_STACK_SIZE (0)
#define EXECUTE_THREAD_PRIORITY (0)

#define APP1_THREAD_STACK_SIZE (0)
#define APP1_THREAD_PRIORITY (0)

#define SBRO_THREAD_STACK_SIZE (0)
#define SBRO_THREAD_PRIORITY (0)

#define ABDL_RECEIVE_THREAD_STACK_SIZE (0)
#define ABDL_RECEIVE_THREAD_PRIORITY (0)
#define ABDL_SEND_THREAD_STACK_SIZE (0)
#define ABDL_SEND_THREAD_PRIORITY (0)

//scheduling of apps
#define ABOS_MAESTRO_PERIOD_MS (1000)
#define CMAS_MAESTRO_APPS_NO (2)
#define SWBUS_TIME_START_MS (10)
#define SWBUS_TIME_LENGTH_MS (90)
#define APP1_TIME_START_MS (110)
#define APP1_TIME_LENGTH_MS (90)

//SW BUS Configuration
#define SBRO_TC_SUBSCRIBERS_MAX_NO (6)
#define SBRO_QUEUE_NB (2000)
#define SBRO_PACKET_MAX_NB (256)

//Datalink
#define ABDL_RECEIVE_QUEUE_NB (2000)
#define ABDL_SEND_QUEUE_NB (2000)
#define ABDL_SERVER_PORT (4163)
#define ABDL_CLIENT_PORT (4164)
#define ABDL_RECEIVE_THREAD_MS (250)
#define ABDL_SEND_THREAD_MS (250)

//Application 1
#define APP1_QUEUE_NB (SBRO_PACKET_MAX_NB*4)
#define APP1_TC_MAX_NB (4)

/* types------------------------------------------------------------------------*/
/* none */

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
/* none */


/* end */
#endif /* CONFIGURATION_H */
