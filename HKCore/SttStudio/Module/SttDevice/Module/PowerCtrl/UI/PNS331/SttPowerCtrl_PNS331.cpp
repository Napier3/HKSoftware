#include "stdafx.h"
#include "SttPowerCtrl_PNS331.h"
#include "../../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrl_PNS331::CSttPowerCtrl_PNS331()
{
}

void CSttPowerCtrl_PNS331::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

    if(fVout < 60)
    {
        fVout = 60;    //Ä£¿éµäÐÍÖµ
    }

    if(fVout > 270)
    {
        fVout = 270;
    }

    float fDa = (fVout * 1.414 - 0.4374 * fVout + 118.04 - 74.1) / 43.58;
    fDa = fDa / 2 * 1.009;
    unsigned char nByte;

    if(fDa > 3.55999)
    {
        nByte = 255;
    }
    else
    {
        nByte = fDa / 3.56 * 255;
    }

    m_nDA = nByte << (2 * 8);
}

void CSttPowerCtrl_PNS331::SetCurrentDA(float fIoutSum, float fIoutMax, int nModuleIndex, BOOL bIsDc)
{
    float fDAValue = 0;
    float fVset = 0;
    int nPowerMode = STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode_UI(nModuleIndex, nPowerMode, fVset);

    switch(nPowerMode)
    {
        case STT_CurrentMODULE_POWER_LOW:
            fDAValue = 0;
            break;

        case STT_CurrentMODULE_POWER_MIDDLE:
        {
            fDAValue = 3.5;
        }
        break;

        case STT_CurrentMODULE_POWER_HIGH:
        {
            fDAValue = 6.5;
        }
        break;

        case STT_CurrentMODULE_POWER_OTHER:
        {
            if(fVset > 0 && fVset < 3.3)
            {
            }
            else
            {
                fVset = 0;
            }

            fDAValue = fVset * 3;
        }
        break;
    }

    fDAValue = fDAValue / 2;
    unsigned char nByte = fDAValue / 3.56 * 255;
	if(nByte == 0)
		nByte = 1;
    m_nDA |= nByte;
}

void CSttPowerCtrl_PNS331::SetVoltDA_State()
{
    SetVoltDA(270, FALSE);
}

void CSttPowerCtrl_PNS331::SetCurrentDA_State(int nModuleIndex)
{
    float fDAValue = 0;
    float fVset = 0;
    int nPowerMode = STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode_UI(nModuleIndex, nPowerMode, fVset);

    switch(nPowerMode)
    {
        case STT_CurrentMODULE_POWER_LOW:
            fDAValue = 0;
            break;

        case STT_CurrentMODULE_POWER_MIDDLE:
        {
            fDAValue = 3.5;
        }
        break;

        case STT_CurrentMODULE_POWER_HIGH:
        {
            fDAValue = 6.5;
        }
        break;

        case STT_CurrentMODULE_POWER_OTHER:
        {
            if(fVset > 0 && fVset < 3.3)
            {
            }
            else
            {
                fVset = 0;
            }

            fDAValue = fVset * 3;
        }
        break;
    }

    fDAValue = fDAValue / 2;
    unsigned char nByte = fDAValue / 3.56 * 255;
	if(nByte == 0)
		nByte = 1;
    m_nDA |= nByte;
}

