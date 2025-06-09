#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV300_PI:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV300_PI();
	~CSttPowerCtrlV300_PI();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
