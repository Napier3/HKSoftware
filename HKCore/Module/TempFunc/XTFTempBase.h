

//XTFTempBase.h  CXTFTempBase

#pragma once

#include "TempFuncGlobal.h"

class CXTFTempBase : public CExBaseList
{
public:
	CXTFTempBase();
	virtual ~CXTFTempBase();

protected:

	//���غ���
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXTEMPBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsTemp();     }
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
