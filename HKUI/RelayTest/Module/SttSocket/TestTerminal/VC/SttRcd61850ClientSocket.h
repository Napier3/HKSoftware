#ifndef _CSttRcd61850ClientSocket_h__
#define _CSttRcd61850ClientSocket_h__

#include "../SttClientSocketBase.h"

#ifdef _PSX_QT_LINUX_
#include "../../../../../Module/Socket/Qt/WinTcpSocketClient.h"
#else
#include "../../../../../Module/Socket/WinTcpSocketClient.h"
#endif

//定义录波接受缓存，默认最大缓存为200K，即200K批量处理一次。
#define RCDRCV_BUFFER_MAX_LEN   204800

class CSttRcdBufferRcvMsg
{
public:
	virtual void OnRcdBufRcv(BYTE *pBuffer, long nLen) = 0;
};

class CSttRcd61850ClientSocket : public CWinTcpSocketClient
{
public:
	CSttRcd61850ClientSocket();
  virtual ~CSttRcd61850ClientSocket();
	
	CString m_strIPRemote;
	int m_nPortRemote;

	void AttatchRcdBufRcvMsg(CSttRcdBufferRcvMsg *p)	{	m_pSttRcdBufferRcvMsg = p;	}
	void SetRcdRcvBuffMaxLen(long nLen);

public:
	virtual void OnClose(int nErrorCode);
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnSocketIdle(long nMs);

protected:
	long m_nCurrRcdRcvLen;
	BYTE  *m_pRcdRcvBuff;
	long m_nRcdBuffMaxLen;
	long m_nSocketIdleLong;
	CSttRcdBufferRcvMsg *m_pSttRcdBufferRcvMsg;

	void FireRcdBufRcvMsg();
};

#endif // _CSttRcd61850ClientSocket_h__
