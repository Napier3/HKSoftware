#include "stdafx.h"
#include "SttPowerCtrl_V270.h"


CSttPowerCtrlV270::CSttPowerCtrlV270()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=270;
	m_fMaxVal2=270;
}

float CSttPowerCtrlV270::GetVoltDA(float fVout)
{
	if(fVout<120)
		fVout = 120;//模块典型值

	if(fVout>270)
		fVout=270;

	return (fVout*1.414-163)/82;
}
