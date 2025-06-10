// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// Iec61850Config.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "Iec61850Config.h"
#include "MainFrm.h"

#include "IecConfigFrame.h"
#include "IecConfigDoc.h"
#include "IecConfigView.h"

#include "StateToolFrame.h"
#include "StateToolDoc.h"
#include "StateToolView.h"

#include "SclFileFrame.h"
#include "SclFileDoc.h"
#include "SclFileTreeView.h"

#include "SclFileHistoryDlg.h"

#include "..\Module\UI\DlgNewDevConfig.h"

#include "..\Module\IecCfgDownInterface\IecCfgDownInterface.h"
#include "..\..\Module\API\SingleAppMutexApi.h"
#include "..\..\Module\TestMacro\TestMacroConfig.h"
#include "..\Module\IecCfgSclTool\SclToIecCfgTool.h"
#include "..\..\Module\XfileMngrBase\XFileSaveAsDlg.h"

#include "..\..\System\Module\XAtsSysSvrClient.h"
#include "..\..\Module\XfileMngrBase\YunFileApi\XYunFileApi.h"
#include "..\Module\CfgDataMngr\IecCfgDeviceCreater.h"
#include "TestEngine.h"

#include "../../Module/API/FileApi.h"
#ifdef _USE_IN_AT02D_MODE_
#include "../Module/AT02DTool/AT02D_Tool.h"
#endif

#include "SelectAT02D_CBDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIec61850ConfigApp

BEGIN_MESSAGE_MAP(CIec61850ConfigApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CIec61850ConfigApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CIec61850ConfigApp::OnFileNew)

	ON_COMMAND(ID_FILE_NEW_AT02D, &CIec61850ConfigApp::OnFileNew_AT02D)//周宏军 20200616  增加AT02配置

	ON_COMMAND(ID_FILE_NEW_DEVICE, &CIec61850ConfigApp::OnFileNewDevice)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_DEVICE, &CIec61850ConfigApp::OnUpdateFileNewDevice)
	ON_COMMAND(ID_FILE_NEW_DEVICE_AT02D, &CIec61850ConfigApp::OnFileNewDeviceAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW_DEVICE_AT02D, &CIec61850ConfigApp::OnUpdateFileNewDeviceAT02D)
	ON_COMMAND(ID_FILE_OPEN, &CIec61850ConfigApp::OnFileOpen)
	ON_COMMAND(ID_FILE_OPEN_SCL, &CIec61850ConfigApp::OnFileOpenScl)
	ON_COMMAND(ID_FILE_OPEN_SCL_HIS, &CIec61850ConfigApp::OnFileOpenSclHis)
	ON_COMMAND(ID_FILE_OPEN_SCL_AT02D, &CIec61850ConfigApp::OnFileOpenSclAT02D)
	ON_COMMAND(ID_FILE_OPEN_SCL_HIS_AT02D, &CIec61850ConfigApp::OnFileOpenSclHisAT02D)
	ON_COMMAND(ID_FILE_SAVE, &CIec61850ConfigApp::OnFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CIec61850ConfigApp::OnUpdateFileSave)

	ON_COMMAND(ID_SEND_CONFIG, &CIec61850ConfigApp::OnSendConfig)
	ON_UPDATE_COMMAND_UI(ID_SEND_CONFIG, &CIec61850ConfigApp::OnUpdateSendConfig)

	ON_COMMAND(ID_FILE_SAVE_AS, &CIec61850ConfigApp::OnFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CIec61850ConfigApp::OnUpdateFileSaveAs)
	ON_COMMAND(ID_FILE_SAVE_AT02D, &CIec61850ConfigApp::OnFileSaveAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AT02D, &CIec61850ConfigApp::OnUpdateFileSaveAT02D)
	ON_COMMAND(ID_FILE_SAVE_AS_AT02D, &CIec61850ConfigApp::OnFileSaveAsAT02D)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS_AT02D, &CIec61850ConfigApp::OnUpdateFileSaveAsAT02D)
	ON_COMMAND(ID_EXPORT_DEVICE_MODEL, &CIec61850ConfigApp::OnExportDevModel)
	ON_UPDATE_COMMAND_UI(ID_EXPORT_DEVICE_MODEL, &CIec61850ConfigApp::OnUpdateExportDevModel)
	ON_COMMAND(ID_FILE_USE_IECCFGFILE, &CIec61850ConfigApp::OnFileUseIeccfgfile)
	ON_UPDATE_COMMAND_UI(ID_FILE_USE_IECCFGFILE, &CIec61850ConfigApp::OnUpdateFileUseIeccfgfile)
	ON_COMMAND(ID_FILE_STATE_TOOL, &CIec61850ConfigApp::OnFileStateTool)
	ON_UPDATE_COMMAND_UI(ID_FILE_STATE_TOOL, &CIec61850ConfigApp::OnUpdateFileStateTool)
	ON_COMMAND(ID_FILE_STATE_STARTTEST, &CIec61850ConfigApp::OnFileStateStarttest)
	ON_UPDATE_COMMAND_UI(ID_FILE_STATE_STARTTEST, &CIec61850ConfigApp::OnUpdateFileStateStarttest)
	ON_COMMAND(ID_FILE_STATE_STOPTEST, &CIec61850ConfigApp::OnFileStateStoptest)
	ON_UPDATE_COMMAND_UI(ID_FILE_STATE_STOPTEST, &CIec61850ConfigApp::OnUpdateFileStateStoptest)
	ON_COMMAND(ID_VIEW_IECCFG_USEDIN, &CIec61850ConfigApp::OnViewIeccfgUsedin)
	ON_UPDATE_COMMAND_UI(ID_VIEW_IECCFG_USEDIN, &CIec61850ConfigApp::OnUpdateViewIeccfgUsedin)
	ON_COMMAND(ID_VIEW_CH_PATH, &CIec61850ConfigApp::OnViewChPath)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CH_PATH, &CIec61850ConfigApp::OnUpdateViewChPath)
END_MESSAGE_MAP()


// CIec61850ConfigApp 构造

CIec61850ConfigApp::CIec61850ConfigApp()
{

	m_bHiColorIcons = TRUE;

	m_pSclFileFrame = NULL;
	m_bIsNowTesting = FALSE;
	m_pStateToolFrame = NULL;
	m_pCurrSelSclIed = NULL;
	m_bIsCfgInStationTest = FALSE;
}

// 唯一的一个 CIec61850ConfigApp 对象

CIec61850ConfigApp theApp;

// 生成的此标识符在统计上对于您的应用程序是唯一的
// 如果您更愿选择一个特定的标识符，则可以更改它

// {AD0B02A6-A607-432C-9B4A-D0C77A4079F5}
//7afcf044-5364-425e-b30f-a9c9551b1914
static const CLSID clsid =
{ 0x7afcf044, 0x5364, 0x425e, { 0xb3, 0x0f, 0xa9, 0xc9, 0x55, 0x1b, 0x19, 0x14 } };

const GUID CDECL BASED_CODE _tlid =
{ 0xBFA9896E, 0x3425, 0x473B, { 0x93, 0x76, 0x68, 0x96, 0x2C, 0x0D, 0xC8, 0x7E } };//BFA9896E-3425-473B-9376-68962C0DC87E
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CIec61850ConfigApp 初始化

BOOL CIec61850ConfigApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_P_GetCompany());
	LoadStdProfileSettings(0);  // 加载标准 INI 文件选项

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	//初始化
	_P_InitSystemPath();

	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(new CXLanguageResourceIec_61850Cfg(), TRUE );
	Yun_Init();

	CDataMngrXmlRWKeys::Create();
	CCfgDataMngrXmlRWKeys::Create();
	CIecCfgToolXmlRWKeys::Create();
	CIecCfgTool::Create();
	CCfgDataMngrConstGlobal::Create();
	CFilterTextXmlRWKeys::Create();
	CTestMacroXmlRWKeys::Create();
	//CTestMacroConfigs::Create();
	CXScdDrawConstGlobal::Create();

	CCfgDataMngrConstGlobal::SetViewOnlyUsedInChs(CIecCfgTool::IsViewOnlyUsedInChs());
	CXScdDrawConstGlobal::SetOnlyShowUsedSvOutChs(CIecCfgTool::IsViewOnlyUsedInChs());
	CXScdDrawConstGlobal::SetOnlyShowUsedGsOutChs(CIecCfgTool::IsViewOnlyUsedInChs());
	CXAtsSysSvrClient::Create();

	if (!atssys_CreateSingleAppMutex(_T("Iec61850Config_Inst_Lock"), XMODULE_ID_Iec61850Config) )
	{
		return FALSE;
	}

	g_nEngineDispMode = _DISP_MODE_NORMAL;

// 	long nAppID = 22222;
// 
// 	CString strTmp;
// 	strTmp.Format(_T("%04X"),nAppID);

