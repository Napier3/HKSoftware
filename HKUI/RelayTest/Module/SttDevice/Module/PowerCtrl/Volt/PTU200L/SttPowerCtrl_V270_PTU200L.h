#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV270_PTU200L:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV270_PTU200L();
	~CSttPowerCtrlV270_PTU200L();

public:
	//Volt
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetVoltDA_State();
};
