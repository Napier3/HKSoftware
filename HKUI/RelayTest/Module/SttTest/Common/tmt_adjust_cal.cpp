#include "stdafx.h"
#include "tmt_adjust_cal.h"
#include "tmt_adjust_sys_parameter.h"
//#ifdef _PSX_QT_LINUX_
#include "math.h"
//#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, long nChannel,long nTempretureID,
							   long &nGearID, long &nFreqSel,TMT_ADJ_CHANNEL_VECTOR_EX &oVector)
{
	if (nChannel < 0 || nChannel >= ADJUST_MAX_CHANNEL_COUNT)
	{
		return false;
	}

	//TMT_ADJ_CHANNEL_VECTOR *pVector = &pParas->m_oChannels[nChannel].m_harm[nFreqSel];
	TMT_ADJ_CHANNEL_VECTOR *pVector = &pParas->m_oChannels[nChannel].m_oVector;
	oVector.m_fMag = pVector->m_fMag;
	oVector.m_fAngle = pVector->m_fAngle;
	oVector.m_fFreq = pParas->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	PSTT_MODULE pModule=stt_adj_find_module_byModulePos(g_theDeviceSystemParameter, pParas->m_nModuleIndex, pParas->m_nModuleType);
	if(pModule==NULL)
		return false;

	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
	if (nTempretureID > 0)
	{//温区有效，则获取温区的参数
		if (nTempretureID < 0 || nTempretureID >= ADJUST_MAX_TEMPRERATURE_COUNT)
		{
			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
		}
		else
		{
			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[nTempretureID];
		}
	}
	else
	{
		pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
	}

	PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj=
			&pTemperatureAdj->m_oChsAdjust[nChannel].m_oChWaveAdj[pParas->m_nFreqIndex];

	nGearID=pChWaveAdj->m_nGearCount-1;
	for(int nGearIndex=0;nGearIndex<pChWaveAdj->m_nGearCount;nGearIndex++)
	{
		if(oVector.m_fMag <= pChWaveAdj->m_oChGearAdj[nGearIndex].m_fGearValue)
		{
			nGearID=nGearIndex;
			break;
		}
	}

	nFreqSel=pParas->m_nFreqIndex;
	return true;
}

bool stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector)
{
	return stt_adj_get_output_vector(pParas
									 , oAdjCalVector.m_oAdjParas.m_nChannel
									 , oAdjCalVector.m_oAdjParas.m_nTempretureID
									 , oAdjCalVector.m_oAdjParas.m_nGearID
									 , oAdjCalVector.m_oAdjParas.m_nFreqSel
									 , oAdjCalVector.m_oOutputVector);
}

