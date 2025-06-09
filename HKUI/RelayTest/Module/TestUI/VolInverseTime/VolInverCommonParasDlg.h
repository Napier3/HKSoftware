#ifndef QVOLINVERCOMMONPARASDLG_H
#define QVOLINVERCOMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"

#include "SttMultiMacroVolInverseTimeParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include "../../XLangResource_Native.h"

namespace Ui {
class QVolInverseCommonParasDlg;
}
class QVolInverseCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QVolInverseCommonParasDlg(QWidget *parent = 0);
    ~QVolInverseCommonParasDlg();

	void initConnections();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void SetDatas(CDataGroup *pParas);
	void UpdataAllCommonParas(CExBaseList *pParas);
	BOOL CheckItemsModify(CExBaseList *pAllItems);

private slots:
	void slot_cmb_Value_currentIndexChanged(int index);
	void slot_cmb_CTPos_Changed(int index);

	void slot_lne_PreFaultTime_editingFinished();
	void slot_lne_FaultVolt_editingFinished();
	void slot_lne_FaultCurr_editingFinished();
	void slot_lne_Ang_editingFinished();
	void slot_lne_Hz_editingFinished();
	void slot_lne_FaultTime_editingFinished();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();

private:
    Ui::QVolInverseCommonParasDlg *ui;
	CExBaseList *m_pParas;
	int m_nModify;

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	virtual void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	CString GetLangStrByFileAddSuffix(CString strID);
	
};
#endif // QVOLINVERCOMMONPARASDLG_H