// 	LoadDownIecCfgFileLib(CIecCfgTool::GetIecCfgDownDllFile());

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	InitTemplate();

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 MDI 应用程序中，这应在设置 m_pMainWnd 之后立即发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();

	m_server.ConnectTemplate(clsid, m_pIecConfigDocTemplate, TRUE);
	// 启用“DDE 执行”
	//EnableShellOpen();
	//RegisterShellFileTypes(TRUE);

	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	m_bIsRunAutomaition = FALSE;

	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	//使应用程序作为自动化服务器运行。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// 将所有的 OLE 服务器工厂注册为正在运行。这将启用
		//  OLE 库以从其他应用程序中创建对象
		COleTemplateServer::RegisterAll();

		// 不显示主窗口
		//return TRUE;
		m_bIsRunAutomaition = TRUE;
	}
	// 使用 /Unregserver 或 /Unregister 开关启动应用程序。注销
	// 类型库。其他注销操作在 ProcessShellCommand() 中发生。
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;//zhouhj 20211124 反注册直接返回
	}
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		return FALSE;//zhouhj  注册直接返回
	}
	// 应用程序是以独立方式或用其他开关(如 /Register
	// 或 /Regserver)启动的。更新注册表项，包括类型库。
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
//		return FALSE;
	}

	cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	OpenLastFiles();//zhouhj 20200904
	CXAtsSysSvrClient::RegisterModule(CXLanguageResourceIec_61850Cfg::g_sLangTxt_TesterIEC61850Config/*_T("测试仪Iec61850Config")*/, XMODULE_ID_Iec61850Config, (DWORD)m_pMainWnd->m_hWnd, (DWORD)m_hInstance, WM_XATSSYSCLIENT);

	return TRUE;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CIec61850ConfigApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIec61850ConfigApp 自定义加载/保存方法

void CIec61850ConfigApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CIec61850ConfigApp::LoadCustomState()
{
}

void CIec61850ConfigApp::SaveCustomState()
{
}

// CIec61850ConfigApp 消息处理程序




BOOL CIec61850ConfigApp::InitTemplate()
{
	m_pIecConfigDocTemplate = new CMultiDocTemplate(IDR_Iec61850ConfigTYPE,
		RUNTIME_CLASS(CIecConfigDoc),
		RUNTIME_CLASS(CIecConfigFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CIecConfigView));
	if (!m_pIecConfigDocTemplate)
		return FALSE;
	AddDocTemplate(m_pIecConfigDocTemplate);

	m_pSclFileDocTemplate = new CMultiDocTemplate(IDR_SclFileTYPE,
		RUNTIME_CLASS(CSclFileDoc),
		RUNTIME_CLASS(CSclFileFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CSclFileTreeView));

	if (!m_pSclFileDocTemplate)
		return FALSE;

	AddDocTemplate(m_pSclFileDocTemplate);

	m_pStateDocTemplate = new CMultiDocTemplate(IDR_SclFileTYPE,
		RUNTIME_CLASS(CStateToolDoc),
		RUNTIME_CLASS(CStateToolFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CStateToolView));

	if (!m_pStateDocTemplate)
		return FALSE;

	AddDocTemplate(m_pStateDocTemplate);

	return TRUE;
}

void CIec61850ConfigApp::OpenDocTemplate(CMultiDocTemplate *pDocTemplate, CView **pView, CMDIChildWndEx **pFrame)
{
	CDocument *pDoc = pDocTemplate->OpenDocumentFile(NULL);
	POSITION	pos = pDoc->GetFirstViewPosition();
	*pView=pDoc->GetNextView(pos);
	ASSERT(*pView != NULL);
	*pFrame = (CMDIChildWndEx*)(*pView)->GetParentFrame();
	ASSERT(*pFrame != NULL);
}


void CIec61850ConfigApp::OpenAllFrame()
{
	CView *pView = NULL;

	CMDIChildWndEx *m_pPackageFrame;
	CMDIChildWndEx *m_pRecordFrame;

	OpenDocTemplate(m_pIecConfigDocTemplate, &pView, &m_pPackageFrame);
	CDocument *pDoc = pView->GetDocument();
	pDoc->SetTitle(CXLanguageResourceIec_61850Cfg::g_sLangTxt_MsgMonitorWnd/*_T("报文监视窗口")*/);

	OpenDocTemplate(m_pSclFileDocTemplate, &pView, &m_pRecordFrame);
	pDoc = pView->GetDocument();
	pDoc->SetTitle(CXLanguageResourceIec_61850Cfg::g_sLangTxt_WaveMonitorWnd/*_T("波形监视窗口")*/);
}

CIecConfigFrame* CIec61850ConfigApp::CreateNewIecCfgFrame(CIecCfgFile *pIecCfgFile)
{
	CMDIChildWndEx *pFrame;
	CView *pView = NULL;

	OpenDocTemplate(m_pIecConfigDocTemplate, &pView, &pFrame);
	CIecConfigDoc *pDoc = (CIecConfigDoc*)pView->GetDocument();
	pDoc->m_pIecCfgFile = pIecCfgFile;

 	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)) );
 
 	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	pIecConfigFrame->m_pIecCfgFile = pIecCfgFile;
	pIecConfigFrame->m_pDocument = pDoc;
	pDoc->UpdateAllViews(NULL, (LPARAM)pIecCfgFile, NULL);
	pDoc->SetTitle(pIecCfgFile->m_strName);

	pIecCfgFile->SetRefFrameWnd(pIecConfigFrame);
	CIecCfgDataCopyPasteTool::EnableAllPasteButtons();

	//显示文件名称到状态栏
	ShowIecCfgFileTitleToStatusBar(pIecCfgFile);

	return pIecConfigFrame;
}

void CIec61850ConfigApp::CloseIecfgFrame(CExBaseObject *pIecCfgDatasMngr, BOOL bDelete)
{
	CIecCfgFileDevice *pIecFileDevice = (CIecCfgFileDevice *)pIecCfgDatasMngr->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
	ASSERT (pIecFileDevice != NULL);

	if (pIecFileDevice == NULL)
	{
		return;
	}

	CIecCfgFile *pIecfgFile = pIecFileDevice->FindIecfgDataMngr((CIecCfgDatasMngr*)pIecCfgDatasMngr);

	if (pIecfgFile == NULL)
	{
		return;
	}

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pIecfgFile->GetRefFrameWnd();

	if (pIecConfigFrame == NULL)
	{
		return;
	}

	pIecConfigFrame->SetCloseFrameByDelete(bDelete);
	pIecConfigFrame->PostMessage(WM_CLOSE, 0, 0);
}

void CIec61850ConfigApp::UpdateIecfgFileTitle(CExBaseObject *pIecCfgDatasMngr)
{
	CIecCfgFileDevice *pIecFileDevice = (CIecCfgFileDevice *)pIecCfgDatasMngr->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
	ASSERT (pIecFileDevice != NULL);

	if (pIecFileDevice == NULL)
	{
		return;
	}

	CIecCfgFile *pIecfgFile = pIecFileDevice->FindIecfgDataMngr((CIecCfgDatasMngr*)pIecCfgDatasMngr);

	if (pIecfgFile == NULL)
	{
		return;
	}

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pIecfgFile->GetRefFrameWnd();

	if (pIecConfigFrame == NULL)
	{
		return;
	}

	pIecConfigFrame->m_pDocument->SetTitle(pIecCfgDatasMngr->m_strID);
	ShowIecCfgFileTitleToStatusBar(pIecfgFile);
}

CIecConfigFrame* CIec61850ConfigApp::CreateNewIecCfgFrame(CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	CMDIChildWndEx *pFrame;
	CView *pView = NULL;

	CIecCfgFileDevice *pIecFileDevice = (CIecCfgFileDevice *)pIecCfgDatasMngr->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
	ASSERT (pIecFileDevice != NULL);

	if (pIecFileDevice == NULL)
	{
		return NULL;
	}

	CIecCfgFile *pIecfgFile = pIecFileDevice->FindIecfgDataMngr(pIecCfgDatasMngr);

	if (pIecfgFile != NULL)
	{
		pFrame = (CMDIChildWndEx*)pIecfgFile->GetRefFrameWnd();
		pFrame->ActivateFrame(1);
		return (CIecConfigFrame*)pFrame;
	}

	pIecfgFile = pIecFileDevice->AddIecfgDataMngr(pIecCfgDatasMngr);
	OpenDocTemplate(m_pIecConfigDocTemplate, &pView, &pFrame);
	CIecConfigDoc *pDoc = (CIecConfigDoc*)pView->GetDocument();
	pDoc->m_pIecCfgFile = pIecfgFile;

	ASSERT (pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)) );

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	pIecConfigFrame->m_pIecCfgFile = pIecfgFile;
	pIecConfigFrame->m_pDocument = pDoc;
	pDoc->UpdateAllViews(NULL, (LPARAM)pIecfgFile, NULL);
	pDoc->SetTitle(pIecfgFile->GetName());

	pIecfgFile->SetRefFrameWnd(pIecConfigFrame);
	CIecCfgDataCopyPasteTool::EnableAllPasteButtons();

	//显示文件名称到状态栏
	ShowIecCfgFileTitleToStatusBar(pIecfgFile);

	return pIecConfigFrame;
}

CIecConfigFrame* CIec61850ConfigApp::CreateNewIecCfgFrame_FirstIecCfgDatasMngr(CIecCfgFileDevice *pIecfileDevice)
{
	CIecCfgDevice *pIecfgDevice = pIecfileDevice->GetIecCfgDevice();
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);

	if (pIecfgDatasMngr != NULL)
	{
		return theApp.CreateNewIecCfgFrame(pIecfgDatasMngr);
	} 
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("当前CIecCfgDevice对象中,无CIecCfgDatasMngr配置文件."));
		return NULL;
	}
}

