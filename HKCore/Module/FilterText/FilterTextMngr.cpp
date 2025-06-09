//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextMngr.cpp  CFilterTextMngr


#include "stdafx.h"
#include "FilterTextMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFilterTextMngr::CFilterTextMngr()
{
	//初始化属性

	//初始化成员变量
	m_bChanged = FALSE;
}

CFilterTextMngr::~CFilterTextMngr()
{
}

long CFilterTextMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CFilterTextXmlRWKeys *pXmlKeys = (CFilterTextXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CFilterTextMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CFilterTextXmlRWKeys *pXmlKeys = (CFilterTextXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CFilterTextMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CFilterText *p = NULL;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CFilterText *)GetNext(pos);

		if (p->m_strName.GetLength() == 0)
		{
			DeleteAt(posPrev);
		}
	}
}

BOOL CFilterTextMngr::IsEqualOwn(CBaseObject* pObj)
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

BOOL CFilterTextMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CFilterTextMngr *p = (CFilterTextMngr*)pDest;

	return TRUE;
}

CBaseObject* CFilterTextMngr::Clone()
{
	CFilterTextMngr *p = new CFilterTextMngr();
	Copy(p);
	return p;
}

CExBaseObject* CFilterTextMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CFilterTextXmlRWKeys *pXmlKeys = (CFilterTextXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCFilterTextKey)
	{
		pNew = new CFilterText();
	}

	return pNew;
}

CExBaseObject* CFilterTextMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == FLTCLASSID_CFILTERTEXT)
	{
		pNew = new CFilterText();
	}

	return pNew;
}


BOOL CFilterTextMngr::OpenXmlFile(const CString &strFile)
{
	m_strFile = strFile;

	return CExBaseObject::OpenXmlFile(strFile, CFilterTextXmlRWKeys::CFilterTextMngrKey(), CFilterTextXmlRWKeys::g_pXmlKeys);
}

BOOL CFilterTextMngr::SaveXmlFile()
{
	return CExBaseObject::SaveXmlFile(m_strFile, CFilterTextXmlRWKeys::g_pXmlKeys);
}

CFilterText* CFilterTextMngr::AddText(const CString &strText)
{
	CFilterText *pText = NULL;
	
	pText = (CFilterText*)FindByName(strText);

	if (pText == NULL)
	{
		pText = new CFilterText();
		pText->m_strName = strText;
		pText->m_strID = strText;
		AddTail(pText);
		pText->SetParent(this);
		m_bChanged = TRUE;
	}

	return pText;
}