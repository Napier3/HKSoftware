//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjModule.cpp  CSttAdjModule


#include "stdafx.h"
#include "SttAdjModule.h"
#include "SttMesLocalDb.h"
#include "../SttGlobalDef.h"
#include "../SttCmd/SttParas.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttAdjModule::CSttAdjModule()
{
	//初始化属性
	m_nChannelCnt = 8;
	m_nWaveCnt = 32;
	//初始化成员变量

	m_bModifiedFlag = FALSE;
}

CSttAdjModule::~CSttAdjModule()
{

}

CDataGroup* CSttAdjModule::GetModuleAttrs()
{
	return GetModuleAttrs(m_pSttAdjRef);
}

CDataGroup* CSttAdjModule::GetModuleAttrs(CDataGroup *pModule)
{
	if (pModule == NULL)
	{
		return NULL;
	}

	return pModule->FindByDataType(STT_ADJ_DATA_TYPE_ModuleAttrs);
}

void CSttAdjModule::GetModuleAttrs(CDataGroup *pModule, BOOL bOnlyAttrs)
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return;
	}

	if (!bOnlyAttrs)
	{
		pModule->AddNewChild((CExBaseObject*)pAttrs->Clone());
		return;
	}

	POS pos = pAttrs->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pAttrsNew = (CDataGroup*)pAttrs->CloneEx();
	pModule->AddNewChild(pAttrsNew);

	while (pos != NULL)
	{
		p = pAttrs->GetNext(pos);
		
		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			pAttrsNew->AddNewChild((CExBaseObject*)p->Clone());
		}
	}
}

void CSttAdjModule::GetAttrs()
{
	CDataGroup* pAttrGroup = GetModuleAttrs();
	pAttrGroup->GetDataValue(STT_ADJ_ID_Model, m_strModel);
	pAttrGroup->GetDataValue(STT_ADJ_ID_SN, m_strSN);
	pAttrGroup->GetDataValue(STT_ADJ_ID_FACTORY, m_strFactory);
	pAttrGroup->GetDataValue(STT_ADJ_ID_DATEFAC, m_strDateFac);
	pAttrGroup->GetDataValue(STT_ADJ_ID_StateCount, m_nStateCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_BinCount, m_nBinCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_BoutCount, m_nBoutCount);
	pAttrGroup->GetDataValue(STT_ADJ_ID_STModeSet, m_nSTModeSet);
	pAttrGroup->GetDataValue(STT_ADJ_ID_UartCount,m_nUartCount);
}

CDataGroup* CSttAdjModule::GetHdGear(const CString &strHdGearID)
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDataGroup *pFind = (CDataGroup*)pAttrs->FindByID(strHdGearID);

	return pFind;
}


// 2020-10-15 mym 获取硬件档位
CDataGroup* CSttAdjModule::GetHdGearItem(const CString &strHdGearID)
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDataGroup *pFindHdGearID = (CDataGroup*)pAttrs->FindByID(strHdGearID);
	if (pFindHdGearID==NULL)
		return NULL;
	//CString strHdGear_GearID = _T("HdGear0");
	return (CDataGroup*)pFindHdGearID->FindByDataType(STT_ADJ_DATA_TYPE_HdGear);//FindByID(strHdGear_GearID);//
}


// 2020-10-15 mym 添加硬件档位
CDataGroup* CSttAdjModule::AddNewHdGear(const CString &strHdGearID)
{
	CDataGroup *pNew  =  NULL; 
	CDataGroup *pHardGears  = GetHdGear(strHdGearID);
	if (pHardGears==NULL)
		return NULL;
// 	CDvmData *pDvmData = (CDvmData *)pHardGears->FindByID(STT_ADJ_ID_HdGearCount);
// 	if (pDvmData==NULL)
// 		return NULL;
	CDataGroup *pHardGears_Gear  =  GetHdGearItem(strHdGearID);
	if (pHardGears_Gear==NULL)
		return NULL;

	pNew = (CDataGroup*)pHardGears_Gear->Clone();
	pHardGears->AddNewChild(pNew, TRUE);
// 
// 	int nHdGearCount  = atoi (pDvmData->m_strValue);
// 	nHdGearCount++;
// 	pDvmData->m_strValue.Format(_T("%d"),  nHdGearCount );

	stt_IncreaseCountData(pHardGears, STT_ADJ_ID_HdGearCount);

	return pNew;
}


void  CSttAdjModule::DeleteHdGear(CDataGroup*pDataGroup, const CString &strHdGearID,  long nValAdd)
{
	stt_DecreaseCountData(pDataGroup, strHdGearID, nValAdd);
}

CDataGroup* CSttAdjModule::GetHdChDefine()
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDataGroup *pChMapDef = (CDataGroup*)pAttrs->FindByID(STT_ADJ_ID_ChMapDef);
	
	if (pChMapDef == NULL)
	{
		return NULL;
	}

	CDataGroup *pHdChDefine = (CDataGroup*)pChMapDef->FindByID(STT_ADJ_ID_ChDefine);

	return pHdChDefine;
}

