#pragma once

#include "PxProtocolBase.h"
#include "../EdgeMqttEngineBase.h"

class CMqttEdgeProtocol:public CPxProtocolBase,public CEdgeMqttEngineBase
{
public:
	CMqttEdgeProtocol();
	virtual ~CMqttEdgeProtocol();

public:
	//协议被调用执行接口
	virtual long RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
		,CDvmDataset *pDataset,const CString &strRecordMode);
	virtual long PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset);
	virtual long PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen);
	virtual long GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset);
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();
};