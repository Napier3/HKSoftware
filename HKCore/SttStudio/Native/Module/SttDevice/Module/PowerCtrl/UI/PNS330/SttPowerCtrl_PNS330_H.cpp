#include "stdafx.h"
#include "SttPowerCtrl_PNS330_H.h"
#include "../../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrl_PNS330_H::CSttPowerCtrl_PNS330_H()
{

}

void CSttPowerCtrl_PNS330_H::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

	float fDa = (43.04 + fVout*0.9766)/31;
	if(fDa > 9.9999)
		fDa = 9.9999;

    int nByte = fDa/10.0*32767;
    m_nDA = nByte<<(2*8);
    m_nDA = m_nDA*(-1);
}

void CSttPowerCtrl_PNS330_H::SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc)
{
    float fDAValue=0;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode_UI(nModuleIndex,nPowerMode,fVset);

	switch(nPowerMode)
	{
	case STT_CurrentMODULE_POWER_LOW:
        fDAValue=0;
		break;
	case STT_CurrentMODULE_POWER_MIDDLE:
	{
        fDAValue=3.5;
	}
		break;
	case STT_CurrentMODULE_POWER_HIGH:
	{
        fDAValue=6.5;
    }
		break;
	case STT_CurrentMODULE_POWER_OTHER:
	{
        if(fVset>0&&fVset<3.3)
		{

		}
		else
		{
            fVset=0;
		}
        fDAValue=fVset*3;
	}
		break;
	}

    unsigned int nByte = fDAValue/10.0*32767;
	if(nByte == 0)
		nByte = 1;//15秒关闭时需要一个非零的值作为判断
    m_nDA |= nByte;
}

void CSttPowerCtrl_PNS330_H::SetVoltDA_State()
{
	SetVoltDA(270,FALSE);
}

void CSttPowerCtrl_PNS330_H::SetCurrentDA_State(int nModuleIndex)
{
    float fDAValue=0;
    float fVset=0;
    int nPowerMode=STT_CurrentMODULE_POWER_LOW;
    GetCurrentPowerMode_UI(nModuleIndex,nPowerMode,fVset);

    switch(nPowerMode)
    {
    case STT_CurrentMODULE_POWER_LOW:
        fDAValue=0;
        break;
    case STT_CurrentMODULE_POWER_MIDDLE:
    {
        fDAValue=3.5;
    }
        break;
    case STT_CurrentMODULE_POWER_HIGH:
    {
		fDAValue=6.5;
    }
        break;
    case STT_CurrentMODULE_POWER_OTHER:
    {
        if(fVset>0&&fVset<3.3)
        {

        }
        else
        {
            fVset=0;
        }
        fDAValue=fVset*3;
    }
        break;
    }

    unsigned int nByte = fDAValue/10.0*32767;
	if(nByte == 0)
		nByte = 1;//15秒关闭时需要一个非零的值作为判断
    m_nDA |= nByte;
}

