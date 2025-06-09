#pragma once
#include "../PxPrcdrBase.h"

class CProcedureFactory
{
public:
	CProcedureFactory(void);
	virtual ~CProcedureFactory(void);

public:
	static CPxPrcdrBase* CreateProcedure(const CString &strPrcdrID);
};
