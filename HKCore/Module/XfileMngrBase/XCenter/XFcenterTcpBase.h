#pragma once


class CXFcenterTcpBase
{
public:
	CXFcenterTcpBase(void);
	virtual ~CXFcenterTcpBase(void);

	CString m_strServerIP;
	CString m_nServerPort;

	unsigned long destAddr;
	SOCKADDR_IN destSockAddr;
	SOCKET destSocket;


	CString GetError(DWORD error);

};
