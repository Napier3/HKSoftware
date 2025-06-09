//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MmsEngineDsCfg.cpp  CMmsEngineDsCfg


#include "stdafx.h"
#include "MmsEngineDsCfg.h"

CMmsEngineDsCfg::CMmsEngineDsCfg()
{
	//初始化属性
	m_nRead = 0;

	//初始化成员变量
}

CMmsEngineDsCfg::~CMmsEngineDsCfg()
{
}

long CMmsEngineDsCfg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strKeyKey, oNode, m_strKey);
	xml_GetAttibuteValue(pXmlKeys->m_strReadKey, oNode, m_nRead);
	return 0;
}

long CMmsEngineDsCfg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMmsEngineConfigXmlRWKeys *pXmlKeys = (CMmsEngineConfigXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strKeyKey, oElement, m_strKey);
	xml_SetAttributeValue(pXmlKeys->m_strReadKey, oElement, m_nRead);
	return 0;
}

BOOL CMmsEngineDsCfg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMmsEngineDsCfg *p = (CMmsEngineDsCfg*)pObj;

	if(m_strKey != p->m_strKey)
	{
		return FALSE;
	}

	if(m_nRead != p->m_nRead)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMmsEngineDsCfg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CMmsEngineDsCfg *p = (CMmsEngineDsCfg*)pDest;

	p->m_strKey = m_strKey;
	p->m_nRead = m_nRead;
	return TRUE;
}

CBaseObject* CMmsEngineDsCfg::Clone()
{
	CMmsEngineDsCfg *p = new CMmsEngineDsCfg();
	Copy(p);
	return p;
}

