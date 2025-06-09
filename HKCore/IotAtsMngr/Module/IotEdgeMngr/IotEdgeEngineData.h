#pragma once

#include "../SttMqttClientTool.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "IotEdgeEngineThread.h"

class CIotEdgeEngineData: public CExBaseList, public CSttMqttMsgInterface
{
public:
	CIotEdgeEngineData(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);
	virtual ~CIotEdgeEngineData();

	CDvmDevice m_oDvmDevice;
	CIotEdgeEngineThread *m_pEngineThread;

	//mqtt½Ó¿Ú
public:
	virtual void OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen);
	virtual void OnMqttDisconnected(char *pszErr);


};