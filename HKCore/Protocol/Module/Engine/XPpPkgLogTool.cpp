#include "StdAfx.h"
#include "XPpPkgLogTool.h"
#include "../../../Module/API/GlobalConfigApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//

CXPpPkgLogTool *CXPpPkgLogTool::g_pPpPkgLogTool = NULL;
long CXPpPkgLogTool::g_nPpPkgLogToolRef = 0;

#define XPP_PKG_LOG_BUF_MAX  10240

CXPpPkgLogTool::CXPpPkgLogTool()
{
	m_nPpPkgAddPos = 0;
	m_nPpPkgLogPos = 0;
	m_nPpPkgLogCount = 0;
	memset(m_oXPpPkgLog, 0, sizeof(X_PP_PKG_LOG) * MAX_X_PP_PKG_LOG);

    m_nXPpLogBufferLen = 0;
    m_pszXPpLogBuffer = NULL;
    SetXPpLogBufferLen(XPP_PKG_LOG_BUF_MAX);

	m_bProtocolSpy = FALSE;
	m_bPpPkgLogWrite = FALSE;
    m_nXPpLogTxtLen = 0;

	for (int k=0; k<XPPPKGLOG_ENGINEDATA_COUNT; k++)
	{
		m_pEngineDatas[k] = 0;
	}

}

CXPpPkgLogTool::~CXPpPkgLogTool()
{
	long nIndex = 0;

	for (nIndex=0; nIndex< MAX_X_PP_PKG_LOG; nIndex++)
	{
		XPpPkgLog_Free(m_oXPpPkgLog[nIndex]);
	}

	delete m_pszXPpLogBuffer;
	m_pszXPpLogBuffer = NULL;

	if (m_bPpPkgLogWrite)
	{
		m_oPpPkgLogWrite.Close();
	}
}

CXPpPkgLogTool* CXPpPkgLogTool::Create()
{
	g_nPpPkgLogToolRef++;

	if (g_nPpPkgLogToolRef == 1)
	{
		g_pPpPkgLogTool = new CXPpPkgLogTool();
	}

	return g_pPpPkgLogTool;
}

void CXPpPkgLogTool::Release()
{
	g_nPpPkgLogToolRef--;

	if (g_nPpPkgLogToolRef == 0)
	{
		delete g_pPpPkgLogTool;
		g_pPpPkgLogTool = NULL;
	}
}

void CXPpPkgLogTool::CreateLogWriteFile()
{
	g_pPpPkgLogTool->In_CreateLogWriteFile();
}

void CXPpPkgLogTool::In_CreateLogWriteFile()
{
	if (m_bPpPkgLogWrite)
	{
		return;
	}

	CString strFile;
    strFile = _P_GetDBPath();
	strFile += _T("PpPkgLogDb.txt");
	m_bPpPkgLogWrite = m_oPpPkgLogWrite.Open(strFile, CFile::modeCreate | CFile::modeWrite);;
}

void CXPpPkgLogTool::XPpPkgLog_Free(X_PP_PKG_LOG &oXPpPkgLog)
{
#ifndef XPP_PKG_LOG_CYCLEBUF_MODE
	if (oXPpPkgLog.pBuffer != NULL)
	{
		delete oXPpPkgLog.pBuffer;
		oXPpPkgLog.pBuffer = NULL;
	}
#endif
	oXPpPkgLog.pEngineData = NULL;
}

void CXPpPkgLogTool::XPpPkgLog_SetLen(X_PP_PKG_LOG &oXPpPkgLog, long nLen)
{
#ifndef XPP_PKG_LOG_CYCLEBUF_MODE
	if (oXPpPkgLog.nMaxLen > nLen)
	{
		return;
	}

	XPpPkgLog_Free(oXPpPkgLog);
    oXPpPkgLog.pBuffer = new BYTE[nLen+10];
	oXPpPkgLog.nMaxLen = nLen+10;
#endif
}