CDataGroup* CSttAdjModule::GetChDrvPos()
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDataGroup *pChMapDef = (CDataGroup*)pAttrs->FindByID(STT_ADJ_ID_ChMapDef);
	
	if (pChMapDef == NULL)
	{
		return NULL;
	}

	CDataGroup *pChMaps = (CDataGroup*)pChMapDef->FindByID(STT_ADJ_ID_ChDrvPos);

	return pChMaps;
}

CDataGroup* CSttAdjModule::GetAdjustParas()
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pAdjustParas = (CDataGroup*)m_pSttAdjRef->FindByDataType(STT_ADJ_DATA_TYPE_AdjustParas);
	return pAdjustParas;
}

CDataGroup* CSttAdjModule::GetAdjTRange(long nIndex)
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pAdjustParas = GetAdjustParas();

	if (pAdjustParas == NULL)
	{
		return NULL;
	}

	return (CDataGroup*)pAdjustParas->FindByDataType(STT_ADJ_DATA_TYPE_TRange, nIndex);
}

CDataGroup* CSttAdjModule::GetAdjTRange(const CString &strT_Range)
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pAdjustParas = GetAdjustParas();

	if (pAdjustParas == NULL)
	{
		return NULL;
	}

	//2021-5-3  lijunqing
	CDataGroup *pTrange = (CDataGroup*)pAdjustParas->FindByID(strT_Range);

	if (pTrange != NULL)
	{
		return pTrange;
	}

	return GetAdjTRange(0);
}

CDataGroup* CSttAdjModule::GetAdjChannel(const CString &strT_Range, const CString &strChID)
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pT_Range = GetAdjTRange(strT_Range);

	if (pT_Range == NULL)
	{
		return NULL;
	}

	if (strChID == STT_ADJ_ID_Ch_Idc || strChID == STT_ADJ_ID_Ch_Udc)
	{
		return NULL;
	}

	return (CDataGroup*)pT_Range->FindByID(strChID);
}

CDataGroup* CSttAdjModule::GetAdjChWaveAdjusts(const CString &strT_Range, const CString &strChID, const CString &strWaveID)
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pT_Range = GetAdjTRange(strT_Range);

	if (pT_Range == NULL)
	{
		return NULL;
	}

	if (strChID == STT_ADJ_ID_Ch_Idc)
	{
		return (CDataGroup*)pT_Range->FindByID(STT_ADJ_ID_Ch_Idc);
	}

	if (strChID == STT_ADJ_ID_Ch_Udc)
	{
		return (CDataGroup*)pT_Range->FindByID(STT_ADJ_ID_Ch_Udc);
	}

	CDataGroup *pChannel = (CDataGroup*)pT_Range->FindByID(strChID);

	if (pChannel == NULL)
	{
		return NULL;
	}

	return (CDataGroup*)pChannel->FindByID(strWaveID);
}

CDataGroup* CSttAdjModule::AddNewChMap()
{
	CDataGroup *pChMaps = GetHdChDefine();
	CDataGroup *pNewMap = AddNewChMap(pChMaps);

	return pNewMap;
}

CDataGroup* CSttAdjModule::AddNewChMap(CDataGroup *pMaps)
{
	CDataGroup *pMap = pMaps->AddNewGroup(_T("通道映射"), _T("ChMap"), _T("ChMap"));
	pMap->AddNewData(_T("Index"), _T("Index"), _T("long"), _T("0"));
	pMap->AddNewData(_T("ID"), _T("ID"), _T("long"), _T(""));

	return pMap;
}

CDvmData* CSttAdjModule::AddNewChDrvPos()
{
	CDataGroup *pChMaps = GetChDrvPos();
	CDvmData *ChDrvPos = AddNewChDrvPos(pChMaps);

	return ChDrvPos;
}

CDvmData* CSttAdjModule::AddNewChDrvPos(CDataGroup *pMaps)
{
	long nDataCnt = pMaps->GetChildCount(DVMCLASSID_CDVMDATA);
	CString strName,  strID,  strDataType = _T(""),  strValue;
	strName.Format(_T("Ch%dPos"),  nDataCnt + 1);
	strID.Format(_T("Ch%dPos"),  nDataCnt + 1);
	strValue.Format(_T("%d"),  nDataCnt);

	CDvmData *pNew = pMaps->AddNewData(strName,  strID,  strDataType, strValue);

	return pNew;
}

//添加温区 2020-10-12 mym
CDataGroup* CSttAdjModule::AddNewTrang()
{
	CDataGroup *pTRange = GetAdjTRange(0);

	if (pTRange == NULL)
	{
		return NULL;
	}

	CDataGroup *pAdjustParas = GetAdjustParas();
	CDataGroup *pNew = (CDataGroup*)pTRange->Clone();
	pAdjustParas->AddNewChild(pNew, TRUE);

	return pNew;
}


CDvmData* CSttAdjModule::GetModuleType(CDataGroup *pModule)
{
	CDataGroup *pAttrs = GetModuleAttrs(pModule);

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDvmData *pModuleType = (CDvmData*)pAttrs->FindByID(STT_ADJ_ID_ModuleType);

	return pModuleType;
}



CDvmData*  CSttAdjModule::GetModuleType()
{
	return GetModuleType(m_pSttAdjRef);
}


