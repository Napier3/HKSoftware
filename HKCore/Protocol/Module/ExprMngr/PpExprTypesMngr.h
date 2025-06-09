//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpExprTypesMngr.h  CPpExprTypesMngr

#pragma once

#include "ExprMngrGlobal.h"


#include "PpExprRcvTypes.h"
#include "PpExprSendTypes.h"

class CPpExprTypesMngr : public CExBaseList
{
public:
	CPpExprTypesMngr();
	virtual ~CPpExprTypesMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return EXPCLASSID_CPPEXPRTYPESMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CExprMngrXmlRWKeys::CPpExprTypesMngrKey();     }
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
	CPpExprRcvTypes *m_pExprRcvTypes;
	CPpExprSendTypes *m_pExprSendTypes;

	CString GetExprMngrFile();

//˽�г�Ա�������ʷ���
public:
	void ReadExpressionXmlFile();
	void WriteExpressionXmlFile();

	CPpExprRcvTypes* GetExprRcvTypes()	{	return m_pExprRcvTypes;	}
	CPpExprSendTypes* GetExprSendTypes()	{	return m_pExprSendTypes;	}
};

