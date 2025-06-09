// WndApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WndApi.h"

HWND GetSysTrayWnd()
{
	HWND hwnd ;
	hwnd = ::FindWindow(_T("Shell_TrayWnd"), NULL ) ;
	hwnd = ::FindWindowEx(hwnd, 0, _T("TrayNotifyWnd"), NULL );

	return hwnd ;
}

void RefurbishTray()
{
	RECT   WindowRect ;
	POINT point  ;
	int x ;
	int y ; 
	HWND hwnd = GetSysTrayWnd()  ; 
	::GetWindowRect(hwnd , &WindowRect ) ;
	::GetCursorPos(&point) ;
	for( x = 1 ; x < WindowRect.right - WindowRect.left - 1  ; x ++  )
	{
		for( y = 1 ; y < WindowRect.bottom - WindowRect.top - 1 ; y ++  )
		{
			SetCursorPos( WindowRect.left + x, WindowRect.top + y ) ;
			Sleep(0);
		}
	}
}  