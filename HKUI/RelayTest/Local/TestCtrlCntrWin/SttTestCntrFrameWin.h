#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStatusBar>
#include <QDockWidget>
#include <QVBoxLayout>
#include "../../Module/UI/SttTestCntrFrameBase.h"
#include "../../Module/UI/Controls/SttMenuBar.h"
#include "../../Module/UI/Controls/SttToolBar.h"
#include "../../Module/UI/CommCmdWzd/SttCommCmdWzdMainWidget.h"
#include "../../Module/UI/CommCmdWzd/SttCmdWzdDsEditWidget.h"

//2022-11-15 lijunqing
#include "../../Module/SmartTestInterface/QT/PpSttIotEngineClientWidgetMain.h"
#include "../../Module/UI/SCL/QSttSelSclFileWidget.h"
#include "../../../61850/Module/SCL/SclFileRead.h"
#include "../../Module/UI/ImportDvmFile/SttImportDvmFileWidget.h"
#include "../../Module/ui/Controls/SettingCtrls/SettingInterface.h"
#include "../../Module/ui/Controls/SettingCtrls/settingselectdlg.h"


class QSttTestCntrFrameWin : public QSttTestCntrFrameBase
{
    Q_OBJECT

public:
    explicit QSttTestCntrFrameWin(QWidget *parent = 0);
    virtual ~QSttTestCntrFrameWin();

	virtual void InitFrame(const CString &strFrameCfgFile);
	virtual void slot_UpdateChRsMaps( BOOL bSysParasHasChanged );
	void InitToolButtons_AfterInit();  //程序启动后，初始化菜单、工具栏的按钮状态
	void UpdateToolButtons_AfterNew();  //新建测试后，更新菜单、工具栏的按钮状态
	void UpdateToolButtons_AfterAddMacro();  //选择功能后，更新菜单、工具栏的按钮状态
	void UpdateCmdButtonsState_AddMacro();  //单独刷新“选择功能”按钮的使能状态
	void ReInitViews();
	void EnableMenu(const CString& strID, BOOL bEnable);
	void EnableAction(const CString& strID, BOOL bEnable, BOOL bSelect = FALSE);
	void ShowButtonsByID(const CString& strButtonID, BOOL bShow);
	void SelectActionByID(const CString& strID, BOOL bSelect);
	void SelectActionByName(const CString& strName, BOOL bSelect);
	void AdjustMacroToolWidget(QWidget* pWidget, const CString& strMacroID);
	void AdjustMacroToolWidgetOrder(const CString &strMacroID);//2024-8-8 wuxinyi 调整右侧试图顺序
	void AdjustMacroToolWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	void CharactDatasToTestMacroParas();//20230323 zhouhj 将测试特性曲线界面参数同步到网页界面,在保存参数时调用
	void FFT_CalDebug();//zhouhj 2024.4.25 调试使用
    void ClearResultWidget();   //20240909 wanmj 清空结果栏

	virtual void InitUI(); 
	virtual void InitIcon();
	virtual void InitIcon(const CString& strItemID, const QIcon& icon);

	virtual void PromptToSave(CExBaseObject *pSelObj, BOOL bIsItemSame = FALSE);
	BOOL UpdateChildren(CDataGroup* pSrcObj, CDataGroup* pDesObj);
	void ClearEmptyChildren(CDataGroup* pSrcObj, CDataGroup* pDesObj);
	void SaveTestMacroUIParas(CDataGroup *pParas);
	virtual BOOL IsContinueCreateNew();   //当测试已存在时，是否继续创建测试
	void ClearSmartGenWzd();  //清除向导，以便重新创建测试
	void AddAinDataMapValues(CSttReport *pSttReport);
	void AddAinDataMapValues_ProcessRatios(const CString &strDataMapID, const CString& strSrcValue, CString &strDestValue);  //添加遥测报告时，处理变比
	void AddAinDataMapValues_ProcessRatios_I(const CString& strSrcValue, CString &strDestValue);
	void AddAinDataMapValues_ProcessRatios_U(const CString& strSrcValue, CString &strDestValue);
	void AddAinDataMapValues_ProcessRatios_PQ(const CString& strSrcValue, CString &strDestValue);
	virtual BOOL IsAinDataMapValid();  //当有遥测项目时，遥测参数映射是否有效
	virtual BOOL Warning_AinDataMapInvalid(CSttItemBase *pItem);

