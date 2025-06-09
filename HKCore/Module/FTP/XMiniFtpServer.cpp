#include "StdAfx.h"
#include "XMiniFtpServer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define _USE_IP_SET_

BOOL CXMiniFtpServer::g_bUseRelRootPath = FALSE;

CXMiniFtpServer::CXMiniFtpServer(void)
{
	strcpy(FTP_USER, "admin");
	strcpy(FTP_PASS, "admin");

	strcpy(DEFAULT_HOME_DIR, "C:\\Temp");
	g_dwEventTotal = 0;
	m_hFtpServerThread = NULL;
	m_bFtpServerExit = FALSE;
}

CXMiniFtpServer::~CXMiniFtpServer(void)
{
	
}

DWORD WINAPI CXMiniFtpServer::FtpServer( LPVOID lpParam )
{
	CXMiniFtpServer *pFtpServer = (CXMiniFtpServer*)lpParam;
	return pFtpServer->x_FtpServer(lpParam);
}

DWORD WINAPI CXMiniFtpServer::x_FtpServer( LPVOID lpParam )
{
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..........FtpServer Begin.........."));

	WSADATA wsaData;
	SOCKET sListen, sAccept;
	SOCKADDR_IN inetAddr;
	DWORD dwFlags;
	DWORD dwThreadId;
	DWORD dwRecvBytes;
	INT   nRet;

	InitializeCriticalSection(&g_cs);

	if (( nRet = WSAStartup(0x0202,&wsaData)) != 0 ) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：WSAStartup failed with error %d\n"), nRet);
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	if ((sListen = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, 
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：Failed to get a socket %d\n"), WSAGetLastError());
		WSACleanup();
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	inetAddr.sin_family = AF_INET;

 #ifdef _USE_IP_SET_
 	inetAddr.sin_addr.s_addr = inet_addr(g_szLocalAddr);
 #else
	inetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
#endif

	inetAddr.sin_port = htons(FTP_PORT);

	if (bind(sListen, (PSOCKADDR) &inetAddr, sizeof(inetAddr)) == SOCKET_ERROR)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：bind() failed with error %d\n"), WSAGetLastError());
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	if (listen(sListen, SOMAXCONN))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：listen() failed with error %d\n"), WSAGetLastError());
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Mini Ftpserver已经启动 \n"));
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Mini Ftpserver开始侦听 \n"));

	if ((sAccept = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0,
		WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：Failed to get a socket %d\n"), WSAGetLastError());
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	//创建第一个手动重置对象 
	if ((g_events[0] = WSACreateEvent()) == WSA_INVALID_EVENT)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：WSACreateEvent failed with error %d\n"), WSAGetLastError());
		m_hFtpServerThread = NULL;
		return FALSE;
	}

	// 创建一个线程处理请求
	if (CreateThread(NULL, 0, ProcessTreadIO, this, 0, &dwThreadId) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：CreateThread failed with error %d\n"), GetLastError());
		m_hFtpServerThread = NULL;
		return FALSE;
	} 

	g_dwEventTotal = 1;

	while(TRUE)
	{
		if (m_bFtpServerExit)
		{
			break;
		}

		//处理入站连接
		if ((sAccept = accept(sListen, NULL, NULL)) == INVALID_SOCKET)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：accept failed with error %d\n"), WSAGetLastError());
			break;
		}

		sockaddr_in addrMy;
		memset(&addrMy,0,sizeof(addrMy));
		int len = sizeof(addrMy);
		int ret = getpeername(sAccept,(sockaddr*)&addrMy,&len);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Accept：%d.%d.%d.%d")
			, addrMy.sin_addr.S_un.S_un_b.s_b1
			, addrMy.sin_addr.S_un.S_un_b.s_b2
			, addrMy.sin_addr.S_un.S_un_b.s_b3
			, addrMy.sin_addr.S_un.S_un_b.s_b4);

		//回传欢迎消息
		if( !WelcomeInfo( sAccept ) ) 
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("WelcomeInfo Error..."));
			break;
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("WelcomeInfo success..."));
		}

		//操作临界区，防止出错
		EnterCriticalSection(&g_cs);

		//创建一个新的SOCKET_INF结构处理接受的数据socket.
		if ((g_sockets[g_dwEventTotal] = (LPSOCKET_INF) 
			GlobalAlloc(GPTR,sizeof(SOCKET_INF))) == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：GlobalAlloc() failed with error %d\n"), GetLastError());
			break;
		} 

		//初始化新的SOCKET_INF结构
		char buff[DATA_BUFSIZE]; memset( buff,0,DATA_BUFSIZE );
		g_sockets[g_dwEventTotal]->wsaBuf.buf = buff;  
		g_sockets[g_dwEventTotal]->wsaBuf.len = DATA_BUFSIZE;
		g_sockets[g_dwEventTotal]->s = sAccept;
		memset(&(g_sockets[g_dwEventTotal]->o),0, sizeof(OVERLAPPED));
		g_sockets[g_dwEventTotal]->dwBytesSend = 0;
		g_sockets[g_dwEventTotal]->dwBytesRecv = 0;
		g_sockets[g_dwEventTotal]->nStatus     = WSA_RECV;    // 接收

		//创建事件
		if ((g_sockets[g_dwEventTotal]->o.hEvent = g_events[g_dwEventTotal] = 
			WSACreateEvent()) == WSA_INVALID_EVENT)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WSACreateEvent() failed with error %d\n"), WSAGetLastError());
			break;
		}

		//发出接受请求
		dwFlags = 0;

		if (WSARecv(g_sockets[g_dwEventTotal]->s, 
			&(g_sockets[g_dwEventTotal]->wsaBuf), 1, &dwRecvBytes, &dwFlags,
			&(g_sockets[g_dwEventTotal]->o), NULL) == SOCKET_ERROR)
		{
			if (WSAGetLastError() != ERROR_IO_PENDING)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：WSARecv():%d failed with error %d\n"), g_dwEventTotal,WSAGetLastError());
				break;
			}
		}
		g_dwEventTotal++;

		//离开临界区
		LeaveCriticalSection(&g_cs);

		//使第一个事件有信号。使工作者线程处理其他的事件
		if (WSASetEvent(g_events[0]) == FALSE)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：WSASetEvent failed with error %d\n"), WSAGetLastError());
			break;
		}
	}

	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..........FtpServer End.........."));

	m_hFtpServerThread = NULL;
	return TRUE;
}


