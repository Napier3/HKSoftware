#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV270_PN:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270_PN();
	~CSttPowerCtrlV270_PN();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetVoltDA_State();
};
