#if !defined(_X_FileFindBase_H__)
#define _X_FileFindBase_H__

#include "../OSInterface/OSInterface.h"

#define  X_MAX_PATH   8192
#define  X_MAX_DIR    8192 /* max. length of path component */
#define  X_MAX_FNAME  8192 /* max. length of file name component */
#define  X_MAX_EXT    8192 /* max. length of extension component */

//2020-12-1  lijunqing  
class CXFileFindBase
{
public:
	CXFileFindBase()	{}
	virtual ~CXFileFindBase()	{}
	// Attributes
public:
    virtual __uint64 GetLength() = 0;
	virtual CString GetFileName() = 0;
	virtual CString GetFilePath() = 0;
	virtual CString GetFileTitle() = 0;
	virtual CString GetFileURL() = 0;
	virtual CString GetRoot() = 0;

	virtual BOOL GetLastWriteTime(FILETIME* pTimeStamp) = 0;
	virtual BOOL GetLastAccessTime(FILETIME* pTimeStamp) = 0;
	virtual BOOL GetCreationTime(FILETIME* pTimeStamp) = 0;
	virtual BOOL GetLastWriteTime(CTime& refTime) = 0;
	virtual BOOL GetLastAccessTime(CTime& refTime) = 0;
	virtual BOOL GetCreationTime(CTime& refTime) = 0;

	virtual BOOL MatchesMask(DWORD dwMask) = 0;

	virtual BOOL IsDots() = 0;
	// these aren't virtual because they all use MatchesMask(), which is
	virtual BOOL IsReadOnly() = 0;
	virtual BOOL IsDirectory() = 0;
	virtual BOOL IsCompressed() = 0;
	virtual BOOL IsSystem() = 0;
	virtual BOOL IsHidden() = 0;
	virtual BOOL IsTemporary() = 0;
	virtual BOOL IsNormal() = 0;
	virtual BOOL IsArchived() = 0;

	// Operations
	virtual void Close() = 0;
	virtual BOOL FindFile(const CString &strName, DWORD dwUnused = 0) = 0;
	virtual BOOL FindNextFile() = 0;

	virtual long FindFileCount(const CString &strRoot, const CString &strFileType) = 0;

    virtual void ClearFileFilters() = 0;
    virtual void AddFileFilter(const CString &strFilter) = 0;
};

#endif

