#include "stdafx.h"
#include "SttPowerCtrl_PTU_V300.h"

CSttPowerCtrlV300_PTU::CSttPowerCtrlV300_PTU(BOOL bHas440V)
{	
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=300;
	m_fMaxVal2=300;

	if(bHas440V)
	{		
		m_bVolt_440V=TRUE;
		m_fMaxVal=300;
		m_fMaxVal2=440;
	}
}

void CSttPowerCtrlV300_PTU::SetVoltDA(float fVout, BOOL bIsDc)
{	
	if(fVout<120)
		fVout = 116;//Ä£¿éµäÐÍÖµ

	if(fVout>300)
		fVout=300;

	float fDAValue = (fVout*1.414-163)/82;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}
