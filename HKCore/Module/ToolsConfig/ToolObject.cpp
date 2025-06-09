//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ToolObject.cpp  CToolObject


#include "stdafx.h"
#include "ToolObject.h"

const CString CToolObject::g_strToolType_cmd = _T("cmd");
const CString CToolObject::g_strToolType_exe = _T("exe");

const CString CToolObject::g_strToolServer_macrotest = _T("macrotest");
const CString CToolObject::g_strToolServer_ppengine = _T("ppengine");

CToolObject::CToolObject()
{
	//初始化属性

	//初始化成员变量
	m_nCmdID = 0;
}

CToolObject::~CToolObject()
{
}

long CToolObject::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CToolsConfigXmlRWKeys *pXmlKeys = (CToolsConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strModeKey, oNode, m_strMode);
	xml_GetAttibuteValue(pXmlKeys->m_strParaKey, oNode, m_strPara);
	xml_GetAttibuteValue(pXmlKeys->m_strTitleKey, oNode, m_strTitle);

	xml_GetAttibuteValue(pXmlKeys->m_strServerNameKey, oNode, m_strServerName);

	return 0;
}

long CToolObject::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CToolsConfigXmlRWKeys *pXmlKeys = (CToolsConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strModeKey, oElement, m_strMode);
	xml_SetAttributeValue(pXmlKeys->m_strParaKey, oElement, m_strPara);
	xml_SetAttributeValue(pXmlKeys->m_strTitleKey, oElement, m_strTitle);

	xml_SetAttributeValue(pXmlKeys->m_strServerNameKey, oElement, m_strServerName);

	return 0;
}

BOOL CToolObject::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CToolObject *p = (CToolObject*)pDest;

	p->m_strType = m_strType;
	p->m_strMode = m_strMode;
	p->m_strPara = m_strPara;
	p->m_strTitle = m_strTitle;
	p->m_strServerName = m_strServerName;

	return TRUE;
}

CBaseObject* CToolObject::Clone()
{
	CToolObject *p = new CToolObject();
	Copy(p);
	return p;
}

