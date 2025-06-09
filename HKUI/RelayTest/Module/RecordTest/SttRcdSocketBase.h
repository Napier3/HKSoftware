#ifndef _CSttRcdSeverClientSocket_h__
#define _CSttRcdSeverClientSocket_h__

#include "../SttSocket/SttSocketDataBase.h"
#include "SttRcdSocketBufferZip.h"

#include "SttRcdBufferRcvMsg.h"

class CSttRcdSocketBase : public CWinTcpSocketClient
{
public:
	CSttRcdSocketBase();
    virtual ~CSttRcdSocketBase();
	
	void AttatchSocketDatabase(CSttSocketDataBase *pSttSocket);
	void AttatchRcdBufRcvMsg(CSttRcdBufferRcvMsg *p)	{	m_pSttRcdBufferRcvMsg = p;	}
	CSttRcdBufferRcvMsg* GetRcdBufRcvMsg()	{	return m_pSttRcdBufferRcvMsg;	}
	//void SetRcdRcvBuffMaxLen(long nLen);

	void SttRcdSocketClose();
public:
	virtual void OnClose(int nErrorCode);
	virtual long OnReceive(BYTE *pRcvBuf, int iLen);
	virtual void OnSocketIdle(long nMs);

	virtual long OnReceive_Zip(BYTE *pRcvBuf, int iLen);

protected:
	long m_nCurrRcdRcvLen;
	BYTE  m_pRcdRcvBuff[OUT_RCD_BUFFER_MAX_LEN*2];
	BYTE  m_pRcdRcvBuff_Uzip[OUT_RCD_BUFFER_MAX_LEN];
	long m_nRcdBuffMaxLen;
	long m_nSocketIdleLong;
	CSttRcdBufferRcvMsg *m_pSttRcdBufferRcvMsg;

	CSttSocketDataBase *m_pSttSocket;

	void FireRcdBufRcvMsg();
	long FireRcdBufRcvMsg_Zip(BYTE *pBuff);
	CTickCount32 m_oSendTickCount;

public:
	CWinThread *m_pSttRcdRecvThread;
	BOOL m_bRcdSocketClosing;//20220622 zhouhj 增加用于退出录波线程

public:
	static __int64 m_n64RecvTotalSize;
	static __int64 m_n64RecvPrevSize;
	static CString m_strWriteFilePath;

	static long CalRecvSizeRate();

public:
	static void CreateAt02dRcdFileWrite(const CString &strFile);
	static void CloseAt02dRcdFileWrite();
	static bool IsWriteAt02dRcdFileWrite();

protected:
	static FILE *m_pWriteAt02dRcdFile;

};

// #ifdef _PSX_QT_LINUX_//20220621 zhouhj 返回值改为与window下保持一致方式
// UINT SttRcdRecvThread(LPVOID pParam);
// #else 
UINT SttRcdRecvThread(LPVOID pParam);
//#endif


#endif // _CSttRcdSeverClientSocket_h__