	virtual void ShowCharEditTab();//从ShowCharLib改为ShowCharEditTab
	virtual void HideCharEditTab();//从HideCharLib改为HideCharEditTab
	virtual void ShowHideCharactUI(BOOL bIsInternationalMode, BOOL bHasCharLibFile);//显示/隐藏特性曲线界面(国际版模式、是否包含特性曲线文件)

	virtual void closeEvent(QCloseEvent *event);

public:
	int m_nScreenWidth;//屏幕宽度
	int m_nScreenHeight;//屏幕高度

	QWidget *m_wndWorkspace;//整个工作区
	QWidget *m_wndTopTestWnds;//工作区中间的测试区
	QVBoxLayout *m_pVLayout;
	QHBoxLayout* m_pHBoxLayout;

	QSttMenuBar *m_pMenuBar;//菜单
	QSttToolBar *m_pToolBarWin;//工具栏
	QDockWidget *m_wndDockStatusBar; //状态灯承载

	QSplitter *m_pSplitClientVert;//上下分隔：上m_pSplitWorkspace， 下：OutputWnd
	QSplitter *m_pSplitWorkspace;//左右分割 左边树，中间参数，右边图
	QTabWidget *m_tabTestViews;//中间区域
	QTabWidget *m_tabTestTools;//右侧区域
	QTabWidget *m_tabTestOutput;//下方区域
	QSttOutPutWidget *m_pWinResultWidget; //测试结果框
	
	//通讯命令添加向导
	QSttCommCmdWzdMainWidget *m_pSttCommCmdWzdMainWidget;

	//导入模型后，重新配置通讯命令参数
	QSttImportDvmFileWidget *m_pSttImportDvmFileWidget;

	//通信命令编辑  2022-9-11  lijuniqng
	QSttCmdWzdDsEditWidget *m_pCmdWzdDsEditWidget;
	CSttMacroTest *m_pCurrGbWzdMacroTestEdit;  //2022-9-19

	//2022-11-15 lijunqing
	//zhouhj 2024.1.4 移入基类
//	QPpSttIotEngineClientWidget *m_pEngineClientWidget;
	//2022-12-08  shaolei
	QSttSelSclFileWidget *m_pSelSCLWidget;
	CSclFileRead *m_pSclFileRead;
//	BOOL m_bUpdateTabTestViewsSelChanged;//20230318 判断测试功能tab切换时是否更新,用于同步特性曲线图界面参数

//	CExBaseList m_oSttItemsRptTileList;//zhouhj 2023.7.28 在保存编辑或测试项切换时,会重新生成模板,生成模板前记录当前模板各级标题名称,模板生成后,用于更新各级标题

protected:
	//原生态的测试功能，只有一个电气量项目，记录该项目
	//用于获取项目路径，以便响应SetItemPara指令（例如：通用试验的锁与解锁）
	//好像可以不用这个指针，可以用m_pSttGbTreeView->m_pCurrSelRootNode去查找
	CExBaseObject *m_pMacroTest_Original;  
	CSttTestAppCfg m_oStt61850CapTestAppCfg;//2023.5.31 zhouhj IEC探测与底层进行探测报文数据链接的配置

