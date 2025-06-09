#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV270:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270();
	~CSttPowerCtrlV270();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
};
