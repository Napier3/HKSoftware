#ifndef STTMACROPARAEDITVIEWREMOTECtrl_H
#define STTMACROPARAEDITVIEWREMOTECtrl_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "RemoteCtrlBtnWidget.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"
class QSttMacroParaEditViewRemoteCtrl : public QWidget
{
    Q_OBJECT

public:
	explicit QSttMacroParaEditViewRemoteCtrl(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewRemoteCtrl();

	QBoxLayout* m_pMainLayout;	
	QRemoteCtrlBtnWidget* m_pBtnWidget;
	long m_nRecordIndex;

	QTimer m_oRemoteCtrlTimer;
	long m_nReadCount;//读取的次数

private:
	void InitUI();
//	void SendUpdateParameter();
	void SetManualOtherParasFont();
	void InitGirdData();

public:
	void InitConnect();
	virtual void ShowReport(CDvmValues *pValues);
	void StartTest();//开始测试，连接测试仪
	void UpdateExeResult(QString strID,long nErrorInfor);

	void UpdateEventGrid();
	void UpdateDeviceModelRef();
	void SatrtRemoteCtrlTimer();
	void StopRemoteCtrlTimer();


signals:
	void sig_updataParas();
//	void sig_UpdateExeResult(long nErrorInfor);

protected slots:
	virtual void slot_InterSelectIndexChanged(int nIndex);
	void slot_ChannelSelect_cmb_Changed(int index);
	void slot_ReadCondition_PushButton_Clicked();
	void slot_RemoteCtrlPre_PushButton_Clicked();
	void slot_RemoteCtrlExe_PushButton_Clicked();
	void slot_RemoteCtrlCancel_PushButton_Clicked();

	void slot_updateParas();
	void slot_RemoteCtrlTimer();

//2024-9-10 lijunqing 优化系统程序启动的效率
protected:
	bool m_bHasInitFinished;  //是否已经初始化完成，没有初始化，不能进行操作
	virtual void showEvent(QShowEvent *event);
	void InitMacroParaEditViewRemoteCtr();
};

extern QSttMacroParaEditViewRemoteCtrl* g_pRemoteCtrl;

#endif // STTMACROPARAEDITVIEWREMOTECtrl_H
