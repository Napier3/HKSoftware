#include "stdafx.h"
#include "drv_gradient_test.h"
#include"math.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "drv_manugradient_def.h"
#include "../../SttDevice/RelayTest/drv_define.h"

#define CURRENTCHANNELNUMS 6

void tmt_to_drv_manu(tmt_GradientTest *pTmt ,drv_manu_test *pDrv, drv_manu_bi *pDrvBin)
{
	tmt_to_drv_manual_digital(pDrv, pTmt->m_oGradientParas.m_uiVOL[2],
			pTmt->m_oGradientParas.m_uiCUR[2]);
	tmt_to_drv_manual_analog(pDrv, pTmt->m_oGradientParas.m_uiVOL[2],
			pTmt->m_oGradientParas.m_uiCUR[2], pTmt->m_oGradientParas.m_binOut[1]);

	//bi
	pDrvBin->nmdelay = 0;//?
	pDrvBin->nbiRef = 0;
	pDrvBin->nisSend0 = 0;//?
	pDrvBin->nisStop = 0;
	if (pTmt->m_oGradientParas.m_nBinLogic)//2
	{
		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			pDrvBin->nbiAndValid |= ((pTmt->m_oGradientParas.m_binIn[i].nSelect?1:0) << i);
		}
	}
	else
	{
		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			pDrvBin->nbiOrValid |= ((pTmt->m_oGradientParas.m_binIn[i].nSelect?1:0)<<i);
		}
	}
}

void tmt_to_drv_NormalPara(drv_gradientnormal *pDrv, tmt_Channel *puData, tmt_Channel *piData)
{
	for (int i=0; i<CURRENTCHANNELNUMS; i++)
	{
		CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(puData[i].Harm[1].fAmp,
				puData[i].Harm[1].fAngle,
				puData[i].Harm[1].fFreq, i,
				pDrv->alg[0].ndat);

		CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(piData[i].Harm[1].fAmp,
				piData[i].Harm[1].fAngle,
				piData[i].Harm[1].fFreq, i,
				pDrv->alg[1].ndat);
	}

	//digital
	int nChannelA_drv_Index_Volt=0,nChannelA_drv_Index_Curr=0;
	for(int i=0; i<MAX_DIGITAL_GROUP_NUM; i++)
	{
//		bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Volt,VOLT);
//		ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Curr,CURRENT);

		nChannelA_drv_Index_Volt=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,VOLT,Ang);
		nChannelA_drv_Index_Curr=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,CURRENT,Ang);

		for(int channel=0;channel<3;channel++)//A B C
		{
			CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(puData[i*3+channel].Harm[1].fAmp,
					puData[i*3+channel].Harm[1].fAngle,
					puData[i*3+channel].Harm[1].fFreq, i ,
					&pDrv->dig[0].ndat[nChannelA_drv_Index_Volt+channel*3]);
			CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurToDrv(piData[i*3+channel].Harm[1].fAmp,
					piData[i*3+channel].Harm[1].fAngle,
					piData[i*3+channel].Harm[1].fFreq, i ,
					&pDrv->dig[0].ndat[nChannelA_drv_Index_Curr+channel*3]);
		}
	}

}

void tmt_to_drv(tmt_GradientTest *pTmt ,drv_manu_gradient_test *pDrv, tmt_GradientProcess *pGradientProcess)
{
	tmt_to_drv_manu(pTmt, &pDrv->m_oManuStruct, &pDrv->m_oManuBinStruct);//init datas
	pDrv->m_oGradientStruct.nalgCount = 2;
	pDrv->m_oGradientStruct.ndigCount = 1;//digital
	pDrv->m_oGradientStruct.ngradientCount = pGradientProcess->m_nStepCount;
	pDrv->m_oGradientStruct.nisReturn = pTmt->m_oGradientParas.m_nTestMode;//
	pDrv->m_oGradientStruct.ndiLogic = pTmt->m_oGradientParas.m_nBinLogic;
	pDrv->m_oGradientStruct.ndiValid = 0;
	pDrv->m_oGradientStruct.ndiRef = pTmt->m_oGradientParas.m_binIn[0].nTrigMode;
	pDrv->m_oGradientStruct.ntimeDiv = pTmt->m_oGradientParas.m_fStepTime*1000;
	pDrv->m_oGradientStruct.ntimeBfChg = pTmt->m_oGradientParas.m_fPrepareTime*1000;
	pDrv->m_oGradientStruct.ntimeBfFault = pTmt->m_oGradientParas.m_fPreFaultTime*1000;
	pDrv->m_oGradientStruct.nDIBfFault = 0;
	pDrv->m_oGradientStruct.nDIFault = 0;
	pDrv->m_oGradientStruct.nDIFaultFlipnSec = 0;
	pDrv->m_oGradientStruct.nDIFaultFlipSec = 0;
	for (int i=0; i<10; i++)
	{
		pDrv->m_oGradientStruct.ndiValid |= ((pTmt->m_oGradientParas.m_binIn[i].nSelect?1:0)<<i);
	}

	tmt_to_drv_NormalPara(&pDrv->m_oGradientStruct.bfChange,  pTmt->m_oGradientParas.m_uiVOL[0], pTmt->m_oGradientParas.m_uiCUR[0]);
	tmt_to_drv_NormalPara(&pDrv->m_oGradientStruct.bfFault, pTmt->m_oGradientParas.m_uiVOL[1], pTmt->m_oGradientParas.m_uiCUR[1]);

	tmt_to_drv_Gradient_alg(&pDrv->m_oGradientStruct, pGradientProcess, pTmt->m_oGradientParas.m_nType);
	tmt_to_drv_Gradient_dig(&pDrv->m_oGradientStruct, pGradientProcess, pTmt->m_oGradientParas.m_nChannel);
}



