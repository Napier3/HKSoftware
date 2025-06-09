#if !defined(_SplashWndBase_h__)
#define _SplashWndBase_h__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SplashWndBase.h : header file
//

#include "..\BaseClass\DIB.h"

class CXSplashWndBase : public CWnd  
{  
protected:  
	CXSplashWndBase();  
	virtual ~CXSplashWndBase();  

	virtual void PostNcDestroy();  

public:  

protected:  
	static BOOL g_bShowSplashWnd;  
	static CXSplashWndBase* g_pSplashWnd;  
	CDib m_oDib;  //创建位图对象

public:  
	static void EnableSplashScreen(BOOL bEnable = TRUE);  
	static void ShowSplashScreen(const CString &strFile, CWnd* pParentWnd = NULL);  
	static BOOL PreTranslateAppMessage(MSG* pMsg);  

protected:  
	BOOL Create(CWnd* pParentWnd = NULL);  
	void HideSplashScreen();  

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
	afx_msg void OnPaint();  
	afx_msg void OnTimer(UINT nIDEvent);  

protected:  
	DECLARE_MESSAGE_MAP()  
};  

#endif // !defined(_SplashWndBase_h__)
