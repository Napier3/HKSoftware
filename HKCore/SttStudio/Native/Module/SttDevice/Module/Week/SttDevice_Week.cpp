#include "stdafx.h"
#include "SttDevice_Week.h"

//直流插件 直流加在第一个波形上
//交流插件 直流加在直流分量上
//PN466平台
#define K01_ECTEVT    1<<5  //IO15_AB18 BIT[5]
#define K02_ECTEVT    1<<4  //IO17_AA20 BIT[4]
#define K03_ECTEVT    1<<11 //IO13_V18  BIT[11]
#define K04_ECTEVT    1<<10 //IO14_AA18 BIT[10]
#define K05_ECTEVT    1<<9  //IO18_AB20 BIT[9]
#define K06_ECTEVT    1<<8  //IO11_R16  BIT[8]
#define K07_ECTEVT    1<<7  //IO27_W22  BIT[7]
#define K08_ECTEVT    1<<6  //IO25_U20  BIT[6]
#define K09_ECTEVT    1<<1  //IO26_T20  BIT[1]
#define K10_ECTEVT    1<<0  //IO16_R17  BIT[0]
#define K11_ECTEVT    1<<3  //IO19_AA21 BIT[3]
#define K12_ECTEVT    1<<2  //IO12_U17  BIT[2]

//PI平台
#define K01_PIA12DS    1<<0  //IO15_AB18 BIT[0]
#define K02_PIA12DS    1<<1  //IO17_AA20 BIT[1]
#define K03_PIA12DS    1<<2  //IO13_V18  BIT[2]
#define K04_PIA12DS    1<<3  //IO14_AA18 BIT[3]
#define K05_PIA12DS    1<<4  //IO18_AB20 BIT[4]
#define K06_PIA12DS    1<<5  //IO11_R16  BIT[5]
#define K07_PIA12DS    1<<6  //IO27_W22  BIT[6]
#define K08_PIA12DS    1<<7  //IO25_U20  BIT[7]
#define K09_PIA12DS    1<<8  //IO26_T20  BIT[8]
#define K10_PIA12DS    1<<9  //IO16_R17  BIT[9]
#define K11_PIA12DS    1<<10 //IO19_AA21 BIT[10]
#define K12_PIA12DS    1<<11 //IO12_U17  BIT[11]

int g_nWeekTap = 0;
int WeekTap[4][ADJUST_MAX_CHANNEL_COUNT] =
{
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

//[0]代表最小档 4U4I 6U6I
#ifdef _MainBoard_PI_
unsigned int ECTEVT_Tap[8][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, K08_PIA12DS, K08_PIA12DS},

	{0, K01_PIA12DS, K04_PIA12DS | K01_PIA12DS},
	{0, K02_PIA12DS, K05_PIA12DS | K02_PIA12DS},
	{0, K12_PIA12DS, K06_PIA12DS | K12_PIA12DS},
	{0, K07_PIA12DS, K07_PIA12DS}
};
#else
unsigned int ECTEVT_Tap[8][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, K08_ECTEVT, K08_ECTEVT},

	{0, K01_ECTEVT, K04_ECTEVT | K01_ECTEVT},
	{0, K02_ECTEVT, K05_ECTEVT | K02_ECTEVT},
	{0, K12_ECTEVT, K06_ECTEVT | K12_ECTEVT},
	{0, K07_ECTEVT, K07_ECTEVT}
};
#endif

//直流增量插件 6U2I
unsigned int ECTEVT_Ex1_Tap[8][2] =
{
	{0, K07_ECTEVT},
	{0, K06_ECTEVT},
	{0, K05_ECTEVT},
	{0, K04_ECTEVT},
	{0, K10_ECTEVT},
	{0, K11_ECTEVT},

	{K01_ECTEVT, 0},
	{K02_ECTEVT, 0}
};

unsigned int PIA12DS_Tap[12][2] =
{
	{0, K07_PIA12DS},
	{0, K06_PIA12DS},
	{0, K05_PIA12DS},
	{0, K04_PIA12DS},
	{0, K11_PIA12DS},
	{0, K10_PIA12DS},

	{K09_PIA12DS, 0},
	{K12_PIA12DS, 0},
	{K02_PIA12DS, 0},
	{K01_PIA12DS, 0},
	{K03_PIA12DS, 0},
	{K08_PIA12DS, 0}
};

unsigned int DC6U10V_Tap[6][2] =
{
	{0, K04_ECTEVT},
	{0, K05_ECTEVT},
	{0, K06_ECTEVT},
	{0, K11_ECTEVT},
	{0, K10_ECTEVT},
	{0, K09_ECTEVT}
};

unsigned int DC6I20mA_Tap[6][3] =
{
	{0, K08_ECTEVT, K07_ECTEVT | K08_ECTEVT},
	{0, K10_ECTEVT, K09_ECTEVT | K10_ECTEVT},
	{0, K12_ECTEVT, K11_ECTEVT | K12_ECTEVT},
	{0, K02_ECTEVT, K01_ECTEVT | K02_ECTEVT},
	{0, K04_ECTEVT, K03_ECTEVT | K04_ECTEVT},
	{0, K06_ECTEVT, K05_ECTEVT | K06_ECTEVT}
};

unsigned int PNS331_Tap[8][2] =
{
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},

	{1 << 0, 0},
	{1 << 1, 0},
	{1 << 2, 0},
	{1 << 3, 0}
};

unsigned int L336D_Tap[12][2] =
{
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},
	{0, 0},

	{1 << 0, 0},
	{1 << 1, 0},
	{1 << 2, 0},
	{1 << 3, 0}
};

unsigned int PN_DC6U6I_Tap[12][2] =
{
	{0, K04_ECTEVT},
	{0, K05_ECTEVT},
	{0, K06_ECTEVT},
	{0, K11_ECTEVT},
	{0, K10_ECTEVT},
	{0, K09_ECTEVT},

	{0, K08_ECTEVT},
	{0, K07_ECTEVT},
	{0, K12_ECTEVT},
	{0, K02_ECTEVT},
	{0, K01_ECTEVT},
	{0, K03_ECTEVT}
};

#ifdef _MainBoard_PI_
unsigned int ADMU_Tap[8][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, K08_PIA12DS, K08_PIA12DS},

	{0, K01_PIA12DS, K04_PIA12DS | K01_PIA12DS},
	{0, K02_PIA12DS, K05_PIA12DS | K02_PIA12DS},
	{0, K12_PIA12DS, K06_PIA12DS | K12_PIA12DS},
	{0, K07_PIA12DS, K07_PIA12DS}
};
#else
unsigned int ADMU_Tap[8][3] =
{
	{0, 0, 0},
	{0, 0, 0},
	{0, 0, 0},
	{0, 1<<7, 1<<7},

	{0, 1<<0, 1<<3 | 1<<0},
	{0, 1<<1, 1<<4 | 1<<1},
	{0, 1<<11, 1<<5 | 1<<11},
	{0, 1<<6, 1<<6}
};
#endif

long TranslateACFre(float fFre)
{
	double dFre = fFre / 400000.0;
	if(dFre > 0.999999)
	{
		return 0xFFFFFFFF;
	}
	else
	{
		dFre = dFre * 0xFFFFFFFF;
		long nFre = dFre + 0.5;//4舍5入，减小递变时累积误差
		return nFre;
	}
}

void WeekGradientPreProcess(float &fStart, float &fEnd, float &fStep, long &nStepCnt,
							long &nSign, long GradientType, PSTT_MODULE pModule, long nChannel, long nHarmIndex)
{
	if(GradientType == GRADIENT_AMP)
	{
		if(fEnd < fStart)
		{
			nSign = -1;
		}
		else
		{
			nSign = 1;
		}

		float fTemp = fabs(fEnd - fStart) / fStep;
		long nTemp = (long)fTemp;

		if((fTemp - nTemp) > EPSINON)
		{
			nStepCnt = nTemp + 1;
		}
		else
		{
			nStepCnt = nTemp;
		}

		float fCoef = 1;

		if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
		{
			STT_CHANNEL_ADJUSTS oChsAdjust = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel];

			if(oChsAdjust.m_pChWaveAdj != NULL)
			{
				if(nHarmIndex < oChsAdjust.nHarmCount)
				{
					STT_CHANNEL_WAVE_ADJUST oChWaveAdj = oChsAdjust.m_pChWaveAdj[nHarmIndex];

					if(oChWaveAdj.m_nGearCount <= 1)
					{
						fCoef = oChWaveAdj.m_oChGearAdj[0].m_oAdjItem.m_fCoef;
					}
					else
					{
						for(int nGearIndex = 0; nGearIndex < oChWaveAdj.m_nGearCount; nGearIndex++)
						{
							if(fabs(fEnd) <= oChWaveAdj.m_oChGearAdj[nGearIndex].m_fGearValue
									&& fabs(fStart) <= oChWaveAdj.m_oChGearAdj[nGearIndex].m_fGearValue)
							{
								fCoef = oChWaveAdj.m_oChGearAdj[nGearIndex].m_oAdjItem.m_fCoef;
								break;
							}
						}
					}
				}
			}
		}

		fStep = fStep * fCoef;
	}
	else
	{
		if(fEnd < fStart)
		{
			nSign = -1;
		}
		else
		{
			nSign = 1;
		}

		float fTemp = fabs(fEnd - fStart) / fStep;
		long nTemp = (long)fTemp;

		if((fTemp - nTemp) > EPSINON)
		{
			nStepCnt = nTemp + 1;
		}
		else
		{
			nStepCnt = nTemp;
		}
	}
}

