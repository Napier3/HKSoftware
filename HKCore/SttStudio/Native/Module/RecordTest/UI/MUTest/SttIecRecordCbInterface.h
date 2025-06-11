#pragma once

//2022-12-02  lijunqing  
#include "../../../Assist/SttAssistGlobalApi.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"

#define STT_IEC_RECORD_TIMER_DEFAULT_VALUE              0.5f

#define STT_MUTEST_CHSSET_MODIFY_TYPE_NO                              0  //û�в����ı�
#define STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc                1  //ֻ�޸��˱��,׼ȷ��,����,ѡ��״̬
#define STT_MUTEST_CHSSET_MODIFY_TYPE_ChTypeMap                       2  //�޸���ͨ�����ͺ�ͨ��ӳ��

class CSttIecRecordCbInterface :public CSttWndAssistInterface  //2022-12-02 lijunqing ����������صĽӿ�
{
public:
	CSttIecRecordCbInterface(void);
	virtual ~CSttIecRecordCbInterface(void);

	void SetMUTestMode(bool bMUTestMode){m_bMUTestMode = bMUTestMode;}
	bool IsMUTestMode(){return m_bMUTestMode;}

	virtual void BtnBack(){}//���ذ�ť����
	virtual void InitIecRecordCb(const CString &strIecFunc){}//��������¼���洢ģʽ���ǷǴ洢ģʽ
	virtual void SetSelectedCbs(CExBaseList *pSelectedCbs){}
	virtual void Ats_IecRecord(BOOL bIsFromIecfgFile){}
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect){}
	virtual void SetEnable_BtnBack(bool bEnable){}
	virtual void UpdateSVDatasetsPowerVector(){}
//	virtual void UpdateCapDevice(CCapDeviceBase *pCapDevice){}
	virtual void ExecIecFunc(){}//ִ�е�ǰ���Թ���
	virtual bool IsTabUI_Mode(){return false;}//���ص�ǰ���ƿ������ʾ��ʽ�Ƿ�Ϊtab��ʾ��ʽ
	virtual void Update_IecRcdTimer();

	//����д�ļ��Ĵ�С��ʱ��
	virtual void UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize);

	//�������ܲ���������ͼ
	virtual void UpdateFirstCirclePlot(long nChSetModifyType);

	CDvmData *m_pSVDelayData;
	float m_fIecRcdTimer;
	CExBaseList *m_pSelectedCbs;
	BOOL m_bStopTimerUpdate;//ֹͣ��ʱ���ĸ���,��IEC�����޸ĺ�,��Ҫ����ֹͣ��ʱ���ĸ���,��ֹ���õ�IEC������������ѱ�����
protected:
	bool m_bMUTestMode;//20220822 �ϲ���Ԫ����ģʽ
};

extern CSttIecRecordCbInterface *g_pSttIecRecordCbWidget;