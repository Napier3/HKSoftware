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

	//����ֵΪ���̾�������ж�OpenProcess�Ƿ�ɹ�  
	HANDLE setpid(DWORD ProcessID);

	//-1 ��Ϊʧ�ܻ�������˳��� ����ɹ����״ε��û᷵��-2����;��setpid������PID���״ε���Ҳ�᷵��-2��  
	float get_cpu_usage();    

private:  
	typedef long long          int64_t;  
	typedef unsigned long long uint64_t;  
	HANDLE m_hProcess;    
	int m_nNumProcessor;    //cpu����    
	int64_t m_n64_last_time;         //��һ�ε�ʱ��    
	int64_t m_n64_last_system_time;    
	CString m_strExePath;

	// ʱ��ת��    
	uint64_t file_time_2_utc(const FILETIME* ftime);  

	// ���CPU�ĺ���    
	int get_processor_number();  

	//��ʼ��  
	void init()  ;

	//�رս��̾��  
	void clear()  ;
};

#endif // !defined(_SysExeCpuUsage_H__)
