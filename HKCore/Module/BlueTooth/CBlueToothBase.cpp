// BlueToothCmm.cpp : 实现文件
//

#include "stdafx.h"
#include "CBlueToothBase.h"
#include <fstream> 

int  g_ulMaxCxnCycles = 1;

// CBlueToothBase

CBlueToothBase::CBlueToothBase()
{
	m_hSocketClient = INVALID_SOCKET;
	m_hSocketServer = INVALID_SOCKET;
	m_nBTState = BT_STATE_IDLE;
}

CBlueToothBase::~CBlueToothBase()
{
}

int CBlueToothBase::WSAScanNearbyBth()
{
	m_RemoteBthAddress.clear();

// 	pWSAQuerySet = (PWSAQUERYSET) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ulPQSSize);
// 
// 	if ( NULL == pWSAQuerySet ) 
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_ERROR,L"!ERROR! | Unable to allocate memory for WSAQUERYSET\n");
// 		return -1;
// 	}

	WSAQUERYSET wsaq;
	HANDLE hLookup;
	union
	{
		CHAR buf[5000];
		double __unused; // ensure proper alignment
	};

	LPWSAQUERYSET pwsaResults = (LPWSAQUERYSET) buf;
	DWORD dwSize = sizeof(buf);
	BOOL bHaveName;
	ZeroMemory(&wsaq, sizeof(wsaq));
	wsaq.dwSize = sizeof(wsaq);
	wsaq.dwNameSpace = NS_BTH;
	wsaq.lpcsaBuffer = NULL;
	if (ERROR_SUCCESS != WSALookupServiceBegin (&wsaq, LUP_CONTAINERS/* | LUP_FLUSHCACHE */, &hLookup))
	{
		TRACE ( _T("WSALookupServiceBegin failed\n") );
		return -1;
	}

	ZeroMemory(pwsaResults, sizeof(WSAQUERYSET));
	pwsaResults->dwSize = sizeof(WSAQUERYSET);
	pwsaResults->dwNameSpace = NS_BTH;
	pwsaResults->lpBlob = NULL;

	while ( ERROR_SUCCESS == WSALookupServiceNext(hLookup, LUP_RETURN_NAME | LUP_RETURN_ADDR, &dwSize, pwsaResults) ) 
	{
		t_RemoteBthInfo b;
		b.Address = ((SOCKADDR_BTH *)pwsaResults->lpcsaBuffer->RemoteAddr.lpSockaddr)->btAddr;
		bHaveName = pwsaResults->lpszServiceInstanceName && *(pwsaResults->lpszServiceInstanceName);
		if ( bHaveName )
		{
			StringCchPrintf ( b.szName, sizeof(b.szName), _T("%s"), pwsaResults->lpszServiceInstanceName );
		}
		m_RemoteBthAddress.push_back(b);
	}

	// End the lookup service
	WSALookupServiceEnd(hLookup);

// 	if ( NULL != pwsaResults ) 
// 	{
// 		HeapFree(GetProcessHeap(), 0, pwsaResults);
// 		pwsaResults = NULL;
// 	}

	return (int)m_RemoteBthAddress.size();
}


int CBlueToothBase::EnumerateLocalRadios()
{
	m_LocalBthInfoList.clear();

	HANDLE hRadio = NULL;
	BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(btfrp) };

	HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio( &btfrp, &hRadio );
	if ( NULL != hFind )
	{
		do
		{
			if ( hRadio )
			{
				BLUETOOTH_RADIO_INFO LocalRadioInfo;
				memset ( &LocalRadioInfo, 0, sizeof(BLUETOOTH_RADIO_INFO) );
				LocalRadioInfo.dwSize = sizeof(BLUETOOTH_RADIO_INFO);

				if ( ERROR_SUCCESS == BluetoothGetRadioInfo ( hRadio, &LocalRadioInfo) )
				{
					// 千万注意：以下代码让蓝牙虚拟传出串口能正常工作，我是花了一个通宵的时间才找到这个原因的。
					if (FALSE == BluetoothEnableDiscovery(hRadio, TRUE))
					{
						// 						TRACE(_T("%s\n"), hwFormatMessage(GetLastError()));
						//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%d\n"),GetLastError());
					}
					if (FALSE == BluetoothEnableIncomingConnections(hRadio, TRUE))
					{
						// 						TRACE(_T("%s\n"), hwFormatMessage(GetLastError()));
						//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%d\n"),GetLastError());
					}
				}
				m_LocalBthInfoList.push_back(LocalRadioInfo);
			}

		}
		while( BluetoothFindNextRadio( hFind, &hRadio ) );
		BluetoothFindRadioClose( hFind );
		return m_LocalBthInfoList.size();
	}

	return 0;
}

