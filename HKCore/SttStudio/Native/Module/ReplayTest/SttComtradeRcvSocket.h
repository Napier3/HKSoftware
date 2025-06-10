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

	//�յ�������ɺ�֪ͨ�����߳�
	void OnSendDataFinish(int nIndex,int nSendNum);
	void OnSendDataStart(int nIndex,int nSendNum);
	//�յ�������ɺ󣬽��������ݽ�ѹ����䵽ָ��ComtradeBuf��
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
	long m_nRecvPacketState;//0:δ�յ�׼���������1���յ�׼�������������δ��ʼ���ܣ�2����ʼ��������

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
