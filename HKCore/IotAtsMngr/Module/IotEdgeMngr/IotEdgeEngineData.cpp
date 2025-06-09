#include "stdafx.h"
#include "IotEdgeEngineData.h"

CIotEdgeEngineData::CIotEdgeEngineData(const CString &strPpTemplateFile, const CString &strDeviceFile, const CString &strDeviceID)
{
	m_pEngineThread = NULL;

	m_strID = strDeviceID;
	m_oDvmDevice.OpenXmlFile(strDeviceFile,CDataMngrXmlRWKeys::g_pXmlKeys);
}

CIotEdgeEngineData::~CIotEdgeEngineData()
{

}

void CIotEdgeEngineData::OnMqttMsgRecieve(const CString &strTopic,char *pBuf,long nLen)
{

}

void CIotEdgeEngineData::OnMqttDisconnected(char *pszErr)
{

}