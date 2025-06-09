#include "stdafx.h"

#include "SttUdpSocketDataBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttUdpSocketDataBase::CSttUdpSocketDataBase()
{
	m_pCurSockaddr = NULL;
	m_oExpandRecvBuf.AllocBuffer();
}

CSttUdpSocketDataBase::~CSttUdpSocketDataBase()
{

}

void CSttUdpSocketDataBase::OnReceiveBuffer(BYTE *pBuf, long nLen,sockaddr_in* fsockaddr)
{
	if ((nLen <= 0) || (fsockaddr == NULL))
	{
		return;
	}

	if (m_pCurSockaddr != NULL)
	{
		if (m_pCurSockaddr->sin_addr.s_addr != fsockaddr->sin_addr.s_addr)
		{
			long nLeft = m_oExpandRecvBuf.GetDataLength();
			if (nLeft != 0)
			{
				m_oExpandRecvBuf.PosMoveByUsedLen(nLeft);
			}
		}
	}

	m_pCurSockaddr = fsockaddr;

	m_oExpandRecvBuf.AppendBuffer(pBuf,nLen);
	AnalysisRecvBuf(fsockaddr);
}

BOOL CSttUdpSocketDataBase::AnalysisRecvBuf(sockaddr_in* fsockaddr)
{
	BYTE *pTemp = (BYTE *)m_oExpandRecvBuf.GetDataBuffer();
	long nDataLen = m_oExpandRecvBuf.GetDataLength();
	long nReadPos = 0;
	long nPkgDataLen = 0;
	long nPkgLen = 0;
	BOOL bSucc = TRUE;

	while(nDataLen - nReadPos >= m_nHeadLen)
	{
		if(!is_pkg_match_head(pTemp))
		{
			nReadPos += 1;
			pTemp += 1;
			continue;//
		}

		nPkgDataLen = get_pkg_data_len(pTemp);
		nPkgLen = nPkgDataLen + m_nHeadLen;

		if (nPkgLen > nDataLen - nReadPos)
		{//余下的报文长度不够一个完整的报文
			break;
		}

		ProcessRecvPacket(pTemp, nPkgLen,fsockaddr);

		nReadPos += nPkgLen;
		pTemp += nPkgLen ;
	}

	//非完整包数据移到缓存开头
	m_oExpandRecvBuf.PosMoveByUsedLen(nReadPos);	

	return TRUE;
}

BOOL CSttUdpSocketDataBase::ProcessRecvPacket(BYTE *pBuf,long nLen,sockaddr_in* fsockaddr)
{
	return FALSE;
}