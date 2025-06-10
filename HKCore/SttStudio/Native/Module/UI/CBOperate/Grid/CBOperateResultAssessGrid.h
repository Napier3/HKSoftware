#ifndef QCBOPERATEADDMULTRESULTASSESS_H
#define QCBOPERATEADDMULTRESULTASSESS_H

#include <QDialog>
#include <QTableWidget>
#include "../../Controls/SttCheckBox.h"
#include <QPushButton>
#include "../../../SttTest/Common/Impedance/tmt_cb_operate_test.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

class CBOperateResultAssessGrid : public QDialog
{
	Q_OBJECT

public:
	CBOperateResultAssessGrid(tmt_CBOperateParas *pCBOperateParas ,QWidget *parent = 0);
	virtual ~CBOperateResultAssessGrid();            

	void InitUI();
	void InitFont();
	void InitConnections(); 
	void UpdataResultAssess();
	bool eventFilter(QObject *obj, QEvent *event);

public:
	QStringList headers;
	QTableWidget *m_pResultTableWidget;
	QTableWidgetItem *item;

	QSttCheckBox *m_pChbActionTime;
	QSttCheckBox *m_pChbTripTime;
	QSttCheckBox *m_pChbAccTime;

	tmt_CBOperateTest m_oCBOperateTest;
	tmt_CBOperateParas *m_oCBOperateParas;

	QPushButton *m_pBtnOK;
	QPushButton *m_pBtnCancel;
	QVBoxLayout *m_pMainLayout;
	QHBoxLayout *m_pButtonLayout;
	QComboBox *m_pCmbActionTime;
	QComboBox *m_pCmbTtripTime;
	QComboBox *m_pCmbAccTime;

	QTableWidgetItem *m_pItem1;
	QTableWidgetItem *m_pItem2;
	QTableWidgetItem *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
	QTableWidgetItem *m_pItem6;
	QTableWidgetItem *m_pItem7;
	QTableWidgetItem *m_pItem8;
	QTableWidgetItem *m_pItem9;

public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
	 
	void slot_ChbActionTime(bool state);
	void slot_ChbTripTime(bool state);
	void slot_ChbAccTime(bool state);
	void slot_cellClicked(int row ,int col);
};

#endif