BOOL CSttAdjModule::GetModel(CString &strModel)
{
	CDvmData *pModel = GetModel();

	if (pModel == NULL)
	{
		strModel.Empty();
		return FALSE;
	}
	else
	{
		strModel = pModel->m_strValue;
		return TRUE;
	}
}

CDvmData*  CSttAdjModule::GetModel()
{
	CDataGroup *pAttrs = GetModuleAttrs();

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDvmData *pModel = (CDvmData*)pAttrs->FindByID(STT_ADJ_ID_Model);

	return pModel;
}


// mym 2021-4-22 add
BOOL  CSttAdjModule::GetModulePos(CString &strModulePos)
{
	CDvmData *pModulePos = GetModulePos();

	if (pModulePos == NULL)
	{
		return FALSE;
	}

	strModulePos = pModulePos->m_strValue;

	return TRUE;
}

BOOL  CSttAdjModule::GetModulePos(long &nModulePos)
{
	nModulePos = -1;
	CDvmData *pModulePos = GetModulePos();

	if (pModulePos == NULL)
	{
		return FALSE;
	}

	nModulePos = CString_To_long(pModulePos->m_strValue);
	return TRUE;
}


// mym add 2021-4-22 获取模块位置；
CDvmData* CSttAdjModule::GetModulePos(CDataGroup *pModule)
{
	CDataGroup *pAttrs = GetModuleAttrs(pModule);

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDvmData *pModuleType = (CDvmData*)pAttrs->FindByID(STT_ADJ_ID_ModulePos);

	return pModuleType;
}

// mym 2021-4-22 add
CDvmData*  CSttAdjModule::GetModulePos()
{
	return GetModulePos(m_pSttAdjRef);
}

// mym 2021-4-22 add
BOOL CSttAdjModule::GetModule_Pos_Index(CString &strModulePos, long &nModulePos, long &nModuleIndex )
{
	if (!GetModulePos(strModulePos))
	{
		return FALSE;
	}

	nModulePos =  CString_To_long(strModulePos);
	//return TRUE;

	CDataGroup *pDevice = (CDataGroup*)m_pSttAdjRef->GetParent();
	CExBaseList listModule;
	pDevice->FindByDataType(STT_ADJ_DATA_TYPE_Module,  listModule);

	POS pos = listModule.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CDvmData *pModulePos = NULL;
	//nModulePos = -1;

	int  nIndexModule = 0;
	while (pos != NULL)
	{
		pModule = (CDataGroup *)listModule.GetNext(pos);
		pModulePos = GetModulePos(pModule);

		if (pModulePos == NULL)
		{
			continue;
		}

		//if (pModulePos->m_strValue == strModulePos)
		//{
			//nModulePos++;
			//nIndexModule++;
		//}

		if (pModule == m_pSttAdjRef)
		{
			break;
		}
		nIndexModule++;
	}
	nModuleIndex = nIndexModule ;
	listModule.RemoveAll();

	return TRUE;
}

BOOL  CSttAdjModule::GetModuleType(CString &strModuleType)
{
	CDvmData *pModuleType = GetModuleType();

	if (pModuleType == NULL)
	{
		return FALSE;
	}

	strModuleType = pModuleType->m_strValue;

	return TRUE;
}

BOOL CSttAdjModule::GetModuleType(long &nModuleType)
{
	CString strModuleType;

	if (!GetModuleType(strModuleType))
	{
		return FALSE;
	}

	CDataType *pFind = (CDataType*)g_pSttAdjSysParaDataTypes->FindByID(STT_ADJ_ID_ModuleType);

	if (pFind == NULL)
	{
		return FALSE;
	}

	CDataTypeValue *pValue = (CDataTypeValue*)pFind->FindByID(strModuleType);

	if (pValue == NULL)
	{
		return FALSE;
	}

	nModuleType = CString_To_long(pValue->m_strIndex);
	return TRUE;
}

CDvmData*  CSttAdjModule::GetModuleAttrByID(CDataGroup *pModule, const CString &strAttrID)
{
	CDataGroup *pAttrs = GetModuleAttrs(pModule);

	if (pAttrs == NULL)
	{
		return NULL;
	}

	CDvmData *pAttr = (CDvmData*)pAttrs->FindByID(strAttrID);
	return pAttr;
}

CDvmData*  CSttAdjModule::GetModuleChannelNum()
{
	return GetModuleChannelNum(m_pSttAdjRef);
}

CDvmData* CSttAdjModule::GetModuleChannelNum(CDataGroup *pModule)
{
	return GetModuleAttrByID(pModule, STT_ADJ_ID_ChannelNum);
}

BOOL  CSttAdjModule::GetModuleChannelNum(CString &strChannelNum)
{
	CDvmData *pModuleChannelNum = GetModuleChannelNum();

	if (pModuleChannelNum == NULL)
	{
		return FALSE;
	}

	strChannelNum = pModuleChannelNum->m_strValue;
	return TRUE;
}

BOOL CSttAdjModule::GetModuleChannelNum(long &nChannelNum)
{
	CString strChannelNum;

	if (!GetModuleChannelNum(strChannelNum))
	{
		return FALSE;
	}

	nChannelNum = CString_To_long(strChannelNum);
	return TRUE;
}

