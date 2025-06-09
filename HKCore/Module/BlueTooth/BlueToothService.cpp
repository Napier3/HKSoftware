#include "StdAfx.h"
#include "BlueToothService.h"

#define CXN_INSTANCE_STRING L"Sample Bluetooth Server"

CBlueToothService::CBlueToothService(void):CBlueToothBase()
{
	m_pThread = NULL;
}

CBlueToothService::~CBlueToothService(void)
{
	if (m_pThread != NULL)
	{
		CloseSocket(BT_STATE_CLOSE);

		CTickCount32 oTick;
		while(m_pThread != NULL)
		{
			oTick.DoEvents(10);
		}
		delete m_pThread;
		m_pThread = NULL;
	}
}


void CBlueToothService::ReSetFileLoadFlag( CExBaseObject* pObj,BOOL bflag )
{
	if(xfile_IsFolder(pObj->GetClassID()))
	{
		ASSERT(pObj != NULL);
		CExBaseObject* pObjChild = NULL;

		if( xfile_IsFolder(pObj->GetClassID()) )
		{
			CExBaseList* pList = (CExBaseList*)pObj;
			POS pos = pList->GetHeadPosition();

			while(pos != NULL)
			{
				pObjChild = (CExBaseObject*)pList->GetNext(pos);
				ReSetFileLoadFlag(pObjChild,bflag);
			}
		}
	}
	if (xfile_IsFile(pObj->GetClassID()))
	{
		if (bflag = FALSE)
		{
			pObj->m_dwItemData = 0;
		}
		else
		{
			CString strFold = ((CXFile*)pObj)->GetTotalFileName();
			if (strFold == m_strSendFile)
			{
				pObj->m_dwItemData = 1;//表示已经被发送了
			}
		}
	}
}

void CBlueToothService::JointFileName( CExBaseObject* pObj,CString &strFileName,int nFileType )
{
	if(xfile_IsFolder(pObj->GetClassID()))
	{
		ASSERT(pObj != NULL);
		CExBaseObject* pObjChild = NULL;

		if( xfile_IsFolder(pObj->GetClassID()) )
		{
			CExBaseList* pList = (CExBaseList*)pObj;
			POS pos = pList->GetHeadPosition();

			while(pos != NULL)
			{
				pObjChild = (CExBaseObject*)pList->GetNext(pos);
				JointFileName(pObjChild,strFileName,nFileType);
			}
		}
	}
	if (xfile_IsFile(pObj->GetClassID()))
	{
		if (nFileType == 0 || pObj->m_dwItemData != 1)
		{
			CString strFold = ((CXFile*)pObj)->GetFolderPath();
			strFileName += strFold + pObj->m_strName;
			strFileName += _T(":");
		}

	}
}

UINT CBlueToothService::StartBlueTooth( LPVOID lpParameter )
{
	CBlueToothService *pThis = (CBlueToothService*)lpParameter;

	ULONG       ulRetCode = CXN_SUCCESS;
	WSADATA     WSAData = {0};

	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);

	if (CXN_SUCCESS != ulRetCode) 
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, L"-FATAL- | Unable to initialize Winsock version 2.2\n");
		return -1;
	}

	ulRetCode = pThis->RunServerMode(1);

	pThis->m_pThread = NULL;

	return 1;
}

void CBlueToothService::StartBlueTooth_Thread()
{
	m_pThread = AfxBeginThread(StartBlueTooth, this, THREAD_PRIORITY_ABOVE_NORMAL,0,0,NULL);
	m_pThread->m_bAutoDelete = TRUE;
	
	if (m_pThread == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("[CPonovoVmApp::StartExternBlueToothCtrl]启动蓝牙服务失败！"));
	}
}


