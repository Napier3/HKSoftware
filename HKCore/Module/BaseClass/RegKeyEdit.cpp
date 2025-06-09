#include "StdAfx.h"
#include "RegKeyEdit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRegKeyEdit::CRegKeyEdit() throw() : 
m_hKey( NULL ), m_samWOW64(0)
{
}

CRegKeyEdit::CRegKeyEdit( CRegKeyEdit& key ) throw() :
m_hKey( NULL ), m_samWOW64(key.m_samWOW64)
{
	Attach( key.Detach() );
}

CRegKeyEdit::CRegKeyEdit(HKEY hKey) throw() :
m_hKey(hKey), m_samWOW64(0)
{
}

CRegKeyEdit::~CRegKeyEdit() throw()
{Close();}

CRegKeyEdit& CRegKeyEdit::operator=( CRegKeyEdit& key ) throw()
{
	if(m_hKey!=key.m_hKey)
	{
		Close();
		Attach( key.Detach() );
		m_samWOW64 = key.m_samWOW64;
	}
	return( *this );
}

CRegKeyEdit::operator HKEY() const throw()
{return m_hKey;}

HKEY CRegKeyEdit::Detach() throw()
{
	HKEY hKey = m_hKey;
	m_hKey = NULL;
	m_samWOW64 = 0;
	return hKey;
}

void CRegKeyEdit::Attach(HKEY hKey) throw()
{
	ASSERT(m_hKey == NULL);
	m_hKey = hKey;
	m_samWOW64 = 0;
}

LONG CRegKeyEdit::DeleteSubKey(LPCTSTR lpszSubKey) throw()
{
	ASSERT(m_hKey != NULL);

#if WINVER >= 0x0501
	typedef LSTATUS (WINAPI * PFNRegDeleteKeyEx)(HKEY, LPCTSTR, REGSAM, DWORD);
	static bool bInitialized = false;
	static PFNRegDeleteKeyEx pfnRegDeleteKeyEx = NULL;

	if (!bInitialized)
	{
		HMODULE hAdvapi32 = GetModuleHandle(_T("Advapi32.dll"));
		if (hAdvapi32 != NULL)
		{
#ifdef _UNICODE
			pfnRegDeleteKeyEx = (PFNRegDeleteKeyEx)GetProcAddress(hAdvapi32, "RegDeleteKeyExW");
#else
			pfnRegDeleteKeyEx = (PFNRegDeleteKeyEx)GetProcAddress(hAdvapi32, "RegDeleteKeyExA");
#endif	// _UNICODE
		}
		bInitialized = true;
	}

	if (pfnRegDeleteKeyEx != NULL)
	{
		return pfnRegDeleteKeyEx(m_hKey, lpszSubKey, m_samWOW64, 0);
	}

#endif	// WINVER

	return RegDeleteKey(m_hKey, lpszSubKey);
}

LONG CRegKeyEdit::DeleteValue(LPCTSTR lpszValue) throw()
{
	ASSERT(m_hKey != NULL);
	return RegDeleteValue(m_hKey, (LPTSTR)lpszValue);
}

LONG CRegKeyEdit::Close() throw()
{
	LONG lRes = ERROR_SUCCESS;
	if (m_hKey != NULL)
	{
		lRes = RegCloseKey(m_hKey);
		m_hKey = NULL;
	}
	m_samWOW64 = 0;
	return lRes;
}

LONG CRegKeyEdit::Flush() throw()
{
	ASSERT(m_hKey != NULL);

	return ::RegFlushKey(m_hKey);
}

LONG CRegKeyEdit::EnumKey(_In_ DWORD iIndex, _Out_z_cap_post_count_(*pnNameLength, *pnNameLength) LPTSTR pszName, _Inout_ LPDWORD pnNameLength, _Out_opt_ FILETIME* pftLastWriteTime) throw()
{
	FILETIME ftLastWriteTime;

	ASSERT(m_hKey != NULL);
	if (pftLastWriteTime == NULL)
	{
		pftLastWriteTime = &ftLastWriteTime;
	}

	return ::RegEnumKeyEx(m_hKey, iIndex, pszName, pnNameLength, NULL, NULL, NULL, pftLastWriteTime);
}

LONG CRegKeyEdit::NotifyChangeKeyValue(BOOL bWatchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, BOOL bAsync) throw()
{
	ASSERT(m_hKey != NULL);
	ASSERT((hEvent != NULL) || !bAsync);

	return ::RegNotifyChangeKeyValue(m_hKey, bWatchSubtree, dwNotifyFilter, hEvent, bAsync);
}

