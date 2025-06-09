//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterText.cpp  CFilterText


#include "stdafx.h"
#include "FilterText.h"
#include "FilterTextMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFilterText::CFilterText()
{
	//初始化属性

	//初始化成员变量
}

CFilterText::~CFilterText()
{
}

long CFilterText::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey, oNode, m_strName);	
	//xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);
	m_strID = m_strName;

	CFilterTextXmlRWKeys *pXmlKeys = (CFilterTextXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CFilterText::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
//	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);

	CFilterTextXmlRWKeys *pXmlKeys = (CFilterTextXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CFilterText::InitAfterRead()
{
}

BOOL CFilterText::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CFilterText *p = (CFilterText*)pObj;

	return TRUE;
}

BOOL CFilterText::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CFilterText *p = (CFilterText*)pDest;

	return TRUE;
}

CBaseObject* CFilterText::Clone()
{
	CFilterText *p = new CFilterText();
	Copy(p);
	return p;
}

CString CFilterText::GetFile()
{
	CFilterTextMngr *pMngr = (CFilterTextMngr*)GetParent();

	if (m_strName.GetAt(2) == ':')
	{
		return m_strName;
	}
	else
	{
		CString strFile;
		strFile = pMngr->m_strRootPath + m_strName;

		return strFile;
	}
}

void CFilterText::SetFile(const CString &strFile)
{
	CFilterTextMngr *pMngr = (CFilterTextMngr*)GetParent();
	m_strName = strFile;
	m_strName.Replace(pMngr->m_strRootPath, _T(""));
}
