#ifndef DIFFBINARYSDLG_H
#define DIFFBINARYSDLG_H

#include <QDialog>
#include "./DiffCommonParasDlg.h"


namespace Ui {
class QDiffBinarysDlg;
}

class QDiffBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDiffBinarysDlg(QWidget *parent = 0);
    ~QDiffBinarysDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	void SetBinBoutName();
private slots:

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDiffBinarysDlg *ui;
	CExBaseList *m_pParas;
	void InitUI();
	void CheckInputSel(int index);
    int m_nModify;
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // DIFFBINARYSDLG_H
