#pragma once

#include"../../../Module/BaseClass/ExBaseList.h"


//报文监视接口
class CPpPkgSpyInterface
{
public:
	CPpPkgSpyInterface();
	virtual ~CPpPkgSpyInterface();

public:
	virtual long PkgSpy(const CString &strPkgTxt, const CString &strDeviceID, const CString &strDir
		, const CString &strType, const CString &strTime, CExBaseObject *pEngineData);

};

