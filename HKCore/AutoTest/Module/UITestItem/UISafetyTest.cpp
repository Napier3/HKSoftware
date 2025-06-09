// D:\WorkPM\Source\PMTest\Module\Safety\UISafetyTest.cpp : 实现文件
//

#include "stdafx.h"
#include "UISafetyTest.h"

#include "../../../Module/api/GloblaDrawFunctions.h"
#include "../TCtrlCntrDefine.h"
#include "..\TestControl/TestControlWnd.h"
#include "..\TestControl/TestControl.h"
#include "..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\TestControl/TCtrlCntrBaseApp.h"

#include "..\XLanguageResourceAts.h"
#include "../SmartTestRpcEventApi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUISafetyTest 对话框
#ifndef _UITEST_USE_DIALOGEX
IMPLEMENT_DYNAMIC(CUISafetyTest, CDialog)
#endif

CUISafetyTest::CUISafetyTest(CWnd* pParent /*=NULL*/)
	//: CDialog(CUISafetyTest::IDD, pParent)
{
	m_lfFont = InitLogFont();
#ifdef UNICODE
	lstrcpy(m_lfFont.lfFaceName,_T("Tahoma"));
#else
	strcpy(m_lfFont.lfFaceName, _T("Tahoma"));
#endif // UNICODE

	m_lfFont.lfHeight = 16;
	m_lfFont.lfWeight = 0;
	m_font.CreateFontIndirect(&m_lfFont);
	m_lfFont.lfHeight = 14;
	m_fontRsltCtrl.CreateFontIndirect(&m_lfFont);

}

CUISafetyTest::~CUISafetyTest()
{

}

void CUISafetyTest::DoDataExchange(CDataExchange* pDX)
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::DoDataExchange(pDX);
#else
	CDialog::DoDataExchange(pDX);
#endif
}


#ifdef _UITEST_USE_DIALOGEX
BEGIN_MESSAGE_MAP(CUISafetyTest, CDynDialogEx)
#else
BEGIN_MESSAGE_MAP(CUISafetyTest, CDialog)
#endif
	ON_BN_CLICKED(10001, &CUISafetyTest::OnFinished)
	ON_WM_CLOSE()
	ON_WM_DELETEITEM()
	ON_MESSAGE(WM_MEDIAPLAY,OnMediaPlayStateChange)
	ON_MESSAGE(WM_QRCODEREAD_FINISH,OnQRCodeReadFinish)
	ON_MESSAGE(WM_FINISH_INPUTDATA, OnFinishInputData)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CUISafetyTest 消息处理程序

