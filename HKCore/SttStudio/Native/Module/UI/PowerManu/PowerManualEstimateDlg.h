#ifndef POWERMANUALESTIMATEDLG_H
#define POWERMANUALESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/Power/tmt_power_manu_test.h"

class PowerEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	PowerEstimateGrid(int rows, int columns, QWidget* parent);
	~PowerEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_PowerManuParas* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);


private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_PowerManuParas* m_pParas;


protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class PowerManualEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_PowerManuParas* m_pParas;
	PowerEstimateGrid* m_pGrid;

public:
	PowerManualEstimateDlg(tmt_PowerManuParas* pParas, QWidget* parent = NULL);
	~PowerManualEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif