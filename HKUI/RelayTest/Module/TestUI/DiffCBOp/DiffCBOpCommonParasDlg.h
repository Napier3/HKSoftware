#ifndef DIFFCBOPCOMMONPARASDLG_H
#define DIFFCBOPCOMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"
#include "SttMultiMacroDiffCBOpParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include <math.h>
//#include "DiffCBOpItemParaEditWidget.h"


namespace Ui {
    class QDiffCBOpCommonParasDlg;
}
class QDiffCBOpCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDiffCBOpCommonParasDlg(QWidget *parent = 0);
    ~QDiffCBOpCommonParasDlg();

    Ui::QDiffCBOpCommonParasDlg *ui;
    void GetDatas(CExBaseList *pParas);
    void SetDatas(CExBaseList *pParas);
    void UpdataAllCommonParas(CExBaseList *pParas);
    BOOL CheckItemsModify(CExBaseList *pAllItems);
	virtual void InitLanuage();
private slots:
    void on_m_pEditPrepareTime_editingFinished();
    void on_m_pEditPreFaultTime_editingFinished();
    void on_m_pEditFaultTimeMargin_editingFinished();
    void on_m_pEditActionHoldTime_editingFinished();
    void on_m_pEditFactor1_editingFinished();
    void on_m_pEditFactor2_editingFinished();
    void on_m_pEditCBTripTime_editingFinished();
    void on_m_pEditCBCloseTime_editingFinished();
	void on_m_pEditFaultTime_editingFinished();
	void on_m_pEditStep_editingFinished();
	void on_m_pEditVg1_editingFinished();
	void on_m_pEditVg2_editingFinished();

    void on_m_pCmbCBSimulation_currentIndexChanged(int nIndex);
	void on_m_pCmbInsel_currentIndexChanged(int nIndex);
	void on_m_pCmbCoordinate_currentIndexChanged(int nIndex);
	void on_m_pCmbAdoptWind_currentIndexChanged(int nIndex);

    void on_m_pBtnOk_clicked();
    void on_m_pBtnCancel_clicked();


public:
    void SetValueToPage(CSttMacroTestParaData *pData);
    void GetPageToValue(CSttMacroTestParaData *pData);
    CExBaseList *m_pParas;
    int m_nModify;
	int m_nCoordinate;
    void InitUI();
    int m_nAdoptWind;
    int m_nConnectMode;	
    void CheckAllPresence(CExBaseList *pParas);

    CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);

    //void CheckRxValue(CString &strR,CString &strX,CString strZSetting,CString strZAng);
    //void CheckZSettingAndZAng(CString strR,CString strX,CString &strZSetting,CString &strZAng);
    void CheckForPresence(CExBaseList *pParas,CString strID);
};

#endif // COMMONPARASDLG_H
