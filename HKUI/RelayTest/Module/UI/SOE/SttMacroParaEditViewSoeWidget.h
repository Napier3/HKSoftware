#ifndef QSttMacroParaEditViewSoeWidget_H
#define QSttMacroParaEditViewSoeWidget_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QComboBox>

#include "SttMacroParaEditViewSoeTable.h"

#include "../Controls/SttTabWidget.h"
#include "../../SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../SttTest/Common/tmt_result_def.h"
#include "../../SttTest/Common/tmt_soe_test.h"

#include "../Controls/SttLineEdit.h"
#include "../Module/ScrollCtrl/ScrollComboBox.h"

class QSttMacroParaEditViewSoeWidget : public QWidget 
{
    Q_OBJECT

public:
    explicit QSttMacroParaEditViewSoeWidget(QWidget *parent = 0);
    ~QSttMacroParaEditViewSoeWidget();

	void InitUI();
	void initConnections();
	void InitComboxData();
	void StartInit();
	void StopInit();

public:

	QVBoxLayout *m_pMain_VLayout; 

	QHBoxLayout *m_pBtn_HLayout;
	QHBoxLayout *m_pHLayout;
	QVBoxLayout *m_pSoe_VLayout; 

	QWidget *m_pSoe_Widget;
	QSttTabWidget *m_pSoeTab;

	QSttLineEdit *m_pPulseWidth_Edit;//脉冲宽度
	QLabel *m_pPulseWidth_Label; 

	QSttLineEdit *m_pSOE_Edit;//SOE分辨率
	QLabel *m_pSOE_Label; 

	QSttLineEdit *m_pDeflectio_Edit;//变位次数
	QLabel *m_pDeflection_Label;
	
	QPushButton *m_pSelectAll_PushButton;//全部选择
	QPushButton *m_pCancelAll_PushButton;//全部取消
	
	QPushButton *m_pInitialAll_PushButton;//初始全合
	QPushButton *m_pInitialDivideAll_PushButton;//初始全分


	QLabel *m_pTrigger_Label;//触发方式
	QScrollComboBox* m_pTrigerConditionCombox;


	QLabel *m_pGPSTime_Label;//触发时刻
	QSttLineEdit *m_pHourEdit; 
	QSttLineEdit *m_pMinuteEdit;
	QSttLineEdit *m_pSecondEdit;
	QLabel * m_pHourLabel;
	QLabel * m_pMinuteLabel;
	QLabel * m_pSecondLabel;
	
	QSttMacroParaEditViewSoeTable *m_pSoeGrid;
		
public:
	
	tmt_SoeParas    *m_pSoeParas;
	QStringList listTrigerConditions;
	


public:
	void SetData(tmt_SoeParas* pSoeParas);
	void UpdateData();
	void UpdateTriggerBtnState();

public slots:

	void slot_currentChangedTabWidget(int nCurrIndex);


	void slot_cmb_TrigerConditionChanged(int index);



};


#endif // QSttMacroParaEditViewSoeWidget_H
