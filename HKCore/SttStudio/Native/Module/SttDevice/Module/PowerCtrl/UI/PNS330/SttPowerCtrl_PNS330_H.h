#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrl_PNS330_H:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrl_PNS330_H();
	~CSttPowerCtrl_PNS330_H();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
    virtual void SetVoltDA_State();
	virtual void SetCurrentDA_State(int nModuleIndex);
};
