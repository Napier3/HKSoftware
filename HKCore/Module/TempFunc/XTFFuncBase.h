

//XTFFuncBase.h  CXTFFuncBase

#pragma once

#include "TempFuncGlobal.h"
#include "XTFKeysBase.h"
#include "XTFTempBase.h"

class CXTFFuncBase : public CExBaseList
{
public:
	CXTFFuncBase();
	virtual ~CXTFFuncBase();


	CXTFKeysBase *m_pKeys;
	CXTFTempBase *m_pTemplate;
protected:

	//重载函数
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXFUNCBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsFunc();     }
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
	
public:
	BOOL XMatch(CXKeyMatchRefList *pXkeyMatchRefList);
	long QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate);
};
