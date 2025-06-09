

//XTFFolderBase.h  CXTFFolderBase

#pragma once

#include "TempFuncGlobal.h"
#include "XTFFuncBase.h"

class CXTFFolderBase : public CExBaseList
{
public:
	CXTFFolderBase();
	virtual ~CXTFFolderBase();

	
protected:

	//���غ���
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXFOLDERBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsFolder();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


//˽�г�Ա����
private:

public:
	long QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate);
};
