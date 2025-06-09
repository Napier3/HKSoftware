#include "stdafx.h"
#include "SttPowerCtrlBase.h"
#include "../../../SttTest/Common/SttSystemConfig.h"

CSttPowerCtrlBase::CSttPowerCtrlBase()
{
	m_nDA=0;
}

void CSttPowerCtrlBase::GetCurrentPowerMode(int nModuleIndex,int &nPowerMode,float &fVset)
{
	fVset=0;
	nPowerMode=STT_CurrentMODULE_POWER_LOW;
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I[nModuleIndex];
	if(pModule!=NULL)
	{
		int nModulePos=pModule->m_oModuleAttr.m_nModuleIndex;
		for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
		{
			tmt_CurModuleGear &oCurModuleGear=g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
			if(oCurModuleGear.m_nModulePos==nModulePos)
			{
				nPowerMode=oCurModuleGear.m_nIPowerMode;
				fVset=oCurModuleGear.m_fVoltSet;
				break;
			}
		}
	}
}

void CSttPowerCtrlBase::GetCurrentPowerMode_UI(int nModuleIndex,int &nPowerMode,float &fVset)
{
	fVset=0;
	nPowerMode=STT_CurrentMODULE_POWER_LOW;
	PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];
	if(pModule!=NULL)
	{
		int nModulePos=pModule->m_oModuleAttr.m_nModuleIndex;
		for(int nIndex=0;nIndex<g_theSystemConfig->m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
		{
			tmt_CurModuleGear &oCurModuleGear=g_theSystemConfig->m_oGearSetCurModules.m_oCurModuleGear[nIndex];
			if(oCurModuleGear.m_nModulePos==nModulePos)
			{
				nPowerMode=oCurModuleGear.m_nIPowerMode;
				fVset=oCurModuleGear.m_fVoltSet;
				break;
			}
		}
	}
}

void CSttPowerCtrlBase::SetVoltDA_DC_300V(float fVout)
{
	if((fVout<140)||(fVout>300))
		fVout = 220;//Ä£¿éµäÐÍÖµ

	float fDAValue = (fVout-140)/49;
	unsigned char nByte = fDAValue/3.3*255;
	m_nDA |= ((unsigned int)nByte);
}
