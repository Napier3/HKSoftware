#ifndef FAULTGRADIENTESTIMATEDLG_H
#define FAULTGRADIENTESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include "../../SttTest/Common/Gradient/tmt_fault_gradient_test.h"
#include "../Module/ScrollCtrl/ScrollTableWidget.h"
namespace Ui {class CFaultGradientEstimateDlg;};

class QFaultGradientEstimateGrid : public QScrollTableWidget //public QTableWidget//20240808 gongyiping
{
	Q_OBJECT
public:
	explicit QFaultGradientEstimateGrid(QWidget *parent = 0);
	virtual ~QFaultGradientEstimateGrid();
	void SetItemEnable(int nRow, int nCol, BOOL bEnable);
	virtual void InitGrid();
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);
	virtual void InitData(tmt_fault_gradient_test* pParas);
	void addTabRow(int nRow,QString strValue,int nComType,long l1Value,float f2Value,float f3Value,float f4Value);
	void CbbErrorType(int nIndex, CString strText);
	void SetTabComboxModelStyle(QComboBox *pCombox);

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

class CFaultGradientEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	CFaultGradientEstimateDlg(tmt_fault_gradient_test* pPara,QWidget *parent = 0);
	~CFaultGradientEstimateDlg();

public:
	void initUI();
	void initTab();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

private:
	Ui::CFaultGradientEstimateDlg *ui;
	tmt_fault_gradient_test*	   m_pCurFGTest;
};

#endif // FAULTGRADIENTESTIMATEDLG_H
