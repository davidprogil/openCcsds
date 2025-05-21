/*******************************************************************************/
/* Copyright David Gil 1998-TODO                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

#ifndef CMP_Comparators_H
#define CMP_Comparators_H

/* system includes-------------------------------------------------------------*/
/* none */

/* application includes--------------------------------------------------------*/
#include <myTypes.h>

/* component includes----------------------------------------------------------*/
/* none */

/* macros-----------------------------------------------------------------------*/
#define CMP_COMPARE_FUNCTION_PROTOTYPE(name,type) bool_t (name)(type received,type wanted,bool_t isSmaller, bool_t isEqualAllwowed)
#define CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(name,type) bool_t (name)(type received,type wanted)

/* types------------------------------------------------------------------------*/
typedef struct _CMP_Comparators_t_
{

}CMP_Comparators_t;

/* public variables-------------------------------------------------------------*/
/* none */

/* public functions--------------------------------------------------------------*/
void CMP_Init(CMP_Comparators_t *this);
void CMP_Execute(CMP_Comparators_t *this);

CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint8,	uint8_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt8,		int8_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint16,	uint16_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt16,	int16_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint32,	uint32_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt32,	int32_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint64,	uint64_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt64,	int64_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareFloat32,	float32_t);
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareFloat64,	float64_t);

CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint8,	uint8_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt8,		int8_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint16,	uint16_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt16,	int16_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint32,	uint32_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt32,	int32_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint64,	uint64_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt64,	int64_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualFloat32,	float32_t);
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualFloat64,	float64_t);

/* end */
#endif /* CMP_Comparators_H */

