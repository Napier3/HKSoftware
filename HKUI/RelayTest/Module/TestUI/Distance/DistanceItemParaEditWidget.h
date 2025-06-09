#ifndef PARASETWIDGET_H
#define PARASETWIDGET_H

#include <QWidget>
//#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "./DistanceCommonParasDlg.h"
#include "../Interface/QItemParaEditWidgetBase.h"

namespace Ui {
class QDistanceItemParaEditWidget;
}

class QDistanceItemParaEditWidget : public QItemParaEditWidgetBase

{
    Q_OBJECT

public:
    explicit QDistanceItemParaEditWidget(QWidget *parent = 0);
    virtual ~QDistanceItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList *GetMacroTestParaDatas();
	void InitLanuage();
//	CExBaseList *GetMacroTestParaDatas_Inner();
	void SetPageFont(CFont oPageFont);//20240806 luozibing 测试使用
private slots:
    void on_m_cmbK0Mode_currentIndexChanged(int index);
	void on_m_cmb_ErrorType_currentIndexChanged(int index);
	void on_m_cmb_ErrorDirc_currentIndexChanged(int index);
	void on_m_cmb_ErrorNature_currentIndexChanged(int index);
	void slot_ZoneTypeCurrentIndexChanged(int index);

	void on_m_txtZSetting_editingFinished();
	void on_m_txtZAng_editingFinished();
	void on_m_txtR_editingFinished();
	void on_m_txtX_editingFinished();
	void on_m_txtRate_editingFinished();
	void on_m_txtKlKr_editingFinished();
	void on_m_txtAngKx_editingFinished();
	void on_m_txtFaultCurrent_editingFinished();
	void on_m_txtTSetting_editingFinished();
	void on_m_txtPlus_editingFinished();
	void on_m_txtMinus_editingFinished();
	void on_m_txtRelErr_editingFinished();

signals:
//	void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);  //移入基类
private:
    Ui::QDistanceItemParaEditWidget *m_pParaUI;
	virtual void InitUI();
	virtual void ConnectAll_SigSlot();
	virtual void DisConnectAll_SigSlot();
	void UpdatePara(CString strID,CString strValue);
	CString GetParaDataByID(CString strID);

	void SetValueToPage(CSttMacroTestParaData *pData);

	void SetModeText(int nIndex);

	void CheckAllPresence(CExBaseList *pParas);

	void UpdateBtnEnable(BOOL bEnable);
	//根据故障类型设置区段下拉框显示数据 20240911 luozibing
	virtual void UpdZoneTypeCmbParas(CSttMacroTestParaData *pData,int nFaultType);

	void GetZSettingValueFromParas();//根据参数获取最新阻抗定值 20241009luozibing
};

extern bool Stt_Global_IsSetting(QObject *pObject);		//20240805 huangliang 
#endif // PARASETWIDGET_H