//PIA48S
void TransAnalogDCToDrv_Week_PIA48S(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;

	if(fChMax > 0)
	{
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		if(fabs(fAmp) > fVoltMax)
		{
			if(fAmp > 0)
			{
				fAmp = fVoltMax;
			}
			else
			{
				fAmp = fVoltMax * (-1);
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[0];
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > EPSINON)
	{
		long nRef;

		if(bUseDcZero)
		{
			nRef = 0x7fffffff;
		}
		else
		{
			nRef = 0xffffffff;
		}

		fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChDCMaxValue;
		fAmp = fAmp / fChMax;

		if(fAmp > 0.9999999)
		{
			pDrvData[0] = nRef;
		}
		else
		{
			unsigned long nH = fAmp * nRef;
			pDrvData[0] = nH;
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long TranslateACAmp_Week_PIA48S(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	//fChMax算幅值做分母
	float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;

	if(fChMax > 0)
	{
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	//fVoltMax限制fAmp的最大值
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarm);

	if(fVoltMax > 0)
	{
		fVoltMax = qMin(fVoltMax, fChMax);

		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pChsAdjust != NULL)
	{
		fZero = pChsAdjust->m_fDcZero[0];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					fCoef = pAdjItem->m_fCoef;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							fCoef = pAdjItem->m_fCoef;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > 0)
	{
		fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChDCMaxValue;
		fAmp = fAmp * 1.414 / fChMax;

		if(fAmp > 0.999999)
		{
			return 0xffffffff;
		}
		else
		{
			unsigned long nH = fAmp * 0xffffffff;
			return nH;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void TransAnalogToDrv_Week_PIA48S(float fAmp, float fAng, float fFre, int nChannel,
								  int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_PIA48S(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef * 16); //小信号需要乘以16
	pnDrvData[2] = TranslateACAmp_Week_PIA48S(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_PIA48S(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	if(bIsDc)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fabs(fAmp), k, nIndex, dat + k);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 48 + 48 * 3 * 2;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				TransAnalogDCToDrv_Week_PIA48S(fAmp, k, nIndex, dat + k);
			}
			//Base
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
					fFreq = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
				}

				TransAnalogToDrv_Week_PIA48S(fAmp, fAngle,
											 fFreq, k, nIndex, dat + 48 + k * 3);
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarm = 0;
				for(int nHarmIndex = 2; nHarmIndex < nHarmCount; nHarmIndex++)
				{
					nHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].nSelectIndex;

					if(nHarm > 0 && nHarm < 31)
					{
						oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
						fAmp = oTmtHarm->fAmp;

						if(fWeekPT > EPSINON)
						{
							fAmp = fAmp / fWeekPT;
						}
						else
						{
							fAmp = 0;
						}

						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogToDrv_Week_PIA48S(fAmp, fAngle,
													 fFreq, k, nIndex, dat + 48 + k * 3 + 3 * 48);
						break;
					}
				}
			}
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 48 + 2 * 3 * 48;
	}
}

void State_Week_PIA48S(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 48 + 2 * 3 * 48;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fabs(fAmp), k, nIndex, dat + k);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fAmp, k, nIndex, dat + k);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_PIA48S(fAmp, fAngle,
										 fFreq, k, nIndex, dat + 48 + k * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_PIA48S(fAmp, fAngle,
												 fFreq, k, nIndex, dat + 48 + k * 3 + 3 * 48);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_PIA48S(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								BOOL bIsDc, int nStatus)
{
}

//PN Main
void TransAnalogToDrv_Week_PN_Main(float fAmp, float fAng, float fFre, int nChannel,
								   int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_PIA48S(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef * 8);
	pnDrvData[2] = TranslateACAmp_Week_PIA48S(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_PN_Main(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						 BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	int nDrvPos;
	float fWeekPT = 0;

	if(bIsDc)
	{
		for(int k = 0; k < 12; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < 12; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				TransAnalogDCToDrv_Week_PIA48S(fAmp, k, nIndex, dat + nDrvPos);
			}
			//Base
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
					fFreq = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
				}

				TransAnalogToDrv_Week_PN_Main(fAmp, fAngle,
											  fFreq, k, nIndex, dat + 12 + nDrvPos * 3);
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_PN_Main(fAmp, fAngle,
														  fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + nHarmIndex * 3 * 12);
							break;
						}
					}
				}
			}
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + nHarm * 3 * 12;
	}
}

void State_Week_PN_Main(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 2 * 3 * 12;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	int nDrvPos;
	float fWeekPT = 0;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PIA48S(fAmp, k, nIndex, dat + nDrvPos);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_PN_Main(fAmp, fAngle,
										  fFreq, k, nIndex, dat + 12 + nDrvPos * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_PN_Main(fAmp, fAngle,
												  fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + 3 * 12);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_PN_Main(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								 BOOL bIsDc, int nStatus)
{
}

//PIA12DS
void TransAnalogDCToDrv_Week_PIA12DS(float fAmp, int nChannel, int nModuleIndex, long *pDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 6)
	{
		//Volt
		if(nTap == 0)
		{
			fChMax = 0.2;
		}
		else
		{
			fChMax = 10;
		}
	}
	else
	{
		//Current
		if(nTap == 0)
		{
			fChMax = 0.001;
		}
		else
		{
			fChMax = 0.02;
		}
	}

	fChMax = fChMax * 1.2;
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		fZero = pChsAdjust->m_fDcZero[0];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	/*************fAmp值补偿************/
	/******设置零漂******/
	double fH;

	if(nChannel < 6)
	{
		fH = (-fZero) * 32768 / (fChMax * 1.414);
	}
	else
	{
		fH = fZero * 32768 / (fChMax * 1.414);
	}

	long nH = fH;
	long nL = (fH - nH) * 65536;
	pDrvData[nChannel]  = ((nH << 16) & 0xFFFF0000) + nL;
	/******设置零漂******/
	long  nPh;

	if(fAmp > 0 || fabs(fAmp) < EPSINON)
	{
		nPh = 90 * 65536 / 360;
	}
	else
	{
		nPh = 270 * 65536 / 360;
	}

	pDrvData[nChannel * 3 + 12] = nPh << 16;
	fAmp = fabs(fAmp);
	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		pDrvData[nChannel * 3 + 2 + 12] = 0;
		return;
	}

	/*************确定合适的fAmp值************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > EPSINON)
	{
		fAmp = fAmp * fCoef;
		double fH = fAmp * 65536 / fChMax;
		long nH = fH;
		long nL = (fH - nH) * 65536;
		pDrvData[nChannel * 3 + 2 + 12]  = ((nH << 16) & 0xFFFF0000) + nL;
	}
	else
	{
		pDrvData[nChannel * 3 + 2 + 12] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

void Manual_Week_PIA12DS(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	float fWeekPT = 0;
	float fMaxOut[12];

	for(int k = 0; k < 12; k++)
	{
		nTmtPos = k;

		if(bIsModuleOutput)
		{
			pTmt_channel = pTmt_Volt;
			fWeekPT = 1.0f;
		}
		else
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(k < 6)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(bIsModuleOutput)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					if(k < 6)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						if(fWeekPT > 1.001)
						{
							//电流分段变比
							if(fAmp > 0 || fabs(fAmp) < EPSINON)
							{
								fAmp = fAmp / fWeekPT;
								fAmp = (20 - 12) * fAmp / 20 + 0.012;
							}
							else
							{
								//负数段
								fAmp = fabs(fAmp) / fWeekPT;
								fAmp = 0.012 - (12 - 4) * fAmp / 20;
							}
						}
						else
						{
							fAmp = fAmp / fWeekPT;
						}
					}
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		fMaxOut[k] = fAmp;
	}

	g_nWeekTap = GetTapCode_PIA12DS(fMaxOut, FALSE, WeekTap[nIndex]);

	for(int k = 0; k < 12; k++)
	{
		TransAnalogDCToDrv_Week_PIA12DS(fMaxOut[k], k, nIndex, dat);
	}

	pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
}

void State_Week_PIA12DS(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 12 * 3;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	for(int k = 0; k < nTmtChanNum; k++)
	{
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(k < 6)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					if(fWeekPT > 1.001)
					{
						//电流分段变比
						if(fAmp > 0 || fabs(fAmp) < EPSINON)
						{
							fAmp = fAmp / fWeekPT;
							fAmp = (20 - 12) * fAmp / 20 + 0.012;
						}
						else
						{
							//负数段
							fAmp = fabs(fAmp) / fWeekPT;
							fAmp = 0.012 - (12 - 4) * fAmp / 20;
						}
					}
					else
					{
						fAmp = fAmp / fWeekPT;
					}
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		TransAnalogDCToDrv_Week_PIA12DS(fAmp, k, nIndex, dat);
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_PIA12DS(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								 BOOL bIsDc, int nStatus)
{
}

int GetTapCode_PIA12DS(float *fMaxOut, BOOL bStateTest, int *nTap)
{
	int nRetTap = 0;

	//6U
	for(int i = 0; i < 6; i++)
	{
		if(fabs(fMaxOut[i]) > 0.2001 || bStateTest)
		{
			nRetTap |= PIA12DS_Tap[i][1];
			nTap[i] = 1;//fVoltMax =10
		}
		else
		{
			nRetTap |= PIA12DS_Tap[i][0];
			nTap[i] = 0;//fVoltMax =0.2
		}
	}

	//6I
	for(int i = 6; i < 12; i++)
	{
		if(fabs(fMaxOut[i]) > 0.001001 || bStateTest)
		{
			nRetTap |= PIA12DS_Tap[i][1];
			nTap[i] = 1;//fVoltMax =0.02
		}
		else
		{
			nRetTap |= PIA12DS_Tap[i][0];
			nTap[i] = 0;//fVoltMax =0.001
		}
	}

	return nRetTap;
}

//EVTECT
void TransAnalogDCToDrv_Week_EVTECT(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			if(nTap == 0)
			{
				fChMax = 0.7;
			}
			else
			{
				fChMax = 7.8;
			}
		}
		else
		{
			fChMax = 3.8;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 0.1;
			}
			else if(nTap == 1)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[nTap];
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > EPSINON)
	{
		long nRef;

		if(bUseDcZero)
		{
			nRef = 0x7fffffff;
		}
		else
		{
			nRef = 0xffffffff;
		}

		fChMax = fChMax * 1.414;
		fAmp = fAmp / fChMax;

		if(fAmp > 0.9999999)
		{
			pDrvData[0] = nRef;
		}
		else
		{
			unsigned long nH = fAmp * nRef;
			pDrvData[0] = nH;
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long TranslateACAmp_Week_EVTECT(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			if(nTap == 0)
			{
				fChMax = 0.7;
			}
			else
			{
				fChMax = 7.8;
			}
		}
		else
		{
			fChMax = 3.8;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 0.1;
			}
			else if(nTap == 1)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					fCoef = pAdjItem->m_fCoef;
					fZero = pAdjItem->m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							fCoef = pAdjItem->m_fCoef;
							fZero = pAdjItem->m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > 0)
	{
		fAmp = fAmp / fChMax;

		if(fAmp > 0.999999)
		{
			return 0xffffffff;
		}
		else
		{
			unsigned long nH = fAmp * 0xffffffff;
			return nH;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void TransAnalogToDrv_Week_EVTECT(float fAmp, float fAng, float fFre, int nChannel,
								  int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_EVTECT(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef);
	pnDrvData[2] = TranslateACAmp_Week_EVTECT(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_EVTECT(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;
	float fDcMaxOut[8];
	float fMaxOut[8];
	float fFreq[8];
	float fAngle[8];

	if(nHarm > 1)
	{
		g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
	}

	BOOL bTapDc[8];

	if(bIsDc)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			fDcMaxOut[k] = fAmp;
			bTapDc[k] = TRUE;
		}

		g_nWeekTap = GetTapCode_EVTECT(fDcMaxOut, FALSE, bTapDc, WeekTap[nIndex]);

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_EVTECT(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				fDcMaxOut[k] = fAmp;
			}
			//Base
			{
				bTapDc[k] = FALSE;

				if(nTmtPos < 0)
				{
					fMaxOut[k] = 0;
					fFreq[k] = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fMaxOut[k] = fAmp / fWeekPT;
					}
					else
					{
						fMaxOut[k] = 0;
					}

					fAngle[k] = oTmtHarm->fAngle;
					fFreq[k] = oTmtHarm->fFreq;

					if(fFreq[k] < EPSINON)
					{
						bTapDc[k] = TRUE;
					}
				}
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_EVTECT(fAmp, fAngle,
														 fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + nHarmIndex * 3 * 12);
							break;
						}
					}
				}
			}
		}

		if(nHarm == 1)
		{
			g_nWeekTap = GetTapCode_EVTECT(fMaxOut, FALSE, bTapDc, WeekTap[nIndex]);
		}

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_EVTECT(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
			TransAnalogToDrv_Week_EVTECT(fMaxOut[k], fAngle[k],
										 fFreq[k], k, nIndex, dat + 12 + nDrvPos * 3);
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + nHarm * 3 * 12;
	}
}

void State_Week_EVTECT(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 2 * 3 * 12;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_EVTECT(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_EVTECT(fAmp, k, nIndex, dat + nDrvPos);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_EVTECT(fAmp, fAngle,
										 fFreq, k, nIndex, dat + 12 + nDrvPos * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_EVTECT(fAmp, fAngle,
												 fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + 3 * 12);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_EVTECT(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								BOOL bIsDc, int nStatus)
{
}

int GetTapCode_EVTECT(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap)
{
	int nRetTap = 0;
	float nValue;

	//4U
	for(int i = 0; i < 4; i++)
	{
		if(bStateTest)
		{
			nRetTap |= ECTEVT_Tap[i][2];
			nTap[i] = 2;
			continue;
		}

		nValue = fabs(fMaxOut[i]);

		switch(i)
		{
			case 0:
			case 1:
			case 2:
			{
				nRetTap |= ECTEVT_Tap[i][0];
				nTap[i] = 0;//fVoltMax =3.8
			}
			break;

			case 3:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 0.7001 * 1.414;
				}
				else
				{
					nTapValue = 0.7001;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= ECTEVT_Tap[i][1];
					nTap[i] = 1;//fVoltMax = 7.8
				}
				else
				{
					nRetTap |= ECTEVT_Tap[i][0];
					nTap[i] = 0;//fVoltMax =0.7
				}
			}
			break;
		}
	}

	//4I
	for(int i = 4; i < 8; i++)
	{
		if(bStateTest)
		{
			nRetTap |= ECTEVT_Tap[i][2];
			nTap[i] = 2;
			continue;
		}

		nValue = fabs(fMaxOut[i]);

		switch(i)
		{
			case 4:
			case 5:
			case 6:
			{
				float nTapValue_l, nTapValue_m;

				if(bTapDc[i])
				{
					nTapValue_l = 0.1001 * 1.414;
					nTapValue_m = 1.2001 * 1.414;
				}
				else
				{
					nTapValue_l = 0.1001;
					nTapValue_m = 1.2001;
				}

				if(nValue > nTapValue_m)
				{
					nRetTap |= ECTEVT_Tap[i][2];
					nTap[i] = 2;//fVoltMax = 20
				}
				else if(nValue > nTapValue_l)
				{
					nRetTap |= ECTEVT_Tap[i][1];
					nTap[i] = 1;//fVoltMax = 1.2
				}
				else
				{
					nRetTap |= ECTEVT_Tap[i][0];
					nTap[i] = 0;//fVoltMax =0.1
				}
			}
			break;

			case 7:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 0.2401 * 1.414;
				}
				else
				{
					nTapValue = 0.2401;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= ECTEVT_Tap[i][1];
					nTap[i] = 1;//fVoltMax = 4
				}
				else
				{
					nRetTap |= ECTEVT_Tap[i][0];
					nTap[i] = 0;//fVoltMax =0.24
				}
			}
			break;
		}
	}

	return nRetTap;
}

//EVTECT_Ex1
void TransAnalogDCToDrv_Week_EVTECT_Ex1(float fAmp, int nChannel, int nModuleIndex, long *pDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	long nDrvPos = pModule->m_nChDrvPos[nChannel];
	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 6)
	{
		//Volt
		if(nChannel < 4)
		{
			if(nTap == 0)
			{
				fChMax = 0.2;
			}
			else
			{
				fChMax = 10;
			}
		}
		else
		{
			fChMax = 0.5;
		}
	}
	else
	{
		//Current
		if(nTap == 0)
		{
			fChMax = 0.001;
		}
		else
		{
			fChMax = 0.03;
		}
	}

	fChMax = fChMax * 1.2;
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		fZero = pChsAdjust->m_fDcZero[0];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	/*************fAmp值补偿************/
	/******设置零漂******/
	double fH;

	if(nChannel < 6)
	{
		fH = (-fZero) * 32768 / (fChMax * 1.414);
	}
	else
	{
		fH = fZero * 32768 / (fChMax * 1.414);
	}

	long nH = fH;
	long nL = (fH - nH) * 65536;
	pDrvData[nDrvPos]  = ((nH << 16) & 0xFFFF0000) + nL;
	/******设置零漂******/
	long  nPh;

	if(fAmp > 0 || fabs(fAmp) < EPSINON)
	{
		nPh = 90 * 65536 / 360;
	}
	else
	{
		nPh = 270 * 65536 / 360;
	}

	pDrvData[nDrvPos * 3 + 12] = nPh << 16;
	fAmp = fabs(fAmp);
	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		pDrvData[nDrvPos * 3 + 2 + 12] = 0;
		return;
	}

	/*************确定合适的fAmp值************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > EPSINON)
	{
		fAmp = fAmp * fCoef;
		double fH = fAmp * 65536 / fChMax;
		long nH = fH;
		long nL = (fH - nH) * 65536;
		pDrvData[nDrvPos * 3 + 2 + 12]  = ((nH << 16) & 0xFFFF0000) + nL;
	}
	else
	{
		pDrvData[nDrvPos * 3 + 2 + 12] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

void Manual_Week_EVTECT_Ex1(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	float fWeekPT = 0;
	float fMaxOut[8];

	for(int k = 0; k < 8; k++)
	{
		nTmtPos = k;

		if(bIsModuleOutput)
		{
			pTmt_channel = pTmt_Volt;
			fWeekPT = 1.0f;
		}
		else
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				fAmp = fAmp / fWeekPT;
			}
			else
			{
				fAmp = 0;
			}
		}

		fMaxOut[k] = fAmp;
	}

	g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, FALSE, WeekTap[nIndex]);

	for(int k = 0; k < 8; k++)
	{
		TransAnalogDCToDrv_Week_EVTECT_Ex1(fMaxOut[k], k, nIndex, dat);
	}

	pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
}

void State_Week_EVTECT_Ex1(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 12 * 3;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	for(int k = 0; k < nTmtChanNum; k++)
	{
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				fAmp = fAmp / fWeekPT;
			}
			else
			{
				fAmp = 0;
			}
		}

		TransAnalogDCToDrv_Week_EVTECT_Ex1(fAmp, k, nIndex, dat);
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void State_Gradient_Week_EVTECT_Ex1(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
									int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	float fLastStep;
	long nStepCount;
	long nSign;
	int nChPos;
	long nTmtPos;
	float fChMax;
	float fWeekPT;

	for(int k = 0; k < pModule->m_oModuleAttr.m_nChannelNum; k++)
	{
		nChPos = pModule->m_nChDrvPos[k];
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];
		PSTT_MODULE_CH_DEF pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k];
		fChMax = pChDef->m_fChDCMaxValue * 1.2;

		if(nTmtPos >= 0)
		{
			if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			tmt_channel &ui = pTmt_channel[nTmtPos];

			if(ui.Ramp[0].nIndex > -1)
			{
				fStart = fabs(ui.Harm[1].fAmp);
				fEnd = fabs(ui.Ramp[0].fEnd);
				fStep = fabs(ui.Ramp[0].fStep);

				if(fEnd < fStart)
				{
					nSign = -1;
				}
				else
				{
					nSign = 1;
				}

				if(fWeekPT > EPSINON)
				{
					fStart = fStart / fWeekPT;
					fEnd = fEnd / fWeekPT;
					fStep = fStep / fWeekPT;
				}
				else
				{
					continue;
				}

				if(fStep > (fChMax * 0.5))
				{
					fStep = fChMax * 0.5;
				}

				float fTemp = fabs(fEnd - fStart) / fStep;
				long nTemp = (long)fTemp;

				if((fTemp - nTemp) > EPSINON)
				{
					nStepCount = nTemp + 1;
				}
				else
				{
					nStepCount = nTemp;
				}

				if(fabs(fEnd - fStart) < fStep)
				{
					fLastStep = fabs(fEnd - fStart);
				}
				else
				{
					fLastStep = fStart + fStep * nSign * (nStepCount - 1);

					if(fabs(fEnd - fLastStep) > EPSINON)
					{
						fLastStep = fabs(fEnd - fLastStep);
					}
					else
					{
						fLastStep = fStep;
					}
				}

				float fCoef = 1;

				if(k < pModule->m_oModuleAttr.m_nChannelNum)
				{
					STT_CHANNEL_ADJUSTS oChsAdjust = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[k];

					if(oChsAdjust.m_pChWaveAdj != NULL)
					{
						STT_CHANNEL_WAVE_ADJUST oChWaveAdj = oChsAdjust.m_pChWaveAdj[0];

						if(oChWaveAdj.m_nGearCount > 0)
						{
							fCoef = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fCoef;
						}
					}
				}

				fStep = fStep * fCoef;
				fLastStep = fLastStep * fCoef;

				if(fStep > StateDegressMinStep)
				{
					oDrvStateDeg.nCount[12 + nChPos * 3 + 2] = nStepCount;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					oDrvStateDeg.changeVal[12 + nChPos * 3 + 2] = nSign * (((nH << 16) & 0xFFFF0000) + nL);
					nH = fLastStep * 65536 / fChMax;
					fH = fLastStep * 65536 / fChMax;
					nL = (fH - nH) * 65536;
					oDrvStateDeg.lastVal[12 + nChPos * 3 + 2] = nSign * (((nH << 16) & 0xFFFF0000) + nL);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

void Gradient_NormalWeek_EVTECT_Ex1(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
									BOOL bIsDc, int nStatus)
{
}

int GetTapCode_EVTECT_Ex1(float *fMaxOut, BOOL bStateTest, int *nTap)
{
	int nRetTap = 0;

	//6U
	for(int i = 0; i < 6; i++)
	{
		switch(i)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			{
				if(fabs(fMaxOut[i]) > 0.2001 || bStateTest)
				{
					nRetTap |= ECTEVT_Ex1_Tap[i][1];
					nTap[i] = 1;//fVoltMax =10
				}
				else
				{
					nRetTap |= ECTEVT_Ex1_Tap[i][0];
					nTap[i] = 0;//fVoltMax =0.2
				}
			}
			break;

			case 4:
			case 5:
			{
				nRetTap |= ECTEVT_Ex1_Tap[i][1];
				nTap[i] = 1;//fVoltMax =0.5
			}
			break;
		}
	}

	//2I
	for(int i = 6; i < 8; i++)
	{
		if(fabs(fMaxOut[i]) > 0.0011 || bStateTest)
		{
			nRetTap |= ECTEVT_Ex1_Tap[i][1];
			nTap[i] = 1;//fVoltMax =0.03
		}
		else
		{
			nRetTap |= ECTEVT_Ex1_Tap[i][0];
			nTap[i] = 0;//fVoltMax =0.001
		}
	}

	return nRetTap;
}

//DC6U10V
void TransAnalogDCToDrv_Week_DC6U10V(float fAmp, int nChannel, int nModuleIndex, long *pDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	float fChMax;
	long nDrvPos = pModule->m_nChDrvPos[nChannel];
	int nTap = WeekTap[nModuleIndex][nChannel];

	//Volt
	if(nTap == 0)
	{
		fChMax = 0.2;
	}
	else
	{
		fChMax = 10;
	}

	fChMax = fChMax * 1.2;
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1;//幅值系数
	float fZero = 0;//零漂
	float fDcZero = 0;//直流零漂

	if(pChsAdjust != NULL)
	{
		fDcZero = pChsAdjust->m_fDcZero[nTap];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
				fZero = pAdjItem->m_fZero;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						fZero = pAdjItem->m_fZero;
						break;
					}
				}
			}
		}
	}

	/*************fAmp值补偿************/
	float fValue;
	fValue = -fDcZero;
	pDrvData[nDrvPos] = fValue / fChMax * 0x7fffffff;
	fValue = fAmp * fCoef + fZero;
	long  nPh;

	if(fValue > 0 || fabs(fValue) < EPSINON)
	{
		nPh = 90 * 65536 / 360;
	}
	else
	{
		nPh = 270 * 65536 / 360;
	}

	pDrvData[nDrvPos * 3 + 12] = nPh << 16;
	fValue = fabs(fValue) / fChMax;

	if(fValue > 0.9999999)
	{
		pDrvData[nDrvPos * 3 + 12 + 2] = 0xffffffff;
	}
	else
	{
		unsigned long nH = fValue * 0xffffffff;
		pDrvData[nDrvPos * 3 + 12 + 2] = nH;
	}
}

