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

//�����ӿ�
public:

//��д���෽��
public:
	virtual UINT GetClassID()		{			return GBCLASSID_ITEMRSLTEXPRRUN;			}
	virtual BSTR GetXmlElementKey()		{		return CGbXMLKeys::g_pGbXMLKeys->m_strCItemRsltExprRunKey;			}
	virtual CBaseObject* Clone();

	BOOL CanRun();
	long RunRsltExprScript(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	void InitByRsltExprGen(CXExprNode *pExpr);
	void InitOwnByRsltExprGen(CXExprNode *pExpr);
};

