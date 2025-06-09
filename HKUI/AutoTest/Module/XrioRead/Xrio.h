#pragma once

#include "XrioCfgMngrGlobal.h"

#include "XrioCustom.h"
#include "XrioRio.h"
#include "XrioRioConverter.h"

// CXrio
class CXrio: public CExBaseList
{
public:
	CXrio();
	virtual ~CXrio();
	//重载函数
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_XRIO;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::XrioKey();     }
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

	CXrioCustom* GetXrioCustom();
    CXrioRio* GetXrioRio();
    CXrioRioConverter* GetXrioRioConverter();
public:
	BOOL ReadXRIOFile(const CString& strXRIOFilePath);
    BOOL WriteXRIOFile(const CString& strXRIOFilePath);
};
 