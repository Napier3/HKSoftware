#pragma once

#include "XrioCfgMngrGlobal.h"
#include "RioRefPointMag.h"
#include "RioRefPointAngle.h"
#include "RioRadius.h"
#include "RioStartAngle.h"
#include "RioEndAngle.h"
#include "RioDir.h"







// CRioArc
class CRioArc: public CExBaseList
{
public:
    CRioArc();
    virtual ~CRioArc();
        CString m_strType;
        CString m_strBlockType;
 CString m_strEnabled;
	//重载函数
public:
	virtual UINT GetClassID() {    return XRIOCLASSID_ARC;   }
    virtual BSTR GetXmlElementKey()  {      return CXrioCfgMngrXmlRWKeys::ArcKey();     }
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



