#pragma once

#include "../../../Module/CriticalSection/SynCriticalSection.h"
#include "../../../Module/MemBuffer/CycleMemBuffer.h"
#include "../XLanguageResourcePp.h"
#include "PpGlobalDefine.h"

typedef struct struct_XPpPkgLog
{
	SYSTEMTIME tm;

#ifdef XPP_PKG_LOG_CYCLEBUF_MODE
	CYCLEMEMBUFFERPOS oBuffer;
#else
	BYTE *pBuffer;
	long nLen;
	long nMaxLen;  //lijunqing 2020-11-15
#endif

	long bRcv;
	CExBaseObject *pEngineData;
	long nSndRcvIndex;  //2025-3-14 lijunqing
}X_PP_PKG_LOG;

#define MAX_X_PP_PKG_LOG   1000
#define XPPPKGLOG_TIMER_ID  3269
#define XPPPKGLOG_TIMER_LONG  300
#define XPPPKGLOG_ENGINEDATA_COUNT  30

class CXPpPkgLogTool
{
private:
	CXPpPkgLogTool(void);
	virtual ~CXPpPkgLogTool(void);

	static CXPpPkgLogTool *g_pPpPkgLogTool;
	static long g_nPpPkgLogToolRef;
	
private:
	X_PP_PKG_LOG m_oXPpPkgLog[MAX_X_PP_PKG_LOG];
	long m_nPpPkgAddPos;
	long m_nPpPkgLogPos;
	long m_nPpPkgLogCount;
	CAutoCriticSection m_oAutoCriticSection;
	long m_nXPpLogBufferLen;
	char *m_pszXPpLogBuffer;
    long m_nXPpLogTxtLen;
	BOOL m_bProtocolSpy;

	CExBaseObject* m_pEngineDatas[XPPPKGLOG_ENGINEDATA_COUNT];

	BOOL m_bPpPkgLogWrite;
	CFile m_oPpPkgLogWrite;

	void SetXPpLogBufferLen(long nLen)
	{
		if (m_nXPpLogBufferLen < nLen)
		{
			delete m_pszXPpLogBuffer;
			m_pszXPpLogBuffer = new char [nLen];
			m_nXPpLogBufferLen = nLen;
		}
	}

	void XPpPkgLog_Free(X_PP_PKG_LOG &oXPpPkgLog);
	void XPpPkgLog_SetLen(X_PP_PKG_LOG &oXPpPkgLog, long nLen);

	void XPpPkgLog_Set(X_PP_PKG_LOG &oXPpPkgLog, BYTE* buffer, long len, BOOL bRcv);
	void XPpPkgLog_Set2(X_PP_PKG_LOG &oXPpPkgLog, BYTE* buffer, long len, BOOL bRcv, CExBaseObject *pEngineData);
	void In_AddPpPkgLog(BYTE* buffer, long len, BOOL bRcv);
	void In_AddPpPkgLog(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv);
	void In_AddPpPkgLog2(BYTE* buffer, long len, BOOL bRcv, CExBaseObject *pEngineData);
	void In_AddPpPkgLog2(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv, CExBaseObject *pEngineData, long nSndRcvIndex);
	void In_XPpPkgLog(X_PP_PKG_LOG &oXPpPkgLog);
    void In_XPpPkgLog(X_PP_PKG_LOG &oXPpPkgLog, CString &strMsg, BOOL bAddTitle, BOOL bAddNewLine);
    void In_XPpPkgLog_Hex(X_PP_PKG_LOG &oXPpPkgLog, BOOL bAddNewLine);
	void In_XPpPkgLog_Hex(BYTE *pBegin, BYTE *pEnd, char* &pLogBuffer);
	void In_XPpPkgLog();
    void In_GetPpPkgLogIndex(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
    void In_PpPkgLogStr(long nIndex, CString &strText, CString &strType);
	void In_CreateLogWriteFile();
	void In_PpPkgCloseDevice(CExBaseObject *pEngineData);

	void AddCloseDevice(CExBaseObject *pEngineData);
	void RemoveCloseDevice(CExBaseObject *pEngineData);
	bool HasCloseDevice(CExBaseObject *pEngineData);
public:
	static CXPpPkgLogTool* Create();
	static void Release();
	static void CreateLogWriteFile();

	static void AddPpPkgLog(BYTE* buffer, long len, BOOL bRcv)
	{
		g_pPpPkgLogTool->In_AddPpPkgLog(buffer, len, bRcv);
	}
	static void AddPpPkgLog(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv)
	{
		g_pPpPkgLogTool->In_AddPpPkgLog(oBufPos, bRcv);
	}

	static void AddPpPkgLog2(BYTE* buffer, long len, BOOL bRcv, CExBaseObject *pEngineData)
	{
		g_pPpPkgLogTool->In_AddPpPkgLog2(buffer, len, bRcv, pEngineData);
	}
	static void AddPpPkgLog2(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv, CExBaseObject *pEngineData, long nSndRcvIndex)
	{
		g_pPpPkgLogTool->In_AddPpPkgLog2(oBufPos, bRcv, pEngineData, nSndRcvIndex);
	}

	static void XPpPkgLog()
	{
		g_pPpPkgLogTool->In_XPpPkgLog();
	}

	static void SetProtocolSpy(BOOL bProtocolSpy=TRUE)
	{
		g_pPpPkgLogTool->m_bProtocolSpy = bProtocolSpy;
	}

    static void GetPpPkgLogIndex(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
    {
        if (g_pPpPkgLogTool == 0)
        {
            nBegin1 = -1;            nBegin2 = -1;            nEnd1 = -1;            nEnd2 = -1;
            return;
        }

        g_pPpPkgLogTool->In_GetPpPkgLogIndex(nBegin1, nEnd1, nBegin2, nEnd2);
    }

    static void PpPkgLogStr(long nIndex, CString &strText, CString &strType)
    {
        g_pPpPkgLogTool->In_PpPkgLogStr(nIndex, strText, strType);
    }
	static void PpPkgCloseDevice(CExBaseObject *pEngineData)
	{
		g_pPpPkgLogTool->AddCloseDevice(pEngineData);
		g_pPpPkgLogTool->In_PpPkgCloseDevice(pEngineData);
	}

	static void PpPkg_AddCloseDevice(CExBaseObject *pEngineData)
	{
		g_pPpPkgLogTool->AddCloseDevice(pEngineData);
		g_pPpPkgLogTool->In_PpPkgCloseDevice(pEngineData);
	}
	static void PpPkg_RemoveCloseDevice(CExBaseObject *pEngineData)
	{
		g_pPpPkgLogTool->RemoveCloseDevice(pEngineData);
	}
};
