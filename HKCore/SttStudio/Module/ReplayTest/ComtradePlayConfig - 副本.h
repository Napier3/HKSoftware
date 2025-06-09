#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
// #include "SttComtradeGroup.h"  //2021-11-2  lijunqing
#include "SttModuleChComtradeBind.h"
#include "../../../Module/Record/Comtrade/ComtradeMngr.h"
#include "../../../Module/Record/Comtrade/ComtradeRateData.h"
#ifdef _PSX_IDE_QT_
#include "../SttTest/Common/tmt_replay_test.h"
#endif

#define COMTRADE_CONFIG_KEY_Module	_T("MODULE")
#define COMTRADE_CONFIG_KEY_U		_T("U")
#define COMTRADE_CONFIG_KEY_I		_T("I")
#define COMTRADE_CONFIG_KEY_A		_T("A")
#define COMTRADE_CONFIG_KEY_B		_T("B")
#define COMTRADE_CONFIG_KEY_K		_T("K")
#define COMTRADE_CONFIG_KEY_MomentaryVal	_T("MomentaryVal")

#define CMTRD_FLUSH_TYPE_NoFlush			0
#define CMTRD_FLUSH_TYPE_FlushOneCh			1
#define CMTRD_FLUSH_TYPE_FlushAll			2
#define CMTRD_FLUSH_TYPE_FlushUModule		3
#define CMTRD_FLUSH_TYPE_FlushIModule		4

#define BIG_COMTRADE_REPLAY_CH_MAX_NUM                                                64  //20220519 ���д����ݻط�ͬʱ���ѡ��Ӳ��ͨ������ �ݶ�12

//������ģ��ͨ��ӳ��ڼ���
#define DIGITAL_CH_MAP_FRIST_GROUP		0		
#define DIGITAL_CH_MAP_SECOND_GROUP		1

class CComtradePlayConfig : public CDataGroup
{
public:
	CComtradePlayConfig(void);
	virtual ~CComtradePlayConfig(void);

	long m_nStartCycleNum;	//��ʼѭ���ܲ������޴�������Ч
	long m_nTrigAfterMode;	//����������ģʽ��1ѭ����������л���0�������л�

	double m_fSampleFreq;
	long m_nTriggerType;	//��������
#ifdef _PSX_IDE_QT_
	tmt_time	    m_tGps;
#endif
// 	long m_nTrigTimeS;		//����ʱ��
// 	long m_nTrigTimeNS;
	float m_fPTRatio[2];	//PT��Ȳ���
	float m_fCTRatio[2];	//CT��Ȳ���

#ifdef _PSX_IDE_QT_
	tmt_BinaryConfig m_oBinaryConfig;	//����������
	tmt_replay_WaveEditPara m_oWaveEditParas;//2023-12-21 wuxinyi ���α༭���ò���
#endif
	//CSttComtradeGroup *m_pChMapConfig;	//ͨ��ӳ�����ã������ط����ݻ���
	CSttModulesComtradeBind m_oSttModulesComtradeBind;	//ͨ��ӳ�����ã������ط����ݻ���
	long m_nReplayBufFlush;//�طŻ���ˢ�±��,0:��ˢ�£�1����ͨ��ˢ�£�2������ͨ��ˢ��

// 	BOOL m_bUseBinaryModule;//���忪��ģ���Ƿ�ʹ��
	CSttModuleComtradeBind * GetBinaryModule();//��ȡ���忪����ģ��ָ��ӿ�

public:
	long GetTotalChannelNum();
	long GetTotalUChannelNum();
	long GetTotalIChannelNum();
	//�������ò����������С���㻺�����ܴ��������,����ط������ݻ���
	void InitReplayBuf(long nABBufLen);
	//��ջطŻ�������
	void ResetReplayBuf();

	//���»طŻ������ݺ���ã����ڽ�����ʾ
//	void GetWeekChMaxValue(double &fUMax,double &fIMax,int nRealModuleIndex);//���ź���ÿ��ģ��Ӧ�ֿ���ʾ���ֵ��ѹ����
	void GetDigitalChMaxValue(double &fUMax,double &fIMax);
#ifdef _PSX_IDE_QT_
	void GetReplayChMaxValue(double &fUMax,double &fIMax,int nModuleType = REPLAY_MODULE_TYPE_ANALOG);
#endif
	void CalcReplayChMaxValue();
	void CalcReplayChMaxValue(int nModuleIndex,int nChIndex);
	bool CalDigitalChMaxValue(CSttModuleChComtradeBind *pCh, int nChannelGroupIndex);//ʵ������ģ��ͨ��������ֵ
	bool VaildDigitalChMaxValue(CSttModuleComtradeBind *pModule);
	bool VaildDigitalChMaxValue();

	bool VaildWeekChMaxValue(); //���ź����ֵ��֤

	int GetFT3MaxCodeValue(int nChannelGroupIndex, CSttModuleChComtradeBind *pCh);//��ȡ�����ֵ
	bool HasFT3ChMap();//�����������ΪFT3����ֱ/��ͨ��,�Ƿ���ӳ�䵽������ǰ��������

	//��ȱ仯�󣬸������ֵ
	void CalcReplayChUMaxValue();
	void CalcReplayChIMaxValue();

	//��ȡ��ǰ�طŻ����е���
	long GetReplayBufPoints();

	//��ȡָ��ʱ����ͨ��˲ʱֵ
	void GetReplayBufFixedMomentaryVal(double fStartTime,double fFixTime,double fSampleFreq);

	//�Ƿ���ѭ������
	BOOL HasLoopData();

#ifdef _PSX_IDE_QT_
	//�����ö�������tmt�ṹ��
	void GenerateReplayTestParas(tmt_ReplayParas &oReplayParas,long nSampleFreq);
	void GenerateReplayConfigFromTMT(tmt_ReplayParas *pReplayParas,BOOL bUpdateChMapConfig);
#endif

	long GetTotalChs_SelectedModule();
	void GetTotalChs_SelectedModule(float ***pppdChValue);//��ȡ���ڵ��£�����ģ�������ͨ�� ��ͨ��δѡ��ʱ��ֵΪ��
	//void GetTotalChs_SelectedModule(CExBaseList &oModuleChsRef);//2024-02-22 wuxinyi ��������������ģ�飬�ú�����ʱע��

	//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTCMTRDPLAYCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmtrdCfgDefineXmlRWKeys::CSttCmtrdReplayCfgKey();     }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	BOOL Open(const CString &strFile, double &fSampleFreq);
	BOOL Save(const CString &strFile, double fSampleFreq);
	void InitDefault(BOOL bInitNotModuleParas = TRUE);//���α�ʶ�Ƿ��ʼ����ģ�����(���롢������ʽ��)
};

