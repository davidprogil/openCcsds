/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* application includes--------------------------------------------------------*/
#include <LIB_Comparators.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
#define CMP_COMPARE_FUNCTION_BODY bool_t  criteriaMet = M_FALSE;\
		if (isEqualAllwowed)\
		{criteriaMet = (wanted == received);}\
		if (M_FALSE == criteriaMet){\
			if (isSmaller)	{criteriaMet = (received < wanted);	}\
			else	{		criteriaMet = (received > wanted);	}}\
			return criteriaMet;

#define CMP_COMPARE_FUNCTION_EQUAL_BODY return (wanted == received);
/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
/* none */

/* public functions -----------------------------------------------------------*/
void CMP_Init(CMP_Comparators_t *this)
{
	//printf("CMP_Init\n");
	memset(this,0,sizeof(CMP_Comparators_t));
}

void CMP_Execute(CMP_Comparators_t *this)
{
	//printf("CMP_Execute\n");
}

CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint8,uint8_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt8,	int8_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint16,uint16_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt16,	int16_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint32,uint32_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt32,	int32_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareUint64,uint64_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareInt64,	int64_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareFloat32,	float32_t)
{
	CMP_COMPARE_FUNCTION_BODY
}
CMP_COMPARE_FUNCTION_PROTOTYPE(CMP_CompareFloat64,	float64_t)
{
	CMP_COMPARE_FUNCTION_BODY
}

CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint8,	uint8_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt8,		int8_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint16,	uint16_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt16,	int16_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint32,	uint32_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt32,	int32_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualUint64,	uint64_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualInt64,	int64_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualFloat32,	float32_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
CMP_COMPARE_FUNCTION_EQUAL_PROTOTYPE(CMP_CompareEqualFloat64,	float64_t)
{
	CMP_COMPARE_FUNCTION_EQUAL_BODY;
}
/* local functions ------------------------------------------------------------*/
/* none */

/* end */