LONG CRegKeyEdit::Create(_In_ HKEY hKeyParent, _In_z_ LPCTSTR lpszKeyName,
							_In_opt_z_ LPTSTR lpszClass, _In_ DWORD dwOptions, _In_ REGSAM samDesired,
							_In_opt_ LPSECURITY_ATTRIBUTES lpSecAttr, _Out_opt_ LPDWORD lpdwDisposition) throw()
{
	ASSERT(hKeyParent != NULL);
	DWORD dw;
	HKEY hKey = NULL;
	LONG lRes = RegCreateKeyEx(hKeyParent, lpszKeyName, 0,
		lpszClass, dwOptions, samDesired, lpSecAttr, &hKey, &dw);
	if (lpdwDisposition != NULL)
		*lpdwDisposition = dw;
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		m_hKey = hKey;
#if WINVER >= 0x0501
		m_samWOW64 = samDesired & (KEY_WOW64_32KEY | KEY_WOW64_64KEY);
#endif
	}
	return lRes;
}

LONG CRegKeyEdit::Open(HKEY hKeyParent, LPCTSTR lpszKeyName, REGSAM samDesired) throw()
{
	ASSERT(hKeyParent != NULL);
	HKEY hKey = NULL;
	LONG lRes = RegOpenKeyEx(hKeyParent, lpszKeyName, 0, samDesired, &hKey);
	if (lRes == ERROR_SUCCESS)
	{
		lRes = Close();
		ASSERT(lRes == ERROR_SUCCESS);
		m_hKey = hKey;
#if WINVER >= 0x0501
		m_samWOW64 = samDesired & (KEY_WOW64_32KEY | KEY_WOW64_64KEY);
#endif
	}
	return lRes;
}

#pragma warning(push)
#pragma warning(disable: 4996)
LONG CRegKeyEdit::QueryValue(DWORD& dwValue, LPCTSTR lpszValueName)
{
	DWORD dwType = NULL;
	DWORD dwCount = sizeof(DWORD);
	LONG lRes = RegQueryValueEx(m_hKey, lpszValueName, NULL, &dwType,
		(LPBYTE)&dwValue, &dwCount);
	ASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_DWORD));
	ASSERT((lRes!=ERROR_SUCCESS) || (dwCount == sizeof(DWORD)));
	if (dwType != REG_DWORD)
		return ERROR_INVALID_DATA;
	return lRes;
}

#pragma warning(disable: 6053 6385)
LONG CRegKeyEdit::QueryValue(_Out_opt_z_cap_post_count_(*pdwCount, *pdwCount) LPTSTR pszValue, _In_opt_z_ LPCTSTR lpszValueName, _Inout_ DWORD* pdwCount)
{
	ATLENSURE(pdwCount != NULL);
	DWORD dwType = NULL;
	LONG lRes = RegQueryValueEx(m_hKey, lpszValueName, NULL, &dwType, (LPBYTE)pszValue, pdwCount);
	ASSERT((lRes!=ERROR_SUCCESS) || (dwType == REG_SZ) ||
		(dwType == REG_MULTI_SZ) || (dwType == REG_EXPAND_SZ));
	if (pszValue != NULL)
	{
		if(*pdwCount>0)
		{
			switch(dwType)
			{
			case REG_SZ:
			case REG_EXPAND_SZ:
				if ((*pdwCount) % sizeof(TCHAR) != 0 || pszValue[(*pdwCount) / sizeof(TCHAR) - 1] != 0)
				{
					pszValue[0]=_T('\0');
					return ERROR_INVALID_DATA;
				}
				break;
			case REG_MULTI_SZ:
				if ((*pdwCount) % sizeof(TCHAR) != 0 || (*pdwCount) / sizeof(TCHAR) < 1 || pszValue[(*pdwCount) / sizeof(TCHAR) -1] != 0 || (((*pdwCount) / sizeof(TCHAR))>1 && pszValue[(*pdwCount) / sizeof(TCHAR) - 2] != 0) )
				{
					pszValue[0]=_T('\0');
					return ERROR_INVALID_DATA;
				}
				break;
			default:
				// Ensure termination
				pszValue[0]=_T('\0');
				return ERROR_INVALID_DATA;
			}
		}
		else
		{
			// this is a blank one with no data yet
			// Ensure termination
			pszValue[0]=_T('\0');
		}
	}
	return lRes;
}
#pragma warning(pop)	

