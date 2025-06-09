#ifndef QSTTTESTCNTRFRAMEBASE_H
#define QSTTTESTCNTRFRAMEBASE_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "Webkit/SttMacroParaEditViewHtml.h"
#include "Webkit/SttReportViewHtml.h"
#include "Interface/SttMacroParaEditViewMngr.h"


#include "Config/Frame/SttFrameConfig.h"
#include "Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "Controls/SttGuideBookTreeCtrl.h"
#include "Controls/SttPanelBase.h"
#include "Controls/SttMenuWidget.h"
#include "Controls/SttAddMacroWidget.h"
#include "Controls/SttGuideBookTreeWidget.h"
#include "Controls/SttOutPutWidget.h"
#include "Controls/SttLanguageCfgDialog.h"
#include "Controls/SttReportHeadSetDlg.h"

//#include "Module/StateMonitor/QStateMonitorWidgetImp.h"
#include "Module/infoWidget/infowidget.h"
#include "Module/VectorWidget/vectorwidget.h"
#include "Module/PowerWidget/QPowerDiagramWidgetImp.h"
#include "Module/LuminousPower/LuminousPowerDlg.h"

//#include "Module/CharLibWidget/CharLibWidget.h"

//2022-12-02 修改功能ID，导致所有的都要编译，效率低下，所以从头文件中去掉，在任何需要包含的地方进行包含
//#include "SttTestCntrCmdDefine.h" 
#include "../SttTestCtrl/SttTestCtrlCntrBase.h"
#include "../SttTestCtrl/SttTestAppBase.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"

#ifdef use_CSmartCapCtrl
#include "../RecordTest/UI/SttIecRecordMainWidget.h"
#endif  //use_CSmartCapCtrl

//#include "Module/CharLibWidget/CharLibWidget.h"   //2022-9-3  lijunqing  
#include "Module/CharLibWidget/CharEditMainWidget.h"
#include "../LiveUpdate/UpdateConfig/VerUpdateCfgMngr.h"
#include "../SttSocket/TestTerminal/SttClientSocketBase.h"
#include "../../../Module/MemBuffer/TxRingPtrBuffer.h"
#include "../SttSocket/Multicast/SttMulticastClientSocket.h"
#include "../SttTestAppConfig/SttTestAppCfg.h"
#include "../../../AutoTest/Module/Characteristic/QT/SttCharacterDrawPng.h"
#include "Module/ChRsMap/QChMapsDlg.h"
#include "IEC61850Config/SttIecConfigDialog.h"
#include "Module/DCOutput/QAuxDCOutputDlg.h"
#include "../../../Module/TestMacro/TestMacros.h"

#include "../SttCmd/GuideBook/SttContents.h"

//2022-12-02  lijunqing  
#include "../Assist/SttAssistGlobalApi.h"
#include "Module/CharLibWidget/QCharactWidgetForTest.h"
#include "Module/CharLibWidget/QCharTestPointsGrid.h"
#include "Controls/SafetyMsgCfg/SttSafetyMsgCfgs.h"
/*lijunqing 2024-7-13*/ //#include "RemoteCtrl/SttMacroParaEditViewRemoteCtrl.h"
#include "../SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"
#include "Module/CommConfigurationDlg/PkgMonitor/QSttCommCfgPkgMonitorWidget.h"

#include "../TestUI/Module/DeviceModelUI_Eng/QDeviceModelDlg_Eng.h"
#include "./Module/CharLibWidget/ZTViewWidget.h"
class QSttTestCntrFrameBase : public QMainWindow, public CLogBase, CSttTestCtrlCntrMsgInterface,
	public CSttWndAssistInterface  //2022-12-02 lijunqing 测试助手相关的接口
{
    Q_OBJECT

public:
    explicit QSttTestCntrFrameBase(QWidget *parent);
    virtual ~QSttTestCntrFrameBase();

//CSttWndAssistInterface
public:
	//查找窗口，保留用 找到返回窗口,      否则返回NULL
	//具体对象必须重载此函数，因为如果直接返回窗口指针，然后强制转换为CSttWndAssistInterface，会出错
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//功能执行接口
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

public:
	//2022-3-23  提取的公共框架函数，在Win、LINUX独立实现
	virtual void InitFrame(const CString &strFrameCfgFile);

	virtual void InitUI(); 
	virtual void InitIcon();
	virtual void InitIcon(const CString& strItemID, const QIcon& icon);
	virtual void InitIcon(const CString& strItemID, const CString& strIcon);
	virtual void InitPinyinLib();
	virtual void CalRectArea();
	virtual BOOL GetDatas();
	virtual void PromptToSave(CExBaseObject *pSelObj, BOOL bIsItemSame = FALSE);
	virtual BOOL IsUiParasChanged(BOOL &bChanged, CDataGroup *pParas);

	//2022-10-16  lijunqing 记录和保存当前页面设置的值：设置为默认值
	virtual void SaveUIParaFile(CDataGroup *pParas);
public:
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);
	virtual long OnUpdateException();//20220914 zhouhj 更新异常信息
	virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestFinished();
	virtual long OnTestStarted();
	virtual long OnTestStoped();
	virtual long OnTestCreated();
	virtual void OnReport(CExBaseObject *pItem) ;
	virtual void OnReport_ReadDevice(CDataGroup *pDeviceGroup);
	virtual void OnAtsGenerate();
	virtual void OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent=FALSE,BOOL bIsInternationalMode = FALSE);
	virtual void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	virtual void OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList);
	virtual void OnAtsQueryItem(CExBaseObject *pItemPara);  //2022-9-13  lijunqing
	virtual void OnInputData(CSttParas *pParas,CExBaseList *pMsgs);  //SHAOLEI  2023-7-21
	virtual void OnTestDisconnected(); //shaolei 2023-9-19 断链

	virtual void FillReport(CExBaseObject *pItem);
	virtual void FillReport();

	//更新Qt原生报告的接口函数
    virtual void AddUpdateReport_QT(QString strItemsPath, bool bReportHead = false); //ftt
    virtual void DeleteReport_QT(QString strItemsPath); //ftt
    virtual void ClearAllReports_QT(); //ftt 2024.10.16

	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void AdjustMacroEditWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI);

	virtual BOOL CanAddTestMacroUI();
	virtual void closeEvent(QCloseEvent *event);

