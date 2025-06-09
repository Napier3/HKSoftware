#ifndef _CRegKeyEdit_h__
#define _CRegKeyEdit_h__
/////////////////////////////////////////////////////////////////////////////
// CRegKeyEdit

class CRegKeyEdit
{
public:
	CRegKeyEdit() throw();
	CRegKeyEdit( CRegKeyEdit& key ) throw();
	explicit CRegKeyEdit(HKEY hKey) throw();
	virtual ~CRegKeyEdit() throw();

	CRegKeyEdit& operator=( CRegKeyEdit& key ) throw();

	// Attributes
public:
	operator HKEY() const throw();
	HKEY m_hKey;
	REGSAM m_samWOW64;

	// Operations
public:
	LONG SetValue(DWORD dwValue, LPCTSTR lpszValueName);
	LONG SetValue(LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL, bool bMulti = false, int nValueLen = -1);
	LONG SetValue(LPCTSTR pszValueName, DWORD dwType, const void* pValue, ULONG nBytes) throw();
	LONG SetGUIDValue(LPCTSTR pszValueName, REFGUID guidValue) throw();
	LONG SetBinaryValue(LPCTSTR pszValueName, const void* pValue, ULONG nBytes) throw();
	LONG SetDWORDValue(LPCTSTR pszValueName, DWORD dwValue) throw();
	LONG SetQWORDValue(LPCTSTR pszValueName, ULONGLONG qwValue) throw();
	LONG SetStringValue(_In_opt_z_ LPCTSTR pszValueName, _In_opt_z_ LPCTSTR pszValue, _In_ DWORD dwType = REG_SZ) throw();
	LONG SetMultiStringValue(LPCTSTR pszValueName, LPCTSTR pszValue) throw();

	LONG QueryValue(_Out_ DWORD& dwValue, _In_opt_z_ LPCTSTR lpszValueName);
	LONG QueryValue(_Out_opt_z_cap_post_count_(*pdwCount, *pdwCount) LPTSTR szValue, _In_opt_z_ LPCTSTR lpszValueName, _Inout_ DWORD* pdwCount);
	LONG QueryValue(_In_opt_z_ LPCTSTR pszValueName, DWORD* pdwType, void* pData, ULONG* pnBytes) throw();
	LONG QueryGUIDValue(_In_opt_z_ LPCTSTR pszValueName, GUID& guidValue) throw();
	LONG QueryBinaryValue(_In_opt_z_ LPCTSTR pszValueName, void* pValue, ULONG* pnBytes) throw();
	LONG QueryDWORDValue(_In_opt_z_ LPCTSTR pszValueName, DWORD& dwValue) throw();
	LONG QueryQWORDValue(_In_opt_z_ LPCTSTR pszValueName, ULONGLONG& qwValue) throw();
	LONG QueryStringValue(_In_opt_z_ LPCTSTR pszValueName, _Out_opt_z_cap_post_count_(*pnChars, *pnChars)  LPTSTR pszValue, _Inout_ ULONG* pnChars) throw();
	LONG QueryMultiStringValue(_In_opt_z_ LPCTSTR pszValueName, _Out_opt_z_cap_post_count_(*pnChars, *pnChars)  LPTSTR pszValue, _Inout_ ULONG* pnChars) throw();

	// Get the key's security attributes.
	LONG GetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd, LPDWORD pnBytes) throw();
	// Set the key's security attributes.
	LONG SetKeySecurity(SECURITY_INFORMATION si, PSECURITY_DESCRIPTOR psd) throw();

	LONG SetKeyValue(LPCTSTR lpszKeyName, LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL) throw();
	static LONG WINAPI SetValue(HKEY hKeyParent, LPCTSTR lpszKeyName,
		LPCTSTR lpszValue, LPCTSTR lpszValueName = NULL);

	// Create a new registry key (or open an existing one).
	LONG Create(_In_ HKEY hKeyParent, _In_z_ LPCTSTR lpszKeyName,
		_In_opt_z_ LPTSTR lpszClass = REG_NONE, _In_ DWORD dwOptions = REG_OPTION_NON_VOLATILE,
		_In_ REGSAM samDesired = KEY_READ | KEY_WRITE,
		_In_opt_ LPSECURITY_ATTRIBUTES lpSecAttr = NULL,
		_Out_opt_ LPDWORD lpdwDisposition = NULL) throw();
	// Open an existing registry key.
	LONG Open(HKEY hKeyParent, LPCTSTR lpszKeyName,
		REGSAM samDesired = KEY_READ | KEY_WRITE) throw();

	BOOL OpenEx(LPCTSTR lpSubKey, HKEY hKeyParent);
	BOOL CreateEx(LPCTSTR lpSubKey, HKEY hKeyParent);
	BOOL OpenEx_User(LPCTSTR lpSubKey);
	BOOL CreateEx_User(LPCTSTR lpSubKey);
	BOOL OpenEx_LocalMachine(LPCTSTR lpSubKey);
	BOOL CreateEx_LocalMachine(LPCTSTR lpSubKey);

	// Close the registry key.
	LONG Close() throw();
	// Flush the key's data to disk.
	LONG Flush() throw();

	// Detach the CRegKeyEdit object from its HKEY.  Releases ownership.
	HKEY Detach() throw();
	// Attach the CRegKeyEdit object to an existing HKEY.  Takes ownership.
	void Attach(HKEY hKey) throw();

	// Enumerate the subkeys of the key.
	LONG EnumKey(_In_ DWORD iIndex, _Out_z_cap_post_count_(*pnNameLength, *pnNameLength) LPTSTR pszName, _Inout_ LPDWORD pnNameLength, _Out_opt_ FILETIME* pftLastWriteTime = NULL) throw();
	LONG NotifyChangeKeyValue(BOOL bWatchSubtree, DWORD dwNotifyFilter, HANDLE hEvent, BOOL bAsync = TRUE) throw();

	LONG DeleteSubKey(LPCTSTR lpszSubKey) throw();
	LONG RecurseDeleteKey(LPCTSTR lpszKey) throw();
	LONG DeleteValue(LPCTSTR lpszValue) throw();
};

#endif //_CRegKeyEdit_h__