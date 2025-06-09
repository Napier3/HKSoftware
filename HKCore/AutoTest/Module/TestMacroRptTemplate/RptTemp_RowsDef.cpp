//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_RowsDef.cpp  CRptTemp_RowsDef


#include "stdafx.h"
#include "RptTemp_RowsDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_RowsDef::CRptTemp_RowsDef()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_RowsDef::~CRptTemp_RowsDef()
{
}

long CRptTemp_RowsDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_RowsDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_RowsDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_RowsDef::InitAfterRead()
{
}

BOOL CRptTemp_RowsDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_RowsDef *p = (CRptTemp_RowsDef*)pObj;

	return TRUE;
}

BOOL CRptTemp_RowsDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_RowsDef *p = (CRptTemp_RowsDef*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_RowsDef::Clone()
{
	CRptTemp_RowsDef *p = new CRptTemp_RowsDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_RowsDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_RowsDef *p = new CRptTemp_RowsDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_RowsDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_ROWDEF)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_RowsDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_RowDefKey)
	{
		pNew = new CRptTemp_RowDef();
	}

	return pNew;
}

CExBaseObject* CRptTemp_RowsDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_ROWDEF)
	{
		pNew = new CRptTemp_RowDef();
	}

	return pNew;
}
