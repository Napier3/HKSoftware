#pragma once
#include "../../../Module/Expression/XExprNode.h"
#include "GbItemsGenRuleDefMngrGlobal.h"

class CItemGenRsltExpr : public CXExprNode
{
public:
	CItemGenRsltExpr();
	virtual ~CItemGenRsltExpr();

//公共接口
public:

//重写父类方法
public:
	virtual UINT GetClassID()		{			return GBITEMSGENMNGRCLASSID_CITEMGENRSLTEXPR;			}
	virtual BSTR GetXmlElementKey()		{		return CGbItemsGenRuleDefMngrXmlRWKeys::g_pXmlKeys->m_strCItemRsltExprKey;			}
	virtual CBaseObject* Clone();

};

