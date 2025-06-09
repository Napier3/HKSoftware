//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TestMacroUiRpt.cpp  CRptTemp_TestMacroUiRpt


#include "stdafx.h"
#include "RptTemp_TestMacroUiRpt.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_TestMacroUiRpt::CRptTemp_TestMacroUiRpt()
{
	//初始化属性

	//初始化成员变量
	m_pReportTemplate = NULL;
}

CRptTemp_TestMacroUiRpt::~CRptTemp_TestMacroUiRpt()
{
}

long CRptTemp_TestMacroUiRpt::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_TestMacroUiRpt::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_TestMacroUiRpt::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_TestMacroUiRpt::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
		{
			m_pReportTemplate = (CRptTemp_ReportTemplate*)p;
		}
	}
}

BOOL CRptTemp_TestMacroUiRpt::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_TestMacroUiRpt *p = (CRptTemp_TestMacroUiRpt*)pObj;

	return TRUE;
}

BOOL CRptTemp_TestMacroUiRpt::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_TestMacroUiRpt *p = (CRptTemp_TestMacroUiRpt*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_TestMacroUiRpt::Clone()
{
	CRptTemp_TestMacroUiRpt *p = new CRptTemp_TestMacroUiRpt();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_TestMacroUiRpt::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_TestMacroUiRpt *p = new CRptTemp_TestMacroUiRpt();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_TestMacroUiRpt::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_TestMacroUiRpt::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ItemsKey)
	{
		pNew = new CRptTemp_Items();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

CExBaseObject* CRptTemp_TestMacroUiRpt::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		pNew = new CRptTemp_Items();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}
