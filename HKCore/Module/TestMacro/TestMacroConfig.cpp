//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacroConfig.cpp  CTestMacroConfig


#include "stdafx.h"
#include "TestMacroConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CTestMacroConfig
CTestMacroConfig::CTestMacroConfig()
{
	//初始化属性

	//初始化成员变量
}

CTestMacroConfig::~CTestMacroConfig()
{
}

long CTestMacroConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIecConfigFileKey, oNode, m_strIecConfigFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	if (m_strType.GetLength() == 0)
	{
		m_strType = g_strDefaultMacroType;
	}

	return 0;
}

long CTestMacroConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIecConfigFileKey, oElement, m_strIecConfigFile);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	return 0;
}

CBaseObject* CTestMacroConfig::Clone()
{
	CTestMacroConfig *p = new CTestMacroConfig();
	Copy(p);
	return p;
}

BOOL CTestMacroConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacroConfig *p = (CTestMacroConfig*)pDest;

	p->m_strIecConfigFile = m_strIecConfigFile;
	return TRUE;
}

BOOL CTestMacroConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacroConfig *p = (CTestMacroConfig*)pObj;

	if(m_strIecConfigFile != p->m_strIecConfigFile)
	{
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CTestMacroConfigs
CTestMacroConfigs::CTestMacroConfigs()
{
	//初始化属性

	//初始化成员变量
}

CTestMacroConfigs::~CTestMacroConfigs()
{
}

long CTestMacroConfigs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strActiveMacroTestKey, oNode, m_strActiveMacroTest);

	return 0;
}

long CTestMacroConfigs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strActiveMacroTestKey, oElement, m_strActiveMacroTest);

	return 0;
}

CBaseObject* CTestMacroConfigs::Clone()
{
	CTestMacroConfigs *p = new CTestMacroConfigs();
	Copy(p);
	return p;
}

BOOL CTestMacroConfigs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacroConfigs *p = (CTestMacroConfigs*)pDest;

	p->m_strType = m_strType;
	p->m_strActiveMacroTest = m_strActiveMacroTest;

	return TRUE;
}

BOOL CTestMacroConfigs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacroConfigs *p = (CTestMacroConfigs*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strActiveMacroTest != p->m_strActiveMacroTest)
	{
		return FALSE;
	}

	return TRUE;
}


CExBaseObject* CTestMacroConfigs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacroConfigKey)
	{
		pNew = new CTestMacroConfig();
	}

	return pNew;
}

CExBaseObject* CTestMacroConfigs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTESTMACROCONFIG)
	{
		pNew = new CTestMacroConfig();
	}

	return pNew;
}
