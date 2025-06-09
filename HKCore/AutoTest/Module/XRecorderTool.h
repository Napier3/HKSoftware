#pragma once
#include "afxwin.h"
#include "..\..\Module\DialogBase\DynDialogEx.h"
#include "TestControl.h"

// CBaseKeyDlg 对话框
#define RECORD_OPTR_NONE      0
#define RECORD_OPTR_CONFIG    1
#define RECORD_OPTR_CMD       2
#define RECORD_OPTR_SAVE      3

#define RECORD_OPTR_DELAY_TIME      4

#define RECORD_OPTR_RCD_START_RCD    5
#define RECORD_OPTR_RCD_READ_DIR      6
#define RECORD_OPTR_RCD_READ_FILE     7

//操作执行ID
#define RECORD_OPTR_EXEC_TIMER_ID       100
//操作计时的ID
#define RECORD_OPTR_TIMER_ID                101
//操作延时ID
#define RECORD_DELAY_TIMER_ID              102

#define RECORD_TIMER_LONG  1000
#define RECORD_EXEC_TIMER_LONG  200


#define  WM_RECORD_MESSAGE  (WM_USER+1606)

class CXRecorderTool : public CDynDialogEx
{
	DECLARE_DYNAMIC(CXRecorderTool)

public:
	CXRecorderTool(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXRecorderTool();

	CTestControl *m_pTestControl;
	CMacroTest *m_pMacroTest;
	CString m_strRecordFile;
	long m_nTimerLong;

	CString m_strCmdID;
	CString m_strCmdPara;

	virtual BOOL OnInitDialog();
	void CreateControls();
	virtual int DoModal();
	virtual void OnOK();
	virtual void OnCancel();

	CEdit m_editMsg;

protected:
	CDWordArray m_dwarrRecordOptr;
	UINT m_nRecordOptr;
	CString m_strOptrNameMsg;

public:
	void AddRecordOptr(DWORD dwOptr);

private:
	void StartExcuteRecordOptrTimer();
	void ExcuteRecordOptr();
	void ExcuteRecordOptr_Config();
	void ExcuteRecordOptr_CMD();
	void ExcuteRecordOptr_Save();
	void ExcuteRecordOptr_Delay();
	void ExcuteRecordOptr_StartRCD();
	void ExcuteRecordOptr_ReadDir();
	void ExcuteRecordOptr_ReadFile();
	void FinishExcuteOneOptr();

	BOOL OnTimer_Delay(UINT_PTR nIDEvent);
	
	void OnInitDialog_Recorder();
	void OnInitDialog_PpEngine();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg LRESULT OnRecordMessage(WPARAM wParam, LPARAM lParam);

	afx_msg LRESULT OnCommCommandMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnEngineSystemMessage(WPARAM wPara,LPARAM lPara);

};


