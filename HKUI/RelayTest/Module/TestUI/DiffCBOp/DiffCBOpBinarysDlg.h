#ifndef DIFFCBOPBINARYSDLG_H
#define DIFFCBOPBINARYSDLG_H

#include <QDialog>
#include "./DiffCBOpCommonParasDlg.h"

namespace Ui {
    class QDiffCBOpBinarysDlg;
}

class QDiffCBOpBinarysDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDiffCBOpBinarysDlg(QWidget *parent = 0);
    ~QDiffCBOpBinarysDlg();

    void GetDatas(CExBaseList *pParas);
    void SetDatas(CExBaseList *pParas);
    void UpdataAllBinarys(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	virtual void InitLanuage();

private slots:
    void on_m_pBtnOk_clicked();
    void on_m_pBtnCancel_clicked();

private:
    Ui::QDiffCBOpBinarysDlg *ui;
    CExBaseList *m_pParas;
    int m_nModify;
    void InitUI();
    void CheckInputSel(int index);

    void CheckForPresence(CExBaseList *pParas,CString strID);
    void SetValueToPage(CSttMacroTestParaData *pData);
    void GetPageToValue(CSttMacroTestParaData *pData);
    void CheckAllPresence(CExBaseList *pParas);
};

#endif // DISTANCEBINARYSDLG_H
