//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMesLocalDb.cpp  CSttMesLocalDb


#include "stdafx.h"
#include "SttMesLocalDb.h"
#include "SttAdjBase.h"
#include "SttAdjModule.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long CSttMesLocalDb::g_nSttMesLocalDb = 0;
CSttMesLocalDb* CSttMesLocalDb::g_pSttMesLocalDb = NULL;

CSttMesLocalDb* CSttMesLocalDb::Create()
{
	g_nSttMesLocalDb++;

	if (g_nSttMesLocalDb == 1)
	{
		g_pSttMesLocalDb = new CSttMesLocalDb();
		g_pSttMesLocalDb->InitSttMesLocalDB();
	}

	return g_pSttMesLocalDb;
}

CSttMesLocalDb* CSttMesLocalDb::GetMesLocalDb()
{
	return g_pSttMesLocalDb;
}

void CSttMesLocalDb::Release()
{
	g_nSttMesLocalDb--;

	if (g_nSttMesLocalDb == 0)
	{
		delete g_pSttMesLocalDb;
		g_pSttMesLocalDb = NULL;
	}
}

CSttMesLocalDb::CSttMesLocalDb()
{
	m_bModifiedFlag = FALSE;
	m_pSttMesLocalDB = new CDataGroup();
	m_pSttMesLocalDB->SetParent(this);
  
	InitHdGearType();
	InitChannelDataType();
	InitChWaveDataType();
	InitGearDataType();
	InitTRangeDataType();
// 	InitWorkModeDataType();
// 	InitEeTypeDataType();

	m_oDataTypes.AddNewChild(&m_oHdGearType);
	m_oDataTypes.AddNewChild(&m_oChannelDataType);
	m_oDataTypes.AddNewChild(&m_oChWaveDataType);
	m_oDataTypes.AddNewChild(&m_oGearDataType);
	m_oDataTypes.AddNewChild(&m_oChannelSwitchDataType);
	m_oDataTypes.AddNewChild(&m_oTRangeDataType);
// 	m_oDataTypes.AddNewChild(&m_oWorkModeDataType);
// 	m_oDataTypes.AddNewChild(&m_oEeTypeDataType);
// 	m_oDataTypes.AddNewChild(&m_oModuleTypeDataType);
}

CSttMesLocalDb::~CSttMesLocalDb()
{
	m_oDataTypes.RemoveAll();
	delete m_pSttMesLocalDB;
	m_pSttMesLocalDB = NULL;
}


void CSttMesLocalDb::SetModifiedFlagOwn(BOOL bModified)
{
	m_bModifiedFlag = bModified;
}

BOOL CSttMesLocalDb::GetModifiedFlagOwn()
{
	return m_bModifiedFlag;
}

void CSttMesLocalDb::SaveBaseObject()
{
	CString strFile = GetMesLocalDbFile();
	BOOL bRet = m_pSttMesLocalDB->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	SetModifiedFlagOwn(FALSE);
}

void CSttMesLocalDb::InitHdGearType()
{
	m_oHdGearType.m_strName = _T("HdGear");
	m_oHdGearType.m_strID = _T("HdGear");
	m_oHdGearType.AddNewValue("独立直流电流通道硬件档位", STT_ADJ_HD_GEAR_ID_IDC, "0");
	m_oHdGearType.AddNewValue("独立直流电压通道硬件档位", STT_ADJ_HD_GEAR_ID_UDC, "1");
	m_oHdGearType.AddNewValue("模块通道档位", STT_ADJ_HD_GEAR_ID_MODULE, "2");
}

