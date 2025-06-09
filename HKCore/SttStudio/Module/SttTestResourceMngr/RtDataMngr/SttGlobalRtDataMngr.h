#pragma once
#include "SttMacroChannelsAsync.h"
#include "../TestResource/SttTestResourceBase.h"
#include "../../SttCmd/SttChMaps.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttRtDataChangeEvent//ʸ��ͼ��ʱ������ͼ�ȵ������
{
public:
	CSttRtDataChangeEvent(){}
	virtual ~CSttRtDataChangeEvent(){}
	virtual void OnRtDataChanged() = 0;//�����麯��,ʵ���յ�ʵʱ���ݺ�Ĵ���
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttGlobalRtDataMngr
{
public:
	CSttGlobalRtDataMngr();
	virtual ~CSttGlobalRtDataMngr();
public:
	long m_nMode;// 1:�첽ģʽ;2: ͬ��ģʽ
	CSttMacroChannelsAsync*m_pMacroChannelsMngr;//�첽ģʽʵ����Դ����
	CSttMacroChannels *m_pMacroChannels;//ͬ��ģʽʵ����Դ����
	CSttBinChlMngr m_oBinChlMngr;//��������ʷ���ݶ���

	CSttRtDataChangeEvent *m_pEventToVector;	//ʸ��ͼ
	CSttRtDataChangeEvent *m_pEventToProgress;	//��ֵʱ��ͼ

	//�����������µ��¼����ܶ������磺�����������ͼ��
	//2021-6-1  yangyijun
	CSttRtDataChangeEvent *m_pEventToPower;		//����ͼ
	CSttRtDataChangeEvent *m_pEventToLineVolt;	//�ߵ�ѹ
	CSttRtDataChangeEvent *m_pEventToSequence;  //�����

	int m_nRtDataFlag;	//��ʶ��ǰ�Ƿ����ڴ������ʵʱ����
	int m_bAutoMode;	//�Զ�ģʽ 2021-6-25 yyj
	//��������ٿ����Ƿ��������־
public:
	void InitSoftResource(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);//��ʼ�������Դ
	void InitGroup();//��ʼ������ͨ������
	void AddMacroChValues(CSttParas *pParas);//engine������øú���
	//����������£�ֻ����ʵʱ���ݣ���������ʷ����
	//���溯������1Ϊ����ָ��,����2Ϊͨ�����ͣ�����3Ϊ�������
	void SetMacroChValues(tmt_RtDataCh *pRtVector, long nChannelType, long nCount);
	//��������,Ϊ���õ��������������
	void SetMacroChValue(tmt_RtDataCh *pRtVector, long nChannelType, long nChIndex);
	void SetMacroChValue(double dMag, double dAng, long nChannelType, long nChIndex);
	void SetMacroChValue(tmt_RtDataCh *pRtVector, const CString &strChID);
	void SetMacroChValue(double dMag, double dAng, const CString &strChID);
	void SetMacroChMagValue(double dMag, const CString &strChID);
	void SetMacroChAngValue(double dAng, const CString &strChID);
//	void RegisterRtDataChangeRcv(CSttRtDataChangeEvent * pEventRcv);//ע����Ҫ������ʾ��ʸ��ͼ��ʱ������ͼ��, ���˺������ڳ�ʼ���е��õġ�
	void FireRtDataChangeEvent();//�ڸ�����ȫ��Ψһ������ʵʱ����ֵ�󣬵��ô˺�������m_listRtDataChangeRcv�����ֱ����ʸ��ͼ�ȵ�OnRtDataChanged()����

	void ClearHisDatas();//���ȫ����ʷ����,�ڿ�ʼ����ʱ����Ҫ����ʷ�������

	void SetAutoMode(bool bAuto){	m_bAutoMode = bAuto;	}
	bool IsAutoMode(){	return m_bAutoMode; }
protected:
	void InitSoftResource_Sync(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);
	void InitSoftResource_Async(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);
};


/*
//����ඨ���ȫ�ֶ��󣬸���m_nMode ֵ�Ĳ�ͬ���������ʹ�á�
m_nMode = 1���첽ģʽ����Ҫ���������Դ����m_pMacroChannelsMngr;
m_nMode = 2��ͬ��ģʽ����MacroChannels;��ʾ����һ�����ݣ��Ͳ���Mngr�ˣ�ֱ����m_pMacroChannels��
�����ݴ�engine �����ˣ�����AddMacroChValues��ͬʱ���þ���ͼ�θ��½ӿ�ʵ�ָ��»�ͼFireRtDataChangeEvent();�����¼��������ݸı䣬 �ı��˻�������*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CSttGlobalRtDataMngr g_oSttGlobalRtDataMngr;//ȫ��Ψһ����,����ʵʱ��������

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
