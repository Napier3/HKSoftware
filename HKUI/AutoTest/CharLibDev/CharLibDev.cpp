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

// CharLibDev.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "CharLibDev.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "CharLibDevDoc.h"
#include "CharLibDevView.h"
#include "afxcmn.h"
#include "..\..\Module\XMinidmp\XMinidmp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar)
{
	return FALSE;
}

CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar)
{
	return NULL;
}

CString* CharVar_CalScriptValue(CExBaseObject *pData)
{
	return &pData->m_strID;
}

void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue)
{

}


// CCharLibDevApp

BEGIN_MESSAGE_MAP(CCharLibDevApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCharLibDevApp::OnAppAbout)
	// 基于文件的标准文档命令
	//ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	//ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CCharLibDevApp 构造

CCharLibDevApp::CCharLibDevApp()
{
	m_bHiColorIcons = TRUE;
	m_pDocTemplate = NULL;

}

// 唯一的一个 CCharLibDevApp 对象

CCharLibDevApp theApp;


// CCharLibDevApp 初始化

BOOL CCharLibDevApp::InitInstance()
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

	_P_InitSystemPath();
	RunCrashHandler();

	CXLanguageXmlRWKeys::Create();
	CXLanguageMngr::Create(new CXLanguageResourceAts_CharLibDev(),TRUE);

	CCharacteristicXmlRWKeys::Create();
	CDataMngrXmlRWKeys::Create();

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	//20230317 zhouhj 通过命令行参数传递库文件路径,打开对应的库文件
	if (IsFileExist(cmdInfo.m_strFileName))
	{
		m_oCharacteristicLib.OpenCharLibFile(cmdInfo.m_strFileName);
	} 
	else
	{
		m_oCharacteristicLib.OpenCharLibFile(_T(""));
	}

//	m_oCharacteristicLib.OpenCharLibFile(_T(""));
	char_dev_SetModifiedFlag(&m_oCharacteristicLib, FALSE);

	CCharacteristicLib::CreateGlobalCharAreaSrc();
	CDocFrameMngr::Create();
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

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_CharLibDevTYPE,
		RUNTIME_CLASS(CCharLibDevDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CCharLibDevView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	m_pDocTemplate = pDocTemplate;

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


	// 分析标准外壳命令、DDE、打开文件操作的命令行
//	::GetCommandLine();
// 	CCommandLineInfo cmdInfo;
// 	ParseCommandLine(cmdInfo);

	cmdInfo.m_nShellCommand = cmdInfo.CCommandLineInfo::FileNothing;

	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s"),cmdInfo.m_strFileName.GetString());

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
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CCharLibDevApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCharLibDevApp 自定义加载/保存方法

void CCharLibDevApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CCharLibDevApp::LoadCustomState()
{
}

void CCharLibDevApp::SaveCustomState()
{
}

// CCharLibDevApp 消息处理程序




int CCharLibDevApp::ExitInstance()
{
	CCharacteristicXmlRWKeys::Release();
	CCharacteristicLib::ReleaseGlobalCharAreaSrc();

	CXLanguageXmlRWKeys::Release();
	CDataMngrXmlRWKeys::Release();
	CXLanguageMngr::Release();
	CDocFrameMngr::Release();

	return CWinAppEx::ExitInstance();
}

void CCharLibDevApp::OpenCharTemplate(CCharacteristic *pCharTemp)
{
	if (pCharTemp == NULL)
	{
		return;
	}

	CMDIChildWndEx *pFrame = CDocFrameMngr::FindDocFrame(pCharTemp);

	if (pFrame != NULL)
	{
		pFrame->ActivateFrame();
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Open Characteristic[%s]"), pCharTemp->m_strName);
	CView *pView = NULL;
	CDocument *pDoc = docfrm_OpenDocTemplateEx(pCharTemp, m_pDocTemplate, &pView, &pFrame);
	pDoc->UpdateAllViews(NULL, (LPARAM)pCharTemp, NULL);
	pDoc->SetTitle(pCharTemp->m_strName);
	((CChildFrame*)pFrame)->m_pCurrCharTemp = pCharTemp;
}

void CCharLibDevApp::CloseCharTempFrame(CMDIChildWndEx *pFrame)
{
	CDocFrameMngr::CloseFrame(pFrame);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
