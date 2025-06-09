#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV300_PN:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV300_PN();
	~CSttPowerCtrlV300_PN();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
	virtual void SetVoltDA_DC_300V(float fVout);
};
