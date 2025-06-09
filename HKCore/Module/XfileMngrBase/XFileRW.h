#ifndef _XFileRW_h__
#define _XFileRW_h__



class CXFileRW : public CFile
{
public:
// Constructors
	CXFileRW();
	CXFileRW(HANDLE hFile);
	CXFileRW(LPCTSTR lpszFileName, UINT nOpenFlags);
	virtual ~CXFileRW();

public:
// Operations
	virtual BOOL Open(const CString &strFileName, UINT nOpenFlags,
		CFileException* pError = NULL);
};



#endif