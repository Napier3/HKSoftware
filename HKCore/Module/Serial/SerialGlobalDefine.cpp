// SerialStopByteComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialGlobalDefine.h"
#include "..\..\Module\API\MathApi.h"
#include <math.h>

CDataType *g_pDataTypeStopByte = NULL;
CDataType *g_pDataTypeDataByte = NULL;
CDataType *g_pDataTypeCheck = NULL;
CDataType *g_pDataTypeBaudRate = NULL;

// CSerialDataTypes
class CSerialDataTypesCreator
{
public:
	CSerialDataTypesCreator()
	{
		g_pDataTypeStopByte = &m_oDataTypeStopByte;
		g_pDataTypeDataByte = &m_oDataTypeDataByte;
		g_pDataTypeCheck = &m_oDataTypeCheck;
		g_pDataTypeBaudRate = &m_oDataTypeBaudRate;

	}
	
	virtual ~CSerialDataTypesCreator()
	{
		
	}

protected:
	CDataType m_oDataTypeStopByte;
	CDataType m_oDataTypeDataByte;
	CDataType m_oDataTypeCheck;
	CDataType m_oDataTypeBaudRate;
	
	void InitStopByteByteString()
	{
		m_oDataTypeStopByte.AddNewValue(SERIAL_STOPBYTE_STRING_1, SERIAL_STOPBYTE_STRING_1, _T("0"));
		m_oDataTypeStopByte.AddNewValue(SERIAL_STOPBYTE_STRING_1, SERIAL_STOPBYTE_STRING_1, _T("1"));
		m_oDataTypeStopByte.AddNewValue(SERIAL_STOPBYTE_STRING_1, SERIAL_STOPBYTE_STRING_1, _T("2"));
	}


	void InitDataByteByteString()
	{
		m_oDataTypeDataByte.AddNewValue(_T("5"), _T("5"), _T("0"));
		m_oDataTypeDataByte.AddNewValue(_T("6"), _T("6"), _T("1"));
		m_oDataTypeDataByte.AddNewValue(_T("7"), _T("7"), _T("2"));
	}


	void InitCheckByteString()
	{
		m_oDataTypeDataByte.AddNewValue(_T("无校验"), SERIAL_CHECKBYTE_STRING_NONE, _T("0"));
		m_oDataTypeDataByte.AddNewValue(_T("奇校验"), SERIAL_CHECKBYTE_STRING_ODD, _T("1"));
		m_oDataTypeDataByte.AddNewValue(_T("偶校验"), SERIAL_CHECKBYTE_STRING_EVEN, _T("2"));
	}


	void InitBaudRateString()
	{
		m_oDataTypeBaudRate.AddNewValue(_T("1200"), _T("1200"), _T("0"));
		m_oDataTypeBaudRate.AddNewValue(_T("2400"), _T("2400"), _T("1"));
		m_oDataTypeBaudRate.AddNewValue(_T("4800"), _T("4800"), _T("2"));
		m_oDataTypeBaudRate.AddNewValue(_T("5600"), _T("5600"), _T("3"));
		m_oDataTypeBaudRate.AddNewValue(_T("9600"), _T("9600"), _T("4"));
		m_oDataTypeBaudRate.AddNewValue(_T("14400"), _T("14400"), _T("5"));
		m_oDataTypeBaudRate.AddNewValue(_T("19200"), _T("19200"), _T("6"));
		m_oDataTypeBaudRate.AddNewValue(_T("38400"), _T("38400"), _T("7"));
		m_oDataTypeBaudRate.AddNewValue(_T("115200"), _T("115200"), _T("8"));
		m_oDataTypeBaudRate.AddNewValue(_T("128000"), _T("128000"), _T("9"));
		m_oDataTypeBaudRate.AddNewValue(_T("256000"), _T("256000"), _T("10"));
	}
};


//////////////////////////////////////////////////////////////////////////

CSerialXmlRWKeys* CSerialXmlRWKeys::g_pXmlKeys = NULL;
long CSerialXmlRWKeys::g_nTMRef = 0;


CSerialXmlRWKeys::CSerialXmlRWKeys()
{
	m_strSerialKey = L"ClockError";
	m_strValueKey = L"value";

	m_strPortNumberKey = L"port-number"; //port_number
	m_strBaudRateKey = L"baud-rate"; //baud-rate
	m_strParityKey = L"parity"; //parity
	m_strByteSizeKey = L"byte-size"; //byte-size
	m_strStopsbitKey = L"stop-bit"; //stop-bit

	m_strWriteLogKey = L"write_log";//WriteLog
	m_strEncodeTypeKey = L"encode_type";//EncodeType
	m_strSeparateCharKey = L"separate_char";//EncodeType
	m_strSeparateEndCharKey = L"separate_end_char";//EncodeType

	m_strQRCodeKey = L"qrcode-config";
}

CSerialXmlRWKeys::~CSerialXmlRWKeys()
{
}

CSerialXmlRWKeys* CSerialXmlRWKeys::Create()
{
	g_nTMRef++;

	if (g_nTMRef == 1)
	{
		g_pXmlKeys = new CSerialXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSerialXmlRWKeys::Release()
{
	g_nTMRef--;

	if (g_nTMRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}
