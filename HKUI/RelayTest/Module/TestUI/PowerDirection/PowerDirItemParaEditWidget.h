#ifndef POWERDIRITEMPARAEDITWIDGET_H
#define POWERDIRITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroPowerDirParasDefine.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

namespace Ui {
class QPowerDirItemParaEditWidget;
}

class QPowerDirItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QPowerDirItemParaEditWidget(QWidget *parent = 0);
    ~QPowerDirItemParaEditWidget();
	virtual void InitUI();
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList* GetMacroTestParaDatas();
	CExBaseList* GetInnerMacroTestParaDatas();
	void DelMacroTestParaDatas();

private:
    Ui::QPowerDirItemParaEditWidget *ui;
	CExBaseList *m_pTestParaDatas;
    int m_nInputWidgetWidth;     //20240723 wanmj lineEdit和comboBox固定宽度

private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	void UpdatePara(CString strID,CString strValue);
	void SetFaultPhaseComboBox(int index);
	void SetFaultPhaseComboBoxIndex(int index);
	int GetFaultPhaseValue(QString str);

signals:
	void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);
	void sig_UpdateVectorWidget();

private slots:
    void on_m_cbbTestPhase_currentIndexChanged(int index);
    void on_m_cbbFaultPhase_currentIndexChanged(const QString &arg1);
    void on_m_editFaultVol_editingFinished();
    void on_m_editFaultCur_editingFinished();
	void on_m_editFaultTime_editingFinished();
    void on_m_editMTA_editingFinished();
    void on_m_editActionAreaRange_editingFinished();
    void on_m_editStepValue_editingFinished();
    void on_m_editAbsErr_editingFinished();
	void on_m_editRelErr_editingFinished();
};

#endif // POWERDIRITEMPARAEDITWIDGET_H
