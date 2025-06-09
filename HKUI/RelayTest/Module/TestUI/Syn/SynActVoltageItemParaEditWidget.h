#ifndef SYNACTVOLTAGEITEMPARAEDITWIDGET_H
#define SYNACTVOLTAGEITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
#include "SttMultiMacroSynParasDefine.h"

namespace Ui {
class QSynActVoltageItemParaEditWidget;
}

class QSynActVoltageItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QSynActVoltageItemParaEditWidget(QWidget *parent = 0);
    ~QSynActVoltageItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();

private slots:

	//电压边界值
	void on_m_lineVzd_editingFinished();           //允许压差
	void on_m_lineAbsErr_editingFinished();        //绝对误差
	void on_m_lineRelErr_editingFinished();        //相对误差
	void on_m_lineUgStart_editingFinished();       //待并测电压
	void on_m_lineFgStart_editingFinished();       //待并测频率
	void on_m_lineUgMagStep_editingFinished();     //待并测电压变化步长
	void on_m_lineUt_editingFinished();            //调压周期

	//void slot_MultiTab_clicked(int index);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private:
    Ui::QSynActVoltageItemParaEditWidget *ui;
	void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void UpdatePara(CString strID,CString strValue);

};

#endif // SYNACTVOLTAGEITEMPARAEDITWIDGET_H
