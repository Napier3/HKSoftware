//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDevice92.cpp  CCapDevice92

#include "stdafx.h"
#include "CapDevice92.h"


#include "../../../Record/FFT/FFT.h" // mym add 2020-6-25 ;
#include "../../../API/MathApi.h"
#include "../../../Record/RecordTest/CalFunctions.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCapDevice92::CCapDevice92()
{
	//��ʼ������

	//��ʼ����Ա����
	ZeroMemory(m_dVariable_Fft, CAP_FFT_CAL_POINTS*sizeof(double));

	m_nFFTIndex  = 0;
	m_nFFTState   = 0 ;   // ���ӣ�State����������ʼ״̬ = 0����¼��������״̬ = 1����¼��� = 2��

	m_nFFTIndexComp  = 0;
	m_nFFTStateComp   = 0 ; 

	m_nFFTStateCount = 0;	
	m_dwTimeDelay  = 0 ;
	m_nFFTStateCountComp = 0;
	m_nFirstCW_Index = 0;

	m_fPhase = 0;
	m_fMag = 0;
	m_fFreq = 0;
	m_dTimeDelay = -1;
	m_fZeroDelta = 0;

	memset(m_oFirstCW_RcdDatas, 0,sizeof(double)*255*800);
}

CCapDevice92::~CCapDevice92()
{
}

void CCapDevice92::InitDevice(CIecCfgDataBase *pIecCfgData)
{
	m_pIecCfgData = pIecCfgData;
	
	if(pIecCfgData == NULL)
	{
		return;
	}

	CIecCfg92Data* pCfgData92 = (CIecCfg92Data*)pIecCfgData;

	m_strSVID = pCfgData92->m_strSVID;
	m_dwAppID = pCfgData92->m_dwAppID;
	m_nType = PROTOCOL_61850_TYPE_92;
	m_strDestAddress = pCfgData92->m_strDestAddress;
	m_strSrcAddress = pCfgData92->m_strSrcAddress;
	m_strDataSet = pCfgData92->m_strDataSet;
	m_nConfRev = pCfgData92->m_dwVersion;
	m_nSmpSynch = pCfgData92->m_nSyn;

	CCapDeviceBase::InitDevice(pIecCfgData);
}

void CCapDevice92::GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas)
{
	CCapDeviceSmvCh *pSmvCh = NULL;

	for (int nIndex = 0;nIndex<GetCount();nIndex++)
	{
		pSmvCh = (CCapDeviceSmvCh *)GetAtIndex(nIndex);
		pSmvCh->m_dwValue = pParseDatas->pDatas[nIndex].dwValue;
		pSmvCh->m_dwQuality = pParseDatas->pDatas[nIndex].dwValue2;
		pSmvCh->m_fValue = pSmvCh->m_dwValue * pSmvCh->m_fChRate;
	}
}

extern long g_nIsFirstCWTest;

void CCapDevice92::AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead,long nBufferLenth)
{
	if (g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)
	{
		AnalysisData_DelayTime(pDatas);
	}

	if (g_oCapAnalysisConfig.m_bAnalysisData_Complex)
	{
		AnalysisData_Complex(pDatas);
	}

	if (g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt)
	{
		AnalysisData_PhaseDelt(pDatas);
	}

	if (g_oCapAnalysisConfig.m_bChQualitySpy)
	{
		GetOriginalDatas(pDatas);
	}

	//�����ǰ������Ϊ���ܲ�����,�������ܲ��ĵ�����δ����,��ʼ�������ܲ�������ȡ
	if (g_nIsFirstCWTest && m_nFirstCW_Index< 800)
	{
		GetFirstCWDatas(pDatas);
	}
}

void CCapDevice92::GetFirstCWDatas(EPCAPPARSEDATAS* pParseDatas)
{
	if (m_nFirstCW_Index == 0)
	{
		if (IsFirstCW_FirstData(pParseDatas))
		{
		}
	} 
	else
	{
	}
}

