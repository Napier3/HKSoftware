#ifndef RECLOSEACCITEMPARAEDITWIDGET_H
#define RECLOSEACCITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroRecloseAccParasDefine.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

namespace Ui {
class QRecloseAccItemParaEditWidget;
}

class QRecloseAccItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QRecloseAccItemParaEditWidget(QWidget *parent = 0);
    ~QRecloseAccItemParaEditWidget();
	virtual void InitUI();
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
	CExBaseList* GetMacroTestParaDatas();
	CExBaseList* GetInnerMacroTestParaDatas();
	void DelMacroTestParaDatas();

private:
    Ui::QRecloseAccItemParaEditWidget *ui;
	CExBaseList *m_pTestParaDatas;
    int m_nInputWidgetWidth;     //20240723 wanmj lineEdit和comboBox固定宽度
    double m_dZ;
    double m_dZAng;
    double m_dR;
    double m_dX;

private:
	void SetValueToPage(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	void UpdatePara(CString strID,CString strValue);

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private slots:
	
    void on_m_cbbFaultType_currentIndexChanged(int index);
    void on_m_editZ_editingFinished();
    void on_m_editZAngle_editingFinished();
    void on_m_editISet_editingFinished();
    void on_m_editFre_editingFinished();
    void on_m_cbbK0Mode_currentIndexChanged(int index);
    void on_m_editKlKr_editingFinished();
    void on_m_editAngKx_editingFinished();
    void on_m_editTripTime_editingFinished();
    void on_m_editRecloseTime_editingFinished();
    void on_m_cbbFaultPermanent_currentIndexChanged(int index);
    void on_m_cbbUxMode_currentIndexChanged(int index);
    void on_m_editUxInputFre_editingFinished();
    void on_m_editUxInputMag_editingFinished();
    void on_m_editUxInputAng_editingFinished();
    void on_m_editAbsErr1_editingFinished();
    void on_m_editAbsErr2_editingFinished();
    void on_m_editRelErr_editingFinished();
    void on_m_editR_editingFinished();
    void on_m_editX_editingFinished();
};

#endif // RECLOSEACCITEMPARAEDITWIDGET_H
