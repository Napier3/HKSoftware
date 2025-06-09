#include "stdafx.h"
#include "CapDevice6044.h"

#include "../../../API/MathApi.h"
#include "../../../Record/RecordTest/CalFunctions.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"
#include "CapDeviceMngr.h"
#include "../../../Record/FFT/FFT.h" // mym add 2020-6-25 ;
//#include "../ProtocolBase/61850ParseFrameList.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCapDevice6044::CCapDevice6044()
{
	m_nSmpRate = 4000;
	m_nPkgLenth = 0;
	m_dBaudRate = 0.0f;
	m_nRefChIndex = 0;
	m_bDC_FT3 = FALSE;
	m_nPkgDatasLenth = 2;
	m_nDelayTimeChIndex = 0;
	m_bHasDelayTimeCh = FALSE;
	m_strSTMode = "FT3";
//	m_nDebugIntervalTime = 0;
	m_nStateValueChangedCount = 0;
	m_nFt3_CrcType = 0;

	for (int nIndex = 0;nIndex<STCAPPARSE_DATA_MAX_COUNT;nIndex++)
	{
		m_nChByteLenth[nIndex] = 1;
	}
}

CCapDevice6044::~CCapDevice6044()
{
}

void CCapDevice6044::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;
	
	if(pIecCfgData == NULL)
	{
		return;
	}

	if (pIecCfgData->GetClassID() != CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		return;
	}

	CIecCfg6044CommonInData* pCfgData60044Common = (CIecCfg6044CommonInData*)pIecCfgData;
	m_bHasDelayTimeCh = FALSE;
	int nCurrRow = 0;
	bool bFristCurOrVolChIndex = false;

	if (pCfgData60044Common->m_pCfgChs != NULL)
	{
		CIecCfg6044CommonCh *p6044CommonCh = NULL;
		long nChIndex = 0;
		POS pos = pCfgData60044Common->m_pCfgChs->GetHeadPosition();

		while(pos)
		{
			p6044CommonCh = (CIecCfg6044CommonCh *)pCfgData60044Common->m_pCfgChs->GetNext(pos);

			if (p6044CommonCh->m_strAppChID == g_strAppChID_TDelay)
			{
				m_nDelayTimeChIndex = nChIndex;
				m_bHasDelayTimeCh = TRUE;
			}

			//2024-5-27 wuxinyi 添加进入FT3报文探测时，自动设第一条电流\电压通道为基准相
			if(p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue || 
				p6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
			{
				nCurrRow++;
			}
			else
			{
				if(!bFristCurOrVolChIndex)
				{
					m_nRefChIndex = nCurrRow;
					bFristCurOrVolChIndex = true;
				}

			}


			m_nChByteLenth[nChIndex] = p6044CommonCh->m_nChLenth;
			nChIndex++;
		}
	}

	m_nType = PROTOCOL_61850_TYPE_6044;
	CCapDeviceBase::InitDevice(pIecCfgData);
}

void CCapDevice6044::GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas)
{
	CCapDeviceSmvCh *pSmvCh = NULL;

	for (int nIndex = 0;nIndex<GetCount();nIndex++)
	{
		pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nIndex);
		pSmvCh->m_dwValue = pParseDatas->pDatas[nIndex].dwValue;
		pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
	}
}