void Manual_Week_DC6U10V(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput, int nTap)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	float fWeekPT = 0;
	float fMaxOut[6];

	for(int k = 0; k < 6; k++)
	{
		nTmtPos = k;

		if(bIsModuleOutput)
		{
			pTmt_channel = pTmt_Volt;
			fWeekPT = 1.0f;
		}
		else
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];
			pTmt_channel = pTmt_Volt;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				fAmp = fAmp / fWeekPT;
			}
			else
			{
				fAmp = 0;
			}
		}

		fMaxOut[k] = fAmp;
	}

	g_nWeekTap = GetTapCode_DC6U10V(fMaxOut, FALSE, WeekTap[nIndex], nTap);

	for(int k = 0; k < 6; k++)
	{
		TransAnalogDCToDrv_Week_DC6U10V(fMaxOut[k], k, nIndex, dat);
	}

	pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
}

void State_Week_DC6U10V(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 12 * 3;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	for(int k = 0; k < nTmtChanNum; k++)
	{
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				fAmp = fAmp / fWeekPT;
			}
			else
			{
				fAmp = 0;
			}
		}

		TransAnalogDCToDrv_Week_DC6U10V(fAmp, k, nIndex, dat);
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_DC6U10V(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								 BOOL bIsDc, int nStatus)
{
}

