#ifndef ACTIONTIMEITEMPARAEDITWIDGET_H
#define ACTIONTIMEITEMPARAEDITWIDGET_H

#include <QWidget>
#include "../Interface/QItemParaEditWidgetBase.h"
#include "SttMultiMacroDistanceSearchParasDefine.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

namespace Ui {
class QDistanceSearchItemParaEditWidget;
}

class QDistanceSearchItemParaEditWidget : public QItemParaEditWidgetBase
{
    Q_OBJECT

public:
    explicit QDistanceSearchItemParaEditWidget(QWidget *parent = 0);
    ~QDistanceSearchItemParaEditWidget();
	virtual void InitUI();
	virtual void UpdateParas(CSttMacroTest *pSttMacroTest);
    void UpdateCharactParas(CSttMacroTest *pSttMacroTest);
	CExBaseList* GetMacroTestParaDatas();
	CExBaseList* GetInnerMacroTestParaDatas();
	void DelMacroTestParaDatas();
    virtual void UpdZoneTypeCmbParas(CSttMacroTestParaData *pData,int nFaultType);

private:
    Ui::QDistanceSearchItemParaEditWidget *ui;
	CExBaseList *m_pTestParaDatas;
    int m_nInputWidgetWidth;     //20240723 wanmj lineEdit和comboBox固定宽度

    double m_dBegZ;
    double m_dBegZAng;
    double m_dEndZ;
    double m_dEndZAng;
    int m_nFaultType;
    int m_nZoneType;

private:
	void SetValueToPage(CSttMacroTestParaData *pData);
    void SetValueToPageFromCharact(CSttMacroTestParaData *pData);
	void CheckAllPresence(CExBaseList *pParas);
	void UpdatePara(CString strID,CString strValue);
    void ConnectAll_SigSlot();
    void DisConnectAll_SigSlot();
    void UpdateValueSetting();  //20241022 更新待测定值

signals:
	//void sig_UpdateCurrSelGridData(CSttMacroTest* pSttMacroTest);	//20240805 huangliang 已入基类

private slots:
    void on_m_cbbFaultType_currentIndexChanged(int index);

    void on_m_editStep_editingFinished();

    void slot_m_cbbZoneType_currentIndexChanged(int index);

    void on_m_editFaultIf_editingFinished();

    void on_m_editBeginVal_editingFinished();

    void on_m_editFaultVf_editingFinished();

    void on_m_editBeginValAng_editingFinished();

    void on_m_editTSetting_editingFinished();

    void on_m_editEndVal_editingFinished();

    void on_m_editAbsErr_editingFinished();

    void on_m_editEndValAng_editingFinished();

    void on_m_editRelErr_editingFinished();
};

#endif // ACTIONTIMEITEMPARAEDITWIDGET_H