void CSttMesLocalDb::InitChannelDataType()
{
	m_oChannelDataType.m_strName = _T("Channel");
	m_oChannelDataType.m_strID = _T("Channel");
	m_oChannelSwitchDataType.m_strName = _T("ChannelSwitch");
	m_oChannelSwitchDataType.m_strID = _T("ChannelSwitch");

	long nIndex = 0;
	CString strName, strID;

	//暂时确定为6个通道，最大化，多少后续再完善
	for (long nCh=0; nCh<12/*6*/; nCh++) //zhouhj 20220304 最大通道数,从6改为12  根据周磊实际需求修改
	{
		strName.Format(_T("通道%d"), nCh+1);
		strID.Format(_T("%s%d"), STT_ADJ_ID_Ch_Module, nCh);
		m_oChannelDataType.AddNewValue(strName, strID, nCh);
		m_oChannelSwitchDataType.AddNewValue(strName, strID, nCh);
	}

	m_oChannelDataType.AddNewValue("独立直流电流Idc", STT_ADJ_ID_Ch_Idc, "12");//最后一个参数值6改为12
	m_oChannelDataType.AddNewValue("独立直流电压Udc", STT_ADJ_ID_Ch_Udc, "13");//最后一个参数值7改为13
	m_oChannelSwitchDataType.AddNewValue("通道1-通道3", STT_ADJ_ID_Ch_1_3, "12");//最后一个参数值6改为12
	m_oChannelSwitchDataType.AddNewValue("通道4-通道6", STT_ADJ_ID_Ch_4_6, "13");//最后一个参数值7改为13
}

void CSttMesLocalDb::InitChWaveDataType()
{
	GetChWaveDataType(&m_oChWaveDataType, 51);
}

CDataType* CSttMesLocalDb::GetChWaveDataType(CDataType *pDataType, long nHarmCount)
{
	pDataType->DeleteAll();
	pDataType->m_strName = _T("Harm");
	pDataType->m_strID = _T("Harm");

	pDataType->AddNewValue("直流", STT_ADJ_ID_Ch_Wave_DC, "0");
	pDataType->AddNewValue("基波", STT_ADJ_ID_Ch_Wave_Base, "1");

	long nIndex = 0;
	CString strName, strID;

	//暂时确定为6个通道，最大化，多少后续再完善
	for (long nCh=2; nCh<=nHarmCount; nCh++)
	{
		strName.Format(_T("%d次谐波"), nCh);
		strID.Format(_T("%s%d"), STT_ADJ_ID_Ch_Wave_Harm, nCh);
		pDataType->AddNewValue(strName, strID, nCh);
	}

	return pDataType;
}

void CSttMesLocalDb::InitGearDataType()
{
	m_oGearDataType.m_strName = _T("Gear");
	m_oGearDataType.m_strID = _T("Gear");

	CString strName, strID;

	for (long nIndex=0; nIndex<=7; nIndex++)
	{
		strName.Format(_T("档位%d"), nIndex+1);
		strID.Format(_T("Gear%d"), nIndex);
		m_oGearDataType.AddNewValue(strName, strID, nIndex);
	}
}

void CSttMesLocalDb::InitTRangeDataType()
{
	m_oTRangeDataType.m_strName = _T("T_Range");
	m_oTRangeDataType.m_strID = _T("T_Range");

	CString strName, strID;

	for (long nIndex=0; nIndex<=7; nIndex++)
	{
		strName.Format(_T("温区%d"), nIndex+1);
		strID.Format(_T("T%d"), nIndex);
		m_oTRangeDataType.AddNewValue(strName, strID, nIndex);
	}
}

void CSttMesLocalDb::InitWorkModeDataType()
{
// 	m_oWorkModeDataType.m_strName = STT_ADJ_ID_WorkMode;
// 	m_oWorkModeDataType.m_strID = STT_ADJ_ID_WorkMode;
// 
// 	m_oWorkModeDataType.AddNewValue(_T("输出"), _T("Output"), "0");
// 	m_oWorkModeDataType.AddNewValue(_T("采集"), _T("MEAS"), "1");
}

void CSttMesLocalDb::InitEeTypeDataType()
{
// 	m_oEeTypeDataType.m_strName = _T("EeType");
// 	m_oEeTypeDataType.m_strID = _T("EeType");
// 
// 	m_oEeTypeDataType.AddNewValue(_T("电压"), _T("Voltage"), "0");
// 	m_oEeTypeDataType.AddNewValue(_T("电流"), _T("Current"), "1");
// 	m_oEeTypeDataType.AddNewValue(_T("开关量"), _T("Binary"), "2");
}

