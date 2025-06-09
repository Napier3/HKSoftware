#pragma once

#include "../EngineServer/IotEngineToPxBase.h"

/******************************
传感器协议转换模块：
m_pProtocolImpInterface：指向RTDeviceCtrl
m_pIotEngineProtoSvr：指向CIotEngineProtocolServer
******************************/

class CIotEngineToSensor:public CIotEngineToPxBase
{
public:
	CIotEngineToSensor();
	virtual ~CIotEngineToSensor();

	//m_pProtocolImpInterface:指向RTDeviceCtrl,由外界创建后赋值，不是mqtt客户端
	static CIotEngineToPxBase* CreateEngineToPx()
	{
		CIotEngineToPxBase* pNew =  new CIotEngineToSensor();
		pNew->m_pProtocolImpInterface = NULL;

		return pNew;
	}

public:
	//接口
	virtual long RunProcedure(CSttIotCmd &oIotCmd);
	virtual long PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas);
	virtual long PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas);
	virtual long GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas);
	virtual long ConfigDevice(CSttIotCmd &oIotCmd);
	virtual long CloseDevice(CSttIotCmd &oIotCmd);

	virtual void OnPrcdrFinished(CPxPrcdrBase *pPrcdr);
	virtual void OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef);
	virtual void OnDeviceClosed(long nDeviceIndex);
	virtual void OnPkgReceive(CPxPkgBase *pPkg);
	virtual void OnPkgSend(CPxPkgBase *pPkg);
	virtual void OnException(unsigned long nErrNo);
	virtual void OnClose(char *pszErr);
};

