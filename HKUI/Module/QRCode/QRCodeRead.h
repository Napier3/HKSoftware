#pragma once

#include "..\Serial\Serial.h"
#include "..\Serial\SerialGlobalDefine.h"
#include "..\DataMngr\DvmDataset.h"
#include "XBarcodeStrParser.h"

#define WM_QRCODEREAD_FINISH (WM_USER+2012)

//m_nEncodeType = 0;为utf8编码   m_nEncodeType = 1;为GBK编码       m_nEncodeType = 2;为ASCII编码
#define QRCODE_EncodeType_utf8     0
#define QRCODE_EncodeType_GBK     1
#define QRCODE_EncodeType_ASCII   2
#define QRCODE_EncodeType_none    -1

#define Separate_CHAR_MAP_MAX  8

CString qr_GetEncodeTypeString(long nEncodeType);
long qr_GetEncodeTypeID(const CString &strEncodeType);

//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
//CQRCodeReadXmlRWKeys

class CQRCodeReadXmlRWKeys : public CXmlRWKeys
{
private:
	CQRCodeReadXmlRWKeys();
	virtual ~CQRCodeReadXmlRWKeys();
	static long g_nQRXmlKeysRef;

public:
	static CQRCodeReadXmlRWKeys* g_pQRXmlKeys;
	static CQRCodeReadXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strSerialKey; //macro-test-config
	BSTR m_strValueKey; //test-macro-configs
	BSTR m_strPortNumberKey; //port_number
	BSTR m_strBaudRateKey; //baud-rate
	BSTR m_strParityKey; //byte-size
	BSTR m_strByteSizeKey; //stop-bit
	BSTR m_strStopsbitKey; //parity

	BSTR m_strWriteLogKey;//WriteLog
	BSTR m_strEncodeTypeKey;//EncodeType
	BSTR m_strSeparateCharKey;
	BSTR m_strSeparateEndCharKey;

	BSTR m_strQRCodeKey; //qrcode-config
	BSTR m_strQRCodeSepCharsKey; //separate_chars
	BSTR m_strQRCodeSepEndCharsKey; //separate_end_chars
	BSTR m_strChnHeadCharInvalidKey;

public:
	static BSTR CQRCodeSepCharKey()  {   return g_pQRXmlKeys->m_strSeparateCharKey;  }
	static BSTR CQRCodeSepCharsKey()  {   return g_pQRXmlKeys->m_strQRCodeSepCharsKey;  }
	static BSTR CQRCodeSepEndCharsKey()  {   return g_pQRXmlKeys->m_strQRCodeSepEndCharsKey;  }
	static BSTR CQRCodeKey()  {   return g_pQRXmlKeys->m_strQRCodeKey;  }

};


//////////////////////////////////////////////////////////////////////////
//CQRCodeReadSepChar
class CQRCodeReadSepChar : public CExBaseObject
{
public:
	CQRCodeReadSepChar();
	virtual ~CQRCodeReadSepChar();

public:
	virtual BSTR GetXmlElementKey()  {      return CQRCodeReadXmlRWKeys::CQRCodeSepCharKey();     }

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};


class CQRCodeReadSepChars : public CExBaseList
{
public:
	CQRCodeReadSepChars();
	virtual ~CQRCodeReadSepChars();

public:
	virtual BSTR GetXmlElementKey()  {      return CQRCodeReadXmlRWKeys::CQRCodeSepCharsKey();     }

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	void AddSepChar(const CString &strSepChar);
	void InitSepChars();
};

class CQRCodeReadSepEndChars : public CQRCodeReadSepChars
{
public:
	CQRCodeReadSepEndChars();
	virtual ~CQRCodeReadSepEndChars();

public:
	virtual BSTR GetXmlElementKey()  {      return CQRCodeReadXmlRWKeys::CQRCodeSepEndCharsKey();     }

};

class CQRCodeReadConfigs  : public CExBaseList
{
public:
	CQRCodeReadConfigs();
	virtual ~CQRCodeReadConfigs();

public:
	long m_nPortNo;
	long m_nBaud;
	long m_nParity;
	long m_nDatabits;
	long m_nStopsbits;
	long m_nEncodeType;//m_nEncodeType = 0;为utf8编码   m_nEncodeType = 1;为GBK编码       m_nEncodeType = 2;为ASCII编码
	CString m_strSeparateChar;
	CString m_strSeparateEndChar;
	CString m_strSeparateCharBk;
	CString m_strSeparateEndCharBk;
	long m_nLogFile;

	CQRCodeReadSepChars *m_pQRCodeReadSepChars;
	CQRCodeReadSepEndChars *m_pQRCodeReadSepEndChars;

	//2021-1-7  lijunqing 中文字符开头的二维码，头字符为无效
	long m_nChnHeadCharInvalid;

public:
	virtual BSTR GetXmlElementKey()  {      return CQRCodeReadXmlRWKeys::CQRCodeKey();     }

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual void InitAfterRead();

