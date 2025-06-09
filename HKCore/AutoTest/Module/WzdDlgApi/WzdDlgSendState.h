#pragma once
#include "afxcmn.h"
#include "../../iSmartTestWzd/resource.h"	
#include "../WzdDlgApi/StepCtrl/WzdDlgProgressCtrl.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"
#include "afxwin.h"

#define WM_SET_MAX_RANG		 (WM_USER + 1139)
#define WM_ADD_RANG			 (WM_USER + 1140)

// CWzdDlgSendState 对话框

#define SENDSTATE_TIMER_ID  129

#define	DLG_TYPE_NONE		0		//未设置，不可使用
#define	DLG_TYPE_MODAL		1		//模态对话框
#define	DLG_TYPE_NOMORL		2		//非模态对话框

class CWzdDlgSendState : public CDialog, public CThreadProgressInterface
{
	DECLARE_DYNAMIC(CWzdDlgSendState)

public:
	CWzdDlgSendState(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWzdDlgSendState();

// 对话框数据
	enum { IDD = IDD_DIALOG_SHOWSEND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	CString m_strShowWord;

	int m_iModal;
	int m_iTimeCount;

protected: 
    virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void SetModal();		//模态对话框需先调用，再于线程中调用ShowStart
	void ShowStart(const CString &strWinName);

	void SetTitle(const CString &strWinName);		//非模态对话框时设置，包含显示
	void Finish(DWORD dwParam=0);

	void ShowMsg(const CString &sWord);
	void SetMaxRange(long iMaxR);
	void StepIt();

	void ResetProcess(){}
	void StartTimer(long nTimerLong){}
	
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg LRESULT OnReSetRang(WPARAM wPara,LPARAM lPara);
	afx_msg LRESULT OnStepIt(WPARAM wPara,LPARAM lPara);

	CWzdDlgProgressCtrl m_ProgressCtrl;
	CStatic m_strTime;
};