	//用于确定单机模式还是自动测试
	BOOL m_bIsAutoTest;
	BOOL m_bIsViewStoped; //用于判断frame视图是否已经刷新为停止态
	CDataGroup *m_pAinDataMapCfg;  //遥测参数映射，用于记录上一次的配置情况
	CDataGroup *m_pAinRatios;      //遥测参数映射，用于记录变比信息

public:
	virtual void ClearAllAinDataMap();   //导入模型时，会清空所有的映射
	virtual void AdjustToolBarButtons();
	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual CSttMacroParaEditInterface* CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist=TRUE);
	virtual void CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI, BOOL bUseExist);
	virtual void AdjustMacroEditWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI);
	virtual bool GenerateTemplate(CExBaseObject *pParentItems, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes=1
		, long nRptTitle=0, long nTitleLevel=1);  //2022-3-27  lijunqing 修改为虚函数，Win版本和LINUX版本处理模式不一致
	virtual BOOL CanAddTestMacroUI();
	virtual void AddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID);
	virtual void OpenMacroTestUI(CSttTestMacroUiParas *pUIParas, CSttMacroTestUI_TestMacroUI *pTestMacroUI,CSttTestMacroCharParas *pSttTestMacroCharParas);
	virtual void OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, long nRepeatTimes=1, long nRptTitle=0, long nTitleLevel=1);
	virtual void UpdateStartStopTestButton(const CString &strState);
	virtual void UpdateEnableState(const CString &strState);
	virtual void Ats_UpdateParameter();
	virtual void InitSttIecRecord();//初始化录波
//	virtual void InitSttCap_MUTerminal();//合并单元智能终端测试时,初始化IEC探测功能
	virtual void InitAfterCreateSttMacroPara();//打开界面参数后,初始化部分个性化处理内容(如合并单元数据处理等)

//函数功能统一在基类中实现  2023.3.24 zhouhj
//	virtual void UpdateRptHtml(const CString &strItemsID);
//	virtual void UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath);//20230324 zhouhj 参数2为功能ID根据改ID查找对应的网页文件
//	virtual void GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath);
//	CSttTestMacroUiParas* GetTestMacroUiParas(CSttItems *pRootNodeItems ,BOOL bSetMacroTest = TRUE);

	//window下更新报告网页后,同时更新各测试项目的标题  zhouhj 2023.7.27
	virtual void UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath);
	virtual void GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath);

	virtual void SelectTestMacro_CmdWzd(const CString &strTestMacroUI, const CString &strItemsName, const CString &strItemsID
		, CDataGroup *pCommCmd, const CString &strTestClass, const CString &strDvmFile, long nRepeatTimes, long nRptTitle, long nTitleLevel);

	//2023-03-21 zhouhj 增加切换测试功能接口函数,用于处理特性曲线模块切换时,获取模板中的特性曲线内容,不是直接读本地文件
	virtual BOOL SwitchMacroViewByCurrSel(CSttItems *pCurrSelRootNode);

	//2022-9-11  lijunqing
	virtual void ViewCmdEditWidget(CExBaseObject *pSelObj);
	virtual void ViewMacroEditWidget(CExBaseObject *pSelObj);//2022-9-18  lijunqing
	virtual void SaveMacroParasToCurrWzd(CDataGroup *pCommCmd);  //2022-9-12 lijunqing

	//2023-1-28  lijunqing
	virtual BOOL CreateEngineClientWidget();// zhouhj 2024.2.1 增加返回值,用于标识是否创建对应界面,在创建界面的构造函数中,会进行联机

	//显示测试中特性	曲线界面 2023.03.11
	void ShowCharacterTesting(BOOL bShow);
	//2023-2-6 yizejun
	virtual void LogStringResult(long nLevel, const CString &strMsg);
	virtual void OnMacroTest(CSttMacroTestUI_TestMacroUI* pTestMacroUI);
	virtual void OnAutoTest(QStringList strings);
	//第二个参数设置能否点击，第三个参数设置是否显示
	virtual void UpdateButtonStateByID(const CString &strID,bool bState,bool bShow = true);
	virtual void UpdateCharacterEditButtonState(bool bState, bool bShow, bool bUseCurrMacroUI = false);

