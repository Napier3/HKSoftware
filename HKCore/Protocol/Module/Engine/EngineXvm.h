//EngineHostApi.h

#ifndef _EngineXvm_h__
#define _EngineXvm_h__

#include "../../../Module/XVM/TVMSingle.h"

class CEngineXvm : public CTScriptSingleVM
{
public:
	CEngineXvm();
	virtual ~CEngineXvm();

public:
	virtual void RegisterHostAPIFuncs();
	
};

#endif