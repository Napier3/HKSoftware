#ifndef LOWFREQBINARYSDLG_H
#define LOWFREQBINARYSDLG_H

#include <QDialog>
#include "./LowFreqCommonParasDlg.h"


namespace Ui {
class QLowFreqBinarysDlg;
}

class QLowFreqBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QLowFreqBinarysDlg(QWidget *parent = 0);
    ~QLowFreqBinarysDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	void SetBinBoutName();
private slots:

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QLowFreqBinarysDlg *ui;
	CExBaseList *m_pParas;
	void InitUI();
	void CheckInputSel(int index);
    int m_nModify;
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // LOWFREQBINARYSDLG_H