BOOL CCapDevice92::IsFirstCW_FirstData(EPCAPPARSEDATAS* pParseDatas)
{
	BOOL bIsFirstData = FALSE;

	for (int nChIndex = 0;nChIndex < pParseDatas->oData92.nChCount;nChIndex++)
	{
		if (m_nChType[nChIndex] ==  CAPDEVICE_CHTYPE_T)
		{
			continue;
		}

		if (pParseDatas->pDatas[nChIndex].dwValue == 0)
		{
			continue;
		}

		if (m_oPrevDatas.pDatas[nChIndex].dwValue == 0)
		{
			bIsFirstData = TRUE;
			break;
		}
	}

	return bIsFirstData;
}


//���ݽ��ܳ�ʱ
BOOL CCapDevice92::IsDataRcvOverTime()
{
	return m_oTickCount.GetTickCountLong(FALSE) > 2000; //����ֵ���ݳ���2sδ�յ���Ϊ��ʱ
}

BOOL CCapDevice92::TimeDelayCalFinish()
{
	if (g_oCapAnalysisConfig.m_bAnalysisData_DelayTime)
	{
		if(m_nFFTState  == 2  ||  m_nFFTStateCount   >=  FFT_STATE_CAL_DELAY_TIME_CYCLES  +  2)
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


// mym 2020-6-25 add SV��ʱ���㣻 
void CCapDevice92::AnalysisData_DelayTime(PEPCAPPARSEDATAS pDatas)
{
	long nIndex = 0;
	if (m_oPrevDatas.dwDatas == 0)
		return;

	// mym 2020-12-15 ע����
//	if(TimeDelayCalFinish())
// 		return;

	int nCurSmpCnt = pDatas->oData92.Asdu[0].smpCnt;
	CCapDeviceSmvCh *pChSmv  = (CCapDeviceSmvCh*)GetAtIndex(1);

	if(m_nFFTState==0)
	{
		long nNS = pDatas->n64Time & 0xFFFFFFFF;
		double m    = 	nNS ;

		if (nCurSmpCnt==0)
		//if(nNS  < 249999)
		{
			m_nFirstRcdPointTime = pDatas->n64Time;
			m_nTimeOffset = nNS;
			CString strText;
			ep_cap_timeval_to_string_ns(m_nFirstRcdPointTime, m_strTimeDelay);
			m_nSmpleCount = pDatas->oData92.Asdu[0].smpCnt;
			long nGap = 4000 - m_nSmpleCount;
			m_dTimeDelay = nGap * 250;

			if ( _CAL_DELAY_TIME_USE_SAMPLECOUNT_)
			{
				m_nFFTState = 2;

                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" [%s   %04X] Delay Time.... ")
                                           , m_strDestAddress.GetString(), m_dwAppID);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" 64Time = %I64u"),m_nFirstRcdPointTime); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" Sample Count = %d"),m_nSmpleCount); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" m_dTimeDelay = %f"),m_dTimeDelay); 
			}
			else
			{
				m_dwTimeDelay    = pDatas->pDatas[0].dwValue;
				m_dVariable_Fft[0] = pDatas->pDatas[1].dwValue;
				m_dVariable_Fft[0] *= pChSmv->m_fChRate;
				m_nFFTState = 1;
				m_nFFTIndex = 1;
			}
		}
	}
	else if(m_nFFTState==1)
	{	
		m_dVariable_Fft[m_nFFTIndex] = pChSmv->m_fChRate * pDatas->pDatas[1].dwValue;
		m_nFFTIndex++;

		if (m_nFFTIndex > CAP_FFT_CAL_POINTS)
		{
			m_nFFTStateCount++;

			if (m_nFFTStateCount < FFT_STATE_CAL_DELAY_TIME_CYCLES)
			{//��һ�ν��룬������
				m_nFFTState   = 0;		
				m_nFFTIndex  = 0;
				return;
			}

			memcpy(m_dSttCapRcdData,	 m_dVariable_Fft,	sizeof(double)	*	STT_CAP_RCD_SMV_DATA_MAX_COUNT);
			double dFirstVal = m_dVariable_Fft[0];
			double dMag =  0,  dPhase  = 0, dFreq =  0;
			AfxCalcFFT(m_dVariable_Fft,  1024,  4000,  dMag,  dPhase,  dFreq);	//pRtChAttrVal->dFundValue ,pRtChAttrVal->dFundPhase, dFreq);

			// ��Ҫ�ж�dMagֵ��Ϊ0�����Ϊ0�������Ϊ��Ч�ģ����������g_nFFTState�ó�0�����¿�ʼ���㣻
			//Ƶ��ҲҪ�ж�dFreq ��50HZ���ң�			
			if (dMag > 0.1 && (48 <= dFreq && dFreq <= 52)	 )
			{
				m_fMag = dMag;
				m_fFreq = dFreq;
				m_fPhase = dPhase ;
			
				double dCal = dMag * 1.414159;//���ֵ��
				double d = dCal;
				dCal = dFirstVal / dCal;
				m_fPhase = asin(dCal) * _180_D_PI;
                m_dTimeDelay = fabs (m_fPhase) / 4.5 * 250.0;  //�����΢��ʱ��  //-4.5  250us ��Ӧ ��4.5  // 360  / 4.5 du

                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" Cal Begin Time = %s"),m_strTimeDelay.GetString());
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" [%s   %04X] Delay Time.... ")
                                           , m_strDestAddress.GetString(), m_dwAppID);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" 64Time = %I64u"),m_nFirstRcdPointTime); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" Sample Count = %d"),m_nSmpleCount); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" dFreq = %f"),dFreq); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" dPhase = %f"),dPhase); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" Mag = %f"),dMag); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" fChRate = %f"),pChSmv->m_fChRate); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" m_dTimeDelay = %f"),m_dTimeDelay); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" m_nFFTState = %d  m_nFFTStateCount = %d"),m_nFFTState, m_nFFTStateCount); 				

				m_strSvSynChID = pChSmv->m_strID;
				m_dSvSynChCoef = pChSmv->m_fChRate;

				WriteRcdFile(m_dSttCapRcdData, STT_CAP_SMV_SYN_RCD_MAX_COUNT);

				m_nFFTState = 2;
				m_nFFTIndex  = 0;
			}
			else 
			{
				m_nFFTState   = 0;		
				m_nFFTIndex  = 0;
			}
		}
	}
}