void CIec61850ConfigApp::CreateNewIecCfgDeviceFrame(CIecCfgFile *pIecCfgFile)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecfgFileDevice(pIecCfgFile);
}

void CIec61850ConfigApp::ShowIecCfgFileTitleToStatusBar(const CString &strFile)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecCfgFileTitleToStatusBar(strFile);
}

void  CIec61850ConfigApp::ShowIecCfgFileTitleToStatusBar(CIecCfgFile *pIecfgFile)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecCfgFileTitleToStatusBar(pIecfgFile);
}

void CIec61850ConfigApp::OnFileNew()
{
	//创建新的文件对象
	CIecCfgFile *pNew = CIecCfgTool::NewIecCfgFile();

	CreateNewIecCfgFrame(pNew);

	pNew->SetModified();
	UpdateIecCfgFilesComboBox();
}

void CIec61850ConfigApp::OnFileNew_AT02D()//周宏军 20200616  增加AT02配置
{
	CString strTemplatePath;
	strTemplatePath = _P_GetTemplatePath();
	strTemplatePath.Append(_T("AT02D.iecfg"));

	if (!IsFileExist(strTemplatePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("标准AT02D文件不存在[%s],无法新建."), strTemplatePath);
		return;
	}

	((CMainFrame*)m_pMainWnd)->CloseAllIecfgDeviceFrame();
	CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice*)CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
	CIecCfgDevice *pIecfgDevice = pIecfileDevice->GetIecCfgDevice();
	pIecfgDevice->OpenIecCfgFile(strTemplatePath);
	pIecfgDevice->m_nType = IEC_CFG_DEVICE_USE_TYPE_AT02D;
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecfgFileDevice(pIecfileDevice);
}


void CIec61850ConfigApp::OnFileNewDevice()
{
	((CMainFrame*)m_pMainWnd)->CloseAllIecfgDeviceFrame();

	CDlgNewDevConfig dlg;

	if (dlg.DoModal() == IDOK)
	{
		CString strFile = dlg.m_strStaticPath;
		CString strFileName;
		strFileName = theApp.m_pCurrSelSclIed->m_strName;
		strFileName += _T("_");
		strFileName += theApp.m_pCurrSelSclIed->m_strModel; 
		CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(strFile);//将strFile文件路径下的文件读取，存入pIecCfgFile中；如路径下没有对应文件，返回NULL；

		if (pIecCfgFile == NULL)
		{
			return;
		}

		CIecCfgFileDevice *pIecfileDeviceSrc = (CIecCfgFileDevice *)pIecCfgFile;
		CIecCfgDevice *pIecfgDeviceSrc = pIecfileDeviceSrc->GetIecCfgDevice();//配置设备中包含了IED信息和两个配置文件；
		CIecCfgFileDevice oIecfileDeviceNew;
		oIecfileDeviceNew.m_strName = pIecfileDeviceSrc->m_strName;
		oIecfileDeviceNew.m_strID = pIecfileDeviceSrc->m_strID;
		CIecCfgDevice *pIecfgDeviceNew = oIecfileDeviceNew.GetIecCfgDevice();
		pIecfgDeviceNew->m_strIcdFile = pIecfgDeviceSrc->m_strIcdFile;
		pIecfgDeviceNew->m_nType = pIecfgDeviceSrc->m_nType;
		CSclToIecCfgTool oSclToIecCfgTool;

		if (theApp.m_pSclFileFrame == NULL)
		{
			return ;
		}

		CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
		CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
		oSclToIecCfgTool.AttacthSclFileRead(pSclStation);
		CIecCfgDeviceCreater oIecCfgDeviceCreater;
		oIecCfgDeviceCreater.InitCreate(pIecfgDeviceSrc ,pIecfgDeviceNew , &oSclToIecCfgTool,theApp.m_pCurrSelSclIed);
		CExBaseObject *pCurObj = NULL;
		CIecCfgDatasMngr *pIecfgDatasMngrSrc = NULL;
		POS posMgr = pIecfgDeviceSrc->GetHeadPosition();

		while(posMgr)
		{
			pCurObj = pIecfgDeviceSrc->GetNext(posMgr);

			if (pCurObj->GetClassID() != CFGCLASSID_CIECCFGDATASMNGR)
			{
				continue;
			}

			pIecfgDatasMngrSrc = (CIecCfgDatasMngr*)pCurObj;
			oIecCfgDeviceCreater.CreateCIecCfgDatasMngr(pIecfgDatasMngrSrc);
		}


// 		CIecCfgDatasMngr *pIecfgDatasMngrSrc = (CIecCfgDatasMngr*)pIecfgDeviceSrc->GetHead();
// 		oIecCfgDeviceCreater.CreateCIecCfgDatasMngr(pIecfgDatasMngrSrc);
// 
// 		POS posMgr = pIecfgDeviceSrc->GetHeadPosition();
// 		pIecfgDeviceSrc->GetNext(posMgr);
// 		pIecfgDeviceSrc->GetNext(posMgr);
// 		while (posMgr != NULL)
// 		{
// 			pIecfgDatasMngrSrc = (CIecCfgDatasMngr*)pIecfgDeviceSrc->GetNext(posMgr);
// 			oIecCfgDeviceCreater.CreateCIecCfgDatasMngr(pIecfgDatasMngrSrc);
// 		}

		CString strFilePath = dlg.m_strStaticPathNew;
		strFilePath += strFileName;
		strFilePath += _T("_智能生成.iecfg");
		oIecfileDeviceNew.SaveAs(strFilePath);


		CIecCfgFile *pIecCfgFileRead = CIecCfgTool::OpenIecFile(strFilePath);

		if (dlg.m_bAutoSave)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能生成配置文件，路径为%s"), strFilePath);
		} 
		else
		{
			DeleteFile(strFilePath);
		}
		CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
		pMainFrame->ShowIecfgFileDevice(pIecCfgFileRead);
		CreateNewIecCfgFrame_FirstIecCfgDatasMngr(&oIecfileDeviceNew);
		return;
	}

	CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice*)CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
	OnFileNewDevice(pIecfileDevice);
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecfgFileDevice(pIecfileDevice);
	CLogPrint::LogString(XLOGLEVEL_TRACE,_T("新建设备配置成功."));
	CreateNewIecCfgFrame_FirstIecCfgDatasMngr(pIecfileDevice);
}

void CIec61850ConfigApp::OnFileNewDeviceAT02D()
{
	((CMainFrame*)m_pMainWnd)->CloseAllIecfgDeviceFrame();

	if (g_nEngineDispMode == _DISP_MODE_PNI302)
	{
		CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice*)CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
		OnFileNewDevice(pIecfileDevice);
		pIecfileDevice->m_strID = _P_GetTemplatePath();
		pIecfileDevice->m_strID += _T("PNI302_Config.iecfg");
		CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
		pMainFrame->ShowIecfgFileDevice(pIecfileDevice);
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("新建设备配置成功."));
		CreateNewIecCfgFrame_FirstIecCfgDatasMngr(pIecfileDevice);
		return;
	}

	CSelectAT02D_CBDlg oSelectDlg;
	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	oSelectDlg.m_pCurSclStation = &pSclFileFrame->m_oSclStation;

	if (oSelectDlg.DoModal() != IDOK)
	{
		return;
	}

//	((CMainFrame*)m_pMainWnd)->CloseAllIecfgDeviceFrame();
// 	m_pAT02D_ConfigDlg->Create(IDD_DLG_AT02D_CFG,NULL);
// 	m_pAT02D_ConfigDlg->ShowWindow(SW_SHOW);
	CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice*)CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
	CSclToIecCfgTool oSclToIecCfgTool;
	CIecCfgDevice *pIecfgDevice = pIecfileDevice->GetIecCfgDevice();
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->GetHead();
	pIecfgDevice->SetSclIed(m_pCurrSelSclIed);
	pIecfgDevice->m_nType = IEC_CFG_DEVICE_USE_TYPE_AT02D;

	if (pIecfgDatasMngr == NULL)
	{
		pIecfgDatasMngr = pIecfgDevice->CreateIecCfgDatasMngr();
	}

	CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
	oSclToIecCfgTool.AttacthSclFileRead(pSclStation);
	oSclToIecCfgTool.AddToIecCfg(&oSelectDlg.m_oSMVList ,&oSelectDlg.m_oGoutList,&oSelectDlg.m_oGinList,pIecfgDatasMngr);
	pIecfgDevice->InitAfterRead();

#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oAT02D_Tool;
	oAT02D_Tool.GenerateAT02D_Iecfg(pIecfgDevice ,oSelectDlg.m_nMaxFiberNum);
#endif

	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	pMainFrame->ShowIecfgFileDevice(pIecfileDevice);
	CreateNewIecCfgFrame_FirstIecCfgDatasMngr(pIecfileDevice);
}

void CIec61850ConfigApp::OnFileNewDevice(CIecCfgFileDevice *pIecfileDevice)
{
	CSclToIecCfgTool oSclToIecCfgTool;
	//CSclIed *pIed = theApp.m_pCurrSelSclIed;
	CIecCfgDevice *pIecfgDevice = pIecfileDevice->GetIecCfgDevice();
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->GetHead();
	pIecfgDevice->SetSclIed(m_pCurrSelSclIed);
	
	if (pIecfgDatasMngr == NULL)
	{
		pIecfgDatasMngr = pIecfgDevice->CreateIecCfgDatasMngr();
	}

	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
	oSclToIecCfgTool.AttacthSclFileRead(pSclStation);
	oSclToIecCfgTool.AddToIecCfg(m_pCurrSelSclIed, pIecfgDatasMngr);
//	pIecfgDevice->m_strIcdFile = pSclStation->GetScdFile();
	pIecfgDevice->InitAfterRead();
}

