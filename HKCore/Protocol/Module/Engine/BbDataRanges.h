#pragma once

#include "../../../module/baseclass/exbaselist.h"
#include "ProtocolXmlRWKeys.h"

class CBbDataRanges :	public CExBaseList
{
public:
	CBbDataRanges(void);
	virtual ~CBbDataRanges(void);

public:
	virtual UINT GetClassID() {  return PPCLASSID_BBDATARANGES;    };
	virtual BSTR GetXmlElementKey()  {  return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRangesKey;   };
	
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	void SetCount(long nCount);
};