void cap_cal_har(long *pLong, double &dValue, double &dAngle)
{
	RTCALFUNCPARA oRtFunPara;
	RTCHANNELATTRVALUE oCalValue;
	ZeroMemory(&oRtFunPara, sizeof(RTCALFUNCPARA));
	ZeroMemory(&oCalValue, sizeof(RTCHANNELATTRVALUE));

	oCalValue.dFrequency = 50;
	oRtFunPara.pRefRtChAttrVal = &oCalValue;
	oRtFunPara.dCeofValue = 0.001;
	oRtFunPara.dwSampleRate = 4000;
	oRtFunPara.nBuffer1Len = 80;
	oRtFunPara.nBuffer1Pos = 0;
	oRtFunPara.pnBuffer_long = pLong;
	oRtFunPara.nDataLength = 1200;
	oRtFunPara.nBufferLength = 1200;

	oRtFunPara.nDftBuffer1Pos = 0;
	oRtFunPara.nDftBuffer2Pos = -1;
	oRtFunPara.nDftBuffer1Len = 80;
	oRtFunPara.nDftBuffer2Len = 0;

	CalHar(0, &oRtFunPara, dValue ,dAngle);
}

// mym 2020-9-16 ����ǲ 
void CCapDevice92::AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas)
{
	long nIndex = 0;

	if (m_oPrevDatas.dwDatas == 0)
		return;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int nCurSmpCnt = pDatas->oData92.Asdu[0].smpCnt;

// 	__int64 nCur = (pDatas->n64Time >> 32) * 1000000000 + (pDatas->n64Time & 0xFFFFFFFF);
// 	__int64 nPre = (m_oPrevDatas.n64Time >> 32) * 1000000000 + (m_oPrevDatas.n64Time & 0xFFFFFFFF);
// 
// 	__int64 nErrorValue = nCur-nPre;
// 
// 	if ((nErrorValue)>300000)
// 	{
// 		CString strText1,strText2;
// 		ep_cap_timeval_to_string_ns(pDatas->n64Time, strText1);
// 		ep_cap_timeval_to_string_ns(m_oPrevDatas.n64Time, strText2);
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���ʱ��(%lld)��ǰʱ��(%s),�ϴ�ʱ��(%s)."),nErrorValue,strText1.GetString(),strText2.GetString());
// 	}

	//�����Ƿ���Ҫ��ȡ��ͬͨ����ָ�룬ȥ��ȡͨ��ϵ����
	CCapDeviceSmvCh *pChSmv[256] = {0};
	for (int i = 0;   i  <  pDatas->oData92.nChCount/*/8*/  ;  i++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
		pChSmv[i]   =  (CCapDeviceSmvCh*)GetAtIndex(i);

	if (nCurSmpCnt==0)
	{
		long nNS = pDatas->n64Time & 0xFFFFFFFF;
		CString strText;
		//ep_cap_timeval_to_string_ns(m_n64Time, strText);

		ep_cap_timeval_to_string_ns(pDatas->n64Time, strText);

		struct timeval ts;
		EPTIME64EX tm;
		ts.tv_sec = pDatas->n64Time >> 32;
		ts.tv_usec = pDatas->n64Time & 0xFFFFFFFF;
		long ns = ts.tv_usec  % 1000;
		ts.tv_usec /= 1000;
		ep_cap_timeval_to_64timeex(ts, tm);

		//Ep_EPTIME64Ex_To_String(tm, strTime);
		//strTime.AppendFormat(_T(".%d"), ns);

		//��ȡ������������0��,���ձ��Ķ����ʱ���,����װ�÷������ĵ����շ��յ�����֮���ʱ���(��λ:΢��)
		m_fZeroDelta =  tm.wMilliseconds * 1000 +  tm.wMicrosecond + (double)ns/1000.0;

// 		if (m_fZeroDelta>10000)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��������10000(%lf)��ǰʱ��(%s)."),m_fZeroDelta,strText.GetString());
// 		}
	}

	if(m_nFFTStatePhaseDelt==CAPDEV_SMV_FFTStatePhaseDelt_Init)
	{
		long nNS = pDatas->n64Time & 0xFFFFFFFF;

		if(nNS  < 249999)//�ҵ������,�ĵ�һ����ı���,����250000ns 1����,ʱ����С��250000
			//if (nCurSmpCnt==0)
		{
			m_nFirstRcdPointTime = pDatas->n64Time;
			m_dwTimeDelay = pDatas->pDatas[0].dwValue;

			m_dwTimeDelayForRes  = pDatas->pDatas[0].dwValue;//Ĭ�ϵ�һ��ͨ��Ϊ��ʱͨ��,��¼��ʱͨ����

			for (int nChIndex = 1;  nChIndex < pDatas->oData92.nChCount/*/8 */; nChIndex++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
			{
				if ( pChSmv[nChIndex] != NULL)//�洢�����,��һ���������ֵ,Ĭ�ϵ�һ��ͨ��Ϊ��ʱͨ��,m_dVariable_FftPhaseDeltPoint�в�������ʱͨ��������ֵ
				{
					m_dVariable_FftPhaseDeltPoint[nChIndex-1][0/*m_nFFTIndexPhaseDelt*/] =   pChSmv[nChIndex]->m_fChRate * pDatas->pDatas[nChIndex].dwValue;
					m_nVariable_FftPhaseDeltPoint[nChIndex-1][0/*m_nFFTIndexPhaseDelt*/] = m_dVariable_FftPhaseDeltPoint[nChIndex-1][0/*m_nFFTIndexPhaseDelt*/] ;
				}
			}

			m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Rcd;
			m_nFFTIndexPhaseDelt = 1;
		}
	}
	else if(m_nFFTStatePhaseDelt==CAPDEV_SMV_FFTStatePhaseDelt_Rcd)
	{	
		for (int nChIndex = 1;  nChIndex < pDatas->oData92.nChCount/*/8*/; nChIndex++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
		{
			if ( pChSmv[nChIndex ] !=NULL)
			{
				m_dVariable_FftPhaseDeltPoint[nChIndex-1][m_nFFTIndexPhaseDelt] =   pChSmv[nChIndex]->m_fChRate * pDatas->pDatas[nChIndex].dwValue;
				m_nVariable_FftPhaseDeltPoint[nChIndex-1][m_nFFTIndexPhaseDelt] = m_dVariable_FftPhaseDeltPoint[nChIndex-1][m_nFFTIndexPhaseDelt]*100 ;
			}
		}

		m_nFFTIndexPhaseDelt++;

		if (m_nFFTIndexPhaseDelt > CAP_FFT_CAL_POINTS)//��ǰͨ���б���Ĳ�����������1200ʱ,��ʼ���в�������
		{
			m_nFFTStatePhaseDeltCount++;

			if (m_nFFTStatePhaseDeltCount < FFT_STATE_CAL_DELAY_TIME_CYCLES)
			{
				//��һ�ν��룬������
				m_nFFTStatePhaseDelt   = CAPDEV_SMV_FFTStatePhaseDelt_Init;		
				m_nFFTIndexPhaseDelt   = 0;
				return;
			}

			m_nChnelCnt = pDatas->oData92.nChCount;
			int nMaxIndex = 0;
			memset(m_fPhaseForPhaseDelta,  0x0,  sizeof(double)  *  256);
			memset(m_fChs_Freq,  0x0,  sizeof(double)  *  256);
			double  dMag[256] =  {0},    dPhase[256]  = {0},   dFreq[256] =  {0};
			double dFirstPointNS = m_nFirstRcdPointTime & 0xFFFFFFFF;
			double dBeginCompAngle = 4.5*dFirstPointNS/(250*1000);

			for (int nChIndex = 0;  nChIndex < pDatas->oData92.nChCount/*/8 */ -  1; nChIndex++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
			{	
				dFreq[nChIndex] = 50;//Ƶ�ʹ̶�50Hz
				int nPointCnt = 1024;
				//�ú���,��������λ����90��,��ԭʼ���ݱ��޸�,�ʺ�����Ҫ����90��
				AfxCalcFFT(m_dVariable_FftPhaseDeltPoint[nChIndex], nPointCnt, 4000, dMag[nChIndex], dPhase[nChIndex], dFreq[nChIndex] ); //pRtChAttrVal->dFundValue ,pRtChAttrVal->dFundPhase, dFreq);
				m_fChs_Freq[nChIndex] = dFreq[nChIndex];

				// ��Ҫ�ж�dMagֵ��Ϊ0�����Ϊ0�������Ϊ��Ч�ģ����������g_nFFTState�ó�0�����¿�ʼ���㣻
				//Ƶ��ҲҪ�ж�dFreq ��50HZ���ң�		

				m_fPhaseForPhaseDelta[nChIndex]  =    dPhase[nChIndex]   +    (m_dwTimeDelayForRes/250) * 4.5 + 90 - dBeginCompAngle;//����ʱ����λ+��ʱ��������λֵ
				m_fPhaseForPhase[nChIndex]  = m_fPhaseForPhaseDelta[nChIndex] /* dPhase[nChIndex]  / *dAngAbs* / +    ((m_dwTimeDelayForRes / *+ m_fZeroDelta* /)/250) * 4.5 */ ;//dPhase[0] ; 

				MakeAngleTo360(m_fPhaseForPhase[nChIndex]);
				MakeAngleTo360(m_fPhaseForPhaseDelta[nChIndex]);
			}

			m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Finished;
		}
	}
}

BOOL CCapDevice92::ComplexCalFinish()
{
	if(m_nFFTStateComp==2 || m_nFFTStateCountComp >= FFT_STATE_CAL_DELAY_TIME_CYCLES+2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

long CCapDevice92::GetFirstCW_ChDatasIndex(long nChIndex)
{
	if (m_nChType[nChIndex] == CAPDEVICE_CHTYPE_T)
	{
		return -1;
	}

	long nGroupIndex = m_nChAngType[nChIndex]/4;
	long nAngIndex = m_nChAngType[nChIndex]%4;

	if ((nGroupIndex>1) || (nAngIndex == 3))
	{
		return -1;
	}

	long nChDataIndex = nAngIndex + nGroupIndex*3;

	if (m_nChType[nChIndex] == CAPDEVICE_CHTYPE_U)
	{
		return nChDataIndex;
	}

	return nChDataIndex+6;
}

//���㸴����
void CCapDevice92::AnalysisData_Complex(PEPCAPPARSEDATAS pDatas)
{
	long nIndex = 0;
	if (m_oPrevDatas.dwDatas == 0)
		return;

	//if(ComplexCalFinish())
	//	return;

	int nCurSmpCnt = pDatas->oData92.Asdu[0].smpCnt;

	//CCapDeviceSmvCh *pChSmv  = (CCapDeviceSmvCh*)GetAtIndex(1);
	CCapDeviceSmvCh *pChSmv[256] = {0};
	for (int i = 0;   i  <  pDatas->oData92.nChCount/*/8*/ ;  i++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
		pChSmv[i]   =  (CCapDeviceSmvCh*)GetAtIndex(i);

	if(m_nFFTStateComp==0)
	{
		long nNS = pDatas->n64Time & 0xFFFFFFFF;
		//double m = 	nNS ;

		if(nNS  < 249999)
		{
			m_nSmpleCount = pDatas->oData92.Asdu[0].smpCnt;
			/*
			m_n64Time = pDatas->n64Time;
			m_nTimeOffset = nNS;

		
			long nGap = 4000 - m_nSmpleCount;
			m_dTimeDelay = nGap * 250;

			if ( _CAL_DELAY_TIME_USE_SAMPLECOUNT_)
			{
				m_nFFTState = 2;

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" [%s   %04X] Delay Time.... "), m_strDestAddress, m_dwAppID); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" 64Time = %I64u"),m_n64Time); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" Sample Count = %d"),m_nSmpleCount); 
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T(" m_dTimeDelay = %f"),m_dTimeDelay); 
			}
			else
			*/
			{
				//m_dwTimeDelay       =  pDatas->pDatas[0].dwValue;
				//m_dVariable_Fft[0]   =  pDatas->pDatas[1].dwValue;
				//m_dVariable_Fft[0] *=   pChSmv->m_fChRate;
				int j = 0;
				for (j  =  0;  j < pDatas->oData92.nChCount/*/8*/  - 1;  j++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
					m_dVariable_FftPoint[j][m_nFFTIndexComp] =   pChSmv[j  + 1]->m_fChRate * pDatas->pDatas[j  +  1].dwValue;

				m_nFFTStateComp = 1;

				m_nFFTIndexComp = 1;
			}
		}
	}
	else if(m_nFFTStateComp==1)
	{	
		//m_dVariable_Fft[m_nFFTIndexComp]   =  pChSmv->m_fChRate * pDatas->pDatas[1].dwValue;

		m_nChnelCnt   =  pDatas->oData92.nChCount;
		int j = 0;
		for (j = 0;  j < pDatas->oData92.nChCount/*/8*/  - 1; j++)//20220614 zhouhj ���ڸ�ֵλ��ͳһ�������8������
			m_dVariable_FftPoint[j][m_nFFTIndexComp]     =    pChSmv[j + 1]->m_fChRate * pDatas->pDatas[j + 1].dwValue;

		//��ȡͨ��������		
		m_nFFTIndexComp++;

		if (m_nFFTIndexComp > CAP_COMP_CNT  +  8)
		{
			m_nFFTStateCountComp++;

			if (m_nFFTStateCountComp < FFT_STATE_CAL_DELAY_TIME_CYCLES)
			{//��һ�ν��룬������
				m_nFFTStateComp   = 0;		
				m_nFFTIndexComp   = 0;
				return;
			}

			m_nFFTStateComp   = 2;  //==2�ͱ�ʾ�����ˣ�
			//m_nFFTIndexComp  = 0;
		}
	}
}

// mym 2020-9-17 �������ֵ�� 
void CCapDevice92::FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo)
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
	nMaxNo = nIndex;       //�ҵ������ֵ����ţ�
}

void	CCapDevice92:: Reset()  //��ʼץ������λ֮ǰ��״̬
{
	CCapDeviceBase::Reset();
	
	m_nFFTState = 0;
	m_nFFTIndex = 0;

	m_nFFTStateComp = 0;
	m_nFFTIndexComp = 0;

	m_nFFTStateCount = 0;
	m_strComtradeFile.Empty();
	m_dTimeDelay = -1;

	m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Init;
	m_nFFTStatePhaseDeltCount = 0;
	m_nFFTIndexPhaseDelt = 0;	
	m_dwTimeDelayForRes = 0;
	m_fZeroDelta = 0;
	m_nFFTStateCountComp = 0;
}

void CCapDevice92::WriteRcdFile(double *pdLong, long nWriteCount)
{
	if (g_n_write_SyncDelt_Rcd_file_Mode == 0)
	{
		return;
	}

	if (g_n_write_SyncDelt_Rcd_file_Mode == 1)
	{
		cap_WriteRcdFile_Txt(pdLong, nWriteCount);
		return;
	}

	if (g_n_write_SyncDelt_Rcd_file_Mode == 2)
	{
		WriteRcdFile_Comtrade(pdLong, nWriteCount);
		return;
	}
}

void cap_WriteRcdFile_Txt(double *pdLong, long nWriteCount, const CString &strName)
{
#ifndef _PSX_IDE_QT_
	CString strText;
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	strText = _P_GetLibraryPath();

	if (strName.GetLength() > 0)
	{
		strText.AppendFormat(_T("%s%d%d.txt"), strName, tmSys.wMinute, tmSys.wSecond);
	}
	else
	{
	strText.AppendFormat(_T("SvDelayTime%d%d.txt"), tmSys.wMinute, tmSys.wSecond);
	}

	CFile oFile;
	CLogPrint::LogString(XLOGLEVEL_TRACE, strText);
	long nIndex = 0;

	if (oFile.Open(strText, CFile::modeCreate | CFile::modeWrite))
	{
		for (nIndex=0; nIndex<nWriteCount; nIndex++)
		{
			strText.Format(_T("%f\r\n"),pdLong[nIndex]); 
			oFile.Write(strText, strText.GetLength());
		}

		oFile.Close();
	}
#endif
}

void CCapDevice92::WriteRcdFile_Comtrade(double *pdLong, long nCount)
{
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);

	m_strComtradeFile.Format(_T("SvDelayT_%04X_%02d%02d.dat"), m_dwAppID, tmSys.wMinute, tmSys.wSecond); 
	CCapDeviceSmvCh *pChSmv  = (CCapDeviceSmvCh*)GetAtIndex(1);
	pChSmv->WriteRcdFile_Comtrade(pdLong, nCount, m_strComtradeFile);
}

void CCapDevice92::ClearAnalysisResultErrors()
{
	m_dMaxTimeDiscrete = 0;
	m_oAnalysisResults.dDeltTime = 0.0f;

	for (int i = 0; i < STT_CAP_RCD_SMV_DISCRET_MAX_COUNT; i++)
	{
		m_nDisCretNum[i] = 0;//20231020 dxy ���ʱ������ɢ��ͳ���������
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

void CCapDevice92::UpdateErrorTypeNum()
{
	long nErrorTypeNum = 0;

	for (int nIndex = 0;nIndex<PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM;nIndex++)
	{
		if (m_oAnalysisResults.rslt_92.nErrorType[0][nIndex]>0)
		{
			nErrorTypeNum++;
		}
	}

	if (nErrorTypeNum != m_nCurrErrorTypeNum)
	{
		m_nCurrErrorTypeNum = nErrorTypeNum;
		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("��ǰ�쳣��������(%ld)"),nErrorTypeNum);
	}
}

void CCapDevice92::SetDeviceChMaps()
{
	CCapDeviceSmvCh *pSmvCh = NULL;
	POS pos = GetHeadPosition();
	long nIndex = 0;

	while(pos)
	{
		pSmvCh = (CCapDeviceSmvCh *)GetNext(pos);
		m_nChType[nIndex] = pSmvCh->m_nChType;
		m_nChAngType[nIndex] = pSmvCh->m_nChAngType;
		nIndex++;
	}
}

void CCapDevice92::analysis92(PEPCAPPARSEDATAS pDatas)
{
	if (g_oCapAnalysisConfig.m_bMaxTimeDiscrete || g_oCapAnalysisConfig.m_bSvAnalysis
		|| g_oCapAnalysisConfig.m_bMU_Test)
	{
		ep_protocol_analysis92(&m_oPrevDatas,   pDatas,  &m_oAnalysisResults,m_nChType,m_nChAngType);  
		CalDiscretInterval();
		//�������жϻ�ȡ��ɢ�ȵ����ֵ
		if (fabs((double)m_dMaxTimeDiscrete)   <=  fabs((double)m_oAnalysisResults.dDeltTime))
			m_dMaxTimeDiscrete = m_oAnalysisResults.dDeltTime;
	}

	if (g_oCapAnalysisConfig.m_bPkgConsistence)
	{
		ep_consistence_analysis92();
	}

	for (int nIndex = 0; nIndex < pDatas->oData92.Num_ASDU; nIndex++)//20220615 zhouhj  ֻ��92���Ŀ��Ǵ˴�
	{
		if(pDatas->oData92.Asdu[nIndex].smpCnt == 0)//�жϵ�ǰ֡���Ƿ����������������0������
		{
			if (nIndex == 0)//����ڵ�һ��Asdu��,ȡǰһ֡�������һ��asdu����ֵ
			{
				m_oAnalysisResults.rslt_92.nSmpCountMaxValue = m_oPrevDatas.oData92.Asdu[pDatas->oData92.Num_ASDU-1].smpCnt + 1;
			}
			else
			{
				m_oAnalysisResults.rslt_92.nSmpCountMaxValue = pDatas->oData92.Asdu[nIndex-1].smpCnt + 1;
			}
		}
	}

	pDatas->nFirstPacket = 1; //mym 20202-6-21 �������ǰ֡�Ͱѱ�־��1��
}

void CCapDevice92::CalDiscretInterval()
{
	if (m_oAnalysisResults.dDeltTime > -250000)
	{
		if ((m_oAnalysisResults.dDeltTime < -10000))
	{
		m_nDisCretNum[0]++;
	}
		else if (m_oAnalysisResults.dDeltTime < -1000)
	{
		m_nDisCretNum[1]++;
	}
		else if (m_oAnalysisResults.dDeltTime < 0)
	{
		m_nDisCretNum[2]++;
	}
		else if (m_oAnalysisResults.dDeltTime == 0)
	{
		m_nDisCretNum[3]++;
	}
		else if (m_oAnalysisResults.dDeltTime < 1000)
	{
		m_nDisCretNum[4]++;
	}
		else if (m_oAnalysisResults.dDeltTime <10000)
	{
		m_nDisCretNum[5]++;
	}
		else if (m_oAnalysisResults.dDeltTime <250000)
		{
			m_nDisCretNum[6]++;
		}
	}
	
}