#include "stdafx.h"
#include "SttPowerCtrl_PTU_V270.h"

CSttPowerCtrlV270_PTU::CSttPowerCtrlV270_PTU(BOOL bHas440V)
{	
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=264;
	m_fMaxVal2=264;

	if(bHas440V)
	{
		m_bVolt_440V=TRUE;
		m_fMaxVal2=380;
	}
}

void CSttPowerCtrlV270_PTU::SetVoltDA(float fVout, BOOL bIsDc)
{
	if(fVout<150)
		fVout=150;

	if(fVout>264)
		fVout=264;

	float fDAValue = (fVout*1.414-208)/80;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}
