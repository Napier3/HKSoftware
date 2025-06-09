#include "drv_manugradient_def.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include "../../SttDevice/SttDeviceBase.h"

void tmt_to_drv_manual_digital(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, bool bDC,int harm)
{	
	pDrv->dig.nmoduleCount = 1;//??suiyi
	pDrv->dig.harm[0].nmodule = DIGITAL_CHANNEL_MARK;
	pDrv->dig.harm[0].nharmCnt = harm;
	int nChannelA_drv_Index_Volt,nChannelA_drv_Index_Curr,position=0;

	if(harm==31)
		position = -3*6;//NO U3U4,I3I4

	for(int i=0; i<MAX_DIGITAL_GROUP_NUM; i++)
	{
		if(bDC)
		{
			pUData[i*3+CHANNEL_A].Harm[1].fFreq = 0;
			pUData[i*3+CHANNEL_B].Harm[1].fFreq = 0;
			pUData[i*3+CHANNEL_C].Harm[1].fFreq = 0;

			pIData[i*3+CHANNEL_A].Harm[1].fFreq = 0;
			pIData[i*3+CHANNEL_B].Harm[1].fFreq = 0;
			pIData[i*3+CHANNEL_C].Harm[1].fFreq = 0;
		}

		//bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Volt,VOLT);
		//ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Curr,CURRENT);
		nChannelA_drv_Index_Volt=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,VOLT,Ang);
		nChannelA_drv_Index_Curr=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,CURRENT,Ang);

		for(int channel=0;channel<3;channel++)//A B C
		{
			for(int m=0; m<harm; m++)
			{
				CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(pUData[i*3+channel].Harm[m+1].fAmp,
						pUData[i*3+channel].Harm[m+1].fAngle,
						pUData[i*3+channel].Harm[m+1].fFreq, i ,
						&pDrv->dig.harm[0].ndat[nChannelA_drv_Index_Volt+channel*3+m*DIGITAL_CHANNEL_MAX*3]);

				CSttDeviceBase::g_pSttDeviceBase->TransDigitalCurToDrv(pIData[i*3+channel].Harm[m+1].fAmp,
						pIData[i*3+channel].Harm[m+1].fAngle,
						pIData[i*3+channel].Harm[m+1].fFreq, i ,
						&pDrv->dig.harm[0].ndat[nChannelA_drv_Index_Curr+channel*3+m*DIGITAL_CHANNEL_MAX*3+position]);
			}
		}
	}
}

void tmt_to_drv_manual_analog(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, tmt_BinaryOut *binOut, bool bDC,int harm)
{
	//手动试验
	int nAlgCurModuleCount = 1/*CSttDevice::g_pSttDevice->GetCurModuleCount()*/;
	int nAlgVolModuleCount = 1/*CSttDevice::g_pSttDevice->GetVolModuleCount()*/;
	pDrv->alg.nmdCount = nAlgCurModuleCount + nAlgVolModuleCount;//

	for (int i=0; i<8; i++)//bo
	{
		pDrv->alg.nuiDO += ((binOut[i].nState)<<i);
	}
	int j=0;

	int nChannelCount = nAlgCurModuleCount*CHANNEL_MAX;
	int nTemp = nChannelCount/CHANNEL_MAX;
	int nRem = nChannelCount%CHANNEL_MAX;
	if(nRem > 0)
	{
		nTemp += 1;
	}
	for(int i =0;i<nTemp;i++)
	{
		if(i<nAlgCurModuleCount)
		{
			pDrv->alg.harm[j].nmodule =  CUR_CHANNEL_MARK/*CSttDevice::g_pSttDevice->getModuleNum(CURRENT,i)*/;//电流模块编号this device func private
			pDrv->alg.harm[j].nwaveCount = harm;
			int nEndCount = (i+1)*CHANNEL_MAX;
			if(nEndCount>=nChannelCount)//为了两个电压模块时候处理的方式
			{
				nEndCount = nChannelCount;
			}
			if(bDC)//这边是赋值的过程
			{
				for(int k=0; k<CHANNEL_MAX; k++)
				{
					CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCCurToDrv(pIData[k].Harm[1].fAmp, k ,pDrv->alg.harm[j].ndat);
				}
			}
			else
			{
				for(int k=0; k<CHANNEL_MAX; k++)
				{
					if(harm==31)
					{
						CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCCurToDrv(pIData[k].Harm[0].fAmp, k ,pDrv->alg.harm[j].ndat);
					}

					for(int m=0;m<harm;m++)
					{
						CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(pIData[k].Harm[m+1].fAmp,
								pIData[k].Harm[m+1].fAngle,
								pIData[k].Harm[m+1].fFreq, k,
								pDrv->alg.harm[j].ndat+m*3*CHANNEL_MAX);
					}
				}
			}
			j++;
		}
	}

	nChannelCount = nAlgVolModuleCount*CHANNEL_MAX;
	nTemp = nChannelCount/CHANNEL_MAX;
	nRem = nChannelCount%CHANNEL_MAX;
	if(nRem>0)
		nTemp+=1;
	for(int i =0;i<nTemp;i++)
	{
		if(i<nAlgVolModuleCount)
		{
			pDrv->alg.harm[j].nmodule = VOL_CHANNEL_MARK/*CSttDevice::g_pSttDevice->getModuleNum(VOLT,i)*/;
			pDrv->alg.harm[j].nwaveCount = harm;
			int nEndCount = (i+1)*CHANNEL_MAX;
			if(nEndCount>=nChannelCount)
				nEndCount = nChannelCount;
			if(bDC)
			{
				for(int k=0; k<CHANNEL_MAX; k++)
				{
					CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCVolToDrv(pUData[k].Harm[1].fAmp, k ,pDrv->alg.harm[j].ndat);
				}
			}
			else
			{
				for(int k=0; k<CHANNEL_MAX; k++)
				{
					if(harm==31)
					{
						CSttDeviceBase::g_pSttDeviceBase->TransAnalogDCVolToDrv(pUData[k].Harm[0].fAmp, k ,pDrv->alg.harm[j].ndat);
					}

					for(int m=0;m<harm;m++)
					{
						CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(pUData[k].Harm[m+1].fAmp,
								pUData[k].Harm[m+1].fAngle,
								pUData[k].Harm[m+1].fFreq, k,
								pDrv->alg.harm[j].ndat+m*3*CHANNEL_MAX);
					}
				}
			}
			j++;
		}
	}
}