bool stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector)
{
	bool b1 = stt_adj_get_output_vector(pParas
										, oAdjCalVector.m_oAdjParas.m_nChannel
										, oAdjCalVector.m_oAdjParas.m_nTempretureID
										, oAdjCalVector.m_oAdjParas.m_nGearID
										, oAdjCalVector.m_oAdjParas.m_nFreqSel
										, oAdjCalVector.m_oOutputVector[0]);
	bool b2 = stt_adj_get_output_vector(pParas
										, oAdjCalVector.m_oAdjParas.m_nChannel2
										, oAdjCalVector.m_oAdjParas.m_nTempretureID
										, oAdjCalVector.m_oAdjParas.m_nGearID2
										, oAdjCalVector.m_oAdjParas.m_nFreqSel
										, oAdjCalVector.m_oOutputVector[1]);
	bool b3 = stt_adj_get_output_vector(pParas
										, oAdjCalVector.m_oAdjParas.m_nChannel3
										, oAdjCalVector.m_oAdjParas.m_nTempretureID
										, oAdjCalVector.m_oAdjParas.m_nGearID3
										, oAdjCalVector.m_oAdjParas.m_nFreqSel
										, oAdjCalVector.m_oOutputVector[2]);

	return b1 && b2 && b3;
}
// 
// PSTT_MODULE stt_adj_find_module(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleIndex, long nModuleType)
// {
//     long nFindeIndex = 0;
//     long nIndex = 0;
// 
//     for (nIndex=0; nIndex<pDvSysParas->m_nModuleCount; nIndex++)
//     {
//        if (nModuleType == pDvSysParas->m_oModules[nIndex].m_oModuleAttr.m_nModuleType)
//        {
//            if (nFindeIndex == nModuleIndex)
//            {
//                return &pDvSysParas->m_oModules[nIndex];
//            }
//        }
//     }
// 
//     return NULL;
// }
// 
// PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_TRANGE_ADJUST  pTemperatureAdj, long nChannel, long nFreqSel)
// {
// 	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = NULL;
// 
// 	if (ADJUST_CHANNEL_INDEX_IDC == nChannel)
// 	{
// 		pChWaveAdj = &pTemperatureAdj->m_oChIdcAdj;
// 	}
// 	else if (ADJUST_CHANNEL_INDEX_UDC == nChannel)
// 	{
// 		pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
// 	}
// 	else if (nChannel < 0 || nChannel >= ADJUST_MAX_CHANNEL_COUNT)
// 	{//直流通道
// 		pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
// 	}
// 	else
// 	{//基波和谐波波形
// 		if (nFreqSel < 0 || nFreqSel >= ADJUST_MAX_HARM_COUNT)
// 		{
// 			return NULL;
// 		}
// 		else
// 		{//根据通道和波形次数，得到波形校准系数
// 			pChWaveAdj = &pTemperatureAdj->m_oChsAdjust[nChannel].m_oChWaveAdj[nFreqSel];
// 		}
// 	}
// }
// 
// PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleType,  long nModule, long nTempretureID, long nChannel, long nFreqSel)
// {
// 	if (nModule < 0 || nModule >= ADJUST_MAX_MODULE_COUNT)
// 	{
// 		return NULL;
// 	}
// 
// 	PSTT_MODULE pModule = stt_adj_find_module(pDvSysParas, nModule, nModuleType);
// 
// 	if (pModule == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
// 	PSTT_CHANNEL_ADJUSTS  pChannelAdjs = NULL;
// 	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = NULL;
// 
// 	if (nTempretureID > 0)
// 	{//温区有效，则获取温区的参数
// 		if (nTempretureID < 0 || nTempretureID >= ADJUST_MAX_TEMPRERATURE_COUNT)
// 		{
// 			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
// 		}
// 		else
// 		{
// 			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[nTempretureID];
// 		}
// 	}
// 	else
// 	{
// 		pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
// 	}
// 
// 	pChWaveAdj = stt_adj_find_ch_wave(pTemperatureAdj, nChannel, nFreqSel);
// // 	if (ADJUST_CHANNEL_INDEX_IDC == nChannel)
// // 	{
// // 		pChWaveAdj = &pTemperatureAdj->m_oChIdcAdj;
// // 	}
// // 	else if (ADJUST_CHANNEL_INDEX_UDC == nChannel)
// // 	{
// // 		pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
// // 	}
// // 	else if (nChannel < 0 || nChannel >= ADJUST_MAX_CHANNEL_COUNT)
// // 	{//直流通道
// // 		pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
// // 	}
// // 	else
// // 	{//基波和谐波波形
// // 		if (nFreqSel < 0 || nFreqSel >= ADJUST_MAX_HARM_COUNT)
// // 		{
// // 			return NULL;
// // 		}
// // 		else
// // 		{//根据通道和波形次数，得到波形校准系数
// // 			pChWaveAdj = &pTemperatureAdj->m_oChsAdjust[nChannel].m_oChWaveAdj[nFreqSel];
// // 		}
// // 	}
// 
// 	return pChWaveAdj;
// }
// 
// PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleType,  long nModule, long nTempretureID, long nChannel, long nFreqSel, float fMaxMag)
// {
// 	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = stt_adj_find_ch_wave(pDvSysParas, nModuleType, nModule, nTempretureID, nChannel, nFreqSel);
// 
// 	if (pChWaveAdj == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	if (pChWaveAdj->m_nGearCount <= 1)
// 	{
// 		return &pChWaveAdj->m_oChGearAdj[0].m_oAdjItem;
// 	}
// 
// 	for (long nIndex=0; nIndex<pChWaveAdj->m_nGearCount; nIndex++)
// 	{
// 		if (fMaxMag < pChWaveAdj->m_oChGearAdj[nIndex].m_fGearValue)
// 		{
// 			return &pChWaveAdj->m_oChGearAdj[nIndex].m_oAdjItem;
// 		}
// 	}
// 
// 	return &pChWaveAdj->m_oChGearAdj[0].m_oAdjItem;
// }
// 
// PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModuleType,  long nModule, long nTempretureID, long nChannel, long nFreqSel, long nGearID)
// {
// 	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = stt_adj_find_ch_wave(pDvSysParas, nModuleType, nModule, nTempretureID, nChannel, nFreqSel);
// 
// 	if (pChWaveAdj == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	//档位
// 	if (nGearID < 0 || nGearID >= ADJUST_MAX_GEAR_COUNT)
// 	{
// 		return &pChWaveAdj->m_oChGearAdj[0].m_oAdjItem;
// 	}
// 	else
// 	{
// 		return &pChWaveAdj->m_oChGearAdj[nGearID].m_oAdjItem;
// 	}
// }
// 
// 
PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,  TMT_ADJUST_ONE_PARAS &oAdjOneParas)
{
//	if (oAdjOneParas.m_nModule < 0 || oAdjOneParas.m_nModule >= ADJUST_MAX_MODULE_COUNT)
//	{
//		return NULL;
//	}

	PSTT_MODULE pModule= NULL;
	pModule=stt_adj_find_module_byModulePos(pDvSysParas,oAdjOneParas.m_nModule,oAdjOneParas.m_nModuleType);

	if (pModule == NULL)
	{
		return NULL;
	}

	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
	PSTT_CHANNEL_ADJUSTS  pChannelAdjs = NULL;
	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = NULL;

	if (oAdjOneParas.m_nTempretureID > 0)
	{//温区有效，则获取温区的参数
		if (oAdjOneParas.m_nTempretureID < 0 || oAdjOneParas.m_nTempretureID >= ADJUST_MAX_TEMPRERATURE_COUNT)
		{
			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
		}
		else
		{
			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[oAdjOneParas.m_nTempretureID];
		}
	}
	else
	{
		pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
	}

	pChWaveAdj = stt_adj_find_ch_wave(pTemperatureAdj, oAdjOneParas.m_nChannel, oAdjOneParas.m_nFreqSel);

	//     if (oAdjOneParas.m_nChannel < 0 || oAdjOneParas.m_nChannel >= ADJUST_MAX_CHANNEL_COUNT)
	//     {//直流通道
	//         pChWaveAdj = &pTemperatureAdj->m_oChDCAdj;
	//     }
	//     else
	//     {//基波和谐波波形
	//         if (oAdjOneParas.m_nFreqSel < 0 || oAdjOneParas.m_nFreqSel >= ADJUST_MAX_HARM_COUNT)
	//         {
	//             return NULL;
	//         }
	//         else
	//         {//根据通道和波形次数，得到波形校准系数
	//             pChWaveAdj = &pTemperatureAdj->m_oChsAdjust[oAdjOneParas.m_nChannel].m_oChWaveAdj[oAdjOneParas.m_nFreqSel];
	//         }
	//     }

	if (pChWaveAdj == NULL)
	{
		return NULL;
	}

	//档位
	if (oAdjOneParas.m_nGearID < 0 || oAdjOneParas.m_nGearID >= ADJUST_MAX_GEAR_COUNT)
	{
		return &pChWaveAdj->m_oChGearAdj[0].m_oAdjItem;
	}
	else
	{
		return &pChWaveAdj->m_oChGearAdj[oAdjOneParas.m_nGearID].m_oAdjItem;
	}
}

