#ifndef STATEPARAWIDGET_H
#define STATEPARAWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QStringList>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

class QStateParaWidget : public QWidget
{
	Q_OBJECT

public:
	QStateParaWidget(BOOL *pbTmtParaChanged,QWidget *parent = 0);
	~QStateParaWidget();

	tmt_StatePara* m_pStatePara;
	void setData(tmt_StatePara* pStatePara);

	QStringList listTrigerConditions;
	
	void initUI();
	void initConnections();
	void initBaseData();

	void UpdateData();
	void UpdateInput();
	void UpdateOutPut();
	void UpdateTriggerBtnState();
	void SetBinaryInEnable(bool bFlag);

	void startInit();
	void stopInit();

	virtual void MakeInPut(int nIndex,bool bSel);
	virtual void MakeOutPut(int nIndex,bool bSel);

	long CalculateBin();//开入量选中计算

	void SetStateParaFont();//设置字体大小

private:
	BOOL *m_pbTmtParaChanged;

signals:
	void sig_SwitchStateChanged();

public:
	QGroupBox* m_pTrigerBox;
	QGroupBox* m_pBinBox;
	QGroupBox* m_pBoutBox;

	QLabel* m_pTrigerCondition;
	QLabel* m_pTrigerTime;
	QLabel* m_pOutputTime;
	QLabel* m_pTrigerHoldTime;
	QLabel* m_pOutputHoldTime;
	QLabel* m_pHour;
	QLabel* m_pMinute;
	QLabel* m_pSecond;

	QScrollComboBox* m_pTrigerConditionCombox;
	QSttLineEdit* m_pOutputTimeEdit;
	QSttLineEdit* m_pTrigerHoldTimeEdit;
	QSttLineEdit* m_pOutputHoldTimeEdit;
	QSttLineEdit* m_pHourEdit;
	QSttLineEdit* m_pMinuteEdit;
	QSttLineEdit* m_pSecondEdit;

	QCheckBox* m_pBin_A;
	QCheckBox* m_pBin_B;
	QCheckBox* m_pBin_C;
	QCheckBox* m_pBin_D;
	QCheckBox* m_pBin_E;
	QCheckBox* m_pBin_F;
	QCheckBox* m_pBin_G;
	QCheckBox* m_pBin_H;
	QCheckBox* m_pBin_I;
	QCheckBox* m_pBin_J;

	QRadioButton* m_pLogicOr;
	QRadioButton* m_pLogicAnd;

	QCheckBox* m_pBout_1;
	QCheckBox* m_pBout_2;
	QCheckBox* m_pBout_3;
	QCheckBox* m_pBout_4;
	QCheckBox* m_pBout_5;
	QCheckBox* m_pBout_6;
	QCheckBox* m_pBout_7;
	QCheckBox* m_pBout_8;
	QCheckBox* m_pBout_9;
	QCheckBox* m_pBout_10;
	QCheckBox* m_pChk_HoldTime;

protected slots:
	void slot_cmb_TrigerConditionChanged(int index);
	void slot_lne_OutputTimeChanged();

	void slot_lneH_GPSTimeChanged();
	void slot_lneM_GPSTimeChanged();
	void slot_lneS_GPSTimeChanged();
	void slot_lne_TrigerHoldTimeChanged();

	void slot_chb_InputAStateChanged(int);
	void slot_chb_InputBStateChanged(int);
	void slot_chb_InputCStateChanged(int);
	void slot_chb_InputDStateChanged(int);
	void slot_chb_InputEStateChanged(int);
	void slot_chb_InputFStateChanged(int);
	void slot_chb_InputGStateChanged(int);
	void slot_chb_InputHStateChanged(int);
	void slot_chb_InputIStateChanged(int);
	void slot_chb_InputJStateChanged(int);

	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);
	
	void slot_chb_OutPut1StateChanged(int);
	void slot_chb_OutPut2StateChanged(int);
	void slot_chb_OutPut3StateChanged(int);
	void slot_chb_OutPut4StateChanged(int);
	void slot_chb_OutPut5StateChanged(int);
	void slot_chb_OutPut6StateChanged(int);
	void slot_chb_OutPut7StateChanged(int);
	void slot_chb_OutPut8StateChanged(int);
	void slot_chb_OutPut9StateChanged(int);
	void slot_chb_OutPut10StateChanged(int);
	void slot_lne_OutPutHoldTimeChanged();
	void slot_chb_OutPutHoldTimeStateChanged(int);
 
	void slot_lne_OutputTimeChangedKeyBoard();
	void slot_lneH_GPSTimeChangedKeyBoard();
	void slot_lneM_GPSTimeChangedKeyBoard();
	void slot_lneS_GPSTimeChangedKeyBoard();
	void slot_lne_TrigerHoldTimeChangedKeyBoard();
	void slot_lne_OutPutHoldTimeChangedKeyBoard();
};

#endif // STATEPARAWIDGET_H