LONG CRegKeyEdit::QueryValue(LPCTSTR pszValueName, DWORD* pdwType, void* pData, ULONG* pnBytes) throw()
{
	ASSERT(m_hKey != NULL);

	return( ::RegQueryValueEx(m_hKey, pszValueName, NULL, pdwType, static_cast< LPBYTE >( pData ), pnBytes) );
}

LONG CRegKeyEdit::QueryDWORDValue(LPCTSTR pszValueName, DWORD& dwValue) throw()
{
	LONG lRes;
	ULONG nBytes;
	DWORD dwType;

	ASSERT(m_hKey != NULL);

	nBytes = sizeof(DWORD);
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(&dwValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_DWORD)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}
LONG CRegKeyEdit::QueryQWORDValue(LPCTSTR pszValueName, ULONGLONG& qwValue) throw()
{
	LONG lRes;
	ULONG nBytes;
	DWORD dwType;

	ASSERT(m_hKey != NULL);

	nBytes = sizeof(ULONGLONG);
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(&qwValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_QWORD)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

LONG CRegKeyEdit::QueryBinaryValue(LPCTSTR pszValueName, void* pValue, ULONG* pnBytes) throw()
{
	LONG lRes;
	DWORD dwType;

	ASSERT(pnBytes != NULL);
	ASSERT(m_hKey != NULL);

	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pValue),
		pnBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_BINARY)
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

#pragma warning(push)
#pragma warning(disable: 6053)
/* prefast noise VSW 496818 */
LONG CRegKeyEdit::QueryStringValue(LPCTSTR pszValueName, LPTSTR pszValue, ULONG* pnChars) throw()
{
	LONG lRes;
	DWORD dwType;
	ULONG nBytes;

	ASSERT(m_hKey != NULL);
	ASSERT(pnChars != NULL);

	nBytes = (*pnChars)*sizeof(TCHAR);
	*pnChars = 0;
	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue),
		&nBytes);

	if (lRes != ERROR_SUCCESS)
	{
		return lRes;
	}

	if(dwType != REG_SZ && dwType != REG_EXPAND_SZ)
	{
		return ERROR_INVALID_DATA;
	}

	if (pszValue != NULL)
	{
		if(nBytes!=0)
		{
#pragma warning(suppress:6385) // suppress noisy code analysis warning due to annotation on RegQueryValueEx
			if ((nBytes % sizeof(TCHAR) != 0) || (pszValue[nBytes / sizeof(TCHAR) -1] != 0))
			{
				return ERROR_INVALID_DATA;
			}
		}
		else
		{
			pszValue[0]=_T('\0');
		}
	}

	*pnChars = nBytes/sizeof(TCHAR);

	return ERROR_SUCCESS;
}
#pragma warning(pop)

#pragma warning(push)
#pragma warning(disable: 6053)
/* prefast noise VSW 496818 */
LONG CRegKeyEdit::QueryMultiStringValue(LPCTSTR pszValueName, LPTSTR pszValue, ULONG* pnChars) throw()
{
	LONG lRes;
	DWORD dwType;
	ULONG nBytes;

	ASSERT(m_hKey != NULL);
	ASSERT(pnChars != NULL);

	if (pszValue != NULL && *pnChars < 2)
		return ERROR_INSUFFICIENT_BUFFER;

	nBytes = (*pnChars)*sizeof(TCHAR);
	*pnChars = 0;

	lRes = ::RegQueryValueEx(m_hKey, pszValueName, NULL, &dwType, reinterpret_cast<LPBYTE>(pszValue),
		&nBytes);
	if (lRes != ERROR_SUCCESS)
		return lRes;
	if (dwType != REG_MULTI_SZ)
		return ERROR_INVALID_DATA;
	if (pszValue != NULL && (nBytes % sizeof(TCHAR) != 0 || nBytes / sizeof(TCHAR) < 1 || pszValue[nBytes / sizeof(TCHAR) -1] != 0 || ((nBytes/sizeof(TCHAR))>1 && pszValue[nBytes / sizeof(TCHAR) - 2] != 0)))
		return ERROR_INVALID_DATA;

	*pnChars = nBytes/sizeof(TCHAR);

	return ERROR_SUCCESS;
}
#pragma warning(pop)

