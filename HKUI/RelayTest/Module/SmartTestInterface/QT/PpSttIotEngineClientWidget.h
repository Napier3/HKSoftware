#ifndef PpSttIotEngineClientWIDGET_H
#define PpSttIotEngineClientWIDGET_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/API/StringApi.h"

#include "../PpSttIotEngineClientApp.h"
#include "SttPxEngineDvmTreeCtrl.h"
#include "SttPxEngineDsEditGrid.h"

#include "PpSttIotEngineClientAppWnd.h"
#include "../../../../Module/BaseClass/ExBaseCycleArray.h"

//////////////////////////////////////////////////////////////////////////
//QPpSttIotEngineClientWidget
namespace Ui {
class QPpSttIotEngineClientWidget;
}

class QPpSttIotEngineClientWidget : public QDialog, public CExBaseListTreeOptrInterface
{
    Q_OBJECT

public:
    explicit QPpSttIotEngineClientWidget(QWidget *parent = 0);
    virtual ~QPpSttIotEngineClientWidget();

    CPpSttIotDeviceClient *m_pPpDeviceClient;
	QSttPxEngineDvmTreeCtrl *m_pDvmTreeCtrl;
	CSttPxEngineDsEditGrid *m_pDatasetGrid;
	CExBaseObject *m_pCurrSelDvmDataObj;
	CDvmDataset *m_pCurrWriteDataset;

	QList<CSttParas*>  m_lstSttParas;
	BOOL			   m_bIsStarPkgMonitor;

	CDvmDevice *m_pDvmDevice;
	BOOL m_bDeviceCreateNew;
	BOOL m_bDeviceNeedCheckEnas; //是否需要校验远方压板
	BOOL m_bCloseDeviceWhenRelease;  //析构时，断开连接。不需要添加到m_oArrDelete进行释放。析构中会释放m_pPpDeviceClient

//////////////////////////////////////////////////////////////////////////
//CExBaseListTreeOptrInterface
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);

public://CWnd
	virtual void NewPpSttIotDeviceClient(CPpSttCommConfig *pCommConfig, CDvmDevice *pDvmDevice);
    virtual void OnCommCommandMsg(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam,LPARAM lParam);
    virtual void OnEngineSystemMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam);
	virtual void OnEngineEventMessage(CPpSttIotDeviceClient *pIotDevice, WPARAM wParam, LPARAM lParam);

    virtual void SaveDatasToLocalDvm(CPpSttIotDeviceClient *pIoTDevice);
    void SaveDatasToLocalDvm(CDvmDataset *pDataset);

	void ShowDvmDevice(CDvmDevice *pDevice);
	void UpdateShowDvmDataset(CDvmDataset *pRptDataset);
	void UpdateShowDvmDataset(const CString &strDsPath);
	void InitCommConfig(CPpSttCommConfig *pCommConfig);
    void DeleteIotDevice(CPpSttIotDeviceClient *pIotDevice);
	void ReadEnasAfterConnectDevice();  //连接设备成功后，自动读压板
	void ReadEnas_Ena(CStringArray *pEnaArray, const CString &strDsKey);
	void WaitForRunProcedureFinish();  //等待通讯命令执行结束
	void CheckRemoteEnas(CExBaseList *pDvmDatasets, CStringArray *pArray);
	void CloseDevice_WhenRelease();

	BOOL IsConnectSuccessful();//zhouhj 2024.1.6

    void AddOutputLog(QWidget*pOutputLog);
	void DvmEnumFinish(CPpSttIotDeviceClient *pIotDevice);
	void ShowSoeReport(CPpSttIotDeviceClient *pIotDevice);
	BOOL GetSoeReprt(CExBaseList *pList);//zhouhj2024.3.16 获取当前的Soe报告数据
	void ShowPkgSpy(CPpSttIotDeviceClient *pIotDevice);//zhouhj 2024.1.23

	//zhouhj 2024.1.17 读取遥测数据集
	void ReadAin(const CString &strDatasetPath);
	void ReadSoe(const CString &strDatasetPath);//zhouhj 2024.3.15 读取SOE,用于遥控测试功能模块
	BOOL WiriteEna_Sel(CDvmData *pData,const CString &strDatasetPath);//遥控选择
	BOOL WiriteEna_Oper(CDvmData *pData,const CString &strDatasetPath);//遥控执行
	BOOL WiriteEna_Revoke(CDvmData *pData,const CString &strDatasetPath);//遥控撤销
	BOOL Initialize_Cmd();//zhouhj 2024.2.22 传统规约平台使用的总的初始化命令,初始化完成后,才能读取到SOE

	BOOL ConnectDevice();//zhouhj 2024.1.4 增加用于单独连接服务端,测试是否连接成功
	BOOL IsRunProcedureFinished();
protected:
	virtual void EnableBtns();
	virtual void EnableBtns_Connecting_Closeing();  //正在连接、断开时，所有按钮不可点
	void SetPpIotEngineClientLang();

    int m_nTimerID;
    CExBaseCycleArray m_oArrDelete;
    virtual void timerEvent( QTimerEvent *event);

signals:
    void sig_OnCommCommandMsg(int wParam,int lParam);
    void sig_OnEngineSystemMessage(int wParam, int lParam);
	void sig_OnEngineEventMessage(int wParam, int lParam);
	void sig_OnConfigDevice(CDataGroup *pCommCfg);

private slots:
    //void slot_OnCommCommandMsg(int wParam,int lParam);
    //void slot_OnEngineSystemMessage(int wParam, int lParam);

    void on_m_btnConfigDevice_clicked();
    void on_m_btnCloseDevice_clicked();
    void on_m_btnConnectDevice_clicked();
    void on_m_btnReset_clicked();
    void on_m_btnEnumDevice_clicked();
    void on_m_btnEnumLDevice_clicked();
    void on_m_btnEnumDataset_clicked();
    void on_m_btnReadDataset_clicked();
    void on_m_btnWriteDataset_clicked();
    void on_m_btnReadZone_clicked();
    void on_m_btnWriteZone_clicked();
    void on_m_btnStartRpt_clicked();
    void on_m_btnStopReport_clicked();
    void on_m_btnOpenDvmFile_clicked();
    void on_m_btnSaveDvmFile_clicked();
    void on_m_btnAddDevice_clicked();

protected:
    Ui::QPpSttIotEngineClientWidget *ui;
};

QPpSttIotEngineClientWidget* CreateEngineClientWidget();
void ReleaseEngineClientWidget();

#endif // PpSttIotEngineClientWIDGET_H
