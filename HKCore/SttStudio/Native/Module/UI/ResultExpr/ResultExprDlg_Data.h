#ifndef RESULTEXPRDLG_DATA_H
#define RESULTEXPRDLG_DATA_H

#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/DataMngr/DvmValue.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "../../SttCmd/GuideBook/SttReports.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class QResultExprDlg_Data;
}

class QResultExprDlg_DataGrid : public QExBaseListGridBase
{
public:
	CSttItemBase* m_pCurSttItemBase;
	CTestMacros* m_pTestMacros;

public:
	QResultExprDlg_DataGrid(QWidget* pParent);
	virtual ~QResultExprDlg_DataGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void InitLanguage();
};

class QResultExprDlg_Data : public QDialog
{
    Q_OBJECT
public:
	CDvmValue* m_pCurSelValue;
	CString m_strCurValue;
	CString m_strCurType;

	CSttItemBase* m_pCurSttItemBase;
	CSttReports* m_pReports;
	CSttGuideBook* m_pGuideBook;
	CTestMacros* m_pTestMacros;

    explicit QResultExprDlg_Data(QWidget *parent = NULL);
    virtual ~QResultExprDlg_Data();

	void ShowDatas(CExBaseList* pList);
	void InitDlg(CSttItemBase* pCurSttItemBase, CSttReports* pReports, CSttGuideBook* pGuideBook, CTestMacros* pTestMacros);
	void ShowDatasetTree();
	void InitLanguage();

private slots:
	void slot_btnOK_Clicked(bool bCheck);
	void slot_btnCancel_Clicked(bool bCheck);
	void slot_SelectReport(bool bCheck);
	void slot_btnChangeReport_Clicked();
	void slot_currentChanged(int nIndex);
	void slot_currentItemChanged(QTreeWidgetItem* pCurItem, QTreeWidgetItem* pPrevItem);

private:
    Ui::QResultExprDlg_Data *ui;
	QResultExprDlg_DataGrid* m_pReportGrid;
};

#endif // RESULTEXPRDLG_DATA_H
