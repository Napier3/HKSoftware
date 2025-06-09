// SysExeCpuUsage.h: interface for the CSysExeCpuUsage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SysExeCpuUsage_H__)
#define _SysExeCpuUsage_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSysExeCpuUsage  
{
public:  
	CSysExeCpuUsage(DWORD ProcessID) ;
	CSysExeCpuUsage();
	virtual ~CSysExeCpuUsage();

	HANDLE setpid(const CString &strExe);

	//返回值为进程句柄，可判断OpenProcess是否成功  
	HANDLE setpid(DWORD ProcessID);

	//-1 即为失败或进程已退出； 如果成功，首次调用会返回-2（中途用setpid更改了PID后首次调用也会返回-2）  
	float get_cpu_usage();    

private:  
	typedef long long          int64_t;  
	typedef unsigned long long uint64_t;  
	HANDLE m_hProcess;    
	int m_nNumProcessor;    //cpu数量    
	int64_t m_n64_last_time;         //上一次的时间    
	int64_t m_n64_last_system_time;    
	CString m_strExePath;

	// 时间转换    
	uint64_t file_time_2_utc(const FILETIME* ftime);  

	// 获得CPU的核数    
	int get_processor_number();  

	//初始化  
	void init()  ;

	//关闭进程句柄  
	void clear()  ;
};

#endif // !defined(_SysExeCpuUsage_H__)
