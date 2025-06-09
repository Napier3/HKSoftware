// EpDevice101.h: interface for the CEpDevice101 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPDEVICE101_H__)
#define _EPDEVICE101_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\EpDevice.h"

class CEpDevice101 : public CEpDevice
{
public:
	CEpDevice101();
	virtual ~CEpDevice101();

// Ù–‘
public:
	

public:
	virtual UINT GetClassID()	{	return EPCLASSID_DEVICE;	}

};

#endif // !defined(_EPDEVICE101_H__)
