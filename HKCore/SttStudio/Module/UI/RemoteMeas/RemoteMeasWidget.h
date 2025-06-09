#ifndef REMOTEMEASWIDGET_H
#define REMOTEMEASWIDGET_H

#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/tmt_manu_test.h"

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

class QRemoteMeasWidget : public QWidget
{
	Q_OBJECT

public:
    QRemoteMeasWidget(QWidget *pParent);
    virtual ~QRemoteMeasWidget();
	void InitUI();
	void InitConnect();

	QIcon m_imgLock;
	QIcon m_imgUnlock;

	QLabel* m_pChSelect_Label; 
	//QSttTabWidget *m_pTelemeterTab;

	QGridLayout *m_pMainGridLayout;
	//QWidget *m_pVolCurr_Widget;
	QScrollComboBox *m_pChSelect_ComboBox;
	QScrollComboBox *m_pChGradientType_ComboBox;//通道类型选择(幅值/相位/频率)
	QLabel* m_pStepTime_Label; 
	QSttLineEdit *m_pStepTime_LineEdit;
	QSttCheckBox *m_pAuto_CheckBox;

	QLabel* m_pStartValue_Label; 
	QSttLineEdit *m_pStartValue_LineEdit;

	QLabel* m_pEndValue_Label; 
	QSttLineEdit *m_pEndValue_LineEdit;

	QLabel* m_pStepValue_Label; 
	QSttLineEdit *m_pStepValue_LineEdit;

	QLabel* m_pChangedType_Label; 
	QScrollComboBox *m_pChangedType_ComboBox;

	QPushButton *m_pLock_PushButton;
	QPushButton *m_pAdd_PushButton;
	QPushButton *m_pMinus_PushButton;

public:
	CSttTestResourceBase* m_pTestResource;
	tmt_ManualParas* m_pManualParas;
	CEventResult* m_pEvent;

	int m_nVChNums,m_nIChNums;

public:
	bool m_bControlLock; //锁
	QString m_sUnit;
	CDataType m_oGradientChs;

	long m_nChanneType; //电压还是电流 0-电压 1-电流
	long m_nUnitType; //0-幅值 1-相位 2-频率

	float slot_lne_Changed(QLineEdit* pLineEdit);

public:
	void SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* pManualParas,CEventResult* pEvent);
	void UpdateData();
	void InitGradientData();
	void SetUnitType (int index);
	long GetChsCount() { return m_oGradientChs.GetCount(); }

	void InitGradientVarList();
	void InitGradientVar(para_type vartype);

	void StartInit();
	void StopInit();

public:
	void slot_btn_LockClicked();
	void slot_btn_AddClicked();
	void slot_btn_MinusClicked();
	void slot_lne_startChanged();
	void slot_lne_endChanged();
	void slot_lne_stepChanged();
	void slot_lne_steptimeChanged();
	void slot_cb_AutoClicked();
	void slot_cbb_SelectChanged(int index);
	void slot_cbb_ChannelChanged(int index);
	void slot_cbb_ChangeTypeChanged(int index);

signals:
	//向界面类发信号调用表格类的函数
	void sig_ChannelTableItemValue(QString str,float fstep,int valueFlag,int AddOrMinus,bool bDC);
};

#endif // REMOTEMEASWIDGET_H
