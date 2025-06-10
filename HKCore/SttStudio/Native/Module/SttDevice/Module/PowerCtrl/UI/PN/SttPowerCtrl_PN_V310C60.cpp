#include "stdafx.h"
#include "SttPowerCtrl_PN_V310C60.h"
#include "../../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrlV310C60_PN::CSttPowerCtrlV310C60_PN()
{
}

void CSttPowerCtrlV310C60_PN::SetVoltDA(float fVout, BOOL bIsDc)
{
    m_nDA = 0;
}

void CSttPowerCtrlV310C60_PN::SetCurrentDA(float fIoutSum, float fIoutMax, int nModuleIndex, BOOL bIsDc)
{
}

void CSttPowerCtrlV310C60_PN::SetVoltDA_State()
{
}

void CSttPowerCtrlV310C60_PN::SetCurrentDA_State(int nModuleIndex)
{
}

