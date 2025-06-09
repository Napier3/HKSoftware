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
	void InitDatas();//从系统参数中初始化界面选择
	void SaveDatas();//将界面参数保存到系统参数中

	void InitConnect();

protected:
	QGroupBox *m_pOutputSel_GroupBox;//输出类型选择Group
	QHBoxLayout *m_pOutputSel_HBoxLayout;//输出类型选择布局

	QCheckBox *m_pAnalogSel_CheckBox;//模拟量选择
	QCheckBox *m_pDigitalSel_CheckBox;//数字量选择
	QCheckBox *m_pWeakSel_CheckBox;//弱信号选择
	QLabel *m_pDigitalType_Label;//数字报文类型
	QComboBox *m_pDigitalType_Combobox;//数字报文类型选择

	QGroupBox *m_pMeasSel_GroupBox;//采集类型选择Group
	QHBoxLayout *m_pMeasSel_HBoxLayout;//采集类型选择布局

	QCheckBox *m_pAnalogMeasSel_CheckBox;//采集模拟量选择
	QCheckBox *m_pDigitalMeasSel_CheckBox;//采集数字量选择
// 	QCheckBox *m_pWeakMeasSel_CheckBox;//采集弱信号选择
	QLabel *m_pDigitalMeasType_Label;//采集数字报文类型
	QComboBox *m_pDigitalMeasType_Combobox;//采集数字报文类型选择


	QVBoxLayout *m_pTotal_VBoxLayout;

	QGroupBox *m_pStdValues_GroupBox;//额定值Group
	QGridLayout *m_pStdValues_GridLayout;

	QLabel *m_pStdVol_Label;
	QFloatLineEdit *m_pStdVol_LineEdit;

	QLabel *m_pStdCur_Label;
	QFloatLineEdit *m_pStdCur_LineEdit;

	QLabel *m_pStdFre_Label;
	QFloatLineEdit *m_pStdFre_LineEdit;

	QLabel *m_pAntiShakeTime_Label;//防抖时间
	QFloatLineEdit *m_pAntiShakeTime_LineEdit;

	QLabel *m_pOverLoadDelay_Label;
	QFloatLineEdit *m_pOverLoadDelay_LineEdit;

	QLabel *m_pZeroStdVol_Label; //额定零序电压
	QFloatLineEdit *m_pZeroStdVol_LineEdit;

	QLabel *m_pZeroStdCur_Label; //额定零序电流
	QFloatLineEdit *m_pZeroStdCur_LineEdit;

	QGroupBox *m_pSynSet_GroupBox;//同步设置Group
	QGridLayout *m_pSynSet_GridLayout;
	QLabel *m_pSecondSynSet_Label;
	QComboBox *m_pSecondSynSet_ComboBox;
	QLabel *m_pBCodeLogic_Label;
	QRadioButton *m_pBCodePositiveLogic_RadioBtn;
	QRadioButton *m_pBCodeNegtiveLogic_RadioBtn;
	QLabel *m_p1588Syn_Label;
	QRadioButton *m_p1588PeerDelay_RadioBtn;
	QRadioButton *m_p1588ReqResp_RadioBtn;

    //20240910 wanmj 系统参数误差部分去掉
#if 0
	QGroupBox *m_pSetErrorValues_GroupBox;//误差范围设置
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
#endif

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
