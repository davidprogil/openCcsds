/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef ABST_Osal_H
#define ABST_Osal_H

/* system includes-------------------------------------------------------------*/
#include <unistd.h>

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
/* none */

/* types------------------------------------------------------------------------*/
typedef struct _ABST_Osal_t_
{

}ABST_Osal_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void ABST_Init(ABST_Osal_t *this);
void ABST_Execute(ABST_Osal_t *this);
void ABST_Sleep(uint32_t milliseconds);

/* end */
#endif /* ABST_Osal_H */