bool stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector)
{
	oAdjCalVector.m_pAdjResults = stt_adj_find_adjust_item(pDvSysParas, oAdjCalVector.m_oAdjParas);

	if ( oAdjCalVector.m_pAdjResults == NULL)
	{
		return false;
	}

	return true;
}

void stt_adj_get_para_one_from_three(TMT_ADJUST_THREE_PARAS *pParasSrc , long nIndex, TMT_ADJUST_ONE_PARAS *pParasDest)
{
	memcpy(pParasDest, pParasSrc, sizeof(TMT_ADJUST_ONE_PARAS));

	if (nIndex == 1)
	{
		pParasDest->m_nChannel = pParasSrc->m_nChannel2;
		pParasDest->m_nGearID = pParasSrc->m_nGearID2;
		pParasDest->m_fMag = pParasSrc->m_fMag2;
		pParasDest->m_fAng = pParasSrc->m_fAng2;
		pParasDest->m_fFreq = pParasSrc->m_fFreq2;
	}
	else  if (nIndex == 2)
	{
		pParasDest->m_nChannel = pParasSrc->m_nChannel3;
		pParasDest->m_nGearID = pParasSrc->m_nGearID3;
		pParasDest->m_fMag = pParasSrc->m_fMag3;
		pParasDest->m_fAng = pParasSrc->m_fAng3;
		pParasDest->m_fFreq = pParasSrc->m_fFreq3;
	}
}

bool stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector)
{
	if(pDvSysParas==NULL)
		return false;

	TMT_ADJUST_ONE_PARAS oAdjOneParas;

	oAdjCalVector.m_pAdjResults[0] = stt_adj_find_adjust_item(pDvSysParas, oAdjCalVector.m_oAdjParas);
	if(oAdjCalVector.m_pAdjResults[0] == NULL)
		return false;

	stt_adj_get_para_one_from_three(&oAdjCalVector.m_oAdjParas, 1, &oAdjOneParas);
	oAdjCalVector.m_pAdjResults[1] = stt_adj_find_adjust_item(pDvSysParas, oAdjOneParas);
	if(oAdjCalVector.m_pAdjResults[1] == NULL)
		return false;

	stt_adj_get_para_one_from_three(&oAdjCalVector.m_oAdjParas, 2, &oAdjOneParas);
	oAdjCalVector.m_pAdjResults[2] = stt_adj_find_adjust_item(pDvSysParas, oAdjOneParas);
	if(oAdjCalVector.m_pAdjResults[2] == NULL)
		return false;

	return true;
}

//根据模块输出参数、校准参数，计算校准系数
bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_ONE poAdjParas)
{
	TMT_ADJ_CAL_VECTOR oAdjCalVector;
	memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR));
	oAdjCalVector.m_oAdjParas = poAdjParas->m_oParas;

	if (!stt_adj_get_output_vector(pModuleOutput, oAdjCalVector))
	{
		return false;
	}

	if (!stt_adj_get_adjust_item_ref(pDvSysParas, oAdjCalVector))
	{
		return false;
	}

	if(oAdjCalVector.m_oOutputVector.m_fMag<0.1&&oAdjCalVector.m_oOutputVector.m_fFreq<0.1)
	{
		//DCzero
		PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, poAdjParas->m_oParas.m_nModule, poAdjParas->m_oParas.m_nModuleType);

		if(pModule==NULL)
			return false;

		PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
		if (poAdjParas->m_oParas.m_nTempretureID > 0)
		{//温区有效，则获取温区的参数
			if (poAdjParas->m_oParas.m_nTempretureID < 0 || poAdjParas->m_oParas.m_nTempretureID >= ADJUST_MAX_TEMPRERATURE_COUNT)
			{
				pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
			}
			else
			{
				pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[poAdjParas->m_oParas.m_nTempretureID];
			}
		}
		else
		{
			pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
		}

		PSTT_CHANNEL_ADJUSTS pChanAdjust=NULL;
		if (poAdjParas->m_oParas.m_nChannel < 0 || poAdjParas->m_oParas.m_nChannel >= ADJUST_MAX_CHANNEL_COUNT)
		{
			pChanAdjust=&pTemperatureAdj->m_oChsAdjust[0];
		}
		else
			pChanAdjust=&pTemperatureAdj->m_oChsAdjust[poAdjParas->m_oParas.m_nChannel];

		float fCalZero=pChanAdjust->m_fDcZero+oAdjCalVector.m_oAdjParas.m_fMag;
		if(fabs(fCalZero)>0.1)
		{//零漂计算的结果超范围
			poAdjParas->m_oResult.m_oResult.m_fZero=fCalZero;
			poAdjParas->m_oResult.m_oResult.m_fCoef=-1;
			poAdjParas->m_oResult.m_oResult.m_fAngle=0;
		}
		else
		{
			pChanAdjust->m_fDcZero=fCalZero;
			poAdjParas->m_oResult.m_oResult.m_fZero=pChanAdjust->m_fDcZero;
			poAdjParas->m_oResult.m_oResult.m_fCoef=1;
			poAdjParas->m_oResult.m_oResult.m_fAngle=0;
		}
	}
//频率采用手动修改配置文件方式，软件校准容易因表计误差导致相角差不稳定
//	else if(fabs(oAdjCalVector.m_oAdjParas.m_fAng-360)<0.001&&oAdjCalVector.m_oAdjParas.m_nChannel==0)
//	{
//		//电压电流模块的频率补偿后需同时满足精度要求，否则会导致相位校准偏差
//		//fFreq
//		PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, poAdjParas->m_oParas.m_nModule, poAdjParas->m_oParas.m_nModuleType);

//		if(pModule==NULL)
//			return false;

