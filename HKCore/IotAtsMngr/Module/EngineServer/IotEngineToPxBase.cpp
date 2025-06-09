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
析构函数中删除协议实现接口对象
特别说明:
针对传感器测试：
协议实现接口指针指向RTDeviceCtrl,协议转换模块析构时不能释放RTDeviceCtrl，
所以在具体协议转换模块【CIotEngineToSensor】的析构函数中m_pProtocolImpInterface=NULL；
针对边设备TTU测试：
协议实现接口指针指向IotEdgeProtoServerV4|5,需要释放删除
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