#pragma once

#include "XrioCfgMngrGlobal.h"
#include "XrioListCfg.h"

// CRioVMaxLL
class CRioVMaxLL : public CExBaseList
{
public:
	CRioVMaxLL();
	virtual ~CRioVMaxLL();

	CString m_strValue;
	CString m_strType;


	//���غ���
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_VMAX_LL;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::VMaxLLKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitAfterRead();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InsertOwnTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

	BOOL GetParameterFullPath(CString &strValue);
	BOOL GetParameterValue(CString &strValue);
};

