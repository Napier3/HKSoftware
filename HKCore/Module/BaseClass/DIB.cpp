// DIB.cpp

#include "stdafx.h"
#include "DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDib::CDib()
{
	m_pDib = NULL;

}

CDib::~CDib()
{
	FreeMemeory();
}

void CDib::FreeMemeory()
{
	if( m_pDib != NULL )
	{
		delete [] m_pDib;
		m_pDib=NULL;
	}
}

BOOL CDib::Load( const CString& strPath )
{
	CFile cf;
	if( !cf.Open(strPath,CFile::modeRead))
		return FALSE;
	DWORD dwDibSize=cf.GetLength()-sizeof(BITMAPFILEHEADER);
	unsigned char *pDib=new unsigned char [dwDibSize];
	if(pDib==NULL)return FALSE;
	BITMAPFILEHEADER BFH;
	try
	{
		if(cf.Read(&BFH,sizeof(BITMAPFILEHEADER))!= sizeof( BITMAPFILEHEADER ) ||BFH.bfType != 'MB' ||cf.Read( pDib, dwDibSize ) != dwDibSize )
		{
			delete [] pDib;
			return( FALSE );
		}
	}
	catch( CFileException *e )
	{
		e->Delete();
		delete [] pDib;
		return FALSE;
	}
	if(m_pDib!= NULL)delete m_pDib;
	m_pDib = pDib;
	m_dwDibSize = dwDibSize;
	m_pBIH = (BITMAPINFOHEADER *) m_pDib;
	m_pPalette =(RGBQUAD *) &m_pDib[sizeof(BITMAPINFOHEADER)];
	m_nPaletteEntries = 1 << m_pBIH->biBitCount;
	if( m_pBIH->biBitCount > 8 )
		m_nPaletteEntries = 0;
	else if( m_pBIH->biClrUsed != 0 )
		m_nPaletteEntries = m_pBIH->biClrUsed;
	m_pDibBits =&m_pDib[sizeof(BITMAPINFOHEADER)+m_nPaletteEntries*sizeof(RGBQUAD)];
	if( m_Palette.GetSafeHandle() != NULL )
		m_Palette.DeleteObject();
	if( m_nPaletteEntries != 0 ){
		LOGPALETTE *pLogPal = (LOGPALETTE *) new char[sizeof(LOGPALETTE)+m_nPaletteEntries*sizeof(PALETTEENTRY)];
		if( pLogPal != NULL ){
			pLogPal->palVersion = 0x300;
			pLogPal->palNumEntries = m_nPaletteEntries;
			for( int i=0; i<m_nPaletteEntries; i++ ){
				pLogPal->palPalEntry[i].peRed=m_pPalette[i].rgbRed;
				pLogPal->palPalEntry[i].peGreen=m_pPalette[i].rgbGreen;
				pLogPal->palPalEntry[i].peBlue=m_pPalette[i].rgbBlue;
			}
			m_Palette.CreatePalette( pLogPal );
			delete [] pLogPal;
		}
	}
	return( TRUE );
}

