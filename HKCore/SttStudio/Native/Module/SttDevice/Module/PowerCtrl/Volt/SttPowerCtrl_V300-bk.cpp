#include "stdafx.h"
#include "SttPowerCtrl_V300.h"

CSttPowerCtrlV300::CSttPowerCtrlV300(BOOL bHas440V)
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

float CSttPowerCtrlV300::GetVoltDA(float fVout)
{	
	if(fVout<120)
		fVout = 116;//模块典型值

	if(fVout>300)
		fVout=300;

	return (fVout*1.414-163)/82;
}

float CSttPowerCtrlV300::GetVoltDA_DC_300V(float fVout)
{
	if((fVout<140)||(fVout>300))
		fVout = 220;//模块典型值

	return (fVout-140)/49;
}
