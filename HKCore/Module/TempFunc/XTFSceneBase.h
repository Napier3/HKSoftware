

//XTFSceneBase.h  CXTFSceneBase

#pragma once

#include "TempFuncGlobal.h"
#include "XTFFolderBase.h"
#include "XTFFuncBase.h"


class CXTFSceneBase : public CXTFFolderBase
{
public:
	CXTFSceneBase();
	virtual ~CXTFSceneBase();

	
protected:

	//重载函数
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXSCENEBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsScene();     }
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
};
