//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_MacroTest.cpp  CRptTemp_MacroTest


#include "stdafx.h"
#include "RptTemp_MacroTest.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_MacroTest::CRptTemp_MacroTest()
{
	//初始化属性

	//初始化成员变量
	m_pRpeortsDef = NULL;
	m_pReportTemplateDef = NULL;
	m_pRpeorts = NULL;
	m_pReportTemplate = NULL;
	m_pEnable = NULL;
}

CRptTemp_MacroTest::~CRptTemp_MacroTest()
{
}

long CRptTemp_MacroTest::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacro_IdKey, oNode, m_strMacro_Id);
	xml_GetAttibuteValue(pXmlKeys->m_strRpt_ModeKey, oNode, m_strRpt_Mode);
	return 0;
}

long CRptTemp_MacroTest::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacro_IdKey, oElement, m_strMacro_Id);
	xml_SetAttributeValue(pXmlKeys->m_strRpt_ModeKey, oElement, m_strRpt_Mode);
	return 0;
}

long CRptTemp_MacroTest::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacro_Id);
		BinarySerializeCalLen(oBinaryBuffer, m_strRpt_Mode);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacro_Id);
		BinarySerializeRead(oBinaryBuffer, m_strRpt_Mode);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacro_Id);
		BinarySerializeWrite(oBinaryBuffer, m_strRpt_Mode);
	}
	return 0;
}

void CRptTemp_MacroTest::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTSDEF)
		{
			m_pRpeortsDef = (CRptTemp_ReportsDef*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
		{
			m_pReportTemplateDef = (CRptTemp_ReportTemplateDef*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTS)
		{
			m_pRpeorts = (CRptTemp_Reports*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
		{
			m_pReportTemplate = (CRptTemp_ReportTemplate*)p;
		}
		else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			m_pEnable = (CRptTemp_Enable*)p;
		}
	}
}

BOOL CRptTemp_MacroTest::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_MacroTest *p = (CRptTemp_MacroTest*)pObj;

	if(m_strMacro_Id != p->m_strMacro_Id)
	{
		return FALSE;
	}

	if(m_strRpt_Mode != p->m_strRpt_Mode)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CRptTemp_MacroTest::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_MacroTest *p = (CRptTemp_MacroTest*)pDest;

	p->m_strMacro_Id = m_strMacro_Id;
	p->m_strRpt_Mode = m_strRpt_Mode;
	return TRUE;
}

CBaseObject* CRptTemp_MacroTest::Clone()
{
	CRptTemp_MacroTest *p = new CRptTemp_MacroTest();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_MacroTest::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_MacroTest *p = new CRptTemp_MacroTest();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_MacroTest::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTSDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		return TRUE;
	}


	return FALSE;
}

CExBaseObject* CRptTemp_MacroTest::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateDefKey)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportsDefKey)
	{
		pNew = new CRptTemp_ReportsDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateKey)
	{
		pNew = new CRptTemp_ReportTemplate();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportsKey)
	{
		pNew = new CRptTemp_Reports();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_EnableKey)
	{
		pNew = new CRptTemp_Enable();
	}
	return pNew;
}

CExBaseObject* CRptTemp_MacroTest::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTSDEF)
	{
		pNew = new CRptTemp_ReportsDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATE)
	{
		pNew = new CRptTemp_ReportTemplate();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTS)
	{
		pNew = new CRptTemp_Reports();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		pNew = new CRptTemp_Enable();
	}
	return pNew;
}

CRptTemp_Reports* CRptTemp_MacroTest::AddReprots()
{
	if (m_pRpeorts != NULL)
	{
		return m_pRpeorts;
	}

	m_pRpeorts = new CRptTemp_Reports();
	AddNewChild(m_pRpeorts);
	BringToHead(m_pRpeorts);
	return m_pRpeorts;
}

BOOL CRptTemp_MacroTest::IsEnable(CExBaseList *pParas)
{
	if (m_pEnable == NULL)
	{
		//默认使能为1
		return TRUE;
	}

	return m_pEnable->IsEnable(pParas);
}