#include "stdafx.h"
#include "LogPrint.h"

#include "../API/FileApi.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLogBase *g_pLogErrorSpy = NULL;
CLogBase *g_pLogTracePrint = NULL;
BOOL g_bShowRealTimeInforLevel = FALSE;
long g_bOnlyWriteLogFile = 0;

#define g_lenLogGloalDest   1024000
#define g_lenLogGloalDestCount   50
#define g_lenLogGloalDestOne   20480
long g_nLogPrintBuffIndex = 0;
long g_nLogPrintBuffIndex2 = 0;

#ifdef _PSX_IDE_QT_

char g_strLogGloalDest_Char[g_lenLogGloalDest];
#else

wchar_t g_strLogGloalDest[g_lenLogGloalDest];
char g_strLogGloalDest_Char[g_lenLogGloalDest];

wchar_t* log_get_logprint_buffer_unicode()
{
	long nIndex = g_nLogPrintBuffIndex2;
	g_nLogPrintBuffIndex2++;

	if (g_nLogPrintBuffIndex2 >= g_lenLogGloalDestCount)
	{
		g_nLogPrintBuffIndex2 = 0;
	}

	return g_strLogGloalDest+ nIndex * g_lenLogGloalDestOne;
}

#endif

char* log_get_logprint_buffer()
{
	long nIndex = g_nLogPrintBuffIndex;
	g_nLogPrintBuffIndex++;

	if (g_nLogPrintBuffIndex >= g_lenLogGloalDestCount)
	{
		g_nLogPrintBuffIndex = 0;
	}

	return g_strLogGloalDest_Char+ nIndex * g_lenLogGloalDestOne;
}


//////////////////////////////////////////////////////////////////////////
//
void CLogBase::LogString(long nLevel, const CString &strMsg)
{
#ifndef _PSX_IDE_QT_
    TRACE(L"%s\r\n", strMsg);
#endif
}

void CLogBase::LogString(LPVOID pPara, long nLevel, const CString &strMsg)
{
#ifndef _PSX_IDE_QT_
    TRACE(L"%s\r\n", strMsg);
#endif
}

void CLogBase::LogString(long nLevel, const char *strMsg){};
void CLogBase::LogString(LPVOID pPara, long nLevel, const char* strMsg){};

CLogPrint::CLogPrint(void)
{
	m_pLog = NULL;
	m_bLogFile = FALSE;
	m_bLogFileCreate = FALSE;
	m_bSaveLogFileEveryLog = FALSE;
}

CLogPrint::~CLogPrint(void)
{
	if(m_pLog != NULL)
	{
		delete m_pLog;
		m_pLog = NULL;
	}

	CloseLogFile();
}

DWORD CLogPrint::g_nOutputMode = 1;
long CLogPrint::g_nLogPrintRef = 0;
CLogPrint* CLogPrint::g_pLogPrint = NULL;
	
CLogPrint* CLogPrint::Create(CLogBase *pLog)
{
	ASSERT (pLog != NULL);
	g_nLogPrintRef++;

	if (g_nLogPrintRef == 1)
	{
		g_pLogPrint = new CLogPrint;
		g_pLogPrint->m_pLog = pLog;
	}
	else
	{
		ASSERT (pLog == g_pLogPrint->m_pLog);
	}

	return g_pLogPrint;
}

void CLogPrint::Release()
{
	g_nLogPrintRef--;
	
	if (g_nLogPrintRef == 0)
	{
		delete g_pLogPrint;
		g_pLogPrint = NULL;
	}
}

void CLogPrint::In_CreateLogFile(const CString &strFile)
{
	if (m_bLogFile)
	{
		return;
	}

	CString strTemp;

	if (strFile.GetLength() <= 3)
	{
		strTemp = _P_GetBinPath();
		strTemp += _P_GetMoudleFileName();
		strTemp += _T(".txt");
	}
	else
	{
		strTemp = strFile;
	}

	BOOL bCreateNew = TRUE;

	if (IsFileExist(strTemp))
	{
		long nSize = file_GetFileSize(strTemp);

		if (nSize < 10485760)//10M
		{
			bCreateNew = FALSE;
		}
	}

	if (bCreateNew)
	{
		m_bLogFile = m_oLogFile.Open(strTemp, CFile::modeCreate | CFile::modeWrite);
	}
	else
	{
#ifdef _PSX_IDE_QT_
		m_bLogFile = m_oLogFile.Open(strTemp, CFile::modeNoTruncate/*modeWrite*/);
#else
		m_bLogFile = m_oLogFile.Open(strTemp, CFile::modeWrite);
#endif

		if (m_bLogFile)
		{
			m_oLogFile.SeekToEnd();
		}
	}
}