void CSttMesLocalDb::InitModuleTypeDataType()
{
// 	m_oModuleTypeDataType.DeleteAll();
// 	m_oModuleTypeDataType.m_strName = _T("ModuleType");
// 	m_oModuleTypeDataType.m_strID = _T("ModuleType");
// 
// 	CDataGroup *pModuleTypes = GetSttModuleTypes();
// 	POS pos = pModuleTypes->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pModuleTypes->GetNext(pos);
// 		m_oModuleTypeDataType.AddNewValue(pData->m_strName, pData->m_strID, pData->m_strValue);
// 	}
}

CString CSttMesLocalDb::GetMesLocalDbPath()
{
	CString strPath;
	strPath = _P_GetDBPath();
	strPath += _T("MesLocal\\");

	return strPath;
}

CString CSttMesLocalDb::GetMesLocalDbPath_Model()
{
	CString strPath = GetMesLocalDbPath();
	strPath += _T("Model\\");

	return strPath;
}

CString CSttMesLocalDb::GetMesLocalDbPath_ModuleType()
{
	CString strPath = GetMesLocalDbPath();
	strPath += _T("ModuleType\\");

	return strPath;
}

CString CSttMesLocalDb::GetMesLocalDbFile()
{
	CString strFile = GetMesLocalDbPath();
	strFile += _T("SttMesLocalDb.xml");

	return strFile;
}

CString CSttMesLocalDb::GetMesLocalDbPath_ModuleClassFile(const CString &strSttModuleClass)
{
	CString strFile;

	strFile = GetMesLocalDbPath_ModuleType();
    strFile.AppendFormat(_T("%s.xml"), strSttModuleClass.GetString());

	return strFile;
}

void CSttMesLocalDb::InitSttMesLocalDB()
{
	CString strFile = GetMesLocalDbFile();

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = m_pSttMesLocalDB->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	InitModuleTypeDataType();
}

void CSttMesLocalDb::SaveSttMesLocalDB()
{
	CString strFile = GetMesLocalDbFile();

	BOOL bRet = m_pSttMesLocalDB->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	InitModuleTypeDataType();
}
CDataGroup* CSttMesLocalDb::GetSttModuleTypes()
{
	CDataGroup *pFind = (CDataGroup*)g_pSttMesLocalDb->m_pSttMesLocalDB->FindByID(STT_MES_LOCAL_DB_SttModuleType);

	return pFind;
}

CDataGroup* CSttMesLocalDb::GetSttModuleClasses()
{
	CDataGroup *pFind = (CDataGroup*)g_pSttMesLocalDb->m_pSttMesLocalDB->FindByID(STT_MES_LOCAL_DB_SttModuleClass);

	return pFind;
}

CDataGroup* CSttMesLocalDb::GetSttModels()
{
	CDataGroup *pFind = (CDataGroup*)g_pSttMesLocalDb->m_pSttMesLocalDB->FindByID(STT_MES_LOCAL_DB_SttModel);

	return pFind;
}

#include "../SttTest/Common/tmt_adjust_sys_para_trans.h"
CDataType* CSttMesLocalDb::FindDataType(const CString &strID)
{
	if (strID.GetLength() == 0)
	{
		return NULL;
	}

	CDataType *pFind = NULL;
	ASSERT (g_pSttAdjSysParaDataTypes != NULL);

	if (g_pSttAdjSysParaDataTypes != NULL)
	{
		pFind = (CDataType *)g_pSttAdjSysParaDataTypes->FindByID(strID);

		if (pFind != NULL)
		{
			return pFind;
		}
	}

	return (CDataType*)g_pSttMesLocalDb->m_oDataTypes.FindByID(strID);
}


BOOL CSttMesLocalDb::OpenSttModuleClass(CDataGroup *pNew, const CString &strSttModuleClass)
{
	CString strFile;
	strFile = GetMesLocalDbPath_ModuleType();
    strFile.AppendFormat(_T("%s.xml"), strSttModuleClass.GetString());

	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = pNew->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	return bRet;
}

//2021-5-5  lijunqing  
CDataGroup* CSttMesLocalDb::CreateSttModuleClass(const CString &strSttModuleClass)
{
	CDataGroup *pFind = new CDataGroup();

	if (OpenSttModuleClass(pFind, strSttModuleClass))
	{
		return pFind;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("模块[%s]模板文件不存在"), strSttModuleClass.GetString());
		delete pFind;
		return NULL;
	}
}

