
#include "stdafx.h"
#include"tlhelp32.h"
#include "StrSafe.h"
#include "LiveUpdateInstall.h"
#include "../../../../Module/API/FileApi.h"

#include "Psapi.h"
#pragma comment(lib, "psapi.lib")

CProcessInfo::CProcessInfo()
{
}

CProcessInfo::~CProcessInfo()
{
}

BOOL CProcessInfo::EnableDebugPrivilege(BOOL fEnable)
{  
	BOOL fOk = FALSE;   
	HANDLE hToken;

	// �õ����̵ķ�������
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,&hToken))
	{    
		TOKEN_PRIVILEGES tp;
		tp.PrivilegeCount = 1;
		// �鿴ϵͳ��Ȩֵ������һ��LUID�ṹ�� 
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
		// ����/�ر� ��Ȩ
		AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
		fOk = (GetLastError() == ERROR_SUCCESS);
		CloseHandle(hToken);
	}
	else
	{
		return 0;
	}
	return(fOk);
}

void CProcessInfo::GetProcessName (void)
{
	HANDLE hProcessSnap = NULL;
	HANDLE hProcessDll = NULL;
	BOOL bRet = FALSE; 
	// ��ʼ��dwSizeΪ0����ȻProcess32Firstִ��ʧ��
	PROCESSENTRY32 pe32 = {0};
	MODULEENTRY32 me32;
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dwError;
	ProInfo proinfo;
	LPCTSTR pszFormat = TEXT("��ʼ����ʱ��������! %s");

	// ����һ�����̿���
	if(!EnableDebugPrivilege(1))
	{
		MessageBox(NULL, _T("��Ȩʧ�ܣ�"), _T("��ʾ"), MB_OK|MB_ICONEXCLAMATION);
	}

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		dwError = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER|
			FORMAT_MESSAGE_FROM_SYSTEM|
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			LPTSTR(&lpMsgBuf),
			0,
			NULL);

		lpDisplayBuf = (LPVOID)LocalAlloc(
			LMEM_ZEROINIT,
			(lstrlen((LPCTSTR)lpMsgBuf)+lstrlen(pszFormat))*sizeof(TCHAR));

		// ��ʽ���ַ���
		StringCchPrintf(
			(LPTSTR)lpDisplayBuf,
			LocalSize(lpDisplayBuf),            // �ֽ���
			pszFormat,
			lpMsgBuf);

		CString strTemp;
		strTemp.Format(TEXT("�������Ϊ:%d"), dwError);
		::MessageBox(NULL, (LPCTSTR)lpDisplayBuf, strTemp, MB_OK|MB_ICONEXCLAMATION);
		// ���������ڴ�
		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);

		return;
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);

	Module32First(hProcessSnap, &me32);

	if (Process32First(hProcessSnap, &pe32)) 
	{ 
		do 
		{     
			char path[MAX_PATH]={0};

			proinfo.m_uPID = pe32.th32ProcessID;
			proinfo.m_strPrceName = pe32.szExeFile;

			HMODULE hModule;
			HANDLE hProcess;
			DWORD needed;
			hProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pe32.th32ProcessID); 

			if (hProcess) 
			{
				// ö�ٽ���
				EnumProcessModules(hProcess, &hModule, sizeof(hModule), &needed); 
				// ��ȡ���̵�ȫ·��
				GetModuleFileNameEx(hProcess, hModule, path, sizeof(path));
				// ����·��
				proinfo.m_strFullPath = path;
			}
			else
			{
				proinfo.m_strFullPath = _T("�޷���ý���·��");
			}

			m_vctPrceInfo.push_back(proinfo);
		} 
		while (Process32Next(hProcessSnap, &pe32)); 
	}

	std::vector<ProInfo>::iterator iter;

	for (iter = m_vctPrceInfo.begin(); iter != m_vctPrceInfo.end(); iter++)
	{
		// ��ȡ�ý��̵Ŀ���
		hProcessDll = CreateToolhelp32Snapshot( TH32CS_SNAPMODULE, iter->m_uPID);
		me32.dwSize = sizeof(MODULEENTRY32);

		if (!Module32First(hProcessDll, &me32 ) || iter->m_uPID==0)
		{
			continue;
		}

		do
		{  
			iter->m_strDLLNameArr.push_back(me32.szExePath);
		} 
		while( Module32Next(hProcessDll, &me32));
	}

	// �ر���Ȩ
	EnableDebugPrivilege(0);
	// �ر��ں˶���
	CloseHandle(hProcessSnap ); 
}

#ifndef _PSX_IDE_QT_
void GetProcessFilePath(IN HANDLE hProcess, OUT CString& strFilePath)
{
	strFilePath = _T("");
	TCHAR tsFileDosPath[MAX_PATH + 1];
	ZeroMemory(tsFileDosPath, sizeof(TCHAR)*(MAX_PATH + 1));
	if (0 == GetProcessImageFileName(hProcess, tsFileDosPath, MAX_PATH + 1))
	{
		return;
	}

	// ��ȡLogic Drive String����
	UINT uiLen = GetLogicalDriveStrings(0, NULL);
	if (0 == uiLen)
	{
		return;
	}

	PTSTR pLogicDriveString = new TCHAR[uiLen + 1];
	ZeroMemory(pLogicDriveString, uiLen + 1);
	uiLen = GetLogicalDriveStrings(uiLen, pLogicDriveString);
	if (0 == uiLen)
	{
		delete[]pLogicDriveString;
		return;
	}

	TCHAR szDrive[3] = TEXT(" :");
	PTSTR pDosDriveName = new TCHAR[MAX_PATH];
	PTSTR pLogicIndex = pLogicDriveString;

	do
	{
		szDrive[0] = *pLogicIndex;
		uiLen = QueryDosDevice(szDrive, pDosDriveName, MAX_PATH);
		if (0 == uiLen)
		{
			if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
			{
				break;
			}

			delete[]pDosDriveName;
			pDosDriveName = new TCHAR[uiLen + 1];
			uiLen = QueryDosDevice(szDrive, pDosDriveName, uiLen + 1);
			if (0 == uiLen)
			{
				break;
			}
		}

		uiLen = _tcslen(pDosDriveName);
		if (0 == _tcsnicmp(tsFileDosPath, pDosDriveName, uiLen))
		{
			strFilePath.Format(_T("%s%s"), szDrive, tsFileDosPath + uiLen);
			break;
		}

		while (*pLogicIndex++);
	} while (*pLogicIndex);

	delete[]pLogicDriveString;
	delete[]pDosDriveName;
}

