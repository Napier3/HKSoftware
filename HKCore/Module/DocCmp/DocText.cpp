//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocText.cpp  CDocText


#include "stdafx.h"
#include "DocText.h"

CDocText::CDocText()
{
	//初始化属性
	m_nStart = 0;
	m_nEnd = 0;
	m_nError = 0;

	//初始化成员变量
}

CDocText::~CDocText()
{
}


long CDocText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCmp_IdKey, oNode, m_strCmp_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strStartKey, oNode, m_nStart);
	xml_GetAttibuteValue(pXmlKeys->m_strEndKey, oNode, m_nEnd);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorKey, oNode, m_nError);

	if (g_nDocTextUseCdata != 0)
	{
		xml_GetCDATA(oNode, m_strTxt);
	}
	else
	{
		xml_GetElementText(NULL, oNode, m_strTxt);
		//xml_GetElementText(pXmlKeys->m_strCDocTextValKey, oNode, m_strTxt);
	}

	return 0;
}

long CDocText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDocCmpXmlRWKeys *pXmlKeys = (CDocCmpXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCmp_IdKey, oElement, m_strCmp_Id);
	xml_SetAttributeValue(pXmlKeys->m_strStartKey, oElement, m_nStart);
	xml_SetAttributeValue(pXmlKeys->m_strEndKey, oElement, m_nEnd);
	xml_SetAttributeValue(pXmlKeys->m_strErrorKey, oElement, m_nError);

	if (g_nDocTextUseCdata != 0)
	{
		xml_SetCDATA(oXMLDoc, oElement, m_strTxt);
	}
	else
	{
		xml_SetElementText(NULL, oXMLDoc, oElement, m_strTxt);
		//xml_SetElementText(pXmlKeys->m_strCDocTextValKey, oXMLDoc, oElement, m_strTxt);
	}

	return 0;
}

void CDocText::InitAfterRead()
{
}

BOOL CDocText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDocText *p = (CDocText*)pObj;

	if(m_strCmp_Id != p->m_strCmp_Id)
	{
		return FALSE;
	}

	if(m_strTxt != p->m_strTxt)
	{
		return FALSE;
	}

	if(m_nStart != p->m_nStart)
	{
		return FALSE;
	}

	if(m_nEnd != p->m_nEnd)
	{
		return FALSE;
	}

	if(m_nError != p->m_nError)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDocText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDocText *p = (CDocText*)pDest;

	p->m_strCmp_Id = m_strCmp_Id;
	p->m_strTxt = m_strTxt;
	p->m_nStart = m_nStart;
	p->m_nEnd = m_nEnd;
	p->m_nError = m_nError;
	return TRUE;
}

CBaseObject* CDocText::Clone()
{
	CDocText *p = new CDocText();
	Copy(p);
	return p;
}

void CDocText::Init()
{
	long nLen = m_strTxt.GetLength();

	//去掉换行符号
	if (m_strTxt.GetAt(nLen - 1) == 0x07)
	{
		m_strTxt.SetAt(nLen - 1, 0);
		m_strTxt.SetAt(nLen - 2, 0);
	}
	else
	{
		m_strTxt.SetAt(nLen - 1, 0);
	}
}


void CDocText::SetCmpError()
{
	if (m_strCmp_Id.GetLength() > 0)
	{
		return;
	}

	m_strCmp_Id = docmp_GenDocCmpID();
	m_nError = 1;
}


BOOL CDocText::Cmp(CDocText *pRef)
{
	if (pRef == NULL)
	{
		return FALSE;
	}

	m_strCmp_Id = docmp_GenDocCmpID();
	pRef->m_strCmp_Id = m_strCmp_Id;

	if( m_strTxt == pRef->m_strTxt)
	{
		return TRUE;
	}

	if (m_strTxt.GetLength() == pRef->m_strTxt.GetLength())
	{
		pRef->m_nError = 1;
		m_nError = 1;
		return FALSE;
	}

	if (m_strTxt.GetLength() > pRef->m_strTxt.GetLength())
	{
		m_nError = m_strTxt.Find(pRef->m_strTxt) < 0;
	}
	else
	{
		m_nError = pRef->m_strTxt.Find(m_strTxt) < 0;
	}

	pRef->m_nError = m_nError;

	return (m_nError == 0);
}

