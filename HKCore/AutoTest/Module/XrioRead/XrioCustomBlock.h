#pragma once

#include "XrioCfgMngrGlobal.h"
// CXrioCustomBlock

class CXrioCustomBlock : public CExBaseList
{
public:
	CXrioCustomBlock();
	virtual ~CXrioCustomBlock();

	//CString m_strBlockID;
	CString m_strEnabled;
	CString m_strDescription;
	CString m_strEnabledFormula;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_CUSTOMBLOCK;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::CustomBlockKey();     }
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
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	CExBaseObject *FindParaByName(const CString &strMap,const CString &strForeignId);
	CExBaseObject *FindParaByFullPath(const CString &strMap);
	CExBaseObject *FindOwnParaByName(const CString &strMap,const CString &strForeignId);
};


