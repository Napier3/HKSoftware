#ifndef ThreeRecloseEstimateDlg_H
#define ThreeRecloseEstimateDlg_H
#include <QDialog>
#include <QTableWidget>
#include <QComboBox>
#include "../../DataMngr/DataGroup.h"
#include <QMouseEvent>
#include <QStyle>
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"


class QCenterComboBox : public QComboBox
{
	Q_OBJECT
public:
	explicit QCenterComboBox(QWidget *parent = 0);
	~QCenterComboBox();
    virtual bool eventFilter(QObject *watched, QEvent *event) ;
private:
	bool m_bPopupVisible;
};


class QThreeRecloseEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	QThreeRecloseEstimateGrid(CDataGroup* pParas,QWidget* parent);
	~QThreeRecloseEstimateGrid();

	void InitUI();
	void InitTable();
 	void ComboxModelStyle(QComboBox *pCombox);
// 	QCenterComboBox* NewErrorType();
	QComboBox* NewErrorType();
	void GetComboxValue(const CString &strID,QComboBox *pCombox);
	void GetTableWidgetItemValue(QTableWidgetItem *pItem,const CString &strID,bool bAbs);
	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

private:
	CDataGroup* m_pParas;
	QExBaseListComBoxDelegBase *m_pCbbErrorDelegate;

protected slots:
	void slot_OnCellChanged(int row,int col);
};


class QThreeRecloseEstimateDlg : public QDialog
{
	Q_OBJECT

public:
	QThreeRecloseEstimateDlg(CDataGroup* pParas,QWidget* parent = NULL);
	~QThreeRecloseEstimateDlg();

public:
	void InitUI();

private:
	QThreeRecloseEstimateGrid* m_pGrid;
	CDataGroup* m_pParas;


protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();
};
#endif
