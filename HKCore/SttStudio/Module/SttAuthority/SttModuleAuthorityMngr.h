#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

class CSttModuleAuthorityMngr : public CExBaseList
{
public:
	CSttModuleAuthorityMngr();
	virtual ~CSttModuleAuthorityMngr();

public:
	BOOL HasAuthority(const CString &strModuleID);
	void SetAuthority(const CString &strModuleID, long nValue);

};