#include "stdafx.h"
#include "SttPowerCtrl_C12_5_PTU200L.h"
#include "../../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrlC12_5_PTU200L::CSttPowerCtrlC12_5_PTU200L()
{
	m_fMaxVal_DC=6;
	m_fMaxVal=12.5;
}

void CSttPowerCtrlC12_5_PTU200L::SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc)
{
	float fDAValue=0.7;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode(nModuleIndex,nPowerMode,fVset);

	switch(nPowerMode)
	{
	case STT_CurrentMODULE_POWER_LOW:
		fDAValue=0.7;
		break;
	case STT_CurrentMODULE_POWER_MIDDLE:
		fDAValue=1.5;
		break;
	case STT_CurrentMODULE_POWER_HIGH:
		if(bIsDc)
            fDAValue=2.5;
		else
		{
			if(fIoutMax<10)
				fDAValue=3.3;
			else
			{
				fDAValue=3.3-0.2*(fIoutMax-10);
			}
		}
		break;
	case STT_CurrentMODULE_POWER_OTHER:
	{
		if(fVset>=0.3&&fVset<=8.5)
		{

		}
		else
		{
			fVset=0.7;
		}
		fDAValue=fVset*1.414+12.5*0.1-0.5;
		fDAValue/=3.88;
	}
		break;
	}

	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlC12_5_PTU200L::SetCurrentDA_State(int nModuleIndex)
{
	float fDAValue=0.7;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode(nModuleIndex,nPowerMode,fVset);

	switch(nPowerMode)
	{
	case STT_CurrentMODULE_POWER_LOW:
		fDAValue=0.7;
		break;
	case STT_CurrentMODULE_POWER_MIDDLE:
		fDAValue=1.5;//电流谐波实验如果低功率输出精度不够，可使用中功率
		break;
	case STT_CurrentMODULE_POWER_OTHER:
	{
		if(fVset>=0.3&&fVset<=8.5)
		{

		}
		else
		{
			fVset=0.7;
		}
		fDAValue=fVset*1.414+12.5*0.1-0.5;
		fDAValue/=3.88;
	}
		break;
	}

	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}
