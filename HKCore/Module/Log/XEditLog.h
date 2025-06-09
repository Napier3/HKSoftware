
#pragma once



class CXEditLog
{
private:
	CXEditLog();
	virtual ~CXEditLog();

	static CXEditLog *g_pXEditLog;
	static long g_nXEditLogRef;

public:
	static void Create();
	static void Release();

	static void LogString(long nLevel, const CString &strLog, BOOL bTime = FALSE);
	static void AttachLogWnd(unsigned long hLogWnd);

private:
	void In_LogString(long nLevel, const CString &strLog, BOOL bTime = FALSE);
	void Attach(HWND hWnd);
	void Detach();

	CEdit m_wndEdit;
};
