#pragma once

#include "../ProtocolBase/PxPkgBase.h"
#include "SensorProtocol/SttGlobalSensorDef.h"

class CXSensorPkg:public CPxPkgBase
{
public:
	CXSensorPkg();
	virtual ~CXSensorPkg();

public:
	SensorPkgInfo *m_pSensorPkgInfo;//业务报文数据结构体
};