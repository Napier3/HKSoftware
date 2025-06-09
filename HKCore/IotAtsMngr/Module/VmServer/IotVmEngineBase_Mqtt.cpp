#include "stdafx.h"
#include "IotVmEngineBase_Mqtt.h"

CIotVmEngineBase_Mqtt::CIotVmEngineBase_Mqtt()
:CSttMqttEngineBase()
{

}

CIotVmEngineBase_Mqtt::~CIotVmEngineBase_Mqtt()
{

}

void CIotVmEngineBase_Mqtt::BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	CSttTestCmd *pVmCmd = (CSttTestCmd *)pCmdBase;

	SetXmlBufferLen(nLen * 2);
	pVmCmd->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,_PUGI_XML_TYPE_);
}

