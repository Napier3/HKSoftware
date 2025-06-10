#ifndef CSTTPOWERCTRLV264_H
#define CSTTPOWERCTRLV264_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlV264:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV264(BOOL bHas440V);
	~CSttPowerCtrlV264();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
};
#endif // CSTTPOWERCTRLV264_H
