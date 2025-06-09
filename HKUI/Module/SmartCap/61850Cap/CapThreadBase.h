#pragma once


#include "ProtocolBase/PCAP/FrameMemBufferMngr.h"
#include "../../SmDb/XSmMemBufferMngr.h"
#include "ProtocolBase/ProtocolBase.h"
#include "../XSmartCapInterface.h"
// #include "ProtocolBase/PcapAnalysis/DoMessage.h"
// #include "ProtocolBase/PcapAnalysis/ToWork.h"



//缓冲区记录了1M的数据，就开始写数据库
//#define SMDB_WRITE_SIZE_MIN   1048576
#define SMDB_WRITE_SIZE_MIN   20480

class CCapThreadBase : public CExBaseObject
{
public:
	CCapThreadBase(void);
	virtual ~CCapThreadBase(void);

public:
	CWinThread *m_pCaptureThread;   //报文抓包线程
	CWinThread *m_pParseThread;      //报文解析线程
	CXSmMemBufferMngr *m_pCapBufferMngr;
	CProtocolBase *m_pProtocol;  //关联的规约对象
	//HWND m_hCapParseMonitor;   //cap监视窗口

	BOOL m_bShowFrameRecord;
	BOOL m_bUseParseThread;    //是否使用单独的解析线程，此种模式下，优先保证抓包报文的处理，如果解析来不及，就不完全解析
// 	BOOL m_bCanFreeAllCapDatas;
	BOOL m_bCapData;   //是否抓包数据

	//CToWork    * m_pToWork;

public:
	BOOL IsCapData()	{	return m_bCapData;	}
	void SetCapData(BOOL bCapData=TRUE)	{	m_bCapData = bCapData;	}
	BOOL GetShowFrameRecord()	{	return m_bShowFrameRecord;	}
	void SetShowFrameRecord(BOOL bShowFrameRecord)	{	m_bShowFrameRecord = bShowFrameRecord;	}
	//void AttachCapMonitorWnd(HWND hWnd)	{	m_hCapParseMonitor = hWnd;	}
	//HWND GetCapMonitorWnd()	{	return m_hCapParseMonitor;	}

	CXSmMemBufferMngr* GetCapMemBufferMngr()	{	return m_pCapBufferMngr;	}
	void SetProtocol(CProtocolBase *pProtocol)	{	m_pProtocol = pProtocol;		}

	void SetCapMemBufferMngr(CXSmMemBufferMngr* pCapMemBufferMngr)	{	m_pCapBufferMngr = pCapMemBufferMngr;	}



//抓包相关虚拟函数，抽象抓包相关的操作
public:
	virtual void CreateCapture();
	virtual void ReleaseCapture();
	
	virtual void StopCapture();
	virtual void ResumeCapture();
	virtual BOOL HasAllCapThreadExit();
	virtual BOOL IsCaptureStarted();
	virtual BOOL IsCaptureStop()	{	return m_bStopCapture;	}
	virtual void WriteCap();
	virtual void FreeAllCapDatas();
// 	void SetCanFreeAllCapDatas()		{	m_bCanFreeAllCapDatas = TRUE;	}

public:
	virtual DWORD CreateCaptureThread() = 0;
	virtual void ExitCapture() = 0;

	virtual void FreeAllParsedBuffer();	
	virtual void Parse(CFrameMemBuffer *pCapBuffer);	
	virtual long MemBufferMngrParse();

	
//抓包线程的标志，用于控制线程的流程跳转
public:
	BOOL m_bStopCapture;
	BOOL m_bExitCapture;

public:
	CWinThread *GetCaptureThread() { return m_pCaptureThread; }
	void SetCaptureThread(CWinThread *pCaptureThread) { m_pCaptureThread = pCaptureThread; }
};
