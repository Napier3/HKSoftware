#include "stdafx.h"
#include "drv_manu_test.h"
#include"math.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include "drv_manugradient_def.h"

void tmt_to_drv_manual(tmt_ManualTest *pTmt , drv_manu_test *pDrv, drv_manu_bi *pDrvBin)
{
    tmt_to_drv_manual_digital(pDrv, pTmt->m_oManuParas.m_uiVOL,
                              pTmt->m_oManuParas.m_uiCUR, pTmt->m_oManuParas.m_bDC);
    tmt_to_drv_manual_analog(pDrv, pTmt->m_oManuParas.m_uiVOL,
                             pTmt->m_oManuParas.m_uiCUR, pTmt->m_oManuParas.m_binOut, pTmt->m_oManuParas.m_bDC);

    //bi
    pDrvBin->nmdelay = 0;//?
    pDrvBin->nbiRef = 0;
    pDrvBin->nisSend0 = 0;//?
    pDrvBin->nisStop = 0;
    if (pTmt->m_oManuParas.m_nBinLogic)
    {
        for (int i=0; i<MAX_BINARYIN_COUNT; i++)
        {
            pDrvBin->nbiAndValid |= ((pTmt->m_oManuParas.m_binIn[i].nSelect?1:0) << i);
        }
    }
    else
    {
        for (int i=0; i<MAX_BINARYIN_COUNT; i++)
        {
            pDrvBin->nbiOrValid |= ((pTmt->m_oManuParas.m_binIn[i].nSelect?1:0)<<i);
        }
    }

    if(pTmt->m_oManuParas.m_bLockChanged)
    {
         pDrvBin->nisStop = 1;
         pTmt->m_oManuParas.m_bLockChanged = false;
 //        pTmt->m_oManuParas.m_brelayTest = true;
    }    
}

void tmt_to_drv_Manu_Gradient(drv_gradient_test *pDrvGradient, tmt_ManualTest *pTmt, tmt_GradientProcess *pGradientProcess)//自动
{   
	pDrvGradient->nalgCount = 2;//模拟模块数量待定,ke yi huo qu
	pDrvGradient->ndigCount = 1;//数字模块数量待定
    pDrvGradient->ngradientCount = pGradientProcess->m_nStepCount;
    pDrvGradient->nisReturn = pTmt->m_oManuParas.m_manuGradient.nMode;//返回值
    pDrvGradient->ndiLogic = pTmt->m_oManuParas.m_nBinLogic;
    pDrvGradient->ndiValid = 0;
    pDrvGradient->ndiRef = pTmt->m_oManuParas.m_binIn[0].nTrigMode;
	pDrvGradient->ntimeDiv = pTmt->m_oManuParas.m_manuGradient.fStepTime*1000;
    pDrvGradient->ntimeBfChg = 0;
    pDrvGradient->ntimeBfFault = 0;
    pDrvGradient->nDIBfFault = 0;
    pDrvGradient->nDIFault = 0;
    pDrvGradient->nDIFaultFlipnSec = 0;
    pDrvGradient->nDIFaultFlipSec = 0;

    for (int i=0; i<MAX_BINARYIN_COUNT; i++)
    {
        pDrvGradient->ndiValid |= ((pTmt->m_oManuParas.m_binIn[i].nSelect?1:0)<<i);
    }
    tmt_to_drv_Gradient_alg(pDrvGradient, pGradientProcess, pTmt->m_oManuParas.m_nGradientTpSelect);
    tmt_to_drv_Gradient_dig(pDrvGradient, pGradientProcess, pTmt->m_oManuParas.m_nGradientTpSelect, pTmt->m_oManuParas.m_bDC);
}

void tmt_to_drv(tmt_ManualTest *pTmt , tmt_GradientProcess *pGradientProcess, drv_manu_gradient_test *pDrv)
{
	tmt_to_drv_manual(pTmt, &pDrv->m_oManuStruct, &pDrv->m_oManuBinStruct);

    if(pTmt->m_oManuParas.m_bAuto)
    {
        tmt_to_drv_Manu_Gradient(&pDrv->m_oGradientStruct, pTmt, pGradientProcess);
    }
}





