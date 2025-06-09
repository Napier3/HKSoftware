#include "stdafx.h"
#include "SttPowerCtrl_PN_V130.h"

CSttPowerCtrlV130_PN::CSttPowerCtrlV130_PN()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=130;
	m_fMaxVal2=130;
}

void CSttPowerCtrlV130_PN::SetVoltDA(float fVout, BOOL bIsDc)
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

void CSttPowerCtrlV130_PN::SetVoltDA_State()
{
    SetVoltDA(130,FALSE);
}
