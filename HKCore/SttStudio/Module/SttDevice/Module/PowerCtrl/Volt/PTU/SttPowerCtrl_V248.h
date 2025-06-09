#ifndef CSTTPOWERCTRLV248_H
#define CSTTPOWERCTRLV248_H
#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV248:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV248();
	~CSttPowerCtrlV248();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
};
#endif // CSTTPOWERCTRLV248_H
