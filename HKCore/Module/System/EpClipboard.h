// EpClipboard.h: interface for the CEpClipboard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPCLIPBOARD_H__)
#define _EPCLIPBOARD_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEpClipboard
{
public:
	CEpClipboard(HWND hWnd);
	virtual ~CEpClipboard();

	BOOL IsOpenClipboardSucc()		{	return m_bSuccess;		}
	BOOL Open(HWND hWnd);
	BOOL Close();

	BOOL SetClipboard(const CString &strSrc);
	BOOL GetClipboard(CString &strDest);
	BOOL IsClipboardText();

	BOOL SetClipboard(CBitmap *pBitmap);
	BOOL GetClipboard(CBitmap **pBitmap);
	BOOL IsClipboardBitmap();

protected:
	CEpClipboard();

	HWND m_hWndOwner;
	BOOL m_bSuccess;

	BOOL BitmapToClipboard(HBITMAP hBM);
};

#endif // !defined(_EPCLIPBOARD_H__)
