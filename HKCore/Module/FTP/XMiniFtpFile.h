#pragma once

#define WM_RECEIVE_FILE   (WM_USER + 2332)

class CXMiniFtpFile : public CExBaseObject
{
public:
	CXMiniFtpFile();
	virtual ~CXMiniFtpFile();

};

class CXMiniFtpFileMngr : public CExBaseList
{
public:
	CXMiniFtpFileMngr();
	virtual ~CXMiniFtpFileMngr();

	void AttachMainWnd(CWnd *pMainWnd);
	CXMiniFtpFile* AddFile(const CString &strFile);

protected:
	CWnd *m_pMainWnd;

};

