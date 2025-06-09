//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceSmvBase.cpp  CCapDeviceSmvBase


#include "stdafx.h"
#include "CapDeviceSmvBase.h"

CCapDeviceSmvBase::CCapDeviceSmvBase()
{
	m_dwTimeDelay  = 0 ;
	m_dwTimeDelayForRes = 0;
	m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Init;
	m_nFFTIndexPhaseDelt = 0;
	m_nFFTStatePhaseDeltCount = 0;
	//��ʼ������
	m_nSampleRate = 4000;
	m_nAsduNum = 0;
	m_nRefChIndex = 1;//Ĭ�ϵ�һ��ͨ��Ϊ��ʱͨ��,�Եڶ���ͨ��Ϊ�ο���׼ͨ��
	for(int i = 0; i < STT_CAP_RCD_SMV_DISCRET_MAX_COUNT; i++)
	{
		m_nDisCretNum[i] = 0;
	}

	for (int nIndex = 0;nIndex<STCAPPARSE_DATA_MAX_COUNT;nIndex++)
	{
		m_nChType[nIndex] = CAPDEVICE_CHTYPE_I;
		m_nChAngType[nIndex] = 0;
	}

	m_nChType[0] = CAPDEVICE_CHTYPE_T;
	m_nCurrTimeDataCh = 0;
	m_nCurrAnalogZeroTime = 0;

	//��ʼ����Ա����
}

CCapDeviceSmvBase::~CCapDeviceSmvBase()
{
}

CCapDeviceSmvCh* CCapDeviceSmvBase::GetRefCh()
{
	CCapDeviceSmvCh *pCapDeviceSmvCh = (CCapDeviceSmvCh*)GetAt(m_nRefChIndex);
	return pCapDeviceSmvCh;
}

void CCapDeviceSmvBase::analysis92(PEPCAPPARSEDATAS pDatas)
{
	CCapDeviceBase::analysis92(pDatas);
}

void CCapDeviceSmvBase::SetDeviceChMaps()
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

void CCapDeviceSmvBase::GetSttCapParas(CDataGroup *pSttParas)
{
	CCapDeviceBase::GetSttCapParas(pSttParas);
}

void CCapDeviceSmvBase::InitNameAndID(long nTypeCount)
{
	CCapDeviceBase::InitNameAndID(nTypeCount);
}

BOOL CCapDeviceSmvBase::Compare(PEPCAPBUFFERITEM pItemData)
{
	return CCapDeviceBase::Compare(pItemData);
}

BOOL CCapDeviceSmvBase::PhaseDeltaCalFinish()
{
	if(m_nFFTStatePhaseDelt==CAPDEV_SMV_FFTStatePhaseDelt_Finished || 
		m_nFFTStatePhaseDeltCount >= FFT_STATE_CAL_DELAY_TIME_CYCLES+2)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CCapDeviceSmvBase::AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas)
{

}

void CCapDeviceSmvBase::UpdateErrorTypeNum()
{

}

void CCapDeviceSmvBase:: Reset()  //��ʼץ������λ֮ǰ��״̬
{
	CCapDeviceBase::Reset();
	
//	m_nFFTState = 0;
//	m_nFFTIndex = 0;

//	m_nFFTStateComp = 0;
//	m_nFFTIndexComp = 0;

//	m_nFFTStateCount = 0;
//	m_strComtradeFile.Empty();
//	m_dTimeDelay = -1;

	m_nFFTStatePhaseDelt = CAPDEV_SMV_FFTStatePhaseDelt_Init;
	m_nFFTStatePhaseDeltCount = 0;
	m_nFFTIndexPhaseDelt = 0;	
	m_dwTimeDelayForRes = 0;
	m_nCurrTimeDataCh = 0;
	m_nCurrAnalogZeroTime = 0;
//	m_fZeroDelta = 0;
//	m_nFFTStateCountComp = 0;
}