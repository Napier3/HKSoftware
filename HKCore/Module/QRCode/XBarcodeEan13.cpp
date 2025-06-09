// EAN13.cpp: implementation of the CXBarcodeEan13 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XBarcodeEan13.h"
#include "..\BaseClass\DIB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXBarcodeEan13::CXBarcodeEan13()
{
	m_nSymbology = EAN13;
}

CXBarcodeEan13::~CXBarcodeEan13()
{

}

void CXBarcodeEan13::LoadData(const CString &csMessage, double dNarrowBar, double dFinalHeight, long nGuardbarHeight, HDC hDC, int nStartingXPixel, int nStartingYPixel, double dRatio)
{
	m_nGuardbarHeight = nGuardbarHeight;
	CXBarcodeBase::LoadData(csMessage,dNarrowBar,dFinalHeight,hDC,nStartingXPixel,nStartingYPixel,dRatio);
}

long CXBarcodeEan13::CalculateCheckSumDigit()
{
	int i, nLen, nSum = 0, nItem;
	nLen = m_csMessage.GetLength();

	for (i = nLen ; i >= 1 ; i--)
	{
		nItem = i%2 ? ((int)m_csMessage.GetAt(i-1)-48)*1 : ((int)m_csMessage.GetAt(i-1)-48)*3;
		nSum += nItem;
	}

	CString strMessage=m_csMessage;
	nSum %= 10;
	nSum = (10-nSum)%10;
	strMessage.AppendFormat(_T("%d"), nSum);
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("EAN13 Code=%s"), strMessage);

	return nSum;
}


CString CXBarcodeEan13::RetrieveLeftOddParityPattern(int iNumber)
{
	CString strCharPattern;

	switch(iNumber){
		case 0: 
			strCharPattern = "sssbbsb"; 
			break;
		case 1: 
			strCharPattern = "ssbbssb";
			break;
		case 2: 
			strCharPattern = "ssbssbb"; 
			break;
		case 3: 
			strCharPattern = "sbbbbsb"; 
			break; 
		case 4: 
			strCharPattern = "sbsssbb"; 
			break; 
		case 5: 
			strCharPattern = "sbbsssb"; 
			break;
		case 6:
			strCharPattern = "sbsbbbb";
			break;
		case 7:
			strCharPattern = "sbbbsbb"; 
			break;
		case 8:
			strCharPattern = "sbbsbbb";
			break; 
		case 9:
			strCharPattern = "sssbsbb"; 
			break;
	}
	return strCharPattern;
}


CString CXBarcodeEan13::RetrieveLeftEvenParityPattern(int iNumber)
{
	CString strCharPattern;
	
	switch(iNumber){
		case 0: 
			strCharPattern = "sbssbbb";
			break;
		case 1: 
			strCharPattern = "sbbssbb";
			break; 
		case 2:
			strCharPattern = "ssbbsbb";
			break; 
		case 3: 
			strCharPattern = "sbssssb";
			break;
		case 4:
			strCharPattern = "ssbbbsb";
			break;
		case 5:
			strCharPattern = "sbbbssb";
			break;
		case 6: 
			strCharPattern = "ssssbsb";
			break; 
		case 7: 
			strCharPattern = "ssbsssb";
			break;
		case 8: 
			strCharPattern = "sssbssb"; 
			break;
		case 9:
			strCharPattern = "ssbsbbb";
			break;
	}
	return strCharPattern;
}


CString CXBarcodeEan13::RetrieveRightPattern(int iNumber)
{
	CString strCharPattern;
	
	switch(iNumber){
		case 0: 
			strCharPattern = "bbbssbs";
			break; 
		case 1:
			strCharPattern = "bbssbbs";
			break; 
		case 2: 
			strCharPattern = "bbsbbss";
			break; 
		case 3:
			strCharPattern = "bssssbs"; 
			break; 
		case 4:
			strCharPattern = "bsbbbss"; 
			break; 
		case 5:
			strCharPattern = "bssbbbs";
			break; 
		case 6: 
			strCharPattern = "bsbssss";
			break; 
		case 7: 
			strCharPattern = "bsssbss";
			break; 
		case 8:
			strCharPattern = "bssbsss";
			break; 
		case 9: 
			strCharPattern = "bbbsbss"; 
			break;
	}

	return strCharPattern;
}


