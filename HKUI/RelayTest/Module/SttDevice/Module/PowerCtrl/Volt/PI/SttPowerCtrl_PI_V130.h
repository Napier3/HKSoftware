#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV130_PI:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV130_PI();
	~CSttPowerCtrlV130_PI();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
