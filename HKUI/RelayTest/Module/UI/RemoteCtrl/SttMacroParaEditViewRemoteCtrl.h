#ifndef STTMACROPARAEDITVIEWREMOTECtrl_H
#define STTMACROPARAEDITVIEWREMOTECtrl_H

#include "../Interface/SttMacroParaEditViewOriginal.h"
#include "../Controls/SttLineEdit.h"
#include "../Module/GooseParaWidget/qgooseparawidget.h"
#include "RemoteCtrlBtnWidget.h"
#include "../Manual/QSttManualBinBoutDlg.h"
#include "../SttTestCntrCmdDefine.h"
#include "../Module/FT3Widget/FT3OutParaWidget.h"

class QSttMacroParaEditViewRemoteCtrl : public QWidget, public CSttMacroParaEditInterface
{
    Q_OBJECT

public:
	explicit QSttMacroParaEditViewRemoteCtrl(QWidget *parent = 0);
	virtual ~QSttMacroParaEditViewRemoteCtrl();

public://CSttMacroParaEditInterface
    virtual void SysConfig(CDataGroup *pSysConfig);
    virtual void SysConfig(CDvmDataset *pSysConfig);
    virtual void SysConfig(const CString &strSysConfig );
    virtual void SetDatas(CDvmDataset *pDataset);
    virtual void SetDatas(CDataGroup *pParas);
    virtual void SetDatas(const CString &strDataset);
    virtual void GetDatas(CDvmDataset *pParas);
    virtual void GetDatas(CDataGroup *pParas);
    virtual void GetDatas(CString& strParas);
    virtual CExBaseList* GetCurrentMacroDatas(){ return NULL;};  //20240716 wanmj 单功能多点的测试功能获取当前测试项的数据

public:
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
	void UpdateExeResult(long nErrorInfor);

	void UpdateEventGrid();
	void UpdateDeviceModelRef();

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
};

extern QSttMacroParaEditViewRemoteCtrl* g_pRemoteCtrl;

#endif // STTMACROPARAEDITVIEWREMOTECtrl_H
