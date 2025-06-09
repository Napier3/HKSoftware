#ifndef ACTIONTIMECOMMONPARASDLG_H
#define ACTIONTIMECOMMONPARASDLG_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QActionTimeCommonParasDlg;
}

class QActionTimeCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QActionTimeCommonParasDlg(QWidget *parent = 0);
    ~QActionTimeCommonParasDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllCommonParas(CExBaseList *pAllItems);
	void UpdateCurrentCommonParas(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pAllItems);

private slots:
    void on_m_editPreFaultTime_editingFinished();

    void on_m_editUPre_editingFinished();

    void on_m_editIPre_editingFinished();

    void on_m_editPreAngle_editingFinished();

    void on_m_editPreFre_editingFinished();

    void on_m_editFaultTime_editingFinished();

    void on_m_btnOk_clicked();

    void on_m_btnCancel_clicked();

private:
    Ui::QActionTimeCommonParasDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;
    int m_nInputWidgetWidth;     //20240725 wanmj lineEdit和comboBox固定宽度
	
private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // ACTIONTIMECOMMONPARASDLG_H
