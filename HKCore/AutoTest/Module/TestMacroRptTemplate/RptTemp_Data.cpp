//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Data.cpp  CRptTemp_Data


#include "stdafx.h"
#include "RptTemp_Data.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Data::CRptTemp_Data()
{
	//初始化属性
	m_pEnable = NULL;

	//初始化成员变量
}

CRptTemp_Data::~CRptTemp_Data()
{
}

void CRptTemp_Data::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
		{
			m_pEnable = (CRptTemp_Enable*)p;
		}
	}
}

CBaseObject* CRptTemp_Data::Clone()
{
	CRptTemp_Data *p = new CRptTemp_Data();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Data::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Data *p = new CRptTemp_Data();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Data::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		return TRUE;
	}

	return CDvmData::CanPaste(nClassID);
}

CExBaseObject* CRptTemp_Data::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCRptTemp_EnableKey)
	{
		pNew = new CRptTemp_Enable();
		return pNew;
	}

	return CDvmData::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CRptTemp_Data::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_ENABLE)
	{
		pNew = new CRptTemp_Enable();
		return pNew;
	}

	return CDvmData::CreateNewChild(nClassID);
}

void CRptTemp_Data::SetEnable(CRptTemp_Enable *pEnable)
{
	if (m_pEnable != NULL)
	{
		DeleteEnable();
	}

	if (pEnable == NULL)
	{
		return;
	}

	m_pEnable = pEnable;
	AddNewChild(pEnable);
}

BOOL CRptTemp_Data::IsEnable(CExBaseList *pParas)
{
	if (m_pEnable == NULL)
	{
		//默认使能为1
		return TRUE;
	}

	return m_pEnable->IsEnable(pParas);
}

void CRptTemp_Data::DeleteEnable()
{
	if (m_pEnable != NULL)
	{
		Delete(m_pEnable);
		m_pEnable = NULL;
	}
}