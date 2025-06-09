#ifndef SttMUTestRecordCbWidget_H
#define SttMUTestRecordCbWidget_H

#include <QDialog>
#include <QFont>
#include "../SttIecCbGrid.h"
#include "../../../../../Module/OSInterface/XWndInterface.h"
#include "../../../../../Module/DataMngr/DataTypes.h"
#include "../SttIecRcdFuncInterface.h"
#include "../../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "SttIecRecordCbInterface.h"
#include "../SttIecSmvWaveWidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QLabel>
#include <QTabWidget>
#include "FirstCircleWave/SttMUTestFirstCwWidget.h"

class QSttMUTestRecordCbWidget : public QDialog, public CSttIecRecordCbInterface
{
    Q_OBJECT

public:
    explicit QSttMUTestRecordCbWidget(QFont font,long nPkgDetectType,QWidget *parent = 0);
    virtual ~QSttMUTestRecordCbWidget();

//CSttWndAssistInterface
public:
	void InitUI();
	void InitConnects();
	void ShowDelayTimeUI(bool bShow,bool bIsADMUTest = false);//�Ƿ���ʾ��ʱ��ؽ���
	//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
	//�������������ش˺�������Ϊ���ֱ�ӷ��ش���ָ�룬Ȼ��ǿ��ת��ΪCSttWndAssistInterface�������
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

	//�������ܲ���������ͼ
	virtual void UpdateFirstCirclePlot(long nChSetModifyType);

public:
	virtual void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void SetCapDevice(CCapDeviceBase *pCapDevice);
	virtual void SetSelectedCbs(CExBaseList *pSelectedCbs);
	virtual void Ats_IecRecord(BOOL bIsFromIecfgFile);
    void Ats_IecRecord_Stop();

	virtual void InitIecRecordCb(const CString &strIecFunc);
	void IecRcdFuncUpdate_MUDelayTimes(CCapDeviceBase *pCapDevice);//���ºϲ���Ԫ��ʱ
	

	virtual void BtnBack();//���ذ�ť����
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect);
	virtual bool IsTabUI_Mode(){return true;}//���ص�ǰ���ƿ������ʾ��ʽ�Ƿ�Ϊtab��ʾ��ʽ
	virtual void Update_IecRcdTimer();
	
	void SetIecRecordCbFont(); //2022-10-17
	void HideDelayErrUI();//������ʱ���Ƚ�����ʾ


	QTabWidget *m_pSttRecordCBTabWidget;
	QVBoxLayout *m_pMainVLayout;
	QHBoxLayout *m_pBottomBtnHLayout;
	QSpacerItem *m_pBottomHSpacer1;
	QPushButton *m_pPrevPageBtn;
	QPushButton *m_pNextPageBtn;
	QSpacerItem *m_pBottomHSpacer2;
	QPushButton *m_pSysSetBtn;
	QSttIecSmvWaveWidget *m_pSttIecSmvWaveWidget;
	QSttMUTestFirstCwWidget *m_pSttFirstCwWidget;

	QLabel *m_pDelayChValue_Label;
	QLineEdit *m_pDelayChValue_Edit;
	QLabel *m_pRealDelayValue_Label;
	QLineEdit *m_pRealDelayValue_Edit;
	QLabel *m_pDelayValueError_Label;
	QLineEdit *m_pDelayValueError_Edit;

	QLabel *m_pSampFreqLabel;
	QLabel *m_pOutputRateLabel;
	QLineEdit *m_pSampFreqEdit; //����Ƶ��
	QLineEdit *m_pOutputRateEdit; //�������

public:
	CString m_strIecRcdFuncID;
	CCapDeviceBase *m_pCurrCapDevice;
	
	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;
	
	void RecordCapDevice(CCapDeviceBase *pCapDevice);
	void RecordCapDevice();
	void ExecIecFunc(const CString &strIecfFunc);
	virtual void ExecIecFunc();//ִ�е�ǰ���Թ���
	void ExecIecFunc_SetCapAnalysisConfig();//���ñ��ķ�������
	virtual void UpdateSVDatasetsPowerVector();
	void UpdateSampFreOutputRateData(CCapDeviceBase *pCapDevice);//ˢ�²���Ƶ��/�������

private:
	CDataTypes m_oIecRcdDataTypes;
	CDataType *m_pDataType_SttIecRcdMUFuncs;

	QTimer m_oTimerIecRcdUpdate;

	//2022-4-25  lijunqing ������֮��Ļ��⴦��
	//���磺��ҳ��ҳ�ȵ��»�ͼԪ�ر仯
	//���磺�л�ѡ���ܵ����붨ʱ���ĳ�ͻ��
	CAutoCriticSection m_oFuncCriticSection;
	bool m_bInSetCapDevice;

	void OnCurrFuncChanged(long nIndex);

signals:
//	void sig_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);
	void sig_UpdateSVDatasetsPowerVector();//�������������ʵ�

private slots:
	void slot_currentChangedTabWidget(int nCurrIndex);
	void slot_SysSetBtnClicked();
	void slot_PrevPageBtnClicked();
	void slot_NextPageBtnClicked();

	void slot_Timer_IecRcdUpdate();
	void slot_UpdateSVDatasetsPowerVector();//�������������ʵ�
};

#endif // SttMUTestRecordCbWidget_H
