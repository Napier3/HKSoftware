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

	//�ڴ�����
	return EmptyWorkingSet(hProcess);
}

BOOL mem_EmptySet_CurrApp()
{
// 	DWORD dwProcId=0;//��ŷ��صĽ���ID
// 	DWORD dwThreadId=0;//��ŷ��ص����߳�ID
// 	HWND hWnd=AfxGetMainWnd()->m_hWnd;//�����ڵľ��
// 	dwThreadId=GetWindowThreadProcessId(hWnd,&dwProcId);//ͬʱ�õ�����ID�����߳�ID.

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

	PROCESSENTRY32 ProcessInfo;//����������Ϣ����
	ProcessInfo.dwSize=sizeof(ProcessInfo);//����ProcessInfo�Ĵ�С
	int count = 0;

	//����ϵͳ�е�һ�����̵���Ϣ
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
	
		//��ȡ��һ�����̵���Ϣ
		Status=Process32Next(SnapShot,&ProcessInfo);
	}
	
	//cout << "total:" << count+1 << " processes"<<endl;
	//cout<<"end"<<endl;
	return TRUE;
}

