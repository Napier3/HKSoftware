#pragma once

#include "XrioCfgMngrGlobal.h"
#include "RioCurvePoint.h"



// CRioCurvePoints
class CRioCurvePoints: public CExBaseList
{
public:
    CRioCurvePoints();
    virtual ~CRioCurvePoints();
        CString m_strType;
        CString m_strBlockType;
	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_CURVEPOINTS;   }
    virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::CurvePointsKey();     }
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



