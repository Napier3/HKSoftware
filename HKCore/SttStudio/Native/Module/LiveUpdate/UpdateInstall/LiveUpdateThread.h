#pragma once

#include "../../../../Module/XmlRpc/XmlRpcClient.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"
#include "../../../../Module/FTP/XMiniFtpClient.h"
#include "../../../../Module/XmlRpc/XmlRpc.h"
#include "../../../../OA/Module/OA_DB/VersionMngr/Ats_Versions.h"

#define WM_UPDATEVERSION_START		WM_USER+3001
#define WM_UPDATEVERSION_END		WM_USER+3002

// CLiveUpdateThread

class CLiveUpdateThread : public CWinThread
{
	DECLARE_DYNCREATE(CLiveUpdateThread)

public:
	static CLiveUpdateThread* CreateThread(CThreadProgressInterface *pThreadProgressInterface,CWnd *pMsgRcvWnd)
	{
		CLiveUpdateThread* pThread = (CLiveUpdateThread*)AfxBeginThread(RUNTIME_CLASS(CLiveUpdateThread));
		pThread->m_pThreadProgressInterface = pThreadProgressInterface;
		pThread->m_pRecvWnd = pMsgRcvWnd;
		pThread->ResumeThread();
		pThread->PostThreadMessage(WM_UPDATEVERSION_START, 0, 0);
		return pThread;
	}

protected:
	CLiveUpdateThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CLiveUpdateThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	CThreadProgressInterface *m_pThreadProgressInterface;
	CWnd *m_pRecvWnd;
	BOOL m_bSuccess;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUpdateVersion(WPARAM wParam,LPARAM lParam);

};