void CLogPrint::In_CloseLogFile()
{
	if (m_bLogFile)
	{
		m_bLogFile = FALSE;
		m_oLogFile.Close();
	}
}

void CLogPrint::In_WriteMsg(const CString &strMsg)
{
	if (!m_bLogFile)
	{
		return;
	}

	char pszTime[64];
	GetCurrSystemtimeString2_Short(pszTime, TRUE);
	m_oLogFile.Write(pszTime, strlen(pszTime));

#ifdef _UNICODE
	char *pszText = NULL;
	long nLen = CString_to_char(strMsg, &pszText);
	m_oLogFile.Write(pszText, nLen);
	delete pszText;
#else
    m_oLogFile.Write(strMsg.GetString(), strMsg.GetLength());
#endif

	m_oLogFile.Write("\r\n", 2);

	if (m_bSaveLogFileEveryLog)
	{
		CloseLogFile();
		CreateLogFile();
	}
}

void CLogPrint::In_WriteMsg(const char *strMsg)
{
	CString strText;
	strText = strMsg;
	In_WriteMsg(strText);
}

BOOL CLogPrint::HasCreateLogFile()
{
	if (g_pLogPrint == NULL)
	{
		return FALSE;
	}
	else
	{
		return g_pLogPrint->m_bLogFileCreate;
	}
}

void CLogPrint::OnCreateLogFile()
{
	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_bLogFileCreate)
	{
		g_pLogPrint->m_bLogFileCreate = FALSE;
		CloseLogFile();
	}
	else
	{
		g_pLogPrint->m_bLogFileCreate = TRUE;
		CreateLogFile();
	}
}

void CLogPrint::CreateLogFile(const CString &strFile)
{
	if (g_pLogPrint == NULL)
	{
		return;
	}

	g_pLogPrint->In_CreateLogFile(strFile);
}

void CLogPrint::CloseLogFile()
{
	if (g_pLogPrint == NULL)
	{
		return;
	}

	g_pLogPrint->In_CloseLogFile();
}

void CLogPrint::LogString(long nLevel, const CString &strMsg)
{
	//ASSERT (g_pLogPrint != NULL);
	if (!g_nOutputMode)
	{
		return;
	}

	if (!g_nLogPrintRef)
	{
		return;
	}

	if (g_pLogPrint == NULL)
	{
		return;
	}
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
	}
}


void CLogPrint::LogString(LPVOID pPara, long nLevel, const CString &strMsg)
{
	ASSERT (g_pLogPrint != NULL);
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
	}
}

void CLogPrint::LogFormatString(long nLevel, CString strFormat, ...)
{
    if (!g_nOutputMode)
    {
        return;
    }

    if (!g_nLogPrintRef)
    {
        return;
    }

    if (g_pLogPrint == NULL)
    {
        return;
    }

    ASSERT (g_pLogPrint->m_pLog != NULL);

    if (g_pLogPrint->m_pLog == NULL)
    {
        return;
    }

    const char *pszFormat = strFormat.GetString();
    CString strMsg;
    va_list argList;

#ifdef _PSX_IDE_QT_
    va_start( argList, pszFormat );
    str_formart_v(pszFormat, argList, strMsg);
    va_end( argList );
#else
    char *pBuffer = log_get_logprint_buffer();
    memset(pBuffer, 0, sizeof(char)*g_lenLogGloalDestOne);

    va_start( argList, pszFormat );
    vsprintf_s( pBuffer, g_lenLogGloalDestOne, pszFormat, argList );
    va_end( argList );

    strMsg = pBuffer;
#endif


    g_pLogPrint->In_WriteMsg(strMsg);

    if (g_bOnlyWriteLogFile)
    {
        return;
    }

    if (nLevel == XLOGLEVEL_REALTIME_INFO)
    {
        if (g_bShowRealTimeInforLevel)
        {
            g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
        }
    }
    else
    {
        g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
    }
}

void CLogPrint::LogFormatString(LPVOID pPara, long nLevel, CString strFormat, ...)
{
    if (!g_nOutputMode)
    {
        return;
    }

    if (!g_nLogPrintRef)
    {
        return;
    }

    if (g_pLogPrint == NULL)
    {
        return;
    }

    ASSERT (g_pLogPrint->m_pLog != NULL);

    if (g_pLogPrint->m_pLog == NULL)
    {
        return;
    }

    const char *pszFormat = strFormat.GetString();
    CString strMsg;
    va_list argList;

#ifdef _PSX_IDE_QT_
    va_start( argList, pszFormat );
    str_formart_v(pszFormat, argList, strMsg);
    va_end( argList );
#else
    char *pBuffer = log_get_logprint_buffer();
    memset(pBuffer, 0, sizeof(char)*g_lenLogGloalDestOne);

    va_start( argList, pszFormat );
    vsprintf_s( pBuffer, g_lenLogGloalDestOne, pszFormat, argList );
    va_end( argList );

    strMsg = pBuffer;
#endif


    g_pLogPrint->In_WriteMsg(strMsg);

    if (g_bOnlyWriteLogFile)
    {
        return;
    }

    if (nLevel == XLOGLEVEL_REALTIME_INFO)
    {
        if (g_bShowRealTimeInforLevel)
        {
            g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
        }
    }
    else
    {
        g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
    }
}

