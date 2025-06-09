#ifndef SttGbViewRpts_H
#define SttGbViewRpts_H

#include <QDialog>
#include "../../../SttCmd/GuideBook/SttItemBase.h"
#include "SttGbRptGrid_Dataset.h"
#include "SttGbRptGrid_Values.h"

namespace Ui {
class QSttGbViewRpts;
}

class QSttGbViewRpts : public QDialog, public CExBaseListGridOptrInterface 
{
	Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

public:
    explicit QSttGbViewRpts(CSttItemBase *pSttItemBase, QWidget *parent = 0);
    virtual ~QSttGbViewRpts();

	CSttItemBase *m_pSttItemBase;
	CExBaseList m_oListRsltExpr;  //根据结果判断表达式，筛选的结果变量，重新new出来，存放对象为CDvmValue
	CExBaseList m_oListReports;  //用于显示的报告列表

	QTabWidget *m_tabRpts;
	CSttGbRptGrid_Dataset *m_pGridDataset; //报告数据-数据集；
	CSttGbRptGrid_Values *m_pGridValues_All;   //全部报告数据；
	CSttGbRptGrid_Values *m_pGridValues_RsltExpr;   //结果判断表达式中用到的报告数据；

	void ShowRpts(long nIndex = 0);
	void SetWindowTitle();
	void TestCountComboBox_Init(QComboBox *pComboBox);
	void InitShowReports(CSttItemBase *pSttItemBase, CExBaseList *pListReports);
	void GetRsltExprValues_RelPath(CExBaseList *pRlstExprValues, CExBaseList *pListXExprValues, long nRptIndex);
	CSttItemBase* GetRelItem(const CString &strItemPath);

public slots:
	void on_m_cmbTestCount_currentIndexChanged(int index);

private slots:

private:
    Ui::QSttGbViewRpts *ui;
};

#endif // SttGbViewRpts_H
