#ifndef HARMESTIMATEDLG_H
#define HARMESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/tmt_harm_test.h"

class HarmEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	HarmEstimateGrid(int rows, int columns, QWidget* parent);

	~HarmEstimateGrid();

	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_HarmParas* pParas);
	void ComboxModelStyle(QComboBox *pCombox);
	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent * );

private:
	QComboBox* NewErrorType();
	tmt_HarmParas* m_pParas;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);
};

class HarmEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_HarmParas* m_pParas;
	HarmEstimateGrid* m_pGrid;

public:
	HarmEstimateDlg(tmt_HarmParas* pParas, QWidget* parent = NULL);
	~HarmEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};

#endif