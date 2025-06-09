//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSchemaCheckSettingObjectGlobal.cpp

#include "stdafx.h"
#include "CSchemaCheckSettingObjectGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CCSchemaCheckSettingObjectXmlRWKeys

CCSchemaCheckSettingObjectXmlRWKeys* CCSchemaCheckSettingObjectXmlRWKeys::g_pXmlKeys = NULL;
long CCSchemaCheckSettingObjectXmlRWKeys::g_nMngrRef = 0;


CCSchemaCheckSettingObjectXmlRWKeys::CCSchemaCheckSettingObjectXmlRWKeys()
{
	m_strCMannualCheckSettingKey = L"mannualSetting";
	m_strCMannualCheckSettingsKey = L"mannualSettings";
	m_strCSchemaCheckSettingKey = L"SchemaSetting";
	m_strCSchemaCheckSettingsKey = L"SchemaSettings";
	m_strBeSelectedKey = L"beSelected";
	m_strDescriptionKey = L"description";
	m_strVersionTypeKey = L"versionType";
	m_strXmlMethodKey = L"xmlMethod";
	m_strTokenTypeKey = L"tokenType";
}

CCSchemaCheckSettingObjectXmlRWKeys::~CCSchemaCheckSettingObjectXmlRWKeys()
{
}

CCSchemaCheckSettingObjectXmlRWKeys* CCSchemaCheckSettingObjectXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CCSchemaCheckSettingObjectXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCSchemaCheckSettingObjectXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCSchemaCheckSettingObjectConstGlobal

long CCSchemaCheckSettingObjectConstGlobal::g_nGlobalRef = 0;
CCSchemaCheckSettingObjectConstGlobal* CCSchemaCheckSettingObjectConstGlobal::g_pGlobal = NULL;


CCSchemaCheckSettingObjectConstGlobal::CCSchemaCheckSettingObjectConstGlobal()
{
	InitGlobal();

}

CCSchemaCheckSettingObjectConstGlobal::~CCSchemaCheckSettingObjectConstGlobal()
{
}

CCSchemaCheckSettingObjectConstGlobal* CCSchemaCheckSettingObjectConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCSchemaCheckSettingObjectConstGlobal();
	}

	return g_pGlobal;
}

void CCSchemaCheckSettingObjectConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

void CCSchemaCheckSettingObjectConstGlobal::InitGlobal()
{
	Init_checkObjectSetDataType();
	Init_schemaCheckObjectSetDataType();
	Init_schemaCheckMethodType();
}

void CCSchemaCheckSettingObjectConstGlobal::Init_checkObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("checkObjectSetDataType"), _T("checkObjectSetDataTypeID"));
	pDataType->AddNewValue(_T("提示"), _T("tips"), _T("0"));
	pDataType->AddNewValue(_T("告警"), _T("warning"), _T("1"));
	pDataType->AddNewValue(_T("错误"), _T("error"), _T("2"));
	pDataType->AddNewValue(_T("严重错误"), _T("fatalerror"), _T("3"));
}

void CCSchemaCheckSettingObjectConstGlobal::Init_schemaCheckObjectSetDataType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckVertionType"), _T("schemaCheckVertionTypeID"));
	pDataType->AddNewValue(_T("SCL1.4"), _T("SCL1.4"), _T("0"));
	pDataType->AddNewValue(_T("SCL2.0"), _T("SCL2.0"), _T("1"));
	pDataType->AddNewValue(_T("SCL3.0"), _T("SCL3.0"), _T("2"));
}

void CCSchemaCheckSettingObjectConstGlobal::Init_schemaCheckMethodType()
{
	CDataType *pDataType = m_oIecRtdDataTypes.AddNew2(_T("schemaCheckMethodType"), _T("schemaCheckMethodTypeID"));
	pDataType->AddNewValue(_T("DOM方式"), _T("DOM"), _T("0"));
	pDataType->AddNewValue(_T("SAX方式"), _T("SAX"), _T("1"));
}

CDataType* CCSchemaCheckSettingObjectConstGlobal::FindCheckSettingDataType(const  CString &strDataTypeID)
{
	ASSERT (g_pGlobal != NULL);
	CDataType *pDataType = NULL;

	pDataType = (CDataType*)g_pGlobal->m_oIecRtdDataTypes.FindByID(strDataTypeID);

	return pDataType;
}

