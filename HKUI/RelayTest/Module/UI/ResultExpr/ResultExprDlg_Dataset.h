#ifndef RESULTEXPRDLG_REPORT_H
#define RESULTEXPRDLG_REPORT_H

#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/DataMngr/DvmValue.h"
#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include <QDialog>

namespace Ui {
class QResultExprDlg_Dataset;
}

class QResultExprDlg_DatasetGrid : public QExBaseListGridBase
{
public:
	QResultExprDlg_DatasetGrid(QWidget* pParent);
	virtual ~QResultExprDlg_DatasetGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

class QResultExprDlg_Dataset : public QDialog
{
    Q_OBJECT

public:
	CDvmValue* m_pCurSelValue;
	void InitLanguage();

public:
    explicit QResultExprDlg_Dataset(QWidget *parent = NULL);
    virtual ~QResultExprDlg_Dataset();

	void ShowDatas(CExBaseList* pList);

private slots:
	void slot_btnOK_Clicked(bool bCheck);
	void slot_btnCancel_Clicked(bool bCheck);

private:
    Ui::QResultExprDlg_Dataset *ui;
	QResultExprDlg_DatasetGrid* m_pReportGrid;
	
};

#endif // RESULTEXPRDLG_REPORT_H
