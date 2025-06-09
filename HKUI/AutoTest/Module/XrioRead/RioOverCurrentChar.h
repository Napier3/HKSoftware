#pragma once

#include "XrioCfgMngrGlobal.h"
#include "RioOverCurrentCharA.h"
#include "RioOverCurrentCharB.h"
#include "RioOverCurrentCharP.h"
#include "RioOverCurrentCharQ.h"
#include "RioOverCurrentCharK1.h"
#include "RioOverCurrentCharK2.h"






// COverCurrentChar
class CRioOverCurrentChar: public CExBaseList
{
public:
    CRioOverCurrentChar();
    virtual ~CRioOverCurrentChar();
        CString m_strType;
        CString m_strBlockType;
        CString m_strEnabled;
	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_OVERCURRENT_CHAR;   }
    virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::OverCurrentCharKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
public:
	BOOL ReadXRIOFileRio(const CString& strXRIOFilePath,const long &nXmlRWType = _PUGI_XML_TYPE_);
	BOOL WriteXRIOFileRio(const CString& strXRIOFilePat);
};



