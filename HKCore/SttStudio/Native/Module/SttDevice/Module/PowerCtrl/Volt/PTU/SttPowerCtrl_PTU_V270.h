#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV270_PTU:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270_PTU(BOOL bHas440V);
	~CSttPowerCtrlV270_PTU();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
};
