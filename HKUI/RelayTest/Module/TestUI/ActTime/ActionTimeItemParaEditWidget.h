#ifndef ACTIONTIMEITEMPARAEDITWIDGET_H
#define ACTIONTIMEITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroActionTimeParasDefine.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

namespace Ui {
class QActionTimeItemParaEditWidget;
}

class QActionTimeItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QActionTimeItemParaEditWidget(QWidget *parent = 0);
    ~QActionTimeItemParaEditWidget();
	virtual void InitUI();
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList* GetMacroTestParaDatas();
	CExBaseList* GetInnerMacroTestParaDatas();
	void DelMacroTestParaDatas();

private:
    Ui::QActionTimeItemParaEditWidget *ui;
	CExBaseList *m_pTestParaDatas;
    int m_nInputWidgetWidth;     //20240723 wanmj lineEdit和comboBox固定宽度

private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	void UpdatePara(CString strID,CString strValue);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private slots:
    void on_m_editSettingTime_editingFinished();
    void on_m_editFaultCurrent_editingFinished();   
    void on_m_editPreAngle_editingFinished();   
    void on_m_editPreFre_editingFinished();  
    void on_m_editRelErr_editingFinished(); 
    void on_m_editAbsErr1_editingFinished(); 
    void on_m_editAbsErr2_editingFinished();
    void on_m_cbbFaultType_currentIndexChanged(int index);
    void on_m_cbbFaultVolType_currentIndexChanged(int index);
    void on_m_editFaultVolt_editingFinished();
};

#endif // ACTIONTIMEITEMPARAEDITWIDGET_H
