#pragma once

#include "../ProtocolBase/PxProtoDeviceBase.h"

class CIotVmDevice: public CPxProtoDeviceBase
{//m_strID:DeviceID
public:
	CIotVmDevice();
	virtual ~CIotVmDevice();

public:
	virtual long ConfigDevice(const CString &strConfig);
	virtual long CloseDevice();

	//初始化协议服务模块
	virtual void InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		,const CString &strCmmCfgFile,CDataGroup *pCfgGroup);
	
};
