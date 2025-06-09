#include "stdafx.h"

#include "XFileFindExImp.h"
#include "..\..\API\FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
////////////////////////////////////////////////////////////////////////////
// CXFileFind implementation

CXFileFindExImp::CXFileFindExImp()
{
	m_pFoundInfo = NULL;
	m_pNextInfo = NULL;
	m_hContext = NULL;
	m_chDirSeparator = '\\';

#ifdef UNICODE
	m_pNextInfo = new WIN32_FIND_DATAW;
	m_pFoundInfo = new WIN32_FIND_DATAW;
#else
	m_pNextInfo = new WIN32_FIND_DATA;
	m_pFoundInfo = new WIN32_FIND_DATA;
#endif
}

CXFileFindExImp::~CXFileFindExImp()
{
	Close();

	if (m_pFoundInfo != NULL)
	{
		delete m_pFoundInfo;
		m_pFoundInfo = NULL;
	}

	if (m_pNextInfo != NULL)
	{
		delete m_pNextInfo;
		m_pNextInfo = NULL;
	}
}

void CXFileFindExImp::Close()
{

	if (m_hContext != NULL)
	{
		if (m_hContext != INVALID_HANDLE_VALUE)
			CloseContext();
		m_hContext = NULL;
	}
}

BOOL CXFileFindExImp::FindFile(const CString &strName /* = NULL */,
	DWORD dwUnused /* = 0 */)
{
	UNUSED_ALWAYS(dwUnused);
	Close();

	if (strName.GetLength() >= X_MAX_PATH)//(_countof(((WIN32_FIND_DATAW*) m_pNextInfo)->cFileName)))
	{
		::SetLastError(ERROR_BAD_ARGUMENTS);
		return FALSE;		
	}
	


#ifdef UNICODE
	WIN32_FIND_DATAW *pFindData = (WIN32_FIND_DATAW *)m_pNextInfo;
	pFindData->cFileName[0] = 0;
	m_hContext = ::FindFirstFileW(strName, (WIN32_FIND_DATAW*) m_pNextInfo);
#else
	WIN32_FIND_DATA *pFindData = (WIN32_FIND_DATA *)m_pNextInfo;
	pFindData->cFileName[0] = 0;
	//BSTR bstrName = strName.AllocSysString();
	m_hContext = ::FindFirstFile(strName, (WIN32_FIND_DATA*) m_pNextInfo);
	//::SysFreeString(bstrName);
#endif

	//ERROR_FILE_NOT_FOUND
	if (m_hContext == INVALID_HANDLE_VALUE)
	{
		DWORD dwTemp = ::GetLastError();
		Close();
		::SetLastError(dwTemp);
		return FALSE;
	}

	m_strRoot = GetPathFromFilePathName(strName);

	return TRUE;
}

