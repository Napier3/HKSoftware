// GlobalApi.cpp
//
//////////////////////////////////////////////////////////////////////
#include "../GlobalApi.h"
#include "../FileApi.h"
#include<QProcess>

#ifndef _PSX_QT_LINUX_
#include <Tlhelp32.h>
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


bool ReadDataFromRegister(const CString &pszKey,const CString &pszValueName,CString &strData)
{
     return true;
}

bool WriteDataToRegister(LPCTSTR pszKey,LPCTSTR pszValueName,LPCSTR pszData)
{
     return true;
}

CString ReadDataFromRegister(const CString &strRoot,const CString &strRegKey)
{
    return _T("");
}

bool WriteDataToRegister(const CString &pszKey,const CString &pszValueName,const CString &pszData)
{
     return true;
}


BOOL IsProgramdExeFileSame(const CString &strExeFile, const CString &strProcessFile)
{
  return FALSE;
}

BOOL IsProgramExist(const CString &strProcessName)
{
	BOOL bExist = FALSE;
#ifndef _PSX_QT_LINUX_
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	//现在我们获得了所有进程的信息。
	//将从hSnapShot中抽取数据到一个PROCESSENTRY32结构中
	//这个结构代表了一个进程，是ToolHelp32 API的一部分。
	//抽取数据靠Process32First()和Process32Next()这两个函数。
	//这里我们仅用Process32Next()，他的原形是：
	//BOOL WINAPI Process32Next(HANDLE hSnapshot,LPPROCESSENTRY32 lppe);
	//我们程序的代码中加入：
	PROCESSENTRY32* processInfo=new PROCESSENTRY32;
	// 必须设置PROCESSENTRY32的dwSize成员的值 ;
	processInfo->dwSize=sizeof(PROCESSENTRY32);
	int index=0;
	//这里我们将快照句柄和PROCESSENTRY32结构传给Process32Next()。
	//执行之后，PROCESSENTRY32 结构将获得进程的信息。我们循环遍历，直到函数返回FALSE。
	//printf("****************开始列举进程****************/n");
	int ID = 0;
	char *pProcessName = NULL;
	CString_to_char(strProcessName, &pProcessName);

	while(Process32Next(hSnapShot,processInfo)!=FALSE)
	{
		index++;
		//printf("****************** %d ******************/n",index);
		//printf("PID       Name      Current Threads/n");
		//printf("%-15d%-25s%-4d/n",processInfo->th32ProcessID,processInfo->szExeFile,processInfo->cntThreads);
		int size=WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,NULL,0,NULL,NULL);
		char *ch=new char[size+1];
		if(WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,ch,size,NULL,NULL))
		{
			if(/*strstr(ch,pProcessName)*/strstr(strlwr(ch),strlwr(pProcessName)))
			{
				ID = processInfo->th32ProcessID;
				// qDebug()<<"ID ="<<ID;
				HANDLE hProcess;
				// 现在我们用函数 TerminateProcess()终止进程：
				// 这里我们用PROCESS_ALL_ACCESS
				hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,ID);
				//if(hProcess==NULL)
				//{
				//  printf("Unable to get handle of process: ");
				//  printf("Error is: %d",GetLastError());
				//}
				bExist = TRUE;
				break;
			}
		}
	}
	CloseHandle(hSnapShot);
	delete processInfo;
	delete pProcessName;

	return bExist;
#endif
}

BOOL TerminateProgram(const CString &strProcessName)
{
    BOOL bExist = FALSE;
#ifndef _PSX_QT_LINUX_
	HANDLE hSnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

	//现在我们获得了所有进程的信息。
	//将从hSnapShot中抽取数据到一个PROCESSENTRY32结构中
	//这个结构代表了一个进程，是ToolHelp32 API的一部分。
	//抽取数据靠Process32First()和Process32Next()这两个函数。
	//这里我们仅用Process32Next()，他的原形是：
	//BOOL WINAPI Process32Next(HANDLE hSnapshot,LPPROCESSENTRY32 lppe);
	//我们程序的代码中加入：
	PROCESSENTRY32* processInfo=new PROCESSENTRY32;
	// 必须设置PROCESSENTRY32的dwSize成员的值 ;
	processInfo->dwSize=sizeof(PROCESSENTRY32);
	int index=0;
	//这里我们将快照句柄和PROCESSENTRY32结构传给Process32Next()。
	//执行之后，PROCESSENTRY32 结构将获得进程的信息。我们循环遍历，直到函数返回FALSE。
	//printf("****************开始列举进程****************/n");
	int ID = 0;
	char *pProcessName = NULL;
	CString_to_char(strProcessName, &pProcessName);

	while(Process32Next(hSnapShot,processInfo)!=FALSE)
	{
		index++;
		//printf("****************** %d ******************/n",index);
		//printf("PID       Name      Current Threads/n");
		//printf("%-15d%-25s%-4d/n",processInfo->th32ProcessID,processInfo->szExeFile,processInfo->cntThreads);
		int size=WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,NULL,0,NULL,NULL);
		char *ch=new char[size+1];
		if(WideCharToMultiByte(CP_ACP,0,processInfo->szExeFile,-1,ch,size,NULL,NULL))
		{
			if(/*strstr(ch,pProcessName)*/strstr(strlwr(ch),strlwr(pProcessName)))
			{
				ID = processInfo->th32ProcessID;
				// qDebug()<<"ID ="<<ID;
				HANDLE hProcess;
				// 现在我们用函数 TerminateProcess()终止进程：
				// 这里我们用PROCESS_ALL_ACCESS
				hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,ID);
				//if(hProcess==NULL)
				//{
				//  printf("Unable to get handle of process: ");
				//  printf("Error is: %d",GetLastError());
				//}
				TerminateProcess(hProcess,0);
				CloseHandle(hProcess);
				bExist = TRUE;
			}
		}
	}
	CloseHandle(hSnapShot);
	delete processInfo;
	delete pProcessName;

    return bExist;
