#ifndef IMPEDANCEMANUESTIMATEDLG_H
#define IMPEDANCEMANUESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/Impedance/tmt_manuImped_test.h"

class ImpedanceEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	ImpedanceEstimateGrid(int rows, int columns, QWidget* parent);
	~ImpedanceEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_ManualImpedParas* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);


private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_ManualImpedParas* m_pParas;


protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class ImpedanceManuEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_ManualImpedParas* m_pParas;
	ImpedanceEstimateGrid* m_pGrid;

public:
	ImpedanceManuEstimateDlg(tmt_ManualImpedParas* pParas, QWidget* parent = NULL);
	~ImpedanceManuEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif