//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_Wzd_TemplateUnits.cpp  CAts_Wzd_TemplateUnits


#include "stdafx.h"
#include "Ats_Wzd_TemplateUnits.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CAts_Wzd_TemplateUnits::CAts_Wzd_TemplateUnits()
{
	//初始化属性

	//初始化成员变量
}

CAts_Wzd_TemplateUnits::~CAts_Wzd_TemplateUnits()
{
}

long CAts_Wzd_TemplateUnits::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TemplateUnits::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAts_Wzd_TemplateUnits::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CAts_Wzd_TemplateUnits::InitAfterRead()
{
}

BOOL CAts_Wzd_TemplateUnits::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAts_Wzd_TemplateUnits *p = (CAts_Wzd_TemplateUnits*)pObj;

	return TRUE;
}

BOOL CAts_Wzd_TemplateUnits::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAts_Wzd_TemplateUnits *p = (CAts_Wzd_TemplateUnits*)pDest;

	return TRUE;
}

CBaseObject* CAts_Wzd_TemplateUnits::Clone()
{
	CAts_Wzd_TemplateUnits *p = new CAts_Wzd_TemplateUnits();
	Copy(p);
	return p;
}

CBaseObject* CAts_Wzd_TemplateUnits::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CAts_Wzd_TemplateUnits *p = new CAts_Wzd_TemplateUnits();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CAts_Wzd_TemplateUnits::CanPaste(UINT nClassID)
{
	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAts_Wzd_TemplateUnits::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsGbWizrdXmlRWKeys *pXmlKeys = (CAtsGbWizrdXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAts_Wzd_TemplateUnitKey)
	{
		pNew = new CAts_Wzd_TemplateUnit();
	}

	return pNew;
}

CExBaseObject* CAts_Wzd_TemplateUnits::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT)
	{
		pNew = new CAts_Wzd_TemplateUnit();
	}

	return pNew;
}
CExBaseObject* CAts_Wzd_TemplateUnits::DB_CreateNewChild()
{
	CExBaseObject *pNew  = NULL;

	pNew = new CAts_Wzd_TemplateUnit();

	return pNew;
}

long CAts_Wzd_TemplateUnits::GetSelectedCount()
{
	long nCount = 0;
	POS pos = GetHeadPosition();
	CAts_Wzd_TemplateUnit *pTempUnit = NULL;

	while (pos != NULL)
	{
		pTempUnit = (CAts_Wzd_TemplateUnit *)GetNext(pos);

		if (pTempUnit->m_nSelect)
		{
			nCount++;
		}
	}

	return nCount;
}

void CAts_Wzd_TemplateUnits::SetSelected(long nSelect)
{
	POS pos = GetHeadPosition();
	CAts_Wzd_TemplateUnit *pTempUnit = NULL;

	while (pos != NULL)
	{
		pTempUnit = (CAts_Wzd_TemplateUnit *)GetNext(pos);
		pTempUnit->m_nSelect = nSelect;
	}
}