BOOL CSttAdjModule::GetModuleChannelNum(long &nVolChNum,long &nCurChNum)
{
	CDataGroup* pAttrGroup = GetModuleAttrs();

	if (pAttrGroup == NULL)
	{
		return FALSE;
	}

	CDataGroup* pChMapDefGroup = (CDataGroup*)pAttrGroup->FindByID(STT_CMD_PARA_ChMapDef);

	if (pChMapDefGroup == NULL)
	{
		return FALSE;
	}

	CDataGroup* pChDefGroup = (CDataGroup*)pChMapDefGroup->FindByID(STT_ADJ_DATA_TYPE_ChDefine);

	if (pChDefGroup == NULL)
	{
		return FALSE;
	}

	POS pos = pChDefGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CDataGroup* pHdChGroup = NULL;
	CString strValue;
	nVolChNum = 0;
	nCurChNum = 0;

	while(pos)
	{
		pObj = pChDefGroup->GetNext(pos);

		if ((pObj->m_strID != STT_ADJ_DATA_TYPE_HdCh)||(pObj->GetClassID() != DTMCLASSID_CDATAGROUP))
		{
			continue;
		}

		pHdChGroup = (CDataGroup*)pObj;

		if (stt_GetDataValueByID(pHdChGroup,STT_ADJ_ID_EeType,strValue)&&(strValue == STT_ADJ_ID_EeType_Voltage))
		{
			nVolChNum++;
		}
		else
		{
			nCurChNum++;
		}
	}

	return TRUE;
}

void CSttAdjModule::AddMaxVolCurrValue_VolCurrModule()
{
	CDataGroup* pAttrGroup = GetModuleAttrs();

	if (pAttrGroup == NULL)
	{
		return;
	}

	CDataGroup* pChMapDefGroup = (CDataGroup*)pAttrGroup->FindByID(STT_CMD_PARA_ChMapDef);

	if (pChMapDefGroup == NULL)
	{
		return;
	}

	CDataGroup* pChDefGroup = (CDataGroup*)pChMapDefGroup->FindByID(STT_ADJ_DATA_TYPE_ChDefine);

	if (pChDefGroup == NULL)
	{
		return;
	}

	POS pos = pChDefGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CDataGroup* pHdChGroup = NULL;
	CString strValue;
	long nVolChNum = 0,nCurChNum = 0;
	double dVolMaxValue_AC = 0.0f,dVolMaxValue_DC = 0.0f,dCurMaxValue_AC = 0.0f,dCurMaxValue_DC = 0.0f;
	double dCurrValue_AC = 0.0f,dCurrValue_DC = 0.0f;

	while(pos)
	{
		pObj = pChDefGroup->GetNext(pos);

		if ((pObj->m_strID != STT_ADJ_DATA_TYPE_HdCh)||(pObj->GetClassID() != DTMCLASSID_CDATAGROUP))
		{
			continue;
		}

		dCurrValue_AC = 0.0f,dCurrValue_DC = 0.0f;
		pHdChGroup = (CDataGroup*)pObj;
		pHdChGroup->GetDataValue("ChACMaxValue",dCurrValue_AC);
		pHdChGroup->GetDataValue("ChDCMaxValue",dCurrValue_DC);

		if (stt_GetDataValueByID(pHdChGroup,STT_ADJ_ID_EeType,strValue)&&(strValue == STT_ADJ_ID_EeType_Voltage))
		{
			dVolMaxValue_AC = max(dVolMaxValue_AC,dCurrValue_AC);
			dVolMaxValue_DC = max(dVolMaxValue_DC,dCurrValue_DC);
			nVolChNum++;
		}
		else
		{
			dCurMaxValue_AC = max(dCurMaxValue_AC,dCurrValue_AC);
			dCurMaxValue_DC = max(dCurMaxValue_DC,dCurrValue_DC);
			nCurChNum++;
		}
	}

	//zhouhj 2023.11.13 使用时直接去通道里获取,不再使用此处方式
// 	if (nVolChNum>0)
// 	{
// 		pAttrGroup->SetDataValue(STT_ADJ_ID_VolChMaxValueAC,dVolMaxValue_AC,TRUE);
// 		pAttrGroup->InitNameByID(_T("电压通道出交流最大值"),STT_ADJ_ID_VolChMaxValueAC);
// 		pAttrGroup->SetDataValue(STT_ADJ_ID_VolChMaxValueDC,dVolMaxValue_DC,TRUE);
// 		pAttrGroup->InitNameByID(_T("电压通道出直流最大值"),STT_ADJ_ID_VolChMaxValueDC);
// 	}
// 
// 	if (nCurChNum>0)
// 	{
// 		pAttrGroup->SetDataValue(STT_ADJ_ID_CurChMaxValueAC,dCurMaxValue_AC,TRUE);
// 		pAttrGroup->InitNameByID(_T("电流通道出交流最大值"),STT_ADJ_ID_CurChMaxValueAC);
// 		pAttrGroup->SetDataValue(STT_ADJ_ID_CurChMaxValueDC,dCurMaxValue_DC,TRUE);
// 		pAttrGroup->InitNameByID(_T("电流通道出直流最大值"),STT_ADJ_ID_CurChMaxValueDC);
// 	}
}