BOOL CUISafetyTest::OnInitDialog()
{
#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnInitDialog();
#else
	CDialog::OnInitDialog();
#endif

	CenterWindow();
	// TODO:  在此添加额外的初始化
	GetWindowRect(&m_rectDialog);
	m_nDialogWidth = m_rectDialog.Width();
	m_nDialogHeight = m_rectDialog.Height();

	DWORD dwStyle = /*ES_AUTOHSCROLL | */ES_AUTOVSCROLL | ES_LEFT | ES_MULTILINE | ES_READONLY |WS_VSCROLL/* | WS_HSCROLL*/ ;
	m_edtSafetyData.Create(dwStyle,CRect(10,10,100,100),this,10000);
	m_edtSafetyData.ModifyStyleEx(0,WS_EX_CLIENTEDGE,   SWP_DRAWFRAME);

	dwStyle = BS_PUSHBUTTON;
	m_btnOK.Create(/*g_strTestBtnOK_Finish*/g_sLangTxt_Finish,dwStyle,CRect(0,0,50,30),this,10001);

	m_btnOK.GetWindowRect(&m_rectBtnOK);

	m_nFrameBtnOKGap = m_rectBtnOK.top - m_rectFrame.bottom;
	m_edtSafetyData.SetFont(&m_font);

	m_btnOK.SetFont(&m_font);
	m_oMediaPlay.CreateMedia(this);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUISafetyTest::InitTestItem(CSafety* pTestItemSafety, CTestControlWnd *pWndMsgRcv)
{
	m_pWndMsgRcv = pWndMsgRcv;

	GetWindowRect(&m_rectDialog);
	m_btnOK.GetWindowRect(&m_rectBtnOK);
	ScreenToClient(&m_rectFrame);
	ScreenToClient(&m_rectBtnOK);

	m_pTestItemSafety = pTestItemSafety;
	ASSERT (pTestItemSafety != NULL);

	if (pTestItemSafety == NULL)
	{
		return;
	}

	CTestControl *pTestControl = (CTestControl*)pTestItemSafety->GetAncestor(GBCLASSID_TESTCONTROL);

	if (pTestControl->GetParent() != NULL || pTestControl->IsTestControlMngr())
	{
		if (m_pTestItemSafety->IsManyDeviceTestMode_ManyTime())
		{
			CDevice *pDevice = (CDevice*)m_pTestItemSafety->GetAncestor(GBCLASSID_DEVICE);
			CSysParas *pSysParas = pDevice->GetSysParas();
			CDataObj *pData = (CDataObj*)pSysParas->FindByID(DATAID_DEVICEID);
			CString strTitle;

			if (pData == NULL)
			{
				strTitle.Format(_T("%s:          %s"), pTestControl->GetGbBinaryFileName(), pTestItemSafety->GetName());
			}
			else
			{
				long nDeviceID = CString_To_long(pData->m_strValue) + 1;
				strTitle.Format(_T("第%d台:          %s"), nDeviceID, pTestItemSafety->GetName());
			}

			SetWindowText(strTitle);
		}
		else
		{
			SetWindowText(pTestItemSafety->GetName());
		}
	}
	else
	{
		SetWindowText(pTestItemSafety->GetName());
	}

	//消息文本
	InitMsgText();

	//
	CreateResultWnds();

	PlayMedia();

	//处理DLL调用
	CDllCall *pDllCall = m_pTestItemSafety->GetDllCall();


	if (m_pTestItemSafety->IsSafetyDataModeQRCode())
	{
		CQRCodeRead::InitQRCodeReadParser('=', ';');
		CQRCodeRead::AttachMsgRcvWnd(this);
// 		m_oXBarcodeStrParser.InitParser();
// 		m_oXBarcodeStrParser.SetSeparateChar(pConfig->m_chSeparateChar, pConfig->m_chSeparateEndChar);
// 		m_pQRCodeRead = new CQRCodeRead();
// 		m_pQRCodeRead->AttachMsgRcvWnd(this);
// 		m_pQRCodeRead->InitQRCodeRead();
	}

	CRect rcDlg;
	this->GetWindowRect(rcDlg);

	//2021-4-5  lijunqing  根据主窗口位置，调整rcDlg，避免大字体显示模式下窗口显示不全
	CWnd *pMainFrame = AfxGetMainWnd();
	CRect rcMain;
	pMainFrame->GetWindowRect(rcMain);
	long x=rcMain.right - rcDlg.right;
	long y=rcMain.bottom - rcDlg.bottom;

	if (x > 0)
	{
		x = 0;
	}

	if (y > 0)
	{
		y = 0;
	}

	rcDlg.OffsetRect(x, y);

	pMainFrame->ScreenToClient(rcDlg);


	if (g_bShowTestWndTop)
	{
		if (m_pTestItemSafety->IsSafetyDataModeScript())
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			SetWindowPos(&wndTopMost, rcDlg.top, rcDlg.top, rcDlg.Width(), rcDlg.Height(), SWP_SHOWWINDOW | SWP_NOMOVE);
		}
	}
	else
	{
		if (m_pTestItemSafety->IsSafetyDataModeScript())
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			SetWindowPos(&wndTopMost, rcDlg.top, rcDlg.top, rcDlg.Width(), rcDlg.Height(), SWP_SHOWWINDOW | SWP_NOMOVE);
		}
	}

	if ((pDllCall != NULL) || (m_pTestItemSafety->IsSafetyDataModeScript()))
	{
		SetTimer(UI_SAFETY_DLLCALL_TIMERID, 500, NULL);
	}
	//else
	if(m_pTestItemSafety->IsSafetyDataModeList())
	{
		//如果是RPC模式，且不是ModeScript，需要调用atsrpc_OnInputData();
		if (atsrpc_IsSmartTestRpc())
		{
			atsrpc_OnInputData(m_pTestItemSafety);
		}
	}
	

	m_btnOK.SetFocus();
}

