//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpExpr.h  CPpExpr

#pragma once

#include "ExprMngrGlobal.h"



class CPpExpr : public CExBaseObject
{
public:
	CPpExpr();
	virtual ~CPpExpr();

	CString m_strValue;

//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