BOOL CXFileFindExImp::MatchesMask(DWORD dwMask)
{
	ASSERT(m_hContext != NULL);

	if (m_pFoundInfo != NULL)
#ifdef UNICODE
		return (!!(((LPWIN32_FIND_DATAW) m_pFoundInfo)->dwFileAttributes & dwMask));
#else
		return (!!(((LPWIN32_FIND_DATA) m_pFoundInfo)->dwFileAttributes & dwMask));
#endif
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetLastAccessTime(FILETIME* pTimeStamp)
{
	ASSERT(m_hContext != NULL);
	ASSERT(pTimeStamp != NULL);
	

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{
#ifdef UNICODE
		*pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastAccessTime;
#else
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime;
#endif
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetLastWriteTime(FILETIME* pTimeStamp)
{
	ASSERT(m_hContext != NULL);
	ASSERT(pTimeStamp != NULL);
	

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{	
#ifdef UNICODE
		*pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastWriteTime;
#else
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime;
#endif
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetCreationTime(FILETIME* pTimeStamp)
{
	ASSERT(m_hContext != NULL);
	

	if (m_pFoundInfo != NULL && pTimeStamp != NULL)
	{
#ifdef UNICODE
		*pTimeStamp = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftCreationTime;
#else
		*pTimeStamp = ((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime;
#endif
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetLastAccessTime(CTime& refTime)
{
	ASSERT(m_hContext != NULL);

	if (m_pFoundInfo != NULL)
	{
#ifdef UNICODE
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastAccessTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastAccessTime);
		}
#else
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastAccessTime);
		}
#endif
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetLastWriteTime(CTime& refTime)
{
	ASSERT(m_hContext != NULL);
	

	if (m_pFoundInfo != NULL)
	{
#ifdef UNICODE
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastWriteTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftLastWriteTime);
		}
#else
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftLastWriteTime);
		}
#endif
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::GetCreationTime(CTime& refTime)
{
	ASSERT(m_hContext != NULL);
	

	if (m_pFoundInfo != NULL)
	{
#ifdef UNICODE
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftCreationTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATAW) m_pFoundInfo)->ftCreationTime);
		}
#else
		if (CTime::IsValidFILETIME(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime))
		{
			refTime = CTime(((LPWIN32_FIND_DATA) m_pFoundInfo)->ftCreationTime);
		}
#endif
		else
		{
			refTime = CTime();
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CXFileFindExImp::IsDots()
{
	ASSERT(m_hContext != NULL);
	

	// return TRUE if the file name is "." or ".." and
	// the file is a directory

	BOOL bResult = FALSE;
	if (m_pFoundInfo != NULL && IsDirectory())
	{		
#ifdef UNICODE
		LPWIN32_FIND_DATAW pFindData = (LPWIN32_FIND_DATAW) m_pFoundInfo;
#else
		LPWIN32_FIND_DATA pFindData = (LPWIN32_FIND_DATA) m_pFoundInfo;
#endif
		if (pFindData->cFileName[0] == '.')
		{
			if (pFindData->cFileName[1] == '\0' ||
				(pFindData->cFileName[1] == '.' &&
				 pFindData->cFileName[2] == '\0'))
			{
				bResult = TRUE;
			}
		}
	}

	return bResult;
}

BOOL CXFileFindExImp::FindNextFile()
{
	ASSERT(m_hContext != NULL);

	if (m_hContext == NULL)
		return FALSE;


	void* pTemp = m_pFoundInfo;
	m_pFoundInfo = m_pNextInfo;
	m_pNextInfo = pTemp;

#ifdef UNICODE
	return ::FindNextFileW(m_hContext, (LPWIN32_FIND_DATAW) m_pNextInfo);
#else
	return ::FindNextFile(m_hContext, (LPWIN32_FIND_DATA) m_pNextInfo);
#endif
}

CString CXFileFindExImp::GetFileURL()
{
	ASSERT(m_hContext != NULL);
	

	CString strResult("file://");
	strResult += GetFilePath();
	return strResult;
}

CString CXFileFindExImp::GetRoot()
{
	ASSERT(m_hContext != NULL);
	

	return m_strRoot;
}

CString CXFileFindExImp::GetFilePath()
{
	ASSERT(m_hContext != NULL);
	

	CString strResult = m_strRoot;
	LPCTSTR pszResult;
	LPCTSTR pchLast;
	pszResult = strResult;
	pchLast = _tcsdec( pszResult, pszResult+strResult.GetLength() );
    ENSURE(pchLast!=NULL);
	if ((*pchLast != _T('\\')) && (*pchLast != _T('/')))
		strResult += m_chDirSeparator;
	strResult += GetFileName();
	return strResult;
}

CString CXFileFindExImp::GetFileTitle()
{
	ASSERT(m_hContext != NULL);
	

	CString strFullName = GetFileName();
	CString strResult;

	Checked::tsplitpath_s(strFullName, NULL, 0, NULL, 0, 
		strResult.GetBuffer(X_MAX_FNAME), X_MAX_FNAME, NULL, 0);

	strResult.ReleaseBuffer();
	return strResult;
}

CString CXFileFindExImp::GetFileName()
{
	ASSERT(m_hContext != NULL);
	

	CString ret;

	if (m_pFoundInfo != NULL)
#ifdef UNICODE
		ret = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->cFileName;
#else
		ret = ((LPWIN32_FIND_DATA) m_pFoundInfo)->cFileName;
#endif

	return ret;
}

__uint64 CXFileFindExImp::GetLength()
{
	ASSERT(m_hContext != NULL);
	

   ULARGE_INTEGER nFileSize;

	if (m_pFoundInfo != NULL)
   {
#ifdef UNICODE
	  nFileSize.LowPart = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->nFileSizeLow;
	  nFileSize.HighPart = ((LPWIN32_FIND_DATAW) m_pFoundInfo)->nFileSizeHigh;
#else
	  nFileSize.LowPart = ((LPWIN32_FIND_DATA) m_pFoundInfo)->nFileSizeLow;
	  nFileSize.HighPart = ((LPWIN32_FIND_DATA) m_pFoundInfo)->nFileSizeHigh;
#endif
   }
   else
   {
	  nFileSize.QuadPart = 0;
   }

   return nFileSize.QuadPart;
}

long CXFileFindExImp::FindFileCount(const CString &strRoot, const CString &strFileType)
{
	CString strPath;

	if (strRoot.Right(1) == _P_FOLDER_PATH_SEPARATOR_)
	{
		strPath.Format(_T("%s*.%s"), strRoot, strFileType);
	}
	else
	{
		strPath.Format(_T("%s\\*.%s"), strRoot, strFileType);
	}

	BOOL b = FindFile(strPath);
	long nCount = 0;

	while (b)
	{
		b = FindNextFile();//20220704 zhouhj 改函数的功能是获取当前文件对象到m_pFoundInfo中,返回值标识获取后的下一个文件是否存在

		if( !IsDots() )
		{ 
			if(IsDirectory()) 
			{ 
			}
			else 
			{ 
				nCount++;
			} 
		} 
	}

	return nCount;
}


BOOL CXFileFindExImp::IsReadOnly()
{
	return MatchesMask(FILE_ATTRIBUTE_READONLY);
}

BOOL CXFileFindExImp::IsDirectory()
{
	return MatchesMask(FILE_ATTRIBUTE_DIRECTORY);
}

BOOL CXFileFindExImp::IsCompressed()
{
	return MatchesMask(FILE_ATTRIBUTE_COMPRESSED);
}

BOOL CXFileFindExImp::IsSystem()
{
	return MatchesMask(FILE_ATTRIBUTE_SYSTEM);
}

BOOL CXFileFindExImp::IsHidden()
{
	return MatchesMask(FILE_ATTRIBUTE_HIDDEN);
}

BOOL CXFileFindExImp::IsTemporary()
{
	return MatchesMask(FILE_ATTRIBUTE_TEMPORARY);
}

BOOL CXFileFindExImp::IsNormal()
{
	return MatchesMask(FILE_ATTRIBUTE_NORMAL);
}

BOOL CXFileFindExImp::IsArchived()
{
	return MatchesMask(FILE_ATTRIBUTE_ARCHIVE);
}

void CXFileFindExImp::ClearFileFilters()
{

}

void CXFileFindExImp::AddFileFilter(const CString &strFilter)
{

}

