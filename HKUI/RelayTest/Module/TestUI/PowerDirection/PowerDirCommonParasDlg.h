#ifndef POWERDIRCOMMONPARASDLG_H
#define POWERDIRCOMMONPARASDLG_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QPowerDirCommonParasDlg;
}

class QPowerDirCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QPowerDirCommonParasDlg(QWidget *parent = 0);
    ~QPowerDirCommonParasDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllCommonParas(CExBaseList *pAllItems);
	void UpdateCurrentCommonParas(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pItem);

private slots:
    void on_m_editPreFaultTime_editingFinished();

    void on_m_editUPre_editingFinished();

    void on_m_editIPre_editingFinished();

    void on_m_editPreAngle_editingFinished();

    void on_m_btnOk_clicked();

    void on_m_btnCancel_clicked();

    void on_m_editPrepareTime_editingFinished();

    void on_m_editAngleMargin_editingFinished();

private:
    Ui::QPowerDirCommonParasDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;
    int m_nInputWidgetWidth;     //20240725 wanmj lineEdit和comboBox固定宽度
	
private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // POWERDIRCOMMONPARASDLG_H
