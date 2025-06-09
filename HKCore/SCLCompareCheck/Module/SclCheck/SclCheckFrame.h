#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

// 带有拆分器的 CSclCheckFrame 框架
#define WM_SCLCHECKCLASSID_CLOSEFRAME              (WM_USER + 1901)

class CSclCheckFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSclCheckFrame)

protected:
	CSclCheckFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CSclCheckFrame();

	CSplitterWnd m_wndSplitter;

public:
	void AttachMsgRcvWnd(CWnd *pWnd){m_pMsgRcvWnd = pWnd;}

private:
	CWnd *m_pMsgRcvWnd;


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg void OnMDIActivate(BOOL bActivate, CWnd* pActivateWnd, CWnd* pDeactivateWnd);
};


