#ifndef QAUXDC_OUTPUT_DLG_H
#define QAUXDC_OUTPUT_DLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QSlider>

#include "../CommonCtrl_QT/QFloatLineEdit.h"
#include "../../../SttTest/Common/tmt_system_config.h"
#include "../../Module/ScrollCtrl/ScrollSlider.h"

class QAuxDCOutputDlg : public QDialog
{
	Q_OBJECT

public:
	QAuxDCOutputDlg(QWidget *parent = 0);
	~QAuxDCOutputDlg();

	void initUI();
	void ReleaseUI();
	int SetValueToScaleUI(float fAuxDC_Vol);
	void setDCOutPutFont();

protected:
	void InitDatas();

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGroupBox *m_pAuxDC_GroupBox;//辅助直流设置
	QHBoxLayout *m_pAuxDC_Vol_HBoxLayout;
	QLabel *m_pAuxDC_Vol_Label;
	QFloatLineEdit *m_pAuxDC_Vol_LineEdit;
	ScrollSlider *m_pDC_Value_Slider;
	int m_nOldSliderValue;

	QLabel *m_pScale300V_Label;
	QLabel *m_pScale250V_Label;
	QLabel *m_pScale220V_Label;
	QLabel *m_pScale110V_Label;
	//QLabel *m_pScale48V_Label;
	//QLabel *m_pScale24V_Label;
	//QLabel *m_pScale15V_Label;
	//QLabel *m_pScale10V_Label;
	//QLabel *m_pScale5V_Label;
	QLabel *m_pScaleOther_Label;
	QLabel *m_pScaleClosed_Label;

	QVBoxLayout *m_pScale_VBoxLayout;//刻度显示垂直布局
	QHBoxLayout *m_pBegin_HBoxLayout;//第一行的水平布局
	QHBoxLayout *m_pEnd_HBoxLayout;//第二行的水平布局
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	STT_SystemParas m_oSysParas;

public:
signals:
//	void sig_UpdateAuxDCOutput();//通知外部模块更新测试仪模块辅助直流输出

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_ScaleSetValue(int nValue);
	void SetUI_ToScaleValue(int nValue);
	
};

class QAuxDCOutputDlg_L336EXi : public QDialog
{
	Q_OBJECT

public:
	QAuxDCOutputDlg_L336EXi(QWidget *parent = 0);
	~QAuxDCOutputDlg_L336EXi();

	void initUI();
	void ReleaseUI();
	int SetValueToScaleUI(float fAuxDC_Vol);
	void setDCOutPutFont();

protected:
	void InitDatas();

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGroupBox *m_pAuxDC_GroupBox;//辅助直流设置
	QHBoxLayout *m_pAuxDC_Vol_HBoxLayout;
	QLabel *m_pAuxDC_Vol_Label;
	QFloatLineEdit *m_pAuxDC_Vol_LineEdit;
	ScrollSlider *m_pDC_Value_Slider;
	int m_nOldSliderValue;

	QLabel *m_pScale264V_Label;
	QLabel *m_pScale250V_Label;
	QLabel *m_pScale220V_Label;
	QLabel *m_pScale110V_Label;
	QLabel *m_pScale48V_Label;
	QLabel *m_pScale24V_Label;
	QLabel *m_pScale15V_Label;
	QLabel *m_pScaleOther_Label;
	QLabel *m_pScaleClosed_Label;

	QVBoxLayout *m_pScale_VBoxLayout;//刻度显示垂直布局
	QHBoxLayout *m_pBegin_HBoxLayout;//第一行的水平布局
	QHBoxLayout *m_pEnd_HBoxLayout;//第二行的水平布局
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	STT_SystemParas m_oSysParas;

public:
signals:
//	void sig_UpdateAuxDCOutput();//通知外部模块更新测试仪模块辅助直流输出

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	void slot_ScaleSetValue(int nValue);
		void SetUI_ToScaleValue(int nValue);
};

#endif // QAUXDC_OUTPUT_DLG_H