BOOL CDib::Load( const char *pszFilename )
{
	CFile cf;
#ifdef _UNICODE
	if( !cf.Open(_bstr_t(pszFilename),CFile::modeRead))
#else
	if( !cf.Open(pszFilename,CFile::modeRead))
#endif
		return FALSE;

	DWORD dwDibSize=cf.GetLength()-sizeof(BITMAPFILEHEADER);
	unsigned char *pDib=new unsigned char [dwDibSize];
	if(pDib==NULL)return FALSE;
	BITMAPFILEHEADER BFH;
	try
	{
		if(cf.Read(&BFH,sizeof(BITMAPFILEHEADER))!= sizeof( BITMAPFILEHEADER ) ||BFH.bfType != 'MB' ||cf.Read( pDib, dwDibSize ) != dwDibSize )
		{
			delete [] pDib;
			return( FALSE );
		}
	}
	catch( CFileException *e )
	{
		e->Delete();
		delete [] pDib;
		return FALSE;
	}
	if(m_pDib!= NULL)delete m_pDib;
	m_pDib = pDib;
	m_dwDibSize = dwDibSize;
	m_pBIH = (BITMAPINFOHEADER *) m_pDib;
	m_pPalette =(RGBQUAD *) &m_pDib[sizeof(BITMAPINFOHEADER)];
	m_nPaletteEntries = 1 << m_pBIH->biBitCount;
	if( m_pBIH->biBitCount > 8 )
		m_nPaletteEntries = 0;
	else if( m_pBIH->biClrUsed != 0 )
		m_nPaletteEntries = m_pBIH->biClrUsed;
	m_pDibBits =&m_pDib[sizeof(BITMAPINFOHEADER)+m_nPaletteEntries*sizeof(RGBQUAD)];
	if( m_Palette.GetSafeHandle() != NULL )
		m_Palette.DeleteObject();
	if( m_nPaletteEntries != 0 ){
		LOGPALETTE *pLogPal = (LOGPALETTE *) new char[sizeof(LOGPALETTE)+m_nPaletteEntries*sizeof(PALETTEENTRY)];
		if( pLogPal != NULL ){
			pLogPal->palVersion = 0x300;
			pLogPal->palNumEntries = m_nPaletteEntries;
			for( int i=0; i<m_nPaletteEntries; i++ ){
				pLogPal->palPalEntry[i].peRed=m_pPalette[i].rgbRed;
				pLogPal->palPalEntry[i].peGreen=m_pPalette[i].rgbGreen;
				pLogPal->palPalEntry[i].peBlue=m_pPalette[i].rgbBlue;
				}
			m_Palette.CreatePalette( pLogPal );
			delete [] pLogPal;
			}
		}
	return( TRUE );
}

BOOL CDib::Save( const char *pszFilename )
{

	// If we have no data, we can't save.
	if( m_pDib == NULL )
		return( FALSE );

	CFile cf;

	// Attempt to create the file.

#ifdef _UNICODE
	if( !cf.Open( _bstr_t(pszFilename),
		CFile::modeCreate | CFile::modeWrite ) )
#else
	if( !cf.Open( pszFilename,
		CFile::modeCreate | CFile::modeWrite ) )
#endif
		return( FALSE );
	
	// Write the data.
	try{

		// First, create a BITMAPFILEHEADER
		// with the correct data.
		BITMAPFILEHEADER BFH;
		memset( &BFH, 0, sizeof( BITMAPFILEHEADER ) );
		BFH.bfType = 'MB';
		BFH.bfSize = sizeof( BITMAPFILEHEADER ) + m_dwDibSize;
		BFH.bfOffBits = sizeof( BITMAPFILEHEADER ) +
			sizeof( BITMAPINFOHEADER ) +
			m_nPaletteEntries * sizeof( RGBQUAD );

		// Write the BITMAPFILEHEADER and the
		// Dib data.
		cf.Write( &BFH, sizeof( BITMAPFILEHEADER ) );
		cf.Write( m_pDib, m_dwDibSize );
		}

	// If we get an exception, delete the exception and
	// return FALSE.
	catch( CFileException *e ){
		e->Delete();
		return( FALSE );
		}

	return( TRUE );

}

BOOL CDib::Draw(CDC *pDC,CRect Rect,unsigned long unsrc)
{
	CPoint point;
	int nWidth,nHeight;
	point=Rect.TopLeft();
	nWidth=Rect.Width();
	nHeight=Rect.Height();
	if(nWidth==0)nWidth=-1;
	if(nHeight==0)nHeight=-1;
	return Draw(pDC,point.x,point.y,nWidth,nHeight,unsrc);
}


BOOL CDib::Draw( CDC *pDC, int nX, int nY, int nWidth, int nHeight,unsigned long unsrc)
{
	if( m_pDib == NULL )
		return( FALSE );

	if( nWidth == -1 )
		nWidth = m_pBIH->biWidth;
	if( nHeight == -1 )
		nHeight = m_pBIH->biHeight;
	
	StretchDIBits( pDC->m_hDC, nX, nY,nWidth, nHeight,0, 0,	m_pBIH->biWidth, m_pBIH->biHeight,m_pDibBits,	(BITMAPINFO *) m_pBIH,BI_RGB, unsrc );

	return( TRUE );
}

