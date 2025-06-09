#pragma once

#include "PxPrcdrBase.h"

//协议事件返回
class CPxProtoEventInterface
{
public:
	CPxProtoEventInterface(){}
	virtual ~CPxProtoEventInterface(){}
public:
	virtual void OnPrcdrFinished(CPxPrcdrBase *pPrcdr) = 0;
	virtual void OnPrcdrFinishedEx(char *pszEventID,CDvmDataset *pDatasetRef){};
	virtual void OnDeviceClosed(long nDeviceIndex) = 0;
	virtual void OnPkgReceive(CPxPkgBase *pPkg) = 0;
	virtual void OnPkgSend(CPxPkgBase *pPkg) = 0;
	virtual void OnException(unsigned long nErrNo) = 0;
	virtual void OnClose(char *pszErr) = 0;
};