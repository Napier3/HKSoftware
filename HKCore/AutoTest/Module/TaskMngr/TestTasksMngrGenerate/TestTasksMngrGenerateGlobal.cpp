//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksMngrGenerateGlobal.cpp

#include "stdafx.h"
#include "TestTasksMngrGenerateGlobal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrGenerateXmlRWKeys

CTestTasksMngrGenerateXmlRWKeys* CTestTasksMngrGenerateXmlRWKeys::g_pXmlKeys = NULL;
long CTestTasksMngrGenerateXmlRWKeys::g_nTTMGRef = 0;


CTestTasksMngrGenerateXmlRWKeys::CTestTasksMngrGenerateXmlRWKeys()
{
	m_strCTtmgBatchReportKey = L"report";
	m_strCTtmgBatchsKey = L"batchs";
	m_strCTtmgReportsMngrKey = L"rtps-mngr";
	m_strCTtmgReportsKey = L"rpts";
	m_strCTtmgReportKey = L"rpt";
	m_strCTestTasksMngrGenerateKey = L"rpt-generator";
	m_strCTtmgBatchKey = L"batch";
	m_strCTtmgFactorysKey = L"factorys";
	m_strCTtmgFactoryKey = L"factory";
	m_strCTtmgStationsKey = L"stations";
	m_strCTtmgStationKey = L"station";
	m_strCodeKey = L"code";
	m_strOwnDefKey = L"own-def";
	m_strHdVerKey = L"hd-ver";
	m_strStationKey = L"station";
	m_strFactoryKey = L"factory";
	m_strNumKey = L"num";
	m_strWordBeginNOKey = L"word-no-begin";
	m_strProduceNOKey = L"produce-no";
	m_strErrorsKey = L"errors";
	m_strProduceDateKey = L"produce-date";
	m_strFlowNOKey = L"flow-no";
	m_strFolderKey = L"folder";
	m_strCurrGenIndexKey = L"curr-gen-index";
	m_strHasWriteExcelKey = L"has-write-excel";
	m_strHandTestNumKey = L"hand-test";
	m_strTestBeginTimeKey = L"test-begin-time";
	m_strGbxml1Key = L"gbxml1";
	m_strGbxml2Key = L"gbxml2";
	m_strGbxml3Key = L"gbxml3";
	m_strPathKey = L"path";
	m_strDeviceAttrKey = L"device-attr";
	m_strSrcRptKey = L"src-rpt";
	m_strDestRptKey = L"dest-rpt";
	m_strErrorTypeKey = L"err-type";
	m_strHasGeneratedKey = L"has-gen";
}

CTestTasksMngrGenerateXmlRWKeys::~CTestTasksMngrGenerateXmlRWKeys()
{
}

CTestTasksMngrGenerateXmlRWKeys* CTestTasksMngrGenerateXmlRWKeys::Create()
{
	g_nTTMGRef++;

	if (g_nTTMGRef == 1)
	{
		g_pXmlKeys = new CTestTasksMngrGenerateXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CTestTasksMngrGenerateXmlRWKeys::Release()
{
	g_nTTMGRef--;

	if (g_nTTMGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrGenerateConstGlobal

long CTestTasksMngrGenerateConstGlobal::g_nGlobalRef = 0;
CTestTasksMngrGenerateConstGlobal* CTestTasksMngrGenerateConstGlobal::g_pGlobal = NULL;


CTestTasksMngrGenerateConstGlobal::CTestTasksMngrGenerateConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CTestTasksMngrGenerateConstGlobal::~CTestTasksMngrGenerateConstGlobal()
{
}

CTestTasksMngrGenerateConstGlobal* CTestTasksMngrGenerateConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CTestTasksMngrGenerateConstGlobal();
	}

	return g_pGlobal;
}

void CTestTasksMngrGenerateConstGlobal::Release()
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

//定义全局常量，例如  static CString g_pstrVariableType_CString;

CString TTMG_GetConfigRootPath()
{
	CString strRootPath;

	strRootPath = _P_GetLibraryPath();
	strRootPath += _T("Nari\\");

	return strRootPath;
}


CString TTMG_GetRptGenRootPath()
{
	CString strRootPath;

	strRootPath = _P_GetWorkspacePath();
	strRootPath += _T("Nari\\");

	return strRootPath;
}

