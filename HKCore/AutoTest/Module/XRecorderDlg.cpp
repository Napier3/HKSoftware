// BaseKeyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "XRecorderDlg.h"
#include "TestControl/TCtrlCntrBaseApp.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"

#include "XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBaseKeyDlg 对话框

IMPLEMENT_DYNAMIC(CRecorderDlg, CDialog)

CRecorderDlg::CRecorderDlg(CWnd* pParent /*=NULL*/)
:CDynDialogEx(pParent)
{
	m_pMacroTest = NULL;
	m_nRecordOptr = RECORD_OPTR_NONE;
}

CRecorderDlg::~CRecorderDlg()
{
}

void CRecorderDlg::AddRecordOptr(DWORD dwOptr)
{
	m_dwarrRecordOptr.Add(dwOptr);
}

void CRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecorderDlg, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(WM_RECORD_MESSAGE,OnRecordMessage)
	ON_MESSAGE(WM_COMM_COMMAND, &CRecorderDlg::OnCommCommandMsg)
	ON_MESSAGE(WM_ENGINE_SYSTEM_MSG, &CRecorderDlg::OnEngineSystemMessage)
END_MESSAGE_MAP()


// CBaseKeyDlg 消息处理程序



BOOL CRecorderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();  //创建控件
	CenterWindow();


	//如果没有指定操作类型，就是需要执行全部类型
	if (m_dwarrRecordOptr.GetSize() == 0)
	{
		if (g_theTCtrlCntrApp->GetAddRecorderReport_Recorder())
		{
			OnInitDialog_Recorder();
		}
		else
		{
			OnInitDialog_PpEngine();
		}
	}

	CRect rc;
	GetWindowRect(&rc);
	SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(),SWP_SHOWWINDOW);
	
	StartExcuteRecordOptrTimer();

	return TRUE;
}

void CRecorderDlg::StartExcuteRecordOptrTimer()
{
	switch (m_nRecordOptr)
	{
	case RECORD_OPTR_CONFIG:
		m_strOptrNameMsg = _T("配置操作中，等待配置完成......");
		break;

	case RECORD_OPTR_CMD:
		m_strOptrNameMsg = _T("执行命令......");
		break;

	case RECORD_OPTR_SAVE:
		m_strOptrNameMsg = _T("保存录波文件......");
		break;

	case RECORD_OPTR_DELAY_TIME:
		m_strOptrNameMsg = _T("读取录波文件前延时......");
		break;

	case RECORD_OPTR_RCD_START_RCD:
		m_strOptrNameMsg = _T("启动录波......");
		break;

	case RECORD_OPTR_RCD_READ_DIR:
		m_strOptrNameMsg = _T("召唤录波目录......");
		break;

	case RECORD_OPTR_RCD_READ_FILE:
		m_strOptrNameMsg = _T("读取录波文件......");
		break;

	default:
		break;
	}

	m_editMsg.SetWindowText(m_strOptrNameMsg);
	SetTimer(RECORD_OPTR_EXEC_TIMER_ID, RECORD_EXEC_TIMER_LONG, NULL);
}

void CRecorderDlg::OnInitDialog_Recorder()
{
	AddRecordOptr(RECORD_OPTR_DELAY_TIME);
	AddRecordOptr(RECORD_OPTR_SAVE);
}

void CRecorderDlg::OnInitDialog_PpEngine()
{
	AddRecordOptr(RECORD_OPTR_DELAY_TIME);
	AddRecordOptr(RECORD_OPTR_RCD_START_RCD);
	AddRecordOptr(RECORD_OPTR_RCD_READ_DIR);
	AddRecordOptr(RECORD_OPTR_RCD_READ_FILE);
}

//创建控件  name、 size、 ID、 this    //继续增加各个控件的属性，字体啊什么的
void CRecorderDlg::CreateControls() 
{
	CRect rc;
	GetClientRect(&rc);
	rc.DeflateRect(4,4,4,4);
	CreateEdit(m_editMsg, rc, 1001, this);
	m_editMsg.SetReadOnly(TRUE);

	m_editMsg.SetFont(g_pGlobalFont14);
}

