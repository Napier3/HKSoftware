#ifndef RECLOSEACCCOMMONPARASDLG_H
#define RECLOSEACCCOMMONPARASDLG_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QRecloseAccCommonParasDlg;
}

class QRecloseAccCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QRecloseAccCommonParasDlg(QWidget *parent = 0);
    ~QRecloseAccCommonParasDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllCommonParas(CExBaseList *pAllItems);
	void UpdateCurrentCommonParas(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pItem);

private slots:
    void on_m_editPreFaultTime_editingFinished();

    void on_m_btnOk_clicked();

    void on_m_btnCancel_clicked();

    void on_m_editFaultTime_editingFinished();

    void on_m_cbbFaultTrigMode_currentIndexChanged(int index);

    void on_m_editILoad_editingFinished();

    void on_m_editILoadPh_editingFinished();

    void on_m_cbbSimulateBreakerDelay_currentIndexChanged(int index);

    void on_m_editBrkBreakTime_editingFinished();

    void on_m_editBrkCloseTime_editingFinished();

    void on_m_editActionTime_editingFinished();

private:
    Ui::QRecloseAccCommonParasDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;
    int m_nInputWidgetWidth;     //20240725 wanmj lineEdit和comboBox固定宽度
	
private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // RECLOSEACCCOMMONPARASDLG_H