void CUISafetyTest::InitMsgText()
{
	m_strSafetyData = "";

	ASSERT(m_pTestItemSafety != NULL);
	CExBaseList* pMsgList = m_pTestItemSafety->GetMsgs();

	if(pMsgList != NULL)
	{
		POS pos = pMsgList->GetHeadPosition();
		CMsg* pMsg = NULL;

		while(pos != NULL)
		{
			pMsg = (CMsg*)pMsgList->GetNext(pos);
			m_strSafetyData += pMsg->m_strMsg;

			if ( pos != NULL)
			{
				m_strSafetyData += _T("\r\n");
			}
		}
	}
	else
	{
		m_strSafetyData = _T("");
	}

	m_edtSafetyData.SetWindowText(m_strSafetyData);
}

void CUISafetyTest::CreateResultWnds()
{
	CShortDatas* Result = m_pTestItemSafety->GetDatas();
	ASSERT (Result != NULL);
	UpdateData(FALSE);
	m_oResultWndMngr.DeleteAll();
	
	if (Result != NULL)
	{
		m_oResultWndMngr.CreateRsltEditWnd(Result, this, m_rectFrame);
		m_oResultWndMngr.SetFont(&m_fontRsltCtrl);
		//return;
	}
	
	m_oResultWndMngr.AdjustAllWindows(this, &m_edtSafetyData, &m_btnOK);

	if (m_pWndMsgRcv->m_pTestControl->HasNextItemNeedTest())
	{
		m_btnOK.SetWindowText(/*g_strTestBtnOK_Next*/g_sLangTxt_NextStep);
	}
	else
	{
		m_btnOK.SetWindowText(/*g_strTestBtnOK_Finish*/g_sLangTxt_Finish);
	}
}

BOOL CUISafetyTest::DllCallTimer()
{
	CDllCall *pDllCall = m_pTestItemSafety->GetDllCall();

	if (pDllCall == NULL)
	{
		OnClose();
		return FALSE;
	}

	if (!pDllCall->IsDllCallDefined())
	{
		return FALSE;
	}

	if ( (!pDllCall->IsDllPathValid()) || (pDllCall->IsParaFilePathValid()) )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ErrorDll/*_T("错误的DLL调用 %s::%s(\"%s\", \"%s\")")*/
			, pDllCall->m_strID, pDllCall->m_strFuncName, pDllCall->m_strParaType, pDllCall->m_strParaData);

		OnClose();
		return FALSE;
	}

	EnableOK();

	CDevice *pDevice = (CDevice*)m_pTestItemSafety->GetAncestor(GBCLASSID_DEVICE);
	CGuideBook *pGuideBook = (CGuideBook*)pDevice->GetParent();
	BOOL bRet = CSafetyDllCallMngr::DllCall(pDllCall, m_pTestItemSafety->GetDatas(), pDevice->GetTestParas(), pGuideBook->GetGlobalDatas());

	if (bRet)
	{
		FinishDllCall();
	}
	else
	{
		OnClose();
	}

	return bRet;
}