public:
    void InitConfig(const CString &strFrameCfgFile);//初始化配置
    void ReleaseConfig();
	void GetCharacteristicsFile(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CString &strFile);
	void InitCharacteristics(CSttContents *pContents);  //2022-9-4  lijunqing
	BOOL CurrMacroTestUI_IsInternationalMode();

	//zhouhj 传参标识是否为测试项切换的停止,测试项切换时,不需要停止矢量图和功率图
	void OnViewTestStop_Common(BOOL bItemChanged = FALSE);//zhouhj 2023.8.31 中断公共视图部分

	//关联绑定测试控制中心
	void SetTestCtrlCntrBase(CSttTestCtrlCntrBase *pTestCtrlCntrBase);
	CSttTestCtrlCntrBase* GetTestCtrlCntrBase(){return m_pTestCtrlCntrBase;  }   //获取当前框架关联绑定的测试控制中心
	CSttTestMacroUiParas* GetTestMacroUiParas(CSttItems *pRootNodeItems ,BOOL bSetMacroTest = TRUE);

	//单功能的部分，每次只执行一个功能
	virtual void AddMacroTestReport();
	virtual void AddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID);
    virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes=1, long nRptTitle=0, long nTitleLevel=1);
	virtual void OpenMacroTestUI_NoCmd(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes = 1, long nRptTitle = 0, long nTitleLevel = 1);//zhouhj 2024.10.27 无模板生成等通讯命令的接口函数
	//zhouhj 2024.3.9 在俄罗斯Linux系统下调用上述函数软件未知原因崩溃,改为此函数,去除最后一个传参
	virtual void OpenMacroTestUI_Test(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes=1, long nRptTitle=0);
	virtual void OpenMacroTestUI_OnlyCreate(CSttMacroTestUI_TestMacroUI *pTestMacroUI);

	//多功能测试模板编辑模式
	virtual void AddMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID, CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual void OpenMacroTestUI(CSttTestMacroUiParas *pUIParas, CSttMacroTestUI_TestMacroUI *pTestMacroUI,CSttTestMacroCharParas *pSttTestMacroCharParas);
	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI, BOOL bUseExist);
	virtual void DeleteMacroTestReport(const CString &strParentItemsPath, const CString &strItemsID);
	//20230324 zhouhj 参数2为功能ID根据改ID查找对应的网页文件,参数3位父节点对象
	virtual void UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath);
	virtual void SetMacroTest_Original(CExBaseObject *pMacroTest);
	virtual void SelectTestMacro_CmdWzd(const CString &strTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd, const CString &strTestClass, const CString &strDvmFile, long nRepeatTimes, long nRptTitle, long nTitleLevel);

	//2023-03-21 zhouhj 增加切换测试功能接口函数,用于处理特性曲线模块切换时,获取模板中的特性曲线内容,不是直接读本地文件
	virtual BOOL SwitchMacroViewByCurrSel(CSttItems *pCurrSelRootNode);

	virtual void OnDeleteCurr(CExBaseObject *pCurrObj);
	virtual void OnSaveCurr(CExBaseObject *pCurrObj,BOOL IsInternationalMode);

	//2022-9-11  lijunqing
	virtual void ViewCmdEditWidget(CExBaseObject *pSelObj);
	virtual void ViewMacroEditWidget(CExBaseObject *pSelObj);//2022-9-13  lijunqing
	virtual void SaveMacroParasToCurrWzd(CDataGroup *pCommCmd);  //2022-9-12 lijunqing

	virtual BOOL OpenSclFile();
	virtual CString SelIedFromScl();
	//软件资源管理
//	CSttTestResourceBase *m_pSttTestResource;//zhouhj 20220319 放入CSttTestCtrlCntrBase类中

	CSttTestResourceBase* GetSttTestResource();
	void InitTestResource();
	void OnUpdateTestResource(BOOL bCreateChMaps);
//	void initLocalSysPara();

	void InsertReportHead(CDataGroup *pSttReport);//20240508 suyang 新增插入报告头 
	void UpdateReportHead(CDataGroup *pSttReport);
	void UpdateCustomReport();//20220924 更新自定义的报告,即合并单元等测试项目的报告
	void UpdateCharactWidgetForTest(long nPtIndex = 0);//用于更新测试过程中显示的特性图,在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
	void UpdateCharactWidgetForCurTest(long nPtIndex);
	virtual void UpdateRptHtml();
	virtual void GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath);
	void UpdateResultWidget(CSttReport *pReport,const CString &strItemName,const CString &strMacroID);//更新结果显示窗口
	void OpenDialog(const CString &strDialogID);//主界面进入后的对话框ID，打开主界面进入后的对话框界面

	BOOL HasManuTrigerBtn();//zhouhj 20220403 判断当前测试功能是否包含手动触发
	BOOL HasCharacterEditBtn();//gongyiping 20240731 判断当前测试功能是否包含曲线编辑
	BOOL IsManuTriger_HtmlFaultTrigMode();//zhouhj 20220404 根据当前下发参数,判断是否为手动触发模式
	CDataGroup* GetTestMacroUI_Paras(){return m_pTestMacroUI_Paras;}

	BOOL SetValues_dsRcdStep6U6I(BOOL bClearResult);//20220811 zhouhj 将当前测试项中的6U6I的值赋值到数据集中用于比差、角差计算
	BOOL SetValues_dsRcdStep6U6I(CDataGroup *pDataGroup,BOOL bClearResult);//2024-5-17 wuxinyi 零漂网页界面需刷新6U6I的值
	BOOL IsMenuBtn(QWidget *pWidget);
	virtual BOOL IsMenuWidget(QWidget *pWidget);
	virtual void InitSttIecRecord();//初始化录波
	//2023.6.6 zhouhj 
	virtual void InitAfterCreateSttMacroPara();//打开界面参数后,初始化部分个性化处理内容(如合并单元数据处理等)
	//zhouhj 20230606 改为使用InitAfterCreateSttMacroPara函数