void CXMiniFtpServer::InitXMiniFtpServer(const CString &strIP, const CString &strUser, const CString &strPsw,const CString &strPath)
{
	CString_to_char(strIP, g_szLocalAddr);
	CString_to_char(strUser, FTP_USER);
	CString_to_char(strPsw, FTP_PASS);
	CString_to_char(strPath, DEFAULT_HOME_DIR);

	long nLen = strlen(DEFAULT_HOME_DIR);

	if (DEFAULT_HOME_DIR[nLen-1] == '\\')
	{
		DEFAULT_HOME_DIR[nLen-1] = 0;
	}
}

BOOL CXMiniFtpServer::CreateFtpServer()
{
	if (m_hFtpServerThread != NULL)
	{
		return FALSE;
	}

	DWORD dwThreadId = 0;
	m_hFtpServerThread = CreateThread(NULL, 0, FtpServer, this, 0, &dwThreadId);
	m_bFtpServerExit = FALSE;

	if (m_hFtpServerThread == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("创建FTP Server线程失败"));
	}


	return TRUE;
}

BOOL CXMiniFtpServer::FreeFtpServer()
{
	m_bFtpServerExit = TRUE;

	SuspendThread(m_hFtpServerThread);
	DWORD dw_DEF_EXIT_CODE = 0;
	TerminateThread(m_hFtpServerThread, dw_DEF_EXIT_CODE);

	if (m_hProcessTreadIO != NULL)
	{

	}

	int n = 0;

// 	for (n=0; n<WSA_MAXIMUM_WAIT_EVENTS; n++)
// 	{
// 		WSAResetEvent(g_events);
// 		
// 	}

	return TRUE;
}

//xxy 20200825:当socket出错，关闭删除socket,解决socket一出错就退出整个服务
void CXMiniFtpServer::DeleteClientSocket(LPSOCKET_INF pSI)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Closing socket %d\n"), pSI->s);

	if (closesocket(pSI->s) == SOCKET_ERROR)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：closesocket() failed with error %d\n"), WSAGetLastError());
	}

	GlobalFree(pSI);
	WSACloseEvent(g_events[g_index - WSA_WAIT_EVENT_0]);

	// Cleanup g_sockets and g_events by removing the socket event handle
	// and socket information structure if they are not at the end of the
	// arrays.

	EnterCriticalSection(&g_cs);

	if ((g_index - WSA_WAIT_EVENT_0) + 1 != g_dwEventTotal)
	{
		for (int i = g_index - WSA_WAIT_EVENT_0; i < g_dwEventTotal; i++) 
		{
			g_events[i] = g_events[i + 1];
			g_sockets[i] = g_sockets[i + 1];
		}
	}
	g_dwEventTotal--;

	LeaveCriticalSection(&g_cs);
}

//工作者线程处理函数
DWORD WINAPI CXMiniFtpServer::ProcessTreadIO(LPVOID lpParameter)
{
	CXMiniFtpServer *pFtpServer = (CXMiniFtpServer*)lpParameter;
	return pFtpServer->x_ProcessTreadIO(lpParameter);
}

