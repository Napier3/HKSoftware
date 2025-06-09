//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_MacroCharItems.cpp  CRptTemp_MacroCharItems


#include "stdafx.h"
#include "RptTemp_MacroCharItems.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_MacroCharItems::CRptTemp_MacroCharItems()
{
	//初始化属性

	//初始化成员变量
	m_pReportTemplateDef = NULL;
	m_pReportDef = NULL;
	m_pMacroTest = NULL;
	m_pReport = NULL;
	m_pReportTemplate = NULL;
}

CRptTemp_MacroCharItems::~CRptTemp_MacroCharItems()
{
}

long CRptTemp_MacroCharItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacro_IdKey, oNode, m_strMacro_Id);
	return 0;
}

long CRptTemp_MacroCharItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacro_IdKey, oElement, m_strMacro_Id);
	return 0;
}

long CRptTemp_MacroCharItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacro_Id);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacro_Id);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacro_Id);
	}
	return 0;
}

void CRptTemp_MacroCharItems::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
		{
			m_pReportTemplateDef = (CRptTemp_ReportTemplateDef*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
		{
			m_pReportDef = (CRptTemp_ReportDef*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
		{
			m_pMacroTest = (CRptTemp_MacroTest *)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
		{
			m_pReport = (CRptTemp_Report*)p;
		}
		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
		{
			m_pReportTemplate = (CRptTemp_ReportTemplate*)p;
		}
	}
}

BOOL CRptTemp_MacroCharItems::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_MacroCharItems *p = (CRptTemp_MacroCharItems*)pObj;

	if(m_strMacro_Id != p->m_strMacro_Id)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_MacroCharItems::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_MacroCharItems *p = (CRptTemp_MacroCharItems*)pDest;

	p->m_strMacro_Id = m_strMacro_Id;
	return TRUE;
}

CBaseObject* CRptTemp_MacroCharItems::Clone()
{
	CRptTemp_MacroCharItems *p = new CRptTemp_MacroCharItems();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_MacroCharItems::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_MacroCharItems *p = new CRptTemp_MacroCharItems();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_MacroCharItems::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_MacroCharItems::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ReportDefKey)
	{
		pNew = new CRptTemp_ReportDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_MacroTestKey)
	{
		pNew = new CRptTemp_MacroTest();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateDefKey)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportKey)
	{
		pNew = new CRptTemp_Report();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

CExBaseObject* CRptTemp_MacroCharItems::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTDEF)
	{
		pNew = new CRptTemp_ReportDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
	{
		pNew = new CRptTemp_MacroTest();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORT)
	{
		pNew = new CRptTemp_Report();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		pNew = new CRptTemp_ReportTemplate();
	}

	return pNew;
}

long CRptTemp_MacroCharItems::GetMacroTestCount()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROTEST)
		{
			continue;
		}

		nCount++;
	}

	return nCount;
}

CRptTemp_MacroTest* CRptTemp_MacroCharItems::GetMacroTestByIndex(long nIndex)
{
	CRptTemp_MacroTest* pFind = NULL;
	long nFind = 0;
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROTEST)
		{
			continue;
		}

		if (nFind == nIndex)
		{
			pFind = (CRptTemp_MacroTest*)pObj;
			break;
		}

		nFind++;
	}

	return pFind;
}