void CCapDevice6044::AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead,long nBufferLenth)
{
	if (nBufferLenth > STT_60044_PKG_MAX_LENGTH)
	{
		m_nPkgDatasLenth = STT_60044_PKG_MAX_LENGTH;
		memcpy(m_szPkgDatas,pBuferHead,STT_60044_PKG_MAX_LENGTH);
	} 
	else
	{
		m_nPkgDatasLenth = nBufferLenth;
		memcpy(m_szPkgDatas,pBuferHead,nBufferLenth);
	}
	
// 	long nFT3CrcType = 0;
// 	if (m_pIecCfgData != NULL)
// 	{
// //		nFT3CrcType = m_pIecCfgData->GetFT3CrcType();  //zhouhj 2024.8.10 此处待苏洋更新代码
// 	}

	long nChNum = GetCount();
	long nCurrBytePos = 0,nHasCrcLenth = 0;
	pBuferHead += 2;//跳过报文头2字节0x0564
	CCapDeviceSmvCh *pSmvCh = NULL;

	long nChIndex = 0;
	POS pos = GetHeadPosition();
	if (m_nFt3_CrcType == 2 )
	{
		for (nChIndex= 0;nChIndex<8;nChIndex++)
		{
			if ((nCurrBytePos + m_nChByteLenth[nChIndex])>nBufferLenth)
			{
				break;
			}

			pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nChIndex);
			pDatas->pDatas[nChIndex].dwValue = GetByteChValue(pBuferHead,nCurrBytePos,nHasCrcLenth,m_nChByteLenth[nChIndex],m_nFt3_CrcType);
			//增加将原始数据填入数据通道的功能
			pSmvCh->m_dwValue = pDatas->pDatas[nChIndex].dwValue;
			pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
		}

		nCurrBytePos += 2;

		for (nChIndex= 8;nChIndex<16;nChIndex++)
		{
			if ((nCurrBytePos + m_nChByteLenth[nChIndex])>nBufferLenth)
			{
				break;
			}

			pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nChIndex);
			pDatas->pDatas[nChIndex].dwValue = GetByteChValue(pBuferHead,nCurrBytePos,nHasCrcLenth,m_nChByteLenth[nChIndex],m_nFt3_CrcType);
			//增加将原始数据填入数据通道的功能
			pSmvCh->m_dwValue = pDatas->pDatas[nChIndex].dwValue;
			pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
		}
		nCurrBytePos += 2;

		for (nChIndex = 16; nChIndex < nChNum; nChIndex++)
		{
			if ((nCurrBytePos + m_nChByteLenth[nChIndex])>nBufferLenth)
			{
				break;
			}

			pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nChIndex);
			pDatas->pDatas[nChIndex].dwValue = GetByteChValue(pBuferHead,nCurrBytePos,nHasCrcLenth,m_nChByteLenth[nChIndex],m_nFt3_CrcType);
			//增加将原始数据填入数据通道的功能
			pSmvCh->m_dwValue = pDatas->pDatas[nChIndex].dwValue;
			pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
		}
	}
	else
	{
	while(pos)
	{
		pSmvCh = (CCapDeviceSmvCh *)GetNext(pos);

		if ((nCurrBytePos + m_nChByteLenth[nChIndex])>nBufferLenth)
		{
			break;
		}
		
			pDatas->pDatas[nChIndex].dwValue = GetByteChValue(pBuferHead,nCurrBytePos,nHasCrcLenth,m_nChByteLenth[nChIndex],m_nFt3_CrcType);
		//增加将原始数据填入数据通道的功能
		pSmvCh->m_dwValue = pDatas->pDatas[nChIndex].dwValue;
		pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
		nChIndex++;
	}

	}
		



// 	if (pDatas->dwDatas <= 0)
// 	{
		pDatas->dwDatas = nChNum;
	/*}*/ //dingxy 20240529 pDatas->dwDatas应该随着不同光口的通道数改变
// 	if (g_oCapAnalysisConfig.m_bAnalysisData_Complex)
// 	{
// 		AnalysisData_Complex(pDatas);
// 	}

	if (g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt)
	{
		AnalysisData_PhaseDelt(pDatas);
	}

	if (g_oCapAnalysisConfig.m_bStateValueChangedAnalysis)
	{
		AnalysisStateValueChangedCount(pDatas);
	}

	//zhouhj 2024.3.10 FT3无品质位通道,对应原始报文数据解析已经合并到上面
// 	if (g_oCapAnalysisConfig.m_bChQualitySpy)
// 	{
// 		GetOriginalDatas(pDatas);
// 	}
}

long CCapDevice6044::GetByteChValue(BYTE* pBuferHead,long &nCurrPos,long &nHasCrcLenth,long nChLenth,long nFT3CrcType)
{
	if ((nChLenth>4) ||(nChLenth<=0))
	{
		nCurrPos += nChLenth;
		return 0;
	}

	BYTE *pCurr = &pBuferHead[nCurrPos];
	BYTE *pEnd = pCurr + nChLenth;
	DWORD val = 0;

	if (nFT3CrcType > 0)
	{
		while (pCurr < pEnd)
		{
			val = val << 8;
			val += *pCurr;
			pCurr++;
			nCurrPos++;
		}
	}
	else
	{
	while (pCurr < pEnd)
	{
		if ((nCurrPos>0)&&((nCurrPos-nHasCrcLenth)%16 == 0))//16个字节的倍数位置跳过CRC校验
		{
			nCurrPos += 2;
			pCurr += 2;
			pEnd += 2;
			nHasCrcLenth += 2;
		}

		val = val << 8;
		val += *pCurr;
		pCurr++;
		nCurrPos++;
	}
	}
	

	switch (nChLenth)
	{
	case 1:
		if (val>0x7F)
		{
			val = (val - 0xFF - 1);
		}
		break;
	case 2:
		if (val>0x7FFF)
		{
			val = (val - 0xFFFF - 1);
		}

		break;
	case 3:
		if (val>0x7FFFFF)
		{
			val = (val - 0xFFFFFF - 1);
		}
		break;

	default:
		break;
	}

	return val;
}

