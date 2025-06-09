#ifndef LOWVOLTIMEITEMPARAEDITWIDGET_H
#define LOWVOLTIMEITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowVolAddMultDlg.h"
#include "SttMultiMacroLowVolParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QLowVolTimeItemParaEditWidget;
}

class QLowVolTimeItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QLowVolTimeItemParaEditWidget(QWidget *parent = 0);
	~QLowVolTimeItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类//
	void DelMacroTestParaDatas();
	void USetModeChange(int nUSetMode);
private slots:
	
	//动作时间
	void on_m_txtActTime_TSetting_editingFinished();
	void on_m_txtActTime_Cur_editingFinished();
	void on_m_txtActTime_FSetting_editingFinished();
	void on_m_txtActTime_HoldTime_editingFinished();
	void on_m_txtActTime_RelErr_editingFinished();
	void on_m_txtActTime_AbsErrPos_editingFinished();
	void on_m_txtActTime_AbsErrNeg_editingFinished();
	void on_m_txtActTime_VEnd_editingFinished();
	void on_m_txtActTime_dVdt_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
	Ui::QLowVolTimeItemParaEditWidget *m_pParaUI;
	CExBaseList *m_pTestParaDatas;
	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // LOWVOLTIMEITEMPARAEDITWIDGET_H
