#include "stdafx.h"
#include "SttPowerCtrl_PN_V270.h"

CSttPowerCtrlV270_PN::CSttPowerCtrlV270_PN()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=270;
	m_fMaxVal2=270;
}

void CSttPowerCtrlV270_PN::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(bIsDc)
		fVout = fVout /1.414;

	if(fVout<100)
		fVout = 100;//Ä£¿éµäÐÍÖµ

	if(fVout>300)
		fVout=300;

	float fDAValue = (fVout*1.414-133)/108;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlV270_PN::SetVoltDA_State()
{
    SetVoltDA(300,FALSE);
}
