// GlobalApi.cpp
//
//////////////////////////////////////////////////////////////////////

// #include "stdafx.h"
#include "../GlobalApi.h"
#include "../FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


bool ReadDataFromRegister(const CString &pszKey,const CString &pszValueName,CString &strData)
{
    HKEY hKey = NULL;
    DWORD dw = 0;
    LONG lResult = RegCreateKeyEx(HKEY_CURRENT_USER, pszKey
        ,0L,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);

    if (ERROR_SUCCESS != lResult)
    {
        return false;
    }

     ASSERT(hKey);
    if (hKey == NULL)
    {
        return false;
    }

    DWORD dwType = 0;
    DWORD dwSize = MAX_PATH;
    char pbData[MAX_PATH];
    LONG IReturn = RegQueryValueEx(hKey, pszValueName,NULL,&dwType, (BYTE*)pbData, &dwSize);
    strData = pbData;

    if(IReturn != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}

bool WriteDataToRegister(LPCTSTR pszKey,LPCTSTR pszValueName,LPCSTR pszData)
{
    ASSERT(pszKey != NULL && pszValueName != NULL && pszData != NULL);
    if (pszKey == NULL && pszValueName == NULL && pszData == NULL)
    {
        return false;
    }

    HKEY hKey = NULL;
    DWORD dw = 0;
    LONG lResult = RegCreateKeyEx(HKEY_CURRENT_USER,pszKey
        ,0L,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
    if (ERROR_SUCCESS != lResult)
    {
        return false;
    }

    ASSERT(hKey);
    if (hKey == NULL)
    {
        return false;
    }

    DWORD dwType = 0;

    LONG IReturn = RegSetValueEx(hKey,pszValueName,0L,REG_SZ,(CONST BYTE *)pszData,strlen(pszData)+1);
    if(IReturn != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}

CString ReadDataFromRegister(const CString &strRoot,const CString &strRegKey)
{
    if(strRoot.GetLength() <= 0 || strRegKey.GetLength() <= 0)
        return CString("");

    CString strData;
    //	CPowerRegisterKey regKey;
    //	regKey.RegRegOpen(HKEY_CURRENT_USER,_T(strRoot));
    //	regKey.RegRead(strRegKey,pszRegKeyData);
    if (ReadDataFromRegister(strRoot,strRegKey,strData) )
    {
        strData.TrimLeft();
        strData.TrimRight();
    }
    else
    {
        strData = _T("");
    }


    return strData;
}

bool WriteDataToRegister(const CString &pszKey,const CString &pszValueName,const CString &pszData)
{
    HKEY hKey = NULL;
    DWORD dw = 0;
    LONG lResult = RegCreateKeyEx(HKEY_CURRENT_USER,pszKey
        ,0L,NULL,REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS,NULL,&hKey,&dw);
    if (ERROR_SUCCESS != lResult)
    {
        return false;
    }

    ASSERT(hKey);
    if (hKey == NULL)
    {
        return false;
    }

    DWORD dwType = 0;
    char pszDataBuffer[MAX_PATH];
    CString_to_char(pszData, pszDataBuffer);

    LONG IReturn = RegSetValueEx(hKey,pszValueName,0L,REG_SZ, (const BYTE*)pszDataBuffer,strlen(pszDataBuffer)+1);
    if(IReturn != ERROR_SUCCESS)
    {
        return false;
    }

    return true;
}

BOOL IsProgramdExeFileSame(const CString &strExeFile, const CString &strProcessFile)
{
    long nPos = strProcessFile.Find('~');

    if (nPos > 0)
    {
#ifdef _UNICODE
        return wcsncmp(strExeFile, strProcessFile, nPos) == 0;
#else
        return strncmp(strExeFile, strProcessFile, nPos) == 0;
#endif
    }
    else
    {
		//山东继电保护自动测试项目，在iSmartTest.exe进程中判断SmartTest.exe进程是否存在，此处永远返回TRUE。
        //return strProcessFile.Find(strExeFile,0) >= 0;
		long nLen1 = strExeFile.GetLength();
		long nLen2 = strProcessFile.GetLength();

#ifdef _UNICODE
		return wcsncmp(strExeFile, strProcessFile, min(nLen1, nLen2)) == 0;
#else
		return strncmp(strExeFile, strProcessFile, min(nLen1, nLen2)) == 0;
#endif
    }
}

#include <tlhelp32.h>
BOOL IsProgramExist(const CString &strProcessName)
{
    BOOL bExist = FALSE;
    HANDLE snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0) ;
    if(snapshot == NULL)
        return bExist;

    CString strTemp = strProcessName;
    strTemp.MakeLower();

    SHFILEINFO shSmall;
    CString str;
    PROCESSENTRY32 processinfo ;
    processinfo.dwSize=sizeof(processinfo) ;
    BOOL status=Process32First(snapshot,&processinfo) ;

    while (status)
    {
        ZeroMemory(&shSmall, sizeof(shSmall));
// 		SHGetFileInfo(processinfo.szExeFile,0,&shSmall,sizeof(shSmall),
// 			SHGFI_ICON | SHGFI_SMALLICON);
        str=processinfo.szExeFile;
        str.MakeLower();

        //if (str.Find(strTemp,0) >= 0)
        if (IsProgramdExeFileSame(strTemp, str))
        {
            bExist = TRUE;
            break;
        }

        status = Process32Next (snapshot, &processinfo) ;
    }

    CloseHandle(snapshot);

    return bExist;
}

BOOL TerminateProgram(const CString &strProcessName)
{
    BOOL bExist = FALSE;
    HANDLE snapshot = CreateToolhelp32Snapshot (TH32CS_SNAPPROCESS, 0) ;
    if(snapshot == NULL)
        return bExist;

    CString strTemp = strProcessName;
    strTemp.MakeLower();

    SHFILEINFO shSmall;
    CString str;
    PROCESSENTRY32 processinfo ;
    processinfo.dwSize=sizeof(processinfo) ;
    BOOL status=Process32First(snapshot,&processinfo) ;
    while (status)
    {
        ZeroMemory(&shSmall, sizeof(shSmall));
// 		SHGetFileInfo(processinfo.szExeFile,0,&shSmall,sizeof(shSmall),
// 			SHGFI_ICON | SHGFI_SMALLICON);
        str = processinfo.szExeFile;
        str.MakeLower();

        //if (str.Find(strTemp,0) >= 0)
        if (IsProgramdExeFileSame(strTemp, str))
        {
            TRACE("%s\n",str);
            HANDLE h = OpenProcess(PROCESS_ALL_ACCESS,FALSE,processinfo.th32ProcessID);
            if (h != NULL)
            {
                TerminateProcess(h,0);
                bExist = TRUE;
            }
            else
            {
                //return bExist;
            }
        }
        status = Process32Next (snapshot, &processinfo) ;
    }

    CloseHandle(snapshot);

    return bExist;
}



void GetVariantString(VARIANT *pVar, CString &strVar)
{
    switch (pVar->vt)
    {
    case VT_I2:    // 2,
        strVar.Format(_T("%d"), pVar->iVal);
        break;
    case VT_I4	:    // 3,
        strVar.Format(_T("%d"), pVar->lVal);
        break;
    case VT_R4	:    // 4,
        strVar.Format(_T("%f"), pVar->fltVal);
        break;
    case VT_R8	:    // 5,
        strVar.Format(_T("%f"), pVar->dblVal);
        break;
    case VT_I1	:    // 16,
        strVar.Format(_T("%d"), pVar->cVal);
        break;
    case VT_UI1	:    // 17,
        strVar.Format(_T("%d"), pVar->bVal);
        break;
    case VT_UI2	:    // 18,
        strVar.Format(_T("%d"), pVar->uiVal);
        break;
    case VT_UI4	:    // 19,
        strVar.Format(_T("%d"), pVar->ulVal);
        break;
    case VT_I8	:    // 20,
        strVar.Format(_T("%d"), pVar->llVal);
        break;
    case VT_UI8	:    // 21,
        strVar.Format(_T("%d"), pVar->ullVal);
        break;
    case VT_INT	:    // 22,
        strVar.Format(_T("%d"), pVar->intVal);
        break;
    case VT_UINT:	//= 23,
        strVar.Format(_T("%d"), pVar->uintVal);
        break;
    default:
        strVar = _T("");
        break;
    }
}

BOOL IsCurrTickCountTimeOut(DWORD dwBeginTick, DWORD dwTickLong)
{
    DWORD dwCurrTick = ::GetTickCount();
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
    CString strPN = strExeFileName;
    strPN.MakeLower();
    BOOL b;
    HANDLE hnd;
    PROCESSENTRY32 pe;

    hnd=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    pe.dwSize=sizeof(pe);
    b=Process32First(hnd,&pe);

    while(b)
    {
        CString strTemp;
        strTemp = pe.szExeFile;
        strTemp.MakeLower();

        if(strPN == strTemp)
        {
            return pe.th32ProcessID;
        }

        b=Process32Next(hnd,&pe);
    }

    return 0;
}

void ActiveProcMainWnd(const CString &strExeFileName)
{
    CString strTemp;
    strTemp = strExeFileName;
    strTemp.MakeLower();
    DWORD nProcID = GetProcID(strTemp);
    strTemp = strTemp.Left(strTemp.GetLength() - 4); //???.exe

    if (nProcID == 0)
    {
        return;
    }

    if (nProcID != 0)
    {
        HWND hWnd = GetProcMainWndByPid(nProcID, strTemp);

        if (hWnd != NULL)
        {
            //???????
            ::ShowWindow(hWnd, SW_SHOW);

            //??????
            ::SetForegroundWindow(hWnd);

            //???????
            //::SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
        }
    }
}

HWND GetProcMainWndByPid(DWORD dwProcessID, CString &strTitle)
{
    //????Z????????????
    HWND hDeskTopWnd = ::GetDesktopWindow();//::GetTopWindow(0);
    HWND hWnd = ::GetWindow(hDeskTopWnd,GW_CHILD);        //?????????????????
    HWND hWndFind = NULL;
    TCHAR lpszTitle[100];
    ZeroMemory(lpszTitle, 100);
    TCHAR *pFind = NULL;
    TCHAR *pBuffer = NULL;
    pBuffer = strTitle.GetBuffer();

    while ( hWnd )
    {
        DWORD pid = 0;
        //?????????????????ID
        DWORD dwTheardId = ::GetWindowThreadProcessId( hWnd,&pid);

        if (dwTheardId != 0)
        {
            if ( pid == dwProcessID )
            {
                ::GetWindowText(hWnd, lpszTitle, 100);
                CharLowerBuff(lpszTitle, 100);

#ifdef _UNICODE
                pFind = wcsstr(lpszTitle, pBuffer);
#else
                pFind = strstr(lpszTitle, pBuffer);
#endif

                if (pFind != NULL)
                {
                    hWndFind = hWnd;
                    break;
                }
            }
        }

        //????z???е????????????????????
        hWnd = ::GetNextWindow(hWnd , GW_HWNDNEXT);
    }

    return hWndFind;
}

BOOL KillProc(const CString &pn)
{
    typedef  void WINAPI ZwDuplicateObject(DWORD,HANDLE,DWORD,PHANDLE,unsigned long,unsigned long,unsigned long);
    HMODULE hNTDLL   =   GetModuleHandle(_T("ntdll.dll"));
    ZwDuplicateObject *pZwDuplicateObject=NULL;
    pZwDuplicateObject = (ZwDuplicateObject*)GetProcAddress(hNTDLL,"ZwDuplicateObject");
    DWORD pid=0;

    pid=GetProcID(pn);

    if(pid==0)
    {
        //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "?????????ID");
        return 0;
    }

    HANDLE ProcessHandle=OpenProcess(PROCESS_DUP_HANDLE,FALSE,pid);

    if(ProcessHandle != NULL)
    {
        pZwDuplicateObject(-1,ProcessHandle,-1,&ProcessHandle,2035711,0,1);
        TerminateProcess(ProcessHandle,0);
        return 1;
    }

    //CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "??????/n");

    //getchar();
    return 0;
}

BOOL ExecuteFile(const CString &strExePath, const CString &strCmdLine, const CString &strMode)
{
    CString strExeName = GetPathFileNameFromFilePathName(strExePath);

    if (strMode == _T("single"))
    {
        //if (IsProgramExist(strExeName))
        strExeName.MakeLower();
        DWORD dwPid = GetProcID(strExeName);
        strExeName = strExeName.Left(strExeName.GetLength() - 4);

        if (dwPid > 0)
        {
            HWND hWnd = GetProcMainWndByPid(dwPid, strExeName);

            if (hWnd != NULL)
            {
                //???????
                ::ShowWindow(hWnd, SW_NORMAL);

                //??????
                ::SetForegroundWindow(hWnd);

                //???????
                ::SetWindowPos(hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE|SWP_NOSIZE);
            }

            return TRUE;
        }
    }

    HINSTANCE hInstance = ::ShellExecute(NULL, _T("open"), strExePath, strCmdLine, NULL, SW_SHOWNORMAL);
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("strExeName = %s , hInstance = %d"), strExeName, (long)hInstance);

	if (hInstance == NULL)
	{
		return FALSE;
	}

	return ((long)hInstance > 32);

    //return (hInstance != NULL);
}

void UI_ExpandAllChildren(CTreeCtrl *pTree, HTREEITEM hCurr)
{
    HTREEITEM hChild = pTree->GetChildItem(hCurr);

    while (hChild != NULL)
    {
        UI_ExpandAllChildren(pTree, hChild);
        pTree->Expand(hChild, TVE_EXPAND);
        hChild = pTree->GetNextSiblingItem(hChild);
    }

    pTree->Expand(hCurr, TVE_EXPAND);
}

void UI_BringWndToTop(HWND hWnd)
{
    ::ShowWindow(hWnd, SW_SHOW);
    ::SetWindowPos(hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
    ::BringWindowToTop(hWnd);
    ::SetActiveWindow(hWnd);
    ::SetWindowPos(hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
}

void UI_BringWndToTop(CWnd *pWnd)
{
    pWnd->ShowWindow(SW_SHOW);
    ::SetWindowPos(pWnd->m_hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
    pWnd->BringWindowToTop();
    //pWnd->FlashWindowEx(FLASHW_ALL, 4, 500);
    pWnd->SetActiveWindow();
    ::SetWindowPos(pWnd->m_hWnd,HWND_TOPMOST ,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
}


void GetProgramCompileTime(SYSTEMTIME &st)
{
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

        return;
}