int GetTapCode_DC6U10V(float *fMaxOut, BOOL bStateTest, int *nCalTap, int nUserSetTap)
{
	int nRetTap = 0;

	//6U
	for(int i = 0; i < 6; i++)
	{
		if(fabs(fMaxOut[i]) > 0.2001 || bStateTest)
		{
			nRetTap |= DC6U10V_Tap[i][1];
			nCalTap[i] = 1;//fVoltMax =10
		}
		else
		{
			if(fabs(fMaxOut[i]) < EPSINON)
			{
				//零值输出
				if(nUserSetTap == 0)
				{
					nRetTap |= DC6U10V_Tap[i][0];
					nCalTap[i] = 0;//fVoltMax =0.2
				}
				else
				{
					nRetTap |= DC6U10V_Tap[i][1];
					nCalTap[i] = 1;//fVoltMax =10
				}
			}
			else
			{
				nRetTap |= DC6U10V_Tap[i][0];
				nCalTap[i] = 0;//fVoltMax =0.2
			}
		}
	}

	return nRetTap;
}

//DC6I20mA
void TransAnalogDCToDrv_Week_DC6I20mA(float fAmp, int nChannel, int nModuleIndex, long *pDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	float fChMax;
	long nDrvPos = pModule->m_nChDrvPos[nChannel];
	int nTap = WeekTap[nModuleIndex][nChannel];

	//Current
	if(nTap == 0)
	{
		fChMax = 0.001;
	}
	else if(nTap == 1)
	{
		fChMax = 0.02;
	}
	else
	{
		fChMax = 0.8;
	}

	fChMax = fChMax * 1.2;
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1;//幅值系数
	float fZero = 0;//零漂
	float fDcZero = 0;//直流零漂

	if(pChsAdjust != NULL)
	{
		fDcZero = pChsAdjust->m_fDcZero[nTap];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
				fZero = pAdjItem->m_fZero;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						fZero = pAdjItem->m_fZero;
						break;
					}
				}
			}
		}
	}

	/*************fAmp值补偿************/
	float fValue;
	fValue = fDcZero;
	pDrvData[nDrvPos] = fValue / fChMax * 0x7fffffff;
	fValue = fAmp * fCoef + fZero;
	long  nPh;
	nPh = 90 * 65536 / 360;
	pDrvData[nDrvPos * 3 + 12] = nPh << 16;
	fValue = fabs(fValue) / fChMax;

	if(fValue > 0.9999999)
	{
		pDrvData[nDrvPos * 3 + 12 + 2] = 0xffffffff;
	}
	else
	{
		unsigned long nH = fValue * 0xffffffff;
		pDrvData[nDrvPos * 3 + 12 + 2] = nH;
	}
}

void Manual_Week_DC6I20mA(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput, int nTap)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	float fWeekPT = 0;
	float fMaxOut[6];

	for(int k = 0; k < 6; k++)
	{
		nTmtPos = k;

		if(bIsModuleOutput)
		{
			pTmt_channel = pTmt_Volt;
			fWeekPT = 1.0f;
		}
		else
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];
			pTmt_channel = pTmt_Current;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(bIsModuleOutput)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					if(fWeekPT > 1.001)
					{
						//电流分段变比
						if(fAmp > 0 || fabs(fAmp) < EPSINON)
						{
							fAmp = fAmp / fWeekPT;
							fAmp = (20 - 12) * fAmp / 20 + 0.012;
						}
						else
						{
							//负数段
							fAmp = fabs(fAmp) / fWeekPT;
							fAmp = 0.012 - (12 - 4) * fAmp / 20;
						}
					}
					else
					{
						fAmp = fAmp / fWeekPT;
					}
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		fMaxOut[k] = fAmp;
	}

	g_nWeekTap = GetTapCode_DC6I20mA(fMaxOut, FALSE, WeekTap[nIndex], nTap);

	for(int k = 0; k < 6; k++)
	{
		TransAnalogDCToDrv_Week_DC6I20mA(fMaxOut[k], k, nIndex, dat);
	}

	pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
}

