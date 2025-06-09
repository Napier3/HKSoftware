#include "stdafx.h"
#include "AtlFile.h"
#include "..\API\FileApi.h"

CAtlFile::CAtlFile()
{
	m_hFile = (UINT) hFileNull;
	m_bCloseOnDelete = FALSE;
}

CAtlFile::CAtlFile(int hFile)
{
	m_hFile = hFile;
	m_bCloseOnDelete = FALSE;
}

CAtlFile::CAtlFile(LPCTSTR lpszFileName, UINT nOpenFlags)
{
	Open(lpszFileName, nOpenFlags);
}

CAtlFile::~CAtlFile()
{
	if (m_hFile != (UINT)hFileNull && m_bCloseOnDelete)
		Close();
}

CAtlFile* CAtlFile::Duplicate() const
{
	CAtlFile* pFile = new CAtlFile(hFileNull);
	HANDLE hFile;
	if (!::DuplicateHandle(::GetCurrentProcess(), (HANDLE)m_hFile,
		::GetCurrentProcess(), &hFile, 0, FALSE, DUPLICATE_SAME_ACCESS))
	{
		delete pFile;
	}
	pFile->m_hFile = (UINT)hFile;
	pFile->m_bCloseOnDelete = m_bCloseOnDelete;
	return pFile;
}
//
//CComBSTR CAtlFile::GetFileName() const
//{
//	CFileStatus status;
//	GetStatus(status);
//	CComBSTR strResult;
//	AfxGetFileName(status.m_szFullName, strResult.GetBuffer(_MAX_FNAME),
//		_MAX_FNAME);
//	strResult.ReleaseBuffer();
//	return strResult;
//}
//
//CComBSTR CAtlFile::GetFileTitle() const
//{
//	ASSERT_VALID(this);
//	
//	CFileStatus status;
//	GetStatus(status);
//	CComBSTR strResult;
//	AfxGetFileTitle(status.m_szFullName, strResult.GetBuffer(_MAX_FNAME),
//		_MAX_FNAME);
//	strResult.ReleaseBuffer();
//	return strResult;
//}
//
//CComBSTR CAtlFile::GetFilePath() const
//{
//	ASSERT_VALID(this);
//	
//	CFileStatus status;
//	GetStatus(status);
//	return status.m_szFullName;
//}

#ifndef _PSX_IDE_QT_
BOOL CAtlFile::Open(const CComBSTR &strFileName, UINT nOpenFlags)
{
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFileName);
	
	return Open(szFile, nOpenFlags);
}
#endif

BOOL CAtlFile::Open(BSTR strFileName, UINT nOpenFlags)
{
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFileName);
	
	return Open(szFile, nOpenFlags);
}

