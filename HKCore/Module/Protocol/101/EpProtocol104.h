// EpProtocol104.h: interface for the CEpProtocol104 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOL104_H__)
#define _EPPROTOCOL104_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpProtocol101.h"
#include "Ep104Frame_Group_68.h"
#include "Ep104Frame_68_S.h"
#include "Ep104Frame_68_U.h"

class CEpProtocol104 : public CEpProtocolBase  
{
public:
	CEpProtocol104();
	virtual ~CEpProtocol104();

	static CProtocolBase* CreateProtocol()
	{
		CEpProtocol104 *pProtocol = new CEpProtocol104();
		return pProtocol;
	}

// Ù–‘
public:

public:
	virtual UINT GetClassID()	{	return EPCLASSID_PROTOCOL_101;	}

public:
	virtual void InitDeviceNodes();
};

#endif // !defined(_EPPROTOCOL101_H__)
