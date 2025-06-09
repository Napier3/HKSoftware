#ifndef _CSttRcdSendSocket_h__
#define _CSttRcdSendSocket_h__

#include "../SttSocket/SttSocketDataBase.h"
#include "RingMemBuf.h"
#include "SttRcdSocketBufferZip.h"

class CSttRcdSendSocket : public CWinTcpSocketClient
{
public:
   //记录发送、接受到的数据的长度
    static __int64  g_n64RcdSendSize;
    static __int64  g_n64RcdSendPrevSize;
    static __int64  g_n64RcdDrvRcvSize;
    static __int64  g_n64RcdDrvRcvPrevSize;

    static long CalRcdSendRate();
    static long CalRcdDrvRcvRate();

    //记录发送是否出现过很长时间没有发出去的情况
    static long g_nRcdSendOverTimeMax;
    static long g_nRcdSendOverTimeCount;

    static void ResetRcdSendOverTimeCount()
    {
        g_nRcdSendOverTimeMax = 0;
        g_nRcdSendOverTimeCount = 0;
    }

public:
	CSttRcdSendSocket();
    virtual ~CSttRcdSendSocket();
	
	void AttatchSocketDatabase(CSttSocketDataBase *pSttSocket);

public:
	virtual void OnClose(int nErrorCode);

protected:
	CSttSocketDataBase *m_pSttSocket;

public:
	char m_chSendBuf[RCD_BUFFER_MAX_LEN+10];
	char m_chSendBuf_Zip[OUT_RCD_BUFFER_MAX_LEN+10];
    __int64 m_n64ReadSizeTotal;
    long m_nRingBufReadPos; //数据读的起始位置
	BOOL m_bRunning;

	void InitRecordBuf();
	BOOL WriteRecordBuf(char *pSrcBuf,long nLen);
	long ReadRecordBuf();	

	long SttRcdSocketSend(BYTE *pBuffer, long nLen);

public:
	//开始录波创建线程，停止录波退出线程
	virtual BOOL CreateRcdSendThread();
	virtual void ExitRcdSendThread();

	void CheckRcdInfo();

#ifdef _PSX_QT_LINUX_
	pthread_t m_pSttRcdSendThread;
};
	void *SttRcdSendThread(LPVOID pParam);
#else
	HANDLE m_pSttRcdSendThread;
	static UINT SttRcdSendThread(LPVOID pParam);	
};
#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
extern CSttRcdSendSocket g_oSttRcdSendSocket;
extern pthread_mutex_t g_oSttRcdSendMutex;
#endif

#endif 
