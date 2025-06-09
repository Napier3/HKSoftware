#pragma once

#include "XrioCfgMngrGlobal.h"
#include "XrioListCfg.h"

// CRioManufacturer
class CRioManufacturer : public CExBaseList
{
public:
	CRioManufacturer();
	virtual ~CRioManufacturer();

	CString m_strValue;
	CString m_strValueFormula;
	CString m_strType;
	CString m_strRefParam;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_MANUFACTURER;   }
	virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::ManufacturerKey();     }
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

