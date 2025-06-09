#include "StdAfx.h"
#include "LogPrint.h"

#include "..\API\FileApi.h"
#include "..\API\GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CLogBase *g_pLogErrorSpy = NULL;
CLogBase *g_pLogTracePrint = NULL;
BOOL g_bShowRealTimeInforLevel = FALSE;
long g_bOnlyWriteLogFile = FALSE;

#define g_lenLogGloalDest   102400
wchar_t g_strLogGloalDest[g_lenLogGloalDest];
char g_strLogGloalDest_Char[g_lenLogGloalDest];

//////////////////////////////////////////////////////////////////////////
//
void CLogBase::LogString(long nLevel, const CString &strMsg)
{
	TRACE(L"%s\r\n", strMsg);
}

void CLogBase::LogString(LPVOID pPara, long nLevel, const CString &strMsg)
{
	TRACE(L"%s\r\n", strMsg);
}

CLogPrint::CLogPrint(void)
{
	m_pLog = NULL;
	m_pLogFile = NULL;
	m_bLogFileCreate = FALSE;
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
	if (m_pLogFile != NULL)
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
#ifdef UNICODE
		char *pszFile = NULL;
		CString_to_char(strTemp, &pszFile);
		m_pLogFile = fopen(pszFile, "w+");
		delete pszFile;
#else
		m_pLogFile = fopen(strFile, "w+");
#endif
	}
	else
	{
#ifdef UNICODE
		char *pszFile = NULL;
		CString_to_char(strTemp, &pszFile);
		m_pLogFile = fopen(pszFile, "r+");
		delete pszFile;
#else
		m_pLogFile = fopen(strFile, "r+");
#endif

		if (m_pLogFile)
		{
			fseek(m_pLogFile, 0, SEEK_END);
		}
	}
}

void CLogPrint::In_CloseLogFile()
{
	if (m_pLogFile)
	{
		fclose (m_pLogFile);
		m_pLogFile = NULL;
	}
}

void CLogPrint::In_WriteMsg(const CString &strMsg)
{
	if (!m_pLogFile)
	{
		return;
	}

	CString strTime;
	GetCurrSystemtimeString2(strTime, TRUE);

#ifdef _UNICODE
	fputws(strTime, m_pLogFile);
	fputws(strTime, m_pLogFile);
	fputws(_T("\r\n"), m_pLogFile);
#else
	fputs(strTime, m_pLogFile);
	fputs(strTime, m_pLogFile);
	fputs(_T("\r\n"), m_pLogFile);
#endif
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

	if (nLevel == LOGLEVEL_REALTIME_INFO)
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

	if (nLevel == LOGLEVEL_REALTIME_INFO)
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
	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_bOnlyWriteLogFile)
	{//2019-12-1  用于调试实时信息
		if (g_pLogPrint->m_pLogFile != NULL)
		{
			va_list argList;
			va_start( argList, strFormat );
			fwprintf(g_pLogPrint->m_pLogFile, strFormat, argList);
			va_end( argList );
		}

		return;
	}
//	ASSERT (g_pLogPrint != NULL);

	if (!g_nOutputMode)
	{
		return;
	}

	if (!g_nLogPrintRef)
	{
		return;
	}

	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	memset(g_strLogGloalDest, 0, sizeof(wchar_t)*g_lenLogGloalDest);
	*g_strLogGloalDest = 0;

	va_list argList;
	va_start( argList, strFormat );
	vswprintf_s( g_strLogGloalDest, g_lenLogGloalDest, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = g_strLogGloalDest;
	g_pLogPrint->In_WriteMsg(strMsg);

	if (nLevel == LOGLEVEL_REALTIME_INFO)
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
	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_bOnlyWriteLogFile)
	{//2019-12-1  用于调试实时信息
		if (g_pLogPrint->m_pLogFile != NULL)
		{
			va_list argList;
			va_start( argList, strFormat );
			fwprintf(g_pLogPrint->m_pLogFile, strFormat, argList);
			va_end( argList );
		}

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

	memset(g_strLogGloalDest, 0, sizeof(wchar_t)*g_lenLogGloalDest);
	*g_strLogGloalDest = 0;

	va_list argList;
	va_start( argList, strFormat );
	vswprintf_s( g_strLogGloalDest, g_lenLogGloalDest, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = g_strLogGloalDest;
	g_pLogPrint->In_WriteMsg(strMsg);

	if (nLevel == LOGLEVEL_REALTIME_INFO)
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
	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_bOnlyWriteLogFile)
	{//2019-12-1  用于调试实时信息
		if (g_pLogPrint->m_pLogFile != NULL)
		{
			va_list argList;
			va_start( argList, strFormat );
			fprintf(g_pLogPrint->m_pLogFile, strFormat, argList);
			va_end( argList );
		}

		return;
	}

	ASSERT (g_pLogPrint != NULL);
	if (g_pLogPrint == NULL)
	{
		return;
	}

	ASSERT (g_pLogPrint->m_pLog != NULL);

	if (g_pLogPrint->m_pLog == NULL)
	{
		return;
	}

	memset(g_strLogGloalDest_Char, 0, sizeof(char)*g_lenLogGloalDest);

	va_list argList;
	va_start( argList, strFormat );
	vsprintf_s( g_strLogGloalDest_Char, g_lenLogGloalDest, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = g_strLogGloalDest_Char;
	g_pLogPrint->In_WriteMsg(strMsg);

	if (nLevel == LOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(nLevel, g_strLogGloalDest_Char);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(nLevel, g_strLogGloalDest_Char);
	}
}

void CLogPrint::LogFormatString(LPVOID pPara, long nLevel, const char *strFormat, ...)
{
	if (g_pLogPrint == NULL)
	{
		return;
	}

	if (g_bOnlyWriteLogFile)
	{//2019-12-1  用于调试实时信息
		if (g_pLogPrint->m_pLogFile != NULL)
		{
			va_list argList;
			va_start( argList, strFormat );
			fprintf(g_pLogPrint->m_pLogFile, strFormat, argList);
			va_end( argList );
		}

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

	memset(g_strLogGloalDest_Char, 0, sizeof(char)*g_lenLogGloalDest);
	*g_strLogGloalDest_Char = 0;

	va_list argList;
	va_start( argList, strFormat );
	vsprintf_s( g_strLogGloalDest_Char, g_lenLogGloalDest, strFormat, argList );
	va_end( argList );

	CString strMsg;
	strMsg = g_strLogGloalDest_Char;
	g_pLogPrint->In_WriteMsg(strMsg);

	if (nLevel == LOGLEVEL_REALTIME_INFO)
	{
		if (g_bShowRealTimeInforLevel)
		{
			g_pLogPrint->m_pLog->LogString(pPara, nLevel, g_strLogGloalDest_Char);
		}
	}
	else
	{
		g_pLogPrint->m_pLog->LogString(pPara, nLevel, g_strLogGloalDest_Char);
	}
}

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
	strFile.AppendFormat(_T("%s%d-%d-%d %d-%d-%d.rpccfg"), strPath, tm.wYear, tm.wMonth, tm.wDay
		, tm.wHour, tm.wMinute, tm.wSecond);

	if (oFile.Open(strFile, CFile::modeCreate))
	{
		oFile.Write(pBuffer, nLen);
		oFile.Close();
	}
}

