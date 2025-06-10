//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttParas.h  CSttParas

#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
#include "../../Module/DataMngr/DataGroup.h"
#include "../../Module/Record/RtMemBuffer/MemBuffer_Float.h"
#include "../../Module/Record/Comtrade/ComtradeMngr.h"
#include "../../Module/AdjustTool/SttAdjDevice.h"
#include "../../Module/AdjustTool/SttAdjModule.h"

#ifndef REPLAY_DIGITAL_MODULE_CH_NUM
#define REPLAY_DIGITAL_MODULE_CH_NUM	12	
#endif


#ifndef STT_REPLAY_WEEK_MODULE_CH_EeType_VOL
#define STT_REPLAY_WEEK_MODULE_CH_EeType_VOL		"Voltage"
#endif

#ifndef STT_REPLAY_WEEK_MODULE_CH_EeType_Curr
#define STT_REPLAY_WEEK_MODULE_CH_EeType_Curr		"Current"
#endif

class CSttModuleChComtradeBind : public CExBaseObject
{//��������ģ�顢ͨ��
public:
	CSttModuleChComtradeBind();
	virtual ~CSttModuleChComtradeBind();

public:
	CDataGroup *m_pHdChRef;  //������У׼�����Ӳ��ͨ������
	double m_fMaxAbs;	//������ֵ
	double m_fMomentaryVal;	//������ֵ
	//zhouhj 2023.9.11 �˴��������m_nChA_Index��һ���ظ�,ͳһ�������
//	long m_nComtradeChID_A, m_nComtradeChID_B;//¼���ļ��е�ChID,��ѹ����ͳһ���
	CString m_strComtradeChID_A, m_strComtradeChID_B;
	double m_dCoefA, m_dCoefB, m_dK;
	long m_nChA_Index,m_nChB_Index;//����ͨ��Index,��Ӧ����������,0����ѡ��,������Ӧ�ڼ�����ѹ/����ͨ��(��ѹ�����������,����Ӧ�ڼ�����ѹ/����ͨ��)
	long m_nChSelected;

	CComtradeAnalogData *m_pCh_A, *m_pCh_B;//�˴���������ԭʼ�������ͨ���������ǲ�ֵ���!!!!!!
	
	CComplexMemBuffer_Float *m_pReplayBuf;//�ط�ͨ������

	//��ʱ��ͼ����
	double m_dCoefValue;
	double m_dZeroValue;
	
public:
	double CalcChannelMaxValue();
	BOOL IsChannelSelected();

	//��ʼ��ͨ���طŻ���
	void InitChReplayBuf(long nMaxPoints);

	void InitCh_A(CComtradeAnalogData *pAnalogData);
	void InitCh_B(CComtradeAnalogData *pAnalogData);

	//���ͨ���طŻ���
	void ResetChReplayBuf();

	//�������ģ��
	BOOL IsModuleType_U();//	{	return stt_adj_HdChDef_Is_Voltage(m_pHdChRef);}
	BOOL IsModuleType_I();//	{	return stt_adj_HdChDef_Is_Current(m_pHdChRef);}
	virtual BOOL IsModuleType_B(){		return FALSE;	}//wuxinyi 2024.1.29 ������
	virtual BOOL IsModuleType_W(){		return FALSE;	}//wuxinyi 2024.7.2  ���ź�


	long GetMaxPoints();//��ȡ��ǰͨ���ܵ���
// 	long GetValue_DataA();//zhouhj 2023.9.11 ɾ���˴���������,���ȡ��
// 	long GetValue_DataB();

	double GetValue_DataK();
	CString GetUnit();
	CString GetModuleChPhase();//zhouhj 20211104 ��ȡ��ͨ���ڸ�ģ���е����
	int GetIndexByID(CString ChStrID);//ͨ��ID��ȡͨ�����

	CString GetEleTypeString();//��ȡ��������
	int GetEleTypeIndex();
	void SetEleType(int nEleType);
	float GetChDCMaxValue();//��ȡֱ�����ֵ
};