void CXPpPkgLogTool::XPpPkgLog_Set(X_PP_PKG_LOG &oXPpPkgLog, BYTE* buffer, long len, BOOL bRcv)
{
#ifndef XPP_PKG_LOG_CYCLEBUF_MODE
	XPpPkgLog_SetLen(oXPpPkgLog, len);
	memcpy(oXPpPkgLog.pBuffer, buffer, len);
	oXPpPkgLog.nLen = len;
	oXPpPkgLog.bRcv = bRcv;

	::GetLocalTime(&oXPpPkgLog.tm);
#endif
	oXPpPkgLog.pEngineData = NULL;
}

void CXPpPkgLogTool::XPpPkgLog_Set2(X_PP_PKG_LOG &oXPpPkgLog, BYTE* buffer, long len, BOOL bRcv, CExBaseObject *pEngineData)
{
#ifndef XPP_PKG_LOG_CYCLEBUF_MODE
	XPpPkgLog_SetLen(oXPpPkgLog, len);
	memcpy(oXPpPkgLog.pBuffer, buffer, len);
	oXPpPkgLog.nLen = len;
	oXPpPkgLog.bRcv = bRcv;

	::GetLocalTime(&oXPpPkgLog.tm);
#endif
	oXPpPkgLog.pEngineData = pEngineData;
}

void CXPpPkgLogTool::In_AddPpPkgLog(BYTE* buffer, long len, BOOL bRcv)
{
	XPpPkgLog_Set(m_oXPpPkgLog[m_nPpPkgAddPos], buffer, len, bRcv);
	m_nPpPkgAddPos++;

	if (m_nPpPkgAddPos >= MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgAddPos = 0;
	}

	if (m_nPpPkgLogCount < MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgLogCount++;
	}
}

void CXPpPkgLogTool::In_AddPpPkgLog(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv)
{
	if (!m_bProtocolSpy)
	{
		return;
	}

	X_PP_PKG_LOG &oXPpPkgLog = m_oXPpPkgLog[m_nPpPkgAddPos];

#ifdef XPP_PKG_LOG_CYCLEBUF_MODE
	oXPpPkgLog.oBuffer = oBufPos;
#else
	long nLen1 = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos;
	long nLen2 = 0;
	long nLen = nLen1;

	if (oBufPos.nBuf2EndPos >= 0)
	{
		nLen2 = oBufPos.nBuf2EndPos - oBufPos.nBuf2BeginPos;
		nLen += nLen2;
	}

	XPpPkgLog_SetLen(oXPpPkgLog, nLen);
	memcpy(oXPpPkgLog.pBuffer, oBufPos.pBuffer + oBufPos.nBuf1BeginPos, nLen1);

	if (nLen2 > 0)
	{
		memcpy(oXPpPkgLog.pBuffer + nLen1, oBufPos.pBuffer + oBufPos.nBuf2BeginPos, nLen2);

	}

	oXPpPkgLog.nLen = nLen;
#endif

	oXPpPkgLog.bRcv = bRcv;
	oXPpPkgLog.pEngineData = NULL;

	m_nPpPkgAddPos++;

	if (m_nPpPkgAddPos >= MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgAddPos = 0;
	}

	if (m_nPpPkgLogCount < MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgLogCount++;
	}

	::GetLocalTime(&oXPpPkgLog.tm);
}

void CXPpPkgLogTool::In_AddPpPkgLog2(BYTE* buffer, long len, BOOL bRcv, CExBaseObject *pEngineData)
{
	if (HasCloseDevice(pEngineData))
	{
		return;
	}

	XPpPkgLog_Set2(m_oXPpPkgLog[m_nPpPkgAddPos], buffer, len, bRcv, pEngineData);
	m_nPpPkgAddPos++;

	if (m_nPpPkgAddPos >= MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgAddPos = 0;
	}

	if (m_nPpPkgLogCount < MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgLogCount++;
	}
}

