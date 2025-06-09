// Barcode.h: interface for the CXBarcodeBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XBarcodeBase_h_)
#define _XBarcodeBase_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum XBarcode_Symbology
{
   RATIONALCODABAR,
   TRADITIONALCODABAR,
   I2OF5,
   CODE39,
   COD128,
   UPCEAN,
   CODE93,
   EAN8,	// new symbology
   EAN13	// new symbology
};

#define		COLORWHITE	0x00FFFFFF
#define		COLORBLACK	0x00000000

#include "..\BaseClass\DIB.h"

class CXBarcodeBase  
{
public:
	CXBarcodeBase();
	void	LoadData(const CString &csMessage, double dNarrowBar, double dFinalHeight, HDC pDC, int nStartingXPixel, int nStartingYPixel, double dRatio = 1.0);
	virtual void DrawBitmap() = 0;
	virtual void BitmapToClipboard() = 0;
	virtual ~CXBarcodeBase();
	long	GetBarcodePixelWidth();
	long	GetBarcodePixelHeight();
protected:
	CString m_csMessage;
	HDC		m_hDC;
	long	m_nFinalBarcodePixelWidth;
	long	m_nNarrowBarPixelWidth;
	long	m_nPixelHeight;
	long	m_nStartingXPixel;
	long	m_nStartingYPixel;
	long	m_nSymbology;
	long	m_nWideBarPixelWidth;
	virtual void DrawPattern(const CString &csPattern) = 0;
};

#endif // !defined(_XBarcodeBase_h_)