ULONG CBlueToothService::RunServerMode( _In_ int iMaxCxnCycles )
{
	ULONG           ulRetCode = CXN_SUCCESS;
	int             iAddrLen = sizeof(SOCKADDR_BTH);
	int             iCxnCount = 0;
	UINT            iLengthReceived = 0;
	// 	UINT            uiTotalLengthReceived;
	size_t          cbInstanceNameSize = 0;
	char *          pszDataBuffer = NULL;
	char *          pszDataBufferIndex = NULL;
	wchar_t *       pszInstanceName = NULL;
	wchar_t         szThisComputerName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD           dwLenComputerName = MAX_COMPUTERNAME_LENGTH + 1;
	// 	SOCKET          m_hSocketServer = INVALID_SOCKET;
	// 	SOCKET          m_hSocketClient = INVALID_SOCKET;
	WSAQUERYSET     wsaQuerySet = {0};
	SOCKADDR_BTH    SockAddrBthLocal = {0};
	LPCSADDR_INFO   lpCSAddrInfo = NULL;
	HRESULT         res;

	// This fixed-size allocation can be on the stack assuming the total doesn't cause a stack overflow (depends on your compiler settings)
	// However, they are shown here as dynamic to allow for easier expansion
	lpCSAddrInfo = (LPCSADDR_INFO) HeapAlloc( GetProcessHeap(),	HEAP_ZERO_MEMORY, sizeof(CSADDR_INFO) );
	if ( NULL == lpCSAddrInfo ) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"!ERROR! | Unable to allocate memory for CSADDR_INFO\n");
		ulRetCode = CXN_ERROR;
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		if ( !GetComputerName(szThisComputerName, &dwLenComputerName) ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | GetComputerName() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	// Open a bluetooth socket using RFCOMM protocol

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		m_hSocketServer = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
		if ( INVALID_SOCKET == m_hSocketServer ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		// Setting address family to AF_BTH indicates winsock2 to use Bluetooth port
		SockAddrBthLocal.addressFamily = AF_BTH;
		SockAddrBthLocal.port = BT_PORT_ANY;

		// bind() associates a local address and port combination with the socket just created.
		// This is most useful when the application is a server that has a well-known port that clients know about in advance.
		if ( SOCKET_ERROR == bind(m_hSocketServer, (struct sockaddr *) &SockAddrBthLocal, sizeof(SOCKADDR_BTH) ) ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | bind() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)m_hSocketServer, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		ulRetCode = getsockname(m_hSocketServer, (struct sockaddr *)&SockAddrBthLocal, &iAddrLen);
		if ( SOCKET_ERROR == ulRetCode ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | getsockname() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)m_hSocketServer, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		// CSADDR_INFO
		lpCSAddrInfo[0].LocalAddr.iSockaddrLength = sizeof( SOCKADDR_BTH );
		lpCSAddrInfo[0].LocalAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
		lpCSAddrInfo[0].RemoteAddr.iSockaddrLength = sizeof( SOCKADDR_BTH );
		lpCSAddrInfo[0].RemoteAddr.lpSockaddr = (LPSOCKADDR)&SockAddrBthLocal;
		lpCSAddrInfo[0].iSocketType = SOCK_STREAM;
		lpCSAddrInfo[0].iProtocol = BTHPROTO_RFCOMM;

		// If we got an address, go ahead and advertise it.
		ZeroMemory(&wsaQuerySet, sizeof(WSAQUERYSET));
		wsaQuerySet.dwSize = sizeof(WSAQUERYSET);
		wsaQuerySet.lpServiceClassId = (LPGUID) &g_guidServiceClass;

		// Adding a byte to the size to account for the space in the format string in the swprintf call. 
		// This will have to change if converted to UNICODE
		res = StringCchLength(szThisComputerName, sizeof(szThisComputerName), &cbInstanceNameSize);
		if( FAILED(res) ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"-FATAL- | ComputerName specified is too large\n");
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		cbInstanceNameSize += sizeof(CXN_INSTANCE_STRING) + 1;
		pszInstanceName = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cbInstanceNameSize);
		if ( NULL == pszInstanceName ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"-FATAL- | HeapAlloc failed | out of memory | gle = [%d] \n", GetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		StringCbPrintf(pszInstanceName, cbInstanceNameSize, L"%s %s", szThisComputerName, CXN_INSTANCE_STRING);
		wsaQuerySet.lpszServiceInstanceName = pszInstanceName;
		wsaQuerySet.lpszComment = L"Example Service instance registered in the directory service through RnR";
		wsaQuerySet.dwNameSpace = NS_BTH;
		wsaQuerySet.dwNumberOfCsAddrs = 1;      // Must be 1.
		wsaQuerySet.lpcsaBuffer = lpCSAddrInfo; // Req'd.

		// As long as we use a blocking accept(), we will have a race between advertising the service and actually being ready to
		// accept connections.  If we use non-blocking accept, advertise the service after accept has been called.

		if ( SOCKET_ERROR == WSASetService(&wsaQuerySet, RNRSERVICE_REGISTER, 0) ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | WSASetService() call failed. WSAGetLastError=[%d]\n", WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	// listen() call indicates winsock2 to listen on a given socket for any incoming connection.
	if ( CXN_SUCCESS == ulRetCode ) 
	{
		if ( SOCKET_ERROR == listen(m_hSocketServer, CXN_DEFAULT_LISTEN_BACKLOG) ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"=CRITICAL= | listen() call failed w/socket = [0x%I64X]. WSAGetLastError=[%d]\n", (ULONG64)m_hSocketServer, WSAGetLastError());
			ulRetCode = CXN_ERROR;
		}
	}

	if ( CXN_SUCCESS == ulRetCode ) 
	{
		for ( iCxnCount = 0; (CXN_SUCCESS == ulRetCode) && ( (iCxnCount < iMaxCxnCycles) || (iMaxCxnCycles == 0) ); iCxnCount++ ) 
		{
			// accept() call indicates winsock2 to wait for any incoming connection request from a remote socket.
			// If there are already some connection requests on the queue, then accept() extracts the first request and creates a new socket and
			// returns the handle to this newly created socket. This newly created socket represents the actual connection that connects the two sockets.

			while (BT_STATE_CLOSE != m_nBTState)
			{
				m_nBTState = BT_STATE_ACCEPTING;
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("【蓝牙状态】服务器等待连接……。"));

				m_hSocketClient = accept(m_hSocketServer, NULL, NULL);

				// 注意！一定要加这一段，没有 Select的话，获得的Client句柄无法发送数据，send函数执行成功，但实际客户端收不到
				fd_set  rfds,wfds;
				FD_ZERO(&rfds);  
				FD_ZERO(&wfds);
				FD_SET(m_hSocketClient,&rfds);  
				FD_SET(m_hSocketClient,&wfds);
				int Rtn = select(0, &rfds, &wfds,NULL,NULL);
				if (Rtn>0)  
				{  
					if(FD_ISSET(m_hSocketClient,&rfds)>0)//表示有读的  
					{  
						int i=0;
					}  
					if (FD_ISSET(m_hSocketClient,&wfds)>0)//表示可以写  
					{  
						int i=0;
					}  
				}  

				if ( INVALID_SOCKET == m_hSocketClient ) 
				{
					ulRetCode = CXN_ERROR;
					break; // Break out of the for loop
				}
				m_nBTState = BT_STATE_CONNECTED;
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("【蓝牙状态】服务器已连接。"));

				DealDataBeforeSend();

				// Begin thread of accepting client & receiving data
				AcceptAndReviceData();
			}

		}
	}

	if ( CXN_ERROR == ulRetCode ) 
	{
		CloseSocket(BT_STATE_IDLE);
	}

	if ( NULL != lpCSAddrInfo ) 
	{
		HeapFree(GetProcessHeap(), 0, lpCSAddrInfo);
		lpCSAddrInfo = NULL;
	}
	if ( NULL != pszInstanceName ) 
	{
		HeapFree(GetProcessHeap(), 0, pszInstanceName);
		pszInstanceName = NULL;
	}

	if ( NULL != pszDataBuffer )
	{
		HeapFree(GetProcessHeap(), 0, pszDataBuffer);
		pszDataBuffer = NULL;
	}

	return(ulRetCode);
}
