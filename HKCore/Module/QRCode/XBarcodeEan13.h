// EAN13.h: interface for the CXBarcodeEan13 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CXBarcodeEan13_h_)
#define _CXBarcodeEan13_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XBarcodeBase.h"

class CXBarcodeEan13 : public CXBarcodeBase
{
public:
	CXBarcodeEan13();
	virtual ~CXBarcodeEan13();
	void LoadData(const CString &csMessage, double dNarrowBar, double dFinalHeight, long nGuardbarHeight, HDC hDC, int nStartingXPixel, int nStartingYPixel, double dRatio);
	void DrawBitmap();
	void BitmapToClipboard();
	long CalculateCheckSumDigit();

private:
	long  m_nGuardbarHeight;
	CString RetrieveLeftOddParityPattern(int iNumber);
	CString RetrieveLeftEvenParityPattern(int iNumber);
	CString RetrieveRightPattern(int iNumber);
	CString RetrieveCountryCodePattern(int iNumber);

	void DrawPattern(const CString &csPattern);

};

void xena_WriteXEna13File(const CString &strFilePath, const CString &csMessage, double dNarrowBar=0.02, double dFinalHeight=1.5, long nGuardbarHeight=20, double dRatio=0);

#endif // !defined(_CXBarcodeEan13_h_)