void CIec61850ConfigApp::OnUpdateFileNewDevice(CCmdUI *pCmdUI)
{
	if (m_pSclFileFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame != m_pSclFileFrame)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if (theApp.m_pCurrSelSclIed == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	pCmdUI->Enable(TRUE);
}

void CIec61850ConfigApp::OnUpdateFileNewDeviceAT02D(CCmdUI *pCmdUI)
{
	if (m_pSclFileFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame != m_pSclFileFrame)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	if (theApp.m_pCurrSelSclIed == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	pCmdUI->Enable(TRUE);
}

CIecCfgFile* CIec61850ConfigApp::OpenIecCfgFileEx(const CString &strFile,BOOL bAutoGenerate)
{
	//打开文件对象
	CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(strFile);//将strFile文件路径下的文件读取，存入pIecCfgFile中；如路径下没有对应文件，返回NULL；

	if (pIecCfgFile == NULL)
	{
		return NULL;
	}

	if (pIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE)//如果打开的文件是按照.ixml配置文件格式存储的，进入将其存储为.ixml文件；
	{
		CIecConfigFrame *pFrame = CreateNewIecCfgFrame(pIecCfgFile);
		CString strFilePostfix = ParseFilePostfix(strFile);
		strFilePostfix.MakeLower();

		if (g_strIecCfgFilePostfix != strFilePostfix)
		{
			CString strTemp = GetPathFileNameFromFilePathName(strFile);
			strTemp = ChangeFilePostfix(strTemp, g_strIecCfgFilePostfix);
			pFrame->SaveAs(strTemp);
		}
	}
	else if (bAutoGenerate)//在此else 中完成智能配置的替换；
	{
		CIecCfgFileDevice *pIecfileDeviceSrc = (CIecCfgFileDevice *)pIecCfgFile;
		CIecCfgDevice *pIecfgDeviceSrc = pIecfileDeviceSrc->GetIecCfgDevice();//配置设备中包含了IED信息和两个配置文件；
		CIecCfgFileDevice pIecfileDeviceNew;
		pIecfileDeviceNew.m_strName = pIecfileDeviceSrc->m_strName;
		pIecfileDeviceNew.m_strID = pIecfileDeviceSrc->m_strID;
		CIecCfgDevice *pIecfgDeviceNew = pIecfileDeviceNew.GetIecCfgDevice();
		pIecfgDeviceNew->m_nType = pIecfgDeviceSrc->m_nType;
		pIecfgDeviceNew->m_strIcdFile = pIecfgDeviceSrc->m_strIcdFile;
		
		CSclToIecCfgTool oSclToIecCfgTool;

		if (theApp.m_pSclFileFrame == NULL)
		{
			return pIecCfgFile;
		}

		CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
		CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
		oSclToIecCfgTool.AttacthSclFileRead(pSclStation);

		CIecCfgDeviceCreater oIecCfgDeviceCreater;
		oIecCfgDeviceCreater.InitCreate(pIecfgDeviceSrc ,pIecfgDeviceNew , &oSclToIecCfgTool,theApp.m_pCurrSelSclIed);

		CExBaseObject *pIecfgDatasMngrSrc = NULL;

		POS posMgr = pIecfgDeviceSrc->GetHeadPosition();

		while (posMgr != NULL)
		{
			pIecfgDatasMngrSrc = pIecfgDeviceSrc->GetNext(posMgr);

			if (pIecfgDatasMngrSrc->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
			{
				oIecCfgDeviceCreater.CreateCIecCfgDatasMngr((CIecCfgDatasMngr*)pIecfgDatasMngrSrc);
			}
		}

		CString strFilePath = strFile;
		CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
		CString strFileName = NULL;
		strFileName = theApp.m_pCurrSelSclIed->m_strName;
		strFileName += _T("_");
		strFileName += theApp.m_pCurrSelSclIed->m_strModel; 
		long nPos = strFilePath.ReverseFind('\\');
		strFilePath = strFilePath.Left(nPos+1);
		strFilePath += strFileName;
		strFilePath += _T("_智能生成.iecfg");
		pIecfileDeviceNew.SaveAs(strFilePath);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能生成配置文件，路径为%s"), strFilePath);

		CIecCfgFile *pIecCfgFileRead = CIecCfgTool::OpenIecFile(strFilePath);
		CIecCfgTool::AdjustIecCfgFile(pIecCfgFileRead);
		pIecCfgFile = pIecCfgFileRead;
	}

	pIecCfgFile->SetModified(FALSE);
	return pIecCfgFile;
}


CIecCfgFile* CIec61850ConfigApp::AutoGeneNewIecfgFile(const CString &strSrcIecfgFile,CString strNewIecfgFile)
{
	CIecCfgFile *pIecCfgFile = CIecCfgTool::OpenIecFile(strSrcIecfgFile);//将strFile文件路径下的文件读取，存入pIecCfgFile中；如路径下没有对应文件，返回NULL；

	if (pIecCfgFile == NULL)
	{
		return NULL;
	}

	if (pIecCfgFile->GetClassID() != IFTCLASSID_CIECCFGFILE)//如果打开的文件是按照.ixml配置文件格式存储的，进入将其存储为.ixml文件；
	{
		return NULL;
	}

	CIecCfgFileDevice *pIecfileDeviceSrc = (CIecCfgFileDevice *)pIecCfgFile;
	CIecCfgDevice *pIecfgDeviceSrc = pIecfileDeviceSrc->GetIecCfgDevice();//配置设备中包含了IED信息和两个配置文件；
	CIecCfgFileDevice oIecfileDeviceNew;
	oIecfileDeviceNew.m_strName = pIecfileDeviceSrc->m_strName;
	oIecfileDeviceNew.m_strID = pIecfileDeviceSrc->m_strID;
	CIecCfgDevice *pIecfgDeviceNew = oIecfileDeviceNew.GetIecCfgDevice();
	pIecfgDeviceNew->m_strIcdFile = pIecfgDeviceSrc->m_strIcdFile;
	pIecfgDeviceNew->m_nType = pIecfgDeviceSrc->m_nType;

	CSclToIecCfgTool oSclToIecCfgTool;

	if (m_pSclFileFrame == NULL)
	{
		return pIecCfgFile;
	}

	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)m_pSclFileFrame;
	CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
	oSclToIecCfgTool.AttacthSclFileRead(pSclStation);

	CIecCfgDeviceCreater oIecCfgDeviceCreater;
	oIecCfgDeviceCreater.InitCreate(pIecfgDeviceSrc ,pIecfgDeviceNew , &oSclToIecCfgTool,theApp.m_pCurrSelSclIed);

	CExBaseObject *pIecfgDatasMngrSrc = NULL;

	POS posMgr = pIecfgDeviceSrc->GetHeadPosition();

	while (posMgr != NULL)
	{
		pIecfgDatasMngrSrc = pIecfgDeviceSrc->GetNext(posMgr);

		if (pIecfgDatasMngrSrc->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			oIecCfgDeviceCreater.CreateCIecCfgDatasMngr((CIecCfgDatasMngr*)pIecfgDatasMngrSrc);
		}
	}

	if (strNewIecfgFile.IsEmpty()||(ParseFilePostfix(strNewIecfgFile) != g_strIecCfgFilePostfix))
	{
		CString strFileName;
		strFileName = theApp.m_pCurrSelSclIed->m_strName;
		strFileName += _T("_");
		strFileName += theApp.m_pCurrSelSclIed->m_strModel; 

		long nPos = strSrcIecfgFile.ReverseFind('\\');
		strNewIecfgFile = strSrcIecfgFile.Left(nPos+1);
		strNewIecfgFile += strFileName;
		strNewIecfgFile += _T("_智能生成.iecfg");	
	}

	oIecfileDeviceNew.SaveAs(strNewIecfgFile);
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("智能生成配置文件，路径为%s"), strNewIecfgFile);
	CIecCfgFile *pIecCfgFileRead = CIecCfgTool::OpenIecFile(strNewIecfgFile);
	CIecCfgTool::AdjustIecCfgFile(pIecCfgFileRead);
	pIecCfgFileRead->SetModified(FALSE);
	return pIecCfgFileRead;
}

void CIec61850ConfigApp::OpenLastFiles()
{
	CIecCfgFiles *pIecFiles = CIecCfgTool::GetIecCfgFiles();
	ASSERT (pIecFiles != NULL);

	if (pIecFiles == NULL)
	{
		return ;
	}

	POS pos = pIecFiles->GetHeadPosition();
	CIecCfgFile *pIecCfgFile = NULL;
	CIecCfgFile *pIecCfgFileDevice = NULL;

	while (pos != NULL)
	{
		pIecCfgFile = (CIecCfgFile *)pIecFiles->GetNext(pos);

		if (pIecCfgFile->Open())
		{
			if (pIecCfgFile->GetClassID() == IFTCLASSID_CIECCFGFILE)
			{
				CreateNewIecCfgFrame(pIecCfgFile);
			}
			else
			{
				pIecCfgFileDevice = pIecCfgFile;
			}				

			pIecCfgFile->SetModified(FALSE);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoneConfigFile /*_T("配置文件【%s】不存在")*/, pIecCfgFile->m_strID);
			pIecFiles->Delete(pIecCfgFile);
		}
	}

	CreateNewIecCfgDeviceFrame(pIecCfgFileDevice);
}

