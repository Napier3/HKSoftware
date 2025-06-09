#ifndef QCBOPERATEADDMULTRESULTASSESS_H
#define QCBOPERATEADDMULTRESULTASSESS_H

#include <QLabel>
#include <QDialog>
#include <QTableWidget>
#include "../../Controls/SttCheckBox.h"
#include <QPushButton>
#include "../../../SttTest/Common/Impedance/tmt_cb_operate_test.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../UI/Controls/SettingCtrls/QSettingLineEdit.h"
#include "../../../TestUI/Interface/QModalDlgInterface.h"

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
	void UpdateTable(int nIndex, int row);
public:
	QStringList headers;
	QTableWidget *m_pResultTableWidget;
	QTableWidgetItem *item;
	QLabel *m_pLabActionTime;
	QLabel *m_pLabTripTime;
	QLabel *m_pLabAccTime;

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
	QSettingLineEdit *m_pItem3;
	QTableWidgetItem *m_pItem4;
	QTableWidgetItem *m_pItem5;
	QSettingLineEdit *m_pItem6;
	QTableWidgetItem *m_pItem7;
	QTableWidgetItem *m_pItem8;
	QSettingLineEdit *m_pItem9;

	QTableWidgetItem *m_pItem10;
	QTableWidgetItem *m_pItem11;
	QTableWidgetItem *m_pItem12;


public slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

	void slot_CmbActionTime(int nIndex);
	void slot_CmbTripTime(int nIndex);
	void slot_CmbAccTime(int nIndex);

	void slot_cellClicked(int row ,int col);
	void slot_Item3();
	void slot_Item6();
	void slot_Item9();
};

#endif