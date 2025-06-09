#pragma once

#include "VerUpdateHisVer.h"

class CVerUpdateHisSysVers : public CExBaseList
{
public:
	CVerUpdateHisSysVers();
	virtual ~CVerUpdateHisSysVers();

	//重载函数
public:
	virtual UINT GetClassID() {    return VERUPDATEHISCLASSID_SYSVERS;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateHisXmlRWKeys::SysVersionsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

public:
	long GetMaxEntries();
	void RemoveExtraEntries();
	long GetLocalCurrVerIdx();
	CString GetLocalCurrVer();
	void AddHisVer(CVerUpdateHisVer* pHisVer);
	void AddHisVer(const CString& strDateTime,int nCurrVerIdx,int nPrevVerIdx,const CString& strCurVer,const CString& strPrevVer);
};