void CXPpPkgLogTool::In_AddPpPkgLog2(CYCLEMEMBUFFERPOS &oBufPos, BOOL bRcv, CExBaseObject *pEngineData, long nSndRcvIndex)
{
	if (HasCloseDevice(pEngineData))
	{
		return;
	}

	if (!m_bProtocolSpy)
	{
		return;
	}

	X_PP_PKG_LOG &oXPpPkgLog = m_oXPpPkgLog[m_nPpPkgAddPos];

#ifdef XPP_PKG_LOG_CYCLEBUF_MODE
	oXPpPkgLog.oBuffer = oBufPos;
#else
	long nLen1 = oBufPos.nBuf1EndPos - oBufPos.nBuf1BeginPos;
	long nLen2 = 0;
	long nLen = nLen1;

	if (oBufPos.nBuf2EndPos >= 0)
	{
		nLen2 = oBufPos.nBuf2EndPos - oBufPos.nBuf2BeginPos;
		nLen += nLen2;
	}

	XPpPkgLog_SetLen(oXPpPkgLog, nLen);
	memcpy(oXPpPkgLog.pBuffer, oBufPos.pBuffer + oBufPos.nBuf1BeginPos, nLen1);

	if (nLen2 > 0)
	{
		memcpy(oXPpPkgLog.pBuffer + nLen1, oBufPos.pBuffer + oBufPos.nBuf2BeginPos, nLen2);
	}

	oXPpPkgLog.nLen = nLen;
#endif

	oXPpPkgLog.bRcv = bRcv;
	oXPpPkgLog.pEngineData = pEngineData;
	oXPpPkgLog.nSndRcvIndex = nSndRcvIndex;

	m_nPpPkgAddPos++;

	if (m_nPpPkgAddPos >= MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgAddPos = 0;
	}

	if (m_nPpPkgLogCount < MAX_X_PP_PKG_LOG)
	{
		m_nPpPkgLogCount++;
	}

	::GetLocalTime(&oXPpPkgLog.tm);
}

void CXPpPkgLogTool::In_XPpPkgLog_Hex(BYTE *pBegin, BYTE *pEnd, char* &pLogBuffer)
{
    char *pLogBufferBegin = pLogBuffer;
	BYTE *pBuffer = pBegin;

    if (pEnd - pBegin > m_nXPpLogBufferLen)
    {//2020-11-26  lijunqing  避免内存越界写
        pEnd = pBegin + m_nXPpLogBufferLen;
    }

	while (pBuffer < pEnd)
	{
		ValueToHex(*pBuffer, *pLogBuffer, *(pLogBuffer+1));
		pLogBuffer += 2;
		*pLogBuffer = ' ';
		pLogBuffer++;

		pBuffer++;
	}

    m_nXPpLogTxtLen = pLogBuffer - pLogBufferBegin;
}

void CXPpPkgLogTool::In_XPpPkgLog_Hex(X_PP_PKG_LOG &oXPpPkgLog, BOOL bAddNewLine)
{
	//时间 + g_sLangTxt_Receive or g_sLangTxt_Send
	long nLen = 0;

#ifdef XPP_PKG_LOG_CYCLEBUF_MODE
	nLen = oXPpPkgLog.oBuffer.nBuf1EndPos - oXPpPkgLog.oBuffer.nBuf1BeginPos;

	if (oXPpPkgLog.oBuffer.nBuf2EndPos >= 0)
	{
		nLen += oXPpPkgLog.oBuffer.nBuf2EndPos - oXPpPkgLog.oBuffer.nBuf2BeginPos;
	}
#else
	nLen = oXPpPkgLog.nLen;
#endif

	nLen *= 3;
	nLen += 50;
	SetXPpLogBufferLen(nLen);
	char *pLogBuffer = m_pszXPpLogBuffer;

	sprintf(pLogBuffer, "(%d)", oXPpPkgLog.nSndRcvIndex);
	pLogBuffer += strlen(pLogBuffer);

#ifdef XPP_PKG_LOG_CYCLEBUF_MODE
	In_XPpPkgLog_Hex(oXPpPkgLog.oBuffer.pBuffer+oXPpPkgLog.oBuffer.nBuf1BeginPos
		, oXPpPkgLog.oBuffer.pBuffer+oXPpPkgLog.oBuffer.nBuf1EndPos, pLogBuffer);

	if (oXPpPkgLog.oBuffer.nBuf2EndPos >= 0)
	{
		In_XPpPkgLog_Hex(oXPpPkgLog.oBuffer.pBuffer+oXPpPkgLog.oBuffer.nBuf2BeginPos
			, oXPpPkgLog.oBuffer.pBuffer+oXPpPkgLog.oBuffer.nBuf2EndPos, pLogBuffer);
	}
#else
	In_XPpPkgLog_Hex(oXPpPkgLog.pBuffer, oXPpPkgLog.pBuffer + oXPpPkgLog.nLen, pLogBuffer);
#endif

    if (bAddNewLine)
    {
        *pLogBuffer = '\r';		pLogBuffer++;
        *pLogBuffer = '\n';		pLogBuffer++;
        m_nXPpLogTxtLen += 2;
    }

	*pLogBuffer = 0;
}


