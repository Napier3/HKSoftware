#pragma once

#include "CmmChannel.h"
#include "CmmTcpClientChannel.h"
#include "CmmTcpClientChannel.h"
#include "CmmTcpServerChannel.h"
#include "CmmUdpClientChannel.h"
#include "CmmUdpServerChannel.h"
#include "CmmTcpServer.h"

#ifndef _PSX_IDE_QT_
#include "CmmUdpServer.h"
#endif


#ifndef _PSX_IDE_QT_
#include "CmmSerialChannel.h"
#endif

//设备通道对象创建管理
//目前主要实现TCP服务器端、UDP服务器端的管理
//考虑多设备同时通讯，使用相同的服务器设置（IP地址、Port）

class CCmmChannelCreateMngr :	public CExBaseList
{
private:
	CCmmChannelCreateMngr(void);
	virtual ~CCmmChannelCreateMngr(void);

	static long g_nCmmChannelCreateMngrRef;

public:
	static CCmmChannelCreateMngr *g_pCmmChannelCreateMngr;
	static CCmmChannelCreateMngr* Create();
	static void Release();

public:
    static CCmmTcpServer* RegisterTcpServer(CCmmTcpServerChannel *pTcpServerChannel);
#ifndef _PSX_IDE_QT_
    static CCmmUdpServer* RegisterUdpServer(CCmmUdpServerChannel *pUdpServerChannel);
#endif
    static void UnRegisterTcpServer(CCmmTcpServerChannel *pTcpServerChannel);
#ifndef _PSX_IDE_QT_
    static void UnRegisterUdpServer(CCmmUdpServerChannel *pUdpServerChannel);
#endif
    static void UnRegisterServer(CCmmNetServer *pServer);
	static BOOL HasAllServerExit()
	{
		return (g_pCmmChannelCreateMngr->GetCount() == 0);
	}

// 	static CCmmTcpServer* RegisterTcpServer(const CString &strIP, UINT nPort);
// 	static CCmmUdpServer* RegisterUdpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterTcpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterUdpServer(const CString &strIP, UINT nPort);
// 	static void UnRegisterTcpServer(CCmmTcpServer *pServer);
// 	static void UnRegisterUdpServer(CCmmUdpServer *pServer);

private:
    CCmmNetServer* FindNetServer(const CString &strIP, UINT nPort);
};
