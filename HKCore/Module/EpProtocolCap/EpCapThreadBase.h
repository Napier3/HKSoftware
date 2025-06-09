#pragma once


#include "CapCycleMemBufferMngr.h"
#include "..\ProtocolBase\ProtocolBase.h"
#include "EpFrameRecord.h"
#include "..\..\Module\CriticalSection\SynCriticalSection.h"

#include "EpCapDatasGenerator\EpCapGenDatas.h"
extern long g_EpCapDatasGeneratorMode;

#define WM_CAP_MONITOR  (WM_USER+1012)
#define WM_CAP_MONITORS  (WM_USER+1013)

extern long g_DEBUG_MONITOR_STATE;
//缓冲区记录了1M的数据，就开始写数据库
//#define SMDB_WRITE_SIZE_MIN   1048576
#define SMDB_WRITE_SIZE_MIN   20480

extern long g_nExitCaptrueState;
// #define _use_const_101_104


class CEpCapThreadBase : public CExBaseObject
{
public:
	CEpCapThreadBase(void);
	~CEpCapThreadBase(void);

	CEpCapGenDatas *m_pCapGenDatas;
	POS m_posCurrData;
	BOOL m_bViewThreadRunInfor;

	void CapGenDataThread(LONG nProtocol, EP_ETHER_CAP_IP_GROUP *pIpg=NULL);

protected:
	CWinThread *m_pCaptureThread;
	CWinThread *m_pParseThread;
	CCapCycleMemBufferMngr m_oCapCycleBufferMngr;
	CProtocolBase *m_pProtocol;  //关联的规约对象
	HWND m_hCapParseMonitor;   //cap监视窗口

	CEpFrameRecordMngr m_oRecordMngr;
	BOOL m_bShowFrameRecord;
	BOOL m_bUseParseThread;
	BOOL m_bCanFreeAllCapDatas;
	BOOL m_bCapData;

public:
	BOOL IsCapData()	{	return m_bCapData;	}
	void SetCapData(BOOL bCapData=TRUE)	{	m_bCapData = bCapData;	}
	BOOL GetShowFrameRecord()	{	return m_bShowFrameRecord;	}
	void SetShowFrameRecord(BOOL bShowFrameRecord)	{	m_bShowFrameRecord = bShowFrameRecord;	}
	CEpFrameRecordMngr* GetEpFrameRecordMngr()	{	return &m_oRecordMngr;	}
	void AttachCapMonitorWnd(HWND hWnd)	{	m_hCapParseMonitor = hWnd;	}
	HWND GetCapMonitorWnd()	{	return m_hCapParseMonitor;	}
	CCapCycleMemBufferMngr* GetCapCycleMemBufferMngr()	{	return &m_oCapCycleBufferMngr;	}
	void SetProtocol(CProtocolBase *pProtocol)	{	m_pProtocol = pProtocol;		}
	virtual void CreateCapture();
	virtual void ReleaseCapture();
	
	virtual void StopCapture();
	virtual void ResumeCapture();
	virtual BOOL HasAllCapThreadExit();
	virtual BOOL IsCaptureStarted();
	virtual BOOL IsCaptureStop()	{	return m_bStopCapture;	}
	virtual void WriteCap();
	virtual void FreeAllCapDatas();
	void SetCanFreeAllCapDatas()		{	m_bCanFreeAllCapDatas = TRUE;	}
//	void SetCapThreadCount(long nCount)	{	m_nEpCapThreadCount = nCount;	}

protected:
	virtual DWORD CreateCaptureThread() = 0;
	virtual void ExitCapture() = 0;

	virtual void FreeAllParsedBuffer();	
	//virtual void 	Parse();	
	virtual void 	ParseEx();	
	virtual void 	ParseEx(CCapCycleMemBuffer *pCapBuffer);	
	void RecordFrame(/*CExBaseObject *pFrame,*/ CCapCycleMemBuffer *pCycleBuffer, PEPBUFFERPOS pBuffPos);

protected:
	BOOL m_bStopCapture;
	BOOL m_bExitCapture;
};
