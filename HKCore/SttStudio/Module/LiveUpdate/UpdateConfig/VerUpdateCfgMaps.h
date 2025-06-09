#pragma once

#include "VerUpdateCfgMap.h"

class CVerUpdateCfgMaps : public CExBaseList
{
public:
	CVerUpdateCfgMaps();
	virtual ~CVerUpdateCfgMaps();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return VERUPDATECFGCLASSID_MAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateCfgXmlRWKeys::MapsKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CVerUpdateCfgMap* AddMap(const CString& strShellPath,int nIdxSys);

	CVerUpdateCfgMap* FindByShellPath(const CString& strShellPath);
	void DeleteByShellPath(const CString& strShellPath);
};