BOOL FindExeDllProcess(const CStringArray &strProcessPaths,CLocalProgresses* pLocalProgresses)
{
	ASSERT(pLocalProgresses != NULL);
	pLocalProgresses->DeleteAll();

	CStringArray strExePaths,strDllPaths;
	CString strFilePath,strFileFix,strModulePath;	//��������·��;
	int nCount;

	TCHAR strShortPath[MAX_PATH];
	GetModuleFileName(NULL,strShortPath,MAX_PATH);

	TCHAR strFullPath[MAX_PATH] = { 0 };  
	GetLongPathName( strShortPath, strFullPath, sizeof(strFullPath)/sizeof(TCHAR) );  
	strModulePath = strFullPath;

	for (nCount = 0;nCount<strProcessPaths.GetSize();nCount++)//ȷ�ϴ������ļ�·����Ч����ΪEXE��DLL���ࣻ
	{
		strFilePath = strProcessPaths.GetAt(nCount);

		if (IsFileExist(strFilePath))
		{
			strFileFix = ParseFilePostfix(strFilePath);
			strFileFix.MakeLower();

			if (strFileFix == _T("exe"))
			{
				strExePaths.Add(strFilePath);
			} 
			else if (strFileFix == _T("dll"))
			{
				strDllPaths.Add(strFilePath);
			}
		}
	}

	CProcessInfo procInfor;
	procInfor.GetProcessName();

	CLocalProgress* pLocalProgress = NULL;

	std::vector<ProInfo>::iterator iter;
	int nExeNum = strExePaths.GetSize(),nDllNum = strDllPaths.GetSize();

	try
	{
		for (iter = procInfor.GetBeginPrceInfo(); iter != procInfor.GetEndPrceInfo(); iter++)
		{
			for (int nCount = 0;nCount<nExeNum;nCount++)//ƥ��ý����Ƿ�����Ҫ������EXE�ļ��Ľ���
			{
				if (iter->m_strFullPath.CompareNoCase(strExePaths.GetAt(nCount))==0)
				{
					pLocalProgress = new CLocalProgress;
					pLocalProgress->m_nPID = iter->m_uPID;
					pLocalProgress->m_strName = GetFileNameFromFilePath(iter->m_strFullPath);
					pLocalProgress->m_strPath = GetPathFileNameFromFilePathName(iter->m_strFullPath);
					pLocalProgress->m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, iter->m_uPID);

					if (iter->m_strFullPath.CompareNoCase(strModulePath)==0)
					{
						pLocalProgress->m_bSelf = TRUE;
					}
					else
					{
						pLocalProgress->m_bSelf = FALSE;
					}
					
					if(pLocalProgress->m_bSelf)
					{
						delete pLocalProgress;
					}
					else
					{
						pLocalProgresses->AddNewChild(pLocalProgress);
					}

					break;
				}
			} 

			std::vector<CString>::iterator iterDll;

			for (iterDll = iter->m_strDLLNameArr.begin(); iterDll != iter->m_strDLLNameArr.end(); iterDll++)//ƥ��ý����е�����DLL�ļ��Ƿ�����Ҫ������DLL�ļ�
			{
				for (int nDllCount = 0;nDllCount<nDllNum;nDllCount++)
				{
					if (*iterDll == strDllPaths.GetAt(nDllCount))
					{
						pLocalProgress = new CLocalProgress;
						pLocalProgress->m_nPID = iter->m_uPID;
						pLocalProgress->m_strName = GetFileNameFromFilePath(iter->m_strFullPath);
						pLocalProgress->m_strPath = GetPathFileNameFromFilePathName(iter->m_strFullPath);
						pLocalProgress->m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, true, iter->m_uPID);

						if (iter->m_strFullPath.CompareNoCase(strModulePath)==0)
						{
							pLocalProgress->m_bSelf = TRUE;
						}
						else
						{
							pLocalProgress->m_bSelf = FALSE;
						}

						if(pLocalProgress->m_bSelf)
						{
							delete pLocalProgress;
						}
						else
						{
							pLocalProgresses->AddNewChild(pLocalProgress);
						}

						break;
					}
				}
			}
		}
		return TRUE;
	}
	catch(...)
	{
		return FALSE;
	}
}

void TerminateProcess(CLocalProgresses& oLocalProgresses)
{
	CLocalProgress* pLocalProgress = NULL;
	POS pos = oLocalProgresses.GetHeadPosition();

	while (pos)
	{
		pLocalProgress = (CLocalProgress*)oLocalProgresses.GetNext(pos);

		if (pLocalProgress && pLocalProgress->m_hProcess != INVALID_HANDLE_VALUE && !pLocalProgress->m_bSelf)
		{
			TerminateProcess(pLocalProgress->m_hProcess,0);
			oLocalProgresses.Delete(pLocalProgress);
		}
	}
}
#endif


