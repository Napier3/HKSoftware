

//XTFKeyBase.h  CXTFKeyBase

#pragma once

#include "TempFuncGlobal.h"

class CXTFKeyBase : public CExBaseList
{
public:
	CXTFKeyBase();
	virtual ~CXTFKeyBase();

	long m_nArray;

	//���������صĳ�Ա����  ############
protected:

	//���غ���
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXKEYBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);


//˽�г�Ա����
private:

};
