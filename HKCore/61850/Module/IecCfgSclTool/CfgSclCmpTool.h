#pragma once
#include "CfgCmpToolBase.h"
#include "..\SCL\ReadSCDF.h"

class CCfgSclCmpTool : public CCfgCmpToolBase
{
public:
	CCfgSclCmpTool(void);
	~CCfgSclCmpTool(void);

	BOOL RegisterCmpData2(long nType, DWORD dwItrAddr);

private:
	void RegisterSclData(const SMVINPtr& smviptPtr);
	void RegisterSclData(const SMVOUTPtr& smvoptPtr);
	void RegisterSclData(const GOOSEINPtr& giptPtr);
	void RegisterSclData(const GOOSEOUTPtr& giptPtr);
};