void CXPpPkgLogTool::In_XPpPkgLog(X_PP_PKG_LOG &oXPpPkgLog, CString &strMsg, BOOL bAddTitle, BOOL bAddNewLine)
{
    In_XPpPkgLog_Hex(oXPpPkgLog, bAddNewLine);

    strMsg.Format(_T("%02d:%02d:%02d.%03d"), oXPpPkgLog.tm.wHour, oXPpPkgLog.tm.wMinute, oXPpPkgLog.tm.wSecond, oXPpPkgLog.tm.wMilliseconds);

    if (bAddTitle)
    {
        if (oXPpPkgLog.bRcv)
        {
            strMsg += g_sLangTxt_Receive/*_T("接收 ")*/;
        }
        else
        {
            strMsg += g_sLangTxt_Send/*_T("发送 ")*/;
        }
    }

    strMsg += m_pszXPpLogBuffer;
}

extern long g_bLogPackageInfor;

void CXPpPkgLogTool::In_XPpPkgLog(X_PP_PKG_LOG &oXPpPkgLog)
{
	if (!m_bProtocolSpy)
	{
		return;
	}

	if (oXPpPkgLog.pEngineData == NULL)
	{
		return;
	}

	if (HasCloseDevice(oXPpPkgLog.pEngineData))
	{
		return;
	}

	CString strMsg;
    In_XPpPkgLog(oXPpPkgLog, strMsg, TRUE, TRUE);

	if (m_bPpPkgLogWrite)
	{
        m_oPpPkgLogWrite.Write(strMsg.GetString(), strMsg.GetLength());
	}

	if (oXPpPkgLog.bRcv)
	{
        if (g_pLogPkgReceivePrint != NULL && g_bLogPackageInfor)
        {
            g_pLogPkgReceivePrint->LogString(XLOGLEVEL_TRACE, strMsg);
        }
	}
	else
	{
		if (g_pLogPkgSendPrint != NULL && g_bLogPackageInfor)
        {
            g_pLogPkgSendPrint->LogString(XLOGLEVEL_TRACE, strMsg);
        }
	}

	//待添加：在此处增加发送PxgSpy
	if (g_pLogPkgSpy != NULL)
	{
		CString strDir, strTime, strType, strPkgTxt;

		if (oXPpPkgLog.bRcv)
		{
			strDir = _T("1");  //接收，表示上行
		}
		else
		{
			strDir = _T("0");  //发送，表示下行
		}

		SystemTime_To_StringEx(oXPpPkgLog.tm, strTime);
		
        if ( (m_nXPpLogTxtLen > 0)
                && (m_pszXPpLogBuffer[m_nXPpLogTxtLen - 1]) == '\n'
                && (m_pszXPpLogBuffer[m_nXPpLogTxtLen - 2]) == '\r')
		{  
            m_pszXPpLogBuffer[m_nXPpLogTxtLen - 2] = '\0'; // 替换为字符串结束符
		}  

        g_pLogPkgSpy->PkgSpy((CString)m_pszXPpLogBuffer, _T(""), strDir, strType, strTime, oXPpPkgLog.pEngineData);
	}
}

