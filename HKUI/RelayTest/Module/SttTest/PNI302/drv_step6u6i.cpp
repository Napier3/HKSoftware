#include "stdafx.h"
#include "drv_step6u6i.h"
#include"../../SttDevice/SttDeviceBase.h"


void tmt_to_drv(tmt_HarmTest *pTmt , Drv_ManuData *pDrv)
{
	memset(pDrv,0,sizeof(Drv_ManuData));

	float fVsum=0;
	float fIsum=0;
	float fIMax=0;

	//zhoulei 20201028

//	tmt_channel *pUData=pTmt->m_oHarmParas.m_uiVOL;
//	for(int k=0; k<6; k++)
//	{
//		CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCVolToDrv(pUData[k].Harm[0].fAmp, k ,pDrv->oharm[0].dat);

//		for(int m=0;m<31;m++)
//		{
//			CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(pUData[k].Harm[m+1].fAmp,
//					pUData[k].Harm[m+1].fAngle,
//					pUData[k].Harm[m+1].fFreq, k,
//					pDrv->oharm[0].dat+m*3*6);

//			if(fVsum <= fabs(pUData[k].Harm[m+1].fAmp))
//				fVsum = fabs(pUData[k].Harm[m+1].fAmp);
//		}
//	}
//	pDrv->oharm[0].nDWcnt =31*6*3+6;

//	tmt_channel *pIData=pTmt->m_oHarmParas.m_uiCUR;
//	for(int k=0; k<6; k++)
//	{
//		CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCCurToDrv(pIData[k].Harm[0].fAmp, k ,pDrv->oharm[1].dat);

//		for(int m=0;m<31;m++)
//		{
//			CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(pIData[k].Harm[m+1].fAmp,
//					pIData[k].Harm[m+1].fAngle,
//					pIData[k].Harm[m+1].fFreq, k,
//					pDrv->oharm[1].dat+m*3*6);
//			fIsum += fabs(pIData[k].Harm[m+1].fAmp);
//			if(fIMax <= fabs(pIData[k].Harm[m+1].fAmp))
//				fIMax = fabs(pIData[k].Harm[m+1].fAmp);
//		}
//	}
//	pDrv->oharm[1].nDWcnt =31*6*3+6;


//	CSttDeviceBase::g_pSttDeviceBase->SetCurrentPowerMode(Low);

//	CSttDeviceBase::g_pSttDeviceBase->setCurrentDASetting(fVsum,VOLT);
//	CSttDeviceBase::g_pSttDeviceBase->setCurrentDASetting(fIsum,CURRENT,fIMax);
//	CSttDeviceBase::g_pSttDeviceBase->SetDeviceInnerParaSet();
}



