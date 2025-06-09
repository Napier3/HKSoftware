#ifndef WINSOCKET_H_H_H
#define WINSOCKET_H_H_H

#include <Winsock2.h>
#pragma comment( lib, "ws2_32.lib" )

const int CODE_SUCCESS=0;
const int CODE_ERROR=-1;
const int ERR_MAXLENGTH=512;

class CWinBaseSocket
{
public:
	CWinBaseSocket();
	virtual ~CWinBaseSocket();

public:
	virtual int InitSocket();
	virtual int Creat(int nNetTYpe);
	virtual int Close();
	virtual int Bind( char* strIP, unsigned int iPort );
	virtual int get_LocalIP( char* strIP );											
	virtual int get_LocalPort( int* iPort );							
	virtual int get_RemoteIP( char* strIP );								
	virtual int get_RemotePort( int* iPort );								
	virtual int get_LocalHost( char* strBuffer, int iBufLen );				
	virtual int get_RemoteHost( char* strBuffer, int iBufLen );						
	virtual int set_SendTimeout( int ms );								
	virtual int set_RecvTimeout( int ms );									
	virtual void longToDottedQuad( unsigned long ulLong, char* cBuffer );
	virtual int GetInitFlag();
	virtual void  get_LastError( char* strBuffer, int* iErrNum );
	
public:	
	void CWinBaseSocket::set_LastError( char* newError, int errNum );
public:	
	sockaddr_in m_sockaddr;	
	sockaddr_in m_rsockaddr;	
	WORD m_wVersion;
	int m_nInitFlag;//初始化标志：0表示成功，－1标识失败
	char m_LastError[ERR_MAXLENGTH+1];
	int	 m_ErrorNumber;
public:	
	SOCKET m_hSocket;					
};

#endif