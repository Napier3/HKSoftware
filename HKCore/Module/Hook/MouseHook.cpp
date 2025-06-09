#include "stdafx.h"
#include "MouseHook.h"

HHOOK CMouseHook::g_hHook = NULL;

//钩子函数的实现： 
LRESULT WINAPI MouseHookProc(int nCode,WPARAM wparam,LPARAM lparam) 
{ 
	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *) lparam; 

	if (nCode>=0) 
	{ 
		HWND glhTargetWnd=pMouseHook->hwnd; 
	
		//取目标窗口句柄 
// 		HWND ParentWnd=glhTargetWnd; 
// 		
// 		while (ParentWnd !=NULL) 
// 		{ 
// 			glhTargetWnd=ParentWnd; 
// 			ParentWnd=GetParent(glhTargetWnd); 
// 			//取应用程序主窗口句柄 
// 		} 
// 	
// 		if(glhTargetWnd!=m_hPrevTargetWnd) 
// 		{ 
// 			char szCaption[100]; 
// 			GetWindowText(glhTargetWnd,szCaption,100); 
// 			//取目标窗口标题 
// 			if(IsWindow(m_hPrevTargetWnd)) 
// 				SendMessage(m_hPrevTargetWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption); 
// 			m_hPrevTargetWnd=glhTargetWnd; 
// 			//保存目标窗口 
// 		} 
	} 

	//继续传递消息 
	return CallNextHookEx(CMouseHook::g_hHook,nCode,wparam,lparam); 
} 


CMouseHook::CMouseHook(HINSTANCE hInstance) 
{ 
	m_hInstance = hInstance;    //DLL实例句柄 
} 

CMouseHook::~CMouseHook() 
{ 
	StopHook(); 
} 

//安装钩子并设定接收显示窗口句柄 
BOOL CMouseHook::StartHook() 
{ 
	BOOL bResult=FALSE; 
	g_hHook = SetWindowsHookEx(WH_MOUSE, MouseHookProc,NULL,0); 

	if(g_hHook!=NULL) 
	{
		bResult=TRUE; 
	}

	return bResult; 
} 

//卸载钩子 
BOOL CMouseHook::StopHook() 
{ 
	BOOL bResult=FALSE; 

	if(g_hHook) 
	{ 
		bResult= UnhookWindowsHookEx(g_hHook); 

		if(bResult) 
		{ 
			g_hHook=NULL; 
		} 
	} 

	return bResult; 
} 