#endif
}

BOOL IsCurrTickCountTimeOut(DWORD dwBeginTick, DWORD dwTickLong)
{
    DWORD dwCurrTick = GetTickCount();
    long nTimer = dwCurrTick - dwBeginTick;

    if (nTimer > dwTickLong)
    {
        return TRUE;
    }
    else
    {
        if (nTimer < 0)
        {
            DWORD dwLeft = 0xFFFFFFFF - dwBeginTick;
            nTimer = dwLeft + dwCurrTick;
            return (nTimer > dwTickLong);
        }
        else
        {
            return FALSE;
        }
    }
}

unsigned long GetProcID(const CString &strExeFileName)
{
    return 0;
}

void ActiveProcMainWnd(const CString &strExeFileName)
{
 
}

HWND GetProcMainWndByPid(DWORD dwProcessID, CString &strTitle)
{
    HWND hWndFind = NULL;

    return hWndFind;
}

BOOL KillProc(const CString &pn)
{
    return 0;
}

BOOL ExecuteFile(const CString &strExePath, const CString &strCmdLine, const CString &strMode)
{
	QStringList strList;
	strList << strCmdLine;

	QProcess process;
	return process.startDetached(strExePath, strList);
}

void UI_ExpandAllChildren(CTreeCtrl *pTree, HTREEITEM hCurr)
{
/*
    HTREEITEM hChild = pTree->GetChildItem(hCurr);

    while (hChild != NULL)
    {
        UI_ExpandAllChildren(pTree, hChild);
        pTree->Expand(hChild, TVE_EXPAND);
        hChild = pTree->GetNextSiblingItem(hChild);
    }

    pTree->Expand(hCurr, TVE_EXPAND);
*/
}

void UI_BringWndToTop(HWND hWnd)
{
/*    ::ShowWindow(hWnd, SW_SHOW);
    ::SetWindowPos(hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
    ::BringWindowToTop(hWnd);
    ::SetActiveWindow(hWnd);
    ::SetWindowPos(hWnd,HWND_NOTOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
*/
}

void UI_BringWndToTop(CWnd *pWnd)
{
/*
    pWnd->ShowWindow(SW_SHOW);
    ::SetWindowPos(pWnd->m_hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
    pWnd->BringWindowToTop();
    //pWnd->FlashWindowEx(FLASHW_ALL, 4, 500);
    pWnd->SetActiveWindow();
    ::SetWindowPos(pWnd->m_hWnd,HWND_NOTOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
*/
}

void GetProgramCompileTime(SYSTEMTIME &st)
{
/*
        TCHAR szDate[20];
        ZeroMemory(szDate, sizeof(szDate));
        ZeroMemory(&st, sizeof(SYSTEMTIME));
#ifdef UNICODE
        _vsntprintf(szDate, sizeof(szDate), TEXT("%s"), __TIME__);
#else
        _stprintf(szDate, TEXT("%s"), __DATE__);
#endif

        st.wYear = (WORD)_tcstoul(szDate+7, 0, 10);

        st.wDay = szDate[5] - TEXT('0');
        if (szDate[4] != TEXT(' '))
        {
                st.wDay += (szDate[4] - TEXT('0')) * 10;
        }

        switch(szDate[0])
        {
        case TEXT('A'):
                if (szDate[1] == TEXT('p'))
                {
                        st.wMonth = 4;
                }
                else
                {
                        st.wMonth = 8;
                }
                break;

        case TEXT('D'):
                st.wMonth = 12;
                break;

        case TEXT('F'):
                st.wMonth = 2;
                break;

        case TEXT('J'):
                if (szDate[1] == TEXT('a'))
                {
                        st.wMonth = 1;
                }
                else
                {
                        if (szDate[2] == TEXT('n'))
                        {
                                st.wMonth = 6;
                        }
                        else
                        {
                                st.wMonth = 7;
                        }
                }
                break;

        case TEXT('M'):
                if (szDate[2] == TEXT('r'))
                {
                        st.wMonth = 3;
                }
                else
                {
                        st.wMonth = 5;
                }
                break;

        case TEXT('N'):
                st.wMonth = 11;
                break;

        case TEXT('O'):
                st.wMonth = 10;
                break;

        case TEXT('S'):
                st.wMonth = 9;
                break;
        }

        ZeroMemory(szDate, sizeof(szDate));

#ifdef UNICODE
        _vsntprintf(szDate, sizeof(szDate), TEXT("%s"), __TIME__);
#else
        sprintf(szDate, TEXT("%s"), __TIME__);
#endif


        st.wHour = (szDate[0] -TEXT('0')) * 10 + (szDate[1] - TEXT('0'));
        st.wMinute  = (szDate[3] -TEXT('0')) * 10 + (szDate[4] - TEXT('0'));
        st.wSecond  = (szDate[6] -TEXT('0')) * 10 + (szDate[7] - TEXT('0'));
      */
        return;
}
