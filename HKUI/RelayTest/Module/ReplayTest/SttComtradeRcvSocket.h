#ifndef _CSttComtradeRcvSocket_h__
#define _CSttComtradeRcvSocket_h__

#include "../SttSocket/SttSocketDataBase.h"
#include "../RecordTest/SttRcdSocketBufferZip.h"
#include "ComtradeBufMngr.h"


class CSttComtradeRcvSocket : public CWinTcpSocketClient
{
public:
	CSttComtradeRcvSocket();
	virtual ~CSttComtradeRcvSocket();

	void AttatchSocketDatabase(CSttSocketDataBase *pSttSocket);

	//收到发送完成后，通知接收线程
	void OnSendDataFinish(int nIndex,int nSendNum);
	void OnSendDataStart(int nIndex,int nSendNum);
	//收到发送完成后，将接收数据解压，填充到指定ComtradeBuf中
	BOOL MoveToComtradeBuf();
	void ResetRcvLen();

public:
	virtual void OnClose(int nErrorCode);
	virtual void OnSocketIdle(long nMs);
	virtual void WaitForThreadExit();

protected:
	CSttSocketDataBase *m_pSttSocket;

public:
	long m_nSocketIdleLong;
	BYTE *m_pPacketBuff;//[COMTRADE_ABBUF_SIZE+10];
	
	long m_nReceiveBufLen;
	long m_nCurrRcdRcvLen;
	long m_nRecvPacketState;//0:未收到准备发送命令，1：收到准备发送命令，数据未开始接受，2：开始接受数据

	int m_nSendFinishIndex;
	int m_nSendNum;
	int m_nStartSendIndex;
	int m_nNeedNum;
#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttComtradeRcvThread;
};
void *SttComtradeRcvThread(LPVOID pParam);
#else
	HANDLE m_pSttComtradeRcvThread;
	static UINT SttComtradeRcvThread(LPVOID pParam);	
};
#endif

extern CSttComtradeRcvSocket g_oSttComtradeRcvSocket;


#endif 
