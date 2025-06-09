#ifndef DISTANCESEARCHCOMMONPARASDLG_H
#define DISTANCESEARCHCOMMONPARASDLG_H

#include <QDialog>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QDistanceSearchCommonParasDlg;
}

class QDistanceSearchCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceSearchCommonParasDlg(QWidget *parent = 0);
    ~QDistanceSearchCommonParasDlg();
    void InitUI();
	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdateAllCommonParas(CExBaseList *pAllItems);
	void UpdateCurrentCommonParas(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pAllItems);

private slots:
	void on_m_editPreFaultTime_editingFinished();

	void on_m_editTimeAfterTrigger_editingFinished();

	void on_m_editILoad_editingFinished();

	void on_m_editILoadPh_editingFinished();

	void on_m_cbbK0Mode_currentIndexChanged(int index);

	void on_m_editKlKr_editingFinished();

	void on_m_editAngKx_editingFinished();

	void on_m_editZsMag_editingFinished();

	void on_m_editZsAng_editingFinished();

	void on_m_editBrkBreakTime_editingFinished();

	void on_m_editBrkCloseTime_editingFinished();

	void on_m_editFaultAng_editingFinished();

	void on_m_btnOk_clicked();

	void on_m_btnCancel_clicked();

    void on_m_cbbCalcuMode_currentIndexChanged(int index);

    void on_m_cbbSimulateBreakerDelay_currentIndexChanged(int index);

    void on_m_cbbFaultAngMode_currentIndexChanged(int index);

    void on_m_editFaultTime_editingFinished();

    void on_m_editActionTime_editingFinished();

    void on_m_editZl_editingFinished();

    void on_m_editZAng_editingFinished();

private:
    Ui::QDistanceSearchCommonParasDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;
    int m_nInputWidgetWidth;     //20240725 wanmj lineEdit和comboBox固定宽度
	
private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};

#endif // DISTANCESEARCHCOMMONPARASDLG_H