//	virtual void InitSttCap_MUTerminal();//合并单元智能终端测试时,初始化IEC探测功能
	virtual void InitAllButtonStateByTestMacroUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI);//根据测试功能初始化工具栏等按钮  zhouhj 20221228
	
	//2024.1.4 zhouhj 
	virtual BOOL CreateEngineClientWidget();
	virtual BOOL CreateCommCfgPkgMnWidget(); //chenling 20240301 创建报文监听界面

	//更新全部测试功能参数,用于国际版模式 zhouhj 2024.6.29
	virtual BOOL Ats_UpdateAllMacroItem_InternationalMode(CSttItemBase *pSttItems);

public://界面
	CSttFrame_Button *m_pStartTestBtn;
	CSttFrame_Button *m_pManualTriggerBtn;
	CSttFrame_Button *m_pCharacterEditBtn;//曲线编辑
	CSttFrame_Button *m_pExitBtn;
	CSttFrame_Button *m_pMenu_FrameButton;//菜单按钮
	CSttFrame_Button *GetStartTestBtn();
	CSttFrame_Button *GetManualTriggerBtn();
	CSttFrame_Button *GetCharactEditBtn();
	CSttFrame_Button *GetExitBtn();
	QWidget* GetCharEditMainWidget(){return m_pCharLibWidget;}

	virtual void UpdateStartStopTestButton(const CString &strState);
	virtual void UpdateCmdButtonsState(const CString &strState);
	//第二个参数设置能否点击，第三个参数设置是否显示
	virtual void UpdateButtonStateByID(const CString &strID,bool bState,bool bShow = true);
	virtual void UpdateCharacterEditButtonState(bool bState, bool bShow,bool bUseCurrMacroUI = false);
	virtual void UpdateEnableState(const CString &strState);
	virtual void SetAddMacroEnable(bool bShow);   //2023-2-26  lijunqing  SetSelectEnable函数名非常不合理，做了修改
	virtual void EndBinStateOnStarting();
	virtual CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
	bool m_bInited;

	virtual void OnCmd_CustomSet(); //自定义设置界面
	virtual void ShowCharEditTab()	{}//从ShowCharLib改为ShowCharEditTab
	virtual void HideCharEditTab()	{}//从HideCharLib改为HideCharEditTab
	virtual void ShowHideCharactUI(BOOL bIsInternationalMode, BOOL bHasCharLibFile);//显示/隐藏特性曲线界面(国际版模式、是否包含特性曲线文件)
	BOOL IsCharactTestMacroUI(const CString &strUIID);//根据当前测试功能ID判断是否为特性曲线功能
	void UpdatePowerDirVectorWidgetDatas(CExBaseList* pParas);  //20240711 wanmj 更新功率方向(国际版)矢量图

public://界面相关变量
    QWidget *m_MainWidget;
	QRect m_rcGbItemsArea; //测试模板项目区域
	QRect m_rcWorkArea; //工作区域
	QRect m_rcPaneArea; //停靠栏区域

    CSttFrameConfig *m_pSttFrameConfig;//框架配置参数管理对象
    CFont m_gFont;

	CCharacteristics *m_pCharacteristics;
	CSttCharacterDrawPng* m_pSttCharacterDrawPng;

    QSttBarBase *m_pStatusBar;//状态栏
	QSttBarBase *m_pResultBarUI;//测试结果显示栏
	QSttResultPanel *m_pResultWidget;//测试结果显示窗口
    QSttGuideBookTreeWidget *m_pSttGbTreeView;//左边的数结构
    QSttOutPutWidget *m_pOutputWidget;
	CSttResults m_oTestMacroResults;//所有测试功能的结果ID,用于将结果显示在结果显示窗口
	CDataGroup  m_oBinaryInParas;//记录全部模块开入选择的参数对应ID
    QSttBarDataBtnsMngr m_oDataBtnsMngr;//Data类型的按钮管理对象，用来更新指示灯、状态灯、电量等
	CSttSafetyMsgCfgs m_oSafetyMsgCfgs;  //配置默认的接线提示信息

	//zhouhj 2024.1.4 从派生类移入
	QPpSttIotEngineClientWidget *m_pEngineClientWidget;

	QTimer m_oTimerAtsAutoSave;
	CAutoCriticSection m_oCriticSection_AutoSave;

	QTimer m_oTimerAtsTest;
	QTimer m_oTimerHtmlViewReturn;
	CAutoCriticSection m_oCriticSection_ItemStateList;//20230220 zhouhj 测试项目列表树更新和模板生成更新
	//BOOL m_bAutoUpdateNameByTestCount;   //根据测试次数，自动更新项目名称

	//向导中的误差设置数据
	CDataGroup m_oErrorValueWzdGroup;

	//zhouhj 2024.5.20
	CDataGroup m_oOldSysParasList;//打开系统参数前,记录原因系统参数数据的链表

	QSttCommCfgPkgMonitorWidget *m_pSttCommCfgPkgWidget;
// 	bool m_bFirstUpadeIPowerMode;//20240516 suyang  第一次进入程序时更新 电流档位为1档 
	enum tagAppState
	{
		APPSTATE_NULL,
		APPSTATE_OPENTEMPLATE
	};//替代接下来可能出现的各种BOOL锁
	tagAppState m_tagAppState;

	virtual void AdjustToolBarButtons();
	virtual void AdjustStatusBarButtons();
	virtual void UpdateButtonsStateByID(const CString &strButtonID, BOOL bEnable);
	virtual void Before_OnCmd();
	virtual void UpdateStartStopButtonByItemCount();
	virtual void UpdateToolButtons_FloatPanel();//更新浮点窗口
	CSttMacroParaEditInterface* GetMacroEditView();
	QCharTestPointsGrid* GetCharTestPointsGrid();
	void ClearItemStateList();
	CInternationalCharactInterface* GetInternationalCharactInterface();
    CInternationalZTInterface* GetInternationalZTViewInterface();
	BOOL AddItem_From_Charact(double dX, double dY);//从特性曲线界面添加测试项
    BOOL AddItem_From_Charact(double dBegX, double dBegY, double dEndX, double dEndY);//从特性曲线界面添加测试项
	BOOL UpdateCurrItem_From_Charact(double dX, double dY);//从特性曲线界面更新测试项参数

