#ifndef SEQUENCEGRADIENTESTIMATEDLG_H
#define SEQUENCEGRADIENTESTIMATEDLG_H

#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

class SequenceGradientEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	SequenceGradientEstimateGrid(int rows, int columns, QWidget* parent);
	~SequenceGradientEstimateGrid();

	virtual void InitGrid();//初始化表头
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);//设置某几列的使能状态
	virtual void InitData(tmt_GradientParasEx* pParas);//根据结构体中的数值，对表格各行各列的值进行初始化
	void ComboxModelStyle(QComboBox *pCombox);//下拉框风格初始化
	void CbbErrorType(int nIndex, CString strText);//绝对误差相对误差的编辑状态

private:
	QComboBox* NewErrorType();//创建新的下拉框相对误差以及绝对误差的组合)
	QComboBox* AbsErrorType();//创建绝对误差下拉框
	tmt_GradientParasEx* m_pParas;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);

};

class SequenceGradientEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_GradientParasEx* m_pParas;
	SequenceGradientEstimateGrid* m_pGrid;

public:
	SequenceGradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent = NULL);
	virtual ~SequenceGradientEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

};

#endif