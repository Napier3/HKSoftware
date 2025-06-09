#include "stdafx.h"
#include "tmt_adjust_cal.h"
#include "../tmt_adjust_sys_parameter.h"
#include "math.h"
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
BOOL stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, long nChannel,long nTempretureID,
							   long &nGearID, long &nFreqSel,TMT_ADJ_CHANNEL_VECTOR_EX &oVector)
{
    if (nChannel < 0 || nChannel >= STT_MODULE_CHANNEL_MAX)//20220414 zhoulei 48路小信号
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

	PSTT_CHANNEL_ADJUSTS pChsAdjust = pTemperatureAdj->m_pChsAdjust;
	if(pChsAdjust == NULL)
	{
		return false;
	}

    if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
    {
		if(pParas->m_nFreqIndex < pChsAdjust[nChannel].nHarmCount)
		{
			PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj= pChsAdjust[nChannel].m_pChWaveAdj;

			if(pChWaveAdj != NULL)
			{
				long nGearCount = pChWaveAdj[pParas->m_nFreqIndex].m_nGearCount;
				if(nGearCount == 0)
				{
					return false;
				}

				nGearID = nGearCount - 1;
				for(int nGearIndex=0;nGearIndex<nGearCount;nGearIndex++)
				{
					if(oVector.m_fMag <= pChWaveAdj[pParas->m_nFreqIndex].m_oChGearAdj[nGearIndex].m_fGearValue)
					{
						nGearID=nGearIndex;
						break;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else
			return false;
	}
    else
        return false;

	nFreqSel=pParas->m_nFreqIndex;
    return true;
}

BOOL stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector)
{
    return stt_adj_get_output_vector(pParas
                                     , oAdjCalVector.m_oAdjParas.m_nChannel
                                     , oAdjCalVector.m_oAdjParas.m_nTempretureID
                                     , oAdjCalVector.m_oAdjParas.m_nGearID
                                     , oAdjCalVector.m_oAdjParas.m_nFreqSel
                                     , oAdjCalVector.m_oOutputVector);
}

BOOL stt_adj_get_output_vector(PTMT_ADJ_MODULE_OUTPUT pParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector)
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

BOOL stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR &oAdjCalVector)
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

BOOL stt_adj_get_adjust_item_ref(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector)
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
BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_ONE poAdjParas)
{
    TMT_ADJ_CAL_VECTOR oAdjCalVector;
    memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR));

	oAdjCalVector.m_oAdjParas.m_nModuleType = poAdjParas->m_oParas.m_nModuleType;
	oAdjCalVector.m_oAdjParas.m_nModule = poAdjParas->m_oParas.m_nModule;
	oAdjCalVector.m_oAdjParas.m_nFreqSel = poAdjParas->m_oParas.m_nFreqSel;
	oAdjCalVector.m_oAdjParas.m_nChannel = poAdjParas->m_oParas.m_nChannel;
	oAdjCalVector.m_oAdjParas.m_nTempretureID = poAdjParas->m_oParas.m_nTempretureID;
	oAdjCalVector.m_oAdjParas.m_nGearID = poAdjParas->m_oParas.m_nGearID;
	oAdjCalVector.m_oAdjParas.m_fMag = poAdjParas->m_oParas.m_fMag;
	oAdjCalVector.m_oAdjParas.m_fAng = poAdjParas->m_oParas.m_fAng;
	oAdjCalVector.m_oAdjParas.m_fFreq = poAdjParas->m_oParas.m_fFreq;
	oAdjCalVector.m_oAdjParas.m_fDeviation = poAdjParas->m_oParas.m_fDeviation;

	if (!stt_adj_get_output_vector(pModuleOutput, oAdjCalVector))
    {
        return false;
    }

	if (!stt_adj_get_adjust_item_ref(pDvSysParas, oAdjCalVector))
    {
        return false;
    }

    if(oAdjCalVector.m_oOutputVector.m_fMag < 0.000001 && oAdjCalVector.m_oOutputVector.m_fFreq < 0.1)
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

		PSTT_CHANNEL_ADJUSTS pChsAdjust = pTemperatureAdj->m_pChsAdjust;
		if(pChsAdjust == NULL)
		{
			return false;
		}

		PSTT_CHANNEL_ADJUSTS pChanAdjust=NULL;
        if(poAdjParas->m_oParas.m_nChannel > -1 && poAdjParas->m_oParas.m_nChannel < pModule->m_oModuleAttr.m_nChannelNum)
        {
			pChanAdjust=&pChsAdjust[poAdjParas->m_oParas.m_nChannel];
        }
        else
			pChanAdjust=&pChsAdjust[0];

        float fCalZero=pChanAdjust->m_fDcZero[0]+oAdjCalVector.m_oAdjParas.m_fMag;
        if(fabs(fCalZero) > 0.1)
		{//零漂计算的结果超范围
			poAdjParas->m_oResult.m_oResult.m_fZero=fCalZero;
			poAdjParas->m_oResult.m_oResult.m_fCoef=-1;
			poAdjParas->m_oResult.m_oResult.m_fAngle=0;
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 零漂计算结果%f失真"),poAdjParas->m_oParas.m_nChannel+1,fCalZero);
        }
        else
        {
            pChanAdjust->m_fDcZero[0]=fCalZero;
            poAdjParas->m_oResult.m_oResult.m_fZero=pChanAdjust->m_fDcZero[0];
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

PSTT_CHANNEL_ADJUSTS adj_find_channel(PSTT_DEVICESYSTEMPARAMETER pDvSysParas,long nModule,long nModuleType,long nTempretureID,long nChannel)
{
    PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, nModule, nModuleType);

	if(pModule==NULL)
        return NULL;

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

	PSTT_CHANNEL_ADJUSTS pChsAdjust = pTemperatureAdj->m_pChsAdjust;
	if(pChsAdjust == NULL)
	{
		return NULL;
	}

	PSTT_CHANNEL_ADJUSTS pChanAdjust=NULL;
    if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
    {
		pChanAdjust=&pChsAdjust[nChannel];
    }
    else
		pChanAdjust=&pChsAdjust[0];

    return pChanAdjust;
}

BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJUST_ONE2POINTS poAdjParas)
{
    //DCzero
	long nModule=poAdjParas->m_oParas.m_nModule;
	long nModuleType=poAdjParas->m_oParas.m_nModuleType;
	long nTempretureID=poAdjParas->m_oParas.m_nTempretureID;
	long nChannel=poAdjParas->m_oParas.m_nChannel;
	PSTT_CHANNEL_ADJUSTS pChanAdjust=adj_find_channel(pDvSysParas,nModule,nModuleType,nTempretureID,nChannel);

	if(pChanAdjust==NULL)
        return FALSE;

    if(pChanAdjust->m_pChWaveAdj == NULL)
        return FALSE;

    if(poAdjParas->m_oParas.m_nFreqSel >= pChanAdjust->nHarmCount)
        return FALSE;

    PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj = &pChanAdjust->m_pChWaveAdj[poAdjParas->m_oParas.m_nFreqSel];
	int nGearID = pChWaveAdj->m_nGearCount-1;
	for(int nGearIndex=0;nGearIndex<pChWaveAdj->m_nGearCount;nGearIndex++)
    {
        if(poAdjParas->m_oParas.m_fPoint1RefMag <= pChWaveAdj->m_oChGearAdj[nGearIndex].m_fGearValue
				&&poAdjParas->m_oParas.m_fPoint2RefMag <= pChWaveAdj->m_oChGearAdj[nGearIndex].m_fGearValue)
        {
			nGearID=nGearIndex;
            break;
        }
    }

    PSTT_ADJUST_ITEM pAdjItem = &pChWaveAdj->m_oChGearAdj[nGearID].m_oAdjItem;

    //硬件放大器特性 y=k*x+b,软件需反向补偿 y=(x-b)/k达到效果
    //已有补偿y=k1*x+b1;已有系数k1，已有零漂b1
    //y1=k*(k1*x1+b1)+b,y2=k*(k1*x2+b1)+b
    //已知k1,b1,x1,y1,x2,y2,解得k,b
    //fCoef=1/k,fZero=-b/k
    float fXPoint1 = poAdjParas->m_oParas.m_fPoint1RefMag;
    float fYPoint1 = poAdjParas->m_oParas.m_fPoint1MeasMag;
    float fXPoint2 = poAdjParas->m_oParas.m_fPoint2RefMag;
    float fYPoint2 = poAdjParas->m_oParas.m_fPoint2MeasMag;

	poAdjParas->m_oResult.m_oResult.m_fAngle=pAdjItem->m_fAngle;
	poAdjParas->m_oResult.m_oResult.m_fZero=0;

    float fCoef = pAdjItem->m_fCoef;
	fCoef=fCoef*(fXPoint2-fXPoint1)/(fYPoint2-fYPoint1);
    if(fCoef < 1.3 || nModuleType == STT_MODULE_TYPE_MEAS_VOLT
            || nModuleType == STT_MODULE_TYPE_MEAS_CURRENT)
    {
		pAdjItem->m_fCoef=fCoef;
		poAdjParas->m_oResult.m_oResult.m_fCoef=fCoef;

        float fZero = pAdjItem->m_fZero;
		fZero+=pAdjItem->m_fCoef*(fXPoint1*fYPoint2-fXPoint2*fYPoint1)/(fYPoint2-fYPoint1);

		pAdjItem->m_fZero=fZero;
		poAdjParas->m_oResult.m_oResult.m_fZero=fZero;
    }
    else
    {
		poAdjParas->m_oResult.m_oResult.m_fCoef=pAdjItem->m_fCoef;
		poAdjParas->m_oResult.m_oResult.m_fZero=pAdjItem->m_fZero;
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 原幅值系数%f，当前幅值系数计算结果%f>1.3，失真"),
								   nChannel+1,pAdjItem->m_fCoef,fCoef);

    }

    return TRUE;
}

BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJUST_ANGLE poAdjParas)
{
	long nModule=poAdjParas->m_oParas.m_nModule;
	long nModuleType=poAdjParas->m_oParas.m_nModuleType;
	long nTempretureID=poAdjParas->m_oParas.m_nTempretureID;
	long nChannel=poAdjParas->m_oParas.m_nChannel;
	PSTT_CHANNEL_ADJUSTS pChanAdjust=adj_find_channel(pDvSysParas,nModule,nModuleType,nTempretureID,nChannel);

	if(pChanAdjust==NULL)
        return FALSE;

	if(pChanAdjust->m_pChWaveAdj==NULL)
        return FALSE;

    if(pChanAdjust->nHarmCount <= 1)
        return FALSE;

    float fAngle = pChanAdjust->m_pChWaveAdj[1].m_oChGearAdj[0].m_oAdjItem.m_fAngle;
	fAngle -=poAdjParas->m_oParas.m_fMeasAng;
    pChanAdjust->m_pChWaveAdj[1].m_oChGearAdj[0].m_oAdjItem.m_fAngle = fAngle;

	poAdjParas->m_oResult.m_oResult.m_fZero=pChanAdjust->m_pChWaveAdj[1].m_oChGearAdj[0].m_oAdjItem.m_fZero;
	poAdjParas->m_oResult.m_oResult.m_fCoef=pChanAdjust->m_pChWaveAdj[1].m_oChGearAdj[0].m_oAdjItem.m_fCoef;
	poAdjParas->m_oResult.m_oResult.m_fAngle=fAngle;

    return TRUE;
}

BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJUST_FREQ poAdjParas)
{
    //DCzero
    PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, poAdjParas->m_oParas.m_nModule,
                          poAdjParas->m_oParas.m_nModuleType);

	if(pModule==NULL)
        return FALSE;

	float fFre=1;
	fFre=poAdjParas->m_oParas.m_fRefFreq/poAdjParas->m_oParas.m_fMeasFreq;
	fFre=fFre*pModule->m_oModuleAttr.m_fFreCoef;
    pModule->m_oModuleAttr.m_fFreCoef = fFre;

	poAdjParas->m_oResult.m_oResult.m_fZero=0;
	poAdjParas->m_oResult.m_oResult.m_fCoef=fFre;
	poAdjParas->m_oResult.m_oResult.m_fAngle=0;

    return TRUE;
}

BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJUST_DCZERO poAdjParas)
{
    //DCzero
    long nModule = poAdjParas->m_oParas.m_nModule;
    long nModuleType = poAdjParas->m_oParas.m_nModuleType;
    long nTempretureID = poAdjParas->m_oParas.m_nTempretureID;
    long nChannel = poAdjParas->m_oParas.m_nChannel;
    long nTap = 0;
    PSTT_MODULE pModule = stt_adj_find_module_byModulePos(pDvSysParas, nModule, nModuleType);
    if(pModule == NULL)
        return FALSE;

#ifdef _PSX_QT_LINUX_
    nTap = poAdjParas->m_oParas.m_nTap;
    BOOL bUseTap = FALSE;
    switch(pModule->m_oModuleAttr.m_nModulePower)
    {
        case STT_MODULE_WEEK_DC6U10V:
        case STT_MODULE_WEEK_DC6I20mA:
        case STT_MODULE_WEEK_EVTECT:
        case STT_MODULE_WEEK_PNS331:
        case STT_MODULE_WEEK_PN_DC6U6I:
		case STT_MODULE_WEEK_L336D_ECTEVT:
            bUseTap = TRUE;
            break;
    }

    if(bUseTap)
    {
        switch(nTap)
        {
            case 0:
            case 1:
            case 2:
                break;
            default:
                nTap = 0;
        }
    }
    else
    {
        nTap = 0;
    }
#endif

	PSTT_CHANNEL_ADJUSTS pChanAdjust=adj_find_channel(pDvSysParas,nModule,nModuleType,nTempretureID,nChannel);

	if(pChanAdjust==NULL)
        return FALSE;

    float fCalZero = pChanAdjust->m_fDcZero[nTap] + poAdjParas->m_oParas.m_fMeasDcZero;
    if(fabs(fCalZero) > 0.1)
	{//零漂计算的结果超范围
        poAdjParas->m_oResult.m_oResult.m_fZero = pChanAdjust->m_fDcZero[nTap];
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 零漂计算结果%f失真"),nChannel+1,fCalZero);
    }
    else
    {
        pChanAdjust->m_fDcZero[nTap] = fCalZero;
        poAdjParas->m_oResult.m_oResult.m_fZero = pChanAdjust->m_fDcZero[nTap];
    }

    return TRUE;
}

BOOL stt_adj_cal(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PTMT_ADJ_MODULE_OUTPUT pModuleOutput, PTMT_ADJUST_THREE poAdjParas)
{
    TMT_ADJ_CAL_VECTOR_THREE oAdjCalVector;
    memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR_THREE));
	oAdjCalVector.m_oAdjParas.m_nModuleType = poAdjParas->m_oParas.m_nModuleType;
	oAdjCalVector.m_oAdjParas.m_nModule = poAdjParas->m_oParas.m_nModule;
	oAdjCalVector.m_oAdjParas.m_nFreqSel = poAdjParas->m_oParas.m_nFreqSel;
	oAdjCalVector.m_oAdjParas.m_nChannel = poAdjParas->m_oParas.m_nChannel;
	oAdjCalVector.m_oAdjParas.m_nChannel2 = poAdjParas->m_oParas.m_nChannel2;
	oAdjCalVector.m_oAdjParas.m_nChannel3 = poAdjParas->m_oParas.m_nChannel3;
	oAdjCalVector.m_oAdjParas.m_nTempretureID = poAdjParas->m_oParas.m_nTempretureID;
	oAdjCalVector.m_oAdjParas.m_nGearID = poAdjParas->m_oParas.m_nGearID;
	oAdjCalVector.m_oAdjParas.m_nGearID2 = poAdjParas->m_oParas.m_nGearID2;
	oAdjCalVector.m_oAdjParas.m_nGearID3 = poAdjParas->m_oParas.m_nGearID3;
	oAdjCalVector.m_oAdjParas.m_fMag = poAdjParas->m_oParas.m_fMag;
	oAdjCalVector.m_oAdjParas.m_fMag2 = poAdjParas->m_oParas.m_fMag2;
	oAdjCalVector.m_oAdjParas.m_fMag3 = poAdjParas->m_oParas.m_fMag3;
	oAdjCalVector.m_oAdjParas.m_fAng = poAdjParas->m_oParas.m_fAng;
	oAdjCalVector.m_oAdjParas.m_fAng2 = poAdjParas->m_oParas.m_fAng2;
	oAdjCalVector.m_oAdjParas.m_fAng3 = poAdjParas->m_oParas.m_fAng3;
	oAdjCalVector.m_oAdjParas.m_fFreq = poAdjParas->m_oParas.m_fFreq;
	oAdjCalVector.m_oAdjParas.m_fFreq2 = poAdjParas->m_oParas.m_fFreq2;
	oAdjCalVector.m_oAdjParas.m_fFreq3 = poAdjParas->m_oParas.m_fFreq3;
	oAdjCalVector.m_oAdjParas.m_fDeviation = poAdjParas->m_oParas.m_fDeviation;

	if (!stt_adj_get_output_vector(pModuleOutput, oAdjCalVector))
    {
        return false;
    }

	if (!stt_adj_get_adjust_item_ref(pDvSysParas, oAdjCalVector))
    {
        return false;
    }	

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
			if(nChannel[nIndex]<0 || nChannel[nIndex]>=6 || fMag[nIndex]<0.1)
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

			PSTT_CHANNEL_ADJUSTS pChsAdjust = pTemperatureAdj->m_pChsAdjust;
			if(pChsAdjust == NULL)
			{
				return false;
			}

            if(nChannel[nIndex] > -1 && nChannel[nIndex] < pModule->m_oModuleAttr.m_nChannelNum)
            {
				PSTT_CHANNEL_ADJUSTS pChanAdjust=&pChsAdjust[nChannel[nIndex]];

				fCoef=oAdjCalVector.m_oOutputVector[nIndex].m_fMag/fMag[nIndex];
				fCoef=pChanAdjust->m_fLargeCurrentRatio*fCoef;
				if(fCoef>1.2)
                {
					poAdjParas->m_oResults.m_oResult[nIndex].m_fCoef=-1;
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 原大电流幅值系数%f，当前大电流幅值系数计算结果%f>1.2，失真"),
											   nChannel[nIndex]+1,pChanAdjust->m_fLargeCurrentRatio,fCoef);
                }
                else
                {
					pChanAdjust->m_fLargeCurrentRatio=fCoef;
					poAdjParas->m_oResults.m_oResult[nIndex].m_fCoef=fCoef;
                }

				poAdjParas->m_oResults.m_oResult[nIndex].m_fAngle=0;
				poAdjParas->m_oResults.m_oResult[nIndex].m_fZero=0;
            }
            else
            {
                return false;
            }
        }
    }
    else
		stt_adj_vector_cal(oAdjCalVector,poAdjParas->m_oResults);

    return true;
}

