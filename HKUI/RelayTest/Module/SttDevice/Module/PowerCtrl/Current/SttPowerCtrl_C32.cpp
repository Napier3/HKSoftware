#include "stdafx.h"
#include "SttPowerCtrl_C32.h"
#include "../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrlC32::CSttPowerCtrlC32()
{
    m_fMaxVal_DC = 16;
    m_fMaxVal = 30;
}

void CSttPowerCtrlC32::SetCurrentDA(float fIoutSum, float fIoutMax, int nModuleIndex, BOOL bIsDc)
{
	float fDAValue = 0.7;
    float fVset = 0;
    int nPowerMode = STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode(nModuleIndex, nPowerMode, fVset);

    switch(nPowerMode)
    {
        case STT_CurrentMODULE_POWER_LOW:
			fDAValue = 0.7;
            break;
        case STT_CurrentMODULE_POWER_MIDDLE:
			fDAValue = 1.5;
			break;
        case STT_CurrentMODULE_POWER_HIGH:
        {
			fDAValue = 3.3;

            if(bIsDc)
            {
                if(fIoutSum > 32)
                {
                    if(fIoutSum <= 64)
                    {
                        fDAValue = 1.9;
                    }
                    else if(fIoutSum <= 80)
                    {
                        fDAValue = 1.2;
                    }
                    else
                    {
                        fDAValue = 1;
                    }
                }
			}
        }
        break;
        case STT_CurrentMODULE_POWER_OTHER:
        {
            if(fVset >= 0.6 && fVset <= 7.5)
            {
            }
            else
            {
                fVset = 0.6;
            }

            fDAValue = fVset * 1.414 + 32 * 0.1 - 1.1;
            fDAValue /= 3.88;
        }
        break;
    }

	unsigned char nByte = 0;
	if(fDAValue > 3.299)
	{
		nByte = 255;
	}
	else
	{
		if(fDAValue < 0)
		{
			fDAValue = 0;
		}
		nByte = fDAValue / 3.3 * 255;
	}
    m_nDA = ((unsigned int)nByte) << (1 * 8);
}

void CSttPowerCtrlC32::SetCurrentDA_State(int nModuleIndex)
{
	float fDAValue = 0.7;
    float fVset = 0;
    int nPowerMode = STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode(nModuleIndex, nPowerMode, fVset);

    switch(nPowerMode)
    {
        case STT_CurrentMODULE_POWER_LOW:
			fDAValue = 0.7;
            break;
		case STT_CurrentMODULE_POWER_MIDDLE:
			fDAValue = 1.5;
			break;
		case STT_CurrentMODULE_POWER_HIGH:
			fDAValue = 3.3;
			break;
        case STT_CurrentMODULE_POWER_OTHER:
        {
            if(fVset >= 0.6 && fVset <= 7.5)
            {
            }
            else
            {
                fVset = 0.6;
            }

            fDAValue = fVset * 1.414 + 32 * 0.1 - 1.1;
            fDAValue /= 3.88;
        }
        break;
    }

	unsigned char nByte = 0;
	if(fDAValue > 3.299)
	{
		nByte = 255;
	}
	else
	{
		if(fDAValue < 0)
		{
			fDAValue = 0;
		}
		nByte = fDAValue / 3.3 * 255;
	}
    m_nDA = ((unsigned int)nByte) << (1 * 8);
}
