//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportTemplate.cpp  CRptTemp_ReportTemplate


#include "stdafx.h"
#include "RptTemp_ReportTemplate.h"
#include "RptTemp_Png.h"
#include "RptTemp_Items.h"

class CRptTemp_Items;

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_ReportTemplate::CRptTemp_ReportTemplate()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_ReportTemplate::~CRptTemp_ReportTemplate()
{
}

long CRptTemp_ReportTemplate::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplate::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CRptTemp_ReportTemplate::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CRptTemp_ReportTemplate::InitAfterRead()
{
}

BOOL CRptTemp_ReportTemplate::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CRptTemp_ReportTemplate *p = (CRptTemp_ReportTemplate*)pObj;

	return TRUE;
}

BOOL CRptTemp_ReportTemplate::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CRptTemp_ReportTemplate *p = (CRptTemp_ReportTemplate*)pDest;

	return TRUE;
}

CBaseObject* CRptTemp_ReportTemplate::Clone()
{
	CRptTemp_ReportTemplate *p = new CRptTemp_ReportTemplate();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_ReportTemplate::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_ReportTemplate *p = new CRptTemp_ReportTemplate();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_ReportTemplate::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_TITLE)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_TEXT)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_GRID)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CRPTTEMP_PNG)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CRptTemp_ReportTemplate::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_TitleKey)
	{
		pNew = new CRptTemp_Title();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_TextKey)
	{
		pNew = new CRptTemp_Text();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_GridKey)
	{
		pNew = new CRptTemp_Grid();
	}
	else if (strClassID == pXmlKeys->m_strCRptTemp_PngKey)
	{
		pNew = new CRptTemp_Png();
	}

	return pNew;
}

CExBaseObject* CRptTemp_ReportTemplate::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_TITLE)
	{
		pNew = new CRptTemp_Title();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_TEXT)
	{
		pNew = new CRptTemp_Text();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_GRID)
	{
		pNew = new CRptTemp_Grid();
	}
	else if (nClassID == MNGRCLASSID_CRPTTEMP_PNG)
	{
		pNew = new CRptTemp_Png();
	}

	return pNew;
}

CString CRptTemp_ReportTemplate::GetDataMode()
{
	CRptTemp_Grid *pGrid = (CRptTemp_Grid *)FindByClassID(MNGRCLASSID_CRPTTEMP_GRID);

	if (pGrid == NULL)
	{
		return RPT_TEMPLATE_DATAMODE_NOT_DEF;  //未定义，非法
	}

	return pGrid->m_strData_Mode;
}

BOOL CRptTemp_ReportTemplate::AddTailToIndexList(CExBaseObject *pObj)
{
	CExBaseObject *pParent = (CExBaseObject *)GetParent();

	if (pParent == NULL)
	{
		return FALSE;
	}

	if (pParent->GetClassID() != MNGRCLASSID_CRPTTEMP_ITEMS)
	{
		return FALSE;
	}

	CRptTemp_Items *pItems = (CRptTemp_Items *)pParent;
	pItems->AddTailToIndexList(pObj);

	return TRUE;
}