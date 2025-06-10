// TestEngine.cpp : 实现文件
//

#include "stdafx.h"
#include "TestEngine.h"
#include "MainFrm.h"
#include "Iec61850Config.h"
#include "SclFileFrame.h"

char g_szEngineIecfgPath[500] = {0};
char g_szEngineSCLPath[500] = {0};
HWND g_hEngineMsgWnd = NULL; 
ULONG g_nEngineMSG_ID = 0;
ULONG g_nEngineDispMode = _DISP_MODE_NORMAL;
BOOL g_bSendTestFinished = TRUE;

// CTestEngine

IMPLEMENT_DYNCREATE(CTestEngine, CCmdTarget)


CTestEngine::CTestEngine()
{
	EnableAutomation();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	//	运行，构造函数调用 AfxOleLockApp。
	
	AfxOleLockApp();
}

CTestEngine::~CTestEngine()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 	析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
}


void CTestEngine::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清理代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CTestEngine, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CTestEngine, CCmdTarget)
	DISP_FUNCTION_ID(CTestEngine, "SetWndMsg", dispidSetWndMsg, SetWndMsg, VT_I4, VTS_UI4 VTS_UI4)
	DISP_FUNCTION_ID(CTestEngine, "OpenSCDFile", dispidOpenSCDFile, OpenSCDFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "OpenTscdFile", dispidOpenTscdFile, OpenTscdFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "SetDestPath", dispidSetDestPath, SetDestPath, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "NewIecfgFile", dispidNewIecfgFile, NewIecfgFile, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "EditIecfgFile", dispidEditIecfgFile, EditIecfgFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "SaveIecfgFile", dispidSaveIecfgFile, SaveIecfgFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "CloseIecfgFile", dispidCloseIecfgFile, CloseIecfgFile, VT_I4, VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "ExitEngine", dispidExitEngine, ExitEngine, VT_UI4, VTS_NONE)
	DISP_FUNCTION_ID(CTestEngine, "ExportAt02dFiles", dispidExportAt02dFiles, ExportAt02dFiles, VT_I4, VTS_BSTR VTS_BSTR)
	DISP_FUNCTION_ID(CTestEngine, "SetDispMode", dispidSetDispMode, SetDispMode, VT_EMPTY, VTS_I4)
	DISP_FUNCTION_ID(CTestEngine, "CommConfig", dispidCommConfig, CommConfig, VT_I4, VTS_BSTR)
END_DISPATCH_MAP()

// 注意: 我们添加 IID_ITestEngine 支持
//  以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//  调度接口的 GUID 匹配。

// {27C70E3E-7ED4-4C61-ABF9-3809AB63D54B}
static const IID IID_ITestEngine =
{ 0x27C70E3E, 0x7ED4, 0x4C61, { 0xAB, 0xF9, 0x38, 0x09, 0xAB, 0x63, 0xD5, 0x4B } };

BEGIN_INTERFACE_MAP(CTestEngine, CCmdTarget)
	INTERFACE_PART(CTestEngine, IID_ITestEngine, Dispatch)
END_INTERFACE_MAP()

// {AD0B02A6-A607-432C-9B4A-D0C77A4079F5}
IMPLEMENT_OLECREATE_FLAGS(CTestEngine, "Iec61850Config.TestEngine", afxRegApartmentThreading, 0xAD0B02A6, 0xA607, 0x432C, 0x9B, 0x4A, 0xD0, 0xC7, 0x7A, 0x40, 0x79, 0xF5)


// CTestEngine 消息处理程序
//2014-12-28  lijq
// CTestEngine 消息处理程序
/*
	bstrConfig：如果为空字符串，则表示只是用单台设备
				如果不为空字符串，则制定配置信息，用于控制多台测试仪输出
*/

LONG CTestEngine::SetWndMsg(ULONG hMainWnd, ULONG nMsgID)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	g_hEngineMsgWnd = (HWND)hMainWnd;
	g_nEngineMSG_ID = nMsgID;
	return 0;
}

LONG CTestEngine::OpenSCDFile(LPCTSTR strScdFilePath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (!theApp.OpenSclFile(strScdFilePath))
	{
		CString strTmp;
		strTmp = strScdFilePath;
		CString_to_char(strTmp,g_szEngineSCLPath);
		theApp.CloseSclFileFrame();
	}

	return 0;
}

LONG CTestEngine::OpenTscdFile(LPCTSTR strTscdFilePath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	theApp.OpenTscdFile(strTscdFilePath);
	return 0;
}

LONG CTestEngine::SetDestPath(LPCTSTR strDestPath)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CString strDesIecfgPath;
	strDesIecfgPath = strDestPath;
	CString_to_char(strDesIecfgPath,g_szEngineIecfgPath);
	return 0;
}

