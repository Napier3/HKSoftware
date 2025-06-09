#pragma once


#include "ProtocolBase\FrameMemBufferMngr.h"
#include "ProtocolBase\ProtocolBase.h"



//��������¼��1M�����ݣ��Ϳ�ʼд���ݿ�
//#define SMDB_WRITE_SIZE_MIN   1048576
#define SMDB_WRITE_SIZE_MIN   20480


class CCapThreadBase : public CExBaseObject
{
public:
	CCapThreadBase(void);
	virtual ~CCapThreadBase(void);

protected:
	CWinThread *m_pCaptureThread;   //����ץ���߳�
	CWinThread *m_pParseThread;      //���Ľ����߳�
	CFrameMemBufferMngr m_oCapBufferMngr;   //ץ�����Ļ�����
	CProtocolBase *m_pProtocol;  //�����Ĺ�Լ����
	HWND m_hCapParseMonitor;   //cap���Ӵ���

	BOOL m_bShowFrameRecord;
	BOOL m_bUseParseThread;    //�Ƿ�ʹ�õ����Ľ����̣߳�����ģʽ�£����ȱ�֤ץ�����ĵĴ�������������������Ͳ���ȫ����
// 	BOOL m_bCanFreeAllCapDatas;
	BOOL m_bCapData;   //�Ƿ�ץ������

public:
	BOOL IsCapData()	{	return m_bCapData;	}
	void SetCapData(BOOL bCapData=TRUE)	{	m_bCapData = bCapData;	}
	BOOL GetShowFrameRecord()	{	return m_bShowFrameRecord;	}
	void SetShowFrameRecord(BOOL bShowFrameRecord)	{	m_bShowFrameRecord = bShowFrameRecord;	}
	void AttachCapMonitorWnd(HWND hWnd)	{	m_hCapParseMonitor = hWnd;	}
	HWND GetCapMonitorWnd()	{	return m_hCapParseMonitor;	}

	CFrameMemBufferMngr* GetCapMemBufferMngr()	{	return &m_oCapBufferMngr;	}
	void SetProtocol(CProtocolBase *pProtocol)	{	m_pProtocol = pProtocol;		}

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

protected:
	virtual DWORD CreateCaptureThread() = 0;
	virtual void ExitCapture() = 0;

	virtual void FreeAllParsedBuffer();	
	virtual void 	Parse(CFrameMemBuffer *pCapBuffer);	

//ץ���̵߳ı�־�����ڿ����̵߳�������ת
protected:
	BOOL m_bStopCapture;
	BOOL m_bExitCapture;
};
