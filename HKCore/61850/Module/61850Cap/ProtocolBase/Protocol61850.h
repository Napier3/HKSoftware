// Protocol61850.h: interface for the CProtocol61850 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CProtocol61850_H__)
#define _CProtocol61850_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProtocolBase.h"
#include "61850ParseFrameList.h"
#include "..\CapDevice\CapDeviceMngr.h"

#define WM_ADDCAPDEVICE  (WM_USER+1144)

class CProtocol61850 : public CProtocolBase  
{
public:
	CProtocol61850();
	virtual ~CProtocol61850();

	static CProtocolBase* CreateProtocol()
	{
		CProtocol61850 *pProtocol = new CProtocol61850();
		return pProtocol;
	}

// Ù–‘
public:
	CCapDeviceMngr *m_pCapDeviceMngr;

public:
	virtual CExBaseObject* Parse(CFrameMemBuffer *pBuffer, CFrameDetail *pDetailList, DWORD dwPara);
	virtual CExBaseObject* Parse(CFrameMemBuffer *pBuffer, DWORD dwPara);
	void SetCapDeviceMngr(CCapDeviceMngr *pDeviceMngr)	{	m_pCapDeviceMngr = pDeviceMngr;	}

	void AddCapDevice(PEPCAPBUFFERITEM pItemData, CFrameMemBuffer *pBuffer, CExBaseObject *pFrame);
};

#endif // !defined(_CProtocol61850_H__)