void State_Week_DC6I20mA(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 12 * 3;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	int nTmtPos;
	float fWeekPT = 0;

	for(int k = 0; k < 6; k++)
	{
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];
		pTmt_channel = oTmt_paraState.m_uiCUR;

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(fWeekPT > 1.001)
				{
					//电流分段变比
					if(fAmp > 0 || fabs(fAmp) < EPSINON)
					{
						fAmp = fAmp / fWeekPT;
						fAmp = (20 - 12) * fAmp / 20 + 0.012;
					}
					else
					{
						//负数段
						fAmp = fabs(fAmp) / fWeekPT;
						fAmp = 0.012 - (12 - 4) * fAmp / 20;
					}
				}
				else
				{
					fAmp = fAmp / fWeekPT;
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		TransAnalogDCToDrv_Week_DC6I20mA(fAmp, k, nIndex, dat);
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_DC6I20mA(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								  BOOL bIsDc, int nStatus)
{
}

int GetTapCode_DC6I20mA(float *fMaxOut, BOOL bStateTest, int *nCalTap, int nUserSetTap)
{
	int nRetTap = 0;

	//6I
	for(int i = 0; i < 6; i++)
	{
		if(bStateTest)
		{
			nRetTap |= DC6I20mA_Tap[i][1];
			nCalTap[i] = 1;//fVoltMax =0.02
		}
		else
		{
			if(fabs(fMaxOut[i]) > 0.020001)
			{
				nRetTap |= DC6I20mA_Tap[i][2];
				nCalTap[i] = 2;//fVoltMax =0.8
			}
			else if(fabs(fMaxOut[i]) > 0.001001)
			{
				nRetTap |= DC6I20mA_Tap[i][1];
				nCalTap[i] = 1;//fVoltMax =0.02
			}
			else
			{
				if(fabs(fMaxOut[i]) < EPSINON)
				{
					//零值输出
					if(nUserSetTap == 0)
					{
						nRetTap |= DC6I20mA_Tap[i][0];
						nCalTap[i] = 0;//fVoltMax =0.001
					}
					else if(nUserSetTap == 1)
					{
						nRetTap |= DC6I20mA_Tap[i][1];
						nCalTap[i] = 1;//fVoltMax =0.02
					}
					else
					{
						nRetTap |= DC6I20mA_Tap[i][2];
						nCalTap[i] = 2;//fVoltMax =0.8
					}
				}
				else
				{
					nRetTap |= DC6I20mA_Tap[i][0];
					nCalTap[i] = 0;//fVoltMax =0.001
				}
			}
		}
	}

	return nRetTap;
}


//PNS331
void TransAnalogDCToDrv_Week_PNS331(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			fChMax = 8.0;
		}
		else
		{
			fChMax = 4.0;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[nTap];
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.1;

	if(fAmp > EPSINON)
	{
		long nRef;

		if(bUseDcZero)
		{
			nRef = 0x7fffffff;
		}
		else
		{
			nRef = 0xffffffff;
		}

		fChMax = fChMax * 1.414;
		fAmp = fAmp / fChMax;

		if(fAmp > 0.9999999)
		{
			pDrvData[0] = nRef;
		}
		else
		{
			unsigned long nH = fAmp * nRef;
			pDrvData[0] = nH;
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long TranslateACAmp_Week_PNS331(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			fChMax = 8.0;
		}
		else
		{
			fChMax = 4.0;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					fCoef = pAdjItem->m_fCoef;
					fZero = pAdjItem->m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							fCoef = pAdjItem->m_fCoef;
							fZero = pAdjItem->m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.1;

	if(fAmp > 0)
	{
		fAmp = fAmp / fChMax;

		if(fAmp > 0.999999)
		{
			return 0xffffffff;
		}
		else
		{
			unsigned long nH = fAmp * 0xffffffff;
			return nH;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void TransAnalogToDrv_Week_PNS331(float fAmp, float fAng, float fFre, int nChannel,
								  int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_PNS331(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef * 8);
	pnDrvData[2] = TranslateACAmp_Week_PNS331(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_PNS331(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
						BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;
	float fDcMaxOut[8];
	float fMaxOut[8];
	float fFreq[8];
	float fAngle[8];

	if(nHarm > 1)
	{
		g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
	}

	BOOL bTapDc[8];

	if(bIsDc)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			fDcMaxOut[k] = fAmp;
			bTapDc[k] = TRUE;
		}

		g_nWeekTap = GetTapCode_PNS331(fDcMaxOut, FALSE, bTapDc, WeekTap[nIndex]);

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_PNS331(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 8 + 8 * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				fDcMaxOut[k] = fAmp;
			}
			//Base
			{
				bTapDc[k] = FALSE;

				if(nTmtPos < 0)
				{
					fMaxOut[k] = 0;
					fFreq[k] = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fMaxOut[k] = fAmp / fWeekPT;
					}
					else
					{
						fMaxOut[k] = 0;
					}

					fAngle[k] = oTmtHarm->fAngle;
					fFreq[k] = oTmtHarm->fFreq;

					if(fFreq[k] < EPSINON)
					{
						bTapDc[k] = TRUE;
					}
				}
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_PNS331(fAmp, fAngle,
														 fFreq, k, nIndex, dat + 8 + nDrvPos * 3 + nHarmIndex * 3 * 8);
							break;
						}
					}
				}
			}
		}

		if(nHarm == 1)
		{
			g_nWeekTap = GetTapCode_PNS331(fMaxOut, FALSE, bTapDc, WeekTap[nIndex]);
		}

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_PNS331(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
			TransAnalogToDrv_Week_PNS331(fMaxOut[k], fAngle[k],
										 fFreq[k], k, nIndex, dat + 8 + nDrvPos * 3);
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 8 + nHarm * 3 * 8;
	}
}

void State_Week_PNS331(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 8 + 2 * 3 * 8;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PNS331(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PNS331(fAmp, k, nIndex, dat + nDrvPos);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_PNS331(fAmp, fAngle,
										 fFreq, k, nIndex, dat + 8 + nDrvPos * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_PNS331(fAmp, fAngle,
												 fFreq, k, nIndex, dat + 8 + nDrvPos * 3 + 3 * 8);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_PNS331(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								BOOL bIsDc, int nStatus)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nDrvPos;
	float fAmp, fAngle, fFreq;
	float fWeekPT = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		dat = pszDrv->para[nModuleOffset].bfChangedat;
	}
	else if(nStatus == 1)
	{
		dat = pszDrv->para[nModuleOffset].bfFaultdat;
	}
	else
	{
		dat = pszDrv->para[nModuleOffset].FaultBegindat;
	}

	tmt_channel *pTmt_channel;
	long nTmtPos;

	if(bIsDc)
	{
		for(int k = 0; k < 8; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];
			nDrvPos = pModule->m_nChDrvPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_PNS331(fAmp, k, nModuleIndex, dat + nDrvPos);
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleOffset].nDWcnt = 8 + 8 * 3;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < 8; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				TransAnalogDCToDrv_Week_PNS331(fAmp, k, nModuleIndex, dat + nDrvPos);
			}
			//Base
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
					fFreq = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
				}

				TransAnalogToDrv_Week_PNS331(fAmp, fAngle,
											 fFreq, k, nModuleIndex, dat + 8 + nDrvPos * 3);
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_PNS331(fAmp, fAngle,
														 fFreq, k, nModuleIndex, dat + 8 + nDrvPos * 3 + nHarmIndex * 3 * 8);
							break;
						}
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleOffset].nDWcnt = 8 + nHarm * 3 * 8;
		}
	}
}

void State_Week_PNS331_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	long nTmtPos;
	float fFreCoef;
	float fWeekPT = 0;
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = 8;

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleOffset].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleOffset].nVal[i];
	}

	for(int k = 0; k < nTmtChanNum; k++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		nChPos = pModule->m_nChDrvPos[k];
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(nTmtPos >= 0)
		{
			tmt_channel &Tmtui = pTmt_channel[nTmtPos];

			if(Tmtui.Ramp[0].nIndex > 0)
			{
				fStart = fabs(Tmtui.Harm[1].fAmp);
				fEnd = fabs(Tmtui.Ramp[0].fEnd);
				fStep = fabs(Tmtui.Ramp[0].fStep);
				//幅值递变
				WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
									   pModule, k, 1);

				if(fStep > StateDegressMinStep)
				{
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 2] = nStepCount;
					float fChMax = 20;

					if(k < 4)
					{
						//Volt
						if(k == 3)
						{
							fChMax = 8.0;
						}
						else
						{
							fChMax = 4.0;
						}
					}
					else
					{
						//Current
						if(k == 7)
						{
							fChMax = 4;
						}
						else
						{
							fChMax = 20;
						}
					}

					fChMax = fChMax * 1.1;

					if(fWeekPT > EPSINON)
					{
						fStep = fStep / fWeekPT;
					}
					else
					{
						fStep = 0;
					}

					fStep = fStep / fChMax;
					unsigned int nAmp = fStep * 0xffffffff;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 2] = nSign * nAmp;
					long nHarm, nlastVal;
					//按照始值计算方式计算终值
					float fFreq = Tmtui.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					if(fWeekPT > EPSINON)
					{
						fEnd = fEnd / fWeekPT;
					}
					else
					{
						fEnd = 0;
					}

					nlastVal = TranslateACAmp_Week_PNS331(fEnd, k, nIndex, nHarm + 1);
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 2] = nlastVal;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[1].nIndex > 0)
			{
				//相位递变
				fStart = Tmtui.Harm[1].fAngle;
				fEnd = Tmtui.Ramp[1].fEnd;
				fStep = fabs(Tmtui.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[2].nIndex == 1)
			{
				//单波形输出频率递变
				fStart = fabs(Tmtui.Harm[1].fFreq);
				fEnd = fabs(Tmtui.Ramp[2].fEnd);
				fStep = fabs(Tmtui.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 1] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
					}

					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 1] = nSign * TranslateACFre(fStep * fFreCoef * 8);
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 1] = TranslateACFre(fEnd * fFreCoef * 8);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

int GetTapCode_PNS331(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap)
{
	int nRetTap = 0;
	float nValue;

	//4U
	for(int i = 0; i < 4; i++)
	{
		nTap[i] = 0;
	}

	//4I
	for(int i = 4; i < 8; i++)
	{
		if(bStateTest)
		{
			nRetTap |= PNS331_Tap[i][1];
			nTap[i] = 1;
			continue;
		}

		nValue = fabs(fMaxOut[i]);

		switch(i)
		{
			case 4:
			case 5:
			case 6:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 1.2001 * 1.414;
				}
				else
				{
					nTapValue = 1.201;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= PNS331_Tap[i][1];
					nTap[i] = 1;//fVoltMax = 20
				}
				else
				{
					nRetTap |= PNS331_Tap[i][0];
					nTap[i] = 0;//fVoltMax =1.2
				}
			}
			break;

			case 7:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 0.2401 * 1.414;
				}
				else
				{
					nTapValue = 0.2401;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= PNS331_Tap[i][1];
					nTap[i] = 1;//fVoltMax = 4
				}
				else
				{
					nRetTap |= PNS331_Tap[i][0];
					nTap[i] = 0;//fVoltMax =0.24
				}
			}
			break;
		}
	}

	return nRetTap;
}

