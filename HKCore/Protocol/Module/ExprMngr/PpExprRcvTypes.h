//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpExprRcvTypes.h  CPpExprRcvTypes

#pragma once

#include "ExprMngrGlobal.h"


#include "PpExprType.h"

class CPpExprRcvTypes : public CExBaseList
{
public:
	CPpExprRcvTypes();
	virtual ~CPpExprRcvTypes();


//���غ���
public:
	virtual UINT GetClassID() {    return EXPCLASSID_CPPEXPRRCVTYPES;   }
	virtual BSTR GetXmlElementKey()  {      return CExprMngrXmlRWKeys::CPpExprRcvTypesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

