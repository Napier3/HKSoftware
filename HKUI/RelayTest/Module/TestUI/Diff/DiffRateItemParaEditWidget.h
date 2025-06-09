#ifndef DIFFRATEITEMPARAEDITWIDGET_H
#define DIFFRATEITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroDiffParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QDiffRateItemParaEditWidget;
}

class QDiffRateItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QDiffRateItemParaEditWidget(QWidget *parent = 0);
	~QDiffRateItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 移入基类
	void DelMacroTestParaDatas();
	void UpdateId(double dId, double dMaxdId);
	void UpdateMinaxis(int nMinaxis);//0:有名值(A) 1:标幺值(In)
	double GetBeginValText();
	double m_dBeginVal;
	double m_dEndVal;
private slots:

	//差动曲线搜索
	void on_m_cmbRate_FaultType_currentIndexChanged(int index);
	void on_m_txtRate_BeginVal_editingFinished();
	void on_m_txtRate_EndVal_editingFinished();
	void on_m_txtRate_Step_editingFinished();
	void on_m_txtRate_Freq_editingFinished();
	void on_m_txtRate_Ir_editingFinished();
	void on_m_txtRate_FaultTime_editingFinished();
	void on_m_txtRate_AbsErr_editingFinished();
	void on_m_txtRate_RelErr_editingFinished();

signals:
	void sig_UpdateDiffWiringWidget();//更新右侧接线图
	void sig_UpdateId(double dId);//计算差动电流

private:
	Ui::QDiffRateItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);

};
#endif // DIFFRATEITEMPARAEDITWIDGET_H
