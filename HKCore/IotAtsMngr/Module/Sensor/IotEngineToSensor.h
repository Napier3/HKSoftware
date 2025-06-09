#pragma once

#include "../EngineServer/IotEngineToPxBase.h"

/******************************
������Э��ת��ģ�飺
m_pProtocolImpInterface��ָ��RTDeviceCtrl
m_pIotEngineProtoSvr��ָ��CIotEngineProtocolServer
******************************/

class CIotEngineToSensor:public CIotEngineToPxBase
{
public:
	CIotEngineToSensor();
	virtual ~CIotEngineToSensor();

	//m_pProtocolImpInterface:ָ��RTDeviceCtrl,����紴����ֵ������mqtt�ͻ���
	static CIotEngineToPxBase* CreateEngineToPx()
	{
		CIotEngineToPxBase* pNew =  new CIotEngineToSensor();
		pNew->m_pProtocolImpInterface = NULL;

		return pNew;
	}

public:
	//�ӿ�
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

