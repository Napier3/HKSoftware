#pragma once

#include "../../../../Module/Expression/XExprNode.h"
#include "../SttCmdDefineGlobal.h"

class CSttItemRsltExpr : public CXExprNode
{
public:
	CSttItemRsltExpr();
	virtual ~CSttItemRsltExpr();

//�����ӿ�
public:

//��д���෽��
public:
	virtual UINT GetClassID()		{			return STTGBXMLCLASSID_CSTTITEMRSLTEXPR;			}
	virtual BSTR GetXmlElementKey()		{		return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCSttItemRsltExprKey;			}
	virtual CBaseObject* Clone();
};

