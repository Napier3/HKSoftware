#ifndef CURRINVERPARASETWIDGET_H
#define CURRINVERPARASETWIDGET_H

#include <QWidget>
#include "../Distance/DistanceCommonParasDlg.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroCurrInverseTimeParasDefine.h"

namespace Ui {
class QCurrInverTimeItemParaEditWidget;
}

class QCurrInverTimeItemParaEditWidget : public QItemParaEditWidgetBase

{
    Q_OBJECT

public:
    explicit QCurrInverTimeItemParaEditWidget(QWidget *parent = 0);
    ~QCurrInverTimeItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList *GetMacroTestParaDatas();
//	CExBaseList *GetInnerMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类

	virtual void InitUI();
	void initConnections();

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类
	//void sig_UpdateCurrPoint(CSttMacroTest* pSttMacroTest);

private slots:
	void slot_cmb_FaultVolt_Changed(int index);
	void slot_cmb_ErrorType_currentIndexChanged(int index);

	void slot_lne_FaultVolt_editingFinished();
	void slot_lne_Current_editingFinished();
	void slot_lne_Ang_editingFinished();
	void slot_lne_Hz_editingFinished();
	void slot_lne_TSetting_editingFinished();
	void slot_m_txtPlus_editingFinished();
	void slot_m_txtMinus_editingFinished();
	void slot_lne_RelErr_editingFinished();

private:
    Ui::QCurrInverTimeItemParaEditWidget *m_pParaUI;
	void InitLanuage();
};

#endif // CURRINVERPARASETWIDGET_H
