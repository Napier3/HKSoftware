#ifndef _CLogPrint_h__
#define _CLogPrint_h__

#define XLOGLEVEL_SUM				7
#define XLOGLEVEL_TRACE				0
#define XLOGLEVEL_WARNING			1
#define XLOGLEVEL_EXCEPTION		2
#define XLOGLEVEL_ERROR				3
#define XLOGLEVEL_INFOR				4
#define XLOGLEVEL_REALTIME_INFO				5

//2020-09-09  LIJUNQING  增加调试信息，用于远程或者仪器底层
#define XLOGLEVEL_DEBUG				6


#include "../BaseClass/TLinkList.h"
#include "../OSInterface/OSInterface.h"

#ifdef _PSX_IDE_QT_
#include "../CriticalSection/SynCriticalSection.h"
#endif

class CLogBase
{
public:
	CLogBase(){}
	virtual ~CLogBase()	{}

	virtual void EmptyLog(){};
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(LPVOID pPara, long nLevel, const CString &strMsg);

	virtual void LogString(long nLevel, const char *strMsg){};
	virtual void LogString(LPVOID pPara, long nLevel, const char* strMsg){};
};

class CLogPrint
{
private:
	CLogPrint(void);
	virtual ~CLogPrint(void);

	static long g_nLogPrintRef;
	CLogBase *m_pLog;

	CFile m_oLogFile;
	BOOL m_bLogFile;
	BOOL m_bLogFileCreate;

	void In_CreateLogFile(const CString &strFile);
	void In_CloseLogFile();
	void In_WriteMsg(const CString &strMsg);
	void In_WriteMsg(const char *strMsg);

public:
	static DWORD g_nOutputMode;
	static CLogPrint* g_pLogPrint;
	static CLogPrint* Create(CLogBase *pLog);
	static void Release();
	static void SetLog(CLogBase *pLog)		
	{	
		if (g_pLogPrint != NULL)
		{
			g_pLogPrint->m_pLog = pLog;	
		}
	};
	static CLogBase* GetLog()
	{
		ASSERT (g_pLogPrint != NULL);
		return g_pLogPrint->m_pLog;
	}

	static BOOL HasCreateLogFile();
	static void OnCreateLogFile();
	static void CreateLogFile(const CString &strFile=_T(""));
	static void CloseLogFile();

	static void LogString(long nLevel, const CString &strMsg);
	static void LogString(LPVOID pPara, long nLevel, const CString &strMsg);

// #ifdef _UNICODE
	static void LogFormatString(long nLevel, const wchar_t *strFormat, ...);
	static void LogFormatString(LPVOID pPara, long nLevel, const wchar_t *strFormat, ...);
// #else
	static void LogFormatString(long nLevel, const char *strFormat, ...);
	static void LogFormatString(LPVOID pPara, long nLevel, const char *strFormat, ...);
// #endif

	//2020-06-24  lijunqing
	static void LogBuffer(BYTE *pBuffer, long nBeginIndex, long nCount);

#ifdef _PSX_IDE_QT_
	CAutoCriticSection m_oCriticSection;
	CStringArray m_oLogStringList;
 	static void AppenLogdMsg(const CString &strMsg);
 	static void GetLogdMsg(CStringArray &oStrList);
#endif
};


//2015-3-21  增加可以同时输出到多个窗口，或者只输出与自己相关的对象窗口的功能
typedef CTLinkList<CLogBase> CLogBaseList;

class CLogBaseMngr : public CLogBase, public CLogBaseList
{
private:
	CLogBaseMngr(void);
	virtual ~CLogBaseMngr(void);

	static CLogBaseMngr *g_pLogBaseMngr;
	static long g_nLogBaseMngrRef;

public:
	static void RegisterLogBase(CLogBase *pLogBase);
	static void UnRegisterLogBase(CLogBase *pLogBase);

public:
	virtual void LogString(long nLevel, const CString &strMsg);
	virtual void LogString(LPVOID pPara, long nLevel, const CString &strMsg);

	virtual void LogString(long nLevel, const char *strMsg);
	virtual void LogString(LPVOID pPara, long nLevel, const char* strMsg);

};


extern CLogBase *g_pLogErrorSpy;
extern CLogBase *g_pLogTracePrint;
extern BOOL g_bShowRealTimeInforLevel;
extern long g_bOnlyWriteLogFile;

void log_WriteLogFileForDebug(const CString &strPath, BYTE *pBuffer, long nLen);

#endif // _CLogPrint_h__