DWORD WINAPI CXMiniFtpServer::x_ProcessTreadIO(LPVOID lpParameter)
{
 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..........ProcessTreadIO Begin.........."));

	DWORD dwFlags;
	LPSOCKET_INF pSI;
	DWORD dwBytesTransferred;
	DWORD i; 
	int nRet = 0;

	//处理异步的WSASend, WSARecv等请求等
	while(TRUE)
	{
		if (m_bFtpServerExit)
		{
			break;
		}

		if ((g_index = WSAWaitForMultipleEvents(g_dwEventTotal, g_events, FALSE,
			WSA_INFINITE, FALSE)) == WSA_WAIT_FAILED)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("错误：WSAWaitForMultipleEvents failed %d\n"), WSAGetLastError());
			return 0;
		}

		if ((g_index - WSA_WAIT_EVENT_0) == 0)
		{
			WSAResetEvent(g_events[0]);
			continue;
		}

		pSI = g_sockets[g_index - WSA_WAIT_EVENT_0];
		WSAResetEvent(g_events[g_index - WSA_WAIT_EVENT_0]);

		if (WSAGetOverlappedResult(pSI->s, &(pSI->o), &dwBytesTransferred,
			FALSE, &dwFlags) == FALSE || dwBytesTransferred == 0)
		{
			DeleteClientSocket(pSI);
			continue;
		}

		// 已经有数据传递
		if( pSI->nStatus == WSA_RECV )
		{
			memcpy( &pSI->buffRecv[pSI->dwBytesRecv],pSI->wsaBuf.buf,dwBytesTransferred);
			pSI->dwBytesRecv += dwBytesTransferred;
			LogRcv(pSI->buffRecv);
		
			if( pSI->buffRecv[pSI->dwBytesRecv-2] == '\r'      // 要保证最后是\r\n
				&& pSI->buffRecv[pSI->dwBytesRecv-1] == '\n' 
				&& pSI->dwBytesRecv > 2 )  
			{                 
				if( !g_bLoggedIn )
				{
					nRet = LoginIn(pSI);
					if( nRet == LOGGED_IN )
					{
						g_bLoggedIn = TRUE;
					}
					else if (nRet == -1)
					{//xxy20200825
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("LoginIn(pSI) == -1 \n"), pSI->s);
						DeleteClientSocket(pSI);
						continue;
					}	
				} 
				else 
				{
					nRet = DealCommand(pSI);
					if(nRet == FTP_QUIT)
					{
						continue;
					}
					else if (nRet == -1)
					{//xxy20200825
						CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DealCommand(pSI) == -1 \n"), pSI->s);
						DeleteClientSocket(pSI);
						continue;
					}
						
				}
				// 缓冲区清除
				memset( pSI->buffRecv,0,sizeof(pSI->buffRecv) );
				pSI->dwBytesRecv = 0;
			}
		} 
		else
		{
			pSI->dwBytesSend += dwBytesTransferred;
		}

		// 继续接收以后到来的数据
		if( RecvReq( pSI ) == -1 ) 
		{//xxy20200825
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RecvReq( pSI ) == -1 \n"), pSI->s);
			DeleteClientSocket(pSI);
		}
	}

 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..........ProcessTreadIO End.........."));

	return 0;
}

void CXMiniFtpServer::LogRcv(char *pBuff)
{
	CString str;
	str = pBuff;
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T( ">>%s\n"),str);
}

// 由于只是简单的出现一个登录信息，直接用send就可以了
int CXMiniFtpServer::SendRes( LPSOCKET_INF pSI )
{
	static DWORD dwSendBytes = 0;
	pSI->nStatus = WSA_SEND;
	memset(&(pSI->o), 0,sizeof(WSAOVERLAPPED));
	pSI->o.hEvent = g_events[g_index - WSA_WAIT_EVENT_0];
	pSI->wsaBuf.buf = pSI->buffSend + pSI->dwBytesSend;
	pSI->wsaBuf.len = strlen( pSI->buffSend ) - pSI->dwBytesSend;
	if (WSASend(pSI->s, &(pSI->wsaBuf), 1,&dwSendBytes,
		0,&(pSI->o), NULL) == SOCKET_ERROR) 
	{
		if (WSAGetLastError() != ERROR_IO_PENDING) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WSASend() failed with error %d\n"), WSAGetLastError());
			return -1;
		}
	}
	return 0;
}
//接受数据
int CXMiniFtpServer::RecvReq( LPSOCKET_INF pSI )
{
	static DWORD dwRecvBytes = 0;	
	pSI->nStatus = WSA_RECV;	

	DWORD dwFlags = 0;
	memset(&(pSI->o), 0,sizeof(WSAOVERLAPPED));
	pSI->o.hEvent = g_events[g_index - WSA_WAIT_EVENT_0];
	pSI->wsaBuf.len = DATA_BUFSIZE;

	if (WSARecv(pSI->s, &(pSI->wsaBuf), 1, &dwRecvBytes,
		&dwFlags,&(pSI->o), NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WSARecv() failed with error %d\n"), WSAGetLastError());
			return -1;
		}
	}
	return 0;
}

//显示欢迎消息
BOOL CXMiniFtpServer::WelcomeInfo( SOCKET s )
{
	char* szWelcomeInfo = "220 wolcom Mini FtpServer...\r\n";
	if( send( s,szWelcomeInfo,strlen(szWelcomeInfo),0 ) == SOCKET_ERROR ) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Ftp client error:%d\n"), WSAGetLastError() );
		return FALSE;
	}
	// 刚进来，还没连接，故设置初始状态为false
	g_bLoggedIn = FALSE;
	return TRUE;
}
//登录函数
int CXMiniFtpServer::LoginIn( LPSOCKET_INF pSocketInfo  )
{
	const char* szUserOK = "331 User name okay, need password.\r\n"; 
	const char* szLoggedIn = "230 User logged in, proceed.\r\n";

	int  nRetVal = 0;
	static char szUser[MAX_NAME_LEN], szPwd[MAX_PWD_LEN];
	LPSOCKET_INF pSI = pSocketInfo;
	// 取得登录用户名
	if( strstr(strupr(pSI->buffRecv),"USER") ) 
	{		
		sprintf(szUser,"%s",pSI->buffRecv+strlen("USER")+1);
		strtok( szUser,"\r\n");		
		// 响应信息
		sprintf(pSI->buffSend,"%s",szUserOK );
		if( SendRes(pSI) == -1 ) return -1;
		return USER_OK;
	}
	if( strstr(strupr(pSI->buffRecv),"PASS") || strstr(pSI->buffRecv,"pass") ) 
	{
		sprintf(szPwd,"%s",pSI->buffRecv+strlen("PASS")+1 );
		strtok( szPwd,"\r\n");
		// 判断用户名跟口令正确性
		if( stricmp( szPwd,FTP_USER) || stricmp(szUser,FTP_PASS) ) 
		{
			sprintf(pSI->buffSend,"530 User %s cannot log in.\r\n",szUser );
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("User %s cannot log in\n"),szUser );
			nRetVal = LOGIN_FAILED;
		} 
		else 
		{
			sprintf(pSI->buffSend,"%s",szLoggedIn);
			CString strUser;
			strUser = szUser;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("User %s logged in\n"),strUser );
			nRetVal = LOGGED_IN;
		}
		if( SendRes( pSI ) == -1 ) 
			return -1;
	}
	return nRetVal;
}

