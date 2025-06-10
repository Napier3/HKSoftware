#ifndef MANUALESTIMATEDLG_H
#define MANUALESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/tmt_manu_test.h"
class ManualEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	ManualEstimateGrid(int rows, int columns, QWidget* parent);
	 ~ManualEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_ManualParas* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);

	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_ManualParas* m_pParas;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);

};

class ManualEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_ManualParas* m_pParas;
	ManualEstimateGrid* m_pGrid;

public:
	ManualEstimateDlg(tmt_ManualParas* pParas, QWidget* parent = NULL);
	 ~ManualEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif


