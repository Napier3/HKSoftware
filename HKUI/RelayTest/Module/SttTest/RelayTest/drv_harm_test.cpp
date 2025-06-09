#include "stdafx.h"
#include "drv_harm_test.h"
#include"math.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include "drv_manugradient_def.h"

void tmt_to_drv_harm(tmt_HarmTest *pTmt , drv_manu_test *pDrv, drv_manu_bi *pDrvBin)
{
	tmt_to_drv_manual_digital(pDrv, pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR, false,31);

	tmt_to_drv_manual_analog(pDrv,pTmt->m_oHarmParas.m_uiVOL,pTmt->m_oHarmParas.m_uiCUR,pTmt->m_oHarmParas.m_binOut,false,31);

	//bi
	pDrvBin->nmdelay = 0;//?
	pDrvBin->nbiRef = 0;
	pDrvBin->nisSend0 = 0;//?
	pDrvBin->nisStop = 0;
	if (pTmt->m_oHarmParas.m_nBinLogic)
	{
		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			pDrvBin->nbiAndValid |= ((pTmt->m_oHarmParas.m_binIn[i].nSelect?1:0) << i);
		}
	}
	else
	{
		for (int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			pDrvBin->nbiOrValid |= ((pTmt->m_oHarmParas.m_binIn[i].nSelect?1:0)<<i);
		}
	}

	if(pTmt->m_oHarmParas.m_bLock)
	{
		pDrvBin->nisStop = 1;
		pTmt->m_oHarmParas.m_bLock = false;
		//        pTmt->m_oManuParas.m_brelayTest = true;
	}
}

void tmt_to_drv_Harm_Gradient(drv_gradient_test *pDrvGradient, tmt_HarmTest *pTmt, tmt_GradientProcess *pGradientProcess)//自动
{
	pDrvGradient->nalgCount = 2;//模拟模块数量待定,ke yi huo qu
	pDrvGradient->ndigCount = 1;//数字模块数量待定
	pDrvGradient->ngradientCount = pGradientProcess->m_nStepCount;
	pDrvGradient->nisReturn = pTmt->m_oHarmParas.m_oHarmGradient.nMode;//返回值
	pDrvGradient->ndiLogic = pTmt->m_oHarmParas.m_nBinLogic;
	pDrvGradient->ndiValid = 0;
	pDrvGradient->ndiRef = pTmt->m_oHarmParas.m_binIn[0].nTrigMode;
	pDrvGradient->ntimeDiv = pTmt->m_oHarmParas.m_oHarmGradient.fStepTime*1000;
	pDrvGradient->ntimeBfChg = 0;
	pDrvGradient->ntimeBfFault = 0;
	pDrvGradient->nDIBfFault = 0;
	pDrvGradient->nDIFault = 0;
	pDrvGradient->nDIFaultFlipnSec = 0;
	pDrvGradient->nDIFaultFlipSec = 0;

	for (int i=0; i<MAX_BINARYIN_COUNT; i++)
	{
		pDrvGradient->ndiValid |= ((pTmt->m_oHarmParas.m_binIn[i].nSelect?1:0)<<i);
	}

	tmt_to_drv_Gradient_alg(pDrvGradient, pGradientProcess,
							pTmt->m_oHarmParas.m_nGradientTpSelect,pTmt->m_oHarmParas.m_oHarmGradient.nHarmIndex);
	tmt_to_drv_Gradient_dig(pDrvGradient,pGradientProcess,
							pTmt->m_oHarmParas.m_nGradientTpSelect, false,pTmt->m_oHarmParas.m_oHarmGradient.nHarmIndex);
}

void tmt_to_drv(tmt_HarmTest *pTmt , tmt_GradientProcess *pGradientProcess, drv_manu_gradient_test *pDrv)
{
	tmt_to_drv_harm(pTmt, &pDrv->m_oManuStruct, &pDrv->m_oManuBinStruct);

	if(pTmt->m_oHarmParas.m_bAuto)
	{
		tmt_to_drv_Harm_Gradient(&pDrv->m_oGradientStruct, pTmt, pGradientProcess);
	}
}





