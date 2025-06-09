#include "stdafx.h"
#include "MouseHook.h"

HHOOK CMouseHook::g_hHook = NULL;

//���Ӻ�����ʵ�֣� 
LRESULT WINAPI MouseHookProc(int nCode,WPARAM wparam,LPARAM lparam) 
{ 
	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *) lparam; 

	if (nCode>=0) 
	{ 
		HWND glhTargetWnd=pMouseHook->hwnd; 
	
		//ȡĿ�괰�ھ�� 
// 		HWND ParentWnd=glhTargetWnd; 
// 		
// 		while (ParentWnd !=NULL) 
// 		{ 
// 			glhTargetWnd=ParentWnd; 
// 			ParentWnd=GetParent(glhTargetWnd); 
// 			//ȡӦ�ó��������ھ�� 
// 		} 
// 	
// 		if(glhTargetWnd!=m_hPrevTargetWnd) 
// 		{ 
// 			char szCaption[100]; 
// 			GetWindowText(glhTargetWnd,szCaption,100); 
// 			//ȡĿ�괰�ڱ��� 
// 			if(IsWindow(m_hPrevTargetWnd)) 
// 				SendMessage(m_hPrevTargetWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption); 
// 			m_hPrevTargetWnd=glhTargetWnd; 
// 			//����Ŀ�괰�� 
// 		} 
	} 

	//����������Ϣ 
	return CallNextHookEx(CMouseHook::g_hHook,nCode,wparam,lparam); 
} 


CMouseHook::CMouseHook(HINSTANCE hInstance) 
{ 
	m_hInstance = hInstance;    //DLLʵ����� 
} 

CMouseHook::~CMouseHook() 
{ 
	StopHook(); 
} 

//��װ���Ӳ��趨������ʾ���ھ�� 
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

//ж�ع��� 
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
