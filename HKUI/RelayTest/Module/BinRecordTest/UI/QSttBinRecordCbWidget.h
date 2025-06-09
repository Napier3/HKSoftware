#ifndef QSTTBINRECORDCBWIDGET_H
#define QSTTBINRECORDCBWIDGET_H

#include <QDialog>
#include "ui_QSttBinRecordCbWidget.h"
#include "../../UI/Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../../Module/DataMngr/DataType.h"
#include "../../RecordTest/UI/SttIecRcdFuncInterface.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceMngr.h"
#include "../../RecordTest/UI/SttIecSmvWidget_Harm.h"

class QSttBinRecordCbWidget : public QDialog
{
	Q_OBJECT

public:
	QSttBinRecordCbWidget(QWidget *parent = 0);
	~QSttBinRecordCbWidget();

	CSttIecSmvWidget_Harm *m_pSttIecSmvWidget_Harm;
	CAutoCriticSection m_oFuncCriticSection;
	QScrollComboBox* m_cmbFunc;
	QScrollComboBox* m_cmbCb;
	QScrollComboBox* m_cmbHarmDisplay;//谐波显示
	void InitFuncTypeComboBox();
	void OnCurrFuncChanged(long nIndex);

	CCapDeviceMngr *m_pCapDeviceAll;
	CCapDeviceBase *m_pCurrCapDevice;
	CString m_strIecRcdFuncID;
	CDataType m_oBinRcdFucsDataType;
	CSttIecRcdFuncInterface *m_pSttIecRcdFuncInterface;


	void ExecIecFunc(const CString &strIecfFunc);
	virtual void ExecIecFunc();
	void ExecIecFunc_Create();

	BOOL m_bStopTimerUpdate;
	QTimer m_oTimerBinRcdUpdate;

	void SetCapDevice(CCapDeviceBase *pCapDevice);
	void SetCapDeviceAll(CCapDeviceMngr *pCapDeviceAll);
	void RecordCapDevice(CCapDeviceBase *pCapDevice);
	void RecordCapDevice();
	void BtnBack();//返回按钮功能
	void UpDataShowPrimState();

public slots:
	void slot_CbCurrentIndexChanged(int index);
	void slot_FuncCurrentIndexChanged(int index);
	void slot_CbHarmDisplayIndexChanged(int index);//谐波
	void on_m_btnBack_clicked();
	void slot_Timer_BinRcdUpdate();
	void slot_RBtn_ShowPrim();
private:
	Ui::QSttBinRecordCbWidget ui;
};
extern QSttBinRecordCbWidget *g_pSttBinRecordCbWidget;
#endif // QSTTBINRECORDCBWIDGET_H