LONG CTestEngine::NewIecfgFile(LPCTSTR strIedName,LPCTSTR strSrcIecfgFile)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CSclFileFrame *pSclFrame = (CSclFileFrame*)theApp.m_pSclFileFrame;

	if (pSclFrame == NULL)
	{
		return 0;
	}

	pSclFrame->ActivateFrame(1);
	pSclFrame->OnShowCurIED(strIedName);//选择新建或智能生成的IED
	CString strSrcPath;
	strSrcPath = strSrcIecfgFile;
	CIecCfgFile *pIecCfgFile = NULL;

	if (strSrcPath.IsEmpty())
	{
		CString strPostfix;
		strPostfix = ParseFilePostfix(g_szEngineIecfgPath);

		if (strPostfix == g_strDeviceIecCfgFilePostfix)
		{
			pIecCfgFile = CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);//新建一个空的配置设备对象；
			CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
			theApp.OnFileNewDevice(pIecCfgFileDevice);//将当前选择IED的配置放入配置设备对象中
			pIecCfgFile->SaveAs(g_szEngineIecfgPath);//将新建的设备存储到对应的路径下；

		}
	} 
	else
	{
		pIecCfgFile = theApp.AutoGeneNewIecfgFile(strSrcPath,g_szEngineIecfgPath);
	}

	if (pIecCfgFile != NULL)
	{
		CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
		pMainFrame->ShowIecfgFileDevice((CIecCfgFileDevice*)pIecCfgFile);
		CIecCfgTool::AdjustIecCfgFile(pIecCfgFile);
	}

	return 0;
}

LONG CTestEngine::EditIecfgFile(LPCTSTR strCfgFile)//编辑iec配置文件时,永远都不进行自动生成操作
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CString strDesIecfgPath;
	strDesIecfgPath = strCfgFile;
	CString_to_char(strDesIecfgPath,g_szEngineIecfgPath);
	theApp.CloseSclFileFrame();//编辑配置文件时固定关闭scd导入界面
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
//	BOOL bAutoGenerate = IsFileExist(strDesIecfgPath);
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->OpenIecfgFile(strDesIecfgPath,FALSE);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("打开配置文件[%s]成功."),strDesIecfgPath);
	return 0;
}

LONG CTestEngine::SaveIecfgFile(LPCTSTR strIecfgFile)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	long nRet = theApp.SaveIecfgFile(strIecfgFile);
	return nRet;
}

LONG CTestEngine::CloseIecfgFile(LPCTSTR strIecfgFile)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CIecCfgFile* pIecfgFile = CIecCfgTool::FindIecFile(strIecfgFile);
	CIecCfgTool::CloseIecFile(pIecfgFile,TRUE);
	theApp.UpdateIecCfgFilesComboBox();
	return 0;
}

LONG CTestEngine::ExportAt02dFiles(LPCTSTR strDesIecfgPath, LPCTSTR strCbXml)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: 在此添加调度处理程序代码
	CString strIecfgPath,strCBXmlText;
	strIecfgPath = strDesIecfgPath;
	strCBXmlText = strCbXml;
	return theApp.ExportPNI302IecfgFile(strIecfgPath,strCBXmlText);
}


// ULONG CTestEngine::NewCfgFile(LPCTSTR strTscdFilePath, LPCTSTR strIEDName, LPCTSTR strSavePath)
// {
// 	AFX_MANAGE_STATE(AfxGetAppModuleState());
// 	theApp.CreateNewSclFrame(strTscdFilePath,strIEDName);
// 	CString strCfgFilePath;
// 	strCfgFilePath = strSavePath;
// 	CString_to_char(strCfgFilePath,g_szEngineIecfgPath);
// 	return 0;
// }
// 
// ULONG CTestEngine::EditCfgFile(LPCTSTR strCfgFilePath)
// {
// 	AFX_MANAGE_STATE(AfxGetAppModuleState());
// 	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
// 	pMainFrame->OpenIecfgFile(strCfgFilePath);
// 	return 0;
// }

ULONG CTestEngine::ExitEngine(void)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);

	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL PostMsg_TestEngineFinish(const CString &strEngineIecfgPath)
{
	if (g_hEngineMsgWnd == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前g_hEngineMsgWnd == NULL."));
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("PostMsg_TestEngineFinish."));
	CString_to_char(strEngineIecfgPath,g_szEngineIecfgPath);
	::PostMessage(g_hEngineMsgWnd, g_nEngineMSG_ID, (WPARAM)g_szEngineIecfgPath, 0);
	return TRUE;
}


void CTestEngine::SetDispMode(LONG nMode)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	// TODO: 在此添加调度处理程序代码

	theApp.SetDispMode(nMode);
}

LONG CTestEngine::CommConfig(LPCTSTR strCmmConfig)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: 在此添加调度处理程序代码
	CString strConfig;
	strConfig = strCmmConfig;
	CDvmDataset oDvmDataset;
	oDvmDataset.SetXml(_bstr_t(strConfig),CDataMngrXmlRWKeys::g_pXmlKeys);
	CDvmData *pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("fiber-num"));

	if (pDvmData != NULL)
	{
		long nFiberNum = CString_To_long(pDvmData->m_strValue);

		if (nFiberNum<8)//zhouhj 20211201 最少8光口
		{
			nFiberNum = 8;
		}

		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FiberNum(nFiberNum);
	}

	pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("binex-num"));

	if (pDvmData != NULL)
	{
		long nBinExNum = CString_To_long(pDvmData->m_strValue);
		CCfgDataMngrConstGlobal::UpdataDataType_BinExNum(nBinExNum);
	}

	pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("boutex-num"));

	if (pDvmData != NULL)
	{
		long nBoutExNum = CString_To_long(pDvmData->m_strValue);
		CCfgDataMngrConstGlobal::UpdataDataType_BoutExNum(nBoutExNum);
	}

	return 0;
}
