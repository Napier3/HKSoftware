#ifndef LOWFREQULOCKITEMPARAEDITWIDGET_H
#define LOWFREQULOCKITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroLowFreqParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowFreqULockItemParaEditWidget;
}

class QLowFreqULockItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowFreqULockItemParaEditWidget(QWidget *parent = 0);
	~QLowFreqULockItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();
	void DelMacroTestParaDatas();
	void USetModeChange(int nUSetMode);

private slots:
	
	//低电压闭锁值
	void on_m_txtVBlock_VBlockSetting_editingFinished();
	void on_m_txtVBlock_Cur_editingFinished();
	void on_m_txtVBlock_HoldTime_editingFinished();
	void on_m_cmbVBlock_Var_currentIndexChanged(int index);
	void on_m_txtVBlock_RelErr_editingFinished();
	void on_m_txtVBlock_AbsErr_editingFinished();
	void on_m_txtVBlock_VStart_editingFinished();
	void on_m_txtVBlock_VEnd_editingFinished();
	void on_m_txtVBlock_VStep_editingFinished();
	void on_m_txtVBlock_dfdt_editingFinished();
	void on_m_txtVBlock_FreqEnd_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowFreqULockItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWFREQULOCKITEMPARAEDITWIDGET_H