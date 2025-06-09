#ifndef CUDPSOCKET_H_H_H_H
#define CUDPSOCKET_H_H_H_H

#include "WinBaseSocket.h"

class CUdpSoket : public CWinBaseSocket
{
public:
	CUdpSoket();
	virtual ~CUdpSoket();
public:
	virtual int Receive(char *chReciveBuf,int nLen);
	//virtual int Receive(SOCKET s,char *chReciveBuf,int nLen);
	//virtual int Send(SOCKET s,char *chSendBuf,int nLen);
	virtual int Send(char *chSendBuf,int nLen);
	virtual int SetRemoteIPAndPort(char *chRemoteIP,int nPort);
	virtual int JoinLeaf(char *chMultIp);

	

};
#endif