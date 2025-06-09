#pragma once

#include "XrioCfgMngrGlobal.h"

// CXrioScript
class CXrioScript: public CExBaseList
{
public:
	CXrioScript();
	virtual ~CXrioScript();
    CString m_strCDATA;
	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_Script;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::ScriptKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);
public:
	BOOL ReadXRIOFileCustom(const CString& strXRIOFilePath,const long &nXmlRWType = _PUGI_XML_TYPE_);
	BOOL WriteXRIOFileCustom(const CString& strXRIOFilePat);
};


 