void CBlueToothBase::AcceptAndReviceData(/*LPVOID lpParameter*/)
{
	UINT ulRetCode = CXN_SUCCESS;
	int  iCxnCount = 0;
	UINT            iLengthReceived = 0;//本次接收到的
	UINT            uiTotalLengthReceived;//总计接收到的
	UINT            nAllLen;              //总计需要接收到的
	UINT            nReceivcd;			  //已经接收到的
	BYTE            byteDataRecv[BT_SOCKET_RECV_SIZE];
	BYTE			cReciveData[BT_SOCKET_RECV_SIZE];

	for ( iCxnCount = 0; (CXN_SUCCESS == ulRetCode) && ( (iCxnCount < g_ulMaxCxnCycles) || (g_ulMaxCxnCycles == 0) ); iCxnCount++ ) 
	{
		BOOL bContinue = TRUE;
		uiTotalLengthReceived = 0;
		nReceivcd = 0;
		while ( bContinue /*&& (uiTotalLengthReceived < CXN_TRANSFER_DATA_LENGTH)*/ ) 
		{
			iLengthReceived = recv(m_hSocketClient,	(char*)byteDataRecv/*(char *)pszDataBufferIndex*/,	4110/*(CXN_TRANSFER_DATA_LENGTH - uiTotalLengthReceived)*/,	0);
			switch ( iLengthReceived ) 
			{
			case 0: // socket connection has been closed gracefully
				bContinue = FALSE;
				if (m_nBTState != BT_STATE_CLOSE)
				{
					m_nBTState = BT_STATE_IDLE;
				}
				break;

			case SOCKET_ERROR:
				bContinue = FALSE;
				ulRetCode = CXN_ERROR;
				if (m_nBTState != BT_STATE_CLOSE)
				{
					m_nBTState = BT_STATE_IDLE;
				}
				break;

			default: // Make sure we have enough room
				if ( iLengthReceived > BT_SOCKET_RECV_SIZE/*(CXN_TRANSFER_DATA_LENGTH - uiTotalLengthReceived)*/) 
				{
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("【蓝牙状态】接收数据过多。"));
					continue;
				}
				if (uiTotalLengthReceived == 0)
				{
					nAllLen = CalcTotalLen(byteDataRecv);
					memset(cReciveData,0,nAllLen);
				}
				uiTotalLengthReceived += iLengthReceived;

				if (nAllLen != uiTotalLengthReceived)
				{
					memcpy(cReciveData+nReceivcd,byteDataRecv,iLengthReceived);
					nReceivcd = iLengthReceived;
					Sleep(200);
					continue;
				}
				memcpy(cReciveData+nReceivcd,byteDataRecv,iLengthReceived);

				if ( uiTotalLengthReceived <= BT_SOCKET_RECV_SIZE)	//当前报文全部接收完毕
				{
					uiTotalLengthReceived = 0;
					nReceivcd = 0;
					HandleClientCommand(cReciveData);
					memset(cReciveData,0,BT_SOCKET_RECV_SIZE);
				}
				break;
			}
		}

		if (m_nBTState == BT_STATE_IDLE)
		{
			CLogPrint::LogString(XLOGLEVEL_WARNING, _T("【蓝牙状态】蓝牙连接被关断"));
			CloseSocket(BT_STATE_IDLE);
		}
	}
}


