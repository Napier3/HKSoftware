#pragma once

#include "CmmGlobalDefine.h"

class CCmmNetServer :	public CExBaseList
{
public:
	CCmmNetServer(void);
	virtual ~CCmmNetServer(void);

	CString m_strIP;
	unsigned short m_nPort;
	CString m_strMulticastIP;
	unsigned short m_nMulticastPort;

public:
	virtual UINT GetClassID(){return CMMCLASSID_NETSERVER;};

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort) = 0;
	virtual BOOL CreateServer() = 0;
	virtual BOOL CloseServer(CExBaseObject *pChannel) = 0;
	virtual BOOL IsServerClosed() = 0;

public:
	BOOL IsEqual(const CString &strIP, UINT nPort)
	{
		return ( (m_strIP == strIP) && (m_nPort == nPort) );
	}
};
