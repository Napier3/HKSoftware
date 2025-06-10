// CLiveUpdateThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LiveUpdateThread.h"
#include "../LiveUpdateBaseApp.h"

// CLiveUpdateThread

IMPLEMENT_DYNCREATE(CLiveUpdateThread, CWinThread)

CLiveUpdateThread::CLiveUpdateThread()
{
	m_pThreadProgressInterface = NULL;
	m_pRecvWnd = NULL;
}

CLiveUpdateThread::~CLiveUpdateThread()
{
}

BOOL CLiveUpdateThread::InitInstance()
{
	AfxOleInit();
	AfxSocketInit();

	g_theLiveUpdateBaseApp->ResetUpdate();

	return TRUE;
}

int CLiveUpdateThread::ExitInstance()
{
	m_pRecvWnd->PostMessage(WM_UPDATEVERSION_END,0,(LPARAM)m_bSuccess);
	
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CLiveUpdateThread, CWinThread)
	ON_THREAD_MESSAGE(WM_UPDATEVERSION_START, OnUpdateVersion)
END_MESSAGE_MAP()


// CLiveUpdateThread ��Ϣ�������

//////////////////////////////////////////////////////////////////////////

void CLiveUpdateThread::OnUpdateVersion(WPARAM wParam,LPARAM lParam)
{
	CString strUpdateInfo;
	CString strSvrZipFile;
	CString strTemp;
	m_bSuccess = FALSE;

	strUpdateInfo = _T("��ʼ��ѯ�汾������Ϣ...");
	m_pThreadProgressInterface->ShowMsg(strUpdateInfo);

	m_pThreadProgressInterface->StepIt();

	if (g_theLiveUpdateBaseApp->m_bStopFlag)
	{
		goto ExitUpdate;
	}

	if(!g_theLiveUpdateBaseApp->VerUpdateRpc_BeginUpdate( g_theLiveUpdateBaseApp->m_pVerUpdateHisVer->m_nPrevVerIdx
		, g_theLiveUpdateBaseApp->m_pVerUpdateHisVer->m_nCurrVerIdx
		, g_theLiveUpdateBaseApp->m_pAts_System->m_nIndex_System, strSvrZipFile))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("��ѯ�汾������Ϣʧ�ܣ�"));
		goto ExitUpdate;
	}
	
	m_pThreadProgressInterface->StepIt();

	if (g_theLiveUpdateBaseApp->m_bStopFlag)
	{
		goto ExitUpdate;
	}

	strUpdateInfo = _T("��ʼ���ذ汾�����ļ�...");
	m_pThreadProgressInterface->ShowMsg(strUpdateInfo);

	if (g_theLiveUpdateBaseApp->m_bUpdateToPath && !g_theLiveUpdateBaseApp->m_strUpdateToPath.IsEmpty())
	{
		strTemp = g_theLiveUpdateBaseApp->m_strUpdateToPath;
	}
	else
	{
		strTemp = g_theLiveUpdateBaseApp->m_pAts_System->m_strVerPath;
	}

	if(!g_theLiveUpdateBaseApp->DownloadSvrZipFile(strSvrZipFile,strTemp))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("��Զ�̷��������ظ����ļ�ʧ�ܣ�"));
		goto ExitUpdate;
	}

	//���汾�����ص��ļ�·��
	g_theLiveUpdateBaseApp->m_strLocalZipFile = strTemp;
	g_theLiveUpdateBaseApp->m_strLocalZipFile += GetFileNameFromFilePath(strSvrZipFile);
	
	m_pThreadProgressInterface->StepIt();

	strUpdateInfo = _T("������ذ汾�����ļ�");
	m_pThreadProgressInterface->ShowMsg(strUpdateInfo);

	if (g_theLiveUpdateBaseApp->m_bStopFlag)
	{
		goto ExitUpdate;
	}

	if(!g_theLiveUpdateBaseApp->VerUpdateRpc_FinishUpdate(g_theLiveUpdateBaseApp->m_pVerUpdateHisVer->m_nPrevVerIdx
		, g_theLiveUpdateBaseApp->m_pVerUpdateHisVer->m_nCurrVerIdx
		, g_theLiveUpdateBaseApp->m_pAts_System->m_nIndex_System))
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("��Զ�̷��������ظ����ļ�ʧ�ܣ�"));
		goto ExitUpdate;
	}

	m_pThreadProgressInterface->StepIt();
	m_bSuccess = TRUE;

ExitUpdate:
	while (!PostThreadMessage(WM_QUIT,0,0))
	{
		Sleep(500);
	}
}

