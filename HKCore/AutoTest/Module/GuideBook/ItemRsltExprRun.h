#pragma once

#include "GuideBookDefine.h"
#include "DataSet.h"
#include "../../../Module/Expression/XExprNode.h"
class CDevice;

class CItemRsltExprRun : public CXExprNode
{
public:
	CItemRsltExprRun();
	virtual ~CItemRsltExprRun();

//公共接口
public:

//重写父类方法
public:
	virtual UINT GetClassID()		{			return GBCLASSID_ITEMRSLTEXPRRUN;			}
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strCItemRsltExprRunKey;			}
	virtual CBaseObject* Clone();

	BOOL CanRun();
	long RunRsltExprScript(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	void InitByRsltExprGen(CXExprNode *pExpr);
	void InitOwnByRsltExprGen(CXExprNode *pExpr);
};

