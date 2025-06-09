#ifndef SEQUENCEMANUALESTIMATEDLG_H
#define SEQUENCEMANUALESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/Sequence/tmt_sequence_manu_test.h"
#include "../Module/ScrollCtrl/ScrollTableWidget.h"

class SequenceEstimateGrid : public QScrollTableWidget //public QTableWidget//20240808 gongyiping
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

	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	void SetItemEnable(int nRow, int nCol, BOOL bEnable);//根据使能状态设置背景颜色

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