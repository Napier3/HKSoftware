//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//PpExpr.h  CPpExpr

#pragma once

#include "ExprMngrGlobal.h"



class CPpExpr : public CExBaseObject
{
public:
	CPpExpr();
	virtual ~CPpExpr();

	CString m_strValue;

//重载函数
public:
	virtual UINT GetClassID() {    return EXPCLASSID_CPPEXPR;   }
	virtual BSTR GetXmlElementKey()  {      return CExprMngrXmlRWKeys::CPpExprKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