char* CXMiniFtpServer::ConvertCommaAddress( char* szAddress, WORD wPort )
{
	char szPort[10];
	sprintf( szPort,"%d,%d",wPort/256,wPort%256 );
	char szIpAddr[20];
	sprintf( szIpAddr,"%s,",szAddress );
	int idx = 0;
	while( szIpAddr[idx] ) 
	{
		if( szIpAddr[idx] == '.' )
			szIpAddr[idx] = ',';
		idx ++;
	}
	sprintf( szAddress,"%s%s",szIpAddr,szPort );
	return szAddress;
}

int CXMiniFtpServer::ConvertDotAddress( char* szAddress, LPDWORD pdwIpAddr, LPWORD pwPort ) 
{
	int  idx = 0,i = 0, iCount = 0;
	char szIpAddr[MAX_ADDR_LEN]; memset( szIpAddr,0,sizeof(szIpAddr) );
	char szPort[MAX_ADDR_LEN];   memset( szPort,0,  sizeof(szPort)   );

	*pdwIpAddr = 0; *pwPort = 0;

	while( szAddress[idx]  )
	{
		if( szAddress[idx] == ',' )
		{
			iCount ++;
			szAddress[idx] ='.';
		}
		if( iCount < 4 )
			szIpAddr[idx] = szAddress[idx];
		else
			szPort[i++] =   szAddress[idx];
		idx++;
	}

	if( iCount != 5 ) return -1;
	*pdwIpAddr = inet_addr( szIpAddr );
	if( *pdwIpAddr  == INADDR_NONE ) return -1;
	char *pToken = strtok( szPort+1,"." );
	if( pToken == NULL ) return -1;
	*pwPort = (WORD)(atoi(pToken) * 256);
	pToken = strtok(NULL,".");
	if( pToken == NULL ) return -1;
	*pwPort += (WORD)atoi(pToken);

	return 0;
}

int CXMiniFtpServer::x_strcmp(TCHAR *str1, char *str2)
{
#ifdef UNICODE
	const size_t strsize=wcslen(str1)*2; // 宽字符的长度;
	size_t sz=0;
	char *pDest = new char[strsize+2];
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,pDest,strsize,str1,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
	int nRet = strcmp(pDest, str2);
	delete pDest;

	return nRet;
#else
	return strcmp(str1, str2);
#endif
}

char* CXMiniFtpServer::x_strcat(char *str,  TCHAR *strSrc)
{
#ifdef UNICODE
	const size_t strsize=wcslen(strSrc)*2; // 宽字符的长度;
	size_t sz=0;
	char *pDest = new char[strsize+2];
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,pDest,strsize,strSrc,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
	char* pRet = strcat(str, pDest);
	delete pDest;

	return pRet;
#else
	return strcat(str, strSrc);
#endif
}

int CXMiniFtpServer::x_strlen(TCHAR *strSrc)
{
#ifdef UNICODE
	const size_t strsize=wcslen(strSrc)*2; // 宽字符的长度;
	size_t sz=0;
	char *pDest = new char[strsize+2];
	_wsetlocale(LC_ALL,_T("chs"));
	wcstombs_s(&sz,pDest,strsize,strSrc,_TRUNCATE);
	_wsetlocale(LC_ALL,_T("eng"));
	int nRet = strlen(pDest);
	delete pDest;

	return nRet;
#else
	return strlen(strSrc);
#endif
}

char* CXMiniFtpServer::x_GetCurrentDirectory(int nLen, char *pBuffer)
{
	strcpy(pBuffer, DEFAULT_HOME_DIR);
	return DEFAULT_HOME_DIR;
}

BOOL CXMiniFtpServer::x_SetCurrentDirectory(char *pszDir)
{
#ifdef UNICODE
	return SetCurrentDirectory(CString(pszDir));
#else
	return SetCurrentDirectory(pszDir);
#endif
}

