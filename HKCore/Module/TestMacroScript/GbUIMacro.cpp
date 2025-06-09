//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbUIMacro.cpp  CGbUIMacro


#include "stdafx.h"
#include "GbUIMacro.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGbUIMacro::CGbUIMacro()
{
	//初始化属性

	//初始化成员变量
}

CGbUIMacro::~CGbUIMacro()
{
}

long CGbUIMacro::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDLLKey, oNode, m_strDLL);
	return 0;
}

long CGbUIMacro::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDLLKey, oElement, m_strDLL);
	return 0;
}

BOOL CGbUIMacro::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CGbUIMacro *p = (CGbUIMacro*)pObj;

	if(m_strDLL != p->m_strDLL)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CGbUIMacro::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CGbUIMacro *p = (CGbUIMacro*)pDest;

	p->m_strDLL = m_strDLL;
	return TRUE;
}

CBaseObject* CGbUIMacro::Clone()
{
	CGbUIMacro *p = new CGbUIMacro();
	Copy(p);
	return p;
}

