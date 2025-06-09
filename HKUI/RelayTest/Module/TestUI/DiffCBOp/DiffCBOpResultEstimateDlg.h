#ifndef DIFFCBOPRESULTESTIMATEDLG_H
#define DIFFCBOPRESULTESTIMATEDLG_H

#include <QDialog>
#include <QComboBox>
//#include "../SttTestCntrFrameBase.h"
#include "./DiffCBOpCommonParasDlg.h"

namespace Ui {
    class DiffCBOpResultEstimateDlg;
}

class QDiffCBOpResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDiffCBOpResultEstimateDlg(QWidget *parent = 0);
    ~QDiffCBOpResultEstimateDlg();

    Ui::DiffCBOpResultEstimateDlg *ui;
    void GetDatas(CExBaseList *pParas);
    void SetDatas(CExBaseList *pParas);
    void UpdataAllResults(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
    int m_nModify;
public slots:
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();

	void on_m_cmbFluatType_currentIndexChanged(int nIndex);

    void on_m_txtRel3_editingFinished();
    void on_m_txtPlus_3_editingFinished();
    void on_m_txtMinus_3_editingFinished();
	void on_m_EditSetting_editingFinished();
public:
    CExBaseList *m_pParas;
    void InitUI();
    CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
    void SetValueToPage(CSttMacroTestParaData *pData);
    void GetPageToValue(CSttMacroTestParaData *pData);
    void CheckAllPresence(CExBaseList *pParas);
    void CheckForPresence(CExBaseList *pParas,CString strID);
    void UpdataAllResult(CExBaseList *pAllParas);
};

#endif // DIFFRESULTESTIMATEDLG_H
