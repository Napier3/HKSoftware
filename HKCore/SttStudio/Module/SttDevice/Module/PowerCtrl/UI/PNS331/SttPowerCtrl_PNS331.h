#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrl_PNS331:public CSttPowerCtrlBase
{
public:
    CSttPowerCtrl_PNS331();
    ~CSttPowerCtrl_PNS331();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
    virtual void SetVoltDA_State();
	virtual void SetCurrentDA_State(int nModuleIndex);
};
