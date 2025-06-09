//#include "stdafx.h"
#include "../FileApi.h"
#include "../GlobalConfigApi.h"

#include "afxpriv.h"
#include <shlwapi.h>
#include "winver.h"
#pragma comment(lib, "version")

#ifndef UNICODE
#include "../XfileMngrBase/XFileFindEx.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//将文件的路径写入注册表：传入的参数为文件的绝对路径
void WriteFilePathToRegByFilePathName(const CString &strRoot,const CString &strRegKey,const CString &strPathName)
{
	CString strPath = GetPathFromFilePathName(strPathName);
	WriteDataToRegister(strRoot,strRegKey,strPath);
}


//////////////////////////////////////////////////////////////////////////
//
class CXapiFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CXapiFileDialog)

public:
	CXapiFileDialog(BOOL bOpenFileDialog,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	virtual ~CXapiFileDialog();

	CString m_strDlgCaption;
public:
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal();

};


IMPLEMENT_DYNAMIC(CXapiFileDialog, CFileDialog)

CXapiFileDialog::CXapiFileDialog(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
						   DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{


}

CXapiFileDialog::~CXapiFileDialog()
{
}

// CXFileDialog 消息处理程序
INT_PTR CXapiFileDialog::DoModal()
{
	ASSERT_VALID(this);
	ASSERT(m_ofn.Flags & OFN_ENABLEHOOK);
	ASSERT(m_ofn.lpfnHook != NULL); // can still be a user hook

	// zero out the file buffer for consistent parsing later
	ASSERT(AfxIsValidAddress(m_ofn.lpstrFile, m_ofn.nMaxFile));
	DWORD nOffset = lstrlen(m_ofn.lpstrFile)+1;
	ASSERT(nOffset <= m_ofn.nMaxFile);
	memset(m_ofn.lpstrFile+nOffset, 0, (m_ofn.nMaxFile-nOffset)*sizeof(TCHAR));

	//  This is a special case for the file open/save dialog,
	//  which sometimes pumps while it is coming up but before it has
	//  disabled the main window.
	HWND hWndFocus = ::GetFocus();
	BOOL bEnableParent = FALSE;
	m_ofn.hwndOwner = PreModal();
	AfxUnhookWindowCreate();
	if (m_ofn.hwndOwner != NULL && ::IsWindowEnabled(m_ofn.hwndOwner))
	{
		bEnableParent = TRUE;
		::EnableWindow(m_ofn.hwndOwner, FALSE);
	}

	_AFX_THREAD_STATE* pThreadState = AfxGetThreadState();
	ASSERT(pThreadState->m_pAlternateWndInit == NULL);

	if (m_bVistaStyle == TRUE)
	{
		AfxHookWindowCreate(this);
	}
	else if (m_ofn.Flags & OFN_EXPLORER)
		pThreadState->m_pAlternateWndInit = this;
	else
		AfxHookWindowCreate(this);

	INT_PTR nResult = 0;

	if (m_bVistaStyle == TRUE)
	{
		ApplyOFNToShellDialog();
		IFileDialog *pIFileDialog = static_cast<IFileDialog*>(m_pIFileDialog);

#ifdef _UNICODE
		pIFileDialog->SetTitle(m_strDlgCaption);
#else
		pIFileDialog->SetTitle(_bstr_t(m_strDlgCaption));
#endif
		HRESULT hr = pIFileDialog->Show(m_ofn.hwndOwner);
		nResult = (hr == S_OK) ? IDOK : IDCANCEL;
	}
	else
	{
		m_ofn.lpstrTitle = m_strDlgCaption;

		if (m_bOpenFileDialog)
			nResult = ::AfxCtxGetOpenFileName(&m_ofn);
		else
			nResult = ::AfxCtxGetSaveFileName(&m_ofn);
	}

	if (nResult)
		ASSERT(pThreadState->m_pAlternateWndInit == NULL);
	pThreadState->m_pAlternateWndInit = NULL;

	// Second part of special case for file open/save dialog.
	if (bEnableParent)
		::EnableWindow(m_ofn.hwndOwner, TRUE);
	if (::IsWindow(hWndFocus))
		::SetFocus(hWndFocus);

	PostModal();
	return nResult ? nResult : IDCANCEL;
}


BOOL CXapiFileDialog::OnInitDialog()
{
	CFileDialog::OnInitDialog();

	if (m_strDlgCaption.GetLength() > 0)
	{
		SetWindowText(m_strDlgCaption);
	}

	return TRUE;
}

//
//////////////////////////////////////////////////////////////////////////
//



BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						   ,const CString &strFilter,const CString &strPostFix)
{
#ifdef _UNICODE
	WCHAR pszFilter[255];
	wcscpy(pszFilter,strFilter);
#else
	char pszFilter[255];
	strcpy(pszFilter,strFilter);
#endif
	CString strPath = ReadDataFromRegister(strRoot,strRegKey);
	strPath += _T(".");
	strPath += strPostFix;
	
	CFileDialog dlg(FALSE,strPostFix,strPath,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,pszFilter,pParent);
	if(dlg.DoModal() == IDOK)
	{
		if((dlg.GetFileTitle()).GetLength() > 0)
		{
			strFilePath = dlg.GetPathName();
			WriteFilePathToRegByFilePathName(strRoot,strRegKey,strFilePath);
		}
		else
		{
			strFilePath = _T("");
		}
	}
	if(strFilePath.GetLength() > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL PopupSaveAsFileDialog(CWnd *pParent,CString &strFilePath ,const CString &strFilter,const CString &strPostFix)
{
	CFileDialog dlg(FALSE,strPostFix,strFilePath,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,pParent);

	if(dlg.DoModal() == IDOK)
	{
		if((dlg.GetFileTitle()).GetLength() > 0)
		{
			strFilePath = dlg.GetPathName();
			return TRUE;
		}
		else
		{
			strFilePath = _T("");
		}
	}

	return FALSE;
}

BOOL PopupSaveAsFileDialogEx(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						   ,const CString &strFilter,const CString &strPostFix,const CString &strDefaultFile)
{
#ifdef _UNICODE
	WCHAR pszFilter[255];
	wcscpy(pszFilter,strFilter);
#else
	char pszFilter[255];
	strcpy(pszFilter,strFilter);
#endif
	CString strPath = ReadDataFromRegister(strRoot,strRegKey);
	strPath += strDefaultFile;

	if (strFilePath.GetLength() < 3)
	{
		strPath = ReadDataFromRegister(strRoot,strRegKey);
		strPath += strDefaultFile;
	}
	else
	{
		strPath = strFilePath;
	}
	
	CFileDialog dlg(FALSE,strPostFix,strPath,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,pszFilter,pParent);
	if(dlg.DoModal() == IDOK)
	{
		if((dlg.GetFileTitle()).GetLength() > 0)
		{
			strFilePath = dlg.GetPathName();
			WriteFilePathToRegByFilePathName(strRoot,strRegKey,strFilePath);
		}
		else
		{
			strFilePath = _T("");
		}
	}
	if(strFilePath.GetLength() > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strFilter
						 ,const CString &strPostFix, const CString &strCaption)
{
	CString strPath;

	if (strFilePath.GetLength() < 3)
	{
		strPath = strFilePath;

		if (strPath.Right(1) != "\\")
		{
			strPath += _T("\\");
		}

		strPath += _T(".");
		strPath += strPostFix;
	}
	else
	{
		strPath = strFilePath;
	}

	CXapiFileDialog dlg(TRUE,strPostFix,strPath,OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,strFilter,pParent);
	dlg.m_strDlgCaption = strCaption;

	if(dlg.DoModal() == IDOK)
	{
		strFilePath = dlg.GetPathName();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL PopupOpenFileDialog(CWnd *pParent,CString &strFilePath,const CString &strRoot,const CString &strRegKey
						 ,const CString &strFilter,const CString &strPostFix
						 ,const CString &strCaption)
{
#ifdef _UNICODE
	WCHAR pszFilter[255];
	wcscpy(pszFilter,strFilter);
#else
	char pszFilter[255];
	strcpy(pszFilter,strFilter);
#endif
	CString strPath;
	
	if (strFilePath.GetLength() < 3)
	{
		strPath = ReadDataFromRegister(strRoot,strRegKey);
		strPath += _T(".");
		strPath += strPostFix;
	}
	else
	{
		strPath = strFilePath;
	}
	
	CXapiFileDialog dlg(TRUE,strPostFix,strPath,OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,pszFilter,pParent);
	dlg.m_strDlgCaption = strCaption;

	if(dlg.DoModal() == IDOK)
	{
		if((dlg.GetFileTitle()).GetLength() > 0)
		{
			strFilePath = dlg.GetPathName();
			WriteFilePathToRegByFilePathName(strRoot,strRegKey,strFilePath);
		}
		else
		{
			strFilePath = _T("");
		}
	}
	if(strFilePath.GetLength() > 0)
		return TRUE;
	else
		return FALSE;
}

BOOL PopupOpenFileDialog(CStringArray &vecFiles,const CString &strFilter
						 ,const CString &strPostfix,const CString &strCaption,int nMaxFiles)
{
    CFileDialog dlg(TRUE, strPostfix, NULL
		, OFN_ALLOWMULTISELECT|OFN_HIDEREADONLY | OFN_FILEMUSTEXIST
		, strFilter, NULL); 

	vecFiles.RemoveAll();

	CString strFile;
	dlg.m_ofn.lpstrTitle = strCaption; 

	TCHAR *pBuffer = new TCHAR[MAX_PATH  * nMaxFiles];//最多允许同时打开20个文件
	dlg.m_ofn.lpstrFile = pBuffer;
	dlg.m_ofn.nMaxFile = nMaxFiles * MAX_PATH;
	dlg.m_ofn.lpstrFile[0] = '\0';
	if(dlg.DoModal() == IDOK) 
	{ 
		POSITION fileNamesPosition = dlg.GetStartPosition(); 
		while(fileNamesPosition != NULL) 
		{ 
			strFile = dlg.GetNextPathName(fileNamesPosition); 
			vecFiles.Add(strFile);
		}   
	} 

	delete pBuffer;
	return (vecFiles.GetSize() > 0);
}

BOOL FGetDirectory(HWND hParent, CString &strPath, const CString &strTitle)
{
	wchar_t pszBuffer[MAX_PATH];
	memset(pszBuffer,0,sizeof(wchar_t)*MAX_PATH);

	bstr_t bstrText;
	bstrText = strTitle;

	if (!FGetDirectory(hParent, pszBuffer, bstrText/*_T("选择导入的配置文件夹")*/))
	{
		return FALSE;
	}

	strPath = pszBuffer;
	
	return TRUE;
}

BOOL FGetDirectoryA(HWND hParent, CString &strPath, const CString &strTitle)
{
	char  szPath[MAX_PATH] = {0};
	CString_to_char(strPath,szPath);

	if (!FGetDirectory(hParent, szPath, (char *)strTitle.GetString()))
	{
		return FALSE;
	}

	strPath = szPath;
	return TRUE;
}

//xxy 20210604 用于设置默认选择目录
static int CALLBACK _SHBrowseForFolderCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData )
{
	switch(uMsg)
	{
	case BFFM_INITIALIZED:    
		::SendMessage(hwnd,BFFM_SETSELECTION,TRUE,lpData);   //传递默认打开路径 break;
	default:
		break;
	} 
	return 0;
}

//xxy 20210604 宽字符设置默认路径无效，未找到原因，多字节的可以
BOOL FGetDirectory(HWND hParent, wchar_t *szDir, wchar_t *strTitle) 
{ 
	BOOL  fRet; 
//	wchar_t  szPath[MAX_PATH]; 
	LPITEMIDLIST pidl; 
	LPITEMIDLIST pidlRoot; 
	LPMALLOC lpMalloc; 
	
	BROWSEINFOW bi = 
	{
		hParent, 
			NULL, 
			szDir,
			strTitle, 
			BIF_USENEWUI | BIF_RETURNONLYFSDIRS, 
			_SHBrowseForFolderCallbackProc, 
			LPARAM(szDir), 
			0
	}; 
	
	if (0 != SHGetSpecialFolderLocation(hParent, CSIDL_DRIVES, &pidlRoot)) 
		return FALSE; 
	if (NULL == pidlRoot) 
		return FALSE; 
	
	bi.pidlRoot = pidlRoot; 
	pidl = SHBrowseForFolderW(&bi); 
	
	if (NULL != pidl) 
		fRet = SHGetPathFromIDListW(pidl, szDir); 
	else 
		fRet = FALSE; 
	
	if (!SHGetMalloc(&lpMalloc) && (NULL != lpMalloc)) 
	{ 
		if (NULL != pidlRoot) 
		{ 
			lpMalloc->Free(pidlRoot); 
		} 
		
		if (NULL != pidl) 
		{ 
			lpMalloc->Free(pidl); 
		} 
		
		lpMalloc->Release(); 
	} 
	
	return fRet; 
} 

BOOL FGetDirectory(HWND hParent, char *szDir, char *strTitle) 
{ 
	BOOL  fRet; 
	char  szPath[MAX_PATH]; 
	LPITEMIDLIST pidl; 
	LPITEMIDLIST pidlRoot; 
	LPMALLOC lpMalloc; 

	BROWSEINFOA bi = 
	{
		hParent, 
		NULL, 
		szDir,
		strTitle, 
		BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE , 
		_SHBrowseForFolderCallbackProc, 
		LPARAM(szDir), 
		0
	}; 

	if (0 != SHGetSpecialFolderLocation(HWND_DESKTOP, CSIDL_DRIVES, &pidlRoot)) 
		return FALSE; 
	if (NULL == pidlRoot) 
		return FALSE; 

	bi.pidlRoot = pidlRoot; 
	pidl = SHBrowseForFolderA(&bi); 

	if (NULL != pidl) 
		fRet = SHGetPathFromIDListA(pidl, szDir); 
	else 
		fRet = FALSE; 

	if (!SHGetMalloc(&lpMalloc) && (NULL != lpMalloc)) 
	{ 
		if (NULL != pidlRoot) 
		{ 
			lpMalloc->Free(pidlRoot); 
		} 

		if (NULL != pidl) 
		{ 
			lpMalloc->Free(pidl); 
		} 

		lpMalloc->Release(); 
	} 

	return fRet; 
} 

//创建文件路径
void CreateAllDirectories(CString strDir)
{
	if (strDir.GetLength() == 0)
	{
		return;
	}

	CString strTemp;
	strTemp = strDir.Right(1);
	//remove ending / if exists
	if(strTemp== _T("\\") || strTemp == _T("/"))
		strDir=strDir.Left(strDir.GetLength()-1);

	// base case . . .if directory exists
#ifdef UNICODE
	if(GetFileAttributes(strDir)!=-1)
		return;
#else
	BSTR bstrDir = strDir.AllocSysString();

	if(GetFileAttributesW(bstrDir)!=-1)
	{
		::SysFreeString(bstrDir);
		return;
	}

	::SysFreeString(bstrDir);
#endif

	// recursive call, one less directory
	long nPos = strDir.GetLength()-1;
	TCHAR ch = 0;

	while (TRUE)
	{
		ch = strDir.GetAt(nPos);

		if (ch == '/' || ch == '\\')
		{
			break;
		}

		nPos--;
	}

	CreateAllDirectories(strDir.Left(nPos));

	// actual work
	CreateDirectory(strDir,NULL);
}

BOOL DeleteAllDirectorys(const CString &strDirName, BOOL bDelOwn)
{
	long nLen = strDirName.GetLength();
	ASSERT(nLen > 0);

	if (nLen == 0)
	{
		return FALSE;
	}

#ifdef UNICODE
	CFileFind tempFind; 
#else
	CXFileFindEx tempFind; 
#endif

	CString strFileNeedFind; 
	CString strFindFileName; 
	CString strTempDirectory; 
	CString strTempFileName; 

	strFileNeedFind = strDirName;
	if (strDirName[nLen-1] != '\\')
	{
		strFileNeedFind = strFileNeedFind + _T("\\");
	}

	strFileNeedFind = strFileNeedFind + _T("*.*");

	BOOL IsFinded = tempFind.FindFile(strFileNeedFind); 

	while(IsFinded) 
	{
		IsFinded = tempFind.FindNextFile();

		if( !tempFind.IsDots() ) 
		{ 
			strFindFileName = tempFind.GetFileName(); 

			if(tempFind.IsDirectory()) 
			{ 
				strTempDirectory.Format(_T("%s\\%s"), strDirName, strFindFileName); 
				DeleteAllDirectorys(strTempDirectory, TRUE); 
			}
			else 
			{ 
				strTempFileName.Format(_T("%s\\%s"), strDirName, strFindFileName); 
				X_DeleteFile(strTempFileName); 
			} 
		} 
	} 

	tempFind.Close(); 
	BOOL bRet = FALSE;

	if (!bDelOwn)
	{
		return bRet;
	}

#ifdef UNICODE
	bRet = RemoveDirectory(strDirName);
#else
	BSTR bstrDirName = strDirName.AllocSysString();
	bRet = RemoveDirectoryW(bstrDirName);
	::SysFreeString(bstrDirName);
#endif 

	return bRet; 
}

BOOL DeleteAllFiles(const CString &strDirName, const CString &strFileType)
{
	long nLen = strDirName.GetLength();
	ASSERT(nLen > 0);

	if (nLen == 0)
	{
		return FALSE;
	}

#ifdef UNICODE
	CFileFind tempFind; 
#else
	CXFileFindEx tempFind; 
#endif

	CString strFileNeedFind; 
	CString strFindFileName; 
	CString strTempDirectory; 
	CString strTempFileName; 
	long nCount = 0;

	strFileNeedFind = strDirName;
	if (strDirName[nLen-1] != '\\')
	{
		strFileNeedFind = strFileNeedFind + _T("\\");
	}

	strFileNeedFind.AppendFormat(_T("*.%s"), strFileType);

	BOOL IsFinded = tempFind.FindFile(strFileNeedFind); 

	while(IsFinded) 
	{
		IsFinded = tempFind.FindNextFile();

		if( !tempFind.IsDots() ) 
		{ 
			if(tempFind.IsDirectory()) 
			{ 
			}
			else 
			{ 
				strFindFileName = tempFind.GetFileName(); 
				strTempFileName.Format(_T("%s\\%s"), strDirName, strFindFileName); 
				X_DeleteFile(strTempFileName); 
				nCount++;
			} 
		} 
	}

	return nCount > 0; 
}

void ClearFileReadOnlyAttr(const CString &strFile)
{
	DWORD wAttr = 0;
	BOOL bRet = FALSE;

	BSTR bstrFile = strFile.AllocSysString();
	wAttr = GetFileAttributesW(bstrFile);

	if (wAttr == (DWORD)-1L)
	{
		::SysFreeString(bstrFile);
		return;
	}

	if ( wAttr & FILE_ATTRIBUTE_READONLY )
	{
		wAttr  &= ~FILE_ATTRIBUTE_READONLY;
		bRet = SetFileAttributesW(bstrFile, (DWORD)wAttr);
	}

	::SysFreeString(bstrFile);
}

int file_size2(const CString &strFile)    
{    
	struct _stat64i32 statbuf;    

#ifdef _UNICODE
	_wstat(strFile,&statbuf);    
#else
	BSTR bstrFile = strFile.AllocSysString();
	_wstat(bstrFile, &statbuf); 
	::SysFreeString(bstrFile);
#endif

	int size=statbuf.st_size;    

	return size;    
} 

long file_GetFileSize(const CString &strFile)
{
	return file_size2(strFile);
}

void file_get_time(const CString &strFile, CString &strTime)    
{    
	struct _stat64i32 statbuf;    

#ifdef _UNICODE
	_wstat(strFile,&statbuf);    
#else
	BSTR bstrFile = strFile.AllocSysString();
	_wstat(bstrFile, &statbuf); 
	::SysFreeString(bstrFile);
#endif

	CTime tm(statbuf.st_mtime);
	SYSTEMTIME tmSys;
	tm.GetAsSystemTime(tmSys);

	strTime.Format(_T("%d-%d-%d %d:%d:%d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
} 

CString file_get_time(const CString &strFile)
{
	CString strTime;
	file_get_time(strFile, strTime);
	return strTime;
}

CString file_get_time(const char* pstrFile)
{
	CString strTime;
	file_get_time((CString)pstrFile, strTime);
	return strTime;
}

void file_set_time(HANDLE hFile,SYSTEMTIME &tm)
{
	ASSERT(hFile != INVALID_HANDLE_VALUE);

	FILETIME ft,ft1;
	SystemTimeToFileTime(&tm, &ft);
	LocalFileTimeToFileTime(&ft,&ft1); 
	SetFileTime(hFile, NULL, NULL, &ft1);
}

void file_set_time(const CString& strFile,SYSTEMTIME &tm)
{
	HANDLE hFile;
	hFile = CreateFile(strFile, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ| FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if(hFile != INVALID_HANDLE_VALUE)
	{
		file_set_time(hFile,tm);
		CloseHandle(hFile);
	}
}

//add by yyj at 20200416 begin
void file_set_time(const CString& strFile,unsigned long uTime)
{
	SYSTEMTIME tmSys;

	if (uTime == 0)
	{
		GetLocalTime(&tmSys);
	}
	else
	{
		CTime tm(uTime);
		tm.GetAsSystemTime(tmSys);
	}

	file_set_time(strFile,tmSys);
}
//add by yyj at 20200416 end

void GetRelativePathTo(const CString &strFrom, const CString &strTo, CString &strOut)
{
	TCHAR szOut[MAX_PATH] = _T("");

	PathRelativePathTo(szOut,
		strFrom,
		FILE_ATTRIBUTE_DIRECTORY,
		strTo,
		FILE_ATTRIBUTE_NORMAL);
	strOut = szOut;
}

void GetPathFromRelative(const CString &strFrom, const CString &strFile, CString &strOut)
{
	TCHAR szOut[MAX_PATH] = _T("");

	PathCombine(szOut,strFrom,strFile);
	strOut = szOut;
}

BOOL ValidateFileName(CString &strFileName)
{
	if (strFileName.Find(_T("\\")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("/")) >= 0)
		return FALSE;

	if (strFileName.Find(_T(":")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("*")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("?")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("<")) >= 0)
		return FALSE;

	if (strFileName.Find(_T(">")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("|")) >= 0)
		return FALSE;

	if (strFileName.Find(_T("\"")) >= 0)
		return FALSE;

	return TRUE;
}

#include <stdio.h>
#include <io.h>

BOOL IsFileExist(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

	//四方项目过程中，在AtsBentch启动自动测试程序，AtsBentch的Bin下面拷贝了TestMacro.xml文件
	//自动测试打开测试功能文件时，调用此函数判断文件存在，然后CTestMacros打开TestMacro.xml文件失败
	//因为_access使用了当前系统路径为AtsBentch\Bin，但是SmartTest使用了SmartTest相关的绝对路径，所以打开失败
	//因此，函数确保文件路径为绝对路径，不是绝对路径，就返回不存在
	if (strFile.GetAt(1) != ':')
	{
		return FALSE;
	}

	BSTR bstrFile = strFile.AllocSysString();
	int nRet = _waccess(bstrFile, 0);
	::SysFreeString(bstrFile);

	return (nRet != -1);
}

BOOL X_CopyFile(const CString &strSrcFile, const CString &strDestFile, BOOL bFailIfExists)
{
	BOOL bRet = FALSE;

#ifdef UNICODE
	bRet = ::CopyFileW (strSrcFile, strDestFile, FALSE);
#else
	BSTR bstrSrcFile, bstrDestFile;
	bstrSrcFile = strSrcFile.AllocSysString();
	bstrDestFile = strDestFile.AllocSysString();
	bRet = ::CopyFileW (bstrSrcFile, bstrDestFile, bFailIfExists);
	::SysFreeString(bstrSrcFile);
	::SysFreeString(bstrDestFile);
#endif

	return bRet;
}

BOOL X_DeleteFile(const CString &strFile)
{
	BOOL bRet = FALSE;

#ifdef UNICODE
	bRet = ::DeleteFileW (strFile);
#else
	BSTR bstFile;
	bstFile = strFile.AllocSysString();
	bRet = ::DeleteFileW (bstFile);
	::SysFreeString(bstFile);
#endif

	return bRet;
}


BOOL GetFileVersion(const CString &filePath,unsigned int &nFileVersionMS,  
					unsigned int &nFileVersionLS)  
{  
	DWORD dwHandle;  
	DWORD dwVersionInfoSize; 

#ifdef UNICODE
	const wchar_t *chrFilePath = filePath.GetString();
#else
	const char *chrFilePath = filePath.GetString();
#endif

	dwVersionInfoSize = ::GetFileVersionInfoSize(chrFilePath, &dwHandle);

	if (0 == dwVersionInfoSize)  
	{  
		return FALSE;  
	}  

	char* pVersionInfo = new char[dwVersionInfoSize]; 

	if (! ::GetFileVersionInfo(chrFilePath, 0, dwVersionInfoSize, pVersionInfo))  
	{
		delete[] pVersionInfo;  
		return FALSE;  
	}

	VS_FIXEDFILEINFO* pVersion = NULL;  
	unsigned int nLen;  

	if(! ::VerQueryValue(pVersionInfo, _T("\0"), (void**)&pVersion, &nLen)) 
	{  
		delete[] pVersionInfo;  
		return FALSE;  
	}  

	nFileVersionMS = pVersion->dwFileVersionMS;  
	nFileVersionLS = pVersion->dwFileVersionLS;  

	delete[] pVersionInfo;  

	return TRUE;  
} 

BOOL GetFileVersion(const CString& strFile,CString &strVersion)
{
	if(!IsFileExist(strFile))
	{
		return FALSE;
	}

	unsigned int nFileVersionMS = 0;
	unsigned int nFileVersionLS = 0;

	CString strPostfix = ParseFilePostfix(strFile);

	if (strPostfix.CompareNoCase(_T("exe")) == 0)
	{
		if(GetFileVersion(strFile,nFileVersionMS,nFileVersionLS))
		{
			strVersion.Format(_T("%d.%d.%d.%d")
				,nFileVersionMS>>16	,nFileVersionMS&0xffff
				,nFileVersionLS>>16	,nFileVersionLS&0xffff);
			return TRUE;
		}
	}

	return FALSE;
}