BOOL CDib::DrawEx( CDC *pDC
				  , int nX, int nY, int nWidth, int nHeight
				  , int xBmp, int yBmp, int widthBmp, int heightBmp
				  ,unsigned long unsrc)
{
	if( m_pDib == NULL )
		return( FALSE );

	if( nWidth == -1 )
		nWidth = m_pBIH->biWidth;
	if( nHeight == -1 )
		nHeight = m_pBIH->biHeight;
	
	StretchDIBits(pDC->m_hDC, nX, nY,nWidth, nHeight, xBmp, yBmp, widthBmp, heightBmp, m_pDibBits, (BITMAPINFO *) m_pBIH,BI_RGB, unsrc );

	return( TRUE );
}

BOOL CDib::PatBltDraw(CDC*pDC,int nX, int nY, int nWidth, int nHeight,unsigned long unsrc)
{

	return( TRUE );
}
CRect CDib::GetDibRect()
{
	if( m_pDib == NULL )
		return CRect(0,0,0,0);
	CRect rect=CRect(0,0,0,0);
	rect.bottom=m_pBIH->biHeight;
	rect.right=m_pBIH->biWidth;
	return rect;
}
BOOL CDib::SetPalette( CDC *pDC )
{
	if( m_pDib == NULL )
		return( FALSE );
	if( m_Palette.GetSafeHandle() == NULL )
		return( TRUE );

	CPalette *pOldPalette;
	pOldPalette = pDC->SelectPalette( &m_Palette, FALSE );
	pDC->RealizePalette();
	pDC->SelectPalette( pOldPalette, FALSE );

	return( TRUE );

}


//////////////////////////////////////////////////////////////////////////
CDibDraw::CDibDraw()
{
	m_hdc = NULL;
	m_hdcMem = NULL;
	m_hBitMap = NULL;
	m_pBitMap = NULL;
	m_pMemDC = NULL;
	m_iWidth = 800;
	m_iHeight = 600;
	m_pBits = NULL;
	m_iPixel  = 16;
	m_lpbmih = NULL;
}

CDibDraw::~CDibDraw()
{
	FreeDraw();
}

void CDibDraw::CreateDraw(long iWidth, long iHeight, long iPixel)
{
	if (m_lpbmih != NULL)
	{
		return;
	}

	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iPixel = iPixel;

	m_lpbmih = new BITMAPINFO;
	m_lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_lpbmih->bmiHeader.biWidth = iWidth;
	m_lpbmih->bmiHeader.biHeight = iHeight;
	m_lpbmih->bmiHeader.biPlanes = 1;
	m_lpbmih->bmiHeader.biBitCount = m_iPixel;
	m_lpbmih->bmiHeader.biCompression = BI_RGB;
	m_lpbmih->bmiHeader.biSizeImage = 0;
	m_lpbmih->bmiHeader.biXPelsPerMeter = 0;
	m_lpbmih->bmiHeader.biYPelsPerMeter = 0;
	m_lpbmih->bmiHeader.biClrUsed = 0;
	m_lpbmih->bmiHeader.biClrImportant = 0;

	m_hdc = CreateIC(TEXT("DISPLAY"),NULL,NULL,NULL);
	m_hdcMem = CreateCompatibleDC(m_hdc);
	m_hBitMap = CreateDIBSection(m_hdcMem,m_lpbmih,DIB_PAL_COLORS,(void **)&m_pBits,NULL,0);
	m_pBitMap = new CBitmap;
	m_pBitMap->Attach(m_hBitMap);
	m_pMemDC = new CDC;
	m_pMemDC->Attach(m_hdcMem);
	m_pMemDC->SelectObject(m_pBitMap);
	m_pMemDC->SetBkMode(TRANSPARENT);

	//Ìí¼Ó×Ô»æÍ¼ÐÎ 
	CBrush brushCtl;
	brushCtl.CreateSolidBrush(RGB(255,255,255));
	CRect rc = CRect(0,0,iWidth,iHeight);
	//m_pMemDC->Rectangle(rc);
	m_pMemDC->FillRect(rc,&brushCtl) ;
	brushCtl.DeleteObject();

	ZeroMemory(&m_bmfh,sizeof(BITMAPFILEHEADER));
	*((char *)&m_bmfh.bfType) = 'B';
	*(((char *)&m_bmfh.bfType) + 1) = 'M';
	m_bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	m_bmfh.bfSize = m_bmfh.bfOffBits + (iWidth * iHeight) * m_iPixel / 8;

	int iBMPBytes = iWidth * iHeight * m_iPixel / 8;

}