protected:
	BOOL MUTestValid();
	//bool m_bSelMacroShow;

	long m_nSelMacroShow;
	//zhouhj 2023.8.22 记录OnItemStateChanged改变时,传递SeachReport对应的ItemID和当前测试点值如果本次与上一次相同,则无需添加,防止重复
	CString m_strItemStateChanged_SearchLineString;

	//zhouhj 2023.11.7 标记是否更新测试报告里当前测试项的开始测试时间
	//在打开模板和打开测试功能、打开测试记录时，都标记为未更新
	BOOL m_bHasUpdateRptStartTestTime;

	BOOL m_bIsRunningStartStopCmd;//zhouhj 2024.4.1 增加用于标记当前是否正在执行开始,停止操作,如果正在执行,则忽略当前操作

protected:
	CSttTestCtrlCntrBase *m_pTestCtrlCntrBase;     //当前框架关联绑定的测试控制中心
	//测试功能参数编辑
	CDataGroup *m_pTestMacroUI_Paras;  //当前测试功能页面的参数
	CExBaseObject *m_pCurrEditMacroItems;   //当前测试功能对应的测试项目或者是测试项目分类
    CSttMacroParaEditInterface* m_pMacroEditView;		//测试功能参数编辑
    QSttMacroParaEditViewHtml* m_pSysParaEditView;  //参数编辑视图  2022-3-18  lijunqing
	//CExBaseObject* m_pItemState;//临时存放多线程传递的ItemState，后替换为循环缓存
	CTxRingPtrBuffer<CExBaseObject> m_oItemStateList;

	//云更新
	CVerUpdateCfgMngr m_oVerUpdateCfgMngr;
	//CSttClientSocketBase m_oVerUpdateSocket;
	CSttMulticastClientSocket* m_pSttMulticastClientSocket;

	//测试报告视图
    QSttReportViewHtml *m_pSttReportViewHtml;
    QWidget *m_pSttReportView; //ftt 2024.9.24

	//矢量图
	QVectorWidget *m_pVectorWidget;
	BOOL HasVectorWidget(const CString &strMacroID);

	//状态图
    //QStateMonitorWidgetImp* m_pStateMonitorWidget;
	BOOL HasStateMonitorWidget(const CString &strMacroID);

	//功率图
	QPowerDiagramWidgetImp* m_pPowerDiagramWidget;
	BOOL HasPowerDiagramWidget(const CString &strMacroID);

	//信息图
	QInfoWidget* m_pInfoWidget;
	BOOL HasInfoWidget(const CString &strMacroID);

	//波形图
	QWidget *m_pWaveDrawWidget;//2024-8-5 wuxinyi 右边区域添加波形窗口-用于window下
	BOOL HasWaveWidget(const CString &strMacroID);
	virtual void SetWaveWidget(QWidget *pWidget){}
	virtual void InitWaveDrawWidget(){}
	
	//接线图
	QWidget *m_pSystemDiagramWidget;
	BOOL HasSystemDiagramWidget(const CString &strMacroID);
	virtual void InitSystemDiagramWidget(){}

	//系统图
	QWidget *m_pWiringDiagramWidget;
	BOOL HasWiringDiagramWidget(const CString &strMacroID);
	virtual void InitWiringDiagramWidget(QWidget* pParent = NULL){}

	//FA参数设置
#ifdef _use_QSttFAParasSetDialog  //lijunqing 2024-7-12
	QSttFAParasSetDialog *m_pSttFaParasSetDialog;
#endif



	//特性曲线图
	//2022-9-3  lijunqing
	QCharEditMainWidget* m_pCharLibWidget;	//QCharLibWidget* m_pCharLibWidget;
	QCharactWidgetForTest *m_pCharactWidgetForTest;//20230310 用于测试过程中显示特性曲线图 zhouhj

	QCharTestPointsGrid *m_pCharTestPointsGrid;//20230316 用于测试过程中显示特性曲线中的全部测试点 zhouhj

	//QCharEditMainWidgetForTest* m_pCharLibWidgetForTest;
    QZTViewWidget *m_pZTViewWidget;//20240729 luozibing
	BOOL HasZTViewWidget(const CString &strMacroID);

	//IEC测试
#ifdef use_CSmartCapCtrl
    QSttIecRecordMainWidget *m_pSttIecRecordMainWidget;
#endif  //use_CSmartCapCtrl
	BOOL m_bHasClosedUI;//20221009 zhouhj 点击关闭按钮时增加标记,此时收到测试停止消息,不再更新界面

    /*lijunqing 2024-7-13*/ //QSttMacroParaEditViewRemoteCtrl *m_pRemoteCtrlWidget; //遥控 zhangyq 2023.12.25
private:
	QIcon m_imgStart;
	QIcon m_imgStop;
	QIcon m_imgTriger;

public:
	//当前活动的窗口
	QWidget *m_pActiveWidget; 
	QWidget *m_pPrevActiveWidget; 

	typedef enum _stt_active_widget_type
	{
		ActiveWidgetType_None=0,  //无
		ActiveWidgetType_MacroUI,  //原生态参数界面  或者 测试功能HTML参数界面
		ActiveWidgetType_MacroUI_Original,  //原生态参数界面
		ActiveWidgetType_MacroUI_Html,  //测试功能HTML参数界面
		ActiveWidgetType_Paras_Html,  //其他参数设置HTML界面
		ActiveWidgetType_Other  //其他界面
	}ActiveWidgetType;
	ActiveWidgetType m_nActiveWidgetType;  //当前活动窗口的类型
	ActiveWidgetType m_nPrevActiveWidgetType;  //上一活动窗口的类型

public:
	QWidget* GetMacroEditWidget();
	CString GetMacroEditViewID();
	BOOL IsHtmlParasEditOpen();
	void SetActiveWidget(QWidget *pWidget, ActiveWidgetType nType=ActiveWidgetType_Other);
	void ReturnPrevActiveWidget();
	CString GetCharLibWidgetID();
	CString GetPngFaultTypeID(CSttMacroTest *pSttMacroTest);
    
	void InitPowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);