//PN6U6I直流插件
void TransAnalogDCToDrv_Week_PN_DC6U6I(float fAmp, int nChannel, int nModuleIndex, long *pDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];
	int nDrvPos = pModule->m_nChDrvPos[nChannel];

	if(nChannel < 6)
	{
		//Volt
		if(nTap == 0)
		{
			fChMax = 0.2;
		}
		else
		{
			fChMax = 10;
		}
	}
	else
	{
		//Current
		if(nTap == 0)
		{
			fChMax = 0.001;
		}
		else
		{
			fChMax = 0.02;
		}
	}

	fChMax = fChMax * 1.2;
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0;//零漂
	float fDcZero = 0;//直流零漂

	if(pChsAdjust != NULL)
	{
		fDcZero = pChsAdjust->m_fDcZero[nTap];

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
				fZero = pAdjItem->m_fZero;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						fZero = pAdjItem->m_fZero;
						break;
					}
				}
			}
		}
	}

	/*************fAmp值补偿************/
	/******设置零漂******/
	float fValue;

	if(nChannel < 6)
	{
		fValue = -fDcZero;
	}
	else
	{
		fValue = fDcZero;
	}

	pDrvData[nDrvPos]  = fValue / fChMax * 0x7fffffff;
	/******设置零漂******/
	long  nPh;

	if(fAmp > 0 || fabs(fAmp) < EPSINON)
	{
		nPh = 90 * 65536 / 360;
	}
	else
	{
		nPh = 270 * 65536 / 360;
	}

	pDrvData[nDrvPos * 3 + 12] = nPh << 16;
	fAmp = fabs(fAmp);
	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		pDrvData[nDrvPos * 3 + 2 + 12] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值转FPGA参数************/
	fValue = fAmp * fCoef + fZero;
	fValue = fabs(fValue) / fChMax;

	if(fValue > 0.9999999)
	{
		pDrvData[nDrvPos * 3 + 12 + 2] = 0xffffffff;
	}
	else
	{
		unsigned long nH = fValue * 0xffffffff;
		pDrvData[nDrvPos * 3 + 12 + 2] = nH;
	}

	/*************fAmp值转FPGA参数************/
}

void Manual_Week_PN_DC6U6I(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nIndex, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	int nTmtPos;
	float fWeekPT = 0;
	float fMaxOut[12];

	for(int k = 0; k < 12; k++)
	{
		nTmtPos = k;

		if(bIsModuleOutput)
		{
			pTmt_channel = pTmt_Volt;
			fWeekPT = 1.0f;
		}
		else
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(k < 6)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(bIsModuleOutput)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					if(k < 6)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						if(fWeekPT > 1.001)
						{
							//电流分段变比
							if(fAmp > 0 || fabs(fAmp) < EPSINON)
							{
								fAmp = fAmp / fWeekPT;
								fAmp = (20 - 12) * fAmp / 20 + 0.012;
							}
							else
							{
								//负数段
								fAmp = fabs(fAmp) / fWeekPT;
								fAmp = 0.012 - (12 - 4) * fAmp / 20;
							}
						}
						else
						{
							fAmp = fAmp / fWeekPT;
						}
					}
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		fMaxOut[k] = fAmp;
	}

	g_nWeekTap = GetTapCode_PN_DC6U6I(fMaxOut, FALSE, WeekTap[nIndex]);

	for(int k = 0; k < 12; k++)
	{
		TransAnalogDCToDrv_Week_PN_DC6U6I(fMaxOut[k], k, nIndex, dat);
	}

	pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
}

void State_Week_PN_DC6U6I(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 12 * 3;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	int nTmtPos;
	float fWeekPT = 0;

	for(int k = 0; k < nTmtChanNum; k++)
	{
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
		}
		else
		{
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

			if(fWeekPT > EPSINON)
			{
				if(k < 6)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					if(fWeekPT > 1.001)
					{
						//电流分段变比
						if(fAmp > 0 || fabs(fAmp) < EPSINON)
						{
							fAmp = fAmp / fWeekPT;
							fAmp = (20 - 12) * fAmp / 20 + 0.012;
						}
						else
						{
							//负数段
							fAmp = fabs(fAmp) / fWeekPT;
							fAmp = 0.012 - (12 - 4) * fAmp / 20;
						}
					}
					else
					{
						fAmp = fAmp / fWeekPT;
					}
				}
			}
			else
			{
				fAmp = 0;
			}
		}

		TransAnalogDCToDrv_Week_PN_DC6U6I(fAmp, k, nIndex, dat);
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_PN_DC6U6I(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
								   BOOL bIsDc, int nStatus)
{
}

int GetTapCode_PN_DC6U6I(float *fMaxOut, BOOL bStateTest, int *nTap)
{
	int nRetTap = 0;

	//6U
	for(int i = 0; i < 6; i++)
	{
		if(fabs(fMaxOut[i]) > 0.2001 || bStateTest)
		{
			nRetTap |= PN_DC6U6I_Tap[i][1];
			nTap[i] = 1;//fVoltMax =10
		}
		else
		{
			nRetTap |= PN_DC6U6I_Tap[i][0];
			nTap[i] = 0;//fVoltMax =0.2
		}
	}

	//6I
	for(int i = 6; i < 12; i++)
	{
		if(fabs(fMaxOut[i]) > 0.001001 || bStateTest)
		{
			nRetTap |= PN_DC6U6I_Tap[i][1];
			nTap[i] = 1;//fVoltMax =0.02
		}
		else
		{
			nRetTap |= PN_DC6U6I_Tap[i][0];
			nTap[i] = 0;//fVoltMax =0.001
		}
	}

	return nRetTap;
}

//L336D
void TransAnalogDCToDrv_Week_L336D(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 8)
	{
		//Volt
		fChMax = 10.0;
	}
	else
	{
		//Current
		if(nTap == 0)
		{
			fChMax = 1;
		}
		else
		{
			fChMax = 20;
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[nTap];
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > EPSINON)
	{
		long nRef;

		if(bUseDcZero)
		{
			nRef = 0x7fffffff;
		}
		else
		{
			nRef = 0xffffffff;
		}

		fChMax = fChMax * 1.414;
		fAmp = fAmp / fChMax;

		if(fAmp > 0.9999999)
		{
			pDrvData[0] = nRef;
		}
		else
		{
			unsigned long nH = fAmp * nRef;
			pDrvData[0] = nH;
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long TranslateACAmp_Week_L336D(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel <8)
	{
		//Volt
		fChMax = 10.0;
	}
	else
	{
		//Current
		if(nTap == 0)
		{
			fChMax = 1;
		}
		else
		{
			fChMax = 20;
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					fCoef = pAdjItem->m_fCoef;
					fZero = pAdjItem->m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							fCoef = pAdjItem->m_fCoef;
							fZero = pAdjItem->m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > 0)
	{
		fAmp = fAmp / fChMax;

		if(fAmp > 0.999999)
		{
			return 0xffffffff;
		}
		else
		{
			unsigned long nH = fAmp * 0xffffffff;
			return nH;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void TransAnalogToDrv_Week_L336D(float fAmp, float fAng, float fFre, int nChannel,
								 int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_L336D(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef * 8);
	pnDrvData[2] = TranslateACAmp_Week_L336D(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_L336D(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
					   BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	long nTmtChanNum = 12;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;
	float fDcMaxOut[12];
	float fMaxOut[12];
	float fFreq[12];
	float fAngle[12];

	if(nHarm > 1)
	{
		g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
	}

	BOOL bTapDc[12];

	if(bIsDc)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			fDcMaxOut[k] = fAmp;
			bTapDc[k] = TRUE;
		}

		g_nWeekTap = GetTapCode_L336D(fDcMaxOut, FALSE, bTapDc, WeekTap[nIndex]);

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_L336D(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + 12 * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				fDcMaxOut[k] = fAmp;
			}
			//Base
			{
				bTapDc[k] = FALSE;

				if(nTmtPos < 0)
				{
					fMaxOut[k] = 0;
					fFreq[k] = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fMaxOut[k] = fAmp / fWeekPT;
					}
					else
					{
						fMaxOut[k] = 0;
					}

					fAngle[k] = oTmtHarm->fAngle;
					fFreq[k] = oTmtHarm->fFreq;

					if(fFreq[k] < EPSINON)
					{
						bTapDc[k] = TRUE;
					}
				}
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_L336D(fAmp, fAngle,
														fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + nHarmIndex * 3 * 12);
							break;
						}
					}
				}
			}
		}

		if(nHarm == 1)
		{
			g_nWeekTap = GetTapCode_L336D(fMaxOut, FALSE, bTapDc, WeekTap[nIndex]);
		}

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_L336D(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
			TransAnalogToDrv_Week_L336D(fMaxOut[k], fAngle[k],
										fFreq[k], k, nIndex, dat + 12 + nDrvPos * 3);
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 12 + nHarm * 3 * 12;
	}
}

void State_Week_L336D(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	tmt_channel *pTmt_channel;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 12 + 2 * 3 * 12;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	long nTmtChanNum = 12;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_L336D(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_L336D(fAmp, k, nIndex, dat + nDrvPos);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_L336D(fAmp, fAngle,
										fFreq, k, nIndex, dat + 12 + nDrvPos * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_L336D(fAmp, fAngle,
												fFreq, k, nIndex, dat + 12 + nDrvPos * 3 + 3 * 12);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_L336D(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
							   BOOL bIsDc, int nStatus)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nDrvPos;
	float fAmp, fAngle, fFreq;
	float fWeekPT = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		dat = pszDrv->para[nModuleOffset].bfChangedat;
	}
	else if(nStatus == 1)
	{
		dat = pszDrv->para[nModuleOffset].bfFaultdat;
	}
	else
	{
		dat = pszDrv->para[nModuleOffset].FaultBegindat;
	}

	tmt_channel *pTmt_channel;
	long nTmtPos;

	if(bIsDc)
	{
		for(int k = 0; k < 12; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];
			nDrvPos = pModule->m_nChDrvPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_L336D(fAmp, k, nModuleIndex, dat + nDrvPos);
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleOffset].nDWcnt = 12 + 12 * 3;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < 12; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				TransAnalogDCToDrv_Week_L336D(fAmp, k, nModuleIndex, dat + nDrvPos);
			}
			//Base
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
					fFreq = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
				}

				TransAnalogToDrv_Week_L336D(fAmp, fAngle,
											fFreq, k, nModuleIndex, dat + 12 + nDrvPos * 3);
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_L336D(fAmp, fAngle,
														fFreq, k, nModuleIndex, dat + 12 + nDrvPos * 3 + nHarmIndex * 3 * 12);
							break;
						}
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleOffset].nDWcnt = 12 + nHarm * 3 * 12;
		}
	}
}

