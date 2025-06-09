#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV264_PTU:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV264_PTU(BOOL bHas440V);
	~CSttPowerCtrlV264_PTU();

public:
	//Volt
	virtual float GetVoltDA(float fVout);
};