#ifdef _use_QSttFAParasSetDialog  //lijunqing 2024-7-12
    void InitFAParasSetDialog(QWidget* pParent = NULL);
#endif
    void UpdatePowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList);
	void UpdatePowerData();
	void StartPowerWidget();
	void StopPowerWidget(bool bUpdate = false);
	void InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);
	void UpdateVectorRange(float fUStart, float fUEnd, float fIStart, float fIEnd);
	void UpdateVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* m_pCurChList);
	void UpdateVectorData();
	void StartVectorWidget();
	void SetVectorGradient(bool bIsGradient);
	void StopVectorWidget(bool bUpdate = false);

	void InitInfoWidget(QWidget* pParent = NULL);
	void ClearInfoWidget();
	void InitIecRecordMain();
	void InitToolBtnFocusPos(const CString &strBtnID);//20230302 zhouhj 初始化工具栏按钮焦点位置
	CXDrawLine* GetCharLibLeftButtonLine();

    void InitZTViewWidget(QWidget* pParent = NULL);

	virtual void InitCharLibWidget(QWidget* pParent = NULL);
	virtual void InitCommCmdWzdMain(CExBaseList *pParentItem);
	virtual void FreeCommCmdWzdMain();

	void OnEventMsg();
	void UpdateEventMsg(CEventResult *pEventInfo);
	void PrintEventInfo();
	void UpdateToolButtons();
	tmt_BinaryConfig* GetBinaryConfig();
	void UpdateToolButtons_ParaEdit();
	void UpdateToolButtons_Bin();
	void UpdateToolButtons_Bout();
	void UpdateToolButtons_Light();
	void SyncBinOutDatas(BOOL b=TRUE);
	void InitBinaryIn_WebUI(CDataGroup *pParas);//zhouhj 网页界面 对开入选择进行初始化

	void TemplateView_Prepare();//打开模板视图时,提前准备,如：差动同步特性曲线界面参数
	void CharDrawView_Prepare();//打开特性曲线视图时,提前准备,如：差动同步模板视图界面参数
	void OnCmd_IecCap_Prepare();//打开报文探测界面前,需要进行的处理,主要处理合并单元测试当前设定值数据的同步
	//zhouhj 2023.10.16 通过当前测试项的参数,更新公共参数
	void InitCommonParasByDatas(CDataGroup *pDataGroup_Paras);

	bool IsTestStarted();
	bool IsStateTest();
	bool IsMultiTestItems();//判断当前测试项是否为多测试项
	bool HasCharChanged();//判断特性曲线是否改变
	void AddTestPoints(double dX, double dY,BOOL bAct);
	void SetCharChanged(bool bCharChanged);
	void UpdateCharScriptByUIParas(CDataGroup *pCurrentUIParas);//根据界面参数更新特性曲线中的脚本计算内容  20221022 zhouhj
	virtual bool GenerateTemplate(CExBaseObject *pParentItems, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1);  //2022-3-27  lijunqing 修改为虚函数，Win版本和LINUX版本处理模式不一致

	virtual bool GenerateTemplate_International(CExBaseObject *pParentItems,const CString &strMacroID, const CString &strItemsName, 
		const CString &strItemsID, BOOL bHasCharacter, long nRepeatTimes = 1
		, long nRptTitle=0, long nTitleLevel=1); 
	virtual bool SendSetItemState(CSttItemBase *pItemBase);//更新测试项选中状态

	virtual void InitStateMonitor(bool bIsEx = false, QWidget* pParent = NULL);
	virtual void InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget = NULL);
	virtual bool PrepStartTest();//zhouhj 20221027 开始测试前的准备工作
	void StartStateMonitor();
	void StopStateMonitor();
	void CloseMenu();

	void SysStateReport_OnSwitchChanged(CEventResult *pEventInfo);
	void SysStateReport_OnStateChanged(CEventResult *pEventInfo);

	bool IsTestAppConnect();
	virtual void Ats_UpdateParameter();
	virtual void OpenMenuHtmlFile(const CString &strMemuFileName);//打开网页菜单

	virtual void Cmd_SendChMapsConfig();//zhouhj 20220316 增加用于发送通道映射文件命令
	virtual void Cmd_SendSystemConfig();//zhouhj 20220316 增加用于发送系统参数命令命令

	void UpdateSysConfig();//zhouhj 20220409 系统参数修改后,发送此信号,更新界面显示,更新相关参数,即发送命令给MainCore
	void UpdatePowerGear();//zhouhj 20220409 功率档位修改后,发送此信号,更新相关参数,即发送命令给MainCore
	virtual void New_SysConfig();
	void EnableStartStopButton(BOOL bEanble);
	void EnableManualTriggerButton(BOOL bEanble);
	BOOL OpenTemplate(CString strFilePath, const CString &strDvmFile);
	BOOL OpenDscXmlFile(CString strFilePath);
	BOOL OpenGbXmlFile(CString strFilePath);
	BOOL AfterOpenDscXmlFile(CString strFilePath); //打开dscxml后，初始化页面
	BOOL OpenTest(CString strFilePath, const CString &strDvmFile);
	BOOL FillRptTitle(CExBaseObject *pCurrSelGbItem);//2023.7.25 修改报告中当前items的标题

	void SaveMacroTestUI_ParaFile(const CString &strNameAdd);
	CEventResult* GetCurEventResult();

	QSttReportViewHtml* GetReportViewHtml(){ return m_pSttReportViewHtml; }
