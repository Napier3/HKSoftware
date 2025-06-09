#pragma once
#include "../../../module/baseclass/exbaseobject.h"
#include "../../../Module/MemBuffer/CycleMemBuffer.h"

#include "PpPackageDetail.h"
#include "CmmChannel/CmmChannel.h"
/*
发送报文对象
*/

class CPpPackageSend :	public CExBaseObject
{
public:
	CPpPackageSend(CExBaseObject *pPpProcedureRun, CCmmChannel *pChannel, long nBufferLen);
	virtual ~CPpPackageSend(void);

public:
	CCmmChannel *m_pChannel;
	CPpPackageDetail *m_pPackageDetail;
	CExBaseObject *m_pPpProcedureRun;
	CCycleMemBuffer m_oBuffer;
	CWinThread *m_pEngineThread;
	BOOL m_bHasSended;
	BOOL m_bIsLocked;    //是否被锁定，不能删除
	CString m_strChCmmMode;
	long m_nSendtimes;

public:
	void GetPackageBufferPos(PACKAGEBUFFERPOS &oPkgBufPos);
	void Send();
	
	//监视报文
	void LogAndRecordProtocol();
	CPpPackageDetail* DettachPpPackage();

	void SetSendState(BOOL bSend=TRUE);
	BOOL HasSended()	{		return m_bHasSended;	}
	BOOL IsTimeout()	{	return m_pPackageDetail->IsTimeout();	}

	void Lock(BOOL bLock=TRUE)	{		m_bIsLocked = bLock;	}
	BOOL IsLock()	{		return m_bIsLocked;	}

	BOOL IsChCmmModeBroadCast();
	BOOL IsChCmmModeMultiCast();
	BOOL IsChCmmModeToPoint();
};
