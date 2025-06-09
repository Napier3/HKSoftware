#pragma once

#include "../ProtocolBase/PxPkgBase.h"
#include "../ProtocolBase/XMqttTitleData.h"

//mqtt 报文对象基类
class CMqttEdgePkgBase:public CPxPkgBase
{
public:
	CMqttEdgePkgBase();
	virtual ~CMqttEdgePkgBase();

	CXMqttTitleData m_oMqttData;

};