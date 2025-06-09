#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../../Module/UI/SttTestCntrFrameBase.h"

//2023-2-20  lijunqing 通信模块
//#include "../../Module/SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"

class QSttTestCntrFrameLinux : public QSttTestCntrFrameBase
{
    Q_OBJECT

public:
    explicit QSttTestCntrFrameLinux(QWidget *parent = 0);
    virtual ~QSttTestCntrFrameLinux();

public:
	virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestFinished();
	virtual long OnTestStarted();
	virtual long OnTestStoped();
	virtual long OnTestCreated();
	virtual void OnReport(CExBaseObject *pItem) ;
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);


	virtual void FillReport(CExBaseObject *pItem);
	virtual void FillReport();

public://界面相关变量
	QSttBarBase *m_pToolBar;//工具栏
	QSttMenuWidget *m_pMenuWidget;//菜单按钮弹出界面

	virtual void AdjustToolBarButtons();
	virtual void AdjustStatusBarButtons();

	virtual void UpdateButtonsStateByID();
	virtual void Before_OnCmd();

	virtual void InitUI(); 
	virtual void CalRectArea();

	virtual void UpdateButtonStateByID(const CString &strID,bool bState,bool bShow = true);//第二个参数设置能否点击，第三个参数设置是否显示
	virtual void UpdateToolButtons_FloatPanel();//更新浮点窗口
	virtual void UpdateEnableState(const CString &strState);
	virtual void InitSttIecRecord();//初始化录波
	//zhouhj 20230606 改为使用InitAfterCreateSttMacroPara函数
//	virtual void InitSttCap_MUTerminal();//合并单元智能终端测试时,初始化IEC探测功能
	virtual BOOL IsMenuWidget(QWidget *pWidget);
	virtual void UpdateRptHtml();

public:
	virtual void OnCmd_Menu();
	virtual void OnCmd_IecCap(); //2022-4-10  lijunqing
	virtual void OnCmd_IecCapWriteFile(); //2022-6-13  lijunqing
	virtual void OnCmd_IecCapDebugHead(); //2022-6-13  lijunqing
	virtual void InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns = true);//20220526 对从主界面进入IEC测试做初始化
	virtual void OnCmd_Liveupdate();
	virtual void OnCmd_ULiveupdate();
	virtual void OnCmd_AuxIPSet();
	virtual void OnCmd_AddMacro(BOOL bUseNameID=FALSE);
	virtual void OnCmd_StartTest();
	virtual void OnCmd_PpIotEngineClient();
	virtual void OnCmd_NetworkConfig();

	virtual void OnCmd_OpenTest();

	virtual void InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns = true);
	virtual void OnCmd_RemoteCtrl();
	virtual void OnCmd_PpIotEngineClientDlg(); //装置通讯对话框
	//zhouhj 2024.3.17 停止测试后,立刻将测试界面恢复,防止开始、停止按钮无法操作
	virtual void OnCmd_StopTest();
    virtual void OnMacroTest(CSttMacroTestUI_TestMacroUI* pTestMacroUI);

//2023-2-20  lijunqing 通信模块  这个部分其实应该放到QSttTestCntrFrameBase
//但是首先是在Windows版本实现了，所以暂时就不修改基类QSttTestCntrFrameBase
public:
	//zhouhj 2023.1.4 移入基类
//	QPpSttIotEngineClientWidget *m_pEngineClientWidget;
	// zhouhj 2024.2.1 增加返回值,用于标识是否创建对应界面,在创建界面的构造函数中,会进行联机
	virtual BOOL CreateEngineClientWidget();


protected:
	void FillReports(CExBaseList *pItems);
	void FillReport_ForState();
	void FillReport_OnlyHtmlRpt(CExBaseObject *pItem);//只更新html报告内容,不更新原始界面的结果显示,及不打印测试结果

signals:
	
private slots:
	virtual void slot_CloseMenu();

protected:
    virtual void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
