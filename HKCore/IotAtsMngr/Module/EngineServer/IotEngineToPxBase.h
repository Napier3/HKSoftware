#pragma once

#include "IotEngineProtoSvrImpInterface.h"
#include "../ProtocolBase/PxProtoEventInterface.h"
#include "IotEngineProtocolServer.h"
#include "../ProtocolBase/PxProtocolImpInterface.h"

/*************************************
协议转换模块基类：
m_pProtocolImpInterface;//指向RTDeviceCtrl 或者 IotEdgeProtoServerV4|5
m_pIotEngineProtoSvr;//指向CIotEngineProtocolServer

主要通过这两个指针实现与CIotEngineProtocolServer和
如果是传感器测试：
RTDeviceCtrl模块接口和事件互调；
如果是边设备TTU测试：
IotEdgeProtoServerV4|5模块接口和事件互调；
*************************************/

class CIotEngineToPxBase:public CIotEngineProtoSvrImpInterface,public CPxProtoEventInterface
{
public:
	CIotEngineToPxBase();
	virtual ~CIotEngineToPxBase();

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

public:
	void SetPxProtoImpInterface(CPxProtocolImpInterface *pMqttProtocol);
	void SetIotEngineProtocolServer(CIotEngineProtocolServer *pIotEngineProtoSvr);
	void ConfigMqttProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);
	BOOL InitMqttProtocol(const CString &strIP,long nPort);

	//2021-8-19  lijunqing  如果设备不存在，在处理任何命令的时候，都返回失败信息
	CPxProtocolImpInterface *m_pProtocolImpInterface;//指向RTDeviceCtrl 或者 IotEdgeProtoServerV4|5
	CIotEngineProtocolServer *m_pIotEngineProtoSvr;//指向CIotEngineProtocolServer
};