public:
    virtual void LogString(long nLevel, const CString &strMsg);
    virtual void LogString(long nLevel, const char *strMsg);

	virtual void LogStringResult(long nLevel, const CString &strMsg);//zhouhj 20220417 打印测试结果
	void ClearAll_ResultUI();
	void CloseIecCapDetect();//20220629 zhouhj 关闭测试功能界面时,如果底层还处于探测模式,关闭探测通道
	void SendMenuButtonClick(QString strFuncID);

	CString FindNameFromTestMacros(CTestMacros* pTestMacros, CString strMacroID, CString strID);
	void SetErrorValueFromWzd(CDataGroup* pDataGroup);

	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults);//20231109 suyang add 

	virtual void InitRemoteCtrlTest(bool bActiveRemoteCtrl, bool bStart,bool bShowMenuBtns = true);//2023-12-25  zhangyq
	void InitRemoteCtrl();
	void UpdateDeviceModelRef();//更新设备数据模型关联信息 zhouhj 2024.3.18
	virtual void keyPressEvent(QKeyEvent *event);
	bool keyPressEvent_Exec(int nKeyValue);      //20240510 xueyangfan  开始测试 手动触发 停止测试按键响应 
	BOOL CurrCharTestObjectHasChanged();//判断当前测试项特性曲线测试点或测试线数据有没有改变,主要用于国际版软件
	void UpdateSearchReport(const CString &strCurrUI_ID, const CString &strMacroID, CDataGroup *pSearchResults);
	void UpdateCharactResult_I(const CString &strMacroID, const CString &strItemPath, CDvmValues *pSearchResults);//zhouhj 2024.10.24 更新国际版模块特性曲线测试结果

public:
	virtual void OnCmd_Menu();
	virtual void OnCmd_StartTest();
	virtual void OnCmd_TestThis();
	void OnCmd_ManuTriger();
	virtual void OnCmd_StopTest();
	virtual void OnCmd_AddMacro(BOOL bUseNameID);
	void OnCmd_ItemList();
	virtual void OnCmd_TemplateView();
	virtual void OnCmd_ReportView();
	void OnCmd_HardConfig();
	virtual void OnCmd_IECConfig();
	virtual void OnCmd_VectorDrawView();
	virtual void OnCmd_WaveDrawView();
	virtual void OnCmd_StateDrawView();
	virtual void OnCmd_PowerDrawView();
	virtual void OnCmd_CharDrawView();
	virtual void OnCmd_CharactEditView();//特性曲线编辑

	virtual void OnCmd_NewTest();
	virtual void OnCmd_TestedObject();//被测对象,国际版使用
	virtual void OnCmd_OpenTemplate();
	virtual void OnCmd_SaveTemplate();
	virtual void OnCmd_SaveAsTemplate();
	virtual void OnCmd_SaveTest();
	virtual void OnCmd_SaveAsTest();
	virtual void OnCmd_SaveAsRpt();//20230607 zhouhj 单独存储报告
	virtual void OnCmd_ExportWordRpt();  //20230625 shaolei 导出word及XML报告
	virtual void OnCmd_OpenTest();
	virtual void OnCmd_SelSCLFile();
	virtual void OnCmd_SaveEdit();
	virtual void OnCmd_PpIotEngineClient();

	//2023.11.15 lichao PNS331 新增
	virtual void OnCmd_PpIotEngineClientDlg(); //装置通讯对话框
	virtual void OnCmd_CommConfiguration();        //通讯配置
	virtual void OnCmd_PkgMonitor();               //报文监听
	virtual void OnCmd_PpXmlFileMngr();		       //规约模板管理
	virtual void OnCmd_DvmFileMngr();              //点表文件管理
	virtual void OnCmd_RemoteCtrl(); //遥控 zhangyq 2023.12.25
	virtual void OnCmd_PkgMonitorDlg(); //报文监听对话框chenling20240301

	//20240802 huangliang 统一在函数Stt_Global_SettingParent中执行，删除此处代码
////	static void OnCmd_SettingSelect(QWidget *parent = 0);	//20240730 huangliang  弹出定值选择界面
//	virtual void SettingSelect(CExBaseObject *pItem){}
//	virtual void SettingSelect(const CString &sValue){}

	virtual void OnCmd_NetworkConfig();
	virtual void OnCmd_ClearReportRslts();
	virtual void OnCmd_ImportDvmFile();

	//2023/8/31 wjs 遥感试验按钮
	virtual void OnCmd_AinDataMapConfig();
	virtual void OnCmd_SystemParas();
	void OnCmd_GeneralParas();
	//void OnCmd_SwitchSet();
	virtual void OnCmd_DcSet();
	void OnCmd_OutputPower();
	void OnCmd_DeviceCom();
	void OnCmd_LangSettingView();
	void OnCmd_ReportSetting();
	void OnCmd_ChRsMaps();
	void OnCmd_AuxDCOutput();
	void OnCmd_IecCapDialog();
	virtual void OnCmd_TransPcapFile();

	void OnCmd_ItemListView();
	void OnCmd_DeviceComView();
//	virtual void OnCmd_CharaView();
	void OnCmd_SequenceView();
	virtual void OnCmd_InfoView();
	void OnCmd_LogView();
	void OnCmd_VersionInfo();
	virtual void OnCmd_AuxIPSet();
	virtual void OnCmd_Liveupdate();
	virtual void OnCmd_LiveupdateDevice();
	virtual void OnCmd_ULiveupdate();
	void OnCmd_CloudConfig();
	void OnCmd_UpdateAdjCoef();
	void OnCmd_RegisterRemoteTest();
	void OnCmd_RemoteRegistAssist();
	void OnCmd_DownloadTestTemplate();
	void OnCmd_DownloadPpTemplate();
	void OnCmd_UploadingReport();

	void OnCmd_DebugSetDatas();
	void OnCmd_DebugSetDatasFile(long nFileIndex);
	void OnCmd_DebugSetDatasFile1();
	void OnCmd_DebugSetDatasFile2();
	void OnCmd_DebugSaveDatasFile();
	void OnCmd_DebugGetDatas();
	void OnCmd_DebugUpdateReport();
	void OnCmd_DebugFillReport();
	void OnCmd_DebugItemStateChanged();
	virtual void OnCmd_DebugOutPutWidget();
	void OnCmd_DebugStartTest();
	void OnCmd_DebugStopTest();
	void OnCmd_ConnectApp();
	void OnCmd_Debug();
	void OnCmd_DebugSaveTest();
	void OnCmd_DebugGenForDebug();
	void OnCmd_DebugGenTemplate();
	void OnCmd_DebugSaveAsSysFiles();
	virtual void OnCmd_IecCap(); //2022-4-10  lijunqing
	virtual void OnCmd_IecCapWriteFile(); //2022-6-13  lijunqing
	virtual void OnCmd_IecCapDebugHead(); //2022-6-19  lijunqing
	void OnCmd_ScreenShot();//截屏命令
	void OnCmd_Assist();	//2022-12-02  lijunqing
    virtual void OnCmd_ZTView();
        void OnCmd_IecBinRecordDialog();//20240812 zhouyangyong新增开关量录波窗口
	void OnCmd_BinConfigDialog();//20240903 zhouyangyong 新增开关量配置窗口
	virtual void OnCmd_SystemView();
	virtual void OnCmd_WiringView();

