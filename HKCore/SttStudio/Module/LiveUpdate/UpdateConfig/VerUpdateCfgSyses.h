#pragma once

#include "VerUpdateCfgSys.h"

class CVerUpdateCfgSyses : public CExBaseList
{
public:
	CVerUpdateCfgSyses();
	virtual ~CVerUpdateCfgSyses();

	//÷ÿ‘ÿ∫Ø ˝
public:
	virtual UINT GetClassID() {    return VERUPDATECFGCLASSID_SYSES;   }
	virtual BSTR GetXmlElementKey()  {      return CVerUpdateCfgXmlRWKeys::SysesKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CVerUpdateCfgSys* FindByIdxSys(int nIdxSys);
	CVerUpdateCfgSys* FindByRunPath(const CString& strRunPath);
	void DeleteInvalidCfgSys(CExBaseList& oValidList);
	void DeleteInvalidCfgSys(CVerUpdateCfgSys* pCfgSys);
};


