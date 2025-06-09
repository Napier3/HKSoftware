#include "stdafx.h"
#include "IotEngineToPxBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEngineToPxBase::CIotEngineToPxBase()
{
	m_pProtocolImpInterface = NULL;
	m_pIotEngineProtoSvr = NULL;
}

/*************************************
����������ɾ��Э��ʵ�ֽӿڶ���
�ر�˵��:
��Դ��������ԣ�
Э��ʵ�ֽӿ�ָ��ָ��RTDeviceCtrl,Э��ת��ģ������ʱ�����ͷ�RTDeviceCtrl��
�����ھ���Э��ת��ģ�顾CIotEngineToSensor��������������m_pProtocolImpInterface=NULL��
��Ա��豸TTU���ԣ�
Э��ʵ�ֽӿ�ָ��ָ��IotEdgeProtoServerV4|5,��Ҫ�ͷ�ɾ��
*************************************/
CIotEngineToPxBase::~CIotEngineToPxBase()
{
	if (m_pProtocolImpInterface != NULL)
	{
		delete m_pProtocolImpInterface;
		m_pProtocolImpInterface = NULL;
	}
}

long CIotEngineToPxBase::RunProcedure(CSttIotCmd &oIotCmd)
{
	return 0;
}

long CIotEngineToPxBase::PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	return 0;
}

long CIotEngineToPxBase::PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	return 0;
}

long CIotEngineToPxBase::GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas)
{
	return 0;
}

long CIotEngineToPxBase::ConfigDevice(CSttIotCmd &oIotCmd)
{
	return 0;
}

long CIotEngineToPxBase::CloseDevice(CSttIotCmd &oIotCmd)
{
	return 0;
}


void CIotEngineToPxBase::OnPrcdrFinished(CPxPrcdrBase *pPrcdr)
{

}

void CIotEngineToPxBase::OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef)
{

}

void CIotEngineToPxBase::OnDeviceClosed(long nDeviceIndex)
{

}

void CIotEngineToPxBase::OnPkgReceive(CPxPkgBase *pPkg)
{

}

void CIotEngineToPxBase::OnPkgSend(CPxPkgBase *pPkg)
{

}

void CIotEngineToPxBase::OnException(unsigned long nErrNo)
{

}

void CIotEngineToPxBase::OnClose(char *pszErr)
{

}

void CIotEngineToPxBase::SetPxProtoImpInterface(CPxProtocolImpInterface *pMqttProtocol)
{
	m_pProtocolImpInterface = pMqttProtocol;
}

void CIotEngineToPxBase::SetIotEngineProtocolServer(CIotEngineProtocolServer *pIotEngineProtoSvr)
{
	m_pIotEngineProtoSvr = pIotEngineProtoSvr;
}

void CIotEngineToPxBase::ConfigMqttProtocol(const CString &strDeviceID,const CString &strDvmFile
					,const CString &strPpxmlFile,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	m_pProtocolImpInterface->InitProtocol(strDeviceID,strDvmFile,strPpxmlFile,strCmmCfgFile,pCfgGroup);
}

BOOL CIotEngineToPxBase::InitMqttProtocol(const CString &strIP,long nPort)
{
	if (m_pProtocolImpInterface == NULL || m_pIotEngineProtoSvr == NULL)
	{
		return FALSE;
	}

	return m_pProtocolImpInterface->Init(strIP,nPort);
}