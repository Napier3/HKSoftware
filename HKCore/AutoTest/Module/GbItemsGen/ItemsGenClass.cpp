//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenClass.cpp  CItemsGenClass


#include "stdafx.h"
#include "ItemsGenClass.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenClass::CItemsGenClass()
{
	//初始化属性

	//初始化成员变量
}

CItemsGenClass::~CItemsGenClass()
{
}

BOOL CItemsGenClass::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CItemsGenBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenClass *p = (CItemsGenClass*)pObj;

	return TRUE;
}

BOOL CItemsGenClass::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenBase::CopyOwn(pDest);

	CItemsGenClass *p = (CItemsGenClass*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenClass::Clone()
{
	CItemsGenClass *p = new CItemsGenClass();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenClass::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenClass *p = new CItemsGenClass();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenClass::CanPaste(UINT nClassID)
{
	if (CItemsGenBase::CanPaste(nClassID))
	{
		return TRUE;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CPARASGENNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenClass::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CGbItemsGenRuleDefMngrXmlRWKeys *pXmlKeys = (CGbItemsGenRuleDefMngrXmlRWKeys*)pXmlRWKeys;


	pNew = CItemsGenBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	if (pNew)
	{
		return pNew;
	}

	if (strClassID == pXmlKeys->m_strCItemsGenNodeKey)
	{
		pNew = new CParasGenNode();
	}

	return pNew;
}

CExBaseObject* CItemsGenClass::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CItemsGenBase::CreateNewChild(nClassID);

	if (pNew)
	{
		return pNew;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CPARASGENNODE)
	{
		pNew = new CParasGenNode();
	}

	return pNew;
}
