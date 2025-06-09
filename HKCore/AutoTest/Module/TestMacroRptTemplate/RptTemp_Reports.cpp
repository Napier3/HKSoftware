//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Reports.cpp  CRptTemp_Reports


#include "stdafx.h"
#include "RptTemp_Reports.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Reports::CRptTemp_Reports()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_Reports::~CRptTemp_Reports()
{
}

long CRptTemp_Reports::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_Reports::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_Reports::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_Reports::InitAfterRead()
{
}

BOOL CRptTemp_Reports::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_Reports *p = (CRptTemp_Reports*)pObj;

	return TRUE;
}

BOOL CRptTemp_Reports::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_Reports *p = (CRptTemp_Reports*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_Reports::Clone()
{
	CRptTemp_Reports *p = new CRptTemp_Reports();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Reports::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Reports *p = new CRptTemp_Reports();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Reports::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_VALUE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_Reports::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ReportKey)
	{
		pNew = new CRptTemp_Report();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ValueKey)
	{
		pNew = new CRptTemp_Value();
	}

	return pNew;
}

CExBaseObject* CRptTemp_Reports::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
	{
		pNew = new CRptTemp_Report();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_VALUE)
	{
		pNew = new CRptTemp_Value();
	}

	return pNew;
}
