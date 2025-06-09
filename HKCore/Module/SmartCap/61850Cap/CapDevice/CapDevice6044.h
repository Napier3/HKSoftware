#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

#define  CAP_COMP_CNT        80
#define  TEST_CNT_NO_PPS  4000
#define STT_60044_PKG_MAX_LENGTH           1000

class CCapDevice6044 : public CCapDeviceSmvBase
{
public:
	CCapDevice6044();
	virtual ~CCapDevice6044();

	long m_nSmpRate;//������
	long m_nPkgLenth;//��֡�����ܳ���
	double m_dBaudRate;//������
	BOOL m_bDC_FT3;//���Ϊ�Ƿ���ֱFT3
	long m_nDelayTimeChIndex;//��ʱͨ��Index���ڿ��ٻ�ȡ��ʱͨ������ֵ
	BOOL m_bHasDelayTimeCh;//����Ƿ������ʱͨ��
	CString m_strSTMode;//ST��ģʽ   0-None 1-FT3  2-PPS      3-BCode
	long m_nFt3_CrcType;// 20240811 suyang ����FT3 CRC���� 0-��׼16�ֽ�У�飬1-����ĩβУ�飬2-��һ�����ݿ�14�ֽ�У��

	long m_nChByteLenth[STCAPPARSE_DATA_MAX_COUNT];//ͨ���ֽڳ���,���ڱ��Ľ���ʹ��
//	long m_nDebugIntervalTime;//���ʱ��
	long m_nStateValueChangedCount; //��λ����


//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE6044;};

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);
	virtual void ClearAnalysisResultErrors();
	virtual void analysis6044(PEPCAPPARSEDATAS pDatas);
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void Reset(); //��ʼץ������λ֮ǰ��״̬
	//2020-6-25  mym  ��ȡsmptCnt==0��ֵ��
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();
	virtual void GetSttCapParas(CDataGroup *pSttParas);
	virtual void InitNameAndID(long nTypeCount);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);

	long GetByteChValue(BYTE* pBuferHead,long &nCurrPos,long &nHasCrcLenth,long nChLenth,long nFT3CrcType);
	BOOL TimeDelayCalFinish();
	void UseFirstCircleDataRepeat_Debug(long nChs);
	long GetPkgHeadTimeNs();//��ȡ����ͷnsʱ��

	//2023/12/11 wangjunsheng ���ڽ���FT3ԭʼ��������
	char m_szPkgDatas[STT_60044_PKG_MAX_LENGTH];
	long m_nPkgDatasLenth;
protected:
	void FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo);
	//zhouhj 2024.3.11 ����ǲ�Ȳ�
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	virtual void AnalysisStateValueChangedCount(PEPCAPPARSEDATAS pDatas);//chenling 2024.5.30���㿪����λ����
};


