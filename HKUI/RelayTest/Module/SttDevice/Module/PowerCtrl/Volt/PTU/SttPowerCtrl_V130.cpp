#include "stdafx.h"
#include "SttPowerCtrl_V130.h"

CSttPowerCtrlV130::CSttPowerCtrlV130()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=130;
	m_fMaxVal2=130;
}

float CSttPowerCtrlV130::GetVoltDA(float fVout)
{
	if(fVout<63)
		fVout = 63;//模块典型值

	if(fVout>130)
		fVout = 130;

	return (fVout*1.414-89)/32.0;
}

float CSttPowerCtrlV130::GetVoltDA_DC_300V(float fVout)
{
	if((fVout<140)||(fVout>300))
		fVout = 220;//模块典型值

	return (fVout-140)/49;
}
