//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportTemplateDef.cpp  CRptTemp_ReportTemplateDef


#include "stdafx.h"
#include "RptTemp_ReportTemplateDef.h"
#include "RptTemp_PngDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ReportTemplateDef::CRptTemp_ReportTemplateDef()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_ReportTemplateDef::~CRptTemp_ReportTemplateDef()
{
}

long CRptTemp_ReportTemplateDef::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplateDef::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplateDef::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_ReportTemplateDef::InitAfterRead()
{
}

BOOL CRptTemp_ReportTemplateDef::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_ReportTemplateDef *p = (CRptTemp_ReportTemplateDef*)pObj;

	return TRUE;
}

BOOL CRptTemp_ReportTemplateDef::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_ReportTemplateDef *p = (CRptTemp_ReportTemplateDef*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_ReportTemplateDef::Clone()
{
	CRptTemp_ReportTemplateDef *p = new CRptTemp_ReportTemplateDef();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ReportTemplateDef::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ReportTemplateDef *p = new CRptTemp_ReportTemplateDef();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ReportTemplateDef::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_NEWPAGE) //ftt 2024.12.9
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_ReportTemplateDef::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_TitleDefKey)
	{
		pNew = new CRptTemp_TitleDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_TextDefKey)
	{
		pNew = new CRptTemp_TextDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_GridDefKey)
	{
		pNew = new CRptTemp_GridDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_PngDefKey)
	{
		pNew = new CRptTemp_PngDef();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_NewPageKey)  //ftt 2024.12.9
	{
		pNew = new CRptTemp_NewPage();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ReportTemplateDef::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_TITLEDEF)
	{
		pNew = new CRptTemp_TitleDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXTDEF)
	{
		pNew = new CRptTemp_TextDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_GRIDDEF)
	{
		pNew = new CRptTemp_GridDef();
	}

	else if (nClassID == MNGRCLASSID_CRPTTEMP_PNGDEF)
	{
		pNew = new CRptTemp_PngDef();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_NEWPAGE) //ftt 2024.12.9
	{
		pNew = new CRptTemp_NewPage();
	}

	return pNew;
}

CString CRptTemp_ReportTemplateDef::GetDataMode()
{
	CRptTemp_GridDef *pGridDef = (CRptTemp_GridDef *)FindByClassID(MNGRCLASSID_CRPTTEMP_GRIDDEF);

	if (pGridDef == NULL)
	{
		return RPT_TEMPLATE_DATAMODE_NOT_DEF;  //未定义，非法
	}

	return pGridDef->m_strData_Mode;
}