#ifndef STATETRIGERWIDGET_H
#define STATETRIGERWIDGET_H

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
#include <QStackedLayout>
#include "../../Module/SttTest/Common/tmt_state_test.h"
#include "../Controls/SttLineEdit.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/OSInterface/OSInterface.h"


class QStateTrigerWidget : public QWidget
{
	Q_OBJECT

public:
	QStateTrigerWidget(BOOL *pbTmtParaChanged,QWidget *parent = 0);
	~QStateTrigerWidget();
	tmt_StatePara* m_pTrigerWidgetStatePara;
	void SetData(tmt_StatePara* pStatePara);
	bool m_bHorizontal;

	void InitUI();
	QStringList listTrigerConditions;

	void InitBaseData();
	void SetStateFont();//设置字体大小
	void InitConnections();
	void UpdateData();
	void UpdateTriggerBtnState();
	void UpdateOutPut();
	void UpdateInPut();

	void startInit();
	void stopInit();

	virtual void MakeOutPut(int nIndex,bool bSel);
	virtual void MakeInPut(int nIndex,bool bSel);
	
	void UpdateAuxDcEnabled();
	
private:
	BOOL *m_pbTmtParaChanged;

public:
	QLabel* m_pTrigerCondition;//触发条件
    QLabel* m_pTrigerHoldTime;//触发后保持时间:
	QLabel* m_pTrigerTime;//触发时刻
	QLabel* m_pOutputTime;//输出时间
	QLabel* m_pHour;
	QLabel* m_pMinute;
	QLabel* m_pSecond;
	QScrollComboBox* m_pTrigerConditionCombox;
	//QSttLineEdit* m_pTrigerHoldTimeEdit;
	//QSttLineEdit* m_pOutputTimeEdit;
	//QSttLineEdit* m_pHourEdit;
	//QSttLineEdit* m_pMinuteEdit;
	//QSttLineEdit* m_pSecondEdit;
	//QSttLineEdit* m_pEditUdc;
	QSettingLineEdit* m_pTrigerHoldTimeEdit;	//20240625 huangliang
	QSettingLineEdit* m_pOutputTimeEdit;
	QSettingLineEdit* m_pHourEdit;
	QSettingLineEdit* m_pMinuteEdit;
	QSettingLineEdit* m_pSecondEdit;
	QSettingLineEdit* m_pEditUdc;
	QLabel *m_pLabUdc;

	QGroupBox* m_pBoutBox;//开出量
	QCheckBox* m_pBout_1;
	QCheckBox* m_pBout_2;
	QCheckBox* m_pBout_3;
	QCheckBox* m_pBout_4;

	QGridLayout* m_pGridLayoutLeft;
	QGridLayout* m_pBinLayout;//开入量
	QLabel* m_pBinLab;
	QCheckBox* m_pBin_A;
	QCheckBox* m_pBin_B;
	QCheckBox* m_pBin_C;
	QCheckBox* m_pBin_D;

protected slots:
    void slot_cmb_TrigerConditionChanged(int index);
	void slot_lneH_GPSTimeChanged();
	void slot_lneM_GPSTimeChanged();
	void slot_lneS_GPSTimeChanged();

	void slot_lneH_GPSTimeChangedKeyBoard();
	void slot_lneM_GPSTimeChangedKeyBoard();
	void slot_lneS_GPSTimeChangedKeyBoard();

	void slot_lne_OutputTimeChanged();
	void slot_lne_OutputTimeChangedKeyBoard();

 	void slot_chb_OutPut1StateChanged(int);
	void slot_chb_OutPut2StateChanged(int);
 	void slot_chb_OutPut3StateChanged(int);
 	void slot_chb_OutPut4StateChanged(int);

	void slot_chb_InPutA_StateChanged(int);
	void slot_chb_InPutB_StateChanged(int);
	void slot_chb_InPutC_StateChanged(int);
	void slot_chb_InPutD_StateChanged(int);

	void slot_lne_TrigerHoldTimeChanged();
	void slot_lne_TrigerHoldTimeChangedKeyBoard();

	void slot_lne_EditUdcChanged();
	void slot_lne_EditUdcChangedKeyBoard();
	

signals:
	void sig_UpdateToolButtons();
	
};
extern CFont *g_pSttGlobalFont;  
#endif 
