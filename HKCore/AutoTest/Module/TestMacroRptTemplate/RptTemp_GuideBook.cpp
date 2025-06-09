//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_GuideBook.cpp  CRptTemp_GuideBook


#include "stdafx.h"
#include "RptTemp_GuideBook.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_GuideBook::CRptTemp_GuideBook()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_GuideBook::~CRptTemp_GuideBook()
{
}

long CRptTemp_GuideBook::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_GuideBook::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_GuideBook::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CRptTemp_GuideBook::InitAfterRead()
{
}

BOOL CRptTemp_GuideBook::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_GuideBook *p = (CRptTemp_GuideBook*)pObj;

	return TRUE;
}

BOOL CRptTemp_GuideBook::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_GuideBook *p = (CRptTemp_GuideBook*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_GuideBook::Clone()
{
	CRptTemp_GuideBook *p = new CRptTemp_GuideBook();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_GuideBook::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_GuideBook *p = new CRptTemp_GuideBook();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_GuideBook::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_GuideBook::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ItemsKey)
	{
		pNew = new CRptTemp_Items();
	}

	return pNew;
}

CExBaseObject* CRptTemp_GuideBook::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		pNew = new CRptTemp_Items();
	}

	return pNew;
}
