#ifndef LOWVOLILOCKITEMPARAEDITWIDGET_H
#define LOWVOLILOCKITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowVolAddMultDlg.h"
#include "SttMultiMacroLowVolParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowVolILockItemParaEditWidget;
}

class QLowVolILockItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowVolILockItemParaEditWidget(QWidget *parent = 0);
	~QLowVolILockItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();
	void USetModeChange(int nUSetMode);
private slots:
	//低电流闭锁值
	void on_m_txtIBlock_IBlockSetting_editingFinished();
	void on_m_txtIBlock_HoldTime_editingFinished();
	void on_m_cmbIBlock_Var_currentIndexChanged(int index);
	void on_m_txtIBlock_RelErr_editingFinished();
	void on_m_txtIBlock_AbsErr_editingFinished();
	void on_m_txtIBlock_IStart_editingFinished();
	void on_m_txtIBlock_IEnd_editingFinished();
	void on_m_txtIBlock_IStep_editingFinished();
	void on_m_txtIBlock_VEnd_editingFinished();
	void on_m_txtIBlock_dVdt_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowVolILockItemParaEditWidget *m_pParaUI;
	CExBaseList *m_pTestParaDatas;
	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWVOLILOCKITEMPARAEDITWIDGET_H