private:
	//2022-9-18  lijunqing
	void ViewMacroEditWidget_ChMapsConfig(CSttMacroTest *pSttMacroTest);
	void ViewMacroEditWidget_IECConfig(CSttMacroTest *pSttMacroTest);
	void ViewMacroEditWidget_SystemConfig(CSttMacroTest *pSttMacroTest);

	//zhouhj2023.7.27 获取全部标题,更新对应标题
	BOOL GetItemsTitleString(const CString &strItemsPath,char **ppszReport,long &nLen);

public:
	//virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestFinished();
	virtual long OnTestStarted();
	virtual long OnTestStoped();
	virtual long OnItemStateChanged(CExBaseObject *pItem);
	virtual long OnTestCreated();
	virtual void OnReport(CExBaseObject *pItem) ;
	virtual void OnAtsGenerate();
	virtual void OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent=FALSE,BOOL bIsInternationalMode = FALSE);
	virtual void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	virtual void OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList);
	virtual void OnAtsQueryItem(CExBaseObject *pItemPara);  //2022-9-13  lijunqing
	virtual void OnInputData(CSttParas *pParas,CExBaseList *pMsgs);  //SHAOLEI  2023-7-21
	virtual void OnTestDisconnected(); //shaolei 2023-9-19 断链

	virtual void SetMacroTest_Original(CExBaseObject *pMacroTest);
	
	void FillReport(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  CSttReport *pSttReport);
	virtual void FillReport(CExBaseObject *pItem);
	virtual void FillReport();

	virtual void OpenMenuHtmlFile(const CString &strMemuFileName);

	virtual void Cmd_SendChMapsConfig();//zhouhj 20220316 增加用于发送通道映射文件命令
	virtual void Cmd_SendSystemConfig();//zhouhj 20220316 增加用于发送系统参数命令命令

	virtual void InitCommCmdWzdMain(CExBaseList *pParentItem);
	virtual void FreeCommCmdWzdMain();

	virtual void InitStateMonitor(bool bIsEx = false, QWidget* pParent = NULL);
	virtual void InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget = NULL);
	virtual void InitCharLibWidget(QWidget* pParent = NULL);

	CString OpenSclFileDlg(BOOL bIsOpen = TRUE);
	CString OpenDvmFileDlg(const CString &strFileName, BOOL bIsOpen = TRUE);
	CString OpenTemplateDlg(BOOL bIsOpen = TRUE);
	CString OpenTestDlg(BOOL bIsOpen = TRUE);//打开测试记录gbrpt
	CString OpenPpxmlFileDlg(BOOL bIsOpen = TRUE);

	void InitImportDvmFileDlg(CSttItems *pItems);
	void FreeImportDvmFileDlg();
	void OnCmd_IecCap(long nPkgDetectType); //zhouhj 2024.1.10

protected:
	void FillReports(CExBaseList *pItems);
	void OnMenuClickedAction_Test(void* pWidget, const CString strTitle);
	void OnMenuClickedAction_Tools(void* pWidget, const CString strTitle);

public:
	virtual void OnCmd_NewTest();
	virtual void OnCmd_IecCap(); 
	virtual void OnCmd_OpenTemplate();
	virtual void OnCmd_SaveTemplate();
	virtual void OnCmd_SaveAsTemplate();
	virtual void OnCmd_SaveTest();
	virtual void OnCmd_SaveAsTest();
	virtual void OnCmd_SaveAsRpt();//20230607 zhouhj 单独存储报告
	virtual void OnCmd_ExportWordRpt();  //20230625 shaolei 导出word及XML报告
	virtual void OnCmd_OpenTest();
	virtual void OnCmd_AddMacro(BOOL bUseNameID);

	virtual void OnCmd_StartTest();
	virtual void OnCmd_TestThis();	
	virtual void OnCmd_StopTest();

	virtual void OnCmd_IECConfig();
	virtual void OnCmd_ReportView();
	virtual void OnCmd_TemplateView();
	virtual void OnCmd_VectorDrawView();
	virtual void OnCmd_WaveDrawView();
	virtual void OnCmd_StateDrawView();
	virtual void OnCmd_CharDrawView();
	virtual void OnCmd_PowerDrawView();
