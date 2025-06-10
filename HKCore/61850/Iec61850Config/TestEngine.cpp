// TestEngine.cpp : ʵ���ļ�
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
	
	// Ϊ��ʹӦ�ó����� OLE �Զ��������ڻ״̬ʱ����
	//	���У����캯������ AfxOleLockApp��
	
	AfxOleLockApp();
}

CTestEngine::~CTestEngine()
{
	// Ϊ������ OLE �Զ����������ж������ֹӦ�ó���
	// 	������������ AfxOleUnlockApp��
	
	AfxOleUnlockApp();
}


void CTestEngine::OnFinalRelease()
{
	// �ͷ��˶��Զ�����������һ�����ú󣬽�����
	// OnFinalRelease�����ཫ�Զ�
	// ɾ���ö����ڵ��øû���֮ǰ�����������
	// ��������ĸ���������롣

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

// ע��: ������� IID_ITestEngine ֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡��� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {27C70E3E-7ED4-4C61-ABF9-3809AB63D54B}
static const IID IID_ITestEngine =
{ 0x27C70E3E, 0x7ED4, 0x4C61, { 0xAB, 0xF9, 0x38, 0x09, 0xAB, 0x63, 0xD5, 0x4B } };

BEGIN_INTERFACE_MAP(CTestEngine, CCmdTarget)
	INTERFACE_PART(CTestEngine, IID_ITestEngine, Dispatch)
END_INTERFACE_MAP()

// {AD0B02A6-A607-432C-9B4A-D0C77A4079F5}
IMPLEMENT_OLECREATE_FLAGS(CTestEngine, "Iec61850Config.TestEngine", afxRegApartmentThreading, 0xAD0B02A6, 0xA607, 0x432C, 0x9B, 0x4A, 0xD0, 0xC7, 0x7A, 0x40, 0x79, 0xF5)


// CTestEngine ��Ϣ�������
//2014-12-28  lijq
// CTestEngine ��Ϣ�������
/*
	bstrConfig�����Ϊ���ַ��������ʾֻ���õ�̨�豸
				�����Ϊ���ַ��������ƶ�������Ϣ�����ڿ��ƶ�̨���������
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
	pSclFrame->OnShowCurIED(strIedName);//ѡ���½����������ɵ�IED
	CString strSrcPath;
	strSrcPath = strSrcIecfgFile;
	CIecCfgFile *pIecCfgFile = NULL;

	if (strSrcPath.IsEmpty())
	{
		CString strPostfix;
		strPostfix = ParseFilePostfix(g_szEngineIecfgPath);

		if (strPostfix == g_strDeviceIecCfgFilePostfix)
		{
			pIecCfgFile = CIecCfgTool::NewIecCfgFile(g_strDeviceIecCfgFilePostfix);//�½�һ���յ������豸����
			CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pIecCfgFile;
			theApp.OnFileNewDevice(pIecCfgFileDevice);//����ǰѡ��IED�����÷��������豸������
			pIecCfgFile->SaveAs(g_szEngineIecfgPath);//���½����豸�洢����Ӧ��·���£�

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

LONG CTestEngine::EditIecfgFile(LPCTSTR strCfgFile)//�༭iec�����ļ�ʱ,��Զ���������Զ����ɲ���
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	CString strDesIecfgPath;
	strDesIecfgPath = strCfgFile;
	CString_to_char(strDesIecfgPath,g_szEngineIecfgPath);
	theApp.CloseSclFileFrame();//�༭�����ļ�ʱ�̶��ر�scd�������
	CMainFrame *pMainFrame = (CMainFrame*)AfxGetMainWnd();
//	BOOL bAutoGenerate = IsFileExist(strDesIecfgPath);
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->OpenIecfgFile(strDesIecfgPath,FALSE);
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������ļ�[%s]�ɹ�."),strDesIecfgPath);
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

	// TODO: �ڴ���ӵ��ȴ���������
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰg_hEngineMsgWnd == NULL."));
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
	// TODO: �ڴ���ӵ��ȴ���������

	theApp.SetDispMode(nMode);
}

LONG CTestEngine::CommConfig(LPCTSTR strCmmConfig)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// TODO: �ڴ���ӵ��ȴ���������
	CString strConfig;
	strConfig = strCmmConfig;
	CDvmDataset oDvmDataset;
	oDvmDataset.SetXml(_bstr_t(strConfig),CDataMngrXmlRWKeys::g_pXmlKeys);
	CDvmData *pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("fiber-num"));

	if (pDvmData != NULL)
	{
		long nFiberNum = CString_To_long(pDvmData->m_strValue);

		if (nFiberNum<8)//zhouhj 20211201 ����8���
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
