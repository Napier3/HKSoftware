//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Group.cpp  CRptTemp_Group


#include "stdafx.h"
#include "RptTemp_Group.h"
#include "RptTemp_Data.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRptTemp_Group::CRptTemp_Group()
{
	//初始化属性

	//初始化成员变量
}

CRptTemp_Group::~CRptTemp_Group()
{
}

CBaseObject* CRptTemp_Group::Clone()
{
	CRptTemp_Group *p = new CRptTemp_Group();
	Copy(p);
	return p;
}

CBaseObject* CRptTemp_Group::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CRptTemp_Group *p = new CRptTemp_Group();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CRptTemp_Group::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CRPTTEMP_DATA)
	{
		return TRUE;
	}

	return CDataGroup::CanPaste(nClassID);
}

CExBaseObject* CRptTemp_Group::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroRptTemplateXmlRWKeys *pXmlKeys = (CTestMacroRptTemplateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		pNew = new CRptTemp_Data();
		return pNew;
	}

	return CDataGroup::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CRptTemp_Group::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CRPTTEMP_DATA)
	{
		pNew = new CRptTemp_Data();
		return pNew;
	}

	return CDataGroup::CreateNewChild(nClassID);
}
