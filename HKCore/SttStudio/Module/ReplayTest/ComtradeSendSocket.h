#ifndef _CComtradeSendSocket_h__
#define _CComtradeSendSocket_h__

#include "../Engine/SttTestEngineClientData.h"
#include "../RecordTest/SttRcdSocketBufferZip.h"

#define COMTRADE_SENDBUF_ZIP_LEN	20480000//压缩缓存大小

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

	//-1=无效，不发送；0=BufLoop；单数=BufA；双数=BufB
	int m_nCurrSendDataIndex; 
	BOOL m_bSendDataStartAck;
	BOOL *m_pbAnalysisFinish;//标记当前是否分析结束 zhouhj 2023.8.17 修改之前直接采用全局变量的方式

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