long CSttAdjModule::GetModuleIndex()
{
	CString strModuleType;

	if (!GetModuleType(strModuleType))
	{
		return -1;
	}

	CDataGroup *pDevice = (CDataGroup*)m_pSttAdjRef->GetParent();
	CExBaseList listModule;
	pDevice->FindByDataType(strModuleType, listModule);

	long nIndex = listModule.FindIndex(m_pSttAdjRef);
	listModule.RemoveAll();

	return nIndex;
}


BOOL CSttAdjModule::GetModule_Type_Index(CString &strModuleType, long &nModuleIndex)
{
	if (!GetModuleType(strModuleType))
	{
		return FALSE;
	}

	CDataGroup *pDevice = (CDataGroup*)m_pSttAdjRef->GetParent();
	CExBaseList listModule;
	pDevice->FindByDataType(STT_ADJ_DATA_TYPE_Module, listModule);

	POS pos = listModule.GetHeadPosition();
	CDataGroup *pModule = NULL;
	CDvmData *pModuleType = NULL;
	nModuleIndex = -1;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)listModule.GetNext(pos);
		pModuleType = GetModuleType(pModule);

		if (pModuleType == NULL)
		{
			continue;
		}

		if (pModuleType->m_strValue == strModuleType)
		{
			nModuleIndex++;
		}

		if (pModule == m_pSttAdjRef)
		{
			break;
		}
	}

	listModule.RemoveAll();

	return TRUE;
}


CDvmData* CSttAdjModule::GetHarmCount(CDataGroup *pModule)
{
	return GetModuleAttrByID(pModule, STT_ADJ_ID_HarmCount);
}

long CSttAdjModule::GetHarmCount()
{
	CDvmData *pHarmCount = GetHarmCount(m_pSttAdjRef);

	if (pHarmCount == NULL)
	{
		return NULL;
	}

	return CString_To_long(pHarmCount->m_strValue);
}

void CSttAdjModule::InitChannelsID()
{
	long nModuleIndex = 0;
	GetModulePos(nModuleIndex);
	CString strModuleType;
	GetModuleType(strModuleType);
	CString strID_Desc = CSttMesLocalDb::GetModuleType_ChID_Desc(strModuleType);

	InitChannelsID(nModuleIndex, STT_ADJ_ID_EeType_Voltage, _T("U"), strID_Desc);
	InitChannelsID(nModuleIndex, STT_ADJ_ID_EeType_Current, _T("I"), strID_Desc);
	InitChannelsID(nModuleIndex, STT_ADJ_ID_EeType_Binary, _T("B"), strID_Desc);
}

void CSttAdjModule::InitChannelsID(long nModuleIndex, const CString &strEeType, const CString &strID_Type, const CString &strID_Desc)
{
	CDataGroup *pChDefine = GetHdChDefine();
	POS pos = pChDefine->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pCh = NULL;
	CDvmData *pEeType = NULL;
	CDvmData *pID = NULL;
	long nChIndex = 1;

	while (pos != NULL)
	{
		p = pChDefine->GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pCh = (CDataGroup *)p;
		pID = (CDvmData *)pCh->FindByID(_T("ID"));
		pEeType = (CDvmData *)pCh->FindByID(STT_ADJ_ID_EeType);

		if (pID == NULL || pEeType == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("InitChannelsID: ID or EeType Error...."));
			continue;
		}

		if (pEeType->m_strValue != strEeType)
		{
			continue;
		}

		pID->m_strValue.Format(_T("%s%s%d_%d"), strID_Type.GetString(), strID_Desc.GetString(), nModuleIndex, nChIndex);
		nChIndex++;
	}
}

// 2020-10-13 mym
CDataGroup* CSttAdjModule::GetAdjChWaveAdjustsGear(const CString &strT_Range, const CString &strChID, const CString &strWaveID/* , const CString &strGearID*/) 
{
	if (m_pSttAdjRef == NULL)
	{
		return NULL;
	}

	CDataGroup *pT_Range = GetAdjTRange(strT_Range);

	if (pT_Range == NULL)
	{
		return NULL;
	}

	if (strChID == STT_ADJ_ID_Ch_Idc)
	{
		CDataGroup * pTemp = (CDataGroup*)pT_Range->FindByID(STT_ADJ_ID_Ch_Idc);
		return  (CDataGroup*)pTemp->FindByDataType(STT_ADJ_HD_GEAR_DATA_TYPE);//FindByID(strGearID);//
	}

	if (strChID == STT_ADJ_ID_Ch_Udc)
	{
		CDataGroup * pTemp = (CDataGroup*)pT_Range->FindByID(STT_ADJ_ID_Ch_Udc);
		return  (CDataGroup*)pTemp->FindByDataType(STT_ADJ_HD_GEAR_DATA_TYPE);//FindByID(strGearID);//
	}

	CDataGroup *pChannel = (CDataGroup*)pT_Range->FindByID(strChID);

	if (pChannel == NULL)
	{
		return NULL;
	}

	CDataGroup *pGear = (CDataGroup*)pChannel->FindByID(strWaveID);

	if (pGear == NULL)
	{
		return NULL;
	}


	return (CDataGroup*)pGear->FindByDataType(STT_ADJ_HD_GEAR_DATA_TYPE);//FindByID(strGearID);//
}

