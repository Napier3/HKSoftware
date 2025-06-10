#ifndef IMPEDANCEMANUWIDGET_H
#define IMPEDANCEMANUWIDGET_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/Impedance/tmt_manuImped_test.h"
#include "../Module/SttTestBase/SttComplexp.h"

#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QGroupBox>
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttTabWidget.h"
#include "../Controls/SttCheckBox.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SttGroupBox.h"

class QImpedanceManuWidget : public QWidget
{
	Q_OBJECT

public:
    QImpedanceManuWidget(QWidget *pParent);
    virtual ~QImpedanceManuWidget();
	void InitUI();
	void InitConnect();
	void initBaseData();
	void initData();
	void initstrUnit();
	void initPara();
	void FirstModeListChanged();
	void SecondModeListChanged();
	void OnRXValue();

	QIcon m_imgLock;
	QIcon m_imgUnlock;

	QGridLayout *m_pMainGridLayout;
	QPushButton *m_pBinarySet_PushButton;
	QPushButton *m_pEstimate_PushButton;
	QSttTabWidget *m_pImpedanceManuTab;
	

	QWidget *m_pParaSetting_Widget;//��������

public:
	QPushButton *m_pbn_Clear;
	QPushButton *m_pbn_Up;
	QPushButton *m_pbn_Down;
	QPushButton *m_pbn_Lock;
	QLabel *m_pFaultTypeLabel;//��������
	QLabel *m_pCalModeLabel;//�迹����
	QLabel *m_pImpedlabel;//�迹����ѡ��
	QLabel *m_pZLabel;//|Z|
	QLabel *m_pRXLabel;//R,X
	QLabel *m_pDLLabel;//��·
	QLabel *m_pVarSelecLabel;//����ѡ��
	QLabel *m_PrepareTimeLabel;//��̬ʱ��
	QLabel *m_PreFaultTimeLabel;//����ǰʱ��
	QLabel *m_pStepLabel;//�仯����
	QLabel *m_pStartLabel;//�仯ʼֵ
	QLabel *m_pTimeLabel;//�仯ʱ��
	QLabel *m_pEndLabel;//�仯��ֵ
	QLabel *m_pTrigDelayLabel;//��������ʱ
	QLabel *m_pChangeTypeLabel;//�仯��ʽ
	QLabel *m_pActTimeLabel;//����ʱ��
	QLabel *m_pFrequencyLabel;//Ƶ��
	QLabel *m_pZsLabel;
	QLabel *m_pCacuTypeLabel;//ģʽ
	QLabel *m_pAmpLabel;//��ֵ
	QLabel *m_pAngleLabel;//��λ
	QScrollComboBox *m_pCmb_CalMode;
	QScrollComboBox *m_pCmb_FaultType;
	QScrollComboBox *m_pCmb_FirstMode;//����ѡ��1
	QScrollComboBox *m_pCmb_SecondMode;//����ѡ��2
	QScrollComboBox *m_pCmb_CacuType;
	QScrollComboBox *m_pCmb_ChangeType;
	QRadioButton *m_pRad_Z;//Z
	QRadioButton *m_pRad_RX;//R,X
	QSttCheckBox *m_pAuto_CheckBox;//�Զ��ݱ�
	QSttCheckBox *m_pMutation_CheckBox;//ͻ��������
	QSttLineEdit *m_pPhiEdit;
	QSttLineEdit *m_pZEdit;
	QSttLineEdit *m_pXEdit;
	QSttLineEdit *m_pREdit;
	QSttLineEdit *m_pShortIOrZsAmpEdit;//��·����/��·��ѹ/Zs��ֵ
	QSttLineEdit *m_pShortIOrZsAngleEdit;//Zs�Ƕ�
	QSttLineEdit *m_PrepareTimeEdit;//��̬ʱ��
	QSttLineEdit *m_PreFaultTimeEdit;//����ǰʱ��
	QSttLineEdit *m_pStepEdit;//�仯����
	QSttLineEdit *m_pStartEdit;//�仯ʼֵ
	QSttLineEdit *m_pTimeEdit;//�仯ʱ��
	QSttLineEdit *m_pEndEdit;//�仯��ֵ
	QSttLineEdit *m_pFrequencyEdit;//Ƶ��
	QSttLineEdit *m_pTrigDelayEdit;//��������ʱ
	QSttLineEdit *m_pActTimeEdit;//����ʱ��
	QSttLineEdit *m_pAmpEdit;
	QSttLineEdit *m_pAngleEdit;

