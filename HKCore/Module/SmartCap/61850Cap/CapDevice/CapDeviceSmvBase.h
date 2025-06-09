//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceSmvBase.h  CCapDeviceSmvBase

#pragma once

#include "CapDeviceBase.h"
#include "CapDeviceSmvCh.h"

//2020-07-25  lijunqing
#define STT_CAP_RCD_SMV_DATA_MAX_COUNT           400
#define STT_CAP_RCD_SMV_DISCRET_MAX_COUNT          7

#define FFT_STATE_CAL_DELAY_TIME_CYCLES            3

#define CAPDEV_SMV_FFTStatePhaseDelt_Init          0//��ʼ״̬ 
#define CAPDEV_SMV_FFTStatePhaseDelt_Rcd           1//¼��״̬ 
#define CAPDEV_SMV_FFTStatePhaseDelt_Finished      3//¼������״̬ 


class CCapDeviceSmvBase : public CCapDeviceBase
{
public:
	CCapDeviceSmvBase();
	virtual ~CCapDeviceSmvBase();


	long  m_nSampleRate;
	long  m_nAsduNum;
	long m_nRefChIndex;//20221213 zhouhj �ο�ͨ������  
	long m_nDisCretNum[STT_CAP_RCD_SMV_DISCRET_MAX_COUNT];//20231019 dxy ����ͳ����ɢ�ȷֲ����

	CString m_strDataSet;				//���ݼ�����

	//2020-07-25  lijunqing  ���ڼ�¼�ͱ�����������ļ�����ʱ����
	double m_dSttCapRcdData[STT_CAP_RCD_SMV_DATA_MAX_COUNT];
//���غ���
public:
	BOOL PhaseDeltaCalFinish();
	virtual void Reset(); 
	long  m_nFFTStatePhaseDelt ;// ���ӣ�State����������ʼ״̬=0����¼��������״̬=1����¼���=2��
	long m_nFFTIndexPhaseDelt ;//���нǲ����ĵ�ǰ��ֵ������Index,�ӱ���������һ���㿪ʼ����,ֱ������1200�㿪ʼ����FFT����
	long  m_nFFTStatePhaseDeltCount;
	//��һά��ͨ���ţ��ڶ�ά�ǲ���������Ĭ�ϵ�һ��ͨ��Ϊ������ʱ,�洢�ڶ���ͨ����ʼ����ͨ�����1200�������������ֵ,����
	double m_dVariable_FftPhaseDeltPoint[256][CAP_FFT_CAL_POINTS    +  10];
	//��һά��ͨ���ţ��ڶ�ά�ǲ���������Ĭ�ϵ�һ��ͨ��Ϊ������ʱ,�洢�ڶ���ͨ����ʼ����ͨ�����1200�������������ֵ,����
	//�ó�Ա���������´����߼���ʵ��δ�õ���ADMU����ʱ,����Ϊ�丳ֵ
	long m_nVariable_FftPhaseDeltPoint[256][CAP_FFT_CAL_POINTS    +  10];
	//����9-2����ͬ����ʱ.���Ϊ����ʱ����λֵ,�����ں�������ǲ�
	//����ADMU����ģ���������ʱ������ʱ,���Ϊ��ǰ��һ�������λֵ
	double   m_fPhaseForPhaseDelta[256];
	double   m_fChs_Freq[256];//zhouhj 20220818 ��¼ȫ��ͨ��Ƶ��
	DWORD m_dwTimeDelayForRes;//��ʱͨ����//Ĭ�ϵ�һ��ͨ��Ϊ��ʱͨ��,��¼��ʱͨ��ֵ
	__int64 m_nFirstRcdPointTime;  //��¼��һ��������ľ���ʱ��
	DWORD m_dwTimeDelay ;

	long m_nChType[STCAPPARSE_DATA_MAX_COUNT];//2023.7.10zhouhj  ������������˫AD��һ�´���
	long m_nChAngType[STCAPPARSE_DATA_MAX_COUNT];//2023.7.10zhouhj 

	int m_nCurrTimeDataCh;//���͵�ģ����ͨ����Ӧ�ĵ�ѹ������������ԴIndex
	__int64 m_nCurrAnalogZeroTime;  //��¼��һ��������ʱ,���µ�����ģ����ͨ����Ӧ�ľ���ʱ��

protected:
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	virtual void UpdateErrorTypeNum();//�����쳣��������

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceSmvCh();	}
	virtual void GetOriginalDatas(PEPCAPPARSEDATAS* pParseDatas){}
	virtual void SetDeviceChMaps();//20230710 zhouhj ����ͨ��ӳ�� 
	virtual void analysis92(PEPCAPPARSEDATAS pDatas);
	CCapDeviceSmvCh* GetRefCh();
	virtual void GetSttCapParas(CDataGroup *pSttParas);

	virtual void InitNameAndID(long nTypeCount);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);
};

