// XBarcodeStrParser.h: interface for the CXBarcodeStrParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CXBarcodeStrParser_h_)
#define _CXBarcodeStrParser_h_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BARCODE_MODE_ONE_SEPERATER   1
#define BARCODE_MODE_TWO_SEPERATER   2

#define QRCODE_BUFFER_LEN   4096
#define QRCODE_TIMERID        1736
#define QRCODE_TIMERLONG    500

#include "..\System\TickCount32.h"
#include "..\DataMngr\Values.h"
#include "..\DataMngr\DvmDataset.h"
#include "..\DataMngr\ShortDatas.h"

class CXBarcodeStrParser
{
public:
	CXBarcodeStrParser();
	virtual ~CXBarcodeStrParser();
	
	CValues* GetValues()	{	return &m_oValues;	}
	CString GetQRCodeData()		{	return m_strQRCodeData;	}
	void SetSeparateChar(char chSeparateChar, char chSeparateCharEnd);
	void SetSeparateChar(const CString &strSeparateChar = _T("="), const CString &strSeparateEndChar = _T(";"));

	void InitParser();
	BOOL PreTranslateMessage(MSG* pMsg);
	void AddChars(WPARAM wParam);
	void SetQRCodeString(char *pBuffer, long nEncodeType);
	//BOOL FinishBarCodeInput();
	void GetDatas(CExBaseList *pDatas);
	void GetDatas(CDvmDataset *pDatas);
	void NewDatas(CShortDatas *pDatas);
	void NewDatas(CDvmDataset *pDatas);
	BOOL HasValues()	{	return m_oValues.GetCount();	}
	void SetShowLog(BOOL bShowLog=TRUE)	{	m_bShowLog = bShowLog;	}

protected:
	BOOL m_bShowLog;
	CValues m_oValues;
	//////////////////////////////////////////////////////////////////////////
	//ЬѕТы
	char m_pszBarCodeBuffer[QRCODE_BUFFER_LEN];
	long m_nBarCodeLen;
	CTickCount32  m_oCTickCount32;
	CString m_strQRCodeData;
	
// 	char m_chSeparateChar;
// 	char m_chSeparateEndChar;
	CString m_strSeparateChar;
	CString m_strSeparateEndChar;
	UINT m_nBarCodeMode;

	void OnQRCodeInput(long nEncodeType);
	void ParseBarCode2(const char *pBuffer);
	void ParseBarCode1(const char *pBuffer);

};

#endif // !defined(_CXBarcodeStrParser_h_)
