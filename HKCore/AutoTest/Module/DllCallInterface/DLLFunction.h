//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DLLFunction.h  CDLLFunction

#pragma once

#include "DllCallGlobal.h"


#include "FuncParas.h"
#include "FuncResults.h"

class CDLLFunction : public CExBaseList
{
public:
	CDLLFunction();
	virtual ~CDLLFunction();


//���غ���
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CDLLFUNCTION;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CDLLFunctionKey();     }
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
	CFuncParas *m_pParas;
	CFuncResults *m_pResults;

//˽�г�Ա�������ʷ���
public:
	CFuncParas* GetParas();
	CFuncResults* GetResults();
	void GetParas(CString &strParas);
};