void CDibDraw::FreeDraw()
{
	if (m_pMemDC != NULL)
	{
		m_pMemDC->DeleteDC();
		delete m_pMemDC;
		m_pMemDC = NULL;
	}

	if (m_pBitMap != NULL)
	{
		delete m_pBitMap;
		m_pBitMap = NULL;
	}

	if (m_lpbmih != NULL)
	{
		delete m_lpbmih;
		m_lpbmih  = NULL;
	}
}

HDC CDibDraw::GetDrawDC()
{
	return m_hdcMem;
}

void CDibDraw::WriteToFile(const CString &strPath)
{
	CFile file;
	int iBMPBytes = m_iWidth * m_iHeight * m_iPixel / 8;

	if(file.Open(strPath,CFile::modeWrite | CFile::modeCreate))
	{
		file.Write(&m_bmfh,sizeof(BITMAPFILEHEADER));
		file.Write(&(m_lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER));
		file.Write(m_pBits,iBMPBytes);
		file.Close();
	}
}

BOOL CDibDraw::CopyToClipboard(HWND hWnd)
{
	if (!::OpenClipboard(hWnd))
		return false;

	BOOL bRet = dib_CopyToClipboard(hWnd, m_hBitMap);
	::CloseClipboard();

	return bRet;
}

BOOL dib_CopyToClipboard(HWND hWnd, HBITMAP hBitmap)
{
	::EmptyClipboard();

	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	BITMAPINFOHEADER bi;
	::ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bm.bmWidth;
	bi.biHeight = bm.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = bm.bmBitsPixel;
	bi.biCompression = BI_RGB;

	if (bi.biBitCount <= 1)	// make sure bits per pixel is valid
	{
		bi.biBitCount = 1;
	}
	else if (bi.biBitCount <= 4)
	{
		bi.biBitCount = 4;
	}
	else if (bi.biBitCount <= 8)
	{
		bi.biBitCount = 8;
	}
	else // if greater than 8-bit, force to 24-bit
	{
		bi.biBitCount = 24;
	}

	// Get size of color table.
	SIZE_T dwColTableLen = (bi.biBitCount <= 8) ? (1 << bi.biBitCount) * sizeof(RGBQUAD) : 0;

	// Create a device context with palette
	HDC hDC = ::GetDC(NULL);
	HPALETTE hPal = static_cast<HPALETTE>(::GetStockObject(DEFAULT_PALETTE));
	HPALETTE hOldPal = ::SelectPalette(hDC, hPal, FALSE);
	::RealizePalette(hDC);

	// Use GetDIBits to calculate the image size.
	::GetDIBits(hDC, hBitmap, 0, static_cast<UINT>(bi.biHeight), NULL,reinterpret_cast<LPBITMAPINFO>(&bi), DIB_RGB_COLORS);
	
	// If the driver did not fill in the biSizeImage field, then compute it.
	// Each scan line of the image is aligned on a DWORD (32bit) boundary.
	if (0 == bi.biSizeImage)
	{
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) * bi.biHeight;
	}

	// Allocate memory
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_MOVEABLE, sizeof(BITMAPINFOHEADER) + dwColTableLen + bi.biSizeImage);

	if (hDIB)
	{
		union tagHdr_u
		{
			LPVOID             p;
			LPBYTE             pByte;
			LPBITMAPINFOHEADER pHdr;
			LPBITMAPINFO       pInfo;
		} Hdr;

		Hdr.p = ::GlobalLock(hDIB);
		// Copy the header
		::CopyMemory(Hdr.p, &bi, sizeof(BITMAPINFOHEADER));
		// Convert/copy the image bits and create the color table
		int nConv = ::GetDIBits(hDC, hBitmap, 0, static_cast<UINT>(bi.biHeight),
			Hdr.pByte + sizeof(BITMAPINFOHEADER) + dwColTableLen, 
			Hdr.pInfo, DIB_RGB_COLORS);
		::GlobalUnlock(hDIB);
	
		if (!nConv)
		{
			::GlobalFree(hDIB);
			hDIB = NULL;
		}
	}

	if (hDIB)
	{
		::SetClipboardData(CF_DIB, hDIB);
	}

	::SelectPalette(hDC, hOldPal, FALSE);
	::ReleaseDC(NULL, hDC);

	return NULL != hDIB;
}

