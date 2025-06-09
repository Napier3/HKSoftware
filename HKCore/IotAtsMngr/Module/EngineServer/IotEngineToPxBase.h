#pragma once

#include "IotEngineProtoSvrImpInterface.h"
#include "../ProtocolBase/PxProtoEventInterface.h"
#include "IotEngineProtocolServer.h"
#include "../ProtocolBase/PxProtocolImpInterface.h"

/*************************************
Э��ת��ģ����ࣺ
m_pProtocolImpInterface;//ָ��RTDeviceCtrl ���� IotEdgeProtoServerV4|5
m_pIotEngineProtoSvr;//ָ��CIotEngineProtocolServer

��Ҫͨ��������ָ��ʵ����CIotEngineProtocolServer��
����Ǵ��������ԣ�
RTDeviceCtrlģ��ӿں��¼�������
����Ǳ��豸TTU���ԣ�
IotEdgeProtoServerV4|5ģ��ӿں��¼�������
*************************************/

class CIotEngineToPxBase:public CIotEngineProtoSvrImpInterface,public CPxProtoEventInterface
{
public:
	CIotEngineToPxBase();
	virtual ~CIotEngineToPxBase();

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

public:
	void SetPxProtoImpInterface(CPxProtocolImpInterface *pMqttProtocol);
	void SetIotEngineProtocolServer(CIotEngineProtocolServer *pIotEngineProtoSvr);
	void ConfigMqttProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);
	BOOL InitMqttProtocol(const CString &strIP,long nPort);

	//2021-8-19  lijunqing  ����豸�����ڣ��ڴ����κ������ʱ�򣬶�����ʧ����Ϣ
	CPxProtocolImpInterface *m_pProtocolImpInterface;//ָ��RTDeviceCtrl ���� IotEdgeProtoServerV4|5
	CIotEngineProtocolServer *m_pIotEngineProtoSvr;//ָ��CIotEngineProtocolServer
};

