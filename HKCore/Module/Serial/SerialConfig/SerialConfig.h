#pragma once

/**************************************
CSttMqttClientEngineConfig:
**************************************/

#include "../../DataMngr/DataGroup.h"

#define SERIAL_CONFIG_ID_Comm			_T("Comm")
#define SERIAL_CONFIG_ID_BaudRate		_T("BaudRate")
#define SERIAL_CONFIG_ID_DataBit		_T("DataBit")
#define SERIAL_CONFIG_ID_StopBit		_T("StopBit")
#define SERIAL_CONFIG_ID_Parity			_T("Parity")


class CSerialConfig : public CDataGroup
{
public:
	CSerialConfig();
	virtual ~CSerialConfig();

public:
	BOOL Create(const CString &strFile=_T(""));

	BOOL GetSerialComm(long &nComm);
	BOOL GetSerialBaudRate(long &nBaudRate);
	BOOL GetSerialDataBit(long &nDataBit);
	BOOL GetSerialStopBit(long &nStopBit);
	BOOL GetSerialParity(long &nParity);

protected:
	BOOL OpenSerialConfig(const CString &strFile);
	void GetDefaultConfigFile(CString &strFile);

};