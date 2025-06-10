#ifndef PARASETWIDGET_H
#define PARASETWIDGET_H

#include <QWidget>
//#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "./DistanceAddMultDlg.h"
#include "../Interface/QItemParaEditWidgetBase.h"
namespace Ui {
class QDistanceItemParaEditWidget;
}

class QDistanceItemParaEditWidget : public QItemParaEditWidgetBase

{
    Q_OBJECT

public:
    explicit QDistanceItemParaEditWidget(QWidget *parent = 0);
    ~QDistanceItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
private slots:
    void on_m_cmb_RSC_currentIndexChanged(int index);
    void on_m_cmbK0Mode_currentIndexChanged(int index);
	void on_m_cmb_ErrorType_currentIndexChanged(int index);
	void on_m_cmb_ErrorDirc_currentIndexChanged(int index);
	void on_m_cmb_ErrorNature_currentIndexChanged(int index);

	void on_m_txtZSetting_editingFinished();
	void on_m_txtZAng_editingFinished();
	void on_m_txtRate_editingFinished();
	void on_m_txtKlKr_editingFinished();
	void on_m_txtAngKx_editingFinished();
	void on_m_txtFaultCurrent_editingFinished();
	void on_m_txtTSetting_editingFinished();
	void on_m_txtAbsErr_editingFinished();
	void on_m_txtRelErr_editingFinished();


private:
    Ui::QDistanceItemParaEditWidget *m_pParaUI;

	virtual void InitUI();
	void UpdatePara(CString strID,CString strValue);

	void SetDatas(CExBaseList *pParas);
	void SetValueToPage(CShortData *pData);
	void GetDatas(CExBaseList *pParas);//暂未使用
	void GetPageToValue(CShortData *pData);//暂未使用

	void SetModeText(int nIndex);
};
#endif // PARASETWIDGET_H