CString CXBarcodeEan13::RetrieveCountryCodePattern(int iNumber)
{
	CString strCharPattern;
	
	switch(iNumber){
		case 0: 
			strCharPattern = "OOOOO";
			break;  
		case 1:
			strCharPattern = "OEOEE";
			break;  
		case 2: 
			strCharPattern = "OEEOE";
			break;  
		case 3:
			strCharPattern = "OEEEO";
			break;  
		case 4: 
			strCharPattern = "EOOEE"; 
			break;  
		case 5: 
			strCharPattern = "EEOOE";
			break;  
		case 6:
			strCharPattern = "EEEOO";
			break;  
		case 7: 
			strCharPattern = "EOEOE";
			break;  
		case 8: 
			strCharPattern = "EOEEO";
			break;  
		case 9:
			strCharPattern = "EEOEO";
			break;  
	}

	return strCharPattern;
}

void CXBarcodeEan13::DrawPattern(const CString &csPattern)
{
	int			i,nXPixel,nYPixel;
	CDC			oDC;

	// attach to the device context
	oDC.Attach(m_hDC);

	// initialize X pixel value
	nXPixel = m_nStartingXPixel;
	
	for (i=0;i<csPattern.GetLength();i++)
	{
		// X value for loop
		for (nXPixel=m_nStartingXPixel;nXPixel<m_nStartingXPixel+m_nNarrowBarPixelWidth;nXPixel++)
		{
			// Y value for loop
			for (nYPixel=m_nStartingYPixel;nYPixel<m_nStartingYPixel+m_nPixelHeight+m_nGuardbarHeight;nYPixel++)
			{
				// if this is a bar
				if (csPattern.GetAt(i)=='b')
					oDC.SetPixelV(nXPixel,nYPixel,COLORBLACK);

			//	else
				//	oDC.SetPixelV(nXPixel,nYPixel,COLORWHITE);
			}
		}

		// advance the starting position
		m_nStartingXPixel+= m_nNarrowBarPixelWidth;
	}

	// detach from the device context
	oDC.Detach();
	
	return;

}

void CXBarcodeEan13::DrawBitmap()
{
	int i, tmpGuardBarHeight;
	
	DrawPattern(_T("sssssssss")); // draw quite zone
	
	DrawPattern(_T("bsb")); // draw lead

	CString strCountryCodePattern;
	strCountryCodePattern = RetrieveCountryCodePattern((int)m_csMessage.GetAt(0)-48);

	tmpGuardBarHeight = m_nGuardbarHeight;
	m_nGuardbarHeight = 0;

	
	DrawPattern(RetrieveLeftOddParityPattern((int)m_csMessage.GetAt(1)-48));

	
	for (i = 2 ; i < 7 ; i ++){
		if (strCountryCodePattern[i-2] == 'O')
			DrawPattern(RetrieveLeftOddParityPattern((int)m_csMessage.GetAt(i)-48));

		if (strCountryCodePattern[i-2] == 'E')
			DrawPattern(RetrieveLeftEvenParityPattern((int)m_csMessage.GetAt(i)-48));
	}

	m_nGuardbarHeight = tmpGuardBarHeight;

	DrawPattern(_T("sbsbs")); // draw separator bars

	tmpGuardBarHeight = m_nGuardbarHeight;
	m_nGuardbarHeight = 0;
	for (i = 7 ; i < 12 ; i ++)
		DrawPattern(RetrieveRightPattern((int)m_csMessage.GetAt(i)-48));


	DrawPattern(RetrieveRightPattern(CalculateCheckSumDigit()));
	m_nGuardbarHeight = tmpGuardBarHeight;
	
	DrawPattern(_T("bsb")); // draw trailer bars
	DrawPattern(_T("sssssssss")); // draw quite zone 

}

void CXBarcodeEan13::BitmapToClipboard()
{
}

void xena_WriteXEna13File(const CString &strFilePath
						  , const CString &csMessage, double dNarrowBar
						  , double dFinalHeight, long nGuardbarHeight, double dRatio)
{
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteXEna13File EAN13 code=[%s]") , csMessage);
	//144*226
	CDC		memDC;
	memDC.CreateCompatibleDC(NULL);

	// get dpi for the two axes
	int nXAxisDpi = memDC.GetDeviceCaps(LOGPIXELSX);
	int nYAxisDpi = memDC.GetDeviceCaps(LOGPIXELSY);
	int nPixelHeight = (int)((nYAxisDpi*dFinalHeight)+0.5);
	int nPiexlWidth = 226;

	CDibDraw oDibDraw;
	oDibDraw.CreateDraw(nPiexlWidth, nPixelHeight);
	HDC hDC = oDibDraw.GetDrawDC();
	CXBarcodeEan13 oEan13;
	oEan13.LoadData(csMessage, dNarrowBar, dFinalHeight, nGuardbarHeight, hDC, 0, 0, dRatio);
	oEan13.DrawBitmap();

	oDibDraw.WriteToFile(strFilePath);
}

