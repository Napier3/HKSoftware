#include "stdafx.h"
#include "MemClean.h"

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>

#pragma comment (lib,"psapi.lib")

void mem_AdjustTokenPrivilegesForNT()
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;

	// Get a token for this process.
	OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	// Get the LUID for the EmptyWorkingSet privilege.
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkp.Privileges[0].Luid);

	tkp.PrivilegeCount = 1; // one privilege to set
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	// Get the EmptyWorkingSet privilege for this process.
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
}

BOOL mem_EmptySet(HANDLE hProcess)
{
	SetProcessWorkingSetSize(hProcess,-1,-1);

	//内存整理
	return EmptyWorkingSet(hProcess);
}

BOOL mem_EmptySet_CurrApp()
{
// 	DWORD dwProcId=0;//存放返回的进程ID
// 	DWORD dwThreadId=0;//存放返回的主线程ID
// 	HWND hWnd=AfxGetMainWnd()->m_hWnd;//主窗口的句柄
// 	dwThreadId=GetWindowThreadProcessId(hWnd,&dwProcId);//同时得到进程ID和主线程ID.

	HANDLE hProcess = GetModuleHandle(NULL);

	return mem_EmptySet(hProcess);
}

BOOL mem_EmptyAllSet()
{
	HANDLE SnapShot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if(SnapShot==NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("snapshot==null"));
		return FALSE;
	}

	PROCESSENTRY32 ProcessInfo;//声明进程信息变量
	ProcessInfo.dwSize=sizeof(ProcessInfo);//设置ProcessInfo的大小
	int count = 0;

	//返回系统中第一个进程的信息
	BOOL Status=Process32First(SnapShot, &ProcessInfo);
	//cout<<"status="<<Status<<endl;

	while(Status)
	{
		//cout<<"processID="<<ProcessInfo.th32ProcessID<<endl;
		count ++;
		HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,TRUE,
			ProcessInfo.th32ProcessID);

		if(hProcess)
		{
			//cout<<"begin clean Memory"<<endl;
			mem_EmptySet(hProcess);
			CloseHandle(hProcess);
		}
	
		//获取下一个进程的信息
		Status=Process32Next(SnapShot,&ProcessInfo);
	}
	
	//cout << "total:" << count+1 << " processes"<<endl;
	//cout<<"end"<<endl;
	return TRUE;
}

