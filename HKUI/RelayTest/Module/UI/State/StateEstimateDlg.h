#ifndef STATEESTIMATEDLG_H
#define STATEESTIMATEDLG_H

#include "../../SttTest/Common/tmt_state_test.h"

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

class StateEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	tmt_StateParas* m_pParas;

	StateEstimateGrid(int rows, int columns, QWidget* parent);
	virtual ~StateEstimateGrid();

	virtual void InitGrid();
	virtual void InitData(tmt_StateParas* pParas);

	QList<int >m_SelStateList;//勾选的状态序号
private:
	void InitStateData(long nIndexEstimate);
	void InitStateBin(CString strStateName, long nRow, long nCol);
	void CbbErrorType(int nIndex, CString strText);
	void ComboxModelStyle(QComboBox *pCombox);

	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);

private slots:
	void slot_StateBinChanged(const QString& strText);
	void slot_cmbErrorChanged(const QString& strText);
	void slot_OnCellChanged(int row,int col);

};

class StateEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_StateParas* m_pParas;
	StateEstimateGrid* m_pGrid;

public:
	StateEstimateDlg(tmt_StateParas* pParas, QWidget* parent = NULL);
	virtual ~StateEstimateDlg();

public:
	void InitUI();

private:
	CString SaveState(long nRow, long nCol);
	CString SaveStateBin(long nRow, long nCol);

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};



#endif
