#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV248_PN:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV248_PN();
	~CSttPowerCtrlV248_PN();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
