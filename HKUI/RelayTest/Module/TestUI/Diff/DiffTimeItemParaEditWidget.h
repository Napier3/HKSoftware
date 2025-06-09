#ifndef DIFFTIMEILOCKITEMPARAEDITWIDGET_H
#define DIFFTIMEILOCKITEMPARAEDITWIDGET_H

#include <QWidget>
//#include "./LowFreqAddMultDlg.h"
#include "SttMultiMacroDiffParasDefine.h"
#include "../Interface/QItemParaEditWidgetBase.h"
#include "../Distance/DistanceCommonParasDlg.h"
namespace Ui {
	class QDiffTimeItemParaEditWidget;
}

class QDiffTimeItemParaEditWidget : public QItemParaEditWidgetBase

{
	Q_OBJECT

public:
	explicit QDiffTimeItemParaEditWidget(QWidget *parent = 0);
	~QDiffTimeItemParaEditWidget();

	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	virtual void InitUI();
	CExBaseList *GetMacroTestParaDatas();
 //   CExBaseList *GetMacroTestParaDatas_Inner();
	void DelMacroTestParaDatas();
	void UpdateId(double dId);
	void UpdateMinaxis(int nMinaxis);//0:����ֵ(A) 1:����ֵ(In)
private slots:

	//����ʱ��
	void on_m_cmbTime_FaultType_currentIndexChanged(int index);
	void on_m_txtTime_Ir_editingFinished();
	void on_m_txtTime_AbsErrPos_editingFinished();
	void on_m_txtTime_AbsErrNeg_editingFinished();
	void on_m_txtTime_RelErr_editingFinished();
	void on_m_txtTime_Freq_editingFinished();
	void on_m_txtTime_FaultTime_editingFinished();

signals:
	void sig_UpdateDiffWiringWidget();//�����Ҳ����ͼ
	void sig_UpdateId(double dId);//��������
private:
	Ui::QDiffTimeItemParaEditWidget *m_pParaUI;

	void UpdatePara(CString strID,CString strValue);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
};
#endif // DIFFTIMEILOCKITEMPARAEDITWIDGET_H
