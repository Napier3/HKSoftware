#ifndef _CComtradeSendSocket_h__
#define _CComtradeSendSocket_h__

#include "../Engine/SttTestEngineClientData.h"
#include "../RecordTest/SttRcdSocketBufferZip.h"

#define COMTRADE_SENDBUF_ZIP_LEN	20480000//ѹ�������С

class CComtradeSendSocket : public CWinTcpSocketClient
{
public:
	CComtradeSendSocket();
	virtual ~CComtradeSendSocket();

public:
	virtual void OnClose(int nErrorCode);

//protected:
	CSttTestEngineClientData *m_pClientEngineRef; 
	CSttSocketDataBase *m_pSttSocket;

	//-1=��Ч�������ͣ�0=BufLoop������=BufA��˫��=BufB
	int m_nCurrSendDataIndex; 
	BOOL m_bSendDataStartAck;
	BOOL *m_pbAnalysisFinish;//��ǵ�ǰ�Ƿ�������� zhouhj 2023.8.17 �޸�֮ǰֱ�Ӳ���ȫ�ֱ����ķ�ʽ

	char m_chSendBuf_Zip[COMTRADE_SENDBUF_ZIP_LEN+100];
	long SttRcdSocketSend(BYTE *pBuffer, long nLen,long nIndex);

	void WaitForThreadExit();
public:
	void AttatchSocketDatabase(CSttSocketDataBase *pSttSocket);
	void AttatchClientTestEngine(CSttTestEngineClientData *pEngine);
	void SetCurrSendDataIndex(int nIndex)	{	m_nCurrSendDataIndex = nIndex;	}
	void SetSendDataStartAck()	{	m_bSendDataStartAck = TRUE;	}


#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttComtradeSendThread;
};
void *SttComtradeSendThread(LPVOID pParam);
#else
	HANDLE m_pSttComtradeSendThread;
	static UINT SttComtradeSendThread(LPVOID pParam);	
};
#endif


#endif 
