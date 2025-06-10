#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV130C20_PI:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlV130C20_PI();
	~CSttPowerCtrlV130C20_PI();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);

    virtual void SetVoltDA_State();
	virtual void SetCurrentDA_State(int nModuleIndex);
};