void CIec61850ConfigApp::OnFileOpen()
{
	
}

void CIec61850ConfigApp::OnFileOpenSclHis()
{
	if (m_pSclFileFrame != NULL)
	{
		m_pSclFileFrame->ActivateFrame(1);
		return;
	}

	CSclFileHistoryDlg dlg;

	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	if (dlg.m_strSclFile.GetLength() == 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_NoneSclFile/*_T("没有选择SCL文件")*/);
		return; 
	}

	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();
	ASSERT(pSclFiles != NULL);
	CSclFile *pSclFile = pSclFiles->Open(dlg.m_strSclFile);
	CreateNewSclFrame(pSclFile);
}

void CIec61850ConfigApp::OnFileOpenSclHisAT02D()
{
	OnFileOpenSclHis();
}

void CIec61850ConfigApp::OnFileOpenScl()
{
	if (m_pSclFileFrame != NULL)
	{
		m_pSclFileFrame->ActivateFrame(1);
		return;
	}

	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();
	ASSERT(pSclFiles != NULL);

	CSclFile *pSclFile = pSclFiles->Open();

	if (pSclFile == NULL)
	{
		return;
	}

	CreateNewSclFrame(pSclFile);
}

void CIec61850ConfigApp::OnFileOpenSclAT02D()
{
	OnFileOpenScl();
}

BOOL CIec61850ConfigApp::OpenSclFile(const CString &strScdFilePath)
{
	if (m_pSclFileFrame != NULL)
	{
		m_pSclFileFrame->ActivateFrame(1);
		return 0;
	}

	CSclFiles *pSclFiles = CIecCfgTool::GetSclFiles();
	ASSERT(pSclFiles != NULL);

	CSclFile *pSclFile = pSclFiles->Open(strScdFilePath);

	if (pSclFile == NULL)
	{
		return 0;
	}

	CreateNewSclFrame(pSclFile);
	return 1;
}

long CIec61850ConfigApp::ExportPNI302IecfgFile(const CString &strDesIecfgPath,const CString &strCbXml)
{
	CSclCtrlsSmvOut oSMVListRef;
//	CSclCtrlsGsIn oGinListRef;
	CSclCtrlsGsOut oGoutListRef;

	if (m_pSclFileFrame == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("未打开SCD文件,无法从scd中提取配置文件."));
		return 0;
	}

	CSclFileFrame *pSclFileFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;
	pSclFileFrame->m_oSclStation.GetAll92Ref(&oSMVListRef);
//	pSclFileFrame->m_oSclStation.GetAllGinRef(&oGinListRef);
	pSclFileFrame->m_oSclStation.GetAllGoutRef(&oGoutListRef);

	CDvmDataset oDvmDataset;
// 	CString strTmp;
// 	strTmp = _T("D:\\PNI302_rst.xml");
 
//  	oDvmDataset.OpenXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);

	oDvmDataset.SetXml(strCbXml.AllocSysString(),CDataMngrXmlRWKeys::g_pXmlKeys);
//	oDvmDataset.SaveXmlFile(strTmp,CDataMngrXmlRWKeys::g_pXmlKeys);


	long nRet = 0;
	CExBaseObject *pCurDataObj = NULL;
	CDvmData *pCurData = NULL;
	CDvmValue *pCurValue = NULL;
	POS pos_obj = oDvmDataset.GetHeadPosition();
	CString strAppID,/*strDesMac,*/strIecType;
	long nFiberIndex = 0;
	CSclCtrlBase* pSclCtrlBase = NULL;
	CSclCtrlsSmvOut oSMVListRefNew;
	CSclCtrlsGsIn oGinListRefNew;
	CSclCtrlsGsOut oGoutListRefNew;

	while(pos_obj)
	{
		pCurDataObj = oDvmDataset.GetNext(pos_obj);

		if (pCurDataObj->m_strID.Find(_T("CB")) == 0)
		{
			pCurData = (CDvmData *)pCurDataObj;
			pCurValue = (CDvmValue*)pCurData->FindByID("AppID");

			if (pCurValue == NULL)
				continue;

			strAppID = pCurValue->m_strValue;
// 			pCurValue = (CDvmValue*)pCurData->FindByID("DestMac");
// 
// 			if (pCurValue == NULL)
// 				continue;
// 
// 			strDesMac = pCurValue->m_strValue;
			pCurValue = (CDvmValue*)pCurData->FindByID("IecType");

			if (pCurValue == NULL)
				continue;

			strIecType = pCurValue->m_strValue;
			pCurValue = (CDvmValue*)pCurData->FindByID("FiberIndex");

			if (pCurValue == NULL)
				continue;

			nFiberIndex = CString_To_long(pCurValue->m_strValue);
			strIecType.MakeUpper();
//			strDesMac.MakeUpper();

			if (strIecType == _T("9-2"))
			{
				pSclCtrlBase = oSMVListRef.FindSclCtrlByAppID_DesMac(strAppID/*,strDesMac*/);

				if (pSclCtrlBase != NULL)
				{
					oSMVListRefNew.AddTail(pSclCtrlBase);
					pSclCtrlBase->m_dwReserved = nFiberIndex;
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("9-2控制块[%s]添加成功."),strAppID);
				}
				else
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("9-2控制块[%s]未找到."),strAppID);
				}
			}
			else if (strIecType == _T("GOOSE"))
			{
				pSclCtrlBase = oGoutListRef.FindSclCtrlByAppID_DesMac(strAppID/*,strDesMac*/);

				if (pSclCtrlBase != NULL)
				{
					oGoutListRefNew.AddTail(pSclCtrlBase);
					pSclCtrlBase->m_dwReserved = nFiberIndex;
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("GOOSE控制块[%s]添加成功."),strAppID);
				}
				else
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GOOSE控制块[%s]未找到."),strAppID);
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("IecType=%s,不存在."),strIecType);
			}
		}
	}

	CIecCfgFileDevice *pIecfileDevice = (CIecCfgFileDevice*)CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);
	CSclToIecCfgTool oSclToIecCfgTool;
	CIecCfgDevice *pIecfgDevice = pIecfileDevice->GetIecCfgDevice();
	CIecCfgDatasMngr *pIecfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->GetHead();
	pIecfgDevice->SetSclIed(m_pCurrSelSclIed);

	if (pIecfgDatasMngr == NULL)
	{
		pIecfgDatasMngr = pIecfgDevice->CreateIecCfgDatasMngr();
	}

	CSclStation *pSclStation = &pSclFileFrame->m_oSclStation;
	oSclToIecCfgTool.AttacthSclFileRead(pSclStation);
	oSclToIecCfgTool.AddToIecCfg(&oSMVListRefNew ,&oGoutListRefNew,&oGinListRefNew,pIecfgDatasMngr);
	pIecfgDevice->InitAfterRead();

	oSMVListRef.RemoveAll();
//	oGinListRef.RemoveAll();
	oSMVListRefNew.RemoveAll();
	oGinListRefNew.RemoveAll();
	oGoutListRefNew.RemoveAll();
	oGoutListRef.RemoveAll();

	pIecfgDevice->SaveAsIecCfgFile(strDesIecfgPath,TRUE);
	CString strDevModelPath,strPNI302CfgPath;
	strDevModelPath = ChangeFilePostfix(strDesIecfgPath,_T("xml"));
	strPNI302CfgPath = _P_GetConfigPath();
	strPNI302CfgPath.Append(_T("\\AT02D_Config.xml"));

#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oAT02DTool;
	oAT02DTool.ExportDeviceModel(pIecfgDevice,strPNI302CfgPath,strDevModelPath,TRUE);
#endif

	return TRUE;
}

void CIec61850ConfigApp::CreateNewSclFrame(CSclFile *pSclFile)
{
	CFrameWnd *pFrameWnd = pSclFile->GetRefFrameWnd();
	CSclFileFrame *pSclFileFrame = NULL;

	if (pFrameWnd != NULL)
	{
		ASSERT (pFrameWnd->IsKindOf(RUNTIME_CLASS(CSclFileFrame)) );
		pSclFileFrame = (CSclFileFrame*)pFrameWnd;
		pSclFileFrame->ActivateFrame(1);
		return;
	}

	CMDIChildWndEx *pFrame;
	CView *pView = NULL;

	OpenDocTemplate(m_pSclFileDocTemplate, &pView, &pFrame);//在此函数中，读取SCD文件；在CSclFileTreeView::OnTimer函数实现读取，用ReadSclFile函数具体实现
	CSclFileDoc *pDoc = (CSclFileDoc*)pView->GetDocument();
	pDoc->SetTitle(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclFile/*_T("SCL文件")*/);
	pSclFileFrame = (CSclFileFrame*)pFrame;
	pSclFileFrame->m_pSclFile = pSclFile;
	pDoc->UpdateAllViews(NULL, (LPARAM)pSclFile, NULL);
	pDoc->SetTitle(pSclFile->m_strName);
	m_pSclFileFrame = pFrame;
}

