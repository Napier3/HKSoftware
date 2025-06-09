#ifndef CSTTPOWERCTRLV300_H
#define CSTTPOWERCTRLV300_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlV300:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV300(BOOL bHas440V);
	~CSttPowerCtrlV300();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
	virtual float GetVoltDA_DC_300V(float fVout);
};
#endif // CSTTPOWERCTRLV300_H