void CUISafetyTest::FinishDllCall()
{
	//处理结果数据

	//使能OK按钮
	//m_btnOK.EnableWindow(m_oResultWndMngr.IsAllDataEntered());
	EnableOK();

	m_pDllCallThread = NULL;

	if (m_pTestItemSafety->IsSafetyDataModeScript())
	{
		OnFinished();
	}
}

void CUISafetyTest::PlayMedia()
{
	CString strMediaFile = m_pTestItemSafety->GetWaveFilePath();

	if (strMediaFile.GetLength() > 0)
	{
		m_oMediaPlay.Play(strMediaFile);
	}

}


void CUISafetyTest::Finished(long nState)
{
	ShowWindow(SW_HIDE);

	m_oMediaPlay.Stop();
	m_oMediaPlay.Close();

	//如果是QR

	//发送消息给TestControl，测试完成，填写报告
	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_SAFETY_TEST_FINISHED, (WPARAM)m_pTestItemSafety, 1);
	}
}

//点击完成按钮的响应
void CUISafetyTest::OnFinished() 
{
	//m_pTestItemSafety->AddQRCodeData(m_strQRCode);

	if (m_pTestItemSafety->IsSafetyDataModeQRCode())
	{
		m_pTestItemSafety->WriteQRCodePngFile();
// 		ASSERT (m_pQRCodeRead != NULL);
// 		m_pQRCodeRead->ExitQRCodeRead();
// 		delete m_pQRCodeRead;
// 		m_pQRCodeRead = NULL;
		CQRCodeRead::DetachMsgWnd();
	}

	Finished(1);
}

void CUISafetyTest::EnableOK()
{
	BOOL bEnable = TRUE;

	if (!m_oResultWndMngr.IsAllDataEntered())
	{
		bEnable = FALSE;
	}

	CExBaseList *pSubItems = m_pTestItemSafety->GetSubGbItems();

	if (pSubItems->GetCount() > 0)
	{
		bEnable = FALSE;
	}

	m_btnOK.EnableWindow(bEnable);	
}

void CUISafetyTest::ShowInDllCallMsg()
{
	CDllCall *pDllCall = m_pTestItemSafety->GetDllCall();
	CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DllUnStopTest/*_T("DLL调用(%s::%s)处理中，不能终止测试...")*/
		, pDllCall->m_strID, pDllCall->m_strFuncName);
}


void CUISafetyTest::FinishTestCmmCmdItem()
{
	
}

void CUISafetyTest::UIFinishTestItem()
{
	Finished(1);
}

void CUISafetyTest::OnClose()
{
	//停止测试
	ASSERT (m_pWndMsgRcv != NULL);

	if(m_pWndMsgRcv)
	{
		m_pWndMsgRcv->PostMessage(WM_SAFETY_TEST_FINISHED, (WPARAM)m_pTestItemSafety, 0);
	}

	m_oMediaPlay.Stop();
	m_oMediaPlay.Close();
	ShowWindow(SW_HIDE);
}

void CUISafetyTest::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CUISafetyTest::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CUISafetyTest::OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	LPVOID lpszText = (LPVOID)lpDeleteItemStruct->itemData;
	//ASSERT(lpszText != NULL);

	free(lpszText);

	CDialog::OnDeleteItem(nIDCtl, lpDeleteItemStruct);
}


LRESULT CUISafetyTest::OnMediaPlayStateChange(WPARAM wParam, LPARAM lParam)
{
	if (wParam == MEDIA_STATE_BEGIN_PLAY)
	{
// 		m_btnPlay.EnableWindow(FALSE);
// 		m_btnStop.EnableWindow(TRUE);
	}
	else if (wParam == MEDIA_STATE_PLAY_FINISH)
	{
		m_oMediaPlay.Play(0);
// 		m_btnPlay.EnableWindow(TRUE);
// 		m_btnStop.EnableWindow(FALSE);
	}
	else if (wParam == MEDIA_STATE_PLAY_STOP)
	{
		//m_oMediaPlay.Close();
// 		m_btnPlay.EnableWindow(TRUE);
// 		m_btnStop.EnableWindow(FALSE);
	}
	return 0;
}

