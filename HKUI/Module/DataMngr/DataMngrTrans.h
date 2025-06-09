#pragma once

#include "ShortDatas.h"
#include "DvmDataset.h"
#include "DvmLogicDevice.h"

void Append_Datas(CExBaseList *pDestDatas, CDvmDataset *pSrcDatas, BOOL bAddSame=TRUE);
void Append_Datas(CExBaseList *pDestDatas, CExBaseList *pSrcDatas, BOOL bAddSame=TRUE);

void DvmDatas_to_ShortDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas);
void ShortDatas_to_DvmDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas);

void SetVal_DvmDatas_by_ShortDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas);
void SetVal_ShortDatas_by_DvmDatas(CExBaseList *pSrcDatas, CExBaseList *pDestDatas);

void Copy_Data(CShortData *pDestData, CDvmData *pSrcData);
void Copy_Data(CDvmData *pDestData, CShortData *pSrcData);



CDvmData* dvm_AddValuesToDataset(CValues *pValues, CDvmDataset *pDataDef, CDvmDataset *pDsDest);
BOOL dvm_ValidateValuesByDef(CValues *pValues, CDvmDataset *pDataDef);
CDvmData* dvm_FindDataInDataset(CValues *pValues, CDvmDataset *pDsDest);
BOOL dvm_IsSameData(CValues *pValues, CDvmData *pDvmData);
void dvm_SetDvmData(CValues *pValues, CDvmData *pDvmData);

BOOL dvm_IsSameDataset_id_value(CDvmDataset *pSrc, CDvmDataset *pDest);
BOOL dvm_IsSameData_id_value(CDvmData *pSrc, CDvmData *pDest);

CDvmDataset* dvm_FindDsByDatas(CDvmLogicDevice *pLdevice, CDvmDataset *pSrcDs);

//2021-2-23  lijunqing
void DvmDataset_to_Values(CDvmDataset *pSrc, CValues *pValues);

//2022-7-24  lijunqing
void DvmDatas_to_Values(CExBaseList *pSrc, CValues *pValues);
