#ifndef CSTTPOWERCTRLV130_H
#define CSTTPOWERCTRLV130_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlV130:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV130();
	~CSttPowerCtrlV130();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
	virtual float GetVoltDA_DC_300V(float fVout);
};
#endif // CSTTPOWERCTRLV130_H