CDataGroup* CSttMesLocalDb::OpenSttModuleClass(const CString &strSttModuleClass)
{
	CExBaseList *pList = &g_pSttMesLocalDb->m_listModuleClassOpened;
	CDataGroup *pFind = dvm_FindDataGroupByValue(*pList, strSttModuleClass);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CDataGroup();
	
	if (OpenSttModuleClass(pFind, strSttModuleClass))
	{
		pFind->m_strValue = strSttModuleClass;
		pList->AddTail(pFind);
		return pFind;
	}
	else
	{
		delete pFind;
		return NULL;
	}

	return pFind;
}

CDataGroup* CSttMesLocalDb::OpenSttModuleClass(CDataGroup *pModuleClass)
{
	CDvmData *pFind = (CDvmData *)pModuleClass->FindByID(STT_ADJ_ID_Model);

	if (pFind != NULL)
	{
		return OpenSttModuleClass(pFind->m_strValue);
	}

	CSttAdjModule oModule;
	oModule.AttatchAdjRef(pModuleClass);
	CString strModuleClass;

	if (!oModule.GetModel(strModuleClass))
	{
		return NULL;
	}

	return OpenSttModuleClass(strModuleClass);
}

BOOL CSttMesLocalDb::SaveSttModuleClassFile(CDataGroup *pModuleClass)
{
	CSttAdjModule oModule;
	oModule.AttatchAdjRef(pModuleClass);
	CString strModuleClass;
	
	if (!oModule.GetModel(strModuleClass))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模块数据错误，没有定义型号"));
		return FALSE;
	}

	if (strModuleClass.GetLength() == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模块数据错误，型号为空"));
		return FALSE;
	}

	CString strFile = GetMesLocalDbPath_ModuleClassFile(strModuleClass);
	CString strName = pModuleClass->m_strName;
	CString strID = pModuleClass->m_strID;
	pModuleClass->m_strName = strModuleClass;
	pModuleClass->m_strID = strModuleClass;

	BOOL bRet = pModuleClass->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	//2022-2-8  lijunqing 添加到ModuleClass中
	CDvmData *pModel = oModule.GetModel();
	CDataGroup *pClasses = GetSttModuleClasses();
	CDataGroup *pFind = (CDataGroup*)pClasses->FindByID(strModuleClass);

	if (pFind != NULL)
	{
		pFind->InitDataValues(pModuleClass, FALSE);
	}
	else
	{
		pFind = AddNewModuleClass2(pModuleClass);
		pFind->m_strID = strModuleClass;
		pFind->m_strName = strModuleClass;
		g_pSttMesLocalDb->SaveSttMesLocalDB();
	}
	
	pModuleClass->m_strName = strName;
	pModuleClass->m_strID = strID;

	if (bRet)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出【%s】模块系数模板文件成功"), strFile.GetString());
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("导出【%s】模块系数模板文件失败"), strFile.GetString());
	}

	return bRet;
}

//2020-10-13 lijunqing
CDvmData* CSttMesLocalDb::FindModuleTypeData(const CString &strModuleType)
{
	CDataGroup *pModuleTypeDb = GetSttModuleTypes();

	if (pModuleTypeDb == NULL)
	{
		return NULL;
	}

	CDvmData *pData = pModuleTypeDb->FindDataByValue(strModuleType);

	if (pData == NULL)
	{
		pData = (CDvmData*)pModuleTypeDb->FindByID(strModuleType);
	}

	return pData;
}

CDvmData* CSttMesLocalDb::FindModuleTypeData(long nModuleType)
{
	CString strValue;
	strValue.Format(_T("%d"), nModuleType);
	CDataGroup *pModuleTypeDb = GetSttModuleTypes();

	if (pModuleTypeDb == NULL)
	{
		return  NULL;
	}

	POS pos = pModuleTypeDb->GetHeadPosition();
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pModuleTypeDb->GetNext(pos);

		if (p->m_strValue == strValue)
		{
			return p;
		}
	}

	return NULL;
}

CString CSttMesLocalDb::GetModuleType_ChID_Desc(const CString &strModuleType)
{
	CDvmData *pFind = FindModuleTypeData(strModuleType);

	if (pFind == NULL)
	{
		return _T("");
	}
	else
	{
		return pFind->m_strFormat;
	}
}

