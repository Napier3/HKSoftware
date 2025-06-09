// ../Module/Engine/CmmChannel/PpEngineThread.cpp : 实现文件
//

#include "stdafx.h"
#include "PpEngineThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPpEngineThread

CPpEngineThread::CPpEngineThread()
{
}

CPpEngineThread::~CPpEngineThread()
{
	
}

void CPpEngineThread::OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
    switch (nMsgID)
    {
    case WM_THREAD_RECEIVE:
        OnChannelReceive(wParam, lParam);
        break;

    case WM_THREAD_CONNECT:
        OnConnectDevice(wParam, lParam);
        break;

    case WM_THREAD_CONNECT_FINISHED:
        OnConnectDeviceFinished(wParam, lParam);
        break;

    case WM_THREAD_CONNECT_FAILED:
        OnConnectDeviceFailed(wParam, lParam);
        break;

    case WM_THREAD_DISCONNECT:
        OnDisConnectDevice(wParam, lParam);
        break;

    case WM_EXIT_ENGINE_THREAD:
        OnExitEngineThread(wParam, lParam);
        break;

    case WM_DELETE_ALL_RECORD_PACKAGE:
        OnDeleteAllRecordPackage(wParam, lParam);
        break;
    }

}
