#ifndef INTELLTERMINALWIDGET_H
#define INTELLTERMINALWIDGET_H

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
#define PARAS_RSLT_COUNT		150

class QIntellTerminalWidget : public QWidget
{
	Q_OBJECT

public:
    QIntellTerminalWidget(QWidget *pParent);
    virtual ~QIntellTerminalWidget();
	void InitUI();
	void InitConnect();

	QSttTabWidget *m_pIntellTerminalTab;
	QGridLayout *m_pMainGridLayout;
	QPushButton *m_pBinarySet_PushButton;

public:
	CSttTestResourceBase* m_pTestResource;
	tmt_ManualParas* m_pIntellTerminalParas;
	CEventResult* m_pEvent;

public:

	void ValidBinSelect();//验证开入选择是否有效,如果全都不选,默认勾选开入A

public:
	void SetData(CSttTestResourceBase *pSttTestResource,tmt_ManualParas* pIntellTerminalParas,CEventResult* pEvent);
	void UpdateData();

	void StartInit();
	void StopInit();

protected slots:
	void slot_currentChangedTabWidget(int nCurrIndex);

};

#endif //INTELLTERMINALWIDGET_H
