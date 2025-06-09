#ifndef QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H
#define QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H
#include "ui_QSttVoltageTimeGroupTestItemWidget.h"
#include "../Controls/SttLineEdit.h"
#include <QWidget>
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "../SttTestCntrCmdDefine.h"
#include "../../SttTest/Common/FAParasSet/tmt_fa_Paras_set.h"
#include "../../UI/Module/FAParasSetWidget/QSttFAParasSetDialog.h"
#include "../../../../Module/BaseClass/QT/QExBaseListTreeCtrl.h"
#include "../Controls/SttCheckBox.h"
#include <QSplitter>
#include <QTextEdit>
#include <QList>

namespace Ui{
	class QSttVoltageTimeGroupTestItemWidget;
}

class QSttVoltageTimeGroupTestItemWidget : public QWidget
{
	Q_OBJECT

public:
	Ui::QSttVoltageTimeGroupTestItemWidget *ui;

	QSttVoltageTimeGroupTestItemWidget(QWidget *parent = NULL);
	virtual ~QSttVoltageTimeGroupTestItemWidget();

	QWidget* m_pTestResultViewWidget;						//测试结果视图表格

	QSttFAParasSetDialog* m_pSttFAParasSetDialog;

	CDataGroup m_oVolTimeTypeSecDataGroup;
	QSttCheckBox *m_pCheckBox;
	QList<QSttCheckBox*> checkBoxList; // 存储复选框的列表
	QTableWidgetItem *m_pCheckItem;
	QTableWidgetItem  *m_pItem;

public:
	void InitSOEDatas();
	void InitUI();
	void InitStyle();
	void SaveXmlParas();
	void InitConnections();
	void GetDatas(CDataGroup *pParas);
	virtual BOOL OpenTestTestMngrFile(const CString& strParasFile);

public slots:
	void slot_SelectAllClicked(bool checked);
	void slot_UnSelectAllClicked(bool checked);
	void slot_TableWidgetClicked(int row, int col);
	void slot_CheckBoxClicked(bool checked);

};

#endif