BOOL GetGradientPos_alg(int nchannel,int ntype,int nGradientType,int &nTempPos)
{
	BOOL GradientType_Status=TRUE;
	switch(ntype)
	{
	case VOLT:
		break;
	case CURRENT:
		break;
	default:
		return FALSE;
	}

	if(CHANNEL_MAX-nchannel<1)
	{
		return FALSE;
	}

	switch(nGradientType)
	{
	case GRADIENT_AMP:
		nTempPos=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(nchannel,ntype,Amp);
		break;
	case GRADIENT_ANG:
		nTempPos=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(nchannel,ntype,Ang);
		break;
	case GRADIENT_FRE:
		nTempPos=CSttDevice::g_pSttDevice->GetDrvChannel_Analog(nchannel,ntype,Fre);
		break;
	default:
		GradientType_Status=FALSE;
		break;
	}

	return GradientType_Status;
}

BOOL GetGradientPos_dig(int nGradientType,int &nTempPos)
{
	BOOL result=TRUE;
	switch(nGradientType)
	{
	case GRADIENT_AMP:
		nTempPos=DrvPos_Amp;
		break;
	case GRADIENT_ANG:
		nTempPos=DrvPos_Ang;
		break;
	case GRADIENT_FRE:
		nTempPos=DrvPos_Fre;
		break;
	default:
		result=FALSE;
		break;
	}
	return result;
}

void tmt_to_drv_Gradient_alg(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType, int nHarmIndex)
{
	long buffVol[CHANNEL_MAX+3*CHANNEL_MAX] = {0};
	long buffCur[CHANNEL_MAX+3*CHANNEL_MAX] = {0};
	int nTempPos;
	int nUTemp=0;
	int nITemp=0;
	for (unsigned int i=0; i<pDrvGradient->ngradientCount; i++)
	{
		nUTemp=0;
		nITemp=0;
		pDrvGradient->gradient[i].algDgress[0].nmodule = VOL_CHANNEL_MARK/*CSttDevice::g_pSttDevice->getModuleNum(VOLT,0)*/;//是否是电压还是电流
		pDrvGradient->gradient[i].algDgress[0].nposCnt = 0;//下面两个参数是否有效的位数

		pDrvGradient->gradient[i].algDgress[1].nmodule = CUR_CHANNEL_MARK/*CSttDevice::g_pSttDevice->getModuleNum(CURRENT,0)*/;//是否是电压还是电流
		pDrvGradient->gradient[i].algDgress[1].nposCnt = 0;//下面两个参数是否有效的位数

		for (int j=0; j<CHANNEL_MAX; j++)
		{
			if(pGradientProcess->m_bUChange[j][nGradientType] == 1)
			{
				CSttDeviceBase::g_pSttDeviceBase->TransAnalogVolToDrv(pGradientProcess->m_uiStepData[i].fU[j][TmtPos_Amp],
						pGradientProcess->m_uiStepData[i].fU[j][TmtPos_Ang],
						pGradientProcess->m_uiStepData[i].fU[j][TmtPos_Fre], j,
						buffVol);

				if(GetGradientPos_alg(j,VOLT,nGradientType,nTempPos))
				{
					pDrvGradient->gradient[i].algDgress[0].npos[nITemp] =  nTempPos+(nHarmIndex-1)*CHANNEL_MAX*3;
					pDrvGradient->gradient[i].algDgress[0].ndat[nITemp++] = buffCur[nTempPos];
				}

			}

			if(pGradientProcess->m_bIChange[j][nGradientType] == 1)
			{
				CSttDeviceBase::g_pSttDeviceBase->TransAnalogCurToDrv(pGradientProcess->m_uiStepData[i].fI[j][TmtPos_Amp],
						pGradientProcess->m_uiStepData[i].fI[j][TmtPos_Ang],
						pGradientProcess->m_uiStepData[i].fI[j][TmtPos_Fre], j,
						buffCur);

				if(GetGradientPos_alg(j,CURRENT,nGradientType,nTempPos))
				{
					pDrvGradient->gradient[i].algDgress[1].npos[nITemp] =  nTempPos+(nHarmIndex-1)*CHANNEL_MAX*3;
					pDrvGradient->gradient[i].algDgress[1].ndat[nITemp++] = buffCur[nTempPos];
				}

			}
		}

		pDrvGradient->gradient[i].algDgress[0].nposCnt=nUTemp;
		pDrvGradient->gradient[i].algDgress[1].nposCnt=nITemp;
	}
}

