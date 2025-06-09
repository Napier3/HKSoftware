#ifndef VOLINVERPARASETWIDGET_H
#define VOLINVERPARASETWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroVolInverseTimeParasDefine.h"
#include "../Distance/DistanceCommonParasDlg.h"

namespace Ui {
class QVolInverTimeItemParaEditWidget;
}

class QVolInverTimeItemParaEditWidget : public QItemParaEditWidgetBase

{
    Q_OBJECT

public:
    explicit QVolInverTimeItemParaEditWidget(QWidget *parent = 0);
    ~QVolInverTimeItemParaEditWidget();

	virtual void InitUI();
	void initConnections();
	void UpdatePara(CString strID,CString strValue);

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	//void SetDatas(CExBaseList *pParas);
	void SetValueToPage(CSttMacroTestParaData *pData);
	//void GetDatas(CExBaseList *pParas);//暂未使用
	//void GetPageToValue(CShortData *pData);//暂未使用


	CExBaseList *GetMacroTestParaDatas();
	//CExBaseList *GetInnerMacroTestParaDatas();
//	 CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	//void DelMacroTestParaDatas();

	void CheckAllPresence(CExBaseList *pParas);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private slots:
	void slot_cmb_ErrorType_currentIndexChanged(int index);

	void slot_lne_Volt_editingFinished();
	void slot_lne_FaultCurrent_editingFinished();
	void slot_lne_Ang_editingFinished();
	void slot_lne_Hz_editingFinished();
	void slot_lne_TSetting_editingFinished();
	void slot_m_txtPlus_editingFinished();
	void slot_m_txtMinus_editingFinished();
	void slot_lne_RelErr_editingFinished();

private:
    Ui::QVolInverTimeItemParaEditWidget *m_pParaUI;
	CExBaseList *m_pTestParaDatas;
	void InitLanuage();
};

#endif // VOLINVERPARASETWIDGET_H
