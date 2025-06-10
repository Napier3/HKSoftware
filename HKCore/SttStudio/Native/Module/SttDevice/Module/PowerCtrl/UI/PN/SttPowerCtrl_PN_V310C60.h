#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlV310C60_PN: public CSttPowerCtrlBase
{
public:
    CSttPowerCtrlV310C60_PN();
    ~CSttPowerCtrlV310C60_PN();

public:
    virtual void SetVoltDA(float fVout, BOOL bIsDc);
    virtual void SetCurrentDA(float fIoutSum, float fIoutMax, int nModuleIndex, BOOL bIsDc = FALSE);

    virtual void SetVoltDA_State();
    virtual void SetCurrentDA_State(int nModuleIndex);
};