void   CSttAdjModule::SetTrangID_ChannelID(CString strChannelID[] , CString strChWaveID[])
{
	for (int i = 0; i < m_nChannelCnt;i++)
	{
		m_strChannelID[i] = strChannelID[i];
	}
	for (int i = 0; i < m_nWaveCnt;i++)
	{
		m_strChWaveID[i] = strChWaveID[i];
	}
}


CDataGroup* CSttAdjModule::AddNewGear(CDataGroup *pSrcGear, CDataGroup *pParent, const CString &strGearID, const CString &strCountID)
{
	CDataGroup *pNew =  (CDataGroup*)pSrcGear->Clone();
	pParent->AddNewChild(pNew, TRUE);
	stt_IncreaseCountData(pParent, strCountID);

	return pNew;
}

//添加档位；2020-10-13 mym
CDataGroup* CSttAdjModule::AddNewGear(const CString &strT_Range, const CString &strChID, const CString &strWaveID,  const CString &strGearID )
{
	CDataGroup *pChWaveAdj   =  NULL;
	CDataGroup *pGearID  =  NULL;
	CDataGroup *pNew  =  NULL; 

	pChWaveAdj  =  GetAdjChWaveAdjusts(strT_Range,   strChID,  strWaveID);
	pGearID   =  GetAdjChWaveAdjustsGear(strT_Range,  strChID,  strWaveID);//, strGearID);

	if (pGearID  == NULL || pChWaveAdj==NULL)
		return NULL;
	pNew = AddNewGear(pGearID, pChWaveAdj , "", STT_ADJ_ID_GearCount);
	
	return pNew;
}

//2021-5-3  lijunqing
CDataGroup* CSttAdjModule::AddNewGear(CDataGroup *pSrcGear, CDataGroup *pParent)
{
	CDataGroup *pNew =  (CDataGroup*)pSrcGear->Clone();
	pParent->AddNewChild(pNew, TRUE);
	stt_IncreaseCountData(pParent, STT_ADJ_ID_GearCount);

	SetModifiedFlag(TRUE);

	return pNew;
}

//添加所有通道的， 2020-10-16 mym
CDataGroup* CSttAdjModule::AddNewGear_AllChnel(	 const CString &strTrangeID)
{
	//CString strGearID = "Gear0";
	int nWaveCnt = 32;
	int nChnelCnt =  8;

	CDataGroup *pGear   = NULL;

	for (int i = 0;  i  < nChnelCnt; i++)
		pGear = AddNewGear_SingleChnel( strTrangeID, m_strChannelID[i]);
	
	return pGear;
}

//添加单个通道的；2020-10-16 mym
CDataGroup* CSttAdjModule::AddNewGear_SingleChnel( const CString &strTrangeID , const CString &strChannelID )
{
	int nWaveCnt = 32;
	CString strGearID = "Gear0";

	CDataGroup *pGear   = NULL;
	CDataGroup *pGearTemp = NULL;

	if (strChannelID == STT_ADJ_ID_Ch_Idc  || strChannelID == STT_ADJ_ID_Ch_Udc)
		pGear   =  AddNewGear(strTrangeID,  strChannelID,  "",  strGearID);
	else 
	{
		for (int i = 0;  i  < nWaveCnt;  i++)
		{
			pGearTemp  = AddNewGear(strTrangeID, strChannelID,  m_strChWaveID[i],  strGearID);     

			if (i==0)//获取当前次谐波的指针, 用于插入下面的界面；这里只获取第一个的地址；
				pGear = pGearTemp;
		}
	}
	
	return pGear;
}

//////////////////////////////////////////////////////////////////////////
//2021-5-3  lijunqing
CDataGroup* CSttAdjModule::AddNewGear_AllChannel(CDataGroup *pTrange, CDataGroup *pAdjParas, const CString &strWaveID, CDataGroup *pSrcGear)
{
	if (pAdjParas->m_strDataType != STT_ADJ_DATA_TYPE_ChannelAdj)
	{
		return AddNewGear_SingleChannel(pAdjParas, strWaveID, pSrcGear);
	}
	
	CExBaseList listCh;
	pTrange->FindByDataType(STT_ADJ_DATA_TYPE_ChannelAdj, listCh);
	POS pos = listCh.GetHeadPosition();
	CDataGroup *pAdjCh = NULL;
	CDataGroup *pNew = NULL;

	while (pos != NULL)
	{
		pAdjCh = (CDataGroup *)listCh.GetNext(pos);
		pNew = AddNewGear_SingleChannel(pAdjCh, strWaveID, pSrcGear);
	}

	listCh.RemoveAll();
	return pNew;
}

CDataGroup* CSttAdjModule::AddNewGear_SingleChannel(CDataGroup *pAdjParas, const CString &strWaveID, CDataGroup *pSrcGear)
{
	CDataGroup *pGear = pSrcGear;

	if (pAdjParas->m_strDataType == STT_ADJ_DATA_TYPE_ChannelAdj)
	{
		CDataGroup *pWave = (CDataGroup*)pAdjParas->FindByID(strWaveID);

		if (pWave == NULL)
		{
			return NULL;
		}

		if (pGear == NULL)
		{
			pGear = pWave->FindByDataType(STT_ADJ_DATA_TYPE_GearAdjust);
		}

		return AddNewGear(pGear, pWave);
	}
	else
	{//ChWaveAdj
		if (pGear == NULL)
		{
			pGear = pAdjParas->FindByDataType(STT_ADJ_DATA_TYPE_GearAdjust);
		}

		return AddNewGear(pGear, pAdjParas);
	}
}

