//SmartTestHostApi.h

#ifndef _SmartTestXvm_h__
#define _SmartTestXvm_h__

#include "../../../../Module/XVM/TVMSingle.h"

class CSmartTestXvm : public CTScriptSingleVM
{
public:
	CSmartTestXvm();
	virtual ~CSmartTestXvm();

public:
	virtual void RegisterHostAPIFuncs();
	
};

#endif