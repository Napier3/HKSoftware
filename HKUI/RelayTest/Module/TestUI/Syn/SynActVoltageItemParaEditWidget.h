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
 //   CExBaseList *GetMacroTestParaDatas_Inner();//zhouhj 2024.9.4 �������
	void DelMacroTestParaDatas();

private slots:

	//��ѹ�߽�ֵ
	void on_m_lineVzd_editingFinished();           //����ѹ��
	void on_m_lineAbsErr_editingFinished();        //�������
	void on_m_lineRelErr_editingFinished();        //������
	void on_m_lineUgStart_editingFinished();       //�������ѹ
	void on_m_lineFgStart_editingFinished();       //������Ƶ��
	void on_m_lineUgMagStep_editingFinished();     //�������ѹ�仯����
	void on_m_lineUt_editingFinished();            //��ѹ����

	//void slot_MultiTab_clicked(int index);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang �������

private:
    Ui::QSynActVoltageItemParaEditWidget *ui;
	void InitLanuage();
	void CheckAllPresence(CExBaseList *pParas);
	void SetValueToPage(CSttMacroTestParaData *pData);
	void UpdatePara(CString strID,CString strValue);

};

#endif // SYNACTVOLTAGEITEMPARAEDITWIDGET_H