void CIec61850ConfigApp::OpenTscdFile(const CString &strTscdFile)
{
	if (!IsFileExist(strTscdFile))
	{
		return;
	}

	SetCfgInStationTest();
	CSclFileFrame *pSclFrame = (CSclFileFrame*)m_pSclFileFrame;

	if (pSclFrame != NULL)
	{
		pSclFrame->ActivateFrame(1);
		pSclFrame->OpenTscdFile(strTscdFile);
		return;
	}

	CMDIChildWndEx *pFrame;
	CView *pView = NULL;
	OpenDocTemplate(m_pSclFileDocTemplate, &pView, &pFrame);
	CSclFileDoc *pDoc = (CSclFileDoc*)pView->GetDocument();
	pDoc->SetTitle(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclFile/*_T("SCL文件")*/);
	pSclFrame = (CSclFileFrame*)pFrame;
	CString strTitle, strPath;
	strTitle = strTscdFile;
	strPath = _P_GetSystemPath();
	strTitle.MakeLower();
	strPath.MakeLower();
	strTitle.Replace(strPath, _T(""));

	pDoc->SetTitle(strTitle);
	m_pSclFileFrame = pSclFrame;
	pSclFrame->OpenTscdFile(strTscdFile);
}

void CIec61850ConfigApp::CloseSclFileFrame()
{
	if (m_pSclFileFrame == NULL)
	{
		return;
	}

	CSclFileFrame *pSclFrame = (CSclFileFrame*)m_pSclFileFrame;
	pSclFrame->CloseSclFileFrame();

}

void CIec61850ConfigApp::CreateNewSclFrame(const CString &strTscdFile, const CString &strIedId)
{
	if (!IsFileExist(strTscdFile))
	{
		return;
	}

	OpenTscdFile(strTscdFile);
	CSclFileFrame *pSclFrame = (CSclFileFrame*)m_pSclFileFrame;

	if (pSclFrame == NULL)
	{
		return;
	}

	pSclFrame->OnShowCurIED(strIedId);
}

void CIec61850ConfigApp::CreateNewStateFrame()
{
	if (m_pStateToolFrame != NULL)
	{
		m_pStateToolFrame->ActivateFrame(1);
		return;
	}

	CMDIChildWndEx *pFrame;
	CView *pView = NULL;

	OpenDocTemplate(m_pStateDocTemplate, &pView, &pFrame);
	CStateToolDoc *pDoc = (CStateToolDoc*)pView->GetDocument();
	pDoc->SetTitle(CXLanguageResourceIec_61850Cfg::g_sLangTxt_SclStateTool/*_T("SCL状态序列工具")*/);
	m_pStateToolFrame = (CStateToolFrame*)pFrame;
	pDoc->UpdateAllViews(NULL, (LPARAM)0, NULL);
	m_pStateToolFrame = pFrame;
}

int CIec61850ConfigApp::ExitInstance()
{
	CIecCfgTool::Release();
	CIecCfgToolXmlRWKeys::Release();
	CCfgDataMngrXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CCfgDataMngrConstGlobal::Release();
	CFilterTextXmlRWKeys::Release();
	//CTestMacroConfigs::Release();
	CTestMacroXmlRWKeys::Release();
	CXScdDrawConstGlobal::Release();
	CXAtsSysSvrClient::UnRegisterModule();
	CXAtsSysSvrClient::Release();

	ReleaseDownIecCfgFileLib();
	ReleaseMacroTestEngine();
	ReleaseSingleAppMutex();

	CXLanguageXmlRWKeys::Release();
	CXLanguageMngr::Release();
	Yun_Free();


	return CWinAppEx::ExitInstance();
}

void CIec61850ConfigApp::SaveIecfg(CExBaseObject *pIecfg)
{
// 	if (pIecfg->GetClassID() == CFGCLASSID_CIECCFGDEVICE)
// 	{
// 		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecfg->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
// 
// 		if (pIecCfgFileDevice != NULL)
// 		{
// 			pIecCfgFileDevice->Save();
// 		}
// 	}
	SaveIecfgFile((CIecCfgFile*)pIecfg, NULL);
//	PostFinishMsg_ExternExc((CIecCfgFile*)pIecfg);
}

void CIec61850ConfigApp::PostFinishMsg_ExternExc(CIecCfgFile *pIecCfgFile)
{
	if ((pIecCfgFile == NULL)||(!IsRunAutomaition()))
	{
//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("文件对象为空,或者非自动测试模式,无法给外部发送消息."));
		return;
	}

	CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pIecCfgFileDevice == NULL)
	{
		PostMsg_TestEngineFinish(pIecCfgFile->m_strID);
	}
	else
	{
		PostMsg_TestEngineFinish(pIecCfgFileDevice->m_strID);
	}
}

BOOL CIec61850ConfigApp::SaveIecfgFile(CIecCfgFile *pIecCfgFile, CDocument *pDoc,BOOL bIsAT02D_CFG)
{
	CExBaseObject *pAncestor = (CExBaseObject*)pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
	BOOL bRet = FALSE;

	if (pAncestor == NULL)
	{
		//已经有文件路径
		if (pIecCfgFile->m_strID.GetLength() > 8)
		{
			bRet = pIecCfgFile->Save(bIsAT02D_CFG);
		}
		else
		{
			bRet = (SaveAsIecfgFile(pIecCfgFile, pDoc,bIsAT02D_CFG));
		}
	}
	else
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pAncestor;

		if (pIecCfgFileDevice->m_strID.GetLength() > 8)
		{
			bRet = pIecCfgFileDevice->Save(bIsAT02D_CFG);
		}
		else
		{
			bRet = (SaveAsIecfgFile(pIecCfgFile, pDoc,bIsAT02D_CFG));
		}
	}

	if ((bRet)&&(g_nEngineDispMode == _DISP_MODE_PNI302))
	{
		CString strDeviceModelPath;
		ASSERT(pAncestor);
		strDeviceModelPath = ChangeFilePostfix(pAncestor->m_strID,_T("xml"));
		ExportDeviceModelFile_AT02D(strDeviceModelPath);
	}

	if ((bRet)&&g_bSendTestFinished)
	{
		PostFinishMsg_ExternExc(pIecCfgFile);
	}

	if (bRet)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("配置文件保存成功."));
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR,_T("配置文件保存失败."));
	}

	return bRet;
}

BOOL CIec61850ConfigApp::SaveAsIecfgFile(CIecCfgFile *pIecCfgFile, CDocument *pDoc,BOOL bIsAT02D_CFG)
{
	CExBaseObject *pAncestor = (CExBaseObject*)pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	CXFileSaveAsDlg dlg(m_pMainWnd);

	if (bIsAT02D_CFG)//如果是AT02D配置,默认保存为该名称
	{
		pIecCfgFile->m_strName = _T("AT02D");
	}

	dlg.m_strXFile = pIecCfgFile->m_strName;
	CXFileMngr *pXFileMngr = NULL;
	CString strFilePostFix;

	if (pAncestor == NULL)
	{
		pXFileMngr = CIecCfgTool::GetIecCfgFileMngr();
		strFilePostFix = g_strIecCfgFilePostfix;
	}
	else
	{
		pXFileMngr = CIecCfgTool::GetIecCfgDeviceFileMngr();
		strFilePostFix = g_strDeviceIecCfgFilePostfix;
	}

	if (g_nEngineDispMode == _DISP_MODE_PN466)
	{
		CString strFile;

		if (!PopupSaveAsFileDialog(m_pMainWnd, strFile, _T("IEC61850配置文件|*.ixml||"), _T("ixml")))
		{
			return FALSE;
		}

		if (pIecCfgFile->m_pIecCfgDatasMngr != NULL)
		{
			pIecCfgFile->m_pIecCfgDatasMngr->SaveAsIecCfgFile(strFile);
		}

		return FALSE;
	}
	else
	{
		dlg.m_pXFileMngr = pXFileMngr;
		dlg.m_strXFilePostFix = strFilePostFix;

		if (dlg.DoModal() != IDOK)
		{
			return FALSE;
		}

		CXFolder *pXCurrFolder = dlg.m_pCurrSelFolder;

		//保存
		pIecCfgFile->SaveAs(dlg.m_strXFilePath,bIsAT02D_CFG);
		CXFile *pXFile = pXCurrFolder->AddFile2(GetPathFileNameFromFilePathName(dlg.m_strXFilePath));

		//更新界面
		CXFolderTreeCtrl *pTreeCtrl = (CXFolderTreeCtrl*)pXFileMngr->GetRefTreeCtrl();
		ASSERT(pTreeCtrl != NULL);
		pTreeCtrl->Insert(pXFile);
	}

	if (pDoc != NULL)
	{
		pDoc->SetTitle(pIecCfgFile->m_strName);
	}

	theApp.ShowIecCfgFileTitleToStatusBar(pIecCfgFile);

	CIecCfgTool::AdjustIecCfgFile(pIecCfgFile);
	PostFinishMsg_ExternExc((CIecCfgFileDevice *)pIecCfgFile);
	return TRUE;
//	return pXFile;
}

BOOL CIec61850ConfigApp::SaveIecfgFile(const CString &strIecfgFile)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame == NULL)
	{
		return FALSE;
	}

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return FALSE;
	}

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	CIecCfgFile *pIecCfgFile = pIecConfigFrame->m_pIecCfgFile;
	pIecCfgFile->m_strID = strIecfgFile;
	SaveIecfgFile(pIecCfgFile, pIecConfigFrame->m_pDocument);
	return TRUE;
}

