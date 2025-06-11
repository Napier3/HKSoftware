#ifndef COMMONPARASDLG_H
#define COMMONPARASDLG_H

#include <QDialog>
//#include "../SttTestCntrFrameBase.h"

#include "SttMultiMacroDistanceParasDefine.h"
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QDistanceCommonParasDlg;
}
class QDistanceCommonParasDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceCommonParasDlg(QWidget *parent = 0);
    ~QDistanceCommonParasDlg();

	void GetDatas(CDataGroup *pParas);
	void SetDatas(CDataGroup *pParas);
private slots:
	void on_m_txtPreFaultTime_editingFinished();
	void on_m_txtFaultTime_editingFinished();
	void on_m_txtTimeAfter_editingFinished();
	void on_m_txtILoad_editingFinished();
	void on_m_txtILoadPh_editingFinished();
	void on_m_txtBreakTime_editingFinished();
	void on_m_txtCloseTime_editingFinished();
	void on_m_txtVzPh_editingFinished();
	void on_m_cmbBreaker_currentIndexChanged(int index);
	void on_m_cmbVzDefine_currentIndexChanged(int index);

	void on_m_btnOK_clicked();
	void on_m_btnCancel_clicked();
private:
    Ui::QDistanceCommonParasDlg *ui;
	CDataGroup *m_pParas;

	void SetValueToPage(CShortData *pData);
	void GetPageToValue(CShortData *pData);

	void InitUI();
	
};
CString CheckDataMinMax(CString strValue,float nMax,float nMin,int nAfterPoint);
#endif // COMMONPARASDLG_H