LONG CRegKeyEdit::QueryGUIDValue(LPCTSTR pszValueName, GUID& guidValue) throw()
{
	TCHAR szGUID[64];
	LONG lRes;
	ULONG nCount;
	HRESULT hr;

	ASSERT(m_hKey != NULL);

	guidValue = GUID_NULL;

	nCount = 64;
	lRes = QueryStringValue(pszValueName, szGUID, &nCount);

	if (lRes != ERROR_SUCCESS)
		return lRes;

	if(szGUID[0] != _T('{'))
		return ERROR_INVALID_DATA;

	USES_CONVERSION_EX;
	LPOLESTR lpstr = T2OLE_EX(szGUID, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
	if(lpstr == NULL) 
		return E_OUTOFMEMORY;
#endif	

	hr = ::CLSIDFromString(lpstr, &guidValue);
	if (FAILED(hr))
		return ERROR_INVALID_DATA;

	return ERROR_SUCCESS;
}

LONG WINAPI CRegKeyEdit::SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName)
{
	ASSERT(lpszValue != NULL);
	CRegKeyEdit key;
	LONG lRes = key.Create(hKeyParent, lpszKeyName);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetStringValue(lpszValueName, lpszValue);
	return lRes;
}

LONG CRegKeyEdit::SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName) throw()
{
	ASSERT(lpszValue != NULL);
	CRegKeyEdit key;
	LONG lRes = key.Create(m_hKey, lpszKeyName, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_READ | KEY_WRITE | m_samWOW64);
	if (lRes == ERROR_SUCCESS)
		lRes = key.SetStringValue(lpszValueName, lpszValue);
	return lRes;
}

#pragma warning(push)
#pragma warning(disable: 4996)
LONG CRegKeyEdit::SetValue(DWORD dwValue, LPCTSTR pszValueName)
{
	ASSERT(m_hKey != NULL);
	return SetDWORDValue(pszValueName, dwValue);
}

LONG CRegKeyEdit::SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName, bool bMulti, int nValueLen)
{
	ATLENSURE(lpszValue != NULL);
	ASSERT(m_hKey != NULL);

	if (bMulti && nValueLen == -1)
		return ERROR_INVALID_PARAMETER;

	if (nValueLen == -1)
		nValueLen = lstrlen(lpszValue) + 1;

	DWORD dwType = bMulti ? REG_MULTI_SZ : REG_SZ;

	return ::RegSetValueEx(m_hKey, lpszValueName, NULL, dwType,
		reinterpret_cast<const BYTE*>(lpszValue), nValueLen*sizeof(TCHAR));
}
#pragma warning(pop)

LONG CRegKeyEdit::SetValue(LPCTSTR pszValueName, DWORD dwType, const void* pValue, ULONG nBytes) throw()
{
	ASSERT(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, dwType, static_cast<const BYTE*>(pValue), nBytes);
}

LONG CRegKeyEdit::SetBinaryValue(LPCTSTR pszValueName, const void* pData, ULONG nBytes) throw()
{
	ASSERT(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_BINARY, reinterpret_cast<const BYTE*>(pData), nBytes);
}

LONG CRegKeyEdit::SetDWORDValue(LPCTSTR pszValueName, DWORD dwValue) throw()
{
	ASSERT(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_DWORD, reinterpret_cast<const BYTE*>(&dwValue), sizeof(DWORD));
}

LONG CRegKeyEdit::SetQWORDValue(LPCTSTR pszValueName, ULONGLONG qwValue) throw()
{
	ASSERT(m_hKey != NULL);
	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_QWORD, reinterpret_cast<const BYTE*>(&qwValue), sizeof(ULONGLONG));
}

LONG CRegKeyEdit::SetStringValue(_In_opt_z_ LPCTSTR pszValueName, _In_opt_z_ LPCTSTR pszValue, _In_ DWORD dwType) throw()
{
	ASSERT(m_hKey != NULL);
	ATLENSURE_RETURN_VAL(pszValue != NULL, ERROR_INVALID_DATA);
	ASSERT((dwType == REG_SZ) || (dwType == REG_EXPAND_SZ));

	return ::RegSetValueEx(m_hKey, pszValueName, NULL, dwType, reinterpret_cast<const BYTE*>(pszValue), (lstrlen(pszValue)+1)*sizeof(TCHAR));
}

