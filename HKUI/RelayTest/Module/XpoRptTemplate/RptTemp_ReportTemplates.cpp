//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportTemplates.cpp  RptTemp_ReportTemplates


#include "stdafx.h"
#include "RptTemp_ReportTemplates.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ReportTemplates::CRptTemp_ReportTemplates()
{
	//初始化属性

	//初始化成员变量
	//m_pReportTemplate = NULL; //ftt 2024.6.17 delete
}

CRptTemp_ReportTemplates::~CRptTemp_ReportTemplates()
{
}

long CRptTemp_ReportTemplates::XmlReadOwn(CXmlRWNodeBase& oNode, CXmlRWKeys* pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys* pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplates::XmlWriteOwn(CXmlRWDocBase& oXMLDoc, CXmlRWElementBase& oElement, CXmlRWKeys* pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys* pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplates::SerializeOwn(CBinarySerialBuffer& oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if (oBinaryBuffer.IsReadMode())
	{
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CRptTemp_ReportTemplates::InitAfterRead()
{
	//ftt 2024.6.17 delete 
	/*POS pos = GetHeadPosition();
	CBaseObject* p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
		{
			m_pReportTemplate = (CRptTemp_ReportTemplate*)p;
		}
	}*/
}

BOOL CRptTemp_ReportTemplates::IsEqualOwn(CBaseObject* pObj)
{
	if (this == pObj)
	{
		return TRUE;
	}

	CRptTemp_ReportTemplates* p = (CRptTemp_ReportTemplates*)pObj;

	return TRUE;
}

BOOL CRptTemp_ReportTemplates::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	CRptTemp_ReportTemplates* p = (CRptTemp_ReportTemplates*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_ReportTemplates::Clone()
{
	CRptTemp_ReportTemplates* p = new CRptTemp_ReportTemplates();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ReportTemplates::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ReportTemplates* p = new CRptTemp_ReportTemplates();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ReportTemplates::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		return TRUE;
	}

	//ftt delete 2024.6.15
	/*if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		return TRUE;
	}*/

	return FALSE;
}

CExBaseObject* CRptTemp_ReportTemplates::CreateNewChild(const CString& strClassID, BOOL& bAddToTail, CXmlRWKeys* pXmlRWKeys)
{
	CExBaseObject* pNew = NULL;
	CTestMacroRptTemplateXmlRWKeys* pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	//ftt delete 2024.6.15
	//if (strClassID == pXmlKeys->m_strCRptTemp_ItemsKey)
	//{
	//	pNew = new CRptTemp_Items();
	//}
	//else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ReportTemplates::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject* pNew = NULL;

	//ftt delete 2024.6.15
	//if (nClassID == MNGRCLASSID_CRPTTEMP_ITEMS)
	//{
	//	pNew = new CRptTemp_Items();
	//}
	//else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}
