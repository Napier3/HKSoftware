#pragma once


class CXUserTcpBase
{
public:
	CXUserTcpBase(void);
	virtual ~CXUserTcpBase(void);

	CString m_strServerIP;
	CString m_nServerPort;

	unsigned long destAddr;
	SOCKADDR_IN destSockAddr;
	SOCKET destSocket;


	CString GetError(DWORD error);

};