//////////////////////////////////////////////////////////////////////////
//mym
CDvmData* CSttMesLocalDb::AddNewModuleType()
{
	CDataGroup *pModuleType = GetSttModuleTypes();

	CDvmData *pData = AddNewModuleType(pModuleType);

	return pData;
}

CDvmData* CSttMesLocalDb::AddNewModuleType(int nFalg)
{
	CDataGroup *pModuleType = GetSttModuleTypes();
	CDvmData *pData  = AddNewModuleType(pModuleType);
	return pData;
}

CDvmData* CSttMesLocalDb::AddNewModuleType(CDataGroup *pModuleType)
{
	long nDataCnt  = pModuleType->GetChildCount(DVMCLASSID_CDVMDATA);
	CString strName,  strID,  strDataType = _T(""),  strValue;
	strName = "新模块类型" ; 
	strID = "VOLTAGE";  //2021-5-4  lijunqing  新模块类型，缺省为电压模块
	strValue.Format(_T("%d"),  nDataCnt );

	CDvmData *pNew = pModuleType->AddNewData(strName,  strID,  strDataType, strValue);

	return pNew;
}

CDataGroup* CSttMesLocalDb::AddNewModuleClass()
{
	CDataGroup *pModuleClass = GetSttModuleClasses();
	CDataGroup *pNewGroup = AddNewModuleClass(pModuleClass);

	return pNewGroup;
}

//添加对应的ModuleClass
CDataGroup* CSttMesLocalDb::AddNewModuleClass(CDataGroup *pModuleClass)
{
	CDataGroup *pClass = pModuleClass->AddNewGroup(_T("模块"),  _T("Moule"),  _T("Moule"));

	//2021-5-4  lijunqing  "Type" >> "ModuleType"
	pClass->AddNewData(_T("模块类型"), _T("ModuleType"), _T("ModuleType"), _T("0"));
	pClass->AddNewData(_T("模块硬件位置"), _T("Pos"), _T("long"), _T("2500"));
	pClass->AddNewData(_T("频率"), _T("Freq"), _T("float"), _T("2500"));
	pClass->AddNewData(_T("通道数"), _T("ChannelCount"), _T("long"), _T("4"));
	pClass->AddNewData(_T("型号"), _T("Model"), _T("string"), _T("PUT-4U"));
	pClass->AddNewData(_T("直流电流通道最大值"), _T("UdcMax"), _T("float"), _T("20"));	
	pClass->AddNewData(_T("直流电压通道最大值"), _T("IdcMax"), _T("float"), _T("20"));	
	pClass->AddNewData(_T("通道最大值"), _T("ChMax"), _T("float"), _T("20"));

	return pClass;
}

//2022-2-8  lijunqing
CDataGroup* CSttMesLocalDb::AddNewModuleClass2(CDataGroup *pSrcModuleClass)
{
	CDataGroup *pModuleClasses = GetSttModuleClasses();
	CDataGroup *pNewGroup = AddNewModuleClass(pModuleClasses);
	pNewGroup->InitDataValues(pSrcModuleClass, FALSE);

	return pNewGroup;
}

//向给定的GROUP中添加Data
CDvmData* CSttMesLocalDb::AddNewModuleClassData(CDataGroup* pDataGroup)
{
	long nDataCnt = pDataGroup->GetChildCount(DVMCLASSID_CDVMDATA);
	CString strName,  strID,  strDataType = _T(""),  strValue;
	strName.Format(_T("Ch%dPos"),  nDataCnt + 1);
	strID.Format(_T("Ch%dPos"),  nDataCnt + 1);
	strValue.Format(_T("%d"),  nDataCnt);

	CDvmData *pNew = pDataGroup->AddNewData(strName,  strID,  strDataType, strValue);

	return pNew;
}

CDataGroup* CSttMesLocalDb::AddNewMode()
{
	CDataGroup *pMode = GetSttModels();
	CDataGroup *pNewMode = AddNewMode(pMode);

	return pNewMode;
}