//删除所有通道的档位；2020-10-16 mym
CDataGroup* CSttAdjModule::DeleteGear_AllGear( const CString &strTrangeID, int &nCmbChannelIndex,  int &nCmbWaveIndex, const CString &strCurID, int &nIndex)
{
	CDataGroup* pDataGroup = NULL;
	CDataGroup *pGearTemp = NULL;
	for (int i = 0;  i  < m_nChannelCnt; i++)
	{
		if (m_strChannelID[i] == STT_ADJ_ID_Ch_Idc  ||  m_strChannelID[i] == STT_ADJ_ID_Ch_Udc)
		{
			pGearTemp = DeleteGear(strTrangeID,  m_strChannelID[i],  "", strCurID, nIndex);	
			if (i==nCmbChannelIndex)
				pDataGroup = pGearTemp;

// 			if (i==nCmbChannelIndex)//当是当前通道的时候，删除控件上的内容；
// 			{
// 				pDataGroup = DeleteGear(strTrangeID,  m_strChannelID[i],  "", strCurID,nIndex);
// 			}
// 			else 				
// 				DeleteGear(strTrangeID,  m_strChannelID[i],  "", strCurID, nIndex);	
		}
		else 
		{
			for(int j = 0; j  < m_nWaveCnt ; j++)
			{
				pGearTemp = DeleteGear(strTrangeID,  m_strChannelID[i],  m_strChWaveID[j],  strCurID, nIndex);
				if (i==nCmbChannelIndex && j==nCmbWaveIndex)
					pDataGroup = pGearTemp;
// 				if (i==nCmbChannelIndex && j==nCmbWaveIndex)//当是当前通道 当前谐波时候删除控件上的东东；
// 					pDataGroup = DeleteGear(strTrangeID,  m_strChannelID[i],  m_strChWaveID[j],  strCurID, nIndex);
// 				else 					
// 					DeleteGear(strTrangeID,  m_strChannelID[i],  m_strChWaveID[j],  strCurID,  nIndex);
 			}
		}
	}
	return pDataGroup;
}

//删除当前通道的档位；2020-10-16 mym
CDataGroup* CSttAdjModule::DeleteGear_SingleGear( const CString &strTrangeID, const CString &strChannelID, const CString &strCurID, int &nIndex)
{
	CDataGroup* pDataGroup = NULL;
	if (strChannelID== STT_ADJ_ID_Ch_Idc  || strChannelID == STT_ADJ_ID_Ch_Udc)
	{
		pDataGroup = DeleteGear(strTrangeID,  strChannelID,  "", strCurID, nIndex);
	}
	else
	{
		for(int i = 0; i  < m_nWaveCnt ; i++)
		{
			pDataGroup = DeleteGear(strTrangeID,  strChannelID,  m_strChWaveID[i], strCurID, nIndex);
		}
	}
	return pDataGroup ;
}

//删除档位；2020-10-16 mym
CDataGroup* CSttAdjModule::DeleteGear( const CString &strTrangeID,  const CString &strChannelID,  const CString &strChWaveID, const CString &strCurID, int &nIndex)
{
	CDataGroup *pChWaveAdjusts = NULL;
	CDataGroup *pGearTemp = NULL;
	CDataGroup *pGear = NULL;
	CDataGroup *pCurrSelGear = NULL;

	pChWaveAdjusts = GetAdjChWaveAdjusts(strTrangeID,  strChannelID,  strChWaveID);

	//这里获取GearCount个数，当剩下一个Gear的时候不再删除，直接返回；
	//CDvmData *pDvmData = (CDvmData *)pChWaveAdjusts->FindByID(_T("GearCount"));
	long nGearCount = 0;//atoi (pDvmData->m_strValue);
	stt_GetCountDataVal(pChWaveAdjusts , STT_ADJ_ID_GearCount, nGearCount);
	if (nGearCount==1)
		return NULL;
	//nGearCount--;
	//pDvmData->m_strValue.Format(_T("%d"),  nGearCount );

	stt_DecreaseCountData(pChWaveAdjusts,  STT_ADJ_ID_GearCount,  -1);

	POS pos = pChWaveAdjusts->GetHeadPosition();
	if (pos ==NULL)
		return NULL;
	int nFind = 0;
	while(pos)
	{
		pGearTemp = (CDataGroup *)pChWaveAdjusts->GetNext(pos);
		if (pGearTemp->m_strID==strCurID)
		{
			nFind = 1;
			break;
		}
	}

	if (pGearTemp==NULL || nFind==0)
		return NULL;

	CSttAdjBase oAdjObj;
	oAdjObj.AttatchAdjRef(pChWaveAdjusts);

	//long nIndex = 0;
	nIndex = oAdjObj.GetGroupIndex(pGearTemp);

	//if (nFlag==0)
	//{
		pCurrSelGear = oAdjObj.DeleteGroup(pGearTemp);
		//if (pCurrSelGear != NULL)		
		//nIndex  = 
		//oAdjObj.GetGroupIndex(pCurrSelGear);		
	//}
	//else 
	//	pCurrSelGear = oAdjObj.DeleteGroup(pGearTemp);
	return pCurrSelGear;
}


