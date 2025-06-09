// EpClipboard.cpp: implementation of the CEpClipboard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpClipboard.h"
#include "..\API\StringApi.h"
#include "..\BaseClass\DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpClipboard::CEpClipboard(HWND hWnd)
{
	Open(hWnd);
}

CEpClipboard::~CEpClipboard()
{
	Close();
}

BOOL CEpClipboard::Open(HWND hWnd)
{
	m_hWndOwner = hWnd;
	m_bSuccess = OpenClipboard(m_hWndOwner);
	return m_bSuccess;
}

BOOL CEpClipboard::Close()
{
	m_bSuccess = FALSE;
	return CloseClipboard(); 
}

BOOL CEpClipboard::SetClipboard(const CString &strSrc)
{
	if (!m_bSuccess)
	{
		return FALSE;
	}

	HGLOBAL clipbuffer; 
	char * buffer; 
	EmptyClipboard(); 
	long nLen = 0;

#ifdef UNICODE
	nLen = strSrc.GetLength() * 2 + 2;
#else
	nLen = strSrc.GetLength() + 1;
#endif

	clipbuffer = GlobalAlloc(GMEM_DDESHARE, nLen); 
	buffer = (char*)GlobalLock(clipbuffer); 
	CString_to_char(strSrc, buffer);
	GlobalUnlock(clipbuffer); 
	SetClipboardData(CF_TEXT,clipbuffer); 
	Close();

	return m_bSuccess;
}

BOOL CEpClipboard::GetClipboard(CString &strDest)
{
	if (!m_bSuccess)
	{
		return FALSE;
	}

	char * buffer = NULL; 
	HANDLE hData = GetClipboardData(CF_TEXT); 

	if (hData == NULL)
	{
		return FALSE;
	}

	buffer = (char*)GlobalLock(hData); 
	strDest = buffer; 
	GlobalUnlock(hData); 

	return m_bSuccess;
}

BOOL CEpClipboard::IsClipboardText()
{
	if (!m_bSuccess)
	{
		return FALSE;
	}

	char * buffer = NULL; 
	HANDLE hData = GetClipboardData(CF_TEXT); 

	return (hData != NULL);
}


/*
if(OpenClipboard()) 
{ 
	EmptyClipboard(); 
	CBitmap * junk = new CBitmap(); 
	CClientDC cdc(this); 
	CDC dc; 
	dc.CreateCompatibleDC(&cdc); 
	CRect client(0,0,200,200); 
	junk->CreateCompatibleBitmap(&cdc,client.Width(),client.Height()); 
	dc.SelectObject(junk); 
	DrawImage(&dc,CString("Bitmap")); 
	//复制数据到剪贴板 
	SetClipboardData(CF_BITMAP,junk->m_hObject); 
	CloseClipboard(); 
	delete junk; 
} 

*/

BOOL CEpClipboard::SetClipboard(CBitmap *pBitmap)
{
	if (!m_bSuccess)
	{
		return FALSE;
	}

	ASSERT (pBitmap != NULL);

	if (pBitmap == NULL)
	{
		return FALSE;
	}

	HBITMAP hBitmap = (HBITMAP)pBitmap->GetSafeHandle();
	EmptyClipboard(); 
	//SetClipboardData(CF_BITMAP,pBitmap->GetSafeHandle()); 
	BitmapToClipboard(hBitmap);

	return m_bSuccess;
}

BOOL CEpClipboard::BitmapToClipboard(HBITMAP hBM)
{
	if ( !IsOpenClipboardSucc())
	{
		return FALSE;
	}

	EmptyClipboard();

	BOOL bRet = dib_CopyToClipboard(m_hWndOwner, hBM);

	Close();

	return bRet;
}

/*
if(OpenClipboard()) 
{ 
	//获得剪贴板数据 
	HBITMAP handle = (HBITMAP)GetClipboardData(CF_BITMAP); 
	CBitmap * bm = CBitmap::FromHandle(handle); 
	CClientDC cdc(this); 
	CDC dc; 
	dc.CreateCompatibleDC(&cdc); 
	dc.SelectObject(bm); 
	cdc.BitBlt(0,0,200,200,&dc,0,0,SRCCOPY); 
	CloseClipboard(); 
} 

*/
BOOL CEpClipboard::GetClipboard(CBitmap **ppBitmap)
{
	if (!m_bSuccess)
	{
		return FALSE;
	}
	
	ASSERT (ppBitmap != NULL);

	if (ppBitmap == NULL)
	{
		return FALSE;
	}

	//获得剪贴板数据 
	HBITMAP handle = (HBITMAP)GetClipboardData(CF_BITMAP); 
	
	if (handle == NULL)
	{
		return FALSE;
	}

	*ppBitmap = CBitmap::FromHandle(handle); 

	return m_bSuccess;
}

BOOL CEpClipboard::IsClipboardBitmap()
{
	if (!m_bSuccess)
	{
		Open(m_hWndOwner);
	}

	if (!IsOpenClipboardSucc())
	{
		return FALSE;
	}

	char * buffer = NULL; 
	HANDLE hData = GetClipboardData(CF_BITMAP); 

	if (hData != NULL)
	{
		return TRUE;
	}

	hData = GetClipboardData(CF_DIB); 
	Close();

	return (hData != NULL);
}

