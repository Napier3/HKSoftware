#pragma once

#include "../ProtocolBase/PxPkgBase.h"
#include "../ProtocolBase/XMqttTitleData.h"

//mqtt ���Ķ������
class CMqttEdgePkgBase:public CPxPkgBase
{
public:
	CMqttEdgePkgBase();
	virtual ~CMqttEdgePkgBase();

	CXMqttTitleData m_oMqttData;

};