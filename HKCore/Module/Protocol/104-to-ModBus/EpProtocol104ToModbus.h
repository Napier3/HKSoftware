// EpProtocol104ToModbus.h: interface for the CEpProtocol104ToModbus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOL104TOMODBUS_H__)
#define _EPPROTOCOL104TOMODBUS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpProtocolBase.h"

//���Ļ��࣬���졢������ƥ�䱨��
class CEpProtocol104ToModbus : public CEpProtocolBase  
{
public:
	CEpProtocol104ToModbus();
	virtual ~CEpProtocol104ToModbus();

//����
public:

public:
	virtual void InitDeviceNodes();
};

#endif // !defined(_EPPROTOCOL104TOMODBUS_H__)
