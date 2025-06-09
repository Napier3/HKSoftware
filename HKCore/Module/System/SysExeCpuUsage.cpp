// SysExeCpuUsage.cpp: implementation of the CSysExeCpuUsage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysExeCpuUsage.h"

#include "..\API\GlobalApi.h"
#include <tlhelp32.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSysExeCpuUsage::CSysExeCpuUsage() 
{ 
	init(); 
	m_nNumProcessor = get_processor_number(); 
}  

CSysExeCpuUsage::CSysExeCpuUsage(DWORD ProcessID)
{   
	init();   
	m_nNumProcessor = get_processor_number();  
	setpid(ProcessID);  
}  

CSysExeCpuUsage::~CSysExeCpuUsage()
{
	clear(); 
} 

void CSysExeCpuUsage::clear()  
{  
	if (m_hProcess)
	{  
		CloseHandle(m_hProcess);  
		m_hProcess = 0;  
	}  
}  

void CSysExeCpuUsage::init()  
{  
	m_n64_last_system_time = 0;  
	m_n64_last_time = 0;  
	m_hProcess = 0;  
}  

HANDLE CSysExeCpuUsage::setpid(DWORD ProcessID)
{  
	//如果之前监视过另一个进程，就先关闭它的句柄
	clear();
	init();   
	m_hProcess = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ProcessID);   

	return m_hProcess;
}  

HANDLE CSysExeCpuUsage::setpid(const CString &strExe)
{
	if (m_strExePath == strExe)
	{
		return m_hProcess;
	}

	m_strExePath = strExe;
	BOOL bExist = FALSE;
	HANDLE snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0) ;
	if(snapshot == NULL)
		return NULL;

	CString strTemp = strExe;
	strTemp.MakeLower();

	m_hProcess = NULL;
	SHFILEINFO shSmall;
	CString str;
	PROCESSENTRY32 processinfo ;
	processinfo.dwSize=sizeof(processinfo) ;
	BOOL status=Process32First(snapshot,&processinfo) ;
	while (status)
	{
		ZeroMemory(&shSmall, sizeof(shSmall));		
		str = processinfo.szExeFile;
		str.MakeLower();

		if (IsProgramdExeFileSame(strTemp, str))
		{
			m_hProcess = OpenProcess(PROCESS_ALL_ACCESS,FALSE,processinfo.th32ProcessID);
			break;
		}

		status = Process32Next (snapshot, &processinfo) ;
	}	

	CloseHandle(snapshot);

	return m_hProcess;	
}

float CSysExeCpuUsage::get_cpu_usage()  
{  
	FILETIME now;  
	FILETIME creation_time;  
	FILETIME exit_time;  
	FILETIME kernel_time;  
	FILETIME user_time;  
	int64_t system_time;  
	int64_t time;  
	int64_t system_time_delta;  
	int64_t time_delta;  

	DWORD exitcode;  

	float cpu = -1;  

	if (!m_hProcess) return -1;  

	GetSystemTimeAsFileTime(&now);  

	//判断进程是否已经退出  
	GetExitCodeProcess(m_hProcess, &exitcode);    
	if (exitcode != STILL_ACTIVE) {  
		clear();  
		return -1;  
	}  

	//计算占用CPU的百分比  
	if (!GetProcessTimes(m_hProcess, &creation_time, &exit_time, &kernel_time, &user_time))  
	{  
		clear();  
		return -1;  
	}  

	system_time = (file_time_2_utc(&kernel_time) + file_time_2_utc(&user_time))  
		/ m_nNumProcessor;  
	time = file_time_2_utc(&now);  

	//判断是否为首次计算  
	if ((m_n64_last_system_time == 0) || (m_n64_last_time == 0))  
	{  
		m_n64_last_system_time = system_time;  
		m_n64_last_time = time;  
		return -2;  
	}  

	system_time_delta = system_time - m_n64_last_system_time;  
	time_delta = time - m_n64_last_time;  

	if (time_delta == 0) {  
		return -1;  
	}  

	cpu = (float)system_time_delta * 100 / (float)time_delta;  
	m_n64_last_system_time = system_time;  
	m_n64_last_time = time;  

	return cpu;  
}  

CSysExeCpuUsage::uint64_t CSysExeCpuUsage::file_time_2_utc(const FILETIME* ftime)  
{  
	LARGE_INTEGER li;  

	li.LowPart = ftime->dwLowDateTime;  
	li.HighPart = ftime->dwHighDateTime;  

	return li.QuadPart;  
}  

int CSysExeCpuUsage::get_processor_number()  
{  
	SYSTEM_INFO info;  
	GetSystemInfo(&info);  
	return info.dwNumberOfProcessors;  
}  
