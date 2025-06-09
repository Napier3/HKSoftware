#include "stdafx.h"
#include "SerialConfig.h"
#include "../../API/FileApi.h"
#include "../../API/GlobalConfigApi.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CSerialConfig::CSerialConfig()
{
}

CSerialConfig::~CSerialConfig()
{

}

BOOL CSerialConfig::Create(const CString &strFile)
{
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL nRes = OpenSerialConfig(strFile);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	return nRes;
}

BOOL CSerialConfig::GetSerialComm(long &nComm)
{
	nComm = 0;
	return GetDataValue(SERIAL_CONFIG_ID_Comm,nComm);
}

BOOL CSerialConfig::GetSerialBaudRate(long &nBaudRate)
{
	nBaudRate = 9600;
	return GetDataValue(SERIAL_CONFIG_ID_BaudRate,nBaudRate);
}

BOOL CSerialConfig::GetSerialDataBit(long &nDataBit)
{
	nDataBit = 8;
	return GetDataValue(SERIAL_CONFIG_ID_DataBit,nDataBit);
}

BOOL CSerialConfig::GetSerialStopBit(long &nStopBit)
{
	nStopBit = 1;
	return GetDataValue(SERIAL_CONFIG_ID_StopBit,nStopBit);
}

BOOL CSerialConfig::GetSerialParity(long &nParity)
{
	nParity = 0;
	return GetDataValue(SERIAL_CONFIG_ID_Parity,nParity);
}

BOOL CSerialConfig::OpenSerialConfig(const CString &strFile)
{
	CString strPath = strFile;
	
	if (strPath.GetLength() <= 5)
	{
		GetDefaultConfigFile(strPath);
	}
	else
	{
		if (!IsFileExist(strPath))
		{
			GetDefaultConfigFile(strPath);
		}
	}
	
	return OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void CSerialConfig::GetDefaultConfigFile(CString &strFile)
{
	strFile = _P_GetConfigPath();
	strFile += _T("SerialConfig.xml");
}