ULONG CBlueToothBase::SendMsg(char *pchMsg,BYTE bCmmd,int nLen)
{
	if (m_hSocketClient == INVALID_SOCKET)
	{
		return CXN_ERROR;
	}

	ULONG	ulRetCode = CXN_SUCCESS;
	
	int nAllLen = nLen + BT_EX_LEN;

	//拼报文头
	BYTE bstrCmd[BT_SOCKET_RECV_SIZE];

	JointMessage(bstrCmd,pchMsg,bCmmd,nLen);

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"*INFO* | Sending following data string:\n%s\n", CharToString(pchMsg));

	ulRetCode = send(m_hSocketClient, (char*)bstrCmd, nAllLen,0);

	//ulRetCode = send(m_hSocketClient, pchSendCmd, nLen,0);

	if ( SOCKET_ERROR ==  ulRetCode) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | send() call failed w/socket = [0x%I64X], szData = [%p], dataLen = [%I64u]. WSAGetLastError=[%d]\n", (ULONG64)m_hSocketClient, pchMsg, (ULONG64)CXN_TRANSFER_DATA_LENGTH, WSAGetLastError());
		ulRetCode = CXN_ERROR;
	}

	return ulRetCode;
}

ULONG	CBlueToothBase::SendMsg(CString strMsg,BYTE bCmmd,int nLen)
{
	char *pchSendMsg = NULL;
	long nSize = CString_to_char(strMsg,&pchSendMsg);

	char *pszUtf8 = NULL;
	long nDestLen = 0;
	charGBK_to_charUtf8(pchSendMsg, nSize,&pszUtf8,nDestLen);

	ULONG	ulRetCode = SendMsg(pszUtf8,bCmmd,nDestLen);
	delete []pchSendMsg;
	delete []pszUtf8;

	return ulRetCode;
}

ULONG CBlueToothBase::CloseSocket(int nBTState)
{
	ULONG ulReturn = CXN_SUCCESS;

	m_nBTState = nBTState;
	//手动关闭才初始化服务端，否则只初始化客户端Socket
	if (m_hSocketServer != INVALID_SOCKET && m_nBTState == BT_STATE_CLOSE)
	{
		if (SOCKET_ERROR == closesocket(m_hSocketServer) ) 
		{
			ulReturn = CXN_ERROR;
		}
		m_hSocketServer = INVALID_SOCKET;
	}

	if (m_hSocketClient != INVALID_SOCKET)
	{
		if (SOCKET_ERROR == closesocket(m_hSocketClient) ) 
		{
			ulReturn = CXN_ERROR;
		}
		m_hSocketClient = INVALID_SOCKET;
	}
	return ulReturn;
}

CString CBlueToothBase::FormatBthAddress(BYTE *BthAddress)
{
	ASSERT ( BthAddress );
	BLUETOOTH_ADDRESS Address;
	// 	ASSERT_ADDRESS ( BthAddress, LENGTH(Address.rgBytes)*sizeof(TCHAR) );	//deleted
	CString csBthAddress;
	int nLen = sizeof(Address.rgBytes)/sizeof(BYTE);

	for ( int i=0; i<nLen; i++ )	//LENGTH(Address.rgBytes)	Modified
	{
		CString csNode;
		csNode.Format ( _T("%.2x"), BthAddress[nLen-i-1] );		//LENGTH(Address.rgBytes)	Modified
		if ( !csBthAddress.IsEmpty() ) csBthAddress += ":";
		csBthAddress += csNode;
	}
	return csBthAddress;
}

CString CBlueToothBase::FormatBthAddress(BTH_ADDR BthAddress)
{
	BYTE rgByte[6];

    rgByte[0] = (BYTE)(0xff & BthAddress);
    rgByte[1] = (BYTE)((0xff00 & BthAddress) >> 8);
    rgByte[2] = (BYTE)((0xff0000 & BthAddress) >> 16);
    rgByte[3] = (BYTE)((0xff000000 & BthAddress) >> 24);
 	rgByte[4] = (BYTE)((0xff00000000 & BthAddress) >> 32);
 	rgByte[5] = (BYTE)((0xff0000000000 & BthAddress) >> 40);

	return FormatBthAddress(rgByte);
}

