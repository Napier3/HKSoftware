#include "stdafx.h"
#include "SttPowerCtrl_PN_V130C20.h"
#include "../../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrlV130C20_PN::CSttPowerCtrlV130C20_PN()
{

}

void CSttPowerCtrlV130C20_PN::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

    if(fVout<63)
        fVout = 63;//Ä£¿éµäÐÍÖµ

    if(fVout>130)
        fVout = 130;

    float fDAValue = (fVout*1.414-89)/32.0;
    unsigned char nByte = fDAValue/3.3*255;
    m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlV130C20_PN::SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc)
{
	bIsDc=FALSE;
	float fDAValue=0.3;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode_UI(nModuleIndex,nPowerMode,fVset);

	switch(nPowerMode)
	{
	case STT_CurrentMODULE_POWER_LOW:
		fDAValue=0.3;
		break;
	case STT_CurrentMODULE_POWER_MIDDLE:
	{
		fDAValue=1.3;
		if(bIsDc)
		{
			if(fIoutSum>30)
			{
				if(fIoutSum<=45)
					fDAValue=1;
				else
					fDAValue=0.6;
			}
		}		
	}
		break;
	case STT_CurrentMODULE_POWER_HIGH:
	{
		if(bIsDc)
		{
			fDAValue=1.3;
			if(fIoutSum>30)
			{
				if(fIoutSum<=45)
					fDAValue=1;
				else
					fDAValue=0.6;
			}
		}
		else
		{
			float fDa1 =3.3;
			float fDa2 = 0;

            if(fIoutSum > 50)
			{
				fDa1 = 2.8;
			}

			fDAValue=fDa1;
			if(fIoutMax>15)
			{
				fDa2 = 3.3-0.22*(fIoutMax-15);
			}
			else
				fDa2=3.3;

			if(fDa1>fDa2)
				fDAValue=fDa2;
		}
	}
		break;
	case STT_CurrentMODULE_POWER_OTHER:
	{
		if(fVset>=0.6&&fVset<=15.9)
		{

		}
		else
		{
			fVset=0.6;
		}
		fDAValue=fVset*1.414+20*0.1-2.8;
		fDAValue/=6.6;
	}
		break;
	}

	unsigned char nByte = fDAValue/3.3*255;
    m_nDA |= nByte;
}

void CSttPowerCtrlV130C20_PN::SetVoltDA_State()
{
    SetVoltDA(130,FALSE);
}

void CSttPowerCtrlV130C20_PN::SetCurrentDA_State(int nModuleIndex)
{
    float fDAValue=0.3;
    float fVset=0;
    int nPowerMode=STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode_UI(nModuleIndex,nPowerMode,fVset);

    switch(nPowerMode)
    {
    case STT_CurrentMODULE_POWER_LOW:
        fDAValue=0.3;
        break;
    case STT_CurrentMODULE_POWER_OTHER:
    {
        if(fVset>=0.6&&fVset<=15.9)
        {

        }
        else
        {
            fVset=0.6;
        }
        fDAValue=fVset*1.414+20*0.1-2.8;
        fDAValue/=6.6;
    }
        break;
    }

    unsigned char nByte = fDAValue/3.3*255;
    m_nDA |= nByte;
}

