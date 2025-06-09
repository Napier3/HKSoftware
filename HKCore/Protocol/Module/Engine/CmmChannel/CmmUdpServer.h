#pragma once

#include "CmmNetServer.h"
#include "CmmUdpServerChannel.h"

/*
UDP服务器端口
子对象为与Server连接的CmmUdpServer通道
*/

class CCmmUdpServer : public CCmmNetServer
{
public:
	CCmmUdpServer(void);
	virtual ~CCmmUdpServer(void);
	char m_pszPpLogProtocol[10240]; 

public:
	virtual UINT GetClassID(){return CMMCLASSID_UDPSERVER;};

public:
	CWinThread *m_pThread;
	CCycleMemBuffer m_oReceiveByffer;
	long m_nReceiveLen;
	BOOL m_bNeedSend;
	BOOL m_bExitThread;
	CExBaseList m_listPkgSend;

public:
	virtual BOOL CreateServer(const CString &strIP, UINT nPort, const CString &strBoardcastIP, long nMulticastPort);
	virtual BOOL CreateServer();
	virtual BOOL CloseServer(CExBaseObject *pChannel);
	virtual BOOL IsServerClosed();

	BOOL CloseUdpClient(const CString &strIP);

public:
	//UDP服务器端接受函数
	static UINT UdpServerThread(LPVOID pParam);

	void OnReceive(CCmmRcvSndTime *pCmmTime, struct sockaddr_in *pSckAddr, long nPos1Begin =0, long nPos1End =0, long nPos2Begin =0, long nPos2End =0);

	void Send(CExBaseObject *pPkgSend);
	CExBaseObject* GetPackageSend();
	void RemoveHead();

private:
	CAutoCriticSection m_oSendListCriticSection;   //发送链表互斥对象
	CCmmUdpServerChannel* Find(struct sockaddr_in *pSckAddr);
	CCmmUdpServerChannel* FindFirstUnConnected();
};