//数据接受超时
BOOL CCapDevice6044::IsDataRcvOverTime()
{
	return m_oTickCount.GetTickCountLong(FALSE) > 2000; //采样值数据超过2s未收到认为超时
}

// mym 2020-9-17 查找最大值； 
void CCapDevice6044::FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo)
{
	double dCompValue[256] = {0};
	if (nValueCnt  > 256)
		nValueCnt = 256;
	for (int i = 0; i < nValueCnt;  i++)
	{
		dCompValue[i]  = *(pValue + i);
		if (dCompValue[i] <=0 )
			dCompValue[i] = -dCompValue[i];
	}

	int nIndex = 0;
	double fMaxValue = dCompValue[0];
	for (int i = 1;  i  < nValueCnt;  i++)
	{
		if (fMaxValue < dCompValue[i] )
		{
			fMaxValue  =  dCompValue[i] ;
			nIndex = i;
		}
	}
	nMaxNo = nIndex;       //找到了最大值的序号；
}

void CCapDevice6044:: Reset()  //开始抓包，复位之前的状态
{
	CCapDeviceBase::Reset();
	m_nStateValueChangedCount = 0;
}

void CCapDevice6044::ClearAnalysisResultErrors()
{
	m_dMaxTimeDiscrete = 0;
	m_oAnalysisResults.dDeltTime = 0.0f;

	for (int i = 0; i < STT_CAP_RCD_SMV_DISCRET_MAX_COUNT; i++)
	{
		m_nDisCretNum[i] = 0;//20231020 dxy 清空时报文离散度统计数据清空
	}

	for (int nIndex = 0;nIndex<PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM;nIndex++)
	{
		for (int nAsduIndex = 0;nAsduIndex<8;nAsduIndex++)
		{
			m_oAnalysisResults.rslt_92.nErrorType[nAsduIndex][nIndex] = 0;
		}

		m_oAnalysisResults.nPkgNum = 0;
	}
}

void CCapDevice6044::analysis6044(PEPCAPPARSEDATAS pDatas)
{
	double dStdIntervalTime = 1000000000.0f/m_nSmpRate;
	double dCurrIntervalTime = GetTimeGap_EpcapBufferItem(pDatas->n64Time,m_oPrevDatas.n64Time,FALSE);
	double dErrorValue = dCurrIntervalTime - dStdIntervalTime;
	
// 	if (fabs(dErrorValue)>1000.0f)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前时间间隔(%lf),标准时间间隔(%lf),抖动值(%lf)."),dCurrIntervalTime
// 			,dStdIntervalTime,dErrorValue);
// 	}


	//zhouhj FT3不涉及相关
// 	if (g_oCapAnalysisConfig.m_bMaxTimeDiscrete || g_oCapAnalysisConfig.m_bSvAnalysis
// 		|| g_oCapAnalysisConfig.m_bMU_Test)
// 	{
// //		ep_protocol_analysis92(&m_oPrevDatas,   pDatas,  &m_oAnalysisResults,m_nChType,m_nChAngType);  
// 
// 		//在这里判断获取离散度的最大值
// 		if (fabs((double)m_dMaxTimeDiscrete)   <=  fabs((double)m_oAnalysisResults.dDeltTime))
// 			m_dMaxTimeDiscrete = m_oAnalysisResults.dDeltTime;
// 	}

// 	if (g_oCapAnalysisConfig.m_bPkgConsistence)
// 	{
// //		ep_consistence_analysis92();
// 	}
//
//	pDatas->nFirstPacket = 1; //mym 20202-6-21 解析完后当前帧就把标志置1；
}

