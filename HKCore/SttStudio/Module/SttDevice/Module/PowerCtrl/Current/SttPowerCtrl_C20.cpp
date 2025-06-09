#include "stdafx.h"
#include "SttPowerCtrl_C20.h"
#include "../../../../SttTest/Common/tmt_system_config.h"

CSttPowerCtrlC20::CSttPowerCtrlC20()
{
	m_fMaxVal_DC=10;
	m_fMaxVal=20;
}

void CSttPowerCtrlC20::SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc)
{
	float fDAValue=0.3;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode(nModuleIndex,nPowerMode,fVset);

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
		else
		{
			if(fIoutSum>80)
			{
				if(fIoutSum<=100)
					fDAValue=1.1;
				else
					fDAValue=1;
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

			if(fIoutSum<=50)
			{

			}
			else if(fIoutSum<=60)
			{
				fDa1 = 2.8;
			}
			else if(fIoutSum<=70)
			{
				fDa1 = 2.4;
			}
			else if(fIoutSum<=80)
			{
				fDa1 = 2;
			}
			else if(fIoutSum<=90)
			{
				fDa1 = 1.7;
			}
			else if(fIoutSum<=100)
			{
				fDa1 = 1.4;
			}
			else if(fIoutSum<=110)
			{
				fDa1 = 1.2;
			}
			else
			{
				fDa1 = 1;
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
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlC20::SetCurrentDA_State(int nModuleIndex)
{
	float fDAValue=0.3;
	float fVset=0;
	int nPowerMode=STT_CurrentMODULE_POWER_LOW;
	GetCurrentPowerMode(nModuleIndex,nPowerMode,fVset);

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
	m_nDA = ((unsigned int)nByte)<<(1*8);
}
