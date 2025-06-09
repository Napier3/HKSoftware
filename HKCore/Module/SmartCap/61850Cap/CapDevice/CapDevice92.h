//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDevice92.h  CCapDevice92

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

#define  CAP_COMP_CNT        80
#define  TEST_CNT_NO_PPS  4000

class CCapDevice92 : public CCapDeviceSmvBase
{
public:
	CCapDevice92();
	virtual ~CCapDevice92();

	CString m_strSVID;
	long m_nConfRev;
	long m_nSmpSynch;

	//ͬ������
	double m_oFirstCW_RcdDatas[255][800];//��һά��ͨ���ţ��ڶ�ά�ǵ���,���ܲ����Ե�¼������
	long m_nFirstCW_Index;//���ܲ�����Index���
	double m_dVariable_Fft[CAP_FFT_CAL_POINTS    +   10];
	double m_dVariable_FftPoint[256][CAP_COMP_CNT    +  10];//��һά��ͨ���ţ��ڶ�ά�ǲ���������

    int         m_nChnelCnt;
	long m_nFFTIndex ;
	long  m_nFFTState ;// ���ӣ�State����������ʼ״̬=0����¼��������״̬=1����¼���=2��

	//zhouhj 2024.3.8 �������
//	long  m_nFFTStatePhaseDelt ;// ���ӣ�State����������ʼ״̬=0����¼��������״̬=1����¼���=2��
//	long m_nFFTIndexPhaseDelt ;//���нǲ����ĵ�ǰ��ֵ������Index,�ӱ���������һ���㿪ʼ����,ֱ������1200�㿪ʼ����FFT����
//	long			m_nFFTStatePhaseDeltCount;


	long m_nFFTIndexComp ;
	long  m_nFFTStateComp ;// ���ӣ�State����������ʼ״̬=0����¼��������״̬=1����¼���=2��

	//����ʱ����λֵ
	double   m_fPhaseForPhase[256];//zhouhj 2024.3.29 �ó�Ա������m_fPhaseForPhaseDelta�ظ�,��������ɾ��
	double   m_fResponseTime;
	double   m_fResponseError;
	double   m_fZeroDelta;//��ȡ������������0��,���ձ��Ķ����ʱ���,����װ�÷������ĵ����շ��յ�����֮���ʱ���(��λ:΢��)
//	double   m_fDCValue[256];//�ڳ������ʱ,�Ѽ���ֱ�������˴������ظ�����  20220817 zhouhj



	long  m_nFFTStateCount;
	long  m_nFFTStateCountComp;

	double m_fPhase;
	double m_fMag;
	double m_fFreq;
	double m_dTimeDelay;
	CString m_strTimeDelay;

	long m_nTimeOffset;
//	__int64 m_n64Time;  �������,���Ƹ�Ϊm_nFirstRcdPointTime��¼��һ��������ľ���ʱ��
	long m_nSmpleCount;
	CString m_strComtradeFile;
	CString m_strSvSynChID;
	double m_dSvSynChCoef;


//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE92;};

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);
	virtual void ClearAnalysisResultErrors();
	virtual void SetDeviceChMaps();//20230710 zhouhj ����ͨ��ӳ�� 
	virtual void analysis92(PEPCAPPARSEDATAS pDatas);

	void GetFirstCWDatas(EPCAPPARSEDATAS* pParseDatas);
	BOOL IsFirstCW_FirstData(EPCAPPARSEDATAS* pParseDatas);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void Reset(); //��ʼץ������λ֮ǰ��״̬
	//2020-6-25  mym  ��ȡsmptCnt==0��ֵ��
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();
	//�Զ�������ɢ������ֵ
	void CalDiscretInterval();

	BOOL TimeDelayCalFinish();
	BOOL ComplexCalFinish();
	long GetFirstCW_ChDatasIndex(long nChIndex);

	virtual void UpdateErrorTypeNum();//�����쳣��������

protected:
	void AnalysisData_DelayTime(PEPCAPPARSEDATAS pDatas);
	void AnalysisData_Complex(PEPCAPPARSEDATAS pDatas);
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	void FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo);

	void WriteRcdFile(double *pdLong, long nWriteCount);
	void WriteRcdFile_Comtrade(double *pdLong, long nWriteCount);
};

void cap_WriteRcdFile_Txt(double *pdLong, long nWriteCount, const CString &strName=_T(""));