#ifdef _use_QSttFAParasSetDialog  //lijunqing 2024-7-12
    void OnCmd_FAParasSetDialog(); //FA参数设置Dialog  xueyangfan 2024-1-23
#endif

	virtual void InitIecCapTest(bool bActiveIecCap, bool bStartDetect,bool bShowMenuBtns = true);//2022-12-27  lijunqing  //参数3为是否显示菜单等按钮,IEC探测时,不需要显示

	void OnCmd_FileMngr();

	void OnCmd_LumPowerView();//光功率chenling20230410

	virtual void OnCmd_OutputDebug(); //输出调试 lcq 2023 8-24
	void OnCmd_Minimize();// 最小化 zhouyangyong 2024-2-26
	void OnUpdateRtCurrModules(CDataGroup *pRtSycTime);  //20240530 xueyangfan 获取实时数据更新电流模块实时值
	void OnUpdateRtInputDev(CDataGroup *pRtSycTime);	//20240530	xueyangfan 获取实时数据更新鼠标键盘

signals:
	void sig_MenuButtonClick(QString);
	void sig_UpdateEnableState(QString);
	void sig_OnViewTestLink(bool b);
	void sig_OnViewTestStart();
	void sig_OnViewTestStop();
	void sig_UpdateToolButtons();
	void sig_OnUpdateGpsTime(CDataGroup *pRtSyncTime);
	void sig_OnUpdateException();
	void sig_UpdateTestResource();
	void sig_CloseMenu();
	void sig_UpdateRptHtml();
	void sig_FillReportImg(QString, QString);
	void sig_MsgBox(QString,QString);//在线程里发送信号进行弹窗提示
//	void sig_LogStringResult(long nLevel,CString strMsg);

	void sig_OnItemStateChanged(CExBaseObject *);
	void sig_ShowItems_TreeView(CExBaseList *);//zhouhj 20220326 更新项目列表改为发送信号方式
	void sig_UpdateHtmlManuTrigerBtn_Testing();
	void sig_UpdateSysConfig();//zhouhj 20220409 系统参数修改后,发送此信号,更新界面显示,更新相关参数,即发送命令给MainCore
	void sig_UpdatePowerGear();//zhouhj 20220409 功率档位修改后,发送此信号,更新相关参数,即发送命令给MainCore
//	void sig_OnItemStateChanged_Frame(CExBaseObject *);   //给FrameBase的测试项目状态改变，也改为信号触发  shaolei 20220411
	void sig_OnInputData(CDataGroup *, CExBaseList *);//接线提示项目执行，形参为CSttParas* pParas, CExBaseList* pMsgs;
	void sig_OnImportDvm(CExBaseList *);  //导入模型后，根据新生成的通讯命令，弹窗逐个配置通讯参数
	void sig_InitImportDvmFile_Widget(CExBaseList *);  //打开配置通讯命令参数的对话框

	void sig_UpdateMultiMacroParaEditView();//更新国际版功能界面表格(在添加系列测试模板生成之后)

    void sig_AddUpdateReportQT(QString strItemsPath, CExBaseObject *pObj); //ftt 2024.10.22
    void sig_DeleteReportQT(QString strItemsPath); //ftt 2024.10.22
    void sig_ClearAllReportsQT(); //ftt 2024.10.16

// 	void sig_UpdateAuxDCEdit();//suyang 20240603 在弹出框中设置直流后更新界面 辅助直流编辑框状态

	//zhouhj 2023.12.27 去除,改为调用虚函数的方式
//	void sig_UpdateEventMsgTime(CEventResult *pEventInfo);//发送信息图显示的数据

	//add wangtao 20241021 更新不同模块的OnSearchPointReport搜索点结果信息 参数1:模块ID 参数2:模块下的单独功能ID 参数3:搜索点结果
//	virtual void sig_UpdateSearchResults(QString, QString, CSttSearchResults*);
	virtual void sig_UpdateDrawCharacters();//add wangtao 20241021 更新特性曲线图
public slots:
	virtual void slot_Timer_AutoSave();
	void slot_Timer();
	void slot_OnViewTestLink(bool b);
	virtual void slot_OnViewTestStart();
	virtual void slot_OnViewTestStop();
	void slot_UpdateToolButtons();
//	void slot_LogStringResult(long nLevel,CString strMsg);

    void slot_MenuButtonClick(QString strID);
	virtual void slot_SelectTestMacro(CSttMacroTestUI_TestMacroUIRef *pTestMacroUIRef, const CString &strItemsName, const CString &strItemsID);
	//线程调用的时候会奔溃，改成信号槽的形式 sf 20220218
	void on_UpdateEnableState(QString strState);
	void slot_OnUpdateRtSyncTime(CDataGroup *pRtSycTime);
	void slot_OnUpdateException();

	virtual void slot_UpdateAuxDCOutput();//zhangyq 20230228 更新辅助直流输出
	virtual void slot_UpdateChRsMaps(BOOL bSysParasHasChanged);
	virtual void slot_ReturnPrevActiveWidget();
	void slot_IecCfgDataMngrUpdate();//zhouhj 20220315 更新IEC数据
	void slot_UpdateTestResource();//更新界面关联的软件资源	
	void slot_UpdateHtmlManuTrigerBtn_Testing();//测试过程中更新手动触发按钮
	void slot_UpdateSysConfig();//zhouhj 20220409 系统参数修改后,发送此信号,更新界面显示,更新相关参数,即发送命令给MainCore
	void slot_UpdatePowerGear();//zhouhj 20220409 功率档位修改后,发送此信号,更新相关参数,即发送命令给MainCore
	virtual void slot_OnItemStateChanged_Frame(CExBaseObject *pItem);
	virtual void slot_OnInputData(CDataGroup *pParas, CExBaseList *pMsgs);
	virtual void slot_OnImportDvm(CExBaseList *pListItems);

	virtual void slot_UpdateMultiMacroParaEditView();

	//zhouhj 2023.10.16 更换更新方案,删除此函数