UINT CXMiniFtpServer::FileListToString( char* buff, UINT nBuffSize,BOOL bDetails )
{
	FILE_INF   fi[MAX_FILE_NUM];
	int nFiles = GetFileList( fi, MAX_FILE_NUM, "*.*" );
	char szTemp[128];
	sprintf( buff,"%s","" );
	if( bDetails ) {
		for( int i=0; i<nFiles; i++) {
			if( strlen(buff)>nBuffSize-128 )   break;
			if(!x_strcmp(fi[i].szFileName, "."))  continue;
			if(!x_strcmp(fi[i].szFileName,"..")) continue;
			// 时间
			SYSTEMTIME st;
			FileTimeToSystemTime(&(fi[i].ftLastWriteTime), &st);
			char  *szNoon = "AM";
			if( st.wHour > 12 ) 
			{ 
				st.wHour -= 12;
				szNoon = "PM"; 
			}
			if( st.wYear >= 2000 )
				st.wYear -= 2000;
			else st.wYear -= 1900;
			sprintf( szTemp,"%02u-%02u-%02u  %02u:%02u%s       ",
				st.wMonth,st.wDay,st.wYear,st.wHour,st.wMonth,szNoon );
			strcat( buff,szTemp );
			if( fi[i].dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
			{
				strcat(buff,"<DIR>");
				strcat(buff,"          ");
			}
			else 
			{
				strcat(buff,"     ");
				// 文件大小
				sprintf( szTemp,"% 9d ",fi[i].nFileSizeLow );
				strcat( buff,szTemp );
			}
			// 文件名
			x_strcat( buff,fi[i].szFileName );
			strcat( buff,"\r\n");
		}
	} 
	else
	{ 
		for( int i=0; i<nFiles; i++)
		{
			if( strlen(buff) + x_strlen( fi[i].szFileName ) + 2 < nBuffSize )
			{ 
				x_strcat( buff, fi[i].szFileName );
				strcat( buff, "\r\n");
			} 
			else
				break;
		}
	}
	return strlen( buff );
}

DWORD CXMiniFtpServer::ReadFileToBuffer( const char* szFile, char *buff, DWORD nFileSize )
{
	DWORD  idx = 0;
	DWORD  dwBytesLeft = nFileSize;
	DWORD  dwNumOfBytesRead = 0;
	char lpFileName[MAX_PATH];

	CString strFile;
	if(g_bUseRelRootPath)
	{
		x_GetCurrentDirectory( MAX_PATH,lpFileName );
		strcat( lpFileName,"\\" );
		strcat(lpFileName,szFile );
		strFile = lpFileName;
	}
	else
	{
		strFile = szFile;
	}
	
	HANDLE hFile = CreateFile( strFile,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( hFile != INVALID_HANDLE_VALUE )
	{
		while( dwBytesLeft > 0 ) 
		{
			if( !ReadFile( hFile,&buff[idx],dwBytesLeft,&dwNumOfBytesRead,NULL ) )
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("读文件出错.\n"));
				CloseHandle( hFile );
				return 0;
			}
			idx += dwNumOfBytesRead;
			dwBytesLeft -= dwNumOfBytesRead;
		}

		CloseHandle( hFile );
	}

	return idx;
}

//xxy 20181112
DWORD CXMiniFtpServer::WriteToFile( SOCKET s , const char* szFile )
{
	DWORD  idx = 0;
	DWORD  dwNumOfBytesWritten = 0;
	DWORD  nBytesLeft = DATA_BUFSIZE;
	char   buf[DATA_BUFSIZE] = {0};
	char   lpFileName[MAX_PATH] = {0};
	
	if(g_bUseRelRootPath)
	{
		x_GetCurrentDirectory( MAX_PATH,lpFileName );
		strcat( lpFileName,"\\" );
		strcat(lpFileName,szFile );
	}
	else
	{
		strcpy(lpFileName,szFile);
	}

	CString strDir;
	strDir = lpFileName;
	strDir = GetPathFromFilePathName(strDir);
	CreateAllDirectories(strDir);

	CString strFile;
	strFile = lpFileName;

	HANDLE hFile = CreateFile( strFile,
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL );

	if( hFile == INVALID_HANDLE_VALUE ) 
	{ 
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("打开文件出错.\n"));
		return 0;
	}

	while( TRUE )
	{
		int nBytesRecv = 0;
		idx = 0; nBytesLeft = DATA_BUFSIZE;
		while( nBytesLeft > 0 )
		{
			nBytesRecv = recv( s,&buf[idx],nBytesLeft,0 );
			if( nBytesRecv == SOCKET_ERROR ) 
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to send buffer to socket %d\n"),WSAGetLastError() );
				return -1;
			}
			if( nBytesRecv == 0 ) break;

			idx += nBytesRecv;
			nBytesLeft -= nBytesRecv;
		}

		nBytesLeft = idx;   // 要写入文件中的字节数
		idx = 0;			// 索引清0,指向开始位置

		while( nBytesLeft > 0 ) 
		{
			// 移动文件指针到文件末尾
			if( !SetEndOfFile(hFile) ) return 0;
			if( !WriteFile( hFile,&buf[idx],nBytesLeft,&dwNumOfBytesWritten,NULL ) ) 
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("写文件出错.\n"));
				CloseHandle( hFile );
				return 0;
			}
			idx += dwNumOfBytesWritten;
			nBytesLeft -= dwNumOfBytesWritten;
		}

		// 如果没有数据可接收，退出循环
		if( nBytesRecv == 0 ) 
			break;
	}

	CloseHandle( hFile );

	AddFile(strFile);

	return idx;
}

int CXMiniFtpServer::CombindFileNameSize( const char* szFileName,char* szFileNS )
{
	// 假定文件的大小不超过4GB,只处理低位
	int nFileSize = -1;
	FILE_INF fi[1];
	int nFiles = GetFileList( fi,1,szFileName );
	if( nFiles != 1 ) return -1;
	sprintf( szFileNS, "%s<%d bytes>",szFileName,fi[0].nFileSizeLow );
	nFileSize = fi[0].nFileSizeLow;
	return nFileSize;
}