void tmt_to_drv_Gradient_dig(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType, int bDC,int nHarmIndex)
{
	unsigned int buff[3] = {0};
	int nTempPos=0;
	int nTemp=0;
	int nVoltChannelA_drv_Index=0;
	int nCurrChannelA_drv_Index=0;

	for (unsigned int i=0; i<pDrvGradient->ngradientCount; i++)
	{
		nTemp=0;
		pDrvGradient->gradient[i].digDgress[0].nmodule = DIGITAL_CHANNEL_MARK;
		pDrvGradient->gradient[i].digDgress[0].nposCnt = 0;//下面两个参数是否有效的位数

		for(int j=0; j<MAX_DIGITAL_GROUP_NUM; j++)
		{
			if(bDC)
			{
				pGradientProcess->m_uiStepData[i].fU[j*3+CHANNEL_A][TmtPos_Fre] = 0;
				pGradientProcess->m_uiStepData[i].fU[j*3+CHANNEL_B][TmtPos_Fre] = 0;
				pGradientProcess->m_uiStepData[i].fU[j*3+CHANNEL_C][TmtPos_Fre] = 0;

				pGradientProcess->m_uiStepData[i].fI[j*3+CHANNEL_A][TmtPos_Fre] = 0;
				pGradientProcess->m_uiStepData[i].fI[j*3+CHANNEL_B][TmtPos_Fre] = 0;
				pGradientProcess->m_uiStepData[i].fI[j*3+CHANNEL_C][TmtPos_Fre] = 0;
			}
			//bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(j,nVoltChannelA_drv_Index,VOLT);
			//CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(j,nCurrChannelA_drv_Index,CURRENT);
			nVoltChannelA_drv_Index=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(j,VOLT,Ang);
			nCurrChannelA_drv_Index=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(j,CURRENT,Ang);
			for(int channel=0;channel<3;channel++)//A B C
			{
				if(pGradientProcess->m_bUChange[j*3+channel][nGradientType] == 1)
				{
					CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(pGradientProcess->m_uiStepData[i].fU[j*3+channel][TmtPos_Amp],
							pGradientProcess->m_uiStepData[i].fU[j*3+channel][TmtPos_Ang],
							pGradientProcess->m_uiStepData[i].fU[j*3+channel][TmtPos_Fre], j,
							buff);//xiangwei-pinlv-fuzhi

					if(GetGradientPos_dig(nGradientType,nTempPos))
					{
						pDrvGradient->gradient[i].digDgress[0].npos[nTemp] =  nVoltChannelA_drv_Index+channel*3+nTempPos+3*DIGITAL_CHANNEL_MAX*(nHarmIndex-1);
						pDrvGradient->gradient[i].digDgress[0].ndat[nTemp++] = buff[nTempPos];
					}
				}

				if(pGradientProcess->m_bIChange[j*3+channel][nGradientType] == 1)
				{
					CSttDeviceBase::g_pSttDeviceBase->TransDigitalVolToDrv(pGradientProcess->m_uiStepData[i].fI[j*3+channel][TmtPos_Amp],
							pGradientProcess->m_uiStepData[i].fI[j*3+channel][TmtPos_Ang],
							pGradientProcess->m_uiStepData[i].fI[j*3+channel][TmtPos_Fre], j,
							buff);

					if(GetGradientPos_dig(nGradientType,nTempPos))
					{
						pDrvGradient->gradient[i].digDgress[0].npos[nTemp] =  nCurrChannelA_drv_Index+channel*3+nTempPos+3*DIGITAL_CHANNEL_MAX*(nHarmIndex-1);
						pDrvGradient->gradient[i].digDgress[0].ndat[nTemp++] = buff[nTempPos];
					}
				}
			}
		}

		pDrvGradient->gradient[i].digDgress[0].nposCnt=nTemp;
	}
}
