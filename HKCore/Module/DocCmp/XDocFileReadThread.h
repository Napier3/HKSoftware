#pragma once

#include "../CriticalSection/SynCriticalSection.h"
#include "../DocCmp/DocXRead_Word.h"
#include "../DocCmp/DocXRead_WPS.h"
#include "../BaseClass/ThreadProgressInterface.h"

#define WM_XDOC_FILE_UPDATE  (WM_USER + 2357)

#define  XDOC_FILE_READ_MAX_FILE    10000
#define  XDOC_FILE_OPTR_BEGIN_READ  1
#define  XDOC_FILE_OPTR_FINISH_READ 2
#define  XDOC_FILE_OPTR_ADD         3

typedef struct _struct_xdoc_file_rd_mngr
{
	long nWriteIndex;
	long nReadIndex;
	long nMngrCount;
	char m_pszFileArray[XDOC_FILE_READ_MAX_FILE][1024];
}XDOC_FILE_READ_MNGR;

// CXDocFileReadThread

class CXDocFileReadThread : public CWinThread
{
	DECLARE_DYNCREATE(CXDocFileReadThread)

public:
	static void AddFileRead(const char*strFile);
	static void AddFileRead(const CString &strFile);
	static void PostXDocFilMsg(WPARAM wPara,LPARAM lPara);
	static CXDocFileReadThread* CreateXDocFileReadThread(CWnd *pMsgRcv, CThreadProgressInterface *pThreadProgressInterface);
	static XDOC_FILE_READ_MNGR* GetXDocFileMngr();
	static void ShowWordApp(long nShow);
	static void SetDocProg(const CString &strDocProg);

protected:
	CXDocFileReadThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CXDocFileReadThread();

	static CXDocFileReadThread *g_theDocFileReadThread;
	CAutoCriticSection m_oCriticSection;
	XDOC_FILE_READ_MNGR m_oXDocFileRead;

	CDocXReadInterface *m_pDocXRead_Prog;
	CWnd *m_pMsgRcvWnd;
	CThreadProgressInterface *m_pThreadProgressInterface;

	long m_nWordShowStateChanged;
	long m_nWordShow;
	CString m_strDocProg;
	long m_nDocProgChanged;

	void CloseDocProg();
	void CreateDocProg();
	void ReadFile();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();

protected:
	DECLARE_MESSAGE_MAP()
};


