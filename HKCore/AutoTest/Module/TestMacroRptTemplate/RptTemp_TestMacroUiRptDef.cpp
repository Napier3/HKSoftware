//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TestMacroUiRptDef.cpp  CRptTemp_TestMacroUiRptDef


#include "stdafx.h"
#include "RptTemp_TestMacroUiRptDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_TestMacroUiRptDef::CRptTemp_TestMacroUiRptDef()
{
	//初始化属性

	//初始化成员变量
	m_pReportTemplateDef = NULL;
	m_pItemsTec = NULL;
}

CRptTemp_TestMacroUiRptDef::~CRptTemp_TestMacroUiRptDef()
{
}

long CRptTemp_TestMacroUiRptDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_TestMacroUiRptDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_TestMacroUiRptDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_TestMacroUiRptDef::InitAfterRead()
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
		else if (nClassID == MNGRCLASSID_CRPTTEMP_GROUP)
		{
			m_pItemsTec = (CRptTemp_Group *)p;
		}
	}
}

BOOL CRptTemp_TestMacroUiRptDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CRptTemp_TestMacroUiRptDef *p = (CRptTemp_TestMacroUiRptDef*)pObj;

	return TRUE;
}

BOOL CRptTemp_TestMacroUiRptDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CRptTemp_TestMacroUiRptDef *p = (CRptTemp_TestMacroUiRptDef*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_TestMacroUiRptDef::Clone()
{
	CRptTemp_TestMacroUiRptDef *p = new CRptTemp_TestMacroUiRptDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_TestMacroUiRptDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_TestMacroUiRptDef *p = new CRptTemp_TestMacroUiRptDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_TestMacroUiRptDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
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

	if (nClassID == MNGRCLASSID_CRPTTEMP_GROUP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_TestMacroUiRptDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_MacroCharItemsKey)
	{
		pNew = new CRptTemp_MacroCharItems();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_MacroTestKey)
	{
		pNew = new CRptTemp_MacroTest();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_ReportTemplateDefKey)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (strClassID == pXmlKeys->m_strCDataGroupKey)
	{
		pNew = new CRptTemp_Group();
	}

	return pNew;
}

CExBaseObject* CRptTemp_TestMacroUiRptDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
	{
		pNew = new CRptTemp_MacroCharItems();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_MACROTEST)
	{
		pNew = new CRptTemp_MacroTest();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_REPORTTEMPLATEDEF)
	{
		pNew = new CRptTemp_ReportTemplateDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_GROUP)
	{
		pNew = new CRptTemp_Group();
	}

	return pNew;
}

CRptTemp_MacroTest* CRptTemp_TestMacroUiRptDef::FindMacroTestByMacroID(const CString &strMacroID, CExBaseList *pListParas)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CRptTemp_MacroTest *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROTEST)
		{
			continue;
		}

		CRptTemp_MacroTest *pMacroTest = (CRptTemp_MacroTest *)pObj;
		
		if (pMacroTest->m_strMacro_Id != strMacroID)
		{
			continue;
		}

		if (pMacroTest->IsEnable(pListParas))
		{
			pFind = pMacroTest;
			break;
		}
	}

	return pFind;
}

CRptTemp_MacroCharItems* CRptTemp_TestMacroUiRptDef::FindMacroCharItemsByMacroID(const CString &strMacroID)
{
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;
	CRptTemp_MacroCharItems *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != MNGRCLASSID_CRPTTEMP_MACROCHARITEMS)
		{
			continue;
		}

		CRptTemp_MacroCharItems *pMacroCharItems = (CRptTemp_MacroCharItems *)pObj;

		if (pMacroCharItems->m_strMacro_Id == strMacroID)
		{
			pFind = pMacroCharItems;
			break;
		}
	}

	return pFind;
}