//根据校准计算参数结构体，计算校准系数
BOOL stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR &oAdjCalVector)
{
    //AC DC fMag
	float fCoef=oAdjCalVector.m_oOutputVector.m_fMag/oAdjCalVector.m_oAdjParas.m_fMag;

	fCoef=oAdjCalVector.m_pAdjResults->m_fCoef*fCoef*(1+oAdjCalVector.m_oAdjParas.m_fDeviation);

	if(fCoef>1.3)
    {
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 原幅值系数%f，当前幅值系数计算结果%f>1.3，失真"),
								   oAdjCalVector.m_oAdjParas.m_nChannel+1,oAdjCalVector.m_pAdjResults->m_fCoef,fCoef);
        return false;//系数误差不合理，本次校准无效
    }
    else
		oAdjCalVector.m_pAdjResults->m_fCoef=fCoef;

    return true;
}

BOOL stt_adj_vector_cal(TMT_ADJ_CAL_VECTOR_THREE &oAdjCalVector,TMT_ADJUST_THREE_RESULTS &oAdjResults)
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
	long nChannel;

	for(int nIndex=0;nIndex<3;nIndex++)
    {
		switch(nIndex)
		{
		case 0:
			nChannel = oAdjCalVector.m_oAdjParas.m_nChannel;
			break;
		case 1:
			nChannel = oAdjCalVector.m_oAdjParas.m_nChannel2;
			break;
		case 2:
			nChannel = oAdjCalVector.m_oAdjParas.m_nChannel3;
			break;
		}

        //Mag
		if(fMag[nIndex]<0.1)
        {
            //采样值不合理，本次不校准
			oAdjResults.m_oResult[nIndex].m_fCoef=-2;
			oAdjResults.m_oResult[nIndex].m_fAngle=0;
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 采集幅值%f<0.1，失真"),nChannel+1,fMag[nIndex]);
            continue;
        }

		fCoef=oAdjCalVector.m_oOutputVector[nIndex].m_fMag/fMag[nIndex];
		fCoef=oAdjCalVector.m_pAdjResults[nIndex]->m_fCoef*fCoef;

		if(fCoef>1.3)
        {
            //系数误差不合理，本次校准无效
			oAdjResults.m_oResult[nIndex].m_fCoef=-1;
			oAdjResults.m_oResult[nIndex].m_fAngle=0;
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("通道%d 原幅值系数%f，当前幅值系数计算结果%f>1.3，失真"),
									   nChannel+1,oAdjCalVector.m_pAdjResults[nIndex]->m_fCoef,fCoef);
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

