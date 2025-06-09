#pragma once

#include "VerUpdateHisSysVers.h"

class CVerUpdateHisSysMngr : public CExBaseList
{
public:
	CVerUpdateHisSysMngr();
	virtual ~CVerUpdateHisSysMngr();

	long m_nMaxEntries;

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return VERUPDATEHISCLASSID_SYSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateHisXmlRWKeys::SysMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CString GetHistoryFile();
	BOOL Open();
	BOOL Save();

	int GetSysLocalVerIdx(const CString& strSysName);
	CString GetSysLocalVer(const CString& strSysName);

	int GetSysLocalVerIdx(int nSysIdx);
	CString GetSysLocalVer(int nSysIdx);
};