BOOL CAtlFile::Open(LPCTSTR lpszFileName, UINT nOpenFlags)
{
//	ASSERT_VALID(this);
//	ATLASSERT(AfxIsValidString(lpszFileName));
//	ATLASSERT(pException == NULL ||
//		AfxIsValidAddress(pException, sizeof(CFileException)));
//	ATLASSERT((nOpenFlags & typeText) == 0);   // text mode not supported
//
	// CAtlFile objects are always binary and CreateFile does not need flag
	nOpenFlags &= ~(UINT)typeBinary;

	m_bCloseOnDelete = FALSE;
	m_hFile = (UINT)hFileNull;
//	memset(m_strFileName, 0, sizeof(TCHAR)*MAX_PATH);
//	m_strFileName.Empty();

//	TCHAR szTemp[_MAX_PATH];
//	AfxFullPath(szTemp, lpszFileName);
//	_tcscpy(m_strFileName, lpszFileName);
	
//	ATLASSERT(sizeof(HANDLE) == sizeof(UINT));
//	ATLASSERT(shareCompat == 0);

	// map read/write mode
//	ATLASSERT((modeRead|modeWrite|modeReadWrite) == 3);
	DWORD dwAccess = 0;
	switch (nOpenFlags & 3)
	{
	case modeRead:
		dwAccess = GENERIC_READ;
		break;
	case modeWrite:
		dwAccess = GENERIC_WRITE;
		break;
	case modeReadWrite:
		dwAccess = GENERIC_READ|GENERIC_WRITE;
		break;
	default:
		break;
	}

	// map share mode
	DWORD dwShareMode = 0;
	switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
	{
	default:
		break;
	case shareCompat:
	case shareExclusive:
		dwShareMode = 0;
		break;
	case shareDenyWrite:
		dwShareMode = FILE_SHARE_READ;
		break;
	case shareDenyRead:
		dwShareMode = FILE_SHARE_WRITE;
		break;
	case shareDenyNone:
		dwShareMode = FILE_SHARE_WRITE|FILE_SHARE_READ;
		break;
	}

	// Note: typeText and typeBinary are used in derived classes only.

	// map modeNoInherit flag
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = (nOpenFlags & modeNoInherit) == 0;

	// map creation flags
	DWORD dwCreateFlag;
	if (nOpenFlags & modeCreate)
	{
		if (nOpenFlags & modeNoTruncate)
			dwCreateFlag = OPEN_ALWAYS;
		else
			dwCreateFlag = CREATE_ALWAYS;
	}
	else
		dwCreateFlag = OPEN_EXISTING;

	// attempt file creation
	HANDLE hFile = ::CreateFile(lpszFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	m_hFile = (HFILE)hFile;
	m_bCloseOnDelete = TRUE;

	return TRUE;
}

UINT CAtlFile::Read(void* lpBuf, UINT nCount)
{
	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (nCount == 0)
		return 0;   // avoid Win32 "null-read"

	ATLASSERT(lpBuf != NULL);
//	ATLASSERT(AfxIsValidAddress(lpBuf, nCount));

	DWORD dwRead = 0;
	::ReadFile((HANDLE)m_hFile, lpBuf, nCount, &dwRead, NULL);

	return (UINT)dwRead;
}

void CAtlFile::Write(const void* lpBuf, UINT nCount)
{
//	ASSERT_VALID(this);
//	ATLASSERT(m_hFile != (UINT)hFileNull);

	if (nCount == 0)
		return;     // avoid Win32 "null-write" option

//	ATLASSERT(lpBuf != NULL);
//	ATLASSERT(AfxIsValidAddress(lpBuf, nCount, FALSE));

	DWORD nWritten;
	::WriteFile((HANDLE)m_hFile, lpBuf, nCount, &nWritten, NULL);
	// Win32s will not return an error all the time (usually DISK_FULL)
/*
	if (nWritten != nCount)
		AfxThrowFileException(CFileException::diskFull, -1, m_strFileName);
*/
}

LONG CAtlFile::Seek(LONG lOff, UINT nFrom)
{
//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);
	ATLASSERT(nFrom == begin || nFrom == end || nFrom == current);
	ATLASSERT(begin == FILE_BEGIN && end == FILE_END && current == FILE_CURRENT);

	DWORD dwNew = ::SetFilePointer((HANDLE)m_hFile, lOff, NULL, (DWORD)nFrom);
/*
	if (dwNew  == (DWORD)-1)
		CFileException::ThrowOsError((LONG)::GetLastError());
*/

	return dwNew;
}

DWORD CAtlFile::GetPosition() const
{
//	ASSERT_VALID(this);
//	ATLASSERT(m_hFile != (UINT)hFileNull);

	DWORD dwPos = ::SetFilePointer((HANDLE)m_hFile, 0, NULL, FILE_CURRENT);
/*
	if (dwPos  == (DWORD)-1)
		CFileException::ThrowOsError((LONG)::GetLastError());
*/

	return dwPos;
}

void CAtlFile::Flush()
{
//	ASSERT_VALID(this);

	if (m_hFile == (UINT)hFileNull)
		return;

//	if (!::FlushFileBuffers((HANDLE)m_hFile))
//		CFileException::ThrowOsError((LONG)::GetLastError());
}

void CAtlFile::Close()
{
//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	BOOL bError = FALSE;
	if (m_hFile != (UINT)hFileNull)
		bError = !::CloseHandle((HANDLE)m_hFile);

	m_hFile = (UINT) hFileNull;
	m_bCloseOnDelete = FALSE;
//	memset(m_strFileName, 0, sizeof(TCHAR)*MAX_PATH);

/*
	if (bError)
		CFileException::ThrowOsError((LONG)::GetLastError());
*/
}

void CAtlFile::Abort()
{
//	ASSERT_VALID(this);
	if (m_hFile != (UINT)hFileNull)
	{
		// close but ignore errors
		::CloseHandle((HANDLE)m_hFile);
		m_hFile = (UINT)hFileNull;
	}
//	memset(m_strFileName, 0, sizeof(TCHAR)*MAX_PATH);
}

void CAtlFile::LockRange(DWORD dwPos, DWORD dwCount)
{
//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	::LockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0);
}

void CAtlFile::UnlockRange(DWORD dwPos, DWORD dwCount)
{
//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	::UnlockFile((HANDLE)m_hFile, dwPos, 0, dwCount, 0);
}

void CAtlFile::SetLength(DWORD dwNewLen)
{
//	ASSERT_VALID(this);
	ATLASSERT(m_hFile != (UINT)hFileNull);

	Seek((LONG)dwNewLen, (UINT)begin);

	::SetEndOfFile((HANDLE)m_hFile);
}

DWORD CAtlFile::GetLength() const
{
//	ASSERT_VALID(this);

	DWORD dwLen, dwCur;

	// Seek is a non const operation
	CAtlFile* pFile = (CAtlFile*)this;
	dwCur = pFile->Seek(0L, current);
	dwLen = pFile->SeekToEnd();

	if(dwCur == (DWORD)pFile->Seek(dwCur, begin))
	{
	}

	return dwLen;
}

// CAtlFile does not support direct buffering (CMemFile does)
UINT CAtlFile::GetBufferPtr(UINT nCommand, UINT /*nCount*/,
	void** /*ppBufStart*/, void** /*ppBufMax*/)
{
//	ATLASSERT(nCommand == bufferCheck);
//	UNUSED(nCommand);    // not used in retail build

	return 0;   // no support
}

void PASCAL CAtlFile::Rename(LPCTSTR lpszOldName, LPCTSTR lpszNewName)
{
	::MoveFile((LPTSTR)lpszOldName, (LPTSTR)lpszNewName);
}

void PASCAL CAtlFile::Remove(LPCTSTR lpszFileName)
{
	X_DeleteFile((LPTSTR)lpszFileName);
}

