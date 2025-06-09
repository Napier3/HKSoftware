#pragma once

#include <string.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include "XMiniFtpFile.h"

#define WSA_RECV         0
#define WSA_SEND         1

#define DATA_BUFSIZE    8192
#define MAX_NAME_LEN    128
#define MAX_PWD_LEN     128
#define MAX_RESP_LEN    1024
#define MAX_REQ_LEN     256
#define MAX_ADDR_LEN    80

#define FTP_PORT        21     // FTP 控制端口
#define DATA_FTP_PORT   20     // FTP 数据端口

#define USER_OK         331
#define LOGGED_IN       230
#define LOGIN_FAILED    530
#define CMD_OK          200
#define OPENING_AMODE   150
#define TRANS_COMPLETE  226
#define CANNOT_FIND     550
#define FTP_QUIT        221
#define CURR_DIR        257
#define DIR_CHANGED     250
#define OS_TYPE         215
#define REPLY_MARKER    504
#define PASSIVE_MODE    227


#define MAX_FILE_NUM        1024

#define MODE_PORT       0
#define MODE_PASV       1

#define PORT_BIND   1821


typedef struct {
	CHAR   buffRecv[DATA_BUFSIZE];
	CHAR   buffSend[DATA_BUFSIZE];
	WSABUF wsaBuf;
	SOCKET s;
	WSAOVERLAPPED o;
	DWORD dwBytesSend;
	DWORD dwBytesRecv;
	int   nStatus;
} SOCKET_INF, *LPSOCKET_INF;

typedef struct {
	TCHAR    szFileName[MAX_PATH];
	DWORD    dwFileAttributes; 
	FILETIME ftCreationTime; 
	FILETIME ftLastAccessTime; 
	FILETIME ftLastWriteTime; 
	DWORD    nFileSizeHigh; 
	DWORD    nFileSizeLow; 
} FILE_INF, *LPFILE_INF;

class CXMiniFtpServer : public CXMiniFtpFileMngr
{
public:
	CXMiniFtpServer(void);
	virtual ~CXMiniFtpServer(void);

	void Set_DEFAULT_HOME_DIR(char *pszRootPath)	{	strcpy(DEFAULT_HOME_DIR, pszRootPath);	}
	char* Get_DEFAULT_HOME_DIR()		{	return DEFAULT_HOME_DIR;	}

public:
	void InitXMiniFtpServer(const CString &strIP, const CString &strUser, const CString &strPsw,const CString &strPath);
	BOOL CreateFtpServer();
	BOOL FreeFtpServer();
	BOOL IsFtpServerExit()	{	return (m_hFtpServerThread == NULL);	}

	static void GetLocalAddress_Str(CString &strIP);
	static BOOL g_bUseRelRootPath;	//相对路径标志

protected:
	char FTP_USER[MAX_PATH];
	char FTP_PASS[MAX_PATH];
	char DEFAULT_HOME_DIR[MAX_PATH];

protected:
	static DWORD WINAPI FtpServer( LPVOID lpParam ) ;
	DWORD WINAPI x_FtpServer( LPVOID lpParam ) ;
	HANDLE m_hFtpServerThread;
	BOOL m_bFtpServerExit;

	DWORD WINAPI x_ProcessTreadIO( LPVOID lpParam ) ;
	static DWORD WINAPI ProcessTreadIO( LPVOID lpParam ) ;
	HANDLE m_hProcessTreadIO;

	//xxy 20200825:当socket出错，关闭删除socket,解决socket一出错就退出整个服务
	void DeleteClientSocket(LPSOCKET_INF pSI);
protected:
	BOOL WelcomeInfo( SOCKET s );
	int LoginIn( LPSOCKET_INF pSocketInfo  );
	int SendRes( LPSOCKET_INF pSI );
	int RecvReq( LPSOCKET_INF pSI );
	int DealCommand( LPSOCKET_INF pSI );

	int GetFileList( LPFILE_INF pFI, UINT nArraySize, const char* szPath  );
	static char* GetLocalAddress();
	char* HostToNet( char* szPath ) ;
	char* NetToHost( char* szPath ) ;
	char* RelativeDirectory( char* szDir );
	char* AbsoluteDirectory( char* szDir );

	char* ConvertCommaAddress( char* szAddress, WORD wPort );
	int ConvertDotAddress( char* szAddress, LPDWORD pdwIpAddr, LPWORD pwPort ) ;
	UINT FileListToString( char* buff, UINT nBuffSize,BOOL bDetails );
	DWORD ReadFileToBuffer( const char* szFile, char *buff, DWORD nFileSize );
	DWORD WriteToFile( SOCKET s , const char* szFile );
	int CombindFileNameSize( const char* szFileName,char* szFileNS );
	int	DataConn( SOCKET& s, DWORD dwIp, WORD wPort, int nMode ) ;
	int DataSend( SOCKET s, char* buff,int nBufSize );
	int DataRecv( SOCKET s, const char* szFileName );
	SOCKET DataAccept( SOCKET& s );

	int x_strcmp(TCHAR *str1, char *str2);
	char* x_strcat(char *str,  TCHAR *strSrc);
	int x_strlen(TCHAR *strSrc);
	char* x_GetCurrentDirectory(int nLen, char *pBuffer);
	BOOL x_SetCurrentDirectory(char *pszDir);
	void LogRcv(char *pBuff);

protected:
	DWORD g_dwEventTotal;
	DWORD g_index;
	WSAEVENT g_events[WSA_MAXIMUM_WAIT_EVENTS];
	LPSOCKET_INF g_sockets[WSA_MAXIMUM_WAIT_EVENTS];
	CRITICAL_SECTION g_cs;  
	char  g_szLocalAddr[MAX_ADDR_LEN]; 
	BOOL  g_bLoggedIn;
};