//		float fFre=1;
//		fFre=oAdjCalVector.m_oOutputVector.m_fFreq/oAdjCalVector.m_oAdjParas.m_fFreq;
//		fFre=fFre*pModule->m_oModuleAttr.m_fFreCoef;
//		if(fFre<0.7||fFre>1.2)
//		{
//			poAdjParas->m_oResult.m_oResult.m_fCoef=-1;
//		}
//		else
//		{
//			pModule->m_oModuleAttr.m_fFreCoef=fFre;
//			poAdjParas->m_oResult.m_oResult.m_fCoef=fFre;
//		}

//		poAdjParas->m_oResult.m_oResult.m_fZero=0;
//		poAdjParas->m_oResult.m_oResult.m_fAngle=0;
//	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Coef=%f"),oAdjCalVector.m_pAdjResults->m_fCoef);

		//AC DC fMag
		if(stt_adj_vector_cal(oAdjCalVector))
		{
			poAdjParas->m_oResult.m_oResult.m_fCoef=oAdjCalVector.m_pAdjResults->m_fCoef;
		}
		else
		{
			poAdjParas->m_oResult.m_oResult.m_fCoef=-1;
		}

		poAdjParas->m_oResult.m_oResult.m_fAngle=0;
		poAdjParas->m_oResult.m_oResult.m_fZero=0;
	}

	return true;
}

bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULECH_OUTPUT pModuleChOutput, PTMT_ADJUST_ONE2POINTS poAdjParas)
{
	return false;
}

bool stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_THREE poAdjParas)
{
	TMT_ADJ_CAL_VECTOR_THREE oAdjCalVector;
	memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR_THREE));
	oAdjCalVector.m_oAdjParas = poAdjParas->m_oParas;

	if (!stt_adj_get_output_vector(pModuleOutput, oAdjCalVector))
	{
		return false;
	}

	if (!stt_adj_get_adjust_item_ref(pDvSysParas, oAdjCalVector))
	{
		return false;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("A Coef=%f,Ang=%f"),oAdjCalVector.m_pAdjResults[0]->m_fCoef,oAdjCalVector.m_pAdjResults[0]->m_fAngle);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("B Coef=%f,Ang=%f"),oAdjCalVector.m_pAdjResults[1]->m_fCoef,oAdjCalVector.m_pAdjResults[1]->m_fAngle);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("C Coef=%f,Ang=%f"),oAdjCalVector.m_pAdjResults[2]->m_fCoef,oAdjCalVector.m_pAdjResults[2]->m_fAngle);

	//大电流幅值校准
	if(oAdjCalVector.m_oAdjParas.m_nLargeCurrent>0)
	{
		if(oAdjCalVector.m_oAdjParas.m_nModuleType==STT_MODULE_TYPE_VOLT)
		{
			return false;
		}

		float fMag[3];
		float fCoef=1;
		fMag[0]=oAdjCalVector.m_oAdjParas.m_fMag;
		fMag[1]=oAdjCalVector.m_oAdjParas.m_fMag2;
		fMag[2]=oAdjCalVector.m_oAdjParas.m_fMag3;
		int nChannel[3];
		nChannel[0]=oAdjCalVector.m_oAdjParas.m_nChannel;
		nChannel[1]=oAdjCalVector.m_oAdjParas.m_nChannel2;
		nChannel[2]=oAdjCalVector.m_oAdjParas.m_nChannel3;

		for(int nIndex=0;nIndex<3;nIndex++)
		{
			if(nChannel[nIndex]<0||nChannel[nIndex]>=ADJUST_MAX_CHANNEL_COUNT||fMag[nIndex]<0.1)
			{
				poAdjParas->m_oResults.m_oResult[nIndex].m_fCoef=-1;
				poAdjParas->m_oResults.m_oResult[nIndex].m_fAngle=0;
				poAdjParas->m_oResults.m_oResult[nIndex].m_fZero=0;
				continue;
			}

			PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, poAdjParas->m_oParas.m_nModule, poAdjParas->m_oParas.m_nModuleType);

			if(pModule==NULL)
				return false;

			PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
			if (poAdjParas->m_oParas.m_nTempretureID > 0)
			{//温区有效，则获取温区的参数
				if (poAdjParas->m_oParas.m_nTempretureID < 0 || poAdjParas->m_oParas.m_nTempretureID >= ADJUST_MAX_TEMPRERATURE_COUNT)
				{
					pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
				}
				else
				{
					pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[poAdjParas->m_oParas.m_nTempretureID];
				}
			}
			else
			{
				pTemperatureAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0];
			}

			PSTT_CHANNEL_ADJUSTS pChanAdjust=&pTemperatureAdj->m_oChsAdjust[nChannel[nIndex]];

			fCoef=oAdjCalVector.m_oOutputVector[nIndex].m_fMag/fMag[nIndex];
			fCoef=pChanAdjust->m_fLargeCurrentRatio*fCoef;
			if(fCoef>1.2)
			{
				poAdjParas->m_oResults.m_oResult[nIndex].m_fCoef=-1;
			}
			else
			{
				pChanAdjust->m_fLargeCurrentRatio=fCoef;
				poAdjParas->m_oResults.m_oResult[nIndex].m_fCoef=fCoef;
			}

			poAdjParas->m_oResults.m_oResult[nIndex].m_fAngle=0;
			poAdjParas->m_oResults.m_oResult[nIndex].m_fZero=0;
		}
	}
	else
		stt_adj_vector_cal(oAdjCalVector,poAdjParas->m_oResults);

	return true;
}

