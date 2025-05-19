/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef CMAS_Maestro_H
#define CMAS_Maestro_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
typedef struct _CMAS_Maestro_t_
{
	bool_t isRunAgain;
}CMAS_Maestro_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void CMAS_Init(CMAS_Maestro_t *this);
void CMAS_Execute(CMAS_Maestro_t *this);


/* end */
#endif /* CMAS_Maestro_H */

