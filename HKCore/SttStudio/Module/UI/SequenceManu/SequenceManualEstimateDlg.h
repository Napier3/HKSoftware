#ifndef SEQUENCEMANUALESTIMATEDLG_H
#define SEQUENCEMANUALESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/Sequence/tmt_sequence_manu_test.h"

class SequenceEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	SequenceEstimateGrid(int rows, int columns, QWidget* parent);
	~SequenceEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_SequenceManuParas* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);


private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_SequenceManuParas* m_pParas;


protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class SequenceManualEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_SequenceManuParas* m_pParas;
	SequenceEstimateGrid* m_pGrid;

public:
	SequenceManualEstimateDlg(tmt_SequenceManuParas* pParas, QWidget* parent = NULL);
	~SequenceManualEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif