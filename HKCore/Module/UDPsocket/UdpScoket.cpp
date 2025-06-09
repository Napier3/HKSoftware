#include "stdafx.h"
#include "UdpScoket.h"

CUdpSoket::CUdpSoket()
{

}


CUdpSoket::~CUdpSoket()
{

}



int CUdpSoket::Receive(char *chReciveBuf,int nLen)
{
	if(chReciveBuf==NULL)
	{
		return CODE_ERROR;
	}

	int len=sizeof(SOCKADDR);
	int nReieve=recvfrom(m_hSocket,chReciveBuf,nLen,0,(SOCKADDR*)&m_rsockaddr,&len);

	return nReieve;
}


int CUdpSoket::Send(char *chSendBuf,int nLen)
{
	if(chSendBuf==NULL)
	{
		return CODE_ERROR;
	}

	int nSend=sendto(m_hSocket,chSendBuf,nLen,0,(SOCKADDR*)&m_rsockaddr,sizeof(SOCKADDR));

	return nSend;
}


int CUdpSoket::SetRemoteIPAndPort(char *chRemoteIP,int nPort)
{
	if((chRemoteIP==NULL) || (strlen(chRemoteIP)==0))
	{
		return CODE_ERROR;
	}

	memset( &m_rsockaddr,0, sizeof( m_rsockaddr ) );
	m_rsockaddr.sin_family = AF_INET;
	m_rsockaddr.sin_addr.s_addr = inet_addr( chRemoteIP );
	m_rsockaddr.sin_port = htons( nPort );

	return CODE_SUCCESS;
}


int CUdpSoket::JoinLeaf(char *chMultIp)
{
	if(chMultIp==NULL)
	{
		return CODE_ERROR;
	}

	ip_mreq ipmreq;

	ipmreq.imr_multiaddr.s_addr=inet_addr(chMultIp);
	ipmreq.imr_interface.s_addr=htons(INADDR_ANY);

	int nLen=sizeof(ipmreq);

	if(setsockopt(m_hSocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&ipmreq,sizeof(ipmreq))!=0)
	{
		set_LastError("Jionleaf failed!", WSAGetLastError());
		return CODE_ERROR;
	}

	return CODE_SUCCESS;


}