//	virtual void slot_UpdateMUTimeAccurRlt(CDvmData *pSVDelayData);//20220825 更新时间精度测试结果
	virtual void slot_OnFreeCommCmdWzdWidget();
	virtual void slot_CloseMenu();
	virtual void slot_UpdateRptHtml();
	void slot_UpdateModulesGear(BOOL bMergeCurrHasChanged);//zhouhj 20211016 更新测试仪档位信息
	void slot_FillReportImg(QString strItemPath, QString strFaultID);//zhouhj 2023.8.22
	void slot_MsgBox(QString strTitle,QString strMsg);

	//zhouhj 2023.12.6 从window程序派生类移入
	void slot_OnConfigDevice(CDataGroup *pCommCfg);
	//add wangtao 20241021 更新不同模块的OnSearchPointReport搜索点结果信息 参数1:模块ID 参数2:模块下的单独功能ID 参数3:搜索点结果
//	void slot_UpdateSearchResults(QString, QString, CSttSearchResults*);
public:
	//shaolei 2022-03-19 根据项目ID，更新参数，目前只适用于Iec61850Config、ChMapsConfig、SystemConfig
	void Ats_SetItemPara(const CString &strItemID);
	virtual void Ats_SetItemPara_RsltExpr(CExBaseObject *pItem);
	//zhangmeng 20220728
	void SaveCharacteristicsData(CString strFile = _T(""));
	virtual BOOL IsContinueCreateNew();   //当测试已存在时，是否继续创建测试
	long GetGbItemCount();
	CString GetCurrentUI_ID();
	virtual void InitTestMacroUI_by_DeviceType(CSttMacroTestUI_TestMacroUIMngr *pTestMacroUIMngr);
	CSclStation* GetSclStation();
	virtual void SetDatas(CDataGroup *pParas);
	virtual void ClearReportRslts_Html();//清除HTML报告的数据
	virtual BOOL IsNeedAddAft();//是否需要添加测试后恢复
	virtual void ItemPaste_RootNode(CSttItems *pDestItems, CExBaseObject *pCurrentSel);  //项目粘贴后，处理报告
	virtual void UpdateStatusBar_Btns(const CString &strID, const CString &strValue);  //更新底部状态灯

	//2024-10-21 zhouyangyong 移植
	virtual void OnMacroTest(CSttMacroTestUI_TestMacroUI* pTestMacroUI) = 0;
	//2024-9-10 lijunqing 优化系统程序启动的效率
	public slots:
	void slot_OpenMacroTest(unsigned long nAddrParser);
	void slot_SendGenerateTemplate(unsigned long nAddrParser);

signals:
	void sig_SendGenerateTemplate(unsigned long nAddrParser);
	void sig_OpenMacroTest(unsigned long nAddrParser);

public:
	void emit_OpenMacroTest(unsigned long nAddrParser);
	void emit_SendGenerateTemplate(unsigned long nAddrParser);

	virtual void UpdateStatusBar_BinBinaryBtns(); //20240912 huangliang 更新底部开入开出状态灯
	virtual void UpdateStatusWight_BinBinaryBtns(); //20240912 huangliang 更新非模态对话框的开入开出信息
	virtual void UpdateStatusTable_BinBinaryBtns(); //20240912 huangliang 更新信息图

	void ShowItems_TreeView(CExBaseList *pCurTestItems);//20241016 zhangyq 发送更新项目列表信号
};


extern QSttTestCntrFrameBase *g_theTestCntrFrame;
extern long g_nLogDebugInfor;
extern CFont *g_pSttGlobalFont;  //2022-9-16  lijunqing
extern double g_dUIShowCoef; // 界面显示缩放比例
extern int g_nUpdateMultiMacroParaEditView;//zhouhj 2024.10.9 生成测试模板后,是否更新当前显示界面;国际版模块在添加单个测试功能时,添加完成后，主动更新,在报文解析线程里无需通知外部再更新


extern CDataGroup *g_pGlobalDatas;
BOOL Stt_CalParaExpression(const CString &strExpress, double &dValue, BOOL bLogError, CValues *pValues=NULL);
BOOL Stt_CalParaExp_FindValue(CValues *pValues, const CString &strVarID, CString &strValue);
void  Stt_Global_SettingSelect(QObject *parent, const CString &sFormat, const CString &sName);	//20240815 huangliang 添加参数
void  Stt_Global_SettingParent(QWidget *parent);	//20240802 huangliang 设置定值相关的父级
void  Stt_Global_SettingParent(QWidget *parent, QWidget *pDlgParent);	//20240806 huangliang 适用于在模态对话框中使用结构体地址编辑定值关联
bool  Stt_Global_IsSetting(QObject *pObject);	//20240802 huangliang 判断控件是否为定值

void Stt_Global_NoticeUpdateBinBinary();	//20240912 huangliang 更新通知各界面刷新信息
QString Stt_Global_GetBinBoutNameForIndex(int iBin, int iIndex);	//20240913 huangliang 取出开入开出量名称,iBin为0开入，1扩展开入，2开出，3扩展开出
QString Stt_Global_GetBinBoutNameForIndex_NoUseDefault(int iBin, int iIndex);	//20241011 huangliang 获取映射后的开入开出名称
void Stt_Global_GetBinBoutMaxWidth();	//20241012 huangliang 获取开入开出映射后的最大宽度
void Stt_Global_GetBinBoutMaxWidth(const CString &sSrcValue);	//20241017 huangliang 记录U/I中最大宽度
QString Stt_Global_GetBinBoutNewString(const QString &strValue, bool bLeft, int iAddLen);	//20241012 huangliang 依据最大宽度获取最新字符串，iAddLen为负值时即偏移量

#endif // QSTTTESTCNTRFRAMEBASE_H
