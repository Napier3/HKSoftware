#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "ProtocolXmlRWKeys.h"

class CPpPackageText :	public CExBaseObject
{
public:
	CPpPackageText(void);
	virtual ~CPpPackageText(void);

	CString m_strText;


public:
	virtual UINT GetClassID()				{        return PPCLASSID_PPPAKAGE_TEXT;													}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextKey;		}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};



class CPpPackageTexts :	public CExBaseList
{
public:
	CPpPackageTexts(void);
	virtual ~CPpPackageTexts(void);

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPPAKAGE_TEXTS;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPackageTextsKey;     }

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
