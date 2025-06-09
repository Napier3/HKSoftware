#ifndef LOWFREQDFDTITEMPARAEDITWIDGET_H
#define LOWFREQDFDTITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroLowFreqParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowFreqDfdtItemParaEditWidget;
}

class QLowFreqDfdtItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowFreqDfdtItemParaEditWidget(QWidget *parent = 0);
	~QLowFreqDfdtItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();

private slots:
	

	//滑差闭锁值
	void on_m_txtSlipTrip_dfdtSetting_editingFinished();
	void on_m_txtSlipTrip_Cur_editingFinished();
	void on_m_txtSlipTrip_HoldTime_editingFinished();
	void on_m_txtSlipTrip_RelErr_editingFinished();
	void on_m_txtSlipTrip_AbsErr_editingFinished();
	void on_m_txtSlipTrip_FreqEnd_editingFinished();
	void on_m_txtSlipTrip_dfdtStart_editingFinished();
	void on_m_txtSlipTrip_dfdtEnd_editingFinished();
	void on_m_txtSlipTrip_dfdtStep_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowFreqDfdtItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWFREQDFDTITEMPARAEDITWIDGET_H