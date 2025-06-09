#ifndef SYNADJVOLITEMPARAEDITWIDGET_H
#define SYNADJVOLITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "SttMultiMacroSynParasDefine.h"

namespace Ui {
class QSynAdjVolItemParaEditWidget;
}

class QSynAdjVolItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QSynAdjVolItemParaEditWidget(QWidget *parent = 0);
    ~QSynAdjVolItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();

private slots:
    void on_m_lineUt_editingFinished();
    void on_m_linePlus_editingFinished();
    void on_m_lineMinus_editingFinished();
    void on_m_lineRelErr_editingFinished();
    void on_m_lineUgStart_editingFinished();
    void on_m_lineFgStart_editingFinished();
    //void on_m_lineUgMagStep_editingFinished();

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
    Ui::QSynAdjVolItemParaEditWidget *ui;
	void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void UpdatePara(CString strID,CString strValue);
};

#endif // SYNADJVOLITEMPARAEDITWIDGET_H
