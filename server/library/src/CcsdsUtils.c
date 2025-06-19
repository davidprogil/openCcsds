/*******************************************************************************/
/* Copyright David Gil 1998-2025                                               */
/* 								                                               */
/* davidgil@dgadv.com 			                                               */
/*******************************************************************************/

/* system includes-------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>

/* application includes--------------------------------------------------------*/
#include <SBCC_CcsdsUtils.h>

/* component includes----------------------------------------------------------*/
/* none */

/* local macros ---------------------------------------------------------------*/
/* none */

/* local types ----------------------------------------------------------------*/
/* none */

/* public variables -----------------------------------------------------------*/
/* none */

/* local variables ------------------------------------------------------------*/
/* none */

/* local prototypes -----------------------------------------------------------*/
/* none */

/* public functions -----------------------------------------------------------*/
bool_t CCSDS_CreatePacket(uint8_t *target,uint16_t targetNb,bool_t isTc,bool_t hasSecondaryHeader,uint16_t apid,uint16_t sequenceCount,uint16_t dataLength,uint8_t *data)
{
	bool_t isError=M_FALSE;
	if (targetNb<dataLength+sizeof(CCSDS_PrimaryHeader_t))
	{
		isError=M_TRUE;
	}
	else
	{
		//header
		CCSDS_PrimaryHeader_t *primaryHeader=(CCSDS_PrimaryHeader_t *)&target[0];
		//uint8_t versionNumber:3; //0 CCSDS 133.0-B-1
		primaryHeader->versionNumber=CCSDS_VERSION_NUMBER;
		//uint8_t packetType:1; //0-TM, 1-TC
		primaryHeader->packetType=isTc;
		//uint8_t secondaryHeader:1; //0-no 1-yes
		primaryHeader->secondaryHeader=hasSecondaryHeader;
		//uint16_t apid:11;
		primaryHeader->apid=apid;
		//uint8_t sequenceFlag:2; //11 for stand alone
		primaryHeader->sequenceFlag=CCSDS_STANDALONE_PACKET;
		//uint16_t sequenceCount:14;
		primaryHeader->sequenceCount=sequenceCount;
		primaryHeader->dataLength=dataLength;
		//copy the data to the packet
		for (uint16_t bIx=0;bIx<dataLength;bIx++)
		{
			//printf("debug: %d %d\n",bIx,data[bIx]);
			target[sizeof(CCSDS_PrimaryHeader_t)+bIx]=data[bIx];
			//printf("debug: %d %d %d\n",bIx,data[bIx],target[sizeof(primaryHeader)+bIx]);
		}
	}

	return isError;
}

void CCSDS_PrintPacket(CCSDS_Packet_t *this)
{
	printf("CCSDS packet:\n");
	//header
	//uint8_t versionNumber:3; //0 CCSDS 133.0-B-1
	printf("\t versionNumber: %d\n",this->primaryHeader.versionNumber);
	//uint8_t packetType:1; //0-TM, 1-TC
	printf("\t packetType: %d\n",this->primaryHeader.packetType);
	//uint8_t secondaryHeader:1; //0-no 1-yes
	printf("\t secondaryHeader: %d\n",this->primaryHeader.secondaryHeader);
	//uint16_t apid:11;
	printf("\t apid: %d\n",this->primaryHeader.apid);
	//sequence control
	//uint8_t sequenceFlag:2; //11 for stand alone
	printf("\t sequenceFlag: %d\n",this->primaryHeader.sequenceFlag);
	//uint16_t sequenceCount:14;
	printf("\t sequenceFlag: %d\n",this->primaryHeader.sequenceCount);
	//packet data length //16 bits
	//uint16_t dataLength;
	printf("\t dataLength: %d\n",this->primaryHeader.dataLength);
	//data
	printf("\t data:");
	for (uint16_t bIx=0;bIx<this->primaryHeader.dataLength;bIx++)
	{
		printf(" %d",((uint8_t*)&this->data)[bIx]);
	}
	printf("\n");
}


/* local functions ------------------------------------------------------------*/
/* none */

/* end */
