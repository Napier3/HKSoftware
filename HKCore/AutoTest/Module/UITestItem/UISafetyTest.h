#pragma once

#include "UISftRsltWndMngr.h"
#include "../GuideBook/GuideBookInterface.h"

#include "UITestGlobalDefine.h"
#include "../../../Module/WavePlay/MediaPlay.h"
#include "../DllCallInterface/DllCallInterface.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../Module/QRCode/XBarcodeStrParser.h"

// CUISafetyTest 对话框

#define UI_SAFETY_DLLCALL_TIMERID			1443
#define UI_SAFETY_DLLCALL_TIMERLONG		    200

#include "../../../Module/QRCode/QRCodeRead.h"

//////////////////////////////////////////////////////////////////////////
#ifdef _UITEST_USE_DIALOGEX

#include "SafetyTestGrid.h"
#include "../../../Module/DialogBase/DynDialogEx.h"

class CUISafetyTest : public CDynDialogEx//, public CExBaseListGridOptrInterface
{

#else

class CUISafetyTest : public CDialog
{
	DECLARE_DYNAMIC(CUISafetyTest)

#endif
//////////////////////////////////////////////////////////////////////////

public:
	CUISafetyTest(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUISafetyTest();

// 对话框数据
	//enum { IDD = IDD_DIALOG_SAFETY };

private:
	CSafety* m_pTestItemSafety;
	CTestControlWnd* m_pWndMsgRcv;

	long m_nDialogWidth;
	long m_nDialogHeight;
	long m_nFrameBtnOKGap;
	CRect m_rectDialog;
	CRect m_rectFrame;
	CRect m_rectBtnOK;

	CFont m_font;
	LOGFONT m_lfFont;
	CFont m_fontRsltCtrl;

	BOOL m_bAdjustWindowPos;
	CUISftRsltWndMngr m_oResultWndMngr;

	CEdit m_edtSafetyData;
	CString m_strSafetyData;
	CButton m_btnOK;

	CMediaPlay m_oMediaPlay;
	CWinThread *m_pDllCallThread;

	void EnableOK();

	//////////////////////////////////////////////////////////////////////////
	//条码
	//CQRCodeRead *m_pQRCodeRead;
	//CXBarcodeStrParser m_oXBarcodeStrParser;
// 	char m_pszBarCodeBuffer[QRCODE_BUFFER_LEN];
// 	long m_nBarCodeLen;
// 	CTickCount32  m_oCTickCount32;
// 
	void OnQRCodeInput();

public:
	void InitTestItem(CSafety* pTestItemSafety, CTestControlWnd *pWndMsgRcv);
	void ShowInDllCallMsg();

	void FinishTestCmmCmdItem();
	void UIFinishTestItem();
	void Finished(long nState);

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnFinished();
	afx_msg LRESULT OnMediaPlayStateChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnQRCodeReadFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnFinishInputData(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDeleteItem(int nIDCtl, LPDELETEITEMSTRUCT lpDeleteItemStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

protected:
	virtual void OnCancel();
	virtual void OnOK();

	void InitMsgText();
	void CreateResultWnds();
	BOOL DllCallTimer();
	void FinishDllCall();
	void PlayMedia();
};
