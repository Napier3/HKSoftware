// ../Module/Engine/CmmChannel/PpEngineThread.cpp : 实现文件
//

#include "stdafx.h"
#include "PpEngineThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPpEngineThread

IMPLEMENT_DYNCREATE(CPpEngineThread, CWinThread)

CPpEngineThread::CPpEngineThread()
{
	
}

CPpEngineThread::~CPpEngineThread()
{
	
}

BEGIN_MESSAGE_MAP(CPpEngineThread, CWinThread)
	ON_THREAD_MESSAGE(WM_THREAD_RECEIVE, &CPpEngineThread::OnChannelReceive)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT, &CPpEngineThread::OnConnectDevice)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT_FINISHED, &CPpEngineThread::OnConnectDeviceFinished)
	ON_THREAD_MESSAGE(WM_THREAD_CONNECT_FAILED, &CPpEngineThread::OnConnectDeviceFailed)
	ON_THREAD_MESSAGE(WM_THREAD_DISCONNECT, &CPpEngineThread::OnDisConnectDevice)
	ON_THREAD_MESSAGE(WM_EXIT_ENGINE_THREAD, &CPpEngineThread::OnExitEngineThread)
	ON_THREAD_MESSAGE(WM_DELETE_ALL_RECORD_PACKAGE, &CPpEngineThread::OnDeleteAllRecordPackage)
END_MESSAGE_MAP()
