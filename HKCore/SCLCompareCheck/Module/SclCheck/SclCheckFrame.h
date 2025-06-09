#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

// ���в������ CSclCheckFrame ���
#define WM_SCLCHECKCLASSID_CLOSEFRAME              (WM_USER + 1901)

class CSclCheckFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CSclCheckFrame)

protected:
	CSclCheckFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


