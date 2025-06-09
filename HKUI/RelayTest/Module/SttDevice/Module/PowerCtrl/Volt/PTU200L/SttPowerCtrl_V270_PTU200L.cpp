#include "stdafx.h"
#include "SttPowerCtrl_V270_PTU200L.h"

CSttPowerCtrlV270_PTU200L::CSttPowerCtrlV270_PTU200L()
{
	m_fMaxVal_DC=300;
	m_bVolt_440V=FALSE;
	m_fMaxVal=270;
	m_fMaxVal2=270;
}

void CSttPowerCtrlV270_PTU200L::SetVoltDA(float fVout, BOOL bIsDc)
{
  //   if(bIsDc)
  //   {
		// if(fVout<120)
		// 	fVout = 156;//ģ�����ֵ

		// // fDAValue = (fVout + 10)*0.01989 - 3.2962;
  //   }
  //   else
  //   {
  //       if(fVout<120)
		// 	fVout = 120;//ģ�����ֵ

		// // fDAValue = (fVout*1.414 + 14)*0.010308 - 1.88295;
  //   }

	if(fVout<120)
		fVout = 120;//ģ�����ֵ

	if(fVout>300)
		fVout = 300;

	float fDAValue = (fVout*1.414 - 133)/108;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA = ((unsigned int)nByte)<<(1*8);
}

void CSttPowerCtrlV270_PTU200L::SetVoltDA_State()
{
	SetVoltDA(270,FALSE);
}