//2021-5-3 lijunqing
BOOL CSttAdjModule::DeleteGear(CDataGroup *pParent, const CString &strGearID)
{
	CExBaseObject *pFind =  pParent->FindByID(strGearID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pParent->GetChildCount(STT_ADJ_DATA_TYPE_GearAdjust) <= 1)
	{
		return FALSE;
	}

	pParent->Delete(pFind);
	stt_DecreaseCountData(pParent, STT_ADJ_ID_GearCount);

	SetModifiedFlag(TRUE);

	return TRUE;
}

BOOL CSttAdjModule::DeleteGear_AllChannel(CDataGroup *pTrange, CDataGroup *pAdjParas, const CString &strWaveID, const CString &strGearID)
{
	if (pAdjParas->m_strDataType != STT_ADJ_DATA_TYPE_ChannelAdj)
	{
		return DeleteGear_SingleChannel(pAdjParas, strWaveID, strGearID);
	}

	CExBaseList listCh;
	pTrange->FindByDataType(STT_ADJ_DATA_TYPE_ChannelAdj, listCh);
	POS pos = listCh.GetHeadPosition();
	CDataGroup *pAdjCh = NULL;

	while (pos != NULL)
	{
		pAdjCh = (CDataGroup *)listCh.GetNext(pos);
		DeleteGear_SingleChannel(pAdjCh, strWaveID, strGearID);
	}

	listCh.RemoveAll();

	return TRUE;
}

BOOL CSttAdjModule::DeleteGear_SingleChannel(CDataGroup *pAdjParas, const CString &strWaveID, const CString &strGearID)
{
	if (pAdjParas->m_strDataType == STT_ADJ_DATA_TYPE_ChannelAdj)
	{
		CDataGroup *pWave = (CDataGroup*)pAdjParas->FindByID(strWaveID);

		if (pWave == NULL)
		{
			return FALSE;
		}

		return DeleteGear(pWave, strGearID);
	}
	else
	{//ChWaveAdj
		return DeleteGear(pAdjParas, strGearID);
	}
}


//2021-5-4  lijunqing  将模块类型由整数转换为字符串，兼容老版本校准系数文件
void CSttAdjModule::TransModuleTypeFromLongToString()
{
	CDvmData *pModuleType = GetModuleType();

	if (pModuleType == NULL)
	{
		return;
	}

	CDataType *pFind = (CDataType*)g_pSttAdjSysParaDataTypes->FindByID(STT_ADJ_ID_ModuleType);

	if (pFind == NULL)
	{
		return;
	}

	CDataTypeValue *pValue = pFind->FindByIndex(pModuleType->m_strValue);

	if (pValue == NULL)
	{
		return;
	}

	pModuleType->m_strValue = pValue->m_strID;
}


void CSttAdjModule::SetModifiedFlagOwn(BOOL bModified)
{
	m_bModifiedFlag = bModified;
}

BOOL CSttAdjModule::GetModifiedFlagOwn()
{
	return m_bModifiedFlag;
}

void CSttAdjModule::SaveBaseObject()
{
	CSttMesLocalDb::SaveSttModuleClassFile(m_pSttAdjRef);

	SetModifiedFlagOwn(FALSE);
}

long stt_adj_HdChDef_GetNum(CDataGroup *pHdChDefine)
{
	CDvmData *pModuleChannelNum = (CDvmData*)pHdChDefine->FindByID(STT_ADJ_ID_ChannelNum);
	
	if (pModuleChannelNum == NULL)
	{
		return 0;
	}

	return CString_To_long(pModuleChannelNum->m_strValue);
}

/*
<group name="硬件通道1" id="HdCh0" data-type="HdCh" value="">
	<data name="通道ID" id="ID" data-type="string" value="U1_1" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="通道索引" id="Index" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="工作模式" id="WorkMode" data-type="WorkMode" value="Output" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="电气类型" id="EeType" data-type="EeType" value="Voltage" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="关联的软件资源" id="ChRsIndex" data-type="long" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="交流最大值" id="ChACMaxValue" data-type="float" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
	<data name="直流最大值" id="ChDCMaxValue" data-type="float" value="0" unit="" min="" max="" format="" index="0" time="0" change="0" step="" />
</group>
*/
CString stt_adj_HdChDef_GetEeType(CDataGroup *pHdChDefine)
{
	CString strValue;
	
	if (!pHdChDefine->GetDataValue(STT_ADJ_ID_EeType, strValue))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error HdChDef_GetEeType [%s]"), pHdChDefine->m_strID.GetString());
	}
	
	return strValue;
}

BOOL stt_adj_HdChDef_Is_Voltage(CDataGroup *pHdChDefine)
{
	return stt_adj_HdChDef_GetEeType(pHdChDefine) == STT_ADJ_ID_EeType_Voltage;
}

BOOL stt_adj_HdChDef_Is_Current(CDataGroup *pHdChDefine)
{
	return stt_adj_HdChDef_GetEeType(pHdChDefine) == STT_ADJ_ID_EeType_Current;
}

