#pragma once

#define SERIAL_CHECKBYTE_NONE    0    //(_T("无校验"));
#define SERIAL_CHECKBYTE_ODD     1    //(_T("奇校验"));
#define SERIAL_CHECKBYTE_EVEN    2    //(_T("偶校验"));

#define SERIAL_CHECKBYTE_STRING_NONE    _T("none")    //(_T("无校验"));
#define SERIAL_CHECKBYTE_STRING_ODD     _T("odd")    //(_T("奇校验"));
#define SERIAL_CHECKBYTE_STRING_EVEN    _T("even")    //(_T("偶校验"));

#define SERIAL_STOPBYTE_STRING_1    _T("1")
#define SERIAL_STOPBYTE_STRING_15     _T("1.5") 
#define SERIAL_STOPBYTE_STRING_2    _T("2")

#include "../DataMngr/DataType.h"
#include <math.h>

inline BYTE Serial_GetStopBits(float fStopBit)
{ /* 0,1,2 = 1, 1.5, 2               */
	if ( fabs(fStopBit - 1) <=0.001 )
	{
		return 0;
	}

	if ( fabs(fStopBit - 1.5) <=0.001 )
	{
		return 1;
	}

	if ( fabs(fStopBit - 2) <=0.001 )
	{
		return 2;
	}

	return 0;
}


inline float Serial_GetStopBits(BYTE nStopBit)
{ /* 0,1,2 = 1, 1.5, 2               */
	if ( nStopBit == 0 )
	{
		return 0;
	}

	if ( nStopBit == 1 )
	{
		return 1.5f;
	}

	if ( nStopBit == 2 )
	{
		return 2.0f;
	}

	return 0;
}

extern CDataType *g_pDataTypeStopByte;
extern CDataType *g_pDataTypeDataByte;
extern CDataType *g_pDataTypeCheck;
extern CDataType *g_pDataTypeBaudRate;



class CSerialXmlRWKeys : public CXmlRWKeys
{
private:
	CSerialXmlRWKeys();
	virtual ~CSerialXmlRWKeys();
	static long g_nTMRef;

public:
	static CSerialXmlRWKeys* g_pXmlKeys;
	static CSerialXmlRWKeys* Create();
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

public:
	static BSTR CQRCodeKey()  {   return g_pXmlKeys->m_strQRCodeKey;  }

};
