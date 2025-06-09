#pragma once

// #include "BlueTooth.h"
// CBlueToothBase 命令目标

#include <initguid.h>
#include <winsock2.h>
#include <ws2bth.h>
#include <strsafe.h>
#include <vector>
#include <BluetoothAPIs.h>
#include "BTProtocol_OperInterface.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment ( lib, "Irprops.lib")

// {00001101-0000-1000-8000-00805F9B34FB}
DEFINE_GUID(g_guidServiceClass, 0x00001101, 0x0000, 0x1000, 0x80, 0x00, 0x00, 0x80, 0x5f, 0x9b, 0x34, 0xfb);

#define CXN_TEST_DATA_STRING              (L"~!@#$%^&*()-_=+?<>1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
#define CXN_TRANSFER_DATA_LENGTH          (sizeof(CXN_TEST_DATA_STRING))

#define BT_STATE_IDLE	0		//空闲
#define BT_STATE_ACCEPTING	1	//服务器端等待连接
#define BT_STATE_CONNECTING	2	//客户端正在连接
#define BT_STATE_CONNECTED	3	//已连接
#define BT_STATE_CLOSE      4   //已关闭

#define CXN_BDADDR_STR_LEN                17   // 6 two-digit hex values plus 5 colons
#define CXN_MAX_INQUIRY_RETRY             3
#define CXN_DELAY_NEXT_INQUIRY            15
#define CXN_SUCCESS                       0
#define CXN_ERROR                         1
#define CXN_DEFAULT_LISTEN_BACKLOG        4

typedef struct _RemoteBthInfo
{
	_RemoteBthInfo()
	{
		memset ( szName, 0, sizeof(szName) );
		memset ( &Address, 0, sizeof(BTH_ADDR) );
	}
	TCHAR szName[64];
	BTH_ADDR Address;
}t_RemoteBthInfo;

class CBlueToothBase : public CObject , public CBTProtocol_OperInterface 
{
public:
	CBlueToothBase();
	virtual ~CBlueToothBase();

	SOCKET m_hSocketClient;
	SOCKET m_hSocketServer;
	int		m_nBTState;
	
	std::vector<BLUETOOTH_RADIO_INFO> m_LocalBthInfoList;
	std::vector<t_RemoteBthInfo> m_RemoteBthAddress;
	BTH_ADDR m_CurrAddress;

public:

	int EnumerateLocalRadios();
	
	int	WSAScanNearbyBth();
	
	ULONG	SendMsg(char *pchMsg,BYTE bCmmd, int nLen);
	ULONG	SendMsg(CString strMsg,BYTE bCmmd, int nLen);
	virtual ULONG	CloseSocket(int nBTState);
	
	void AcceptAndReviceData();

	virtual void DealDataBeforeSend(){	}
	virtual void HandleClientCommand(BYTE *strCmmd) = 0;

	CString FormatBthAddress(BYTE *BthAddress);
	CString FormatBthAddress(BTH_ADDR BthAddress);
};