void CIec61850ConfigApp::OnFileSave()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return;
	}

	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;

	if (g_nEngineDispMode == _DISP_MODE_PNI302)
	{
		ASSERT(pIecConfigFrame->m_pIecCfgFile);
		CExBaseObject *pAncestor = (CExBaseObject*)pIecConfigFrame->m_pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
		pAncestor->m_strID = _P_GetTemplatePath();
		pAncestor->m_strName = _T("PNI302_Config.iecfg");
		pAncestor->m_strID.Append(pAncestor->m_strName);

		if (pIecConfigFrame->Save(TRUE))
		{
			m_pMainWnd->ShowWindow(SW_HIDE);
//			AfxMessageBox(_T("配置文件及模型生成成功."),MB_OK);
		}
		else
		{
			AfxMessageBox(_T("配置文件及模型生成失败."),MB_OK);
		}
	} 
	else
	{
		pIecConfigFrame->Save();
	}
}

void CIec61850ConfigApp::OnSendConfig()
{
	g_bSendTestFinished = TRUE;
	OnFileSave();
}

void CIec61850ConfigApp::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
	pCmdUI->Enable(b);
}

void CIec61850ConfigApp::OnUpdateSendConfig(CCmdUI *pCmdUI)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
	pCmdUI->Enable(b);
}

void CIec61850ConfigApp::OnFileSaveAs()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return;
	}

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	pIecConfigFrame->SaveAs();
	UpdateIecCfgFilesComboBox();
}

void CIec61850ConfigApp::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	OnUpdateFileSave(pCmdUI);
}

void CIec61850ConfigApp::OnFileSaveAT02D()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return;
	}

	// 	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgFileMngr();
	// 	CXFolder *pFolder = pFileMngr->GetCurrFolder();
	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	pIecConfigFrame->Save(TRUE);
}

void CIec61850ConfigApp::OnUpdateFileSaveAT02D(CCmdUI *pCmdUI)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
	pCmdUI->Enable(b);
}

void CIec61850ConfigApp::OnExportDevModel()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return;
	}

	CString strSaveFilePath;
	strSaveFilePath = _P_GetTemplatePath();

	if (!PopupSaveAsFileDialog(m_pMainWnd, strSaveFilePath, _T("AT02D设备数据文件|*.xml||"), _T("xml")))
	{
		return;
	}

	ExportDeviceModelFile_AT02D(strSaveFilePath);
}

BOOL CIec61850ConfigApp::ExportDeviceModelFile_AT02D(const CString &strFilePath)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return FALSE;
	}

	CDvmDevice oDvmDevice;
	CString strAT02D_CfgPath;
	strAT02D_CfgPath = _P_GetConfigPath();
	strAT02D_CfgPath.Append(_T("AT02D_Config.xml"));

#ifdef _USE_IN_AT02D_MODE_
	CAT02D_Tool oAT02D_Tool;
	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	CIecCfgFile *pIecCfgFile = pIecConfigFrame->m_pIecCfgFile;

	CExBaseObject *pAncestor = (CExBaseObject *)pIecCfgFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pAncestor != NULL)
	{
		CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pAncestor;
		CIecCfgDevice *pIecCfgDevice = pIecCfgFileDevice->GetIecCfgDevice();
		oAT02D_Tool.ExportDeviceModel(pIecCfgDevice,strAT02D_CfgPath,strFilePath,CIecCfgTool::IsModelUseHarm());
	} 
	else
	{
		oAT02D_Tool.ExportDeviceModel(pIecCfgFile->m_pIecCfgDatasMngr,strAT02D_CfgPath,strFilePath,CIecCfgTool::IsModelUseHarm());
	}
#endif
	
	return TRUE;
}

void CIec61850ConfigApp::OnUpdateExportDevModel(CCmdUI *pCmdUI)
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (pFrame == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	BOOL b = pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame));
	pCmdUI->Enable(b);
}

void CIec61850ConfigApp::OnFileSaveAsAT02D()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrame = pMainFrame->GetActiveFrame();

	if (!pFrame->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)))
	{
		return;
	}

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrame;
	pIecConfigFrame->SaveAs(TRUE);
	UpdateIecCfgFilesComboBox();
}

void CIec61850ConfigApp::OnUpdateFileSaveAsAT02D(CCmdUI *pCmdUI)
{
	OnUpdateFileSave(pCmdUI);
}

void CIec61850ConfigApp::UpdateIecCfgFilesComboBox()
{
	if (m_pSclFileFrame == NULL)
	{
		return;
	}

	((CSclFileFrame*)m_pSclFileFrame)->UpdateIecCfgFilesComboBox();
}

BOOL CIec61850ConfigApp::IsIn_EReport_Path()
{
	CString strSoft;

	strSoft = _P_GetSystemSoftName();
	strSoft.MakeLower();

	return (strSoft == _T("e-report"));
}

void CIec61850ConfigApp::OnFileUseIeccfgfile()
{
	if (IsIn_EReport_Path())
	{
		DownIecCfgFile();
	}
	else
	{
		UseIeccfgfile();
	}
}

void CIec61850ConfigApp::UseIeccfgfile()
{
	BOOL bReturn = TRUE;

	if (!HasLoadDownIecCfgFileLib())
	{
		bReturn = LoadDownIecCfgFileLib(CIecCfgTool::GetIecCfgDownDllFile());
	}

	if (!bReturn)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_NonePowerTestIecPara /*_T("未配置PowerTest IEC参数！")*/);
		return;
	}

	CString strFile = GetCurrEditIecCfgFile();
	iecfg_DownCfgFile(strFile);
}

CString CIec61850ConfigApp::GetCurrEditIecCfgFile()
{
	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrameWnd = pMainFrame->GetActiveFrame();

	ASSERT (pFrameWnd->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)));

	CIecConfigFrame *pIecConfigFrame = (CIecConfigFrame*)pFrameWnd;

	return pIecConfigFrame->m_pIecCfgFile->m_strID;
}

void CIec61850ConfigApp::OnUpdateFileUseIeccfgfile(CCmdUI *pCmdUI)
{
	if (m_bIsNowTesting)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CMainFrame *pMainFrame = (CMainFrame*)m_pMainWnd;
	CFrameWnd *pFrameWnd = pMainFrame->GetActiveFrame();

	if (pFrameWnd == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	pCmdUI->Enable(pFrameWnd->IsKindOf(RUNTIME_CLASS(CIecConfigFrame)));
}

//////////////////////////////////////////////////////////////////////////

MacroTest::IMacroTestEngine CIec61850ConfigApp::GetMacroTestEngine(const CString &strProgID)
{
	CString strActiveMacroTestEngineProgID = strProgID;
	//strActiveMacroTestEngineProgID = CTestMacroConfigs::GetActiveMcroTestEngineProgID();

	if (m_pMacroTestEngine == NULL)
	{
		m_pMacroTestEngine.CreateDispatch(strActiveMacroTestEngineProgID);

		if (m_pMacroTestEngine == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTestModuleFail/*_T("创建测试组件失败")*/);
		}
	}

	return m_pMacroTestEngine;
}

void CIec61850ConfigApp::ReleaseMacroTestEngine()
{
	try
	{
		if (m_oMacroTest != NULL)
		{
			m_oMacroTest.CloseDevice();
			m_oMacroTest = NULL;
		}
	}
	catch (...)
	{

	}

	try
	{
		if (m_pMacroTestEngine != NULL)
		{
			m_pMacroTestEngine.ExitEngine();
		}
	}
	catch (...)
	{
	}

	m_pMacroTestEngine = NULL;
}


//创建PMTest组件
void CIec61850ConfigApp::CreateMacroTestInterface(const CString &strProgID)
{
	if (m_oMacroTest != NULL)
	{
		BOOL bTrue = TRUE;

		try
		{
			m_oMacroTest.SetWndMsg((long)m_pMainWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch (...)
		{
			bTrue = FALSE;
		}

		if (bTrue)
		{
			return;
		}
		else
		{
			m_oMacroTest = NULL;
		}
	}

	MacroTest::IMacroTestEngine pMacroTestEngine = GetMacroTestEngine(strProgID);

	if (pMacroTestEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterMngrModuleFail/*_T("创建测试仪管理组件失败")*/);
		return;
	}

	//创建底层测试接口
	try
	{
		m_oMacroTest = pMacroTestEngine.CreateMacroTest(_T(""));
	}
	catch (...)
	{
		ReleaseMacroTestEngine();
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleAbn/*_T("创建测试仪通讯组件出现异常")*/);
		return;
	}

	if(m_oMacroTest != NULL)
	{
		try
		{
			m_oMacroTest.SetWndMsg((long)m_pMainWnd->GetSafeHwnd(), WM_ELECTRIC_TEST);
		}
		catch(...)
		{
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_CreateTesterCmmModuleFail/*_T("创建测试仪通讯组件失败")*/);
	}

}

