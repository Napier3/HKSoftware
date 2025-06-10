#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV130C20_PN:public CSttPowerCtrlBase
{
public:
    CSttPowerCtrlV130C20_PN();
    ~CSttPowerCtrlV130C20_PN();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);

    virtual void SetVoltDA_State();
	virtual void SetCurrentDA_State(int nModuleIndex);
};
