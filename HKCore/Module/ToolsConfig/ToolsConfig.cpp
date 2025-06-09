//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ToolsConfig.cpp  CToolsConfig


#include "stdafx.h"
#include "ToolsConfig.h"

CToolsConfig::CToolsConfig()
{
	CToolsConfigXmlRWKeys::Create();
	//初始化属性

	//初始化成员变量
	m_nUserServer = 1;
	m_nUse_TASKTEST = 1;
	m_nUse_SDVMPP = 1;
	m_nUseMDVMGRP = 1;
	m_nUse_ReportPane = 1;
	m_nUseAppSelConfig = 1;
}

CToolsConfig::~CToolsConfig()
{
	CToolsConfigXmlRWKeys::Release();
}

BOOL CToolsConfig::IsOnlySdvSppTest()
{
	if (m_nUse_SDVMPP != 0 
		|| m_nUse_SDVMPP != 0
		|| m_nUseMDVMGRP != 0)
	{
		return FALSE;
	}

	return TRUE;
}

long CToolsConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CToolsConfigXmlRWKeys *pXmlKeys = (CToolsConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUserServerKey, oNode, m_nUserServer);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_TASKTESTKey, oNode, m_nUse_TASKTEST);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_SDVMPPKey, oNode, m_nUse_SDVMPP);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_MDVMGRPKey, oNode, m_nUseMDVMGRP);
	xml_GetAttibuteValue(pXmlKeys->m_strUse_ReportPaneKey, oNode, m_nUse_ReportPane);
	xml_GetAttibuteValue(pXmlKeys->m_strUseAppSelConfigKey, oNode, m_nUseAppSelConfig);
	xml_GetAttibuteValue(pXmlKeys->m_strName_TEST_PROJECT_EXKey, oNode, m_strName_TEST_PROJECT_EX);

	return 0;
}

long CToolsConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CToolsConfigXmlRWKeys *pXmlKeys = (CToolsConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUserServerKey, oElement, m_nUserServer);
	xml_SetAttributeValue(pXmlKeys->m_strUse_TASKTESTKey, oElement, m_nUse_TASKTEST);
	xml_SetAttributeValue(pXmlKeys->m_strUse_SDVMPPKey, oElement, m_nUse_SDVMPP);
	xml_SetAttributeValue(pXmlKeys->m_strUse_MDVMGRPKey, oElement, m_nUseMDVMGRP);
	xml_SetAttributeValue(pXmlKeys->m_strUse_ReportPaneKey, oElement, m_nUse_ReportPane);
	xml_SetAttributeValue(pXmlKeys->m_strUseAppSelConfigKey, oElement, m_nUseAppSelConfig);
	xml_SetAttributeValue(pXmlKeys->m_strName_TEST_PROJECT_EXKey, oElement, m_strName_TEST_PROJECT_EX);

	return 0;
}

BOOL CToolsConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CToolsConfig *p = (CToolsConfig*)pObj;

	return TRUE;
}

BOOL CToolsConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CToolsConfig *p = (CToolsConfig*)pDest;

	return TRUE;
}

CBaseObject* CToolsConfig::Clone()
{
	CToolsConfig *p = new CToolsConfig();
	Copy(p);
	return p;
}

CExBaseObject* CToolsConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CToolsConfigXmlRWKeys *pXmlKeys = (CToolsConfigXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCToolObjectKey)
	{
		pNew = new CToolObject();
	}

	return pNew;
}

CExBaseObject* CToolsConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

void CToolsConfig::OpenToolsConfig()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("ToolsConfig.xml");

	OpenXmlFile(strFile, GetXmlElementKey(), CToolsConfigXmlRWKeys::g_pXmlKeys);

	xlang_TranslateByResourceFileEx(this, _T("ToolsConfig.xml"));
}

void CToolsConfig::SaveToolsConfig()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("ToolsConfig.xml");

	SaveXmlFile(strFile, CToolsConfigXmlRWKeys::g_pXmlKeys);
}

long CToolsConfig::GetCount_cmd()
{
	POS pos = GetHeadPosition();
	CToolObject *pTool = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pTool = (CToolObject *)GetNext(pos);

		if (pTool->IsType_cmd())
		{
			nCount++;
		}
	}

	return nCount;
}

long CToolsConfig::GetCount_exe()
{
	POS pos = GetHeadPosition();
	CToolObject *pTool = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		pTool = (CToolObject *)GetNext(pos);

		if (pTool->IsType_exe())
		{
			nCount++;
		}
	}

	return nCount;
}

CToolObject* CToolsConfig::FindToolObject(UINT nCmdID)
{
	POS pos = GetHeadPosition();
	CToolObject *pTool = NULL;
	CToolObject *pFind = NULL;

	while (pos != NULL)
	{
		pTool = (CToolObject *)GetNext(pos);

		if (pTool->m_nCmdID == nCmdID)
		{
			pFind = pTool;
			break;
		}
	}

	return pFind;
}