int	CXMiniFtpServer::DataConn( SOCKET& s, DWORD dwIp, WORD wPort, int nMode ) 
{
	// 创建一个socket
	s = socket( AF_INET,SOCK_STREAM,0 );
	if( s == INVALID_SOCKET )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to get a socket %d\n"), WSAGetLastError());
		return -1;
	}

	struct sockaddr_in inetAddr;
	inetAddr.sin_family = AF_INET;

	if( nMode == MODE_PASV )
	{
		inetAddr.sin_port = htons( wPort );
		inetAddr.sin_addr.s_addr = dwIp;
	}
	else
	{ 
		inetAddr.sin_port = htons( DATA_FTP_PORT );
#ifdef _USE_IP_SET_
		inetAddr.sin_addr.s_addr = inet_addr(g_szLocalAddr);
#else
		inetAddr.sin_addr.s_addr = inet_addr(GetLocalAddress());
#endif
	}

	BOOL optval = TRUE;
	if( setsockopt(s,SOL_SOCKET,SO_REUSEADDR,
		(char*)&optval,sizeof(optval) ) == SOCKET_ERROR ) 
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to setsockopt %d.\n"),WSAGetLastError() );
		closesocket(s);
		return -1;
	}

	if( bind( s,(struct sockaddr*)&inetAddr,sizeof(inetAddr)) == SOCKET_ERROR )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to bind a socket %d.\n"),WSAGetLastError() );
		closesocket(s);
		return -1;
	}

	if( MODE_PASV == nMode )
	{
		if( listen( s,SOMAXCONN ) == SOCKET_ERROR ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to listen a socket %d.\n"),WSAGetLastError() );
			closesocket(s);
			return -1;
		}
	} 
	else if( MODE_PORT == nMode ) 
	{
		struct sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port   = htons( wPort );
		addr.sin_addr.s_addr   = dwIp;
		if( connect( s, (const sockaddr*)&addr,sizeof(addr) ) == SOCKET_ERROR ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to connect a socket %d\n"),WSAGetLastError() );
			closesocket( s );
			return -1;
		}
	}
	return 0;
}

int CXMiniFtpServer::DataSend( SOCKET s, char* buff,int nBufSize )
{
	int nBytesLeft = nBufSize;
	int idx = 0, nBytes = 0;
	while( nBytesLeft > 0 ) {
		nBytes = send( s,&buff[idx],nBytesLeft,0);
		if( nBytes == SOCKET_ERROR )
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Failed to send buffer to socket %d\n"),WSAGetLastError() );
			closesocket( s );
			return -1;
		}
		nBytesLeft -= nBytes;
		idx += nBytes;
	}
	return idx;
}

int CXMiniFtpServer::DataRecv( SOCKET s, const char* szFileName )
{
	return WriteToFile( s, szFileName );	
}

SOCKET CXMiniFtpServer::DataAccept( SOCKET& s )
{
	SOCKET sAccept = accept( s ,NULL,NULL );
	if( sAccept != INVALID_SOCKET ) 
	{
		closesocket( s );
	}
	return sAccept;
}

