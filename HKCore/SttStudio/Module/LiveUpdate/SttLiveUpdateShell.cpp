
// SttLiveUpdateShell.cpp : ������Ϊ��
//

#include "stdafx.h"
#include "SttLiveUpdateShell.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"
#if _PSX_QT_LINUX_
#include"../../../Module/System/TickCount32.h"
#endif

#ifdef _PSX_IDE_QT_
#include <QCoreApplication>
#include <QProcess>
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSttLiveUpdateShell

CSttLiveUpdateShell::CSttLiveUpdateShell()
{
	
}

CSttLiveUpdateShell::~CSttLiveUpdateShell()
{
	Exit();
}

// CSttLiveUpdateShell

void CSttLiveUpdateShell::Init()
{
	CSttUpdateCfg::Create();
}

void CSttLiveUpdateShell::GetShellParas(int nLiveUpdateType,CString &strParas)
{
	strParas = _T("");

	if (nLiveUpdateType == LIVEUPDATE_LOCAL)
	{
		CString strParaPath;
		
#ifndef _PSX_IDE_QT_
		TCHAR strShortPath[MAX_PATH];
		GetModuleFileName(NULL,strShortPath,MAX_PATH);

		TCHAR strFullPath[MAX_PATH] = { 0 };  
		GetLongPathName( strShortPath, strFullPath, sizeof(strFullPath)/sizeof(TCHAR) );  
		strParaPath = strFullPath;
#else
		strParaPath = QCoreApplication::instance()->applicationFilePath();
#endif
		CString strPara1,strPara2,strPara3;
		strPara1 = CSttUpdateCfg::GetSysID().IsEmpty()?_T(" "):CSttUpdateCfg::GetSysID();
		strPara2 = CSttUpdateCfg::GetVerID().IsEmpty()?_T(" "):CSttUpdateCfg::GetVerID();
		strParaPath = strParaPath.IsEmpty()?_T(" "):strParaPath;
//		strParas.Format(_T("%s$%s$%d$"),strPara1.GetString(),strPara2.GetString(),CSttUpdateCfg::GetVerIdx());
		strParas += strPara1;
		strParas += _T("$");
		strParas += strPara2;
		strParas += _T("$");
		strPara3.Format(_T("%d"),CSttUpdateCfg::GetVerIdx());
		strParas += strPara3;
		strParas += _T("$");
		strParas += strParaPath;
	}
	else if(nLiveUpdateType == LIVEUPDATE_TESTAPP || nLiveUpdateType == LIVEUPDATE_MOBILE)
	{
		strParas = CSttUpdateCfg::GetTestAppID().IsEmpty()?_T(" "):CSttUpdateCfg::GetTestAppID();
	}
}

BOOL CSttLiveUpdateShell::GetLiveUpdatePath(CString &strPath)
{
#ifdef _PSX_QT_LINUX_
	strPath = _P_GetBinPath();
	strPath += STT_LIVEUPDATE_NAME;
#else
	strPath = _P_GetCommonBinPath();
	strPath += LOCAL_LIVEUPDATE_NAME;
#endif

	if (!IsFileExist(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ϵͳ����·����%s��û��LiveUpdate.exe,���²������"),_P_GetCommonBinPath());
		return FALSE;
	}

	return TRUE;
}

void CSttLiveUpdateShell::LocalUpdate()
{
	//ȡ������汾���µĲ���
	CString strParas;
	GetShellParas(LIVEUPDATE_LOCAL,strParas);

	//ȡ��LiveUpdate.exe·��
	CString strLiveUpdatePath;
	if(!GetLiveUpdatePath(strLiveUpdatePath))
	{
		return;
	}

#ifndef _PSX_IDE_QT_
	ShellExecute(NULL,_T("open"),strLiveUpdatePath, strParas, NULL, SW_SHOWNORMAL);
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
#else
	QProcess* pro = new QProcess;
	QStringList list;
	list.append(strParas);
	if (pro->startDetached(strLiveUpdatePath,list))
	{
		exit(0);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("LiveUpdate[%s]����ʧ��."),strLiveUpdatePath.GetString());
	}
#endif
}

bool CSttLiveUpdateShell::IsProcessExist()
{
#ifdef _PSX_IDE_QT_
	QProcess process;
	process.start("tasklist");
	process.waitForFinished();

	QByteArray result = process.readAllStandardOutput();
	QString str = result;

#ifdef _PSX_QT_LINUX_
	if(str.contains(STT_LIVEUPDATE_NAME))
#else
	if(str.contains(LOCAL_LIVEUPDATE_NAME))
#endif
		return true;
	
	return false;
#else
	return false;//��Qtģʽ��,��δʵ�ָú���
#endif
}

void CSttLiveUpdateShell::TestAppUpdate()
{
	//ȡ�ò����ǰ汾���µĲ���
	CString strParas;
	GetShellParas(LIVEUPDATE_TESTAPP,strParas);

	//ȡ��LiveUpdate.exe·��
	CString strLiveUpdatePath;
	if(!GetLiveUpdatePath(strLiveUpdatePath))
	{
		return;
	}

#ifndef _PSX_IDE_QT_
	ShellExecute(NULL,_T("open"),strLiveUpdatePath, strParas, NULL, SW_SHOWNORMAL);
	AfxGetMainWnd()->PostMessage(WM_CLOSE,0,0);
#else
 #ifdef _PSX_QT_LINUX_
    CTickCount32 oTickCount;
    CString strCmdText;
    strCmdText = GetPathFromFilePathName(strLiveUpdatePath);
    strCmdText += GetFileNameFromFilePath(strLiveUpdatePath);
    strCmdText += " ";
    strCmdText += strParas;//�������򲢴���
    strCmdText += " -qws &";
 //   CLogPrint::LogString(XLOGLEVEL_RESULT,strCmdText);
    system(strCmdText.GetString());
    oTickCount.DoEvents(20);
 #else
	QProcess* pProcess = new QProcess;
	QStringList list;
	list.append(strParas);

	if (pProcess->startDetached(strLiveUpdatePath,list))
	{
//		exit(0);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("LiveUpdate[%s]����ʧ��."),strLiveUpdatePath.GetString());
	}

	delete pProcess;
#endif
#endif
}

#ifdef _PSX_QT_LINUX_
void CSttLiveUpdateShell::TestAppUpdate_OffLine(const CString &strArgv)
{
	CTickCount32 oTickCount;

	CString strLiveUpdatePath,strCmdText;
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("LiveUpdate_OffLine[%s]����success."),strArgv.GetString());
	if(!GetLiveUpdatePath(strLiveUpdatePath))
	{
		return;
	}

	if (IsProcessExist())
	{
		strCmdText = "pkill -9 ";
		strCmdText += GetFileNameFromFilePath(strLiveUpdatePath);
		system(strCmdText.GetString());
		oTickCount.DoEvents(20);
	}

	strCmdText = strLiveUpdatePath;
	strCmdText += "  -qws";
	strCmdText += " ";
	strCmdText += strArgv;
	strCmdText += " ";
	system(strCmdText.GetString());
	oTickCount.DoEvents(20);
}
#endif

void CSttLiveUpdateShell::Exit()
{
	CSttUpdateCfg::Release();
}

CSttLiveUpdateShell theLiveUpdate;