int CRecorderDlg::DoModal()   //弹出对话框
{   
	CRect rect(0,0,256,30);   
	SetDlgRect(rect);
	int iRet = CDynDialogEx::DoModal();   

	return iRet;   
}   

void CRecorderDlg::OnOK()
{

}

void CRecorderDlg::OnCancel()
{
	CDialog::OnCancel();
}


void CRecorderDlg::OnTimer(UINT_PTR nIDEvent)
{
	//执行命令
	if (RECORD_OPTR_EXEC_TIMER_ID == nIDEvent)
	{
		KillTimer(nIDEvent);
		CDialog::OnTimer(nIDEvent);
		ExcuteRecordOptr();
		return;
	}

	if (RECORD_DELAY_TIMER_ID == nIDEvent)
	{//延时时间
		//延时时间还没有到
		if (!OnTimer_Delay(nIDEvent))
		{
			CDialog::OnTimer(nIDEvent);
			KillTimer(nIDEvent);
			FinishExcuteOneOptr();
		}

		return;
	}

	//操作计时ID
	if (m_nRecordOptr == RECORD_OPTR_TIMER_ID)
	{
		CString strText;
		m_nTimerLong += RECORD_TIMER_LONG;
		strText.Format(_T("%s [%d s]"), m_strOptrNameMsg, m_nTimerLong/1000);
		m_editMsg.SetWindowText(strText);
	}

	CDialog::OnTimer(nIDEvent);
}

void CRecorderDlg::ExcuteRecordOptr_Config()
{
	m_strOptrNameMsg = _T("配置操作中，等待配置完成......");
	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);

	try
	{
		CRecorderInterface* oRecorder = g_theTCtrlCntrApp->GetRecorder();
		oRecorder->AttachAsyncMsg((UINT)m_hWnd, WM_RECORD_MESSAGE);
		oRecorder->Config();
	}
	catch(...)
	{

	}
}

void CRecorderDlg::ExcuteRecordOptr_CMD()
{
	ASSERT (FALSE);
	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);
}

void CRecorderDlg::ExcuteRecordOptr_Save()
{
	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);

	CMacroTest *pMacroTest = m_pMacroTest;
	DWORD dwRet = 0;

	try
	{
		CRecorderInterface* oRecorder = g_theTCtrlCntrApp->GetRecorder();
		dwRet = oRecorder->SaveRecorder(m_strRecordFile);
	}
	catch(...)
	{

	}

	if (dwRet != rcdStateRecordSuccess)
	{
		CDialog::OnCancel();
	}
	else
	{
		CDialog::OnOK();
	}
}

void CRecorderDlg::ExcuteRecordOptr_Delay()
{
	SetTimer(RECORD_DELAY_TIMER_ID, RECORD_TIMER_LONG, NULL);
}

void CRecorderDlg::ExcuteRecordOptr_StartRCD()
{
	m_pTestControl->RunProcedure(CCommCmd::g_strCmdID_StartRecord, g_strDataSetID[DSID_dsFile]
	, 0, 0, ProcedureType_TestItem, m_hWnd);

	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);
}

void CRecorderDlg::ExcuteRecordOptr_ReadDir()
{
	CProtocolDeviceInterface* oPpDevice = m_pTestControl->GetDevicePtr_0();
	CProtocolParasInterface* oDataInterface = oPpDevice->GetDataInterface();
	ASSERT (oDataInterface != NULL);

	//录波文件时间
	if (oDataInterface != NULL)
	{
		oDataInterface->Reset();
		CReport *pReport = m_pMacroTest->GetReport(-1);
		ASSERT (pReport != NULL);
		CString strEndTime;
		GetCurrSystemtimeString(strEndTime);
		oDataInterface->AddData(CCommCmd::g_strCmdID_Para_TimeStart, pReport->m_strBeginTime);
		oDataInterface->AddData(CCommCmd::g_strCmdID_Para_TimeStart, strEndTime);
		oDataInterface->Release();
	}

	m_pTestControl->RunProcedure(CCommCmd::g_strCmdID_ReadDir, g_strDataSetID[DSID_dsFile]
		, 0, 0, ProcedureType_TestItem, m_hWnd);

	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);
}

