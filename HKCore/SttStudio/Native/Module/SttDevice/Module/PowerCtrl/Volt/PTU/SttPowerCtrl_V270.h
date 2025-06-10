#ifndef CSTTPOWERCTRLV270_H
#define CSTTPOWERCTRLV270_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlV270:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270();
	~CSttPowerCtrlV270();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
};
#endif // CSTTPOWERCTRLV270_H