	virtual BOOL OpenCfgFile();
	virtual BOOL SaveCfgFile();

	CString GetCfgFile();

public:
	void In_ValidateSepChars(const CString &strQRCode);
	void In_ValidateSepChars(const CString &strQRCode, const CString &strSepChar, long &nBeginPos, long &nCount);
	void In_ValidateSepChars(const CString &strQRCode, CString &strSepChar, CExBaseList *pListSepChars, long &nBeginPos, long &nCount);

};

//////////////////////////////////////////////////////////////////////////
//CQRCodeRead
class CQRCodeRead : public CQRCodeReadConfigs
{
private:
	CQRCodeRead();
	virtual ~CQRCodeRead();

	static long g_nQRCodeReadRef;
	static CQRCodeRead* g_pQRCodeRead;

	static CFile m_file;

public:
	static CQRCodeRead* Create();
	static void Release();
	
	static void AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg=WM_QRCODEREAD_FINISH);
	static void DetachMsgWnd();
	static long GetQRCodeValues(CValues &oValues, BOOL bFreeValues);
	static CString GetQRCodeData();
	static void InitQRCodeReadParser(char chSeparateChar = '=', char chSeparateEndChar = ';');
	static void InitQRCodeReadParser(const CString &strSeparateChar = _T("="), const CString &strSeparateEndChar = _T(";"));
	static void GetDatas(CShortDatas *pDatas);
	static void GetDatas(CDvmDataset *pDatas);
	static void NewDatas(CShortDatas *pDatas);
	static void NewDatas(CDvmDataset *pDatas);
	static void DebugWrite(char *pszBuffer);
	static BOOL Match(CDvmDataset *pDatas);
	static BOOL Match(CShortDatas *pDatas);
	static long GetQrCodeEnType();
	static void SetQrCodeEnType(long nEnType);
	static void InputQRCodeString(const CString &strQRCode);
	static void InputQRCodeStringEx(const CString &strQRCode);
	static void ValidateSepChars(const CString &strQRCode);

protected:
	void In_InputQRCodeString(const CString &strQRCode);
	void In_InputQRCodeStringEx(const CString &strQRCode);
	void In_AttachMsgRcvWnd(CWnd *pMsgRcvWnd, UINT nMsg=WM_QRCODEREAD_FINISH);
	void In_DetachMsgWnd();
	long In_GetQRCodeValues(CValues &oValues, BOOL bFreeValues);
	CString In_GetQRCodeData();
	void In_InitQRCodeReadParser(char chSeparateChar, char chSeparateEndChar);
	void In_InitQRCodeReadParser(const CString &strSeparateChar = _T("="), const CString &strSeparateEndChar = _T(";"));
	void In_GetDatas(CShortDatas *pDatas);
	void In_GetDatas(CDvmDataset *pDatas);
	void In_NewDatas(CShortDatas *pDatas);
	void In_NewDatas(CDvmDataset *pDatas);
	void In_DebugWrite(char *pszBuffer);
	BOOL In_Match(CDvmDataset *pDatas);
	BOOL In_Match(CShortDatas *pDatas);

	virtual BOOL OpenCfgFile();
	bool InitQRCodeRead();
	void CloseQRCodeRead();
	void CreateQRCodeReadThread();
	void ReadQRCodeBuffer(char *pDestBuffer);
	char* ReadQRCodeBuffer();
	int UnicodeToChar(char *UnicodeText, /*char *ASCText, */int UnicodeLength);
	void ConvertUtf8ToGBK(BYTE *pszUtf8);

protected:
	void WriteLog(char *pszLog);

	CSerial *m_pSerial;
	BOOL m_bOpenSerialSucc;
	BOOL m_bInOpenSerial;
	CWinThread *m_pQRReadThread;

	BYTE m_byteQRCodeBuffer[1024];
	DWORD m_nRcvBufLen;
	CXBarcodeStrParser m_oXBarcodeStrParser;

	CWnd *m_pMsgRcv;
	UINT m_nMsgRcv;

protected:
	static UINT ReadSerialDataThread(LPVOID pParam);
	BOOL m_bExitQRCodeReadThread;
	
protected:
	void ReadSerialData();
	void OffsetSerialData();
	void WaiteInputQrCodeData();
	BOOL IsValidateChar(BYTE ch);

private:
	static CString g_astrSeparateSrc[Separate_CHAR_MAP_MAX];
	static CString g_astrSeparateDest[Separate_CHAR_MAP_MAX];

	BOOL ChangeSeparate(long nMapIndex);
	void ChangeSeparate(CString &strSeparate, const CString &strValue);
};

BOOL QR_WriteQRCodePngFile(const char *pszQRData, const char *pszPngFile);
