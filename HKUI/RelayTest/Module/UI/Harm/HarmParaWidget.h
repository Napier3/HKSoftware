#ifndef QHARMPARAWIDGET_H
#define QHARMPARAWIDGET_H

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include "../Controls/SttLineEdit.h"
#include "../Module/SttUIDefine.h"
#include "../../../Module/SttTest/Common/tmt_harm_test.h"
#include "../../../Module/SttTestResourceMngr/TestResource/SttTestResourceBase.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../Controls/SttGroupBox.h"
#include "../Controls/SettingCtrls/QSettingLineEdit.h"

class QHarmParaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QHarmParaWidget(QWidget *parent = 0);
	virtual ~QHarmParaWidget();
	void InitUI();
    void SetData(CSttTestResourceBase *pSttTestResource,tmt_HarmParas *pHarmParas);
	void UpdataPara();
	void InitConnect();
	void UpdateBinaryInBinaryOutEnable();

	void StartInit();
	void StopInit();
	int GetHarmIndex();

	void SetGradientCurSelCh(para_type vartype);//设置当前选择通道
	void SetHarmOrderCombox();//设置当前选择谐波次数
	void SetGradientCurSelCh();//设置当前选择通道 //20240327 suyang 增加函数对通道选择做处理，上一次保存数据会重新刷新

	void SetBinaryInBinaryOutEnable(bool bFlag);
	void UpdateGradLabelUnit();
	bool IsHarmGradPercentType();

	virtual void paintEvent(QPaintEvent *);
	void SetHarmParaFont();

	bool IsChannelValid();

public:
	CSttTestResourceBase* m_pTestResource;
	tmt_HarmParas* m_pHarmParas;
	QStringList m_strHarmList;

	int m_nDispMode;				//0:显示一次值 1:显示二次值
	CDataType m_oGradientChs;				//递变通道选择对象
	long m_nHarmGradType;//谐波递变类型 0：幅值  1：百分比
	CString m_strChanelText;

public:
	QVBoxLayout *m_pVBoxLayout_Main;
    QSttGroupBox *m_pGroupBox_Gradient;
	QVBoxLayout *m_pVLayout_GadientMain;
	QGridLayout *m_pGridLayout_Gadient;
	QHBoxLayout *m_pHLayout_Gadient;
	QLabel *m_pLabel_ChannelChose;
	QLabel *m_pLabel_End;
	QLabel *m_pLabel_Step;
	QLabel *m_pLabel_Start;
	QLabel *m_pLabel_StepTime;
	QScrollComboBox *m_pCmb_Chanel;
    QScrollComboBox *m_pCmb_HarmNum;
//	QSttLineEdit *m_pEdit_Step;
//  QSttLineEdit *m_pEdit_End;
//  QSttLineEdit *m_pEdit_Start;
//  QSttLineEdit *m_pEdit_Steptime;
	QSettingLineEdit *m_pEdit_Step;		//20240624 huangliang
	QSettingLineEdit *m_pEdit_End;
	QSettingLineEdit *m_pEdit_Start;
	QSettingLineEdit *m_pEdit_Steptime;

	QCheckBox *m_pCheck_Auto;

	QRadioButton* m_RadioBtn_Amplitude;
	QRadioButton* m_RadioBtn_Percent;

	QSttGroupBox *m_pGroupBox_PutInSet;
	QGridLayout *m_pGridLayout_PutInSet;
	QCheckBox *m_pCheck_Input1;
	QCheckBox *m_pCheck_Input2;
	QCheckBox *m_pCheck_Input3;
	QCheckBox *m_pCheck_Input4;
	QCheckBox *m_pCheck_Input5;
	QCheckBox *m_pCheck_Input6;
	QCheckBox *m_pCheck_Input7;
	QCheckBox *m_pCheck_Input8;
	QCheckBox *m_pCheck_Input9;
	QCheckBox *m_pCheck_Input10;
	QRadioButton* m_pLogicAnd;
	QRadioButton* m_pLogicOr;

	QSttGroupBox *m_pGroupBox_PutOutSet;
    QGridLayout *m_pGridLayout_PutOutSet;
    QCheckBox *m_pCheck_Output1;
    QCheckBox *m_pCheck_Output2;
    QCheckBox *m_pCheck_Output3;
    QCheckBox *m_pCheck_Output4;
    QCheckBox *m_pCheck_Output5;
    QCheckBox *m_pCheck_Output6;
    QCheckBox *m_pCheck_Output7;
    QCheckBox *m_pCheck_Output8;
	QCheckBox *m_pCheck_Output9;
	QCheckBox *m_pCheck_Output10;
signals:
	void sig_OutPutStateChanged();
	void sig_InPutStateChanged();
	void sig_AutoStateChanged(bool);

public slots:
	void slot_cmb_ChanelIndexChanged(int index);
	void slot_cmb_HarmOrderIndexChanged(int index);

	void slot_lne_StartChanged();
	void slot_lne_EndChanged();
	void slot_lne_StepChanged();
	void slot_lne_StepTimeChanged();

	void slot_lne_StartClicked();
	void slot_lne_EndClicked();
	void slot_lne_StepClicked();
	void slot_lne_StepTimeClicked();

	void slot_ck_AutoStateChanged(int);

	void slot_ck_In1StateChanged(int);
	void slot_ck_In2StateChanged(int);
	void slot_ck_In3StateChanged(int);
	void slot_ck_In4StateChanged(int);
	void slot_ck_In5StateChanged(int);
	void slot_ck_In6StateChanged(int);
	void slot_ck_In7StateChanged(int);
	void slot_ck_In8StateChanged(int);
	void slot_ck_In9StateChanged(int);
	void slot_ck_In10StateChanged(int);

	void slot_ck_Out1StateChanged(int);
	void slot_ck_Out2StateChanged(int);
	void slot_ck_Out3StateChanged(int);
	void slot_ck_Out4StateChanged(int);
	void slot_ck_Out5StateChanged(int);
	void slot_ck_Out6StateChanged(int);
	void slot_ck_Out7StateChanged(int);
	void slot_ck_Out8StateChanged(int);
	void slot_ck_Out9StateChanged(int);
	void slot_ck_Out10StateChanged(int);

	void slot_radio_AndStateChanged(bool);
	void slot_radio_OrStateChanged(bool);
	void slot_radio_HarmGradTypeStateChanged(bool);
};

extern CFont *g_pSttGlobalFont; 

#endif // QHARMPARAWIDGET_H
