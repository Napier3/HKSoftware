// DIB.h

#ifndef __DIB_H__
#define __DIB_H__

#include "..\OSInterface\OSInterface.h"

class CDib
{
public:
	CDib();
	~CDib();
	void FreeMemeory();
	BOOL Load( const CString& strPath );
	BOOL Load( const char * );
	BOOL Save( const char * );
	BOOL Draw( CDC *, int nX = 0, int nY = 0,int nWidth = -1, int nHeight = -1,
		unsigned long unsrc=SRCCOPY );

	BOOL DrawEx( CDC *pDC
		, int nX, int nY, int nWidth, int nHeight
		, int xBmp, int yBmp, int widthBmp, int heightBmp
		,unsigned long unsrc=SRCCOPY);

	BOOL Draw(CDC *pDC,CRect Rect=CRect(0,0,0,0),unsigned long unsrc=SRCCOPY);
	BOOL SetPalette( CDC * );
	CRect GetDibRect();
	BOOL PatBltDraw(CDC*pDC,int nX, int nY, int nWidth, int nHeight,unsigned long unsrc);

	void SetTransparent(BOOL bTrans)	{	}
	void SetMaskColor(COLORREF cr)		{	}

private:
	CPalette m_Palette;
	unsigned char *m_pDib, *m_pDibBits;
	DWORD m_dwDibSize;
	BITMAPINFOHEADER *m_pBIH;
	RGBQUAD *m_pPalette;
	int m_nPaletteEntries;
};

class CDibDraw
{
public:
	CDibDraw();
	virtual ~CDibDraw();

private:
	//»æÍ¼Ä£¿é
	HDC m_hdc,m_hdcMem;
	HBITMAP m_hBitMap;
	CBitmap *m_pBitMap;
	CDC *m_pMemDC;
	LPBITMAPINFO m_lpbmih;
	BITMAPFILEHEADER m_bmfh;
	long m_iWidth, m_iHeight, m_iPixel;
	BYTE *m_pBits;

public:
	void CreateDraw(long iWidth, long iHeight, long iPixel=16);
	void FreeDraw();
	HDC GetDrawDC();
	void WriteToFile(const CString &strPath);
	BOOL CopyToClipboard(HWND hWnd);
};

BOOL dib_CopyToClipboard(HWND hWnd, HBITMAP hBitmap);


#endif
