#ifndef DIFFHARMTIMEITEMPARAEDITWIDGET_H
#define DIFFHARMTIMEITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroDiffParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QDiffHarmItemParaEditWidget;
}

class QDiffHarmItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QDiffHarmItemParaEditWidget(QWidget *parent = 0);
	~QDiffHarmItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
//    CExBaseList *GetMacroTestParaDatas_Inner();
	void DelMacroTestParaDatas();
	void UpdateMinaxis(int nMinaxis);//0:有名值(A) 1:标幺值(In)
	float m_fHarmCoef;//谐波制动系数
private slots:
	
	//谐波制动搜索
	void on_m_cmbHarm_FaultType_currentIndexChanged(int index);
	void on_m_cmbHarm_HarmIndex_currentIndexChanged(int index);
	void on_m_txtHarm_Id_editingFinished();
	void on_m_txtHarm_BeginVal_editingFinished();
	void on_m_txtHarm_EndVal_editingFinished();
	void on_m_txtHarm_Step_editingFinished();
	void on_m_cmbHarm_OutSide_currentIndexChanged(int index);
	void on_m_txtHarm_FaultTime_editingFinished();
	void on_m_txtHarm_AbsErrPos_editingFinished();
	void on_m_txtHarm_AbsErrNeg_editingFinished();
	void on_m_txtHarm_RelErr_editingFinished();
	void on_m_txtHarm_CustomHarmIndex_editingFinished();
	
signals:
	void sig_UpdateDiffWiringWidget();//更新右侧接线图

private:
	Ui::QDiffHarmItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // DIFFHARMTIMEITEMPARAEDITWIDGET_H