LRESULT CUISafetyTest::OnQRCodeReadFinish(WPARAM wParam, LPARAM lParam)
{
// 	char *pBuffer = (char*)wParam;
// 	long nLen = lParam;
	//m_oXBarcodeStrParser.SetQRCodeString(m_pQRCodeRead->ReadQRCodeBuffer());
	
	OnQRCodeInput();

	return 0;
}

LRESULT CUISafetyTest::OnFinishInputData(WPARAM wParam, LPARAM lParam)
{
	OnFinished();
	return 0;
}

int UnicodeToChar(char *UnicodeText, char *ASCText, int UnicodeLength)
{
	wchar_t UnicodeWCH[100];
	int MultiLength = 0;
	int WideLength = 0;
	int SMLength = 0;

	while(MultiLength < UnicodeLength)
	{
		UnicodeWCH[WideLength++] = ((unsigned char )UnicodeText[MultiLength] << 8) 
			+ (unsigned char)UnicodeText[MultiLength+1];
		MultiLength += 2;
	}

	UnicodeWCH[WideLength] = 0;

	SMLength = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)UnicodeWCH, WideLength, 
		(LPSTR)ASCText, 161, NULL, NULL);

	return SMLength;
}

void CUISafetyTest::OnQRCodeInput()
{
	CShortDatas *pDatas = m_pTestItemSafety->GetDatas(); 
// 	m_pTestItemSafety->m_strQRCodeData = m_oXBarcodeStrParser.GetQRCodeData();
// 	m_oXBarcodeStrParser.GetDatas(pDatas);
	m_pTestItemSafety->m_strQRCodeData = CQRCodeRead::GetQRCodeData();
	CQRCodeRead::GetDatas(pDatas);

	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;
	long nIndex = 0;
	CUISftRsltWndInterface *pWndUI = NULL;
	long nQRItemCount = 0;

	while (pos != NULL)
	{
		pData = (CShortData *)pDatas->GetNext(pos);
		pWndUI = (CUISftRsltWndInterface*)m_oResultWndMngr.GetAtIndex(nIndex);

		if(pWndUI != NULL)
		{
			if (pWndUI->m_pRsltEditWnd)
			{
				pWndUI->m_pRsltEditWnd->SetWindowText(pData->m_strValue);
			}
		}

		nIndex++;
	}

	EnableOK();
}

void CUISafetyTest::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == UI_SAFETY_DLLCALL_TIMERID)
	{
		KillTimer(nIDEvent);
		
		if (m_pTestItemSafety->IsTypeDllCall(FALSE))
		{
			DllCallTimer();
		}
		else
		{
			if (m_pTestItemSafety->IsSafetyDataModeScript())
			{
				OnFinished();
			}
		}

// 		if (! DllCallTimer())
// 		{
// 			if (m_pTestItemSafety->IsSafetyDataModeScript())
// 			{
// 				OnFinished();
// 			}
// 		}
// 		DllCall();
	}

#ifdef _UITEST_USE_DIALOGEX
	CDynDialogEx::OnTimer(nIDEvent);
#else
	CDialog::OnTimer(nIDEvent);
#endif
}


BOOL CUISafetyTest::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
// 	if (pMsg->message == WM_CHAR)
// 	{
// 		if (m_pTestItemSafety != NULL)
// 		{
// 			if (m_pTestItemSafety->IsSafetyDataModeQRCode())
// 			{
// 				m_oXBarcodeStrParser.AddChars(pMsg->wParam);
// 				return TRUE;
// 			}
// 		}
// 	}

#ifdef _UITEST_USE_DIALOGEX
	return CDynDialogEx::PreTranslateMessage(pMsg);
#else
	return CDialog::PreTranslateMessage(pMsg);
#endif
}
