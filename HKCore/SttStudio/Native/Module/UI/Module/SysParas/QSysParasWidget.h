#ifndef QSYSPARASWIDGET_H
#define QSYSPARASWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QRadioButton>
#include "../CommonCtrl_QT/QFloatLineEdit.h"
#include <QTableWidgetItem>

#include "../CommonMethod/commonMethod.h"

#include "../../../../Module/SttTest/Common/tmt_system_config.h"

class QSysParasWidget : public QWidget
{
	Q_OBJECT

public:
	QSysParasWidget(QWidget *parent = 0);
	~QSysParasWidget();

	void initUI(STT_SystemParas *pSysParas);
	void DisEnableDigitalUI();
	void DisEnableWeekUI();
	void ReleaseUI();
	void InitDatas();//��ϵͳ�����г�ʼ������ѡ��
	void SaveDatas();//������������浽ϵͳ������

	void InitConnect();

protected:
	QGroupBox *m_pOutputSel_GroupBox;//�������ѡ��Group
	QHBoxLayout *m_pOutputSel_HBoxLayout;//�������ѡ�񲼾�

	QCheckBox *m_pAnalogSel_CheckBox;//ģ����ѡ��
	QCheckBox *m_pDigitalSel_CheckBox;//������ѡ��
	QCheckBox *m_pWeakSel_CheckBox;//���ź�ѡ��
	QLabel *m_pDigitalType_Label;//���ֱ�������
	QComboBox *m_pDigitalType_Combobox;//���ֱ�������ѡ��

	QGroupBox *m_pMeasSel_GroupBox;//�ɼ�����ѡ��Group
	QHBoxLayout *m_pMeasSel_HBoxLayout;//�ɼ�����ѡ�񲼾�

	QCheckBox *m_pAnalogMeasSel_CheckBox;//�ɼ�ģ����ѡ��
	QCheckBox *m_pDigitalMeasSel_CheckBox;//�ɼ�������ѡ��
// 	QCheckBox *m_pWeakMeasSel_CheckBox;//�ɼ����ź�ѡ��
	QLabel *m_pDigitalMeasType_Label;//�ɼ����ֱ�������
	QComboBox *m_pDigitalMeasType_Combobox;//�ɼ����ֱ�������ѡ��


	QVBoxLayout *m_pTotal_VBoxLayout;

	QGroupBox *m_pStdValues_GroupBox;//�ֵGroup
	QGridLayout *m_pStdValues_GridLayout;

	QLabel *m_pStdVol_Label;
	QFloatLineEdit *m_pStdVol_LineEdit;

	QLabel *m_pStdCur_Label;
	QFloatLineEdit *m_pStdCur_LineEdit;

	QLabel *m_pStdFre_Label;
	QFloatLineEdit *m_pStdFre_LineEdit;

	QLabel *m_pAntiShakeTime_Label;//����ʱ��
	QFloatLineEdit *m_pAntiShakeTime_LineEdit;

	QLabel *m_pOverLoadDelay_Label;
	QFloatLineEdit *m_pOverLoadDelay_LineEdit;

	QLabel *m_pZeroStdVol_Label; //������ѹ
	QFloatLineEdit *m_pZeroStdVol_LineEdit;

	QLabel *m_pZeroStdCur_Label; //��������
	QFloatLineEdit *m_pZeroStdCur_LineEdit;

	QGroupBox *m_pSynSet_GroupBox;//ͬ������Group
	QGridLayout *m_pSynSet_GridLayout;
	QLabel *m_pSecondSynSet_Label;
	QComboBox *m_pSecondSynSet_ComboBox;
	QLabel *m_pBCodeLogic_Label;
	QRadioButton *m_pBCodePositiveLogic_RadioBtn;
	QRadioButton *m_pBCodeNegtiveLogic_RadioBtn;
	QLabel *m_p1588Syn_Label;
	QRadioButton *m_p1588PeerDelay_RadioBtn;
	QRadioButton *m_p1588ReqResp_RadioBtn;

	QGroupBox *m_pSetErrorValues_GroupBox;//��Χ����
	QGridLayout *m_pSetErrorValues_GridLayout;

	QLabel *m_pCurAbsError_Label;
	QFloatLineEdit *m_pCurAbsError_LineEdit;
	QLabel *m_pCurRelError_Label;
	QFloatLineEdit *m_pCurRelError_LineEdit;

	QLabel *m_pVolAbsError_Label;
	QFloatLineEdit *m_pVolAbsError_LineEdit;
	QLabel *m_pVolRelError_Label;
	QFloatLineEdit *m_pVolRelError_LineEdit;

	QLabel *m_pImpAbsError_Label;
	QFloatLineEdit *m_pImpAbsError_LineEdit;
	QLabel *m_pImpRelError_Label;
	QFloatLineEdit *m_pImpRelError_LineEdit;

	QLabel *m_pTimeAbsError_Label;
	QFloatLineEdit *m_pTimeAbsError_LineEdit;
	QLabel *m_pTimeRelError_Label;
	QFloatLineEdit *m_pTimeRelError_LineEdit;

	QLabel *m_pAngError_Label;
	QFloatLineEdit *m_pAngError_LineEdit;
	QLabel *m_pFreqError_Label;
	QFloatLineEdit *m_pFreqError_LineEdit;

	QLabel *m_pDvDtError_Label;
	QFloatLineEdit *m_pDvDtError_LineEdit;
	QLabel *m_pDfDtError_Label;
	QFloatLineEdit *m_pDfDtError_LineEdit;

	QLabel *m_pDiffHarmCoefRelError_Label;
	QFloatLineEdit *m_pDiffHarmCoefRelError_LineEdit;
	QLabel *m_pDiffHarmCoefAbsError_Label;
	QFloatLineEdit *m_pDiffHarmCoefAbsError_LineEdit;

	QLabel *m_pDiffRateCoefAbsError_Label;
	QFloatLineEdit *m_pDiffRateCoefAbsError_LineEdit;
	QLabel *m_pDiffRateCoefRelError_Label;
	QFloatLineEdit *m_pDiffRateCoefRelError_LineEdit;


	STT_SystemParas *m_pSysParas;

public slots:
	void slot_changeSecondSyn(int nIndex);
	void slot_changeDigitalType(int nIndex);
	void slot_changeDigitalMeasType(int nIndex);
	void slot_radio_BCodePositiveLogicChanged(bool);
	void slot_radio_BCodeNegtiveLogicChanged(bool);
	void slot_radio_1588PeerDelayChanged(bool);
	void slot_radio_1588ReqRespChanged(bool);

	void slot_DigitalCheck_stateChanged(int nState);
	void slot_WeakSelCheck_stateChanged(int nState);

	//2023/7/24 wjs
	//void slot_OnLineEditClicked(QString strValue, QFloatLineEdit currentLineEdit);
	void slot_OnLineEditClicked();
};

#endif // QSYSPARASWIDGET_H
