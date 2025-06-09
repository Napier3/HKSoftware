#if !defined(_X_FileFindImp_H__)
#define _X_FileFindImp_H__

#include "../XFileFindBase.h"


class CXFileFindExImp : public CXFileFindBase
{
public:
	CXFileFindExImp();
	virtual ~CXFileFindExImp();

	virtual __uint64 GetLength();
	virtual CString GetFileName();
	virtual CString GetFilePath();
	virtual CString GetFileTitle();
	virtual CString GetFileURL();
	virtual CString GetRoot();

	virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp);
	virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp);
	virtual BOOL GetCreationTime(FILETIME* pTimeStamp);
	virtual BOOL GetLastWriteTime(CTime& refTime);
	virtual BOOL GetLastAccessTime(CTime& refTime);
	virtual BOOL GetCreationTime(CTime& refTime);

	virtual BOOL MatchesMask(DWORD dwMask);

	virtual BOOL IsDots();
	// these aren't virtual because they all use MatchesMask(), which is
	virtual BOOL IsReadOnly();
	virtual BOOL IsDirectory();
	virtual BOOL IsCompressed();
	virtual BOOL IsSystem();
	virtual BOOL IsHidden();
	virtual BOOL IsTemporary();
	virtual BOOL IsNormal();
	virtual BOOL IsArchived();

	// Operations
	virtual void Close();
	virtual BOOL FindFile(const CString &strName, DWORD dwUnused = 0);
	virtual BOOL FindNextFile();

	virtual long FindFileCount(const CString &strRoot, const CString &strFileType);

	virtual void ClearFileFilters();
	virtual void AddFileFilter(const CString &strFilter);

protected:
	virtual void CloseContext()
	{
		::FindClose(m_hContext);
	}

// Implementation
protected:
	void* m_pFoundInfo;
	void* m_pNextInfo;
	HANDLE m_hContext;

	CString m_strRoot;
	TCHAR m_chDirSeparator;     // not '\\' for Internet classes
};



#endif //_X_FileFindImp_H__