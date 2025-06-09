#include "stdafx.h"
#include "SttPowerCtrl_V248.h"

CSttPowerCtrlV248::CSttPowerCtrlV248()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=248;
	m_fMaxVal2=248;
}

float CSttPowerCtrlV248::GetVoltDA(float fVout)
{
	if(fVout<120)
		fVout = 115;//模块典型值

	if(fVout>230)
		fVout=230;

	return (fVout*1.414+20)/177.42;
}
