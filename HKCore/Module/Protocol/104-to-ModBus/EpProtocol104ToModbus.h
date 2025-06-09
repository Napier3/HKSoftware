// EpProtocol104ToModbus.h: interface for the CEpProtocol104ToModbus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOL104TOMODBUS_H__)
#define _EPPROTOCOL104TOMODBUS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpProtocolBase.h"

//报文基类，制造、解析、匹配报文
class CEpProtocol104ToModbus : public CEpProtocolBase  
{
public:
	CEpProtocol104ToModbus();
	virtual ~CEpProtocol104ToModbus();

//属性
public:

public:
	virtual void InitDeviceNodes();
};

#endif // !defined(_EPPROTOCOL104TOMODBUS_H__)
