//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Head.cpp  CRptTemp_Head


#include "stdafx.h"
#include "RptTemp_Head.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Head::CRptTemp_Head()
{
	//初始化属性
	m_nMergeCol = 0;
	//初始化成员变量
}

CRptTemp_Head::~CRptTemp_Head()
{
}

long CRptTemp_Head::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_Head::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_Head::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CRptTemp_Head::InitAfterRead()
{
}

BOOL CRptTemp_Head::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Head *p = (CRptTemp_Head*)pObj;

	return TRUE;
}

BOOL CRptTemp_Head::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Head *p = (CRptTemp_Head*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_Head::Clone()
{
	CRptTemp_Head *p = new CRptTemp_Head();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Head::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Head *p = new CRptTemp_Head();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Head::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Head::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_CellKey)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Head::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_CELL)
	{
		pNew = new CRptTemp_Cell();
	}

	return pNew;
}
