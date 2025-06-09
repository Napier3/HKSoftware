#if !defined(_X_FileFind_H__)
#define _X_FileFind_H__

#include "XFileFindBase.h"

class CXFileFindEx
{
public:
	CXFileFindEx();
	virtual ~CXFileFindEx();

// Attributes
public:
    virtual __uint64 GetLength() const;
	virtual CString GetFileName() const;
	virtual CString GetFilePath() const;
	virtual CString GetFileTitle() const;
	virtual CString GetFileURL() const;
	virtual CString GetRoot() const;

	virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetCreationTime(FILETIME* pTimeStamp) const;
	virtual BOOL GetLastWriteTime(CTime& refTime) const;
	virtual BOOL GetLastAccessTime(CTime& refTime) const;
	virtual BOOL GetCreationTime(CTime& refTime) const;

	virtual BOOL MatchesMask(DWORD dwMask) const;

	virtual BOOL IsDots() const;
	// these aren't virtual because they all use MatchesMask(), which is
	BOOL IsReadOnly() const;
	BOOL IsDirectory() const;
	BOOL IsCompressed() const;
	BOOL IsSystem() const;
	BOOL IsHidden() const;
	BOOL IsTemporary() const;
	BOOL IsNormal() const;
	BOOL IsArchived() const;

// Operations
	void Close();
	virtual BOOL FindFile(const CString &strName, DWORD dwUnused = 0);
	virtual BOOL FindNextFile();

	virtual long FindFileCount(const CString &strRoot, const CString &strFileType);

    virtual void ClearFileFilters();
    virtual void AddFileFilter(const CString &strFilter);
//2020-12-1  lijunqing  
public:
	CXFileFindBase *m_pContext;
};


#endif
