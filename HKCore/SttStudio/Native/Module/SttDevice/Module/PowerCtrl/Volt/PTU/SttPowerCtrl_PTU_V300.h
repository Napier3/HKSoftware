#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV300_PTU:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV300_PTU(BOOL bHas440V);
	~CSttPowerCtrlV300_PTU();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
};