CDataGroup* CSttMesLocalDb::AddNewMode(CDataGroup *pMode)
{
	CDataGroup *pNewMode = pMode->AddNewGroup(_T("PTU200L"),  _T("PTU200L"),  _T("SttModel"));
	pNewMode->AddNewData(_T("型号"),  _T("Model"),  _T("string"),  _T("PTU200L"));
	pNewMode->AddNewData(_T("模块数"),  _T("ModuleCount"),  _T("long"),  _T("3"));

	return pNewMode;
}

long  CSttMesLocalDb::DeleteModuleTypeByIndex(int nDataIndex)
{
	long nIndexRet = 0;
	CDataGroup *pDataGroup = GetSttModuleTypes();

	POS pos = pDataGroup->FindIndex(nDataIndex);
	nIndexRet = nDataIndex ;
	if (pos != NULL)
	{
		pDataGroup->DeleteAt(pos);
	}

	if (nDataIndex > 1)
		nIndexRet--;
	else 
		nIndexRet = 1;

	return nIndexRet;
}

// long  CSttMesLocalDb::DeleteModuleClass_data_ByIndex(CDataGroup *pDataGroup,  int nDataIndex)
// {
// 	long nIndexRet  = 0;
// 
// 	POS pos = pDataGroup->FindIndex(nDataIndex);
// 	nIndexRet = nDataIndex ;
// 	if (pos != NULL)
// 	{
// 		pDataGroup->DeleteAt(pos);
// 	}
// 
// 	if (nDataIndex > 1)
// 		nIndexRet--;
// 	else 
// 		nIndexRet = 1;
// 
// 	return nIndexRet;
// }

CDataGroup *   CSttMesLocalDb::DeleteModuleClass(CDataGroup *pDataGroup)
{
	long nIndexRet  = 0;
	CDataGroup *pNext = NULL;
	CExBaseList listGroup;
	long nIndex = -1;

	CDataGroup * pModuleClass =  GetSttModuleClasses();

	pModuleClass->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndex = listGroup.FindIndex(pDataGroup);
	pModuleClass->Delete(pDataGroup);
	listGroup.Remove(pDataGroup);

	if (listGroup.GetCount() > 0)
	{
		pNext = (CDataGroup*)listGroup.GetAtIndex(nIndex);

		if (pNext == NULL)
		{
			pNext =  (CDataGroup*)listGroup.GetAtIndex(nIndex-1);
		}
	}

	listGroup.RemoveAll();

	return pNext;



	/*
	POS pos = pDataGroup->FindIndex(nDataIndex);
	nIndexRet = nDataIndex ;
	if (pos != NULL)
	{
		pDataGroup->DeleteAt(pos);
	}

	if (nDataIndex > 1)
		nIndexRet--;
	else 
		nIndexRet = 1;
	*/

	//return nIndexRet;
}

long  CSttMesLocalDb:: GetModuleClassesIndex(CDataGroup *pDataGroup)
{
	long nIndexRet = 0;

	CExBaseList listGroup;
	long nIndex = -1;
	CDataGroup * pModuleClass =  GetSttModuleClasses();
	pModuleClass->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndexRet = listGroup.FindIndex(pDataGroup);
	listGroup.RemoveAll();

	return nIndexRet;
}

long  CSttMesLocalDb::GetModeIndex(CDataGroup * pDataGroup)
{
	long nIndexRet = 0;

	CExBaseList listGroup;
	long nIndex = -1;
	CDataGroup * pMode =  GetSttModels();
	pMode->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndexRet = listGroup.FindIndex(pDataGroup);
	listGroup.RemoveAll();

	return nIndexRet;
}

CDataGroup * CSttMesLocalDb::DeleteMode(CDataGroup * pDataGroup)
{
	CDataGroup *pNext = NULL;
	CExBaseList listGroup;
	long nIndex = -1;

	CDataGroup * pMode =  GetSttModels();
	pMode->FindByDataType(pDataGroup->m_strDataType, listGroup);
	nIndex = listGroup.FindIndex(pDataGroup);
	pMode->Delete(pDataGroup);
	listGroup.Remove(pDataGroup);

	if (listGroup.GetCount() > 0)
	{
		pNext = (CDataGroup*)listGroup.GetAtIndex(nIndex);

		if (pNext == NULL)
		{
			pNext =  (CDataGroup*)listGroup.GetAtIndex(nIndex-1);
		}
	}

	listGroup.RemoveAll();

	return pNext;
}
