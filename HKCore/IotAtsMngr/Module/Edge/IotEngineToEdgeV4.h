#pragma once

#include "../EngineServer/IotEngineToPxBase.h"
#include "IotEdgeProtoServerV4.h"

class CIotEngineToEdgeV4:public CIotEngineToPxBase
{
public:
	CIotEngineToEdgeV4();
	virtual ~CIotEngineToEdgeV4();

	static CIotEngineToPxBase* CreateEngineToPx(CPxProtocolBase *pPxProtocol)
	{
		CIotEdgeProtoServerV4 *pSvr = NULL;
		
		if (pPxProtocol == NULL)
		{
			pSvr = new CIotEdgeProtoServerV4();
		}
		else
		{
			pSvr = (CIotEdgeProtoServerV4*)pPxProtocol;
		}

		CIotEngineToPxBase* pNew =  new CIotEngineToEdgeV4();
		pSvr->AttachProtoEventInterface(pNew);
		pNew->m_pProtocolImpInterface = pSvr;

		return pNew;
	}

public:
	//½Ó¿Ú
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