class CSttModuleBinaryChComtradeBind : public CExBaseObject
{
public:
	CSttModuleBinaryChComtradeBind();
	virtual ~CSttModuleBinaryChComtradeBind();

public:
	CComtradeBinaryData *m_pBinaryCh;
	CString m_strComtradeBinaryCh;	//������ͨ��
	long m_nBinaryCh_Index;			//������ѡ��ͨ��
	long m_nChState;				//0-�Ͽ� 1-�պ� 

public:
	virtual BOOL IsModuleType_B(){		return TRUE;	}//������
	void InitBinaryCh(CComtradeBinaryData *pBinaryData);//��ʼ��������ͨ��

};


class CSttModuleComtradeBind : public CExBaseList
{
public:
	CSttModuleComtradeBind();
	virtual ~CSttModuleComtradeBind();
	//zhouhj 2023.8.14 ���սṹ����ģ��˳�򴴽���ID,��ID��ʽFormat(_T("Module%ld"),nModuleIndex);nModuleIndex��0��ʼ���
	//m_strID����Format(_T("%s%d"), strModuleType.GetString(), nModuleIndex);strModuleTypeΪӲ����Ϣ���ID,nModuleIndex��1��ʼ���
	CString m_strModuleID;
	long m_nModulePos;

	BOOL IsModuleSelected();
	double CalcChMaxValueByIndex(long nChIndex);
	double GetModuleMaxValue_U();
	double GetModuleMaxValue_I();
	void ScalingModuleMaxValue(float fK);
	void InitModuleReplayBuf(long nMaxPoints);
	void ResetModuleReplayBuf();

	long GetCount_U();
	long GetCount_I();
	long GetCount_B();

public:
	//������
	CComplexMemBuffer_Float *m_pReplayBufBinary1;//�ط�ͨ������ ��λ
	CComplexMemBuffer_Float *m_pReplayBufBinary2;//�ط�ͨ������ ��λ
	void InitReplayBufBinary(long nLength);//��ʼ�������ط�ͨ������
	void ResetReplayBufBinaryBuf(/*long nLength*/);//���ÿ������طû��泤��

	//���ź�
	float m_fPTRatio[2];	//PT��Ȳ���
	float m_fCTRatio[2];	//CT��Ȳ���
	BOOL IsWeekChTypeChg();
	void SetWeekChTypeChg(long nWeekChTypeChg);

public:
	BOOL IsDigitalTypeModule();
	BOOL IsBinaryTypeModule();//�Ƿ�Ϊ������ģ��
	BOOL IsAnalogTypeModule();
	BOOL IsWeekTypeModule();

private:
	long  m_nWeekChTypeChg;//ͨ���������Ϳɱ䣻1:�ɱ�,0:���ɱ�

};


class CSttModulesComtradeBind : public CExBaseList
{
public:
	CSttModulesComtradeBind();
	virtual ~CSttModulesComtradeBind();
	
public:
	CSttAdjDevice *m_pSttAdjDevice;	
	void InitBySttAdjDevice(CSttAdjDevice *pAdjDevice);
	void InitBinaryModule();

	long m_nChMaxPoints;
	CSttModuleComtradeBind *m_pBinaryModuleComtradeBind;//���忪����ģ��
	int m_nUseBinaryModule;//���忪��ģ���Ƿ�ʹ��--�·�ʹ��
	int m_nUseBinaryModuleWidget;//���忪��ģ������Ƿ�ʹ��
	BOOL IsBinaryModuleSelected();//���忪���Ƿ�ʹ��

	void InitModuleReplayBuf(long nChMaxPoints);
	long GetDataLength();
	long GetModuleCount();//20231101 wxy ��ȡģ������
	CSttModuleComtradeBind* FindByModuleID(const CString &strModuleID);
	CSttModuleComtradeBind * GetBinaryModule();//������忪����ָ��ӿ�

	int GetAnalogModuleCount();
	int GetDigitalModuleCount();
	int GetWeekModuleCount();

	void InitAllMoudleCount();


private:
	int m_nDigitalModuleCount;
	int m_nAnalogModuleCount;
	int m_nWeekModuleCount;

};