// #ifdef _UNICODE

void CLogPrint::LogFormatString(long nLevel, const wchar_t *strFormat, ...)
{
//	ASSERT (g_pLogPrint != NULL);

	if (!g_nOutputMode)
	{
		return;
	}

	if (!g_nLogPrintRef)
	{
		return;
	}

	if (g_pLogPrint == NULL)
	{
		return;
	}

	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

#ifdef _PSX_IDE_QT_
	CString strMsg;
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strMsg);
	va_end( argList );
#else
	CString strMsg;
	wchar_t *pBuff = log_get_logprint_buffer_unicode();
	memset(pBuff, 0, sizeof(wchar_t)*g_lenLogGloalDestOne);
	*pBuff = 0;

	va_list argList;
	va_start( argList, strFormat );
	vswprintf_s( pBuff, g_lenLogGloalDestOne, strFormat, argList );
	va_end( argList );
	strMsg = pBuff;
#endif


	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
	}
}

void CLogPrint::LogFormatString(LPVOID pPara, long nLevel, const wchar_t *strFormat, ...)
{
	ASSERT (g_pLogPrint != NULL);
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

#ifdef _PSX_IDE_QT_
	CString strMsg;
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strMsg);
	va_end( argList );
#else
	wchar_t *pBuff = log_get_logprint_buffer_unicode();
	memset(pBuff, 0, sizeof(wchar_t)*g_lenLogGloalDestOne);
	*pBuff = 0;

	va_list argList;
	va_start( argList, strFormat );
	vswprintf_s( pBuff, g_lenLogGloalDestOne, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = pBuff;
#endif

	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
	}
}

// #else
void CLogPrint::LogFormatString(long nLevel, const char *strFormat, ...)
{
//	ASSERT (g_pLogPrint != NULL);
	if (g_pLogPrint == NULL)
	{
		return;
	}

	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

#ifdef _PSX_IDE_QT_
	CString strMsg;
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strMsg);
	va_end( argList );
#else
	char *pBuffer = log_get_logprint_buffer();
	memset(pBuffer, 0, sizeof(char)*g_lenLogGloalDestOne);

	va_list argList;
	va_start( argList, strFormat );
	vsprintf_s( pBuffer, g_lenLogGloalDestOne, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = pBuffer;
#endif

	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(nLevel, strMsg);
	}
}

