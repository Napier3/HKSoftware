#ifndef LOWFREQTIMEITEMPARAEDITWIDGET_H
#define LOWFREQTIMEITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroLowFreqParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowFreqTimeItemParaEditWidget;
}

class QLowFreqTimeItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowFreqTimeItemParaEditWidget(QWidget *parent = 0);
	~QLowFreqTimeItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();

private slots:
	
	//动作时间
	void on_m_txtActTime_TSetting_editingFinished();
	void on_m_txtActTime_Cur_editingFinished();
	void on_m_txtActTime_FSetting_editingFinished();
	void on_m_txtActTime_HoldTime_editingFinished();
	void on_m_txtActTime_RelErr_editingFinished();
	void on_m_txtActTime_AbsErrPos_editingFinished();
	void on_m_txtActTime_AbsErrNeg_editingFinished();
	void on_m_txtActTime_FreqEnd_editingFinished();
	void on_m_txtActTime_dfdt_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowFreqTimeItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWFREQTIMEITEMPARAEDITWIDGET_H