void CXPpPkgLogTool::In_XPpPkgLog()
{
	if (!m_bProtocolSpy)
	{
		return;
	}

	if (m_nPpPkgAddPos == m_nPpPkgLogPos)
	{
		return;
	}

	long nPpPkgAddPos = m_nPpPkgAddPos;
	long nIndex = 0;

	if (nPpPkgAddPos > m_nPpPkgLogPos)
	{
		for (nIndex = m_nPpPkgLogPos; nIndex<nPpPkgAddPos; nIndex++)
		{
			In_XPpPkgLog(m_oXPpPkgLog[nIndex]);
		}
	}
	else
	{
		for (nIndex = m_nPpPkgLogPos; nIndex<MAX_X_PP_PKG_LOG; nIndex++)
		{
			In_XPpPkgLog(m_oXPpPkgLog[nIndex]);
		}

		for (nIndex = 0; nIndex<nPpPkgAddPos; nIndex++)
		{
			In_XPpPkgLog(m_oXPpPkgLog[nIndex]);
		}
	}

	m_nPpPkgLogPos = nPpPkgAddPos;
}

void CXPpPkgLogTool::In_GetPpPkgLogIndex(long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
    nBegin1 = -1;
    nBegin2 = -1;
    nEnd1 = -1;
    nEnd2 = -1;

    if (!m_bProtocolSpy)
    {
        return;
    }

    if (m_nPpPkgAddPos == m_nPpPkgLogPos)
    {
        return;
    }

    long nPpPkgAddPos = m_nPpPkgAddPos;
    long nIndex = 0;

    if (nPpPkgAddPos > m_nPpPkgLogPos)
    {
        nBegin1 = m_nPpPkgLogPos;
        nEnd1 = nPpPkgAddPos - 1;
    }
    else
    {
        nBegin1 = m_nPpPkgLogPos;
        nEnd1 = MAX_X_PP_PKG_LOG - 1;
        nBegin1 = 0;
        nEnd1 = nPpPkgAddPos - 1;
    }

    m_nPpPkgLogPos = nPpPkgAddPos;
}

void CXPpPkgLogTool::In_PpPkgLogStr(long nIndex, CString &strText, CString &strType)
{
     In_XPpPkgLog(m_oXPpPkgLog[nIndex], strText, FALSE, FALSE);

     if (m_oXPpPkgLog[nIndex].bRcv)
     {
         strType = _T("RCV");
     }
     else
     {
         strType = _T("SND");
     }
}

void CXPpPkgLogTool::In_PpPkgCloseDevice(CExBaseObject *pEngineData)
{
	long nPpPkgAddPos = m_nPpPkgAddPos;
	long nIndex = 0;

	if (nPpPkgAddPos > m_nPpPkgLogPos)
	{
		for (nIndex = m_nPpPkgLogPos; nIndex<nPpPkgAddPos; nIndex++)
		{
			if (m_oXPpPkgLog[nIndex].pEngineData == pEngineData)
			{
				m_oXPpPkgLog[nIndex].pEngineData = NULL;
			}
		}
	}
	else
	{
		for (nIndex = m_nPpPkgLogPos; nIndex<MAX_X_PP_PKG_LOG; nIndex++)
		{
			if (m_oXPpPkgLog[nIndex].pEngineData == pEngineData)
			{
				m_oXPpPkgLog[nIndex].pEngineData = NULL;
			}
		}

		for (nIndex = 0; nIndex<nPpPkgAddPos; nIndex++)
		{
			if (m_oXPpPkgLog[nIndex].pEngineData == pEngineData)
			{
				m_oXPpPkgLog[nIndex].pEngineData = NULL;
			}
		}
	}
}

void CXPpPkgLogTool::AddCloseDevice(CExBaseObject *pEngineData)
{
	for (int k=0; k<XPPPKGLOG_ENGINEDATA_COUNT; k++)
	{
		if (m_pEngineDatas[k] == 0)
		{
			m_pEngineDatas[k] = pEngineData;
			break;
		}
	}
}

void CXPpPkgLogTool::RemoveCloseDevice(CExBaseObject *pEngineData)
{
	for (int k=0; k<XPPPKGLOG_ENGINEDATA_COUNT; k++)
	{
		if (m_pEngineDatas[k] == pEngineData)
		{
			m_pEngineDatas[k] = 0;
		}
	}
}

bool CXPpPkgLogTool::HasCloseDevice(CExBaseObject *pEngineData)
{
	for (int k=0; k<XPPPKGLOG_ENGINEDATA_COUNT; k++)
	{
		if (m_pEngineDatas[k] == pEngineData)
		{
			return true;
		}
	}

	return false;
}

