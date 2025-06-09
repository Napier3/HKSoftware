#pragma once

#define ID_EDIT	  180
#define ID_TEXT   200


class CXDialogBase
{
public:
	CXDialogBase(HWND hwndOwner = NULL);
	virtual ~CXDialogBase(void);

public:
	virtual INT_PTR DoModal(long x=0, long y=0, long cx=100, long cy=100, DWORD dwStyle=WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION);
	virtual BOOL DoModeless(long x=0, long y=0, long cx=100, long cy=100, DWORD dwStyle=WS_POPUP | WS_BORDER | WS_SYSMENU | DS_MODALFRAME | WS_CAPTION);
	HWND m_hDialog;

	virtual void OnInitionDialog(){}

protected:

	// API中注册的消息处理函数，不能是成员函数，因为成员函数有this指针
	static BOOL CALLBACK XDialogProc(HWND hWnd,
		UINT uMsg, WPARAM wParam, LPARAM lParam);
private:

	HWND  m_hOwnerWnd;
	HINSTANCE m_hInst;

	LPWORD lpwAlign ( LPWORD lpIn)
	{
		ULONG ul;

		ul = (ULONG) lpIn;
		ul +=3;
		ul >>=2;
		ul <<=2;
		return (LPWORD) ul;
	}

};
