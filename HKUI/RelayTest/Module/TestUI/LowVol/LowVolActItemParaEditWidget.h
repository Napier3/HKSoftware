#ifndef LOWVOLACTITEMPARAEDITWIDGET_H
#define LOWVOLACTITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowVolAddMultDlg.h"
#include "SttMultiMacroLowVolParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowVolActItemParaEditWidget;
}

class QLowVolActItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowVolActItemParaEditWidget(QWidget *parent = 0);
	~QLowVolActItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();
	void USetModeChange(int nUSetMode);

private slots:
	
	//动作值
	void on_m_txtActValue_ActValue_editingFinished();
	void on_m_txtActValue_Cur_editingFinished();
	void on_m_txtActValue_HoldTime_editingFinished();
	void on_m_txtActValue_RelErr_editingFinished();
	void on_m_txtActValue_AbsErr_editingFinished();		
	void on_m_txtActValue_VStart_editingFinished();		
	void on_m_txtActValue_VEnd_editingFinished();		
	void on_m_txtActValue_VStep_editingFinished();		
	void on_m_txtActValue_dVdt_editingFinished();
	void slot_m_cmbActValue_Var_currentTextChanged(const QString &strText);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowVolActItemParaEditWidget *m_pParaUI;
	CExBaseList *m_pTestParaDatas;
	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	int m_nFaultType;
	void UpdateFaultTypeCmb();
};
#endif // LOWVOLACTITEMPARAEDITWIDGET_H