void CRecorderDlg::ExcuteRecordOptr_ReadFile()
{
	CProtocolDeviceInterface* oPpDevice = m_pTestControl->GetDevicePtr_0();
	m_pTestControl->RunProcedure(CCommCmd::g_strCmdID_ReadFile, g_strDataSetID[DSID_dsFile]
	, 0, 0, ProcedureType_TestItem, m_hWnd);

	SetTimer(RECORD_OPTR_TIMER_ID, RECORD_TIMER_LONG, NULL);
}

void CRecorderDlg::ExcuteRecordOptr()
{
	if (m_dwarrRecordOptr.GetSize() == 0)
	{
		CDialog::OnOK();
		return;
	}

	m_nRecordOptr = m_dwarrRecordOptr.GetAt(0);

	switch (m_nRecordOptr)
	{
	case RECORD_OPTR_CONFIG:
		ExcuteRecordOptr_Config();
		break;

	case RECORD_OPTR_CMD:
		ExcuteRecordOptr_CMD();
		break;

	case RECORD_OPTR_SAVE:
		ExcuteRecordOptr_Save();
		break;

	case RECORD_OPTR_DELAY_TIME:
		ExcuteRecordOptr_Delay();
		break;

	case RECORD_OPTR_RCD_START_RCD:
		ExcuteRecordOptr_StartRCD();
		break;

	case RECORD_OPTR_RCD_READ_DIR:
		ExcuteRecordOptr_ReadDir();
		break;

	case RECORD_OPTR_RCD_READ_FILE:
		ExcuteRecordOptr_ReadFile();
		break;

	default:
		break;

	}
}

BOOL CRecorderDlg::OnTimer_Delay(UINT_PTR nIDEvent)
{
	m_nTimerLong += RECORD_TIMER_LONG;

	if (m_nTimerLong < g_theTCtrlCntrApp->GetRecorderDelay() )
	{
		CString strText;
		strText.Format(g_sLangTxt_RecordFileRead2/*_T("读取录波文件前延时%d秒,共%d秒")*/
			, m_nTimerLong/1000, g_theTCtrlCntrApp->GetRecorderDelay()/1000);
		m_editMsg.SetWindowText(strText);

		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

LRESULT CRecorderDlg::OnRecordMessage(WPARAM wParam, LPARAM lParam)
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;

	if (wParam != rcdStateRecordSuccess)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_ErrorMessage_a/*_T("错误的处理消息...............")*/);
	}

	try
	{
		CRecorderInterface* oRecorder = pApp->GetRecorder();
		oRecorder->AttachAsyncMsg(0, 0);
	}
	catch(...)
	{

	}

	FinishExcuteOneOptr();

	return 0;
}

void CRecorderDlg::FinishExcuteOneOptr()
{
	m_dwarrRecordOptr.RemoveAt(0);

	if (m_dwarrRecordOptr.GetSize() == 0)
	{
		CDialog::OnOK();
		return;
	}

	//执行下一个命令
	StartExcuteRecordOptrTimer();
}

LRESULT CRecorderDlg::OnCommCommandMsg(WPARAM wParam, LPARAM lParam)
{
	if (lParam == engineCommError)
	{
		m_pTestControl->StopTestExtern(_T(""), TRUE);
		CDialog::OnCancel();
		return 0;
	}

	if (m_nRecordOptr == RECORD_OPTR_RCD_READ_DIR)
	{
		//将读回来的录波文件数据添加到报告中
		CDvmDataset oDataset;
		CProtocolDeviceInterface* oPpDevice = m_pTestControl->GetDevicePtr_0();

		m_pTestControl->ReadEngineDatas(oPpDevice, m_pMacroTest->m_strName, g_strDataSetID[DSID_dsFile] , &oDataset);
		m_pTestControl->UnRegisterProcedureMsg(wParam, lParam, m_hWnd);
	}

	FinishExcuteOneOptr();

	return 0;
}

LRESULT CRecorderDlg::OnEngineSystemMessage(WPARAM wParam, LPARAM lParam)
{
	if (lParam == engineCommError || lParam == engineException)
	{
		m_pTestControl->StopTestExtern(_T(""), TRUE);
		CDialog::OnCancel();
	}

	return 0;
}

