//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenDefine.cpp  CItemsGenDefine


#include "stdafx.h"
#include "ItemsGenDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CItemsGenDefine::CItemsGenDefine()
{
	//初始化属性
	m_pCurrInst = NULL;
	//初始化成员变量
}

CItemsGenDefine::~CItemsGenDefine()
{
}

BOOL CItemsGenDefine::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CItemsGenBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CItemsGenDefine *p = (CItemsGenDefine*)pObj;

	return TRUE;
}

BOOL CItemsGenDefine::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CItemsGenBase::CopyOwn(pDest);

	CItemsGenDefine *p = (CItemsGenDefine*)pDest;

	return TRUE;
}

CBaseObject* CItemsGenDefine::Clone()
{
	CItemsGenDefine *p = new CItemsGenDefine();
	Copy(p);
	return p;
}

CBaseObject* CItemsGenDefine::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CItemsGenDefine *p = new CItemsGenDefine();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CItemsGenDefine::CanPaste(UINT nClassID)
{
	if (CItemsGenBase::CanPaste(nClassID))
	{
		return TRUE;
	}
	
	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CItemsGenDefine::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
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
		pNew = new CItemsGenNode();
	}

	return pNew;
}

CExBaseObject* CItemsGenDefine::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CItemsGenBase::CreateNewChild(nClassID);

	if (pNew)
	{
		return pNew;
	}

	if (nClassID == GBITEMSGENMNGRCLASSID_CITEMSGENNODE)
	{
		pNew = new CItemsGenNode();
	}

	return pNew;
}

CItemsGenInst* CItemsGenDefine::GetCurrentInst()
{
	return m_pCurrInst;
}

void CItemsGenDefine::SetCurrentInst(CItemsGenInst* pInst)
{
	m_pCurrInst = pInst;
}