	QGroupBox *m_pBoutGroupBox;
	QGridLayout *m_pBout_GridLayout;
	QSttCheckBox *m_pBout_CheckBox[4];

private:
	QStringList m_errorTypeList;//���������б�
	QStringList m_CalTypeList;
	QStringList m_CalModList;
	QStringList m_FirstModeList;//����ѡ�� 
	QStringList m_SecondModeList; //����ѡ�� ��ֵ����λ
	QStringList m_ChangeTypeList;//�仯��ʽ

	bool m_bZPhi;
	bool m_bRX;
	int m_bLockChanged;
	float m_fActTime;
	float fValue;
	bool bflag;

	Complex m_fVa;
	Complex m_fVb;
	Complex m_fVc;
	Complex m_fIa;
	Complex m_fIb;
	Complex m_fIc;

	QString strUnit[10];
	bool m_bControlLock; //��


public:
	CSttTestResourceBase* m_pTestResource;
	tmt_ManualImpedParas *m_pManualImpedParas;
	tmt_ManualImpedTest m_oManualImpedTest;
	CEventResult* m_pEvent;

public:
	void SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualImpedParas* pManualImpedParas,CEventResult* pEvent);
	void UpdateData();

	void StartInit();
	void StopInit();
	private slots:
		void slot_CmbErrorTypeIndexChanged(int);
		void slot_CmbCalModeIndexChanged(int);
		void slot_CmbCacuTypeIndexChanged(int);
		void slot_CmbFirstModeIndexChanged(int);  //����ѡ��1
		void slot_CmbSecondModeIndexChanged(int);//����ѡ��2
		void slot_CmbChangeTypeIndexChanged(int);
		void slot_RadioZPhiAndRX_StateChanged();
		void slot_lne_TextChanged(QSttLineEdit* pLineEdit);
		float slot_lne_Changed(QSttLineEdit* pLineEdit);
		void slot_lneZ_TextKeyBoard();
		void slot_lnePhi_TextKeyBoard();
		void slot_lneR_TextKeyBoard();
		void slot_lneX_TextKeyBoard();	
		void slot_lneDLZSAmp_TextKeyBoard(); //��·���� \��·��ѹ\ZS-AMP
		void slot_lneDLZSAngle_TextKeyBoard();//ZS-Angle
		//void slot_lneAmplitudeOrKr_TextChanged();//��ϵ����
		void slot_lneAmplitudeOrKr_TextKeyBoard();
		//void slot_lnePhaseOrKx_TextChanged();//��ϵ����
		void slot_lnePhaseOrKx_TextKeyBoard();
		//void slot_lnePrepareTime_TextChanged();//��̬ʱ��
		void slot_lnePrepareTime_TextKeyBoard();
		//void slot_PreFaultTime_TextChanged();//����ǰʱ��
		void slot_PreFaultTime_TextKeyBoard();
		void slot_lneStep_TextKeyBoard();//�仯������ʱ��
		void slot_lneTime_TextKeyBoard();
		void slot_lneStart_TextKeyBoard();//�仯ʼֵ����ֵ
		void slot_lneEnd_TextKeyBoard();
		void slot_lneTrigDelay_TextKeyBoard();//��������ʱ
		void slot_lneActTime_TextKeyBoard();//����ʱ��
		void slot_Chb_AutoStateChanged(int);//�Զ��ݱ�
		void slot_Chb_MutationStateChanged(int);//ͻ��������
		void slot_pbn_ClearClicked();
		void slot_pbn_UpClicked();
		void slot_pbn_DownClicked();
		void slot_pbn_LockClicked();

		void slot_ck_Out1StateChanged();
		void slot_ck_Out2StateChanged();
		void slot_ck_Out3StateChanged();
		void slot_ck_Out4StateChanged();
signals:

protected slots:
	void slot_currentChangedTabWidget(int nCurrIndex);

};

#endif // IMPEDANCEMANUWIDGET_H
