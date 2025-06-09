#pragma once

#include "EpCmmChannel.h"
#include "EpCmmSerialChannel.h"
#include "EpCmmTcpClientChannel.h"
#include "EpCmmTcpServerChannel.h"
#include "EpCmmUdpServerChannel.h"
#include "EpCmmUdpClientChannel.h"
#include "EpCmmTcpServer.h"
#include "EpCmmUdpServer.h"

//设备通道对象创建管理
//目前主要实现TCP服务器端、UDP服务器端的管理
//考虑多设备同时通讯，使用相同的服务器设置（IP地址、Port）

class CEpCmmChannelCreateMngr :	public CExBaseList
{
private:
	CEpCmmChannelCreateMngr(void);
	~CEpCmmChannelCreateMngr(void);

	static long g_nEpCmmChannelCreateMngrRef;

public:
	static CEpCmmChannelCreateMngr *g_pEpCmmChannelCreateMngr;
	static CEpCmmChannelCreateMngr* Create();
	static void Release();

public:
	static CEpCmmTcpServer* RegisterTcpServer(CEpCmmTcpServerChannel *pTcpServerChannel);
	static CEpCmmUdpServer* RegisterUdpServer(CEpCmmUdpServerChannel *pUdpServerChannel);
	static void UnRegisterTcpServer(CEpCmmTcpServerChannel *pTcpServerChannel);
	static void UnRegisterUdpServer(CEpCmmUdpServerChannel *pUdpServerChannel);
	static void UnRegisterServer(CEpCmmNetServer *pServer);

	static BOOL HasAllServerExit()
	{
		return (g_pEpCmmChannelCreateMngr->GetCount() == 0);
	}

// 	static CEpCmmTcpServer* RegisterTcpServer(const CString &strIP, UINT nPort);
// 	static CEpCmmUdpServer* RegisterUdpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterTcpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterUdpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterTcpServer(CEpCmmTcpServer *pServer);
// 	static void UnRegisterUdpServer(CEpCmmUdpServer *pServer);

private:
	CEpCmmNetServer* FindNetServer(const CString &strIP, UINT nPort);
};