int CXMiniFtpServer::DealCommand( LPSOCKET_INF pSI )
{
	int nRetVal = 0;
	static SOCKET sAccept = INVALID_SOCKET;
	static SOCKET s       = INVALID_SOCKET;
	static BOOL   bPasv   = FALSE;

	char  szCmd[MAX_REQ_LEN]; 
	char  szCurrDir[MAX_PATH];
	strcpy( szCmd, pSI->buffRecv );
	if( strtok( szCmd," \r\n") == NULL ) return -1;
	strupr( szCmd );

	const char*  szOpeningAMode = "150 Opening ASCII mode data connection for ";
	static DWORD  dwIpAddr = 0;
	static WORD   wPort    = 0;
	// ?PORT n1,n2,n3,n4,n5,n6
	if( strstr(szCmd,"PORT") )
	{
		if( ConvertDotAddress( pSI->buffRecv+strlen("PORT")+1,&dwIpAddr,&wPort) == -1 ) 
			return -1;
		const char*  szPortCmdOK    = "200 PORT Command successful.\r\n";
		sprintf(pSI->buffSend,"%s",szPortCmdOK );
		if( SendRes( pSI ) == -1 ) return -1;
		bPasv = FALSE;
		return CMD_OK;
	}

	if( strstr( szCmd,"PASV") ) 
	{
		if( DataConn( s, htonl(INADDR_ANY), PORT_BIND, MODE_PASV ) == -1 )
			return -1;

#ifdef _USE_IP_SET_
		char pszLocalAddress[20];			strcpy(pszLocalAddress, g_szLocalAddr);
		char *szCommaAddress = ConvertCommaAddress( pszLocalAddress,PORT_BIND );
#else
		char *szCommaAddress = ConvertCommaAddress( GetLocalAddress(),PORT_BIND );
#endif

		sprintf( pSI->buffSend,"227 Entering Passive Mode (%s).\r\n",szCommaAddress );
		if( SendRes( pSI ) == -1 ) 
			return -1;
		bPasv = TRUE;
		return PASSIVE_MODE;		
	}
	if( strstr( szCmd, "NLST") || strstr( szCmd,"LIST") ) 
	{
		if( bPasv ) sAccept = DataAccept( s );
		if( !bPasv )
			sprintf(pSI->buffSend,"%s/bin/ls.\r\n",szOpeningAMode );
		else 
			strcpy(pSI->buffSend,"125 Data connection already open; Transfer starting.\r\n");		

		if( SendRes( pSI ) == -1 ) 
			return -1;
		// 取得文件列表信息，并转换成字符串
		BOOL bDetails = strstr(szCmd,"LIST")?TRUE:FALSE;
		char buff[DATA_BUFSIZE];
		UINT nStrLen = FileListToString( buff,sizeof(buff),bDetails);
		if( !bPasv ) 
		{
			if( DataConn( s,dwIpAddr,wPort,MODE_PORT ) == -1 )
				return -1;
			if( DataSend( s, buff,nStrLen ) == -1 )
				return -1;
			closesocket(s);
		}
		else 
		{
			DataSend( sAccept,buff,nStrLen );
			closesocket( sAccept );
		}
		sprintf( pSI->buffSend,"%s","226 Transfer complete.\r\n" );
		if( SendRes( pSI ) == -1 )
			return -1;

		return TRANS_COMPLETE;
	}
	if( strstr( szCmd, "RETR") ) 
	{
		if( bPasv ) sAccept = DataAccept(s);	
		char szFileNS[MAX_PATH];
		//D:\Program Files 路径就不对了
//		char *szFile = strtok( NULL," \r\n" );
		char *szFile = strtok( NULL,"\r\n" );
		int nFileSize = CombindFileNameSize( szFile,szFileNS );
		if( nFileSize == -1  ) 
		{
			sprintf( pSI->buffSend,"550 %s: 系统找不到指定的文件.\r\n",szFile);
			if( SendRes( pSI ) == -1 )
				return -1;
			if( !bPasv ) closesocket( sAccept );
			else closesocket( s );

			return CANNOT_FIND; 
		}
		else 
			sprintf(pSI->buffSend,"%s%s.\r\n",szOpeningAMode,szFileNS);

		if( SendRes( pSI ) == -1 )
			return -1;

		char* buff = new char[nFileSize];
		if( NULL ==buff ) 
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Not enough memory error!\n"));
			return -1;
		}
		if( ReadFileToBuffer( szFile,buff, nFileSize ) == (DWORD)nFileSize ) 
		{
			// 处理Data FTP连接
			Sleep( 10 );
			if( bPasv ) 
			{
				DataSend( sAccept,buff,nFileSize );
				closesocket( sAccept );
			} 
			else 
			{
				if( DataConn( s,dwIpAddr,wPort,MODE_PORT ) == -1 )
					return -1;
				DataSend( s, buff, nFileSize );
				closesocket( s );
			}
		}
		if( buff != NULL )
			delete[] buff;

		sprintf( pSI->buffSend,"%s","226 Transfer complete.\r\n" );
		if( SendRes( pSI ) == -1 )
			return -1;


		return TRANS_COMPLETE;
	}
	if( strstr( szCmd, "STOR") ) 
	{
		if( bPasv ) sAccept = DataAccept(s);
		//xxy 20181112
//		char *szFile = strtok( NULL," \r\n" );
		char *szFile = strtok( NULL,"\r\n" );
		if( NULL == szFile ) return -1;
		sprintf(pSI->buffSend,"%s%s.\r\n",szOpeningAMode,szFile);
		if( SendRes( pSI ) == -1 )
			return -1;

		// 处理Data FTP连接
		if( bPasv ) 
			DataRecv( sAccept,szFile );
		else 
		{
			if( DataConn( s,dwIpAddr,wPort,MODE_PORT ) == -1 )
				return -1;
			DataRecv( s, szFile );
		}

		sprintf( pSI->buffSend,"%s","226 Transfer complete.\r\n" );
		if( SendRes( pSI ) == -1 )
			return -1;

		return TRANS_COMPLETE;
	}
	if( strstr( szCmd,"QUIT" ) )
	{
		sprintf( pSI->buffSend,"%s","221 Good bye,欢迎下次再来.\r\n" );
		if( SendRes( pSI ) == -1 )
			return -1;

		return FTP_QUIT; 
	}
	if( strstr( szCmd,"XPWD" ) || strstr( szCmd,"PWD") ) 
	{
		x_GetCurrentDirectory( MAX_PATH,szCurrDir );

		sprintf( pSI->buffSend,"257 \"%s\" is current directory.\r\n",
			RelativeDirectory(szCurrDir) );

		if( SendRes( pSI ) == -1 ) return -1;

		return CURR_DIR;
	}
	if( strstr( szCmd,"CWD" ) || strstr(szCmd,"CDUP") ) 
	{
		char *szDir = strtok( NULL,"\r\n" );
		if( szDir == NULL ) szDir = "\\";
		char szSetDir[MAX_PATH];
		if( strstr(szCmd,"CDUP") ) 
			strcpy(szSetDir,"..");
		else 
			strcpy(szSetDir,AbsoluteDirectory( szDir ) );
		if( !x_SetCurrentDirectory( szSetDir ) ) 
		{
			sprintf(szCurrDir,"\\%s",szSetDir); 
			sprintf( pSI->buffSend,"550 %s No such file or Directory.\r\n",
				RelativeDirectory(szCurrDir) );
			nRetVal = CANNOT_FIND;
		} 
		else 
		{
			x_GetCurrentDirectory( MAX_PATH,szCurrDir );
			sprintf( pSI->buffSend,"250 Directory changed to /%s.\r\n",
				RelativeDirectory(szCurrDir) );
			nRetVal = DIR_CHANGED;
		}
		if( SendRes( pSI ) == -1 ) return -1;

		return nRetVal;
	}
	if( strstr( szCmd,"SYST" ) ) 
	{
		sprintf( pSI->buffSend,"%s","215 Windows_NT Version 4.0\r\n");
		if( SendRes( pSI ) == -1 ) return -1;
		return OS_TYPE;
	}
	if( strstr( szCmd,"TYPE") ) 
	{
		char *szType = strtok(NULL,"\r\n");
		if( szType == NULL ) szType = "A";
		sprintf(pSI->buffSend,"200 Type set to %s.\r\n",szType );
		if( SendRes( pSI ) == -1 ) 
			return -1;
		return CMD_OK;		
	}
	if( strstr( szCmd,"REST" ) )
	{
		sprintf( pSI->buffSend,"504 Reply marker must be 0.\r\n");
		if( SendRes( pSI ) == -1 ) 
			return -1;
		return REPLY_MARKER;		
	}
	if( strstr( szCmd,"NOOP") ) 
	{
		sprintf( pSI->buffSend,"200 NOOP command successful.\r\n");
		if( SendRes( pSI ) == -1 ) 
			return -1;
		return CMD_OK;		
	}
	//其余都是无效的命令
	sprintf(pSI->buffSend,"500 '%s' command not understand.\r\n",szCmd );
	if( SendRes( pSI ) == -1 ) return -1;	
	return nRetVal;
}

