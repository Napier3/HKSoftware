//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextMngr.cpp  CFilterTextMngr


#include "stdafx.h"
#include "FilterTextMngr.h"

CFilterTextMngr::CFilterTextMngr()
{
	//初始化属性

	//初始化成员变量
}

CFilterTextMngr::~CFilterTextMngr()
{
}

long CFilterTextMngr::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CGlobalDataMngrXmlRWKeys *pXmlKeys = (CGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CFilterTextMngr::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CGlobalDataMngrXmlRWKeys *pXmlKeys = (CGlobalDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CFilterTextMngr::InitAfterRead()
{
}

BOOL CFilterTextMngr::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CFilterTextMngr *p = (CFilterTextMngr*)pObj;

	return TRUE;
}

BOOL CFilterTextMngr::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CFilterTextMngr *p = (CFilterTextMngr*)pDest;

	return TRUE;
}

CExBaseObject* CFilterTextMngr::Clone()
{
	CFilterTextMngr *p = new CFilterTextMngr();
	Copy(p);
	return p;
}

CExBaseObject* CFilterTextMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGlobalDataMngrXmlRWKeys *pXmlKeys = (CGlobalDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCFilterTextKey)
	{
		pNew = new CFilterText();
	}

	return pNew;
}

CExBaseObject* CFilterTextMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TFLTCLASSID_CFILTERTEXT)
	{
		pNew = new CFilterText();
	}

	return pNew;
}


BOOL CFilterTextMngr::OpenXmlFile(const CString &strFile)
{
	m_strFile = strFile;

	return CExBaseObject::OpenXmlFile(strFile, CGlobalDataMngrXmlRWKeys::CFilterTextMngrKey(), CGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CFilterTextMngr::SaveXmlFile()
{
	return CExBaseObject::SaveXmlFile(m_strFile, CGlobalDataMngrXmlRWKeys::g_pXmlKeys);
}

CFilterText* CFilterTextMngr::AddText(const CString &strText)
{
	CFilterText *pText = new CFilterText();
	pText->m_strName = strText;
	pText->m_strID = strText;
	AddTail(pText);
	pText->SetParent(this);

	return pText;
}