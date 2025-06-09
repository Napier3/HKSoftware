#ifndef LOWVOLCOMMONPARASDLG_H
#define LOWVOLCOMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"

#include "SttMultiMacroLowVolParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"

namespace Ui {
class QLowVolCommonParasDlg;
}
class QLowVolCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QLowVolCommonParasDlg(QWidget *parent = 0);
    ~QLowVolCommonParasDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllCommonParas(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	int m_nVType; //0:线电压, 1:相电压
private slots:
	void on_m_txt_SteadyTime_editingFinished();
	void on_m_cmb_VBlock_currentIndexChanged(int index);
	void on_m_rBtn_FreqChange_toggled(bool checked);
	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QLowVolCommonParasDlg *ui;
	CExBaseList *m_pParas;
    CSttMacroTest m_oSttMacroTest_Inner;
    int m_nModify;
	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	void CheckAllPresence(CExBaseList *pParas);
	
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
#endif // LOWVOLCOMMONPARASDLG_H
