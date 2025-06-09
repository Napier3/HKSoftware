#ifndef LOWFREQACTITEMPARAEDITWIDGET_H
#define LOWFREQACTITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroLowFreqParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowFreqActItemParaEditWidget;
}

class QLowFreqActItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowFreqActItemParaEditWidget(QWidget *parent = 0);
	~QLowFreqActItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();

private slots:
	
	//动作值
	void on_m_txtActValue_ActValue_editingFinished();
	void on_m_txtActValue_Cur_editingFinished();
	void on_m_txtActValue_HoldTime_editingFinished();
	void on_m_txtActValue_RelErr_editingFinished();
	void on_m_txtActValue_AbsErr_editingFinished();		
	void on_m_txtActValue_FreqStart_editingFinished();		
	void on_m_txtActValue_FreqEnd_editingFinished();		
	void on_m_txtActValue_FreqStep_editingFinished();		
	void on_m_txtActValue_dvdt_editingFinished();
	

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowFreqActItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWFREQACTITEMPARAEDITWIDGET_H