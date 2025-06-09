#ifndef CURRINVERCOMMONPARASDLG_H
#define CURRINVERCOMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"

#include "SttMultiMacroCurrInverseTimeParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QCurrInverseCommonParasDlg;
}
class QCurrInverseCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCurrInverseCommonParasDlg(QWidget *parent = 0);
    ~QCurrInverseCommonParasDlg();

	void initConnections();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllCommonParas(CExBaseList *pParas);
    //void UpdateCurrentCommonParas(CExBaseList *pItem);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
private slots:
	void slot_cmb_Value_currentIndexChanged(int index);
	void slot_cmb_CTPos_Changed(int index);

	void slot_lne_PreFaultTime_editingFinished();
	void slot_lne_FaultVolt_editingFinished();
	void slot_lne_FaultCurr_editingFinished();
	void slot_lne_Ang_editingFinished();
	void slot_lne_Hz_editingFinished();
	void slot_lne_In_editingFinished();
	void slot_lne_Ip_editingFinished();
	void slot_lne_FaultTime_editingFinished();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();

private:
    Ui::QCurrInverseCommonParasDlg *ui;
	CExBaseList *m_pParas;
    int m_nModify;

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	virtual void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	CString GetLangStrByFileAddSuffix(CString strID);
	
};
#endif // CURRINVERCOMMONPARASDLG_H
