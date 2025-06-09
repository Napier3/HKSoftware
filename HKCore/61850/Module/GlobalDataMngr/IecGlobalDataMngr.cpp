//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGlobalDataMngr.cpp  CIecGlobalDataMngr


#include "stdafx.h"
#include "IecGlobalDataMngr.h"
#include "../../../Module/API/GlobalConfigApi.h"


//////////////////////////////////////////////////////////////////////////
//CIecGlobalDataMngr

long CIecGlobalDataMngr::g_nGlobalRef = 0;
CIecGlobalDataMngr* CIecGlobalDataMngr::g_pGlobal = NULL;


CIecGlobalDataMngr::CIecGlobalDataMngr()
{
	//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()
	InitSTPortsConfig();
	InitFt3PortsConfig();
	InitSclFilterText();
	InitStCfgFileFilterText();
	InitGooseDataTypeMngr();
	InitSmvDataType();
	InitAnalogDataType();
	InitAnalogChType();
	InitQulityDataTypes();
	InitCfgChTypeDataType();
	InitBOutChDataType();
	Init6044SpeedDataType();
	InitCommonDataTypeMngr();
}

CIecGlobalDataMngr::~CIecGlobalDataMngr()
{
}

CIecGlobalDataMngr* CIecGlobalDataMngr::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CIecGlobalDataMngr();
	}

	return g_pGlobal;
}

void CIecGlobalDataMngr::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

void CIecGlobalDataMngr::InitSTPortsConfig()
{
	m_pSTPortsConfig = new CIecFiberConfig();
	AddTail(m_pSTPortsConfig);
	m_pSTPortsConfig->InitFiberConfig(4);
}

void CIecGlobalDataMngr::InitFt3PortsConfig()
{
	m_pFt3PortsConfig = new CIecFiberConfig();
	AddTail(m_pFt3PortsConfig);
	m_pFt3PortsConfig->InitFt3Config(3);
}

void CIecGlobalDataMngr::InitSclFilterText()
{
	m_pSclFilterText = new CFilterTextMngr();
	AddTail(m_pSclFilterText);
	CString strPath = GetConfigFilePath(_T("SclFilterText.xml"));
	m_pSclFilterText->OpenXmlFile(strPath);
}

CString CIecGlobalDataMngr::GetConfigFilePath(const CString &strFileName)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += strFileName;
	return strPath;
}

void CIecGlobalDataMngr::InitStCfgFileFilterText()
{
	m_pStCfgFileFilterText = new CFilterTextMngr();
	AddTail(m_pStCfgFileFilterText);
	CString strPath = GetConfigFilePath(_T("CfgFileFilterText.xml"));
	m_pStCfgFileFilterText->OpenXmlFile(strPath);
}

void CIecGlobalDataMngr::InitGooseDataTypeMngr()
{
	m_pGooseDataTypeMngr = new CIecGooseChDataTypeMngr();
	AddTail(m_pGooseDataTypeMngr);
	CString strPath = GetConfigFilePath(_T("GooseChDataTypeMngr.xml"));
	m_pGooseDataTypeMngr->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CIecGooseChDataTypeMngrKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitSmvDataType()
{
	m_pSmvChDataType = new CIecSmvChDataType();
	AddNewChild(m_pSmvChDataType);

	CString strPath = GetConfigFilePath(_T("SmvChDataType.xml"));
	m_pSmvChDataType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CIecSmvChDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitAnalogDataType()
{
	m_pAnalogChDataType = new CDataType();
	AddNewChild(m_pAnalogChDataType);

	CString strPath = GetConfigFilePath(_T("AnalogChDataType.xml"));
	m_pAnalogChDataType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitAnalogChType()
{
	m_pAnalogChType = new CDataType();
	AddNewChild(m_pAnalogChType);

	CString strPath = GetConfigFilePath(_T("AnalogChType.xml"));
	m_pAnalogChType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitQulityDataTypes()
{
	m_pCfgQulityDataTypes = new CDataTypes();
	AddNewChild(m_pCfgQulityDataTypes);

	CString strPath = GetConfigFilePath(_T("CfgQulityDataTypes.xml"));
	m_pCfgQulityDataTypes->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeMngrKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitCfgChTypeDataType()
{
	m_pCfgChTypeDataType = new CDataType();
	AddNewChild(m_pCfgChTypeDataType);

	CString strPath = GetConfigFilePath(_T("CfgChTypeDataType.xml"));
	m_pCfgChTypeDataType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);

}


void CIecGlobalDataMngr::InitBOutChDataType()
{
	m_pBOutChDataType = new CDataType();
	AddNewChild(m_pBOutChDataType);

	CString strPath = GetConfigFilePath(_T("BOutChDataType.xml"));
	m_pBOutChDataType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);

}

void CIecGlobalDataMngr::Init6044SpeedDataType()
{
	m_p6044SpeedDataType = new CDataType();
	AddNewChild(m_p6044SpeedDataType);

	CString strPath = GetConfigFilePath(_T("Cfg6044Speed.xml"));
	m_p6044SpeedDataType->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecGlobalDataMngr::InitCommonDataTypeMngr()
{
	m_pCommonDataTypes = new CDataTypes();
	AddNewChild(m_pCommonDataTypes);

	CString strPath = GetConfigFilePath(_T("CommonDataTypes.xml"));
	m_pCommonDataTypes->OpenXmlFile(strPath, CIecGlobalDataMngrXmlRWKeys::CDataTypeMngrKey(), CIecGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

CString GetSmvChPhase(const CString &strName,const CString &strID)
{
	CString strPhase;

	if (strName.Find(_T("A相")) >= 0)
	{
		strPhase = _T("A相");
	}
	else if (strName.Find(_T("B相")) >= 0)
	{
		strPhase = _T("B相");
	}
	else if (strName.Find(_T("C相")) >= 0)
	{
		strPhase = _T("C相");
	}
	else if ((strName.Find(_T("抽取")) >= 0)||(strName.Find(_T("间隔")) >= 0))
	{
		strPhase = _T("N相");
	}

	return strPhase;
}

BOOL GetSmvChTypeAndPhase(const CString &strName,const CString &strID,CString &strChType,CString &strPhase)
{
	if (iecfg_IsTimeCh(strName) || iecfg_IsTimeCh(strID))
	{
		strChType = _T("时间")/*iecfg_SmvChDataType_Val_UTCTime*/;
		strPhase = _T("--");
		return TRUE;
	}

	CString strNewID;
	strNewID = strID;

	if ((strNewID.Find(_T("TVTR")) >= 0)||(strName.Find(_T("电压")) >= 0))
	{
		strChType = _T("电压")/*iecfg_SmvChDataType_Val_Vol*/;
		strPhase = GetSmvChPhase(strName,strID);
		return TRUE;
	}

	if ((strNewID.Find(_T("TCTR")) >= 0)||(strName.Find(_T("电流")) >= 0))
	{
		strChType = _T("电流")/*iecfg_SmvChDataType_Val_Curr*/;
		strPhase = GetSmvChPhase(strName,strID);
		return TRUE;
	}

	strChType = _T("--");
	strPhase = _T("--");
	return FALSE;
}

//定义全局常量，例如  static CString g_pstrVariableType_CString;