//	virtual void OnCmd_CharaView();
	virtual void OnCmd_InfoView();
	virtual void OnCmd_Liveupdate();
	virtual void OnCmd_LiveupdateDevice();
	virtual void OnCmd_DebugOutPutWidget();
	virtual void OnCmd_SelSCLFile();
	virtual void OnCmd_SaveEdit();
	virtual void OnCmd_DcSet();
	virtual void OnCmd_PpIotEngineClient();  //用于手动点开通讯后台界面
	virtual void OnCmd_ClearReportRslts();
	virtual void OnCmd_SystemParas();
	virtual void OnCmd_TransPcapFile();
	virtual void OnCmd_ImportDvmFile();
	//2023/8/31 wjs 遥感试验按钮
	virtual void OnCmd_AinDataMapConfig();
	virtual void OnCmd_OutputDebug(); //输出调试 lcq 2023 8-24
     virtual void OnCmd_ZTView();//20240729 luozibing ZT视图
	 virtual void OnCmd_SystemView();//右侧视图系统图
	 virtual void OnCmd_WiringView();//右侧视图接线图

	virtual BOOL OpenSclFile();
	virtual CString SelIedFromScl();

	//新建单独的配置电气量项目
	void OnNew_ChMapsConfig(const CString &strParentItemPath);
	void OnNew_SystemConfig(const CString &strParentItemPath);
	void OnNew_IECConfig(const CString &strParentItemPath);
	virtual void New_SysConfig();
	//新建单独的通讯命令项目
	void OnNew_CommCmd(const CString &strParentItemPath, const CString &strCmdID);

	//2022-9-21  lijunqng
	void SaveTemplate(const CString &strFile,long nSynMode = STT_CMD_Send_Sync);
	void SaveTest(const CString &strFile,long nSynMode = STT_CMD_Send_Sync);
	void ExportWordRpt(const CString &strFile, CDataGroup *pParas);
	void AppendItemsTecFromGuideBook(CDataGroup *pSrcGrp, CDataGroup *pDestGrp);
	void DeleteCmdWzdDsEditWidget();

	virtual void OnDeleteCurr(CExBaseObject *pCurrObj);
	void OnDeleteCurr_CommCmd(CSttCommCmd *pCommCmd);
	void OnDeleteCurr_Items(CSttItems *pItems);
	void OnDeleteCurr_MacroTest(CSttMacroTest *pMacroTest);

	virtual void OnSaveCurr(CExBaseObject *pCurrObj,BOOL IsInternationalMode);
	virtual void Ats_SetItemPara_RsltExpr(CExBaseObject *pItem);

	//更新全部测试功能参数,用于国际版模式 zhouhj 2024.6.29
	virtual BOOL Ats_UpdateAllMacroItem_InternationalMode(CSttItemBase *pSttItems);
	//shaolei 更新系统参数到CSttDevice的m_pSysPara指针
	void UpdataSysParaToDevice(const CString &strSysParas);

	BOOL IsAutoTest();
	void SetAutoTest(BOOL bIsAutoTest);

	void ExpandRootNode();

signals:
	void sig_OnItemStateChanged(CExBaseObject *);
	void sig_New_SysConfig();  //shaolei 20220916 创建系统参数配置的电气量项目
	void sig_ViewMacroEditWidget(CExBaseObject *);
	void sig_UpdateCmdButtons_AddMacro();  //单独刷新“选择功能”的按钮
	void sig_ExpandGuideBookTree();   //展开所有测试项
	void sig_Timer_AutoSave();
	void sig_SettingSelect(CExBaseObject *pItem);//20240703 huangliang
	void sig_SettingSelect(CString sValue);//20240730 huangliang

