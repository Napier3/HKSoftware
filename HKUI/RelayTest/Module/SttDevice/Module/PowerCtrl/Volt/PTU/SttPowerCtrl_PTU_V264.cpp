#include "stdafx.h"
#include "SttPowerCtrl_PTU_V264.h"

CSttPowerCtrlV264_PTU::CSttPowerCtrlV264_PTU(BOOL bHas440V)
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

float CSttPowerCtrlV264_PTU::GetVoltDA(float fVout)
{
	if(fVout<150)
		fVout=150;

	if(fVout>264)
		fVout=264;

	return (fVout*1.414-208)/80;
}