void State_Week_L336D_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	long nTmtPos;
	float fFreCoef;
	float fWeekPT = 0;
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = 12;

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleOffset].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleOffset].nVal[i];
	}

	for(int k = 0; k < nTmtChanNum; k++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		nChPos = pModule->m_nChDrvPos[k];
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(nTmtPos >= 0)
		{
			tmt_channel &Tmtui = pTmt_channel[nTmtPos];

			if(Tmtui.Ramp[0].nIndex > 0)
			{
				fStart = fabs(Tmtui.Harm[1].fAmp);
				fEnd = fabs(Tmtui.Ramp[0].fEnd);
				fStep = fabs(Tmtui.Ramp[0].fStep);
				//幅值递变
				WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
									   pModule, k, 1);

				if(fStep > StateDegressMinStep)
				{
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 2] = nStepCount;
					float fChMax = 20;

					if(k < 8)
					{
						//Volt
						fChMax = 10.0;
					}
					else
					{
						//Current
						fChMax = 20.0;
					}

					fChMax = fChMax * 1.2;

					if(fWeekPT > EPSINON)
					{
						fStep = fStep / fWeekPT;
					}
					else
					{
						fStep = 0;
					}

					fStep = fStep / fChMax;
					unsigned int nAmp = fStep * 0xffffffff;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 2] = nSign * nAmp;
					long nHarm, nlastVal;
					//按照始值计算方式计算终值
					float fFreq = Tmtui.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					if(fWeekPT > EPSINON)
					{
						fEnd = fEnd / fWeekPT;
					}
					else
					{
						fEnd = 0;
					}

					nlastVal = TranslateACAmp_Week_L336D(fEnd, k, nIndex, nHarm + 1);
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 2] = nlastVal;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[1].nIndex > 0)
			{
				//相位递变
				fStart = Tmtui.Harm[1].fAngle;
				fEnd = Tmtui.Ramp[1].fEnd;
				fStep = fabs(Tmtui.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[2].nIndex == 1)
			{
				//单波形输出频率递变
				fStart = fabs(Tmtui.Harm[1].fFreq);
				fEnd = fabs(Tmtui.Ramp[2].fEnd);
				fStep = fabs(Tmtui.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 1] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
					}

					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 1] = nSign * TranslateACFre(fStep * fFreCoef * 8);
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 1] = TranslateACFre(fEnd * fFreCoef * 8);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

int GetTapCode_L336D(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc, int *nTap)
{
	int nRetTap = 0;
	float nValue;

	//8U
	for(int i = 0; i < 8; i++)
	{
		nTap[i] = 0;
	}

	//4I
	for(int i = 8; i < 12; i++)
	{
		if(bStateTest)
		{
			nRetTap |= L336D_Tap[i][1];
			nTap[i] = 1;
			continue;
		}

		nValue = fabs(fMaxOut[i]);
		float nTapValue;

		if(bTapDc[i])
		{
			nTapValue = 1.2001 * 1.414;
		}
		else
		{
			nTapValue = 1.2001;
		}

		if(nValue > nTapValue)
		{
			nRetTap |= L336D_Tap[i][1];
			nTap[i] = 1;//fVoltMax = 20
		}
		else
		{
			nRetTap |= L336D_Tap[i][0];
			nTap[i] = 0;//fVoltMax =1
		}
	}

	return nRetTap;
}

//ADMU
void TransAnalogDCToDrv_Week_ADMU(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			if(nTap == 0)
			{
				fChMax = 0.7;
			}
			else
			{
				fChMax = 7.8;
			}
		}
		else
		{
			fChMax = 3.8;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 0.1;
			}
			else if(nTap == 1)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[nTap];
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[0];
			PSTT_ADJUST_ITEM pAdjItem;

			if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
			{
				pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
				fCoef = pAdjItem->m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
				{
					if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
					{
						pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
						fCoef = pAdjItem->m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > EPSINON)
	{
		long nRef;

		if(bUseDcZero)
		{
			nRef = 0x7fffffff;
		}
		else
		{
			nRef = 0xffffffff;
		}

		fChMax = fChMax * 1.414;
		fAmp = fAmp / fChMax;

		if(fAmp > 0.9999999)
		{
			pDrvData[0] = nRef;
		}
		else
		{
			unsigned long nH = fAmp * nRef;
			pDrvData[0] = nH;
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long TranslateACAmp_Week_ADMU(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fChMax;
	int nTap = WeekTap[nModuleIndex][nChannel];

	if(nChannel < 4)
	{
		//Volt
		if(nChannel == 3)
		{
			if(nTap == 0)
			{
				fChMax = 0.7;
			}
			else
			{
				fChMax = 7.8;
			}
		}
		else
		{
			fChMax = 3.8;
		}
	}
	else
	{
		//Current
		if(nChannel == 7)
		{
			if(nTap == 0)
			{
				fChMax = 0.24;
			}
			else
			{
				fChMax = 4;
			}
		}
		else
		{
			if(nTap == 0)
			{
				fChMax = 0.1;
			}
			else if(nTap == 1)
			{
				fChMax = 1.2;
			}
			else
			{
				fChMax = 20;
			}
		}
	}

	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fChMax > (pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue + EPSINON))
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					fCoef = pAdjItem->m_fCoef;
					fZero = pAdjItem->m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fChMax < (pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue + EPSINON))
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							fCoef = pAdjItem->m_fCoef;
							fZero = pAdjItem->m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/
	/*************fAmp值转FPGA参数************/
	fChMax = fChMax * 1.2;

	if(fAmp > 0)
	{
		fAmp = fAmp / fChMax;

		if(fAmp > 0.999999)
		{
			return 0xffffffff;
		}
		else
		{
			unsigned long nH = fAmp * 0xffffffff;
			return nH;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void TransAnalogToDrv_Week_ADMU(float fAmp, float fAng, float fFre, int nChannel,
								 int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh;
		nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCToDrv_Week_ADMU(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust =
		stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if((nHarm + 1) < pChsAdjust->nHarmCount)
			{
				PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = &pChsAdjust->m_pChWaveAdj[nHarm + 1];
				PSTT_ADJUST_ITEM pAdjItem;

				if(fabs(fAmp) >= pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_fGearValue)
				{
					pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;
					faddPh = pAdjItem->m_fAngle;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < pChWaveAdj->m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
						{
							pAdjItem = &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
							faddPh = pAdjItem->m_fAngle;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef * 8);
	pnDrvData[2] = TranslateACAmp_Week_ADMU(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void Manual_Week_ADMU(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm, int nIndex,
					   BOOL bIsDc, BOOL bIsModuleOutput, int nTap)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_FT3;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	tmt_channel *pTmt_channel;
	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	float fAmp = 0;
	pDrv->oDrv_HarmParam[nModuleOffset].dat[0] = 1;//小信号片选
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[1];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;
	float fDcMaxOut[8];
	float fMaxOut[8];
	float fFreq[8];
	float fAngle[8];

	if(nHarm > 1)
	{
		g_nWeekTap = GetTapCode_ADMU(fMaxOut, TRUE, NULL, WeekTap[nIndex], nTap);
	}

	BOOL bTapDc[8];

	if(bIsDc)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			fDcMaxOut[k] = fAmp;
			bTapDc[k] = TRUE;
		}

		g_nWeekTap = GetTapCode_ADMU(fDcMaxOut, FALSE, bTapDc, WeekTap[nIndex], nTap);

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_ADMU(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 1 + 8 + 8 * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;

			if(bIsModuleOutput)
			{
				pTmt_channel = pTmt_Volt;
				fWeekPT = 1.0f;
			}
			else
			{
				nTmtPos = pModule->m_nChTmtPos[k];
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pTmt_channel = pTmt_Volt;
				}
				else
				{
					pTmt_channel = pTmt_Current;
				}
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				fDcMaxOut[k] = fAmp;
			}
			//Base
			{
				bTapDc[k] = FALSE;

				if(nTmtPos < 0)
				{
					fMaxOut[k] = 0;
					fFreq[k] = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fMaxOut[k] = fAmp / fWeekPT;
					}
					else
					{
						fMaxOut[k] = 0;
					}

					fAngle[k] = oTmtHarm->fAngle;
					fFreq[k] = oTmtHarm->fFreq;

					if(fFreq[k] < EPSINON)
					{
						bTapDc[k] = TRUE;
					}
				}
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_ADMU(fAmp, fAngle,
														fFreq, k, nIndex, dat + 8 + nDrvPos * 3 + nHarmIndex * 3 * 8);
							break;
						}
					}
				}
			}
		}

		if(nHarm == 1)
		{
			g_nWeekTap = GetTapCode_ADMU(fMaxOut, FALSE, bTapDc, WeekTap[nIndex], nTap);
		}

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			TransAnalogDCToDrv_Week_ADMU(fDcMaxOut[k], k, nIndex, dat + nDrvPos);
			TransAnalogToDrv_Week_ADMU(fMaxOut[k], fAngle[k],
										fFreq[k], k, nIndex, dat + 8 + nDrvPos * 3);
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 1 + 8 + nHarm * 3 * 8;
	}
}

void State_Week_ADMU(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_FT3;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];		

	if(pModule == NULL)
	{
		return;
	}

	tmt_channel *pTmt_channel;
	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.nPhase |= 3<<30;
	Voltanal.DWCount = 1 + 8 + 2 * 3 * 8;
	float fAmp;
	Voltanal.nVal[0] = 1;//小信号片选
	long *dat = &Voltanal.nVal[1];
	long nTmtChanNum = 8;
	int nTmtPos;
	float fWeekPT = 0;
	int nDrvPos;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
				fWeekPT = pModule->m_fChTmtCoef[k];

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_ADMU(fabs(fAmp), k, nIndex, dat + nDrvPos);
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < nTmtChanNum; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_ADMU(fAmp, k, nIndex, dat + nDrvPos);

			if(nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}

				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogToDrv_Week_ADMU(fAmp, fAngle,
										fFreq, k, nIndex, dat + 8 + nDrvPos * 3);

			if(nTmtPos < 0)
			{
				continue;
			}

			BOOL bHarm;

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogToDrv_Week_ADMU(fAmp, fAngle,
												fFreq, k, nIndex, dat + 8 + nDrvPos * 3 + 3 * 8);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Voltanal, sizeof(structACParamItem));
}

