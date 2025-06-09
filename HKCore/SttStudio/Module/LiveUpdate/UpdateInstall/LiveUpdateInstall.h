#pragma once

#include <vector>

struct ProInfo
{
	// �������PID
	unsigned int m_uPID;
	// ���������
	CString m_strPrceName;
	// �������·��
	CString m_strFullPath;
	// ����ý��̵���dll����·��
	std::vector<CString> m_strDLLNameArr;
};

class CProcessInfo
{
private:
	// ���������Ȩ��
	BOOL EnableDebugPrivilege(BOOL fEnable);

	// ���������
	std::vector<ProInfo> m_vctPrceInfo;

public:
	std::vector<ProInfo>::iterator GetBeginPrceInfo(){return m_vctPrceInfo.begin();}
	std::vector<ProInfo>::iterator GetEndPrceInfo(){return m_vctPrceInfo.end();}

	CProcessInfo();
	~CProcessInfo();

	// ��ȡ������
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