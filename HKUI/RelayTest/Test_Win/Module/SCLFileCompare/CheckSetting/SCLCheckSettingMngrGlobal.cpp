//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SCLCheckSettingMngrGlobal.cpp

#include "stdafx.h"
#include "SCLCheckSettingMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CSCLCheckSettingMngrXmlRWKeys

CSCLCheckSettingMngrXmlRWKeys* CSCLCheckSettingMngrXmlRWKeys::g_pXmlKeys = NULL;
long CSCLCheckSettingMngrXmlRWKeys::g_nMngrRef = 0;


CSCLCheckSettingMngrXmlRWKeys::CSCLCheckSettingMngrXmlRWKeys()
{
	m_strallchecksKey = L"all-checks";
	m_strMannualcheckKey = L"check-object";
	m_strVirloopchecksKey = L"virloop-checks";
	m_strProjAppchecksKey = L"ProjAppModel-checks";
	m_strDLT860checksKey = L"DLT860Model-checks";
	m_strSchemacheckKey = L"schema-object";
	m_strSchemachecksKey = L"schema-checks";
	m_strSinglePathKey = L"single-path";
	m_strcheckPathsKey = L"check-paths";
	m_strPathKey = L"path";
	m_strChoseKey = L"chose";
	m_strVertionKey = L"vertion";
	m_strMethodKey = L"method";
	m_strTypeKey = L"type";

}

CSCLCheckSettingMngrXmlRWKeys::~CSCLCheckSettingMngrXmlRWKeys()
{
}

CSCLCheckSettingMngrXmlRWKeys* CSCLCheckSettingMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSCLCheckSettingMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSCLCheckSettingMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CSCLCheckSettingMngrConstGlobal

long CSCLCheckSettingMngrConstGlobal::g_nGlobalRef = 0;
CSCLCheckSettingMngrConstGlobal* CSCLCheckSettingMngrConstGlobal::g_pGlobal = NULL;


CSCLCheckSettingMngrConstGlobal::CSCLCheckSettingMngrConstGlobal()
{

	InitGlobal();

}

CSCLCheckSettingMngrConstGlobal::~CSCLCheckSettingMngrConstGlobal()
{
}

CSCLCheckSettingMngrConstGlobal* CSCLCheckSettingMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CSCLCheckSettingMngrConstGlobal();
	}

	return g_pGlobal;
}

void CSCLCheckSettingMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

void CSCLCheckSettingMngrConstGlobal::InitGlobal()
{
	Init_checkObjectSetDataType();
	Init_schemaCheckObjectSetDataType();
	Init_schemaCheckMethodType();
}

void CSCLCheckSettingMngrConstGlobal::Init_checkObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("checkObjectSetDataType"), _T("checkObjectSetDataTypeID"));
	pDataType->AddNewValue(_T("提示"), _T("tips"), _T("0"));
	pDataType->AddNewValue(_T("告警"), _T("warning"), _T("1"));
	pDataType->AddNewValue(_T("错误"), _T("error"), _T("2"));
	pDataType->AddNewValue(_T("严重错误"), _T("fatalerror"), _T("3"));
}

void CSCLCheckSettingMngrConstGlobal::Init_schemaCheckObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckVertionType"), _T("schemaCheckVertionTypeID"));
	pDataType->AddNewValue(_T("SCL1.4"), _T("SCL1.4"), _T("0"));
	pDataType->AddNewValue(_T("SCL2.0"), _T("SCL2.0"), _T("1"));
	pDataType->AddNewValue(_T("SCL3.0"), _T("SCL3.0"), _T("2"));
}

void CSCLCheckSettingMngrConstGlobal::Init_schemaCheckMethodType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckMethodType"), _T("schemaCheckMethodTypeID"));
	pDataType->AddNewValue(_T("DOM方式"), _T("DOM"), _T("0"));
	pDataType->AddNewValue(_T("SAX方式"), _T("SAX"), _T("1"));
}

CDataType* CSCLCheckSettingMngrConstGlobal::FindCheckSettingDataType(const  CString &strDataTypeID)
{
	ASSERT (g_pGlobal != NULL);
	CDataType *pDataType = NULL;

	pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(strDataTypeID);

	return pDataType;
}

