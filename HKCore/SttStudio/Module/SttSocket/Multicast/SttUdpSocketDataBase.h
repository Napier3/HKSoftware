#pragma once
#ifdef _PSX_QT_LINUX_
#include "netinet/in.h"
#else
#include "ws2def.h"
#endif

#include "../../../../Module/MemBuffer/ExpandMemBuf.h"

class CSttUdpSocketDataBase
{
public:
	CSttUdpSocketDataBase();
	virtual ~CSttUdpSocketDataBase();

public:
	//Ω” ’ª∫¥Ê
	CExpandMemBuf m_oExpandRecvBuf;
	sockaddr_in* m_pCurSockaddr;

	virtual void OnReceiveBuffer(BYTE *pBuf, long nLen,sockaddr_in* fsockaddr);
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen,sockaddr_in* fsockaddr);

	BOOL AnalysisRecvBuf(sockaddr_in* fsockaddr);

public:
	long m_nHeadLen;
	virtual BOOL is_pkg_match_head(BYTE *pBuf){return TRUE;}
	virtual long get_pkg_data_len(BYTE *pBuf){return 0;}	
};