void CIec61850ConfigApp::DownIecCfgFile()
{
	CString strIecCfgFile = GetCurrEditIecCfgFile();
	CreateMacroTestInterface(_T("PonovoVm.TestEngine"));

	if(m_oMacroTest == NULL)
	{
		return;
	}

	CString strMacroID = _T("IECConfig");
	CString strTestPara;
	strTestPara.Format(_T("_IecCfgFile=%s;"), GetCurrEditIecCfgFile());
	DWORD nRet = 0;
	try
	{
		nRet = m_oMacroTest.Test(strMacroID,strTestPara); 
		m_bIsNowTesting = TRUE;
	}
	catch(...)
	{
		m_bIsNowTesting = FALSE;
	}

	//如果连接成功，测试试验中的项目
	if ( (nRet & 0xF0000000) != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DownloadConfigFileErr/*_T("下载配置文件错误，错误号：0X%08X")*/, nRet);
	}
}


void CIec61850ConfigApp::TestStateTool()
{
	CreateMacroTestInterface(_T("PonovoVm.TestEngine"));

	if(m_oMacroTest == NULL)
	{
		return;
	}

	CStateToolFrame *pFrame = (CStateToolFrame *)m_pStateToolFrame;
	CString strMacroID = _T("State6U6I");
	CString strTestPara;
	pFrame->GetTestPara(strTestPara);
	DWORD nRet = 0;

	try
	{
		nRet = m_oMacroTest.Test(strMacroID,strTestPara); 
		m_bIsNowTesting = TRUE;
	}
	catch(...)
	{
		m_bIsNowTesting = FALSE;
	}

	//如果连接成功，测试试验中的项目
	if ( (nRet & 0xF0000000) != 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_DownloadConfigFileErr/*_T("下载配置文件错误，错误号：0X%08X")*/, nRet);
	}
}

//底层功能组件消息处理函数
LRESULT CIec61850ConfigApp::OnElectricTestMsg(WPARAM wParam, LPARAM lParam)
{
	long nEvent = wParam;

// 	switch (nEvent)
// 	{
// 	case MacroTest::MTMSG_ConnectSuccess : //0,
// 		CLogPrint::LogString(XLOGLEVEL_TRACE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_TesterLinkSucc /*_T("测试仪联机成功")*/);
// 		break;
// 
// 	case MacroTest::MTMSG_ConnectFaild : //1,
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_LinkFail/*_T("联机失败")*/);
// 		m_bIsNowTesting = FALSE;
// 		break;
// 
// 	case MacroTest::MTMSG_ConnectConfig : //2,
// 		break;
// 
// 	case MacroTest::MTMSG_TestBegin : //3,
// 		break;
// 
// 	case MacroTest::MTMSG_TestFinished : //4, 
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_RecevElectricalTestEndMsg/*_T("收到电气量测试结束消息！")*/);
// 		m_bIsNowTesting = FALSE;
// 		break;
// 
// 	case MacroTest::MTMSG_CommError : //5,
// 		CLogPrint::LogString(XLOGLEVEL_TRACE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_DownloadConfigFileErr /*_T("参数下载失败")*/);
// 		m_bIsNowTesting = FALSE;
// 		break;
// 
// 	case MacroTest::MTMSG_Not_Surport : //6,
// 		{
// 			CLogPrint::LogString(XLOGLEVEL_TRACE,CXLanguageResourceIec_61850Cfg::g_sLangTxt_TesterInterfNoIed61850ConfigFunc /*_T("测试仪器底层功能接口不支持下载Iec61850配置测试功能")*/);
// 		}
// 
// 		break;
// 
// 	case MacroTest::MTMSG_ManualTestBegin : //7,
// 		break;
// 
// 	case MacroTest::MTMSG_ManualTestReturn : //8,
// 		break;
// 
// 	case MacroTest::MTMSG_ManualTestStop : //9,
// 		break;
// 
// 	case MacroTest::MTMSG_ShowCurItem : //10
// 		break;
// 
// 	case MacroTest::MTMSG_TestOverTime : 
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, CXLanguageResourceIec_61850Cfg::g_sLangTxt_TesterTestFuncOvertime/*_T("测试仪器底层测试功能测试超时")*/);
// 		m_bIsNowTesting = FALSE;
// 		break;
// 
// 	default:
// 		break;
// 	}

	DWORD dwEnd = ::GetTickCount();

	return 0;
}

BOOL CIec61850ConfigApp::IsNowTesting()
{
	return m_bIsNowTesting;
}


void CIec61850ConfigApp::OnFileStateTool()
{
	CreateNewStateFrame();
}

void CIec61850ConfigApp::OnUpdateFileStateTool(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_pStateToolFrame == NULL);
}

void CIec61850ConfigApp::OnFileStateStarttest()
{
	TestStateTool();
}

void CIec61850ConfigApp::OnUpdateFileStateStarttest(CCmdUI *pCmdUI)
{
	BOOL bEnable = TRUE;

	if (m_pStateToolFrame == NULL)
	{
		bEnable = FALSE;
	}

	if (IsNowTesting())
	{
		bEnable = FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CIec61850ConfigApp::OnFileStateStoptest()
{
	// TODO: 在此添加命令处理程序代码
}

void CIec61850ConfigApp::OnUpdateFileStateStoptest(CCmdUI *pCmdUI)
{
	BOOL bEnable = TRUE;

	if (m_pStateToolFrame == NULL)
	{
		bEnable = FALSE;
	}

	if (IsNowTesting())
	{
		
	}
	else
	{
		bEnable = FALSE;
	}

	pCmdUI->Enable(bEnable);
}

void CIec61850ConfigApp::OnViewIeccfgUsedin()
{
	CIecCfgTool::SetViewOnlyUsedInChs();
	CCfgDataMngrConstGlobal::SetViewOnlyUsedInChs(CIecCfgTool::IsViewOnlyUsedInChs());
	CXScdDrawConstGlobal::SetOnlyShowUsedSvOutChs(CIecCfgTool::IsViewOnlyUsedInChs());
	CXScdDrawConstGlobal::SetOnlyShowUsedGsOutChs(CIecCfgTool::IsViewOnlyUsedInChs());

	CIecCfgFiles *pIecCfgFiles = CIecCfgTool::GetIecCfgFiles();
	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;
	CFrameWnd *pFrameWnd = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);

		if (pFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
		{
			CIecCfgFileDevice *pFileDevice = (CIecCfgFileDevice*)pFile;
			CExBaseList *pList = pFileDevice->GetListIecfgFile();
			POS posFile = pList->GetHeadPosition();
			CIecCfgFile *p = NULL;

			while (posFile != NULL)
			{
				p = (CIecCfgFile *)pList->GetNext(posFile);
				pFrameWnd = p->GetRefFrameWnd();

				if (pFrameWnd != NULL)
				{
					pFrameWnd->PostMessage(WM_VIEW_IECCFG_ONLY_USEDIN);
				}
			}
		}
		else
		{
			pFrameWnd = pFile->GetRefFrameWnd();

			if (pFrameWnd != NULL)
			{
				pFrameWnd->PostMessage(WM_VIEW_IECCFG_ONLY_USEDIN);
			}
		}
	}
}

void CIec61850ConfigApp::OnUpdateViewIeccfgUsedin(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::IsViewOnlyUsedInChs());
}

void CIec61850ConfigApp::OnViewChPath()
{
	CIecCfgTool::SetViewChsPath();

	CIecCfgFiles *pIecCfgFiles = CIecCfgTool::GetIecCfgFiles();
	POS pos = pIecCfgFiles->GetHeadPosition();
	CIecCfgFile *pFile = NULL;
	CFrameWnd *pFrameWnd = NULL;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)pIecCfgFiles->GetNext(pos);

		if (pFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
		{
			CIecCfgFileDevice *pFileDevice = (CIecCfgFileDevice*)pFile;
			CExBaseList *pList = pFileDevice->GetListIecfgFile();
			POS posFile = pList->GetHeadPosition();
			CIecCfgFile *p = NULL;

			while (posFile != NULL)
			{
				p = (CIecCfgFile *)pList->GetNext(posFile);
				pFrameWnd = p->GetRefFrameWnd();

				if (pFrameWnd != NULL)
				{
					pFrameWnd->PostMessage(WM_VIEW_IECCFG_UPDATE_CHS_GRID);
				}
			}
		}
		else
		{
			pFrameWnd = pFile->GetRefFrameWnd();

			if (pFrameWnd != NULL)
			{
				pFrameWnd->PostMessage(WM_VIEW_IECCFG_UPDATE_CHS_GRID);
			}
		}
	}
}

void CIec61850ConfigApp::OnUpdateViewChPath(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CIecCfgTool::IsViewChsPath());
}

BOOL CIec61850ConfigApp::PreTranslateMessage(MSG* pMsg)
{
	if (CXSplashWndBase::PreTranslateAppMessage(pMsg))
		return TRUE;

	return CWinAppEx::PreTranslateMessage(pMsg);
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CIec61850ConfigApp::SetDispMode(long nDispMode)
{
	if ((nDispMode<_DISP_MODE_NORMAL)||(nDispMode>_DISP_MODE_PN466))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SetDispMode函数参数值【%ld】无效."), nDispMode);
		return;
	}

	if (g_nEngineDispMode != nDispMode)
	{
		if (nDispMode == _DISP_MODE_PN466)
		{
			g_bSendTestFinished = FALSE;
		}

		g_nEngineDispMode = nDispMode;

		if (m_pMainWnd != NULL)
		{
			m_pMainWnd->PostMessage(WM_ON_SETTING_DISP_MODE,0,0);
		}
	}
}