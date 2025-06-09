// DIB.cpp

#include "stdafx.h"
#include "BitmapFile.h"
#include "..\API\GloblaDrawFunctions.h"

CBitmapFile::CBitmapFile()
{
	m_bFirst = FALSE;
	m_bTransparent = FALSE;
}

CBitmapFile::~CBitmapFile()
{
	
}

BOOL CBitmapFile::LoadFile(const CString &strFile)
{
	m_hObject = ::LoadImage(NULL, strFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	return (m_hObject != NULL);
}

BOOL CBitmapFile::Draw( CDC *pDC, int nX, int nY,int nWidth, int nHeight,unsigned long unsrc)
{
	if (m_bTransparent)
	{
		if (!m_bFirst)
		{
			DrawTransparentBitmap(pDC, this, CRect(nX, nY, nX+nWidth, nY+nHeight), m_crMask);
			m_bFirst = TRUE;
			return TRUE;
		}
	}
	
	CDC ImageDC;
	CBitmap *pOldImage;

	ImageDC.CreateCompatibleDC(pDC);
	pOldImage=ImageDC.SelectObject(this);

	pDC->BitBlt(nX,nY,nWidth, nHeight, &ImageDC, 0, 0,SRCCOPY);
	ImageDC.SelectObject(pOldImage);

	return TRUE;
}