void CCapDevice6044::GetSttCapParas(CDataGroup *pSttParas)
{
	CDataGroup *pNew = pSttParas->AddNewGroup("Subscribe", "Subscribe", "Subscribe");
	CString strText;

	pNew->AddNewData(XPARA_ID_Port, m_nFiberIndex);
	pNew->AddNewData(XPARA_ID_BaudRate, m_dBaudRate);
	pNew->AddNewData(XPARA_ID_SampleRate, m_nSmpRate);
	pNew->AddNewData(XPARA_ID_OnePkgLen, m_nPkgLenth);
	pNew->AddNewData(XPARA_ID_STMode, m_strSTMode);
	pNew->AddNewData(XPARA_ID_Type, XPARA_ID_TYPE_FT3);
}

void CCapDevice6044::InitNameAndID(long nTypeCount)
{
	if (m_strID.GetLength() > 0)
	{
		return;
	}

	m_strID.Format(_T("%s%d"),CAP_DATASET_MAP_ID_dsSV, nTypeCount);
	m_strName = "光口";
	m_strName.AppendFormat(_T("%ld_FT3"), m_nFiberIndex+1);
//	m_strName += m_strID;
}

BOOL CCapDevice6044::Compare(PEPCAPBUFFERITEM pItemData)
{
	if (m_nFiberIndex != pItemData->addr_61850.APPID)
	{
		return FALSE;
	}

	if (m_nType != pItemData->nProtocol)
	{
		return FALSE;
	}

	return TRUE;
}
/*
算法思路:
1、根据m_nFFTStatePhaseDelt==0，以及是否包含录波时标数据(测试仪输出时,第一个模拟量通道过零点的时标)进行判断；
(先电压后电流)
2、当记录的点数超过CAP_FFT_CAL_POINTS时，开始进行计算：
1）记录第一个采样数据点的绝对时标到m_nFirstRcdPointTime内；
2）根据上述绝对时标，在录波时标数据链表内找到最接近的时标；
3）计算每个通道第一个点数据对应的绝对相位值；
4）根据上述最接近的录波时标及时标对应的通道，计算出当前通道第一个点时刻的模拟量对应的输出相位；
5）通过当前通道第一个点的绝对相位+通道延时,获取当前通道第一个点对应时刻模拟量通道输出时的相位值；
6）上述两个相位的差值即为对应角差；
*/

void CCapDevice6044::AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas)
{
// 	return;
	CCapDeviceMngr *pCCapDeviceMngr = (CCapDeviceMngr*)GetParent();

	if (pCCapDeviceMngr == NULL)
	{
		return;
	}

	if (m_nFFTStatePhaseDelt == CAPDEV_SMV_FFTStatePhaseDelt_Finished)
	{
		return;
	}

	if (m_oPrevDatas.dwDatas == 0)
		return;

	if (pCCapDeviceMngr->m_oTimeDataList.GetDataLength()<=0)
	{
		if (m_bHasDelayTimeCh)
		{
			if (m_dwTimeDelay != pDatas->pDatas[m_nDelayTimeChIndex].dwValue)
			{
				m_dwTimeDelay = pDatas->pDatas[m_nDelayTimeChIndex].dwValue;
			}
		}
		else
		{
			m_dwTimeDelay = 0;
		}
		
		//录波过程中,时间数据被清空了,则重新开始存储录波数据
		if (m_nFFTStatePhaseDelt == CAPDEV_SMV_FFTStatePhaseDelt_Rcd)
		{
			m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Init;
		}

		return;
	}

	if(m_nFFTStatePhaseDelt==CAPDEV_SMV_FFTStatePhaseDelt_Init)
	{
		m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Rcd;
		m_nFFTIndexPhaseDelt = 0;
		m_nFirstRcdPointTime = pDatas->n64Time;

		if (m_bHasDelayTimeCh)
		{
			m_dwTimeDelay = pDatas->pDatas[m_nDelayTimeChIndex].dwValue;
		}
		else
		{
			m_dwTimeDelay = 0;
		}
		
		m_nCurrTimeDataCh = pCCapDeviceMngr->m_nTimeDataCh;
		pCCapDeviceMngr->m_oTimeDataList.GetLastMemVal(m_nCurrAnalogZeroTime);
	}

	CCapDeviceSmvCh *pChSmv = NULL;
	long nChIndex = 0;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pChSmv = (CCapDeviceSmvCh*)GetNext(pos);
		m_dVariable_FftPhaseDeltPoint[nChIndex][m_nFFTIndexPhaseDelt] = pChSmv->m_fChRate * pDatas->pDatas[nChIndex].dwValue;
		nChIndex++;
	}

	m_nFFTIndexPhaseDelt++;

	if (m_nFFTIndexPhaseDelt > CAP_FFT_CAL_POINTS)//当前通道中保存的采样点数大于1200时,开始进行采样计算
	{
		m_nFFTStatePhaseDeltCount++;

		if (m_nFFTStatePhaseDeltCount < FFT_STATE_CAL_DELAY_TIME_CYCLES)
		{
			//前几次的数据不做角差计算使用，
			m_nFFTStatePhaseDelt   = CAPDEV_SMV_FFTStatePhaseDelt_Init;		
			m_nFFTIndexPhaseDelt   = 0;
			return;
		}

		int nMaxIndex = 0;
		memset(m_fPhaseForPhaseDelta,  0x0,  sizeof(double)  *  256);
		memset(m_fChs_Freq,  0x0,  sizeof(double)  *  256);
		double  dMag[256] =  {0},    dPhase[256]  = {0},   dFreq[256] =  {0};
		int nPointCnt = 1024;
//		UseFirstCircleDataRepeat_Debug(pDatas->dwDatas);

		for (nChIndex = 0;  nChIndex < pDatas->dwDatas; nChIndex++)
		{
			dFreq[nChIndex] = 50;//频率固定50Hz
			//该函数,计算完相位差了90°,且原始数据被修改,故后面需要补偿90°
			memcpy(m_dVariable_FftPhaseDeltPoint[255],m_dVariable_FftPhaseDeltPoint[nChIndex],sizeof(double)*1200);
			AfxCalcFFT(m_dVariable_FftPhaseDeltPoint[nChIndex], nPointCnt, m_nSmpRate, dMag[nChIndex], dPhase[nChIndex], dFreq[nChIndex]);
			//FFT计算过程中,会把原始数据值修改,此操作为先存到最后1个通道,再拷贝回来,最后1个通道不做数据存储使用
			memcpy(m_dVariable_FftPhaseDeltPoint[nChIndex],m_dVariable_FftPhaseDeltPoint[255],sizeof(double)*1200);
			m_fPhaseForPhaseDelta[nChIndex]  =    dPhase[nChIndex] + 90.0f + 360.0f*50.0f/m_nSmpRate;
			m_fChs_Freq[nChIndex] = dFreq[nChIndex];
			MakeAngleTo360(m_fPhaseForPhaseDelta[nChIndex]);
		}

		m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Finished;
	}
}

