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
	CExBaseList m_oListRsltExpr;  //���ݽ���жϱ��ʽ��ɸѡ�Ľ������������new��������Ŷ���ΪCDvmValue
	CExBaseList m_oListReports;  //������ʾ�ı����б�

	QTabWidget *m_tabRpts;
	CSttGbRptGrid_Dataset *m_pGridDataset; //��������-���ݼ���
	CSttGbRptGrid_Values *m_pGridValues_All;   //ȫ���������ݣ�
	CSttGbRptGrid_Values *m_pGridValues_RsltExpr;   //����жϱ��ʽ���õ��ı������ݣ�

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
