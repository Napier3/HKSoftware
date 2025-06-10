#include "stdafx.h"
#include "drv_step6u6i.h"
#include"../../SttDevice/RelayTest/SttDevice.h"

void tmt_to_drv(tmt_HarmTest *pTmt , structManuData *pDrv)
{
	memset(pDrv,0,sizeof(structManuData));

	tmt_channel *pUData=pTmt->m_oHarmParas.m_uiVOL;
	for(int k=0; k<6; k++)
	{
		CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCVolToDrv(pUData[k].Harm[0].fAmp, k ,pDrv->oharm[0].dat);

		for(int m=0;m<31;m++)
		{
			CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(pUData[k].Harm[m+1].fAmp,
					pUData[k].Harm[m+1].fAngle,
					pUData[k].Harm[m+1].fFreq, k,
					pDrv->oharm[0].dat+m*3*6);
		}
	}
	pDrv->oharm[0].nDWcnt =31*6*3+6;

	tmt_channel *pIData=pTmt->m_oHarmParas.m_uiCUR;
	for(int k=0; k<6; k++)
	{
		CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCCurToDrv(pIData[k].Harm[0].fAmp, k ,pDrv->oharm[1].dat);

		for(int m=0;m<31;m++)
		{
			CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(pIData[k].Harm[m+1].fAmp,
					pIData[k].Harm[m+1].fAngle,
					pIData[k].Harm[m+1].fFreq, k,
					pDrv->oharm[1].dat+m*3*6);
		}
	}
	pDrv->oharm[1].nDWcnt =31*6*3+6;
}