void CCapDevice6044::UseFirstCircleDataRepeat_Debug(long nChs)
{
	for (int nPointIndex = 10;nPointIndex<1024;nPointIndex++)
	{
		for (int nChIndex = 0;nChIndex<nChs;nChIndex++)
		{
			m_dVariable_FftPhaseDeltPoint[nChIndex][nPointIndex] = m_dVariable_FftPhaseDeltPoint[nChIndex][nPointIndex%10];
		}
	}
}

long CCapDevice6044::GetPkgHeadTimeNs()
{
	if (m_dBaudRate<0.0001f)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前波特率(%lf)异常,无法进行报文头时间计算."),m_dBaudRate);
		return 0;
	}

	double dNsTime = 16*1000.0f/m_dBaudRate;//2个字节16bit,对应的ns时间
	return dNsTime;
}

BOOL CCapDevice6044::TimeDelayCalFinish()
{
	if (g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)
	{
		if(m_nFFTStatePhaseDelt!=CAPDEV_SMV_FFTStatePhaseDelt_Init)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else if (g_oCapAnalysisConfig.m_bMU_Test && m_bLinkState)
	{
		return TRUE;
	}

	return FALSE;
}
void CCapDevice6044::AnalysisStateValueChangedCount( PEPCAPPARSEDATAS pDatas )
{
	if (m_oPrevDatas.dwDatas == 0)
	{
		return;
	}	

	long nIndex = 0;
	PEPCAPPARSEDATA pPreChData = NULL,pCurrChData = NULL;
	for (nIndex = 0;  nIndex  <  pDatas->dwDatas; nIndex++)
	{
		pPreChData = &m_oPrevDatas.pDatas[nIndex];
		pCurrChData = &pDatas->pDatas[nIndex];

		//if (pCurrChData->dwValue < 0)
		//{
		//	continue;
		//}

		if (m_nChType[nIndex] != CAPDEVICE_CHTYPE_B)
		{
			continue;
		}

		if (pPreChData->dwValue != pCurrChData->dwValue)
		{
			m_nStateValueChangedCount++;
		}
	}
}
