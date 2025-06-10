#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV270_PI:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270_PI();
	~CSttPowerCtrlV270_PI();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