void Gradient_NormalWeek_ADMU(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm, int nModuleIndex,
							   BOOL bIsDc, int nStatus)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_FT3;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nDrvPos;
	float fAmp, fAngle, fFreq;
	float fWeekPT = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		pszDrv->para[nModuleOffset].bfChangedat[0] = 1;
		dat = pszDrv->para[nModuleOffset].bfChangedat + 1;
	}
	else if(nStatus == 1)
	{
		pszDrv->para[nModuleOffset].bfFaultdat[0] = 1;
		dat = pszDrv->para[nModuleOffset].bfFaultdat + 1;
	}
	else
	{
		pszDrv->para[nModuleOffset].FaultBegindat[0] = 1;
		dat = pszDrv->para[nModuleOffset].FaultBegindat + 1;
	}

	tmt_channel *pTmt_channel;
	long nTmtPos;

	if(bIsDc)
	{
		for(int k = 0; k < 8; k++)
		{
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];
			nDrvPos = pModule->m_nChDrvPos[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			if(nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;

				if(fWeekPT > EPSINON)
				{
					fAmp = fAmp / fWeekPT;
				}
				else
				{
					fAmp = 0;
				}
			}

			TransAnalogDCToDrv_Week_ADMU(fAmp, k, nModuleIndex, dat + nDrvPos);
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleOffset].nDWcnt = 1 + 8 + 8 * 3;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;

		for(int k = 0; k < 8; k++)
		{
			nDrvPos = pModule->m_nChDrvPos[k];
			nTmtPos = k;
			nTmtPos = pModule->m_nChTmtPos[k];
			fWeekPT = pModule->m_fChTmtCoef[k];

			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
			}
			else
			{
				pTmt_channel = pTmt_Current;
			}

			//DC
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[nTmtPos].Harm[0].fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}
				}

				TransAnalogDCToDrv_Week_ADMU(fAmp, k, nModuleIndex, dat + nDrvPos);
			}
			//Base
			{
				if(nTmtPos < 0)
				{
					fAmp = 0;
					fFreq = 50;
				}
				else
				{
					oTmtHarm = &pTmt_channel[nTmtPos].Harm[1];
					fAmp = oTmtHarm->fAmp;

					if(fWeekPT > EPSINON)
					{
						fAmp = fAmp / fWeekPT;
					}
					else
					{
						fAmp = 0;
					}

					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
				}

				TransAnalogToDrv_Week_ADMU(fAmp, fAngle,
											fFreq, k, nModuleIndex, dat + 8 + nDrvPos * 3);
			}

			if(nTmtPos < 0)
			{
				continue;
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				float fAngle, fFreq;

				for(int nHarmIndex = 1; nHarmIndex < 31; nHarmIndex++)
				{
					for(int j = 2; j < nHarmCount; j++)
					{
						if(nHarmIndex == pTmt_channel[nTmtPos].Harm[j].nSelectIndex)
						{
							oTmtHarm = &pTmt_channel[nTmtPos].Harm[j];
							fAmp = oTmtHarm->fAmp;

							if(fWeekPT > EPSINON)
							{
								fAmp = fAmp / fWeekPT;
							}
							else
							{
								fAmp = 0;
							}

							fAngle = oTmtHarm->fAngle;
							fFreq = oTmtHarm->fFreq;
							TransAnalogToDrv_Week_ADMU(fAmp, fAngle,
														fFreq, k, nModuleIndex, dat + 8 + nDrvPos * 3 + nHarmIndex * 3 * 8);
							break;
						}
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleOffset].nDWcnt = 1 + 8 + nHarm * 3 * 8;
		}
	}
}

void State_Week_ADMU_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState, int nIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_FT3;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	long nTmtPos,nTempPos;
	float fFreCoef;
	float fWeekPT = 0;
	long nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = 8;

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleOffset].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleOffset].nVal[i];
	}

	for(int k = 0; k < nTmtChanNum; k++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
		}

		nChPos = pModule->m_nChDrvPos[k];
		nTmtPos = pModule->m_nChTmtPos[k];
		fWeekPT = pModule->m_fChTmtCoef[k];

		if(nTmtPos >= 0)
		{
			tmt_channel &Tmtui = pTmt_channel[nTmtPos];

			if(Tmtui.Ramp[0].nIndex > 0)
			{
				nTempPos = nChanSize + nChPos * 3 + 2;
				nTempPos += 1;
				fStart = fabs(Tmtui.Harm[1].fAmp);
				fEnd = fabs(Tmtui.Ramp[0].fEnd);
				fStep = fabs(Tmtui.Ramp[0].fStep);
				//幅值递变
				WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
									   pModule, k, 1);

				if(fStep > StateDegressMinStep)
				{
					oDrvStateDeg.nCount[nTempPos] = nStepCount;
					float fChMax = 20;

					if(k < 4)
					{
						//Volt
						fChMax = 7.8;
					}
					else
					{
						//Current
						fChMax = 20.0;
					}

					fChMax = fChMax * 1.2;

					if(fWeekPT > EPSINON)
					{
						fStep = fStep / fWeekPT;
					}
					else
					{
						fStep = 0;
					}

					fStep = fStep / fChMax;
					unsigned int nAmp = fStep * 0xffffffff;
					oDrvStateDeg.changeVal[nTempPos] = nSign * nAmp;
					long nHarm, nlastVal;
					//按照始值计算方式计算终值
					float fFreq = Tmtui.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					if(fWeekPT > EPSINON)
					{
						fEnd = fEnd / fWeekPT;
					}
					else
					{
						fEnd = 0;
					}

					nlastVal = TranslateACAmp_Week_ADMU(fEnd, k, nIndex, nHarm + 1);
					oDrvStateDeg.lastVal[nTempPos] = nlastVal;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[1].nIndex > 0)
			{
				//相位递变
				nTempPos = nChanSize + nChPos * 3;
				nTempPos += 1;
				fStart = Tmtui.Harm[1].fAngle;
				fEnd = Tmtui.Ramp[1].fEnd;
				fStep = fabs(Tmtui.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nTempPos] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[nTempPos] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[nTempPos] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[2].nIndex == 1)
			{
				//单波形输出频率递变
				nTempPos = nChanSize + nChPos * 3 + 1;
				nTempPos += 1;
				fStart = fabs(Tmtui.Harm[1].fFreq);
				fEnd = fabs(Tmtui.Ramp[2].fEnd);
				fStep = fabs(Tmtui.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
										   pModule, k, 1);
					oDrvStateDeg.nCount[nTempPos] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
					}

					oDrvStateDeg.changeVal[nTempPos] = nSign * TranslateACFre(fStep * fFreCoef * 8);
					oDrvStateDeg.lastVal[nTempPos] = TranslateACFre(fEnd * fFreCoef * 8);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

int GetTapCode_ADMU(float *fMaxOut, BOOL bStateTest, BOOL *bTapDc,int *nCalTap, int nUserSetTap)
{
	int nRetTap = 0;
	float nValue;

	//4U
	for(int i = 0; i < 4; i++)
	{
		if(bStateTest)
		{
			nRetTap |= ADMU_Tap[i][1];
			nCalTap[i] = 2;
			continue;
		}

		nValue = fabs(fMaxOut[i]);

		switch(i)
		{
			case 0:
			case 1:
			case 2:
			{
				nRetTap |= ADMU_Tap[i][0];
				nCalTap[i] = 0;//fVoltMax =3.8
			}
			break;

			case 3:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 0.7001 * 1.414;
				}
				else
				{
					nTapValue = 0.7001;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= ADMU_Tap[i][1];
					nCalTap[i] = 1;//fVoltMax = 7.8
				}
				else
				{
					if(nValue < EPSINON)
					{
						//零值输出，校准零漂时指定档位
						if(nUserSetTap == 0)
						{
							nRetTap |= ADMU_Tap[i][0];
							nCalTap[i] = 0;//fVoltMax =0.7
						}
						else
						{
							nRetTap |= ADMU_Tap[i][1];
							nCalTap[i] = 1;//fVoltMax =7.8
						}
					}
					else
					{
						nRetTap |= ADMU_Tap[i][0];
						nCalTap[i] = 0;//fVoltMax =0.7
					}
				}
			}
			break;
		}
	}

	//4I
	for(int i = 4; i < 8; i++)
	{
		if(bStateTest)
		{
			nRetTap |= ADMU_Tap[i][2];
			nCalTap[i] = 2;
			continue;
		}

		nValue = fabs(fMaxOut[i]);

		switch(i)
		{
			case 4:
			case 5:
			case 6:
			{
				float nTapValue_l, nTapValue_m;

				if(bTapDc[i])
				{
					nTapValue_l = 0.1001 * 1.414;
					nTapValue_m = 1.2001 * 1.414;
				}
				else
				{
					nTapValue_l = 0.1001;
					nTapValue_m = 1.2001;
				}

				if(nValue > nTapValue_m)
				{
					nRetTap |= ADMU_Tap[i][2];
					nCalTap[i] = 2;//fVoltMax = 20
				}
				else if(nValue > nTapValue_l)
				{
					nRetTap |= ADMU_Tap[i][1];
					nCalTap[i] = 1;//fVoltMax = 1.2
				}
				else
				{
					if(nValue < EPSINON)
					{
						//零值输出，校准零漂时指定档位
						if(nUserSetTap == 0)
						{
							nRetTap |= ADMU_Tap[i][0];
							nCalTap[i] = 0;//fVoltMax =0.1
						}
						else if(nUserSetTap == 1)
						{
							nRetTap |= ADMU_Tap[i][1];
							nCalTap[i] = 1;//fVoltMax = 1.2
						}
						else
						{
							nRetTap |= ADMU_Tap[i][2];
							nCalTap[i] = 2;//fVoltMax = 20
						}
					}
					else
					{
						nRetTap |= ADMU_Tap[i][0];
						nCalTap[i] = 0;//fVoltMax =0.1
					}
				}
			}
			break;

			case 7:
			{
				float nTapValue;

				if(bTapDc[i])
				{
					nTapValue = 0.2401 * 1.414;
				}
				else
				{
					nTapValue = 0.2401;
				}

				if(nValue > nTapValue)
				{
					nRetTap |= ADMU_Tap[i][1];
					nCalTap[i] = 1;//fVoltMax = 4
				}
				else
				{
					if(nValue < EPSINON)
					{
						//零值输出，校准零漂时指定档位
						if(nUserSetTap == 0)
						{
							nRetTap |= ADMU_Tap[i][0];
							nCalTap[i] = 0;//fVoltMax =0.24
						}
						else
						{
							nRetTap |= ADMU_Tap[i][1];
							nCalTap[i] = 1;//fVoltMax = 4
						}
					}
					else
					{
						nRetTap |= ADMU_Tap[i][0];
						nCalTap[i] = 0;//fVoltMax =0.24
					}

				}
			}
			break;
		}
	}

	return nRetTap;
}
