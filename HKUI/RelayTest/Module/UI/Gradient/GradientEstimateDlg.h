#ifndef GRADIENTESTIMATEDLG_H
#define GRADIENTESTIMATEDLG_H

#include "../../SttTest/Common/tmt_gradient_test.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../Controls/SettingCtrls/QSettingItem.h"

class GradientEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	GradientEstimateGrid(int rows, int columns, QWidget* parent);
	virtual ~GradientEstimateGrid();
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);
	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_GradientParasEx* pParas);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);//下拉框风格初始化
	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

private:
	QComboBox* NewErrorType();
	QComboBox* AbsErrorType();
	tmt_GradientParasEx* m_pParas;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);

};

class GradientEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_GradientParasEx* m_pParas;
	GradientEstimateGrid* m_pGrid;

public:
	GradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent = NULL);
	virtual ~GradientEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};


#endif