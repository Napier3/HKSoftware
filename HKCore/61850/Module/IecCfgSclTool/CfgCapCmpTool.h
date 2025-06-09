#pragma once
#include "CfgCmpToolBase.h"
#include "..\61850Cap\CapDevice\StCapDevice91.h"
#include "..\61850Cap\CapDevice\StCapDevice92.h"
#include "..\61850Cap\CapDevice\StCapDeviceGoose.h"

class CCfgCapCmpTool : public CCfgCmpToolBase
{
public:
	CCfgCapCmpTool(void);
	~CCfgCapCmpTool(void);

	BOOL RegisterCmpData2(CStCapDeviceBase *pCapDevice);

private:
	void RegisterCapDeviceData(CStCapDevice91 *pCapDevice);
	void RegisterCapDeviceData(CStCapDevice92 *pCapDevice);
	void RegisterCapDeviceData(CStCapDeviceGoose *pCapDevice);
};
