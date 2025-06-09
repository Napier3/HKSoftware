// EpDeviceModBus.h: interface for the CEpDeviceModBus class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPDEVICEModBus_H__)
#define _EPDEVICEModBus_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\Device\EpDevice.h"
#include "EpGlobalDefine_ModBus.h"

class CEpDeviceModBus : public CEpDevice
{
public:
	CEpDeviceModBus();
	virtual ~CEpDeviceModBus();

// Ù–‘
public:


public:
	virtual UINT GetClassID()	{	return EPDCLASSID_CEPDEVICE;	}

};

#endif // !defined(_EPDEVICEModBus_H__)
