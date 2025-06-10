#include "stdafx.h"
#include "SttPowerCtrl_PI_V270.h"

CSttPowerCtrlV270_PI::CSttPowerCtrlV270_PI()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=270;
	m_fMaxVal2=270;
}

void CSttPowerCtrlV270_PI::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

	if(fVout<120)
		fVout = 120;//Ä£¿éµäÐÍÖµ

	if(fVout>270)
		fVout=270;

	float fDAValue = (fVout*1.414-163)/82;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlV270_PI::SetVoltDA_State()
{
    SetVoltDA(270,FALSE);
}
