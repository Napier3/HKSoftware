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
	void UpdateMinaxis(int nMinaxis);//0:����ֵ(A) 1:����ֵ(In)
	float m_fHarmCoef;//г���ƶ�ϵ��
private slots:
	
	//г���ƶ�����
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
	void sig_UpdateDiffWiringWidget();//�����Ҳ����ͼ

private:
	Ui::QDiffHarmItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // DIFFHARMTIMEITEMPARAEDITWIDGET_H
