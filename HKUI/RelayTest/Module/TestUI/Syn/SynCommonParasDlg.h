#ifndef SYNCOMMONPARASDLG_H
#define SYNCOMMONPARASDLG_H

#include <QDialog>

#include "SttMultiMacroSynParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QSynCommonParasDlg;
}

class QSynCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSynCommonParasDlg(QWidget *parent = 0);
    ~QSynCommonParasDlg();

	void SetDatas(CExBaseList *pParas);
	void GetDatas(CExBaseList *pParas);
	void UpdataAllCommonParas(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);

private slots:
    void on_m_lineUs_editingFinished();
    void on_m_lineFs_editingFinished();
    void on_m_lineUg_editingFinished();
    void on_m_cmbUgConnectDef_currentIndexChanged(int index);
    void on_m_cmbVref_currentIndexChanged(int index);
    void on_m_cmbTansConnect_currentIndexChanged(int index);
    void on_m_cmbTansConnect_2_currentIndexChanged(int index);
    void on_m_cmbPointNum_currentIndexChanged(int index);
    void on_m_lineAng_editingFinished();
    void on_m_lineTmax_editingFinished();
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();

private:
    Ui::QSynCommonParasDlg *ui;

	CExBaseList *m_pParas;
    int m_nModify;

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
#endif // SYNCOMMONPARASDLG_H
