#ifndef _ATLFILE_H__
#define _ATLFILE_H__

class CAtlFile
{
public:
// Flag values
	enum OpenFlags {
		modeRead =          0x0000,
		modeWrite =         0x0001,
		modeReadWrite =     0x0002,
		shareCompat =       0x0000,
		shareExclusive =    0x0010,
		shareDenyWrite =    0x0020,
		shareDenyRead =     0x0030,
		shareDenyNone =     0x0040,
		modeNoInherit =     0x0080,
		modeCreate =        0x1000,
		modeNoTruncate =    0x2000,
		typeText =          0x4000, // typeText and typeBinary are used in
		typeBinary =   (int)0x8000 // derived classes only
		};

	enum Attribute {
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20
		};

	enum SeekPosition { begin = 0x0, current = 0x1, end = 0x2 };

	enum { hFileNull = -1 };

// Constructors
	CAtlFile();
	CAtlFile(int hFile);
	CAtlFile(LPCTSTR lpszFileName, UINT nOpenFlags);

// Attributes
	UINT m_hFile;
	operator HFILE() const;

	virtual DWORD GetPosition() const;
//	virtual LPCTSTR GetFileName() const;
//	virtual LPCTSTR GetFileTitle() const;
//	virtual LPCTSTR GetFilePath() const;
	virtual void SetFilePath(LPCTSTR lpszNewName);

	virtual BOOL Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	virtual BOOL Open(const CComBSTR &strFileName, UINT nOpenFlags);
	virtual BOOL Open(BSTR strFileName, UINT nOpenFlags);
	
// Operations
	static void PASCAL Rename(LPCTSTR lpszOldName,
				LPCTSTR lpszNewName);
	static void PASCAL Remove(LPCTSTR lpszFileName);

	DWORD SeekToEnd();
	void SeekToBegin();

	// backward compatible ReadHuge and WriteHuge
	DWORD ReadHuge(void* lpBuffer, DWORD dwCount);
	void WriteHuge(const void* lpBuffer, DWORD dwCount);

// Overridables
	virtual CAtlFile* Duplicate() const;

	virtual LONG Seek(LONG lOff, UINT nFrom);
	virtual void SetLength(DWORD dwNewLen);
	virtual DWORD GetLength() const;

	virtual UINT Read(void* lpBuf, UINT nCount);
	virtual void Write(const void* lpBuf, UINT nCount);

	virtual void LockRange(DWORD dwPos, DWORD dwCount);
	virtual void UnlockRange(DWORD dwPos, DWORD dwCount);

	virtual void Abort();
	virtual void Flush();
	virtual void Close();

// Implementation
public:
	virtual ~CAtlFile();
	enum BufferCommand { bufferRead, bufferWrite, bufferCommit, bufferCheck };
	virtual UINT GetBufferPtr(UINT nCommand, UINT nCount = 0,
		void** ppBufStart = NULL, void** ppBufMax = NULL);

protected:
	BOOL m_bCloseOnDelete;
//	TCHAR m_strFileName[MAX_PATH];
};

// CAtlFile
inline CAtlFile::operator HFILE() const
{ return m_hFile; }
inline DWORD CAtlFile::ReadHuge(void* lpBuffer, DWORD dwCount)
{ return (DWORD)Read(lpBuffer, (UINT)dwCount); }
inline void CAtlFile::WriteHuge(const void* lpBuffer, DWORD dwCount)
{ Write(lpBuffer, (UINT)dwCount); }
inline DWORD CAtlFile::SeekToEnd()
{ return Seek(0, CAtlFile::end); }
inline void CAtlFile::SeekToBegin()
{ Seek(0, CAtlFile::begin); }
inline void CAtlFile::SetFilePath(LPCTSTR lpszNewName)
{
//	_tcscpy(m_strFileName, lpszNewName);
}

#endif

