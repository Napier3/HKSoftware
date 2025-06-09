// EpProtocolModBus.h: interface for the CEpProtocolModBus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOLModBus_H__)
#define _EPPROTOCOLModBus_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ProtocolBase\EpProtocolBase.h"
#include "EpDeviceModBus.h"

class CEpProtocolModBus : public CEpProtocolBase  
{
public:
	CEpProtocolModBus();
	virtual ~CEpProtocolModBus();

// Ù–‘
public:

public:
	virtual UINT GetClassID()	{	return EPCLASSID_PROTOCOL;	}

public:
	virtual void InitDeviceNodes();
	
};

#endif // !defined(_EPPROTOCOLModBus_H__)
