#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrl_PNS330:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrl_PNS330();
	~CSttPowerCtrl_PNS330();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
    virtual void SetVoltDA_State();
	virtual void SetCurrentDA_State(int nModuleIndex);
};
