#include "stdafx.h"
#include "SttPowerCtrl_V270.h"

CSttPowerCtrlV270::CSttPowerCtrlV270()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=270;
	m_fMaxVal2=270;
}

void CSttPowerCtrlV270::SetVoltDA(float fVout, BOOL bIsDc)
{
    if(bIsDc)
    {
        if(fVout<84.866)
            fVout = 94.06;//模块典型值
    }
    else
    {
        if(fVout<120)
            fVout = 94.06;//模块典型值
    }

	if(fVout>300)
		fVout=300;

    float fDAValue = (fVout*1.414-133)/108;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}
