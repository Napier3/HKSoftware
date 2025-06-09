#include "stdafx.h"
#include "ItemRsltExprRun.h"
#include "Device.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemRsltExprRun::CItemRsltExprRun()
{

}


CItemRsltExprRun::~CItemRsltExprRun()
{
	
}

CBaseObject* CItemRsltExprRun::Clone()
{
	CItemRsltExprRun* pNew = new CItemRsltExprRun();
	Copy(pNew);

	return pNew;
}

BOOL CItemRsltExprRun::CanRun()
{
	return (GetCount() > 0);
}

//shaolei  2023-7-3 新增两个形参：
//nCurrTestTimes：当前的测试测次；
//nRepeatTimes：重复测试次数
long CItemRsltExprRun::RunRsltExprScript(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)
{
	return CXExprNode::CalcEx(pExprParent, pCalInterface, nCurrTestTimes, nRepeatTimes);
}

// long CItemRsltExprRun::RunRsltExprScript(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
// {
// 	return Calc(pExprParent, pCalInterface);
// }

void CItemRsltExprRun::InitByRsltExprGen(CXExprNode *pExpr)
{
	if (pExpr == NULL)
	{
		return;
	}

	m_strID = pExpr->m_strID;
	m_strName = pExpr->m_strName;
	m_strLogic = pExpr->m_strLogic;

	AppendCloneEx2(*pExpr, TRUE, TRUE);
}

void CItemRsltExprRun::InitOwnByRsltExprGen(CXExprNode *pExpr)
{
	if (pExpr == NULL)
	{
		return;
	}

	m_strID = pExpr->m_strID;
	m_strName = pExpr->m_strName;
	m_strLogic = pExpr->m_strLogic;
	m_nCntRslt = pExpr->m_nCntRslt;
}