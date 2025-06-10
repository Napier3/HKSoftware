#ifndef LINEVOLTMANUALESTIMATEDLG_H
#define LINEVOLTMANUALESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/LineVolt/tmt_linevolt_manu_test.h"
class LineVoltEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	LineVoltEstimateGrid(int rows, int columns, QWidget* parent);
	~LineVoltEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_LinevoltManuParas* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);


private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_LinevoltManuParas* m_pParas;


protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class LineVoltManualEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_LinevoltManuParas* m_pParas;
	LineVoltEstimateGrid* m_pGrid;

public:
	LineVoltManualEstimateDlg(tmt_LinevoltManuParas* pParas, QWidget* parent = NULL);
	~LineVoltManualEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif