#ifndef TESTWINBASE_H
#define TESTWINBASE_H

#include <QtGui/QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QTabWidget>
#include <QDockWidget>
#include <QStringList>
#include <QTimer>
#include <QLabel>
#include <QTextEdit> 
#include <QMessageBox>
#include "testparaview.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"

#define _WIN32_WINNT  0x0400

#define WM_IEC61850CFGFINISHED_MSG	WM_USER + 1900

#define LogColor_Black  _T(";0")
#define LogColor_Red	_T(";1")

//#define ARGV_CMD_PARA_ID_TmpPath    _T("TmpPath")

//#define STT_IEC_PARSE_USE_Iec61850Config  //使用外部Iec61850Config.exe

//#include "../WordReport/reportSetParaDefine.h"
//#include "../WordReport/wordengine.h"

#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/xml/XmlRWInterface.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../Module/TestMacro/TestMacroGlobal.h"
#include "../../../Module/Log/LogPrint.h"
#include "../../../Module/Socket/XPing.h"
#include "../../../Module/FilterText/FilterTextGlobal.h"
#include "../../Module/Engine/SttPowerTestEngineBase.h"
#include "../IecConfigInterface.h"

#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include "../Module/TestWinFrame/dcsetdlg/CDcSetDlg.h"
#include "../Module/TestWinFrame/dasetdlg/dasetdialog.h"
#include "../Module/TestWinFrame/soedlg/soeDialog.h"
#include "../Module/TestWinFrame/testAppCfgDlg/CommTestAppCfgDlg.h"
#include "../Module/TestWinFrame/QTemplateWidgetExtend.h"
#include "../Module/TestWinFrame/QItemTableBase.h"
#include "../Module/TestWinFrame/LuminousPowerDlg/LuminousPowerDlg.h"

#include "../../../Module/SttSystemConfig/SttSystemConfig.h"
#include "../../../Module/UI/Webkit/SttReportViewHtml.h"
#include "../Module/TestWinFrame/ReportView/SttXTestMngrHtmlRptBase.h"


#include "../../../61850/Module/CfgDataMngr/IecCfgSMVDatas.h"
#include "../Module/TestWinFrame/FT3Widget/FT3ParaWidget.h"


#define FILE_SOETESTPARA		"SoeTest.soexml"
#define FILE_SYSTEMPARA			"SystemParas.sysxml"

#define MACROID_SOETEST			"SttSoeTest"

//2021-5-30  lijunqing 
#include "../../Module/SttTest/Common/tmt_test_mngr.h"
#include "../Module/TestWinFrame/RsltWidget/RsltWidget.h"

//2023-6-19 suyang
#ifdef STT_USE_IecCap_

#include "RecordTest/UI/SttIecCapDialog.h"
#include "RecordTest/UI/SttIecRecordMainWidget.h"
#include "../../../../Module/KeyDb/XKeyDB.h"

#endif

#include "../SttXTestMngrBaseApp.h"
#include "../IecConfigInterface.h"

extern bool g_bTestAppConnect;



class QCustomDockWidget : public QDockWidget 
{
	Q_OBJECT

public:
	QCustomDockWidget(const QString &title, QWidget *parent = NULL);
	~QCustomDockWidget();

protected:
	void closeEvent(QCloseEvent *event) override ;

public:
	QPoint m_initialPosition;


signals:
	void sig_updateQDockWidget();// suyang 20240110 QDockWidget发生位置变化，还原到原来的位置
};


class ParaSetWidgetInterface
{
public:
	virtual void stopInit() = 0;
	virtual void startInit() = 0;
	virtual void setData(PTMT_PARAS_HEAD pCurr) = 0;

	virtual QTabWidget* GetTabWidget(){ return m_tabWidget;};
	void SetTabWidget(QTabWidget* pTab) { m_tabWidget = pTab; }

public:
	QTabWidget* m_tabWidget;
};

class TestWinBase : public QMainWindow, public CLogBase, public CSttXTestMngrBaseApp  //CSttPowerTestEngineBase
{
	Q_OBJECT

public:
	TestWinBase(QWidget *parent = 0, Qt::WFlags flags = 0,int nMode = MODE_COMMON);
	virtual ~TestWinBase();

public:
	//layout
	QWidget *m_centralWidget;
	QGridLayout *m_gridLayout,*m_gridLayout2;
	QTabWidget *m_tabWidget;
	TestParaView *m_testParaView;

	CSttXTestMngrHtmlRptBase* m_pSttXTestMngrHtmlRpt;
	CDataGroup m_oTestReportHead;
//	QWidget *m_reportTab;

	ParaTab* m_pParaTab;
	QTextEdit *m_ReportTextEdit;
	
	QMenuBar *m_menuBar;
	QToolBar *m_mainToolBar;
	QStatusBar *m_statusBar;

	QToolBar *m_headerToolBar;
	QToolBar *m_setToolBar;
	QToolBar *m_reportToolBar;
	QToolBar *m_viewToolBar;
	QToolBar *m_updateToolBar;

	QMenu *m_headerMenu;
	QMenu *m_setMenu;
	QMenu *m_reportMenu;
	QMenu *m_viewMenu;
	QMenu *m_verMenu;

	QLabel *m_LabVersion;//zhouhj 2023.9.15 新增版本信息显示
	QLabel *m_LabGps;
	QLabel *m_LabIconGps;
	QLabel *m_LabVer;
	QLabel *m_LabLinkTxt;
	QLabel *m_LabLinkIcon;

	//QAction
	QAction *m_startAct;
	QAction *m_manuTrigerAct;
	QAction *m_stopAct;
	QAction *m_openAct;
	QAction *m_saveAct;
	QAction *m_saveAsAct;
	QAction *m_IECAct;
	QAction *m_IECCapAct;//20230629 suyang 报文探测
	QAction *m_customSetAct;
	QAction *m_setSysAct;
	QAction *m_soeTestAct;
	QAction *m_setCommonAct;
	QAction *m_setSettingAct;	
	QAction *m_setSwitchAct;	
	QAction *m_setCustomAct;
	QAction *m_Connect;	
	QAction *m_pChRsMaps_Action;	//通道资源映射 zhouhj 20211016
	QAction *m_pAuxDC_Action;	//辅助直流设置 zhouhj 20211016
	QAction *m_pModulesGearSwitch_Action;	//辅助直流设置 zhouhj 20211016
	QAction *m_pLuminousPower_Action;////chenling 20230421 光功率
	QAction *m_OffLineSel_Action;//20231122 suyang 脱机选择

	QAction *m_reportSetAct;	//报告设置
	QAction *m_reportViewAct;	//报告浏览

	QAction *m_reportOpenAct;	
	QAction *m_reportSaveAct;
	QAction *m_viewTestAct;
	QAction *m_viewReportAct;
	QAction *m_viewDockSwitchAct;
	QAction *m_viewDockStaInfoAct;
	QAction *m_VersionInforAct;//zhouhj 20211021 版本信息
	QAction *m_updateLocalAct;
	QAction *m_updateTestAppAct;

	QCustomDockWidget *m_DockSwitch;
	QCustomDockWidget *m_DockStaInfo;
	QTextEdit *m_TextEditStaInfo;

	QToolButton* m_pStartBtn;
	QToolButton* m_pManuTrigerBtn;
	QToolButton* m_pStopBtn;
	QToolButton* m_pSetSysBtn;//"系统参数"按钮
	QToolButton* m_pOffLineSelBtn;//"脱机选择"按钮
	QToolButton* m_pSetCommonBtn;
	QToolButton* m_pSetSwitchBtn;
	QToolButton* m_pSetSettingBtn;
	QToolButton* m_pSetCustomBtn;
	QToolButton* m_pDASetBtn;
	QToolButton* m_pIECBtn;
	QToolButton* m_pIECCapBtn; //20230619 suyang IEC探测
	QToolButton* m_pConnectBtn;
	QToolButton* m_pChRsMapsBtn;//zhouhj 20211016 通道映射
	QToolButton* m_pReportSetBtn;	//报告设置
	QToolButton* m_pReportViewBtn;	//报告浏览
	QToolButton* m_pSoeTestBtn;
	QToolButton* m_pAuxDCBtn;//20203-10-08 suyang 辅助直流设置
	
	QToolButton* m_pViewTestBtn;
	QToolButton* m_pViewReportBtn;
//	QToolButton* m_pDockSwitchBtn;//zhouhj 20211022 只在菜单栏显示
//	QToolButton* m_pDockStaInfoBtn;//zhouhj 20211022 只在菜单栏显示

	int m_nScreenWidth;//屏幕宽度
	int m_nScreenHeight;//屏幕高度

	void setActionEnabled(ACTION_TYPE act,bool bEnable);
	void setMonitorEnabled(MONITOR_TYPE mnt,bool bEnable);
	void setTestParasEnabled(PARAS_TYPE para,bool bEnable);

	void createLayout();	
	virtual void createToolBar();//yyj 20211014
	void CreateToolBar(BOOL bHasManualTrigger,BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs = TRUE,BOOL bIecCap = FALSE, BOOL bAuxDC = FALSE,BOOL bHasChRsMaps = TRUE);
	virtual void createActions();//yyj 20211014
	void CreateActions(BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs = TRUE);
	virtual void createMenus();  //zhouhj 20211014 对于故障回放模块,需要重载该函数,去除菜单栏部分按钮
	void CreateMenus(BOOL bHasCommonParas,BOOL bHasSetting,BOOL bHasReport,BOOL bHasSwitchs = TRUE);
	void createStatusBar();
	virtual void createDockStaInfo();
	void createDockSwitch();

	virtual void SetPlotDigitMaxMinValue();

	virtual void setTitleIcon();
	QToolButton* addToolButton(QString strToolText,QString strPixmap,QString strToolTip);

	void initUI();
	void initConnect();
	void initData();
	virtual void initSettingParas(){} //初始化整定值
	void initCommonParas();
	virtual bool SeparateShowTestView(){return false;}//分开显示试验视图
	virtual bool IsUseScanLan()
	{
		return true;
	}

	virtual CExBaseObject* CreateCharDraw(PTMT_PARAS_HEAD pTmtPara){return NULL;};

	//zhouhj 2023.10.8 如有有程序正在运行时,单独初始化语言资源,及释放语言资源
	static void InitXLanguage();
	static void ReleaseXLanguage();
/*
	void initLocalSysPara();
*/
	int  m_nMode;//更新时间特性图时使用
	bool isGradientMode(){	return m_nMode == MODE_GRADIENT;}
	bool isCommonMode()	{	return m_nMode == MODE_COMMON;	}
	bool isStateMode()	{	return m_nMode == MODE_STATE;	}

	//状态灯
	QList<QToolButton *> m_oBinInToolBtnList;
	QList<QToolButton *> m_oBinOutToolBtnList;
	QList<QToolButton *> m_IInfoList;
	QToolButton *m_V;
	QToolButton *m_OH;
	QToolButton *m_Run;
	QToolButton *m_DCurrent;

	virtual QTabWidget* GetCommonTab_UI()
	{
		return m_testParaView->getMainPara()->m_tabWidget;
	}

	QTabWidget* GetTemplateTab_UI()
	{
		QTemplateWidget* pTemplateWidget = m_testParaView->getMainPara()->m_templateWidget;
		return ((QTemplateWidgetExtend*)pTemplateWidget)->getParaSetWidget()->GetTabWidget();
	}

	tmt_BinaryConfig m_oBinaryConfig;
	void AddRecord(QColor color, QString description );
	void UpdateToolButtons();
	virtual void AddInitRecord(QString strInfo);

	virtual void InitDockSwitch(tmt_BinaryIn *pBinaryIn);//suyang 20230607 初始化状态灯  

	//报告头
	void GetReportHeadFile(CString &strFile);
	void OpenReportHead();
	void SaveReportHead();
	void InsertReportHead(CDataGroup *pSttReport,QSttReportViewHtml* pReportViewHtml);//20240514 suyang 新增插入报告头 
	CString GetReportHeadHtmlFile(CString &strFile);

	virtual void InitIECChannelsData();
	virtual void UpdateIECChannelsData(){};
	//直流
	CDataType m_ListVolChans;
	CDataType m_ListCurChans;
	//交流
	CDataType m_ACListVolChans;
	CDataType m_ACListCurChans;

	//2022.5.20 caoxc 页面是否加载完成
	bool m_bLoadFinished;
#ifdef _GRADIENT_PLOT_
	QReadWriteLock m_oGridentTimeResponse_Lock;
#endif

	//参数表
	QParaSetBase* m_pAnaParaSet;
	QParaSetBase* m_pDigParaSet;
	QParaSetBase* m_pLowSParaSet;
	QParaSetBase* m_pSyncParaSet;

	ParaSetWidgetInterface* m_ParaSetWidgetInterface;
	QItemTableBase *m_TestTable;

	QGooseParaWidget* m_pGooseParaWidget;
	ExSwitchSet* m_pExSwitchInputSetWidget;
	ExSwitchSet* m_pExSwitchOutputSetWidget;

	QTimeResponseWidget* m_pTimeResponseWidget;
	VectorWidget* m_vectorWidget;	
	PowerDiagramWidget* m_powerdiagramWidget;//20230310chenling 功率图
// 	PowerWidget *m_powerWidget;		
	SeqWidget *m_seqWidget;				
	LineVoltWidget *m_lineVoltWidget;
	InfoWidget *m_infoWidget;
	QWidget *m_pWaveWidget;//zhouhj 20211022 用于波形
	
	QFT3ParaWidget *m_pFT3Widget;//FT3界面 chenling20230426
	virtual void AddFT3Widget(CIecCfgDatasSMV *pIecCfgDatasSMV);//2024-4-17 wuxinyi 异步模块界面需重写故改为虚函数

	QStringList  m_strListInfo;

#ifdef STT_IEC_PARSE_USE_Iec61850Config
	Iec61850Config::CTestEngine m_oIecConfig;//zhouhj 20211120 移入testwinbase该成员只能在Window下使用
#endif
	
	CSclStation m_oSclStation;//增加用于存储当前SCD文件中的全部控制块内容,用于IEC配置和IEC探测 zhouhj 20221206
	virtual void InitTestResource();//初始化测试资源
	virtual void GenerateTestCmdFromIEC(CSttParas &oSttParas);

	//DCSetDlg
	CDcSetDlg m_oDcSetDlg;
	bool m_bAuxDCOutputStarted;		//辅助直流控制开始停止状态
	bool m_bCustomACOutputStarted;	//交流控制开始停止状态

	//DASetDlg
	DASetDialog m_oDASetDlg;		
	BOOL m_bSystemParasChanged;		//系统参数设置修改标记
	BOOL m_bChMapsChanged;//表示通道映射文件是否已经改变，在Socket连接成功后，将该参数置为1,在下发一次成功后,将其置为0,如果通道映射改变后,将其置为1
	CString getSystemParasFilePath();
	void LogPrintSoftWareVersionMsg();//zhouhj 20220113 打印当前程序版本信息.

	void LogPrintTypeMsg();//2023-12-19 suyang 打印当前输出类型信息.

	//SoeDialog
/*
	tmt_SoeParas m_oSoeParas;	
*/
	SoeDialog m_oSoeDlg;			
/*
	CString getSoeParasFilePath();
	BOOL SaveSoeParasFile(const CString& strSoeFile="");
	long OpenSoeParasFile(const CString& strSoeFile="");
	void initDefaultSoeParaFile();
	virtual void GenerateTestCmdFromSoeParas(CSttTestCmd &oSttTestCmd);
*/

	//TestApp
	QRsltWidget * m_pRsltWidget; //mym 2021-7-23 
	void UpdateLogString();//mym 2021-7-27
	CString m_strLogInfo[24];     //mym 2021-7-31

	virtual void UpdateEventMsg(CEventResult *pEventInfo);
	virtual void SysStateEvent_OnTestStart();
	virtual void SysStateReport_OnSwithChanged();
	virtual void SysStateReport_OnStateChanged();
	virtual void SysStateEvent_OnTestStoped();
	virtual void SysStateEvent_OnTestFinished();
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){}//zhouhj  增加用于搜索类获取当前点值
	virtual long Event_OnProcessComtradeRequstData(long nIndex){return 0;}
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex){return 0;}

	virtual CString GetDefaultParaFile();
	virtual void initTestParas();
	virtual void InitDefaultTestItems(){};//zhouhj 20211118 修改基类虚函数,确保BaseFrameClient工程编译通过
	virtual void InitTestTable();

	virtual void CalAxisInstructPoint(float fZK,float fAng);//zhangyq 20230713 计算阻抗特性图坐标轴上显示的值
	virtual void UpdateCurveData(); //dxy 2023.9.9 同步初始化标记，避免多重定义宏
	
	// suyang 20230710 报文探测模块
public:

#ifdef STT_USE_IecCap_
	CXKeyDB *m_pKeyDB;
#endif

	BOOL m_bIsUsingIecCap;//20230718 suyang 判断当前是否正在使用报文探测界面
	virtual void SendIecDetect(long bEnable);// suyang 20230710 开始报文探测 发送探测命令
	virtual void SendIecRecord(CDataGroup *pIecRecordParas);

	virtual void InitSttIecRecord(CSttTestAppCfg* pSttTestAppCfg);//suyang 20230710 初始化探测
	virtual void ExitSttIecRecord();
	virtual void InitKeyDB();
	
	//2022-4-13  lijunqing
	virtual void On_IecDetect(CDataGroup *pIecCb);
	void CreateAction_IecCap();//suyang 20230710  设置菜单栏是否有报文探测
	
	virtual void UpdateSettingParas(){}; //20240402 suyang 柔直模块在更新系统参数设置后需要更新整定值的范围
	
	bool m_bReportData;//20240425 suyang 增加对报告视图显示判断，第一次加载，第二次不需要重新加载，开始测试后重新加载


public:
	void signalLink();
	void signalIBreak_UOverLoad_OverHeat();//20240124 suyang 更新电流开路、电压过载、过热指示灯 
	void signalBinInToolBtn();//20240201 chenling 在运行过程中goose数据发送每个通道数值,更新开入量状态灯显示

//chenling
	void StartPowerWidget();
	void StopPowerWidget(bool bUpdate = false);

	virtual void OnViewTestLink(BOOL b=FALSE){};
	virtual void OnViewTestStart();//sf 20210929 增加测试开始,取反置灰
	virtual void OnViewTestStop();//sf 20210929 增加测试开始,取反取消置灰
	virtual void OnUpdateTestResource(BOOL bCreateChMaps);//参数为是否创建通道映射文件,在系统参数更新时,通道映射文件已经存在,不需要再创建
	virtual void UpdateGoutTab(BOOL bUpdateList = FALSE){};//该函数需要重载 zhouhj 不同的测试项Gout界面显示的内容不同,参数标识是否更新每个测试项或者每个状态的Gout数据链表
	virtual void UpdateFT3Tab(BOOL bUpdateList = FALSE){};
	virtual void UpdateBinBoutExTab(){};//更新开关量扩展界面,更新系统参数
	void UpdateToolButtons_BinInPart( int nIndexBin);//sf 20210929 状态灯状态切换
	virtual void UpdateGoutTab_UI(CIecCfgGoutDatas* pCfgGoutDatas );//更新Gout界面,根据当前系统参数判断是否显示
//	virtual void OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend);//zhouhj 20210827更新Gps时间  参数1标识是否同步

	virtual BOOL OnConnectTestApp(const CString &strIP, long nPort);//zhouhj 20210821 对于故障回放模块,在联机成功后,需要CreateSttComtradeSocket
	BOOL OnConnectTestApp();//zhouhj 20211016 先判断当前有没联机成功,如果未联机则联机,返回联机结果;如果当前已联机,则返回true

	virtual void OnTestStarted(const CString &strMacroID, CDataGroup *pParas);
	virtual void OnTestState(const CString &strMacroID, CDataGroup *pParas);
	virtual long OnDisConnect();
	virtual void OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas);//读取Device的Report解析函数

	virtual void EndBinStateOnStarting();

	QTimer m_oTimer;
	CGpsPcTime m_dStartTime;
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(long nLevel, const char *strMsg);

	void RaiseSwitchInfo();
	void RaiseStateInfo();

	virtual void PreCloseMainWidget(){};
	//20230823 zhouhj //验证当前测试项参数是否有效,主要用于故障回放模块,在开始测试前切换回放文件,验证回放文件内容是否满足条件
	virtual bool ValidCurrTestItemParas(){return true;}
	const char* GetFaultTypeText(int nFaultType)
	{
		static const char*  g_pszrFaultType[] = {"A-E","B-E","C-E","A-B","B-C","C-A","A-B-E","B-C-E","C-A-E","A-B-C","单相"};

		if (nFaultType < 0 || nFaultType >= 11)
		{
			return g_pszrFaultType[0];
		}

		return g_pszrFaultType[nFaultType];
	}

	virtual void InitVectorWidget(tmt_channel* pVOL=NULL,tmt_channel* pCUR=NULL); //20211016 sf
	virtual void InitPowerDiagramWidget(tmt_channel* pVOL=NULL,tmt_channel* pCUR=NULL);//20230314 chenling
	virtual void InitTimeResponseWidget();
	virtual void ClearTimeResponseData();  //20211105 sf 
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);

	virtual void UpdateAuxDcEnabled();  //20230407 zhangyq
	virtual void UpdateFreq();  //20230529 zhangyq

	void SetPrintLog(BOOL bPrintLog){	g_bPrintLog = bPrintLog;	}
	void SetSaveFile(BOOL bSaveFile){   g_bSaveFile = bSaveFile;	}

	void updateParas();

	//2023-12-26 wuxinyi 
	QSharedMemory m_oTestMacroSM;//共享内存
	BOOL InitTestMacroSM();// 判断共享内存是否挂载成功
	virtual void UpdateTestModule(const CString& strParasFile,const CString &strTplID);//更新测试模块，发送参数

	BOOL HasFT3Block_Selected();//chenling 2024.4.26 纯数字量输入IEC不勾选控制块 点开始需提示

signals:
	void sig_refreshLog(QString strLog);// suyang 20230710 发送信号，更新QSttIecCapDialog 中输出框打印信息
	void sig_UpdateEventMsg();
	void sig_ViewTestStart();
	void sig_ViewTestStop();
	void sig_ViewTestLink(bool b);
	void sig_UpdateTestResource();
	void sig_LogString(CString strMsg);
	void sig_OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend,QString strTime);
	void sig_OnUpdateGpsTime(CDataGroup *pRtSycTime);

	void sig_updataVectorData();//20230712 suyang 更新矢量图数据

protected slots:
	void slot_LogString(CString strMsg);
	virtual void slot_Timer(); //zhouhj 20211030 
	virtual void slot_UpdateEventMsg();
	void slot_OnUpdateGpsTime(long nSyn, long nSecond,long nNSecend, QString strTime);
	void slot_OnUpdateRtSyncTime(CDataGroup *pRtSycTime);

	//测试用 caoxc
	virtual void slot_initReportView();

	virtual long slot_start();							
	void slot_ViewTestStart();
	void slot_ViewTestStop();
	void slot_ViewTestLink(bool b);
	void slot_UpdateTestResource();//更新界面关联的软件资源	
	void slot_stop();
	virtual void slot_SysParasHasChanged(BOOL bChMapsHasChanged);//系统参数改变后调用的槽函数
	void slot_OffLineSelChanged();//脱机选择改变
	virtual void slot_manuTriger(){};

	virtual void slot_openTestParas();	
	virtual void slot_saveTestParas();	
	virtual void slot_saveAsTestParas();
	virtual void InitUI_OpenParas();
	virtual void slot_updateParas();
	virtual void slot_updateVectorData();//20230712 suyang 更新矢量图数据

	virtual void slot_setSys();				
	void slot_OffLineSel();				
	virtual void slot_setCommon(){};		//各功能模块重载打开各自的通用参数对话框
	virtual void slot_setSetting();
	virtual void slot_SettingValueChanged(){}; //整定值修改之后调用函数 sf 20210804 add 
	virtual void slot_setSwitch(){};		//各功能模块重载开关量设置对话框
	virtual void slot_GooseDataChanged(){};   //GOOSE发布数据改变
	virtual void slot_RepairDataChanged(){};

	virtual void slot_FT3DataChanged(){};   //FT3发布数据改变
	virtual void slot_FT3RepairDataChanged(){};

	void slot_connect();
	void slot_ChRsMaps_Dlg();//进行通道资源映射
	void slot_AuxDC_Dlg();//辅助直流设置
	void slot_ModulesGearSwitch_Dlg();//功率设置
	void slot_TesterIP_Changed();//zhouhj 20211005 修改了网络连接
	void slot_UpdateModulesGear(bool bMergeCurrHasChanged);//zhouhj 20211016 更新测试仪档位信息
	void slot_UpdateAuxDCOutput();//zhouhj 20211016 更新测试仪辅助直流输出
	virtual void slot_UpdateChRsMaps(BOOL bSysParasHasChanged);
	void slot_IEC();			
	void slot_IECCap();
	  
	void slot_setCustom();		
	void slot_soeTest();		
	void slot_LuminousPower_Dlg();//光功率

	void slot_CustomACOutputStart();
	void slot_CustomACOutputEnd();
	void slot_DASetStart(bool bChanged);

	void slot_SoeStart();
	void slot_SoeStop();
	void slot_SoeParasSave();

	void slot_reportSet();

	void slot_reportOpen();
	void slot_reportSave();
//	void slot_ReportSetParaOk(reportSetPara &data);

	virtual void slot_viewTest();
	virtual void slot_viewReport();//suyang 20240320 状态序列重写报告视图

	void slot_viewDockSwich();
	void slot_viewDockStaInfo();

	void slot_viewDockSwichEx();
	void slot_viewDockStaInfoEx();

	void slot_versionInformation();
	void slot_localUpdate();
	void slot_testAppUpdate();

	//测试列表公共槽 yyj 20210714
	virtual void slot_AddItemBF();
	virtual void slot_AddItemAF();
	virtual void slot_DeleteCurr();
	virtual void slot_Delete_N_1();
	virtual void slot_SelectAll();
	virtual void slot_UnselectAll();
	virtual void slot_ClearCurrResult();
	virtual void slot_ClearAllResult();
	virtual void slot_IecCfgDataMngrUpdate();//zhouhj 20220315 更新IEC数据
	//2022.5.19 caoxc
	virtual void slot_loadFinished(bool b);

	void slot_DockClosed();

protected:
	void closeEvent(QCloseEvent *e);
	virtual bool winEvent(MSG* msg, long* result);
};

extern TestWinBase* g_TestWinBase;
extern CSttTestAppCfg g_oSttTestAppCfg;

extern double g_dUIShowCoef; // 界面显示缩放比例

#endif //TESTWINBASE_H
