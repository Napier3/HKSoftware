#ifndef LOWVOLBINARYSDLG_H
#define LOWVOLBINARYSDLG_H

#include <QDialog>
#include "./LowVolCommonParasDlg.h"


namespace Ui {
class QLowVolBinarysDlg;
}

class QLowVolBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QLowVolBinarysDlg(QWidget *parent = 0);
    ~QLowVolBinarysDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	void SetBinBoutName();
private slots:

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QLowVolBinarysDlg *ui;
	CExBaseList *m_pParas;
	void InitUI();
	void CheckInputSel(int index);
    int m_nModify;
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // LOWVOLBINARYSDLG_H