LONG CRegKeyEdit::SetMultiStringValue(LPCTSTR pszValueName, LPCTSTR pszValue) throw()
{
	LPCTSTR pszTemp;
	ULONG nBytes;
	ULONG nLength;

	ASSERT(m_hKey != NULL);
	ATLENSURE_RETURN_VAL(pszValue != NULL, ERROR_INVALID_DATA);

	// Find the total length (in bytes) of all of the strings, including the
	// terminating '\0' of each string, and the second '\0' that terminates
	// the list.
	nBytes = 0;
	pszTemp = pszValue;
	do
	{
		nLength = lstrlen(pszTemp)+1;
		pszTemp += nLength;
		nBytes += nLength*sizeof(TCHAR);
	} while (nLength != 1);

	return ::RegSetValueEx(m_hKey, pszValueName, NULL, REG_MULTI_SZ, reinterpret_cast<const BYTE*>(pszValue),
		nBytes);
}

LONG CRegKeyEdit::SetGUIDValue(LPCTSTR pszValueName, REFGUID guidValue) throw()
{
	OLECHAR szGUID[64];

	ASSERT(m_hKey != NULL);

	::StringFromGUID2(guidValue, szGUID, 64);

	USES_CONVERSION_EX;
	LPCTSTR lpstr = OLE2CT_EX(szGUID, _ATL_SAFE_ALLOCA_DEF_THRESHOLD);
#ifndef _UNICODE
	if(lpstr == NULL) 
		return E_OUTOFMEMORY;
#endif	
	return SetStringValue(pszValueName, lpstr);
}

LONG CRegKeyEdit::GetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd, LPDWORD pnBytes) throw()
{
	ASSERT(m_hKey != NULL);
	ASSERT(pnBytes != NULL);

	return ::RegGetKeySecurity(m_hKey, si, psd, pnBytes);
}

LONG CRegKeyEdit::SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) throw()
{
	ASSERT(m_hKey != NULL);
	ASSERT(psd != NULL);

	return ::RegSetKeySecurity(m_hKey, si, psd);
}

LONG CRegKeyEdit::RecurseDeleteKey(LPCTSTR lpszKey) throw()
{
	CRegKeyEdit key;
	LONG lRes = key.Open(m_hKey, lpszKey, KEY_READ | KEY_WRITE | m_samWOW64);
	if (lRes != ERROR_SUCCESS)
	{
		if (lRes != ERROR_FILE_NOT_FOUND && lRes != ERROR_PATH_NOT_FOUND)
		{
			ATLTRACE(atlTraceCOM, 0, _T("CRegKeyEdit::RecurseDeleteKey : Failed to Open Key %s(Error = %d)\n"), lpszKey, lRes);
		}
		return lRes;
	}
	FILETIME time;
	DWORD dwSize = 256;
	TCHAR szBuffer[256];
	while (RegEnumKeyEx(key.m_hKey, 0, szBuffer, &dwSize, NULL, NULL, NULL,
		&time)==ERROR_SUCCESS)
	{
		lRes = key.RecurseDeleteKey(szBuffer);
		if (lRes != ERROR_SUCCESS)
			return lRes;
		dwSize = 256;
	}
	key.Close();
	return DeleteSubKey(lpszKey);
}



BOOL CRegKeyEdit::OpenEx(LPCTSTR lpSubKey, HKEY hKeyParent)
{
	return Open(hKeyParent, lpSubKey, KEY_ALL_ACCESS);
}

BOOL CRegKeyEdit::CreateEx(LPCTSTR lpSubKey, HKEY hKeyParent)
{
	DWORD dw;
	return Create(hKeyParent, lpSubKey, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &dw);
}

BOOL CRegKeyEdit::OpenEx_User(LPCTSTR lpSubKey)
{
	return OpenEx(lpSubKey, HKEY_CURRENT_USER);
}

BOOL CRegKeyEdit::CreateEx_User(LPCTSTR lpSubKey)
{
	return CreateEx(lpSubKey, HKEY_CURRENT_USER);
}

BOOL CRegKeyEdit::OpenEx_LocalMachine(LPCTSTR lpSubKey)
{
	return OpenEx(lpSubKey, HKEY_LOCAL_MACHINE);
}

BOOL CRegKeyEdit::CreateEx_LocalMachine(LPCTSTR lpSubKey)
{
	return CreateEx(lpSubKey, HKEY_LOCAL_MACHINE);
}
