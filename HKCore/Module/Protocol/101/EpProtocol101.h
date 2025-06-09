// EpProtocol101.h: interface for the CEpProtocol101 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOL101_H__)
#define _EPPROTOCOL101_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ProtocolBase\EpProtocolBase.h"
#include "Ep101Frame_E5.h"
#include "Ep101Frame_10.h"
#include "Ep101Frame_68.h"
#include "Ep101Frame_Group_68.h"

#include "Ep101Frame_68_Asdu01.h"
#include "Device\EpDevice101.h"

class CEpProtocol101 : public CEpProtocolBase  
{
public:
	CEpProtocol101();
	virtual ~CEpProtocol101();

	static CProtocolBase* CreateProtocol()
	{
		CEpProtocol101 *pProtocol = new CEpProtocol101();
		return pProtocol;
	}

//ÊôÐÔ
public:

public:
	virtual UINT GetClassID()	{	return EPCLASSID_PROTOCOL_101;	}

public:
	virtual void InitDeviceNodes();
// 	long GetYcCount()
// 	{
// 		return (m_pYcDataNode == NULL) ? 0 : m_pYcDataNode->GetArrDatas();
// 	}
// 
// 	long GetYxCount()
// 	{
// 		return (m_pYxDataNode == NULL) ? 0 : m_pYxDataNode->GetArrDatas();
// 	}
// 
// 	long GetYkCount()
// 	{
// 		return (m_pYkDataNode == NULL) ? 0 : m_pYkDataNode->GetArrDatas();
// 	}
// 
// 	long GetYtCount()
// 	{
// 		return (m_pYtDataNode == NULL) ? 0 : m_pYtDataNode->GetArrDatas();
// 	}
};

#endif // !defined(_EPPROTOCOL101_H__)