void CLogPrint::LogFormatString(LPVOID pPara, long nLevel, const char *strFormat, ...)
{
	ASSERT (g_pLogPrint != NULL);
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

#ifdef _PSX_IDE_QT_
	CString strMsg;
	va_list argList;
	va_start( argList, strFormat );
	str_formart_v(strFormat, argList, strMsg);
	va_end( argList );
#else
	char *pBuffer = log_get_logprint_buffer();
	memset(pBuffer, 0, sizeof(char)*g_lenLogGloalDestOne);
	*pBuffer = 0;

	va_list argList;
	va_start( argList, strFormat );
	vsprintf_s( pBuffer, g_lenLogGloalDestOne, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = pBuffer;
#endif

	g_pLogPrint->In_WriteMsg(strMsg);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	if (nLevel == XLOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(pPara, nLevel, strMsg);
	}
}

//2020-06-24  lijunqing
void CLogPrint::LogBuffer(BYTE *pBuffer, long nBeginIndex, long nCount)
{
#ifdef _PSX_IDE_QT_
	if (nCount == 0)
	{
		return;
	}

	ASSERT (g_pLogPrint != NULL);
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	char *p = log_get_logprint_buffer();
	BYTE *pTemp= pBuffer + nBeginIndex;
	BYTE *pEnd = pTemp + nCount;
	long nIndex = 0;

	ValueToHex(pTemp, nCount, p, FALSE, FALSE);

	g_pLogPrint->In_WriteMsg(p);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	g_pLogPrint->m_pLog->LogString(XLOGLEVEL_TRACE, p);
#else
	if (nCount == 0)
	{
		return;
	}

	ASSERT (g_pLogPrint != NULL);
	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	char *p = log_get_logprint_buffer();
	BYTE *pTemp= pBuffer + nBeginIndex;
	BYTE *pEnd = pTemp + nCount;
	long nIndex = 0;

	ValueToHex(pTemp, nCount, p, FALSE, FALSE);

	g_pLogPrint->In_WriteMsg(p);

	if (g_bOnlyWriteLogFile)
	{
		return;
	}

	g_pLogPrint->m_pLog->LogString(XLOGLEVEL_TRACE, p);
#endif
}

#ifdef _PSX_IDE_QT_
void CLogPrint::AppenLogdMsg(const CString &strMsg)
{
	CAutoSimpleLock oLock(g_pLogPrint->m_oCriticSection);
	if (g_pLogPrint == NULL)
	{
		return;
	}
    g_pLogPrint->m_oLogStringList.Add(strMsg);
}

void CLogPrint::GetLogdMsg(CStringArray &oStrList)
{
	CAutoSimpleLock oLock(g_pLogPrint->m_oCriticSection);

	if (g_pLogPrint == NULL)
	{
		return;
	}

	oStrList.Append(g_pLogPrint->m_oLogStringList);
	g_pLogPrint->m_oLogStringList.RemoveAll();
}
#endif

//////////////////////////////////////////////////////////////////////////
//CLogBaseMngr
CLogBaseMngr *CLogBaseMngr::g_pLogBaseMngr = NULL;;
long CLogBaseMngr::g_nLogBaseMngrRef = 0;;

CLogBaseMngr::CLogBaseMngr()
{

}

CLogBaseMngr::~CLogBaseMngr()
{

}

void CLogBaseMngr::RegisterLogBase(CLogBase *pLogBase)
{
	g_nLogBaseMngrRef++;

	if (g_nLogBaseMngrRef == 1)
	{
		g_pLogBaseMngr = new CLogBaseMngr();
		CLogPrint::Create(g_pLogBaseMngr);
	}

	ASSERT (g_pLogBaseMngr != NULL);
	ASSERT (g_pLogBaseMngr->Find(pLogBase) == NULL);

	g_pLogBaseMngr->AddTail(pLogBase);
}

void CLogBaseMngr::UnRegisterLogBase(CLogBase *pLogBase)
{
	ASSERT (g_pLogBaseMngr != NULL);
	ASSERT (g_pLogBaseMngr->Find(pLogBase) != NULL);

	g_pLogBaseMngr->Remove(pLogBase);

	g_nLogBaseMngrRef--;

	if (g_nLogBaseMngrRef == 0)
	{
		delete g_pLogBaseMngr;
		g_pLogBaseMngr = NULL;
		CLogPrint::SetLog(NULL);
		CLogPrint::Release();
	}
}

void CLogBaseMngr::LogString(long nLevel, const CString &strMsg)
{
	POS pos = GetHeadPosition();
	CLogBase *pLogBase = NULL;

	while (pos != NULL)
	{
		pLogBase = GetNext(pos);
		ASSERT( pLogBase != NULL);
		pLogBase->LogString(nLevel, strMsg);
	}
}

void CLogBaseMngr::LogString(LPVOID pPara, long nLevel, const CString &strMsg)
{
	POS pos = GetHeadPosition();
	CLogBase *pLogBase = NULL;

	while (pos != NULL)
	{
		pLogBase = GetNext(pos);
		ASSERT( pLogBase != NULL);
		pLogBase->LogString(pPara, nLevel, strMsg);
	}
}

void CLogBaseMngr::LogString(long nLevel, const char *strMsg)
{
	POS pos = GetHeadPosition();
	CLogBase *pLogBase = NULL;

	while (pos != NULL)
	{
		pLogBase = GetNext(pos);
		ASSERT( pLogBase != NULL);
		pLogBase->LogString(nLevel, strMsg);
	}
}

void CLogBaseMngr::LogString(LPVOID pPara, long nLevel, const char* strMsg)
{
	POS pos = GetHeadPosition();
	CLogBase *pLogBase = NULL;

	while (pos != NULL)
	{
		pLogBase = GetNext(pos);
		ASSERT( pLogBase != NULL);
		pLogBase->LogString(pPara, nLevel, strMsg);
	}
}

void log_WriteLogFileForDebug(const CString &strPath, BYTE *pBuffer, long nLen)
{
	SYSTEMTIME tm;
	CFile oFile;
	CString strFile;

	::GetLocalTime(&tm);
    strFile.AppendFormat(_T("%s%d-%d-%d %d-%d-%d.rpccfg"), strPath.GetString(), tm.wYear, tm.wMonth, tm.wDay
		, tm.wHour, tm.wMinute, tm.wSecond);

	if (oFile.Open(strFile, CFile::modeCreate))
	{
		oFile.Write(pBuffer, nLen);
		oFile.Close();
	}
}

