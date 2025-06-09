#pragma once

#include "61850Cap/EthernetCapThread.h"
#include "61850Cap/CapSmDbFile/CapFrameDbFile.h"
#include "61850Cap/ProtocolBase/Protocol61850.h"
#include "61850Cap/Record/CapDeviceChRecordMngr.h"

#include "../Smdb/SmDbWriteThread.h"
#include "X61850CapBase.h"

class CXEthernetCap_61850 : public CX61850CapBase
{
public:
	CXEthernetCap_61850(void);
	virtual ~CXEthernetCap_61850(void);

	virtual void ExitInstance();
	virtual void CreateCapTrhead();
	virtual BOOL BeginCap(CIecCfgDatasMngr *pIecfgDataMngr,BOOL bClearDevices=TRUE);
	virtual BOOL StopCap();

	virtual BOOL IsCapExit();
	virtual BOOL CanClose();
	virtual BOOL IsInCapture();

	virtual void FreeCapture();
	void SetNetCardIndex(long nIndex);

	CXSmMemBufferMngr* GetCapMemBufferMngr()	{	return m_pEthernetCapThread->GetCapMemBufferMngr();	}

protected:
	ETHER_CAP_CONFIG m_oCapConfig;
	CEthernetCapThread *m_pEthernetCapThread;

public:
	PETHER_CAP_CONFIG GetCapConfig();
	void SetCapConfig(PETHER_CAP_CONFIG pCapConfig);

};
