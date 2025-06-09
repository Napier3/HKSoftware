#ifndef LOWVOLDVDTITEMPARAEDITWIDGET_H
#define LOWVOLDVDTITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowVolAddMultDlg.h"
#include "SttMultiMacroLowVolParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowVolDvdtItemParaEditWidget;
}

class QLowVolDvdtItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowVolDvdtItemParaEditWidget(QWidget *parent = 0);
	~QLowVolDvdtItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();
	void USetModeChange(int nUSetMode);

private slots:

	//滑差闭锁值
	void on_m_txtSlipTrip_dfdtSetting_editingFinished();
	void on_m_txtSlipTrip_Cur_editingFinished();
	void on_m_txtSlipTrip_HoldTime_editingFinished();
	void on_m_txtSlipTrip_RelErr_editingFinished();
	void on_m_txtSlipTrip_AbsErr_editingFinished();
	void on_m_txtSlipTrip_VEnd_editingFinished();
	void on_m_txtSlipTrip_VStep_editingFinished();
	void on_m_txtSlipTrip_dfdtStart_editingFinished();
	void on_m_txtSlipTrip_dfdtEnd_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowVolDvdtItemParaEditWidget *m_pParaUI;
	CExBaseList *m_pTestParaDatas;
	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWVOLDVDTITEMPARAEDITWIDGET_H
