#ifndef COMMONPARASDLG_H
#define COMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameApi.h"

#include "SttMultiMacroDistanceParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include "../../XLangResource_Native.h"
#include <math.h> 


namespace Ui {
class QDistanceCommonParasDlg;
}
class QDistanceCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceCommonParasDlg(QWidget *parent = 0);
    ~QDistanceCommonParasDlg();

	void GetDatas(CExBaseList *pParas);
	void SetDatas(CExBaseList *pParas);
	void UpdataAllCommonParas(CExBaseList *pAllItems);
	BOOL CheckItemsModify(CExBaseList *pAllItems, CExBaseList *pParas);
private slots:
	void on_m_txtPreFaultTime_editingFinished();
	void on_m_txtFaultTime_editingFinished();
	void on_m_txtTimeAfter_editingFinished();
	void on_m_txtILoad_editingFinished();
	void on_m_txtILoadPh_editingFinished();
	void on_m_txtBreakTime_editingFinished();
	void on_m_txtCloseTime_editingFinished();
	void on_m_txtVzPh_editingFinished();
	void on_m_txtMinTime_editingFinished();
	void on_m_cmbBreaker_currentIndexChanged(int index);
	void on_m_cmbVzDefine_currentIndexChanged(int index);
	void on_m_txtLine_editingFinished();

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDistanceCommonParasDlg *ui;
	CExBaseList *m_pParas;
	CSttMacroTest m_oSttMacroTest_Inner;
	int m_nModify;

	void SetValueToPage(CSttMacroTestParaData *pData);
	void GetPageToValue(CSttMacroTestParaData *pData);

	void InitUI();
	virtual void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	bool CheckZSetLineItemModify(CExBaseList *pItem,CExBaseList *pCommonItem);
	CString GetLangStrByFileAddSuffix(CString strID);
	
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
void CheckForPresence(CExBaseList *pParas,CString strID);
void CheckRxValue(CString &strR,CString &strX,CString strZSetting,CString strZAng);
void CheckZSettingAndZAng(CString strR,CString strX,CString &strZSetting,CString &strZAng);

extern bool Stt_Global_IsSetting(QObject *pObject);		//20240805 huangliang 
#endif // COMMONPARASDLG_H
