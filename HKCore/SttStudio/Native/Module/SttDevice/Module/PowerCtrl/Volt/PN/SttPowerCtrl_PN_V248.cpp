#include "stdafx.h"
#include "SttPowerCtrl_PN_V248.h"

CSttPowerCtrlV248_PN::CSttPowerCtrlV248_PN()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=248;
	m_fMaxVal2=248;
}

void CSttPowerCtrlV248_PN::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

	if(fVout<120)
		fVout = 115;//Ä£¿éµäÐÍÖµ

	if(fVout>230)
		fVout=230;

	float fDAValue = (fVout*1.414+20)/162;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlV248_PN::SetVoltDA_State()
{
    SetVoltDA(248,FALSE);
}
