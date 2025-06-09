#include "StdAfx.h"
#include "BlueToothClient.h"
#include "../../BlueTooth/BTFileMngrClient/BTFileMngrClient.h"

CBlueToothClient::CBlueToothClient(void):CBlueToothBase()
{
}

CBlueToothClient::~CBlueToothClient(void)
{
}

void CBlueToothClient::HandleClientCommand( BYTE *strCmmd )
{
	int nAllLen = CalcTotalLen(strCmmd);
	int nDataLen = CalDataLen(strCmmd);

	if (CalCRC(strCmmd,nAllLen))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("客户端命令<%s>校验出错，请检查！"),strCmmd);
		return;
	}

	if (strCmmd[7] == 0x81)
	{
	}
	else if(strCmmd[7] == 0x82)
	{
		char cFileName[BT_SOCKET_RECV_SIZE] = {0};
		int i;
		for (i = 0; i < nDataLen; i++)
		{
			cFileName[i] = strCmmd[13 + i];
		}
		char *pchMsg;
		long lDataLen = 0;
		charUtf8_to_charGBK(cFileName,nDataLen,&pchMsg,lDataLen);
		m_strFileNameList = (CString)pchMsg;
		m_pParentWnd->PostMessage(WM_SEND_FILE_LIST,0,0);
		delete []pchMsg;
	}
	else if (strCmmd[7] == 0x83)
	{
	}
	else if (strCmmd[7] == 0x84)
	{
		if (nDataLen != 0)
		{
			CString strFilePath = theApp.m_oXFileMngr.m_strRootPath + m_strDownLoadFileName;
			BOOL bRet = m_oLoadFile.Open(strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareExclusive);
			if (bRet == FALSE)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("文件打开失败"));
				::SendMessage(m_pParentWnd->m_hWnd, WM_END_SEND, 0, 0);
				return;
			}
			char cFileContext[BT_FILE_NAME_MAX] = {0};
			int i;
			for (i = 0; i < nDataLen; i++)
			{
				cFileContext[i] = strCmmd[13 + i];
			}
			m_oLoadFile.SeekToEnd();
			m_oLoadFile.Write(cFileContext,nDataLen);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("文件接收%d字节！"),nDataLen);
			if (m_oLoadFile.m_hFile != INVALID_HANDLE_VALUE)
			{
				m_oLoadFile.Close();
			}
			Sleep(50);
			::SendMessage(m_pParentWnd->m_hWnd, WM_CONTINRUE_SEND, 0, 0);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("文件%s接收完毕！"),m_strDownLoadFileName);
			if (m_oLoadFile.m_hFile != INVALID_HANDLE_VALUE)
			{
				m_oLoadFile.Close();
			}
			::SendMessage(m_pParentWnd->m_hWnd, WM_END_SEND, 0, 0);
		}

	}
	else if (strCmmd[7] == 0x85)
	{
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("客户端命令<%s>无法解析！"),strCmmd);
	}
}

UINT CBlueToothClient::StartBlueTooth( LPVOID lpParameter )
{
	CBlueToothClient *pThis = (CBlueToothClient*)lpParameter;

	ULONG       ulRetCode = CXN_SUCCESS;
	WSADATA     WSAData = {0};

	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);

	if (CXN_SUCCESS != ulRetCode) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, L"-FATAL- | Unable to initialize Winsock version 2.2\n");
		return -1;
	}

	ulRetCode = pThis->RunClientMode(pThis->m_CurrAddress,1);

	return ulRetCode;
}
void CBlueToothClient::StartBlueTooth_Thread()
{
	m_pThread = AfxBeginThread(StartBlueTooth, this, THREAD_PRIORITY_ABOVE_NORMAL,0,0,NULL);
	m_pThread->m_bAutoDelete = TRUE;

	if (m_pThread == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("[CPonovoVmApp::StartExternBlueToothCtrl]启动蓝牙服务失败！"));
	}
}

ULONG CBlueToothClient::RunClientMode( _In_ BTH_ADDR RemoteAddr, _In_ int iMaxCxnCycles )
{
	ULONG           ulRetCode = CXN_SUCCESS;
	int             iCxnCount = 0;
	wchar_t         *pszData = NULL;
	SOCKADDR_BTH    SockAddrBthServer;
	HRESULT         res;

	pszData = (wchar_t *) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,CXN_TRANSFER_DATA_LENGTH);

	if ( NULL == pszData ) 
	{
		ulRetCode = STATUS_NO_MEMORY;
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | HeapAlloc failed | out of memory, gle = [%d] \n", GetLastError());
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		// Setting address family to AF_BTH indicates winsock2 to use Bluetooth sockets
		// Port should be set to 0 if ServiceClassId is spesified.
		SockAddrBthServer.addressFamily = AF_BTH;
		SockAddrBthServer.serviceClassId = g_guidServiceClass;
		SockAddrBthServer.port = 0;
		SockAddrBthServer.btAddr = RemoteAddr;

		// Create a static data-string, which will be transferred to the remote Bluetooth device
		res = StringCbCopyN(pszData, CXN_TRANSFER_DATA_LENGTH, CXN_TEST_DATA_STRING, CXN_TRANSFER_DATA_LENGTH);
		if ( FAILED(res) ) 
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, L"=CRITICAL= | Creating a static data string failed\n");
			ulRetCode = CXN_ERROR;
		}
	}
	if ( CXN_SUCCESS == ulRetCode ) 
	{
		pszData[(CXN_TRANSFER_DATA_LENGTH/sizeof(wchar_t)) - 1] = 0;

		// Run the connection/data-transfer for user specified number of cycles
		for ( iCxnCount = 0; (0 == ulRetCode) && (iCxnCount < iMaxCxnCycles || iMaxCxnCycles == 0);	iCxnCount++ ) 
		{
			// 			wprintf(L"\n");
			// Open a bluetooth socket using RFCOMM protocol
			m_hSocketClient = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
			if ( INVALID_SOCKET == m_hSocketClient ) 
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());
				ulRetCode = CXN_ERROR;
				break;
			}

			m_nBTState = BT_STATE_CONNECTING;
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("【蓝牙状态】客户端等待连接……"));

			// Connect the socket (pSocket) to a given remote socket represented by address (pServerAddr)
			if ( SOCKET_ERROR == connect(m_hSocketClient,(struct sockaddr *) &SockAddrBthServer, sizeof(SOCKADDR_BTH)) ) 
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | connect() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
				ulRetCode = CXN_ERROR;
				break;
			}

			m_nBTState = BT_STATE_CONNECTED;
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("【蓝牙状态】客户端已连接。"));

			AcceptAndReviceData();
		}
	}

	if ( ulRetCode != CXN_SUCCESS)		//INVALID_SOCKET != m_hSocketClient
	{
		CloseSocket(BT_STATE_IDLE);
	}

	if ( NULL != pszData ) 
	{
		HeapFree(GetProcessHeap(), 0, pszData);
		pszData = NULL;
	}

	return(ulRetCode);
}


