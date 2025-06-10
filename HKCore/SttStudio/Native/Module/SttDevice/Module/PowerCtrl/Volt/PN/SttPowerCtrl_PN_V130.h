#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV130_PN:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV130_PN();
	~CSttPowerCtrlV130_PN();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
