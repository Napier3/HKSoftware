//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndPageRef.cpp  CUIWndPageRef


#include "stdafx.h"
#include "UIWndPageDef.h"

CUIWndPageDef::CUIWndPageDef()
{
	//初始化属性

	//初始化成员变量
	m_pPage = NULL;
}

CUIWndPageDef::~CUIWndPageDef()
{
	if (m_pPage != NULL)
	{
		delete m_pPage;
		m_pPage = NULL;
	}
}

long CUIWndPageDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strPageFileKey, oNode, m_strPageFile);

	return 0;
}

long CUIWndPageDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strPageFileKey, oElement, m_strPageFile);

	return 0;
}

long CUIWndPageDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPageFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPageFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPageFile);
	}

	return 0;
}

void CUIWndPageDef::InitAfterRead()
{
}

BOOL CUIWndPageDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndPageDef *p = (CUIWndPageDef*)pObj;

	return TRUE;
}

BOOL CUIWndPageDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CUIWndPageDef *p = (CUIWndPageDef*)pDest;

	return TRUE;
}

CBaseObject* CUIWndPageDef::Clone()
{
	CUIWndPageDef *p = new CUIWndPageDef();
	Copy(p);
	return p;
}

CUIWndPage* CUIWndPageDef::GetPage()
{
	if (m_pPage != NULL)
	{
		return m_pPage;
	}

	m_pPage = new CUIWndPage();
	m_pPage->SetPageFile(m_strPageFile);
	m_pPage->LoadPage();

	return m_pPage;
}

