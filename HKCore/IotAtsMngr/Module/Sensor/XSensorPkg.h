#pragma once

#include "../ProtocolBase/PxPkgBase.h"
#include "SensorProtocol/SttGlobalSensorDef.h"

class CXSensorPkg:public CPxPkgBase
{
public:
	CXSensorPkg();
	virtual ~CXSensorPkg();

public:
	SensorPkgInfo *m_pSensorPkgInfo;//ҵ�������ݽṹ��
};