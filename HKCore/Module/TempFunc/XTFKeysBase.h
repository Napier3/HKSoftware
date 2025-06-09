

//XTFKeysBase.h  CXTFKeysBase

#pragma once

#include "TempFuncGlobal.h"
#include "XTFKeyBase.h"

class CXTFKeysBase : public CExBaseList
{
public:
	CXTFKeysBase();
	virtual ~CXTFKeysBase();

	
	CXKeyMatchRefList m_oXkeyMatchRefList;
protected:

	//重载函数
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXKEYSBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsKeys();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


//私有成员变量
private:

};
