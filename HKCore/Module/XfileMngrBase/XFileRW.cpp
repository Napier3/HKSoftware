#include "stdafx.h"
#include "XFileRW.h"

////////////////////////////////////////////////////////////////////////////
// CXFileRW implementation
CXFileRW::CXFileRW()
: CFile()
{
	
}

CXFileRW::CXFileRW(HANDLE hFile)
: CFile(hFile)
{
	
}

CXFileRW::CXFileRW(LPCTSTR lpszFileName, UINT nOpenFlags)
: CFile(lpszFileName, nOpenFlags)
{

}

CXFileRW::~CXFileRW()
{

}

BOOL CXFileRW::Open(const CString &strFileName, UINT nOpenFlags,
	CFileException* pException)
{
	ASSERT_VALID(this);

	ASSERT(pException == NULL ||
		AfxIsValidAddress(pException, sizeof(CFileException)));
	ASSERT((nOpenFlags & typeText) == 0);   // text mode not supported

	// shouldn't open an already open file (it will leak)
	ASSERT(m_hFile == INVALID_HANDLE_VALUE);

	// CXFileRW objects are always binary and CreateFile does not need flag
	nOpenFlags &= ~(UINT)typeBinary;

	m_bCloseOnDelete = FALSE;

	m_hFile = INVALID_HANDLE_VALUE;
	m_strFileName.Empty();

// 	if (lpszFileName != NULL && SUCCEEDED(StringCchLength(lpszFileName, _MAX_PATH, NULL)) )
// 	{
// 		if( _AfxFullPath2(szTemp, lpszFileName,pException) == FALSE )
// 			return FALSE;
// 	}
// 	else
	if (strFileName.GetLength() <= 3)
	{
		return FALSE; // path is too long
	}
		
	m_strFileName = strFileName;
	ASSERT(shareCompat == 0);

	// map read/write mode
	ASSERT((modeRead|modeWrite|modeReadWrite) == 3);
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
		dwAccess = GENERIC_READ | GENERIC_WRITE;
		break;
	default:
		ASSERT(FALSE);  // invalid share mode
	}

	// map share mode
	DWORD dwShareMode = 0;
	switch (nOpenFlags & 0x70)    // map compatibility mode to exclusive
	{
	default:
		ASSERT(FALSE);  // invalid share mode?
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
		dwShareMode = FILE_SHARE_WRITE | FILE_SHARE_READ;
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

	// special system-level access flags

	// Random access and sequential scan should be mutually exclusive
	ASSERT((nOpenFlags&(osRandomAccess|osSequentialScan)) != (osRandomAccess|
		osSequentialScan) );

	DWORD dwFlags = FILE_ATTRIBUTE_NORMAL;
	if (nOpenFlags & osNoBuffer)
		dwFlags |= FILE_FLAG_NO_BUFFERING;
	if (nOpenFlags & osWriteThrough)
		dwFlags |= FILE_FLAG_WRITE_THROUGH;
	if (nOpenFlags & osRandomAccess)
		dwFlags |= FILE_FLAG_RANDOM_ACCESS;
	if (nOpenFlags & osSequentialScan)
		dwFlags |= FILE_FLAG_SEQUENTIAL_SCAN;

	// attempt file creation

#ifdef UNICODE
	HANDLE hFile = ::CreateFileW(strFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, dwFlags, NULL);
#else
	BSTR bstrFileName = strFileName.AllocSysString();
	HANDLE hFile = ::CreateFileW(bstrFileName, dwAccess, dwShareMode, &sa,
		dwCreateFlag, dwFlags, NULL);
	::SysFreeString(bstrFileName);
#endif

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	m_hFile = hFile;
	m_bCloseOnDelete = TRUE;

	return TRUE;
}