//根据校准计算参数结构体，计算校准系数
bool stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR &oAdjCalVector)
{
	//AC DC fMag
	float fCoef=oAdjCalVector.m_oOutputVector.m_fMag/oAdjCalVector.m_oAdjParas.m_fMag;

	fCoef=oAdjCalVector.m_pAdjResults->m_fCoef*fCoef*(1+oAdjCalVector.m_oAdjParas.m_fDeviation);

	if(fCoef>1.2)
	{
		return false;//系数误差不合理，本次校准无效
	}
	else
		oAdjCalVector.m_pAdjResults->m_fCoef=fCoef;

	return true;
}

bool stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector,TMT_ADJUST_THREE_RESULTS &oAdjResults)
{
	//AC fMag,fAng

	oAdjResults.m_oResult[0].m_fZero=0;//RD33不校准零漂
	oAdjResults.m_oResult[1].m_fZero=0;//RD33不校准零漂
	oAdjResults.m_oResult[2].m_fZero=0;//RD33不校准零漂

	float fAng[3];
	fAng[0]=oAdjCalVector.m_oAdjParas.m_fAng;
	fAng[1]=oAdjCalVector.m_oAdjParas.m_fAng2;
	fAng[2]=oAdjCalVector.m_oAdjParas.m_fAng3;

	float fMag[3];
	fMag[0]=oAdjCalVector.m_oAdjParas.m_fMag;
	fMag[1]=oAdjCalVector.m_oAdjParas.m_fMag2;
	fMag[2]=oAdjCalVector.m_oAdjParas.m_fMag3;

	float fCoef=0;
	float fang=0;

	for(int nIndex=0;nIndex<3;nIndex++)
	{
		//Mag
		if(fMag[nIndex]<0.1)
		{
			//采样值不合理，本次不校准
			oAdjResults.m_oResult[nIndex].m_fCoef=-2;
			oAdjResults.m_oResult[nIndex].m_fAngle=0;
			continue;
		}

		fCoef=oAdjCalVector.m_oOutputVector[nIndex].m_fMag/fMag[nIndex];
		fCoef=oAdjCalVector.m_pAdjResults[nIndex]->m_fCoef*fCoef;

		if(fCoef>1.2)
		{
			//系数误差不合理，本次校准无效
			oAdjResults.m_oResult[nIndex].m_fCoef=-1;
			oAdjResults.m_oResult[nIndex].m_fAngle=0;
		}
		else
		{
			oAdjCalVector.m_pAdjResults[nIndex]->m_fCoef=fCoef;
			oAdjResults.m_oResult[nIndex].m_fCoef=fCoef;
		}

		//Ang
		if(oAdjCalVector.m_oAdjParas.m_nModuleType==STT_MODULE_TYPE_VOLT&&nIndex==0)
		{
			oAdjResults.m_oResult[0].m_fAngle=0;//UA相位不补偿
		}
		else
		{
			fang=oAdjCalVector.m_pAdjResults[nIndex]->m_fAngle-fAng[nIndex];
			while((fang>360)||(fang<0))
			{
				if(fang>360)
				{
					fang-=360;
				}
				else
				{
					fang += 360;
				}
			}

			oAdjCalVector.m_pAdjResults[nIndex]->m_fAngle=fang;
			oAdjResults.m_oResult[nIndex].m_fAngle=oAdjCalVector.m_pAdjResults[nIndex]->m_fAngle;
		}
	}

	return true;
}

