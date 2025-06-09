#ifndef RESULTEXPRDLG_REPORTS_H
#define RESULTEXPRDLG_REPORTS_H

#include "../../../../Module/DataMngr/DvmData.h"
#include "../../../../Module/DataMngr/DvmValue.h"
#include "../../SttCmd/GuideBook/SttReports.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include <QDialog>
#include <QTreeWidgetItem>

namespace Ui {
class QResultExprDlg_Reports;
}

class QResultExprDlg_Reports : public QDialog
{
    Q_OBJECT

public:
	CSttItemBase* m_pCurItemBase;
	CSttGuideBook* m_pGuideBook;
	CString m_strCurrSelPath;
	CSttReport* m_pReport;

public:
    explicit QResultExprDlg_Reports(QWidget *parent = NULL);
    virtual ~QResultExprDlg_Reports();
	void InitDlg(CSttItemBase* pCurItemBase, CSttGuideBook* pGuideBook);
	void InitTree(QTreeWidgetItem* pParent, CSttItemBase* pCurItemBase);
	void InitLanguage();

private slots:
	void slot_btnOK_Clicked(bool bCheck);
	void slot_btnCancel_Clicked(bool bCheck);

private:
    Ui::QResultExprDlg_Reports *ui;
	
};

#endif // RESULTEXPRDLG_REPORTS_H
