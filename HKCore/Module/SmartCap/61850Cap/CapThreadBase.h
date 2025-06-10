#pragma once


#include "ProtocolBase/Pcap/FrameMemBufferMngr.h"
#include "../../Smdb/XSmMemBufferMngr.h"
#include "ProtocolBase/ProtocolBase.h"
#include "../XSmartCapInterface.h"
// #include "ProtocolBase/PcapAnalysis/DoMessage.h"
// #include "ProtocolBase/PcapAnalysis/ToWork.h"



//��������¼��1M�����ݣ��Ϳ�ʼд���ݿ�
//#define SMDB_WRITE_SIZE_MIN   1048576
#define SMDB_WRITE_SIZE_MIN   20480

class CCapThreadBase : public CExBaseObject
{
public:
	CCapThreadBase(void);
	virtual ~CCapThreadBase(void);

public:
	CWinThread *m_pCaptureThread;   //����ץ���߳�
	CWinThread *m_pParseThread;      //���Ľ����߳�
	CXSmMemBufferMngr *m_pCapBufferMngr;
	CProtocolBase *m_pProtocol;  //�����Ĺ�Լ����
	//HWND m_hCapParseMonitor;   //cap���Ӵ���

	BOOL m_bShowFrameRecord;
	BOOL m_bUseParseThread;    //�Ƿ�ʹ�õ����Ľ����̣߳�����ģʽ�£����ȱ�֤ץ�����ĵĴ�������������������Ͳ���ȫ����
// 	BOOL m_bCanFreeAllCapDatas;
	BOOL m_bCapData;   //�Ƿ�ץ������

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



//ץ��������⺯��������ץ����صĲ���
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

	
//ץ���̵߳ı�־�����ڿ����̵߳�������ת
public:
	BOOL m_bStopCapture;
	BOOL m_bExitCapture;

public:
	CWinThread *GetCaptureThread() { return m_pCaptureThread; }
	void SetCaptureThread(CWinThread *pCaptureThread) { m_pCaptureThread = pCaptureThread; }
};