///////////////////////////////////////////////////////////////////////////////////////////
//其他函数
void CXMiniFtpServer::GetLocalAddress_Str(CString &strIP)
{
	WSADATA wsaData;
	INT   nRet;

	if (( nRet = WSAStartup(0x0202,&wsaData)) != 0 ) 
	{
		strIP = _T("192.168.1.1");
	}

	strIP = GetLocalAddress();
}

char* CXMiniFtpServer::GetLocalAddress()
{
	struct in_addr *pinAddr;
	LPHOSTENT	lpHostEnt;
	int			nRet;
	int			nLen;
	char        szLocalAddr[80];
	memset( szLocalAddr,0,sizeof(szLocalAddr) );
	// Get our local name
	nRet = gethostname(szLocalAddr,sizeof(szLocalAddr) );
	if (nRet == SOCKET_ERROR)
	{
		return NULL;
	}
	// "Lookup" the local name
	lpHostEnt = gethostbyname(szLocalAddr);
	if (NULL == lpHostEnt)	
	{
		return NULL;
	}
	// Format first address in the list
	pinAddr = ((LPIN_ADDR)lpHostEnt->h_addr);
	nLen = strlen(inet_ntoa(*pinAddr));
	if ((DWORD)nLen > sizeof(szLocalAddr))
	{
		WSASetLastError(WSAEINVAL);
		return NULL;
	}

	return inet_ntoa(*pinAddr);
}

int CXMiniFtpServer::GetFileList( LPFILE_INF pFI, UINT nArraySize, const char* szPath  )
{
	WIN32_FIND_DATA  wfd;
	int idx = 0;
	char lpFileName[MAX_PATH];

	if(g_bUseRelRootPath)
	{
		x_GetCurrentDirectory( MAX_PATH,lpFileName );
		strcat( lpFileName,"\\" );
		strcat( lpFileName, szPath );	
	}
	else
	{
		strcpy( lpFileName, szPath );
	}
	
	HANDLE hFile = FindFirstFile( CString(lpFileName), &wfd );
	if ( hFile != INVALID_HANDLE_VALUE ) 
	{
		pFI[idx].dwFileAttributes = wfd.dwFileAttributes;
		lstrcpy( pFI[idx].szFileName, wfd.cFileName );
		pFI[idx].ftCreationTime = wfd.ftCreationTime;
		pFI[idx].ftLastAccessTime = wfd.ftLastAccessTime;
		pFI[idx].ftLastWriteTime  = wfd.ftLastWriteTime;
		pFI[idx].nFileSizeHigh    = wfd.nFileSizeHigh;
		pFI[idx++].nFileSizeLow   = wfd.nFileSizeLow;
	
		while( FindNextFile( hFile,&wfd ) && idx < (int)nArraySize ) 
		{
			pFI[idx].dwFileAttributes = wfd.dwFileAttributes;
			lstrcpy( pFI[idx].szFileName, wfd.cFileName );
			pFI[idx].ftCreationTime = wfd.ftCreationTime;
			pFI[idx].ftLastAccessTime = wfd.ftLastAccessTime;
			pFI[idx].ftLastWriteTime  = wfd.ftLastWriteTime;
			pFI[idx].nFileSizeHigh    = wfd.nFileSizeHigh;
			pFI[idx++].nFileSizeLow   = wfd.nFileSizeLow;
		}

		FindClose( hFile );
	}

	return idx;
}
char* CXMiniFtpServer::HostToNet( char* szPath ) 
{
	int idx = 0;
	if( NULL == szPath ) return NULL;
	strlwr( szPath );

	while( szPath[idx] ) 
	{ 
		if( szPath[idx] == '\\' )
			szPath[idx] = '/';
		idx ++;
	}

	return szPath;
}

char* CXMiniFtpServer::NetToHost( char* szPath )
{
	int idx = 0;
	if( NULL == szPath ) return NULL;
	strlwr( szPath );
	while( szPath[idx] ) 
	{ 
		if( '/' == szPath[idx]  )
			szPath[idx] = '\\';
		idx ++;
	}
	return szPath;
}
char* CXMiniFtpServer::RelativeDirectory( char* szDir )
{
	int nStrLen = strlen(DEFAULT_HOME_DIR);

// 	if( !strnicmp( szDir,DEFAULT_HOME_DIR, nStrLen ) ) 
// 	{
// 		szDir += nStrLen;
// 	}

	if( szDir && szDir[0] == '\0' ) szDir = "/";

	return HostToNet(szDir);
}
char* CXMiniFtpServer::AbsoluteDirectory( char* szDir )
{
	char szTemp[MAX_PATH];
	strcpy( szTemp,DEFAULT_HOME_DIR+2 );
	if( NULL == szDir ) return NULL;
	if( '/' == szDir[0] )
		strcat( szTemp, szDir );
	szDir = szTemp ;	
	return NetToHost(szDir);
}