public slots:
	virtual void keyPressEvent(QKeyEvent *event);
	void slot_Timer_AutoSave_Ex();
	virtual void slot_Timer_AutoSave();
	virtual void slot_OnItemStateChanged_Frame(CExBaseObject *pItem);
	virtual void slot_OnFreeCommCmdWzdWidget();
	virtual void slot_OnFreeImportDvmFileWidget();
	virtual void slot_OnViewTestStop();
	virtual void slot_OnViewTestStart();
	void OnCloseTabTestViews(const int& index);
	void slot_currentChangedTabWidget(int nCurrIndex);
	void OnCloseTabTestTools(const int& index);
	void slot_IecCfg_New();   //shaolei 新建单个IEC61850Config的电气量项目
	void slot_New_SysConfig();  //shaolei 20220916 创建系统参数配置项目
	void slot_Edit_SysConfig();  //2022-9-19  lijunqing 编辑系统参数配置项目
	virtual void slot_ReturnPrevActiveWidget();
	virtual void slot_SelectTestMacro(CSttMacroTestUI_TestMacroUIRef *pTestMacroUIRef, const CString &strItemsName, const CString &strItemsID);
	void slot_ViewMacroEditWidget(CExBaseObject *pMacroTest);
	void slot_UpdateCmdButtons_AddMacro();
	void slot_ExpandGuideBookTree();
	virtual void slot_OnInputData(CDataGroup *pParas, CExBaseList *pMsgs);
	virtual void slot_OnImportDvm(CExBaseList *pListItems);
	//zhouhj 2023.12.6 移入基类
//	void slot_OnConfigDevice(CDataGroup *pCommCfg);

	//20240802 huangliang 统一在函数Stt_Global_SettingParent中执行，删除此处代码
	////20240703 huangliang
	//void slot_ShowSetting();
	//virtual void SettingSelect(CExBaseObject *pItem);
	//virtual void SettingSelect(const CString &sValue);	//20240730 huangliang

	virtual void SetWaveWidget(QWidget *pWidget);//2024-8-5 wuxinyi 设置波形图窗口
	virtual void InitWaveDrawWidget();
	virtual void InitSystemDiagramWidget();
	//virtual void InitWiringDiagramWidget();
	virtual void InitWiringDiagramWidget(QWidget* pParent = NULL);
public:
	virtual void InitTestMacroUI_by_DeviceType(CSttMacroTestUI_TestMacroUIMngr *pTestMacroUIMngr);
	virtual void CloseDevice();
	virtual void ClearReportRslts_Html(QSttReportViewHtml* pHtmlView = NULL);  //清除HTML报告的数据
	virtual void ClearReportRslts_Html(CSttItems *pItems, QSttReportViewHtml* pHtmlView = NULL);  //清除HTML报告的数据
	virtual void ClearReportRslts_Html_SetStateNormal(CSttItems *pItems, QSttReportViewHtml* pHtmlView = NULL);//清除报告数据后，将项目状态置为noraml，以修改颜色为黑色
	virtual BOOL IsNeedAddAft();//是否需要添加测试后恢复
	virtual void ItemPaste_RootNode(CSttItems *pDestItems, CExBaseObject *pCurrentSel);  //项目粘贴后，处理报告
	virtual void CheckDvmFileValid(const CString &strDvmFile);  //校验模型文件是否存在
	virtual void InitAinDataMap(CDataGroup *pAinDataMap);  //打开记录或模板后，从模板中更新到界面框架
	virtual BOOL IsNeedSendAsync(const CString &strItemsID);  //是否需要异步发送
	long IsUnMagZero(CDvmDataset *pRptDvmDataset);//判断所有通道电压幅值是否为0
	//private slots:
//    void on_btnSetDatas_clicked();

//private:
//    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
