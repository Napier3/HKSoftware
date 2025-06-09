//////////////////////////////////////////////////////////////////////////
//DataAddrVector.h
#ifndef mms_data_addr_vector_h__
#define mms_data_addr_vector_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include<string.h> 
#include <stdlib.h>
#include <WTypes.h>
#include "61850ClientGlobalDef.h"



#define VECTOR_ADD_NUMBER 10

	typedef struct DatasAddrVector
	{
		ST_INT        capacity;
		ST_INT		numOfData;			//数据个数
		unsigned long* Datas;
	}MMS_ADDR_VECTOR,  *PMMS_ADDR_VECTOR;

	extern void vector_add_capacity(PMMS_ADDR_VECTOR pVector, long nCount);
	extern void vector_free(PMMS_ADDR_VECTOR pVector);
	extern void vector_set_add_data(PMMS_ADDR_VECTOR pVector, LPVOID *pData, long nDataSize);
	extern void vector_add_data(PMMS_ADDR_VECTOR pVector, LPVOID pData);

#ifdef __cplusplus
}
#endif

#endif	// mms_data_addr_vector_h__
