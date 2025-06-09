#ifndef LINEVOLGRADIENTESTIMATEDLG_H
#define LINEVOLGRADIENTESTIMATEDLG_H

#include "../../SttTest/Common/LineVolt/tmt_linevolt_gradient_test.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

#include "../Module/ScrollCtrl/ScrollTableWidget.h"

class LineVolGradientEstimateGrid : public QScrollTableWidget
{
	Q_OBJECT
public:
	LineVolGradientEstimateGrid(int rows, int columns, QWidget* parent);
	virtual ~LineVolGradientEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_LineVolGradientParasEx* pParas);
	void ComboxModelStyle(QComboBox *pCombox);//下拉框风格初始化
	void CbbErrorType(int nIndex, CString strText);//绝对误差相对误差的编辑状态
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);

	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class LineVolGradientEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_LineVolGradientParasEx* m_pParas;
	LineVolGradientEstimateGrid* m_pGrid;

public:
	LineVolGradientEstimateDlg(tmt_LineVolGradientParasEx* pParas, QWidget* parent = NULL);
	virtual ~LineVolGradientEstimateDlg();

public:
	void InitUI();

	protected slots:
		void slot_btnOK_Clicked();
		void slot_btnCancel_Clicked();
};

#endif