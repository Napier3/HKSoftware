#pragma once

#include <vector>

struct ProInfo
{
	// 保存进程PID
	unsigned int m_uPID;
	// 保存进程名
	CString m_strPrceName;
	// 保存进程路径
	CString m_strFullPath;
	// 保存该进程调用dll名和路径
	std::vector<CString> m_strDLLNameArr;
};

class CProcessInfo
{
private:
	// 这个用于提权的
	BOOL EnableDebugPrivilege(BOOL fEnable);

	// 保存进程名
	std::vector<ProInfo> m_vctPrceInfo;

public:
	std::vector<ProInfo>::iterator GetBeginPrceInfo(){return m_vctPrceInfo.begin();}
	std::vector<ProInfo>::iterator GetEndPrceInfo(){return m_vctPrceInfo.end();}

	CProcessInfo();
	~CProcessInfo();

	// 获取进程名
	void GetProcessName (void);
};

#ifndef _PSX_IDE_QT_
class CLocalProgress : public CExBaseObject
{
public:
	CLocalProgress()
	{
		m_nPID = 0;
		m_strName = _T("");
		m_strPath = _T("");
		m_hProcess = INVALID_HANDLE_VALUE;
		m_bSelf = FALSE;
	};
	~CLocalProgress(){};

public:
	long	m_nPID;
	CString m_strName;
	CString m_strPath;
	HANDLE  m_hProcess;
	BOOL	m_bSelf;
};

class CLocalProgresses : public CExBaseList
{
public:
	CLocalProgresses(){};
	~CLocalProgresses(){};
};

void GetProcessFilePath(IN HANDLE hProcess, OUT CString& strFilePath);
BOOL FindExeDllProcess(const CStringArray &strProcessPaths,CLocalProgresses* pLocalProgresses);
void TerminateProcess(CLocalProgresses& oLocalProgresses);
#endif