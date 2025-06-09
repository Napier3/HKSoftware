#include "StdAfx.h"
#include "ScriptFunc_System.h"
#include "../XLanguageResourcePp.h"
// #ifdef _PP_DEV_MODE_
// #include "PpDevBaseApp.h"
// #else
#include "PpEngineBaseApp.h"
// #endif
#include "BbData.h"

#include "PpEngineDataMngrCntr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


char g_pszPpScriptReturn[MAX_PATH];

CDeviceCmmConfig* script_GetDeviceCmmConfig(CTScriptSingleVM *pXvm)   
{
    //CPpDevBaseApp* pApp = g_thePpDevBaseApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CPpTemplate *pTemplate = NULL;

	pTemplate = (CPpTemplate*)pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	
	if (pTemplate == NULL)
	{
		return NULL;
	}

	return pTemplate->m_pCmmConfig;
}

long script_GetSystemPara(CTScriptSingleVM *pXvm, const CString &strID)   
{

// #ifdef _PP_DEV_MODE_
// 
// 	return 1;
// 
// #else

	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pTemplate = NULL;

	pTemplate = pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pApp->FindEngineThread((CPpTemplate*)pTemplate);
	long nAddr = 0;

	CString strTagValue;

	if (pThread->GetDeviceAttribute(strID, strTagValue))
	{
#ifdef UNICODE
		nAddr = _wtol(strTagValue);
#else
        nAddr = atol(strTagValue.GetString());
#endif
	}

	return nAddr;

// #endif
}
//系统相关的函数

static const char* NET_MODE_TCP  = "tcp";
static const char* NET_MODE_UDP  = "udp";

DWORD script_GetIPAddr(const CString &strIP)
{
	long nLen = strIP.GetLength();
	if (nLen < 7)
	{
		return IP_DEFAULT;
	}

	if (nLen > 17)
	{
		return IP_DEFAULT;
	}

	char pszIP[MAX_PATH];
	CString_to_char(strIP, pszIP);

	DWORD dwIP = inet_addr(pszIP);

	return dwIP;
}

//获取设备的IP地址
/*
long script_GetIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp)    
{
	CDeviceCmmConfig *pCmmConfig = script_GetDeviceCmmConfig(pXvm);

	if (pCmmConfig == NULL)
	{
		return IP_DEFAULT;
	}

    if (stricmp(pszTcpOrUdp, NET_MODE_TCP) == 0)
	{
		CCmmTcpServerConfig *pTcpServer = (CCmmTcpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_SERVER_CONFIG);

		if (pTcpServer != NULL)
		{
			return script_GetIPAddr(pTcpServer->m_strLocalIP);
		}

		CCmmTcpClientConfig *pTcpClient = (CCmmTcpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_CLIENT_CONFIG);

		if (pTcpClient != NULL)
		{
			return script_GetIPAddr(pTcpClient->m_strLocalIP);
		}	
	}
    else if (stricmp(pszTcpOrUdp, NET_MODE_UDP) == 0)
	{
		CCmmUdpServerConfig *pUdpServer = (CCmmUdpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_SERVER_CONFIG);

		if (pUdpServer != NULL)
		{
			return script_GetIPAddr(pUdpServer->m_strLocalIP);
		}

		CCmmUdpClientConfig *pUdpClient = (CCmmUdpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_CLIENT_CONFIG);

		if (pUdpClient != NULL)
		{
			return script_GetIPAddr(pUdpClient->m_strLocalIP);
		}
	}

	return IP_DEFAULT;
}
*/
const char* script_GetIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp)    
{
	CDeviceCmmConfig *pCmmConfig = script_GetDeviceCmmConfig(pXvm);
	char* p=NULL;
	if (pCmmConfig == NULL)
	{
		//return IP_DEFAULT;
		return "无通道";
	}

    if (stricmp(pszTcpOrUdp, NET_MODE_TCP) == 0)
	{
		CCmmTcpServerConfig *pTcpServer = (CCmmTcpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_SERVER_CONFIG);

		if (pTcpServer != NULL)
		{
			//return script_GetIPAddr(pTcpServer->m_strLocalIP);

			CString_to_char(pTcpServer->m_strLocalIP,&p);
			return p;
		}

		CCmmTcpClientConfig *pTcpClient = (CCmmTcpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_CLIENT_CONFIG);

		if (pTcpClient != NULL)
		{
			//return script_GetIPAddr(pTcpClient->m_strLocalIP);
			CString_to_char(pTcpClient->m_strLocalIP,&p);
			return p;
		
		}	
	}
    else if (stricmp(pszTcpOrUdp, NET_MODE_UDP) == 0)
	{
		CCmmUdpServerConfig *pUdpServer = (CCmmUdpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_SERVER_CONFIG);

		if (pUdpServer != NULL)
		{
			//return script_GetIPAddr(pUdpServer->m_strLocalIP);
			CString_to_char(pUdpServer->m_strLocalIP,&p);
			return p;
		
		}

		CCmmUdpClientConfig *pUdpClient = (CCmmUdpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_CLIENT_CONFIG);

		if (pUdpClient != NULL)
		{
			//return script_GetIPAddr(pUdpClient->m_strLocalIP);
			CString_to_char(pUdpClient->m_strLocalIP,&p);
			return p;
			
		}
	}

	//return IP_DEFAULT;
	return "无通道";
}
//获取远程的IP地址
long script_GetRemoteIP(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp)
{
	CDeviceCmmConfig *pCmmConfig = script_GetDeviceCmmConfig(pXvm);

	if (pCmmConfig == NULL)
	{
		return IP_DEFAULT;
	}

    if (stricmp(pszTcpOrUdp, NET_MODE_TCP) == 0)
	{
		CCmmTcpClientConfig *pTcpClient = (CCmmTcpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_CLIENT_CONFIG);

		if (pTcpClient != NULL)
		{
			return script_GetIPAddr(pTcpClient->m_strRemoteIP);
		}	
	}
    else if (stricmp(pszTcpOrUdp, NET_MODE_UDP) == 0)
	{
		CCmmUdpClientConfig *pUdpClient = (CCmmUdpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_CLIENT_CONFIG);

		if (pUdpClient != NULL)
		{
			return script_GetIPAddr(pUdpClient->m_strRemoteIP);
		}
	}

	return IP_DEFAULT;
}

//获取设备地址
long script_GetDeviceAddr(CTScriptSingleVM *pXvm)   
{
	return script_GetDeviceAttrL(pXvm, "addr");
}

long script_GetDeviceAttrL(CTScriptSingleVM *pXvm, const char* pszAttrID)   
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pTemplate = NULL;

	pTemplate = pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pApp->FindEngineThread((CPpTemplate*)pTemplate);
	long nAddr = 0;

	CString strTagValue;
	CString strAttrID;
	strAttrID = pszAttrID;
	
	if (pThread->GetDeviceAttribute(strAttrID, strTagValue))
	{
#ifdef UNICODE
		nAddr = _wtol(strTagValue);
#else
        nAddr = atol(strTagValue.GetString());
#endif
	}

	return nAddr;
}
const char* script_GetDeviceAttrStr(CTScriptSingleVM *pXvm, const char* pszAttrID)   
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pTemplate = NULL;

	pTemplate = pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pApp->FindEngineThread((CPpTemplate*)pTemplate);
	long nAddr = 0;

	CString strTagValue;
	CString strAttrID;
	strAttrID = pszAttrID;

	if (pThread->GetDeviceAttribute(strAttrID, strTagValue))
	{
		CString_to_char(strTagValue, g_pszPpScriptReturn);
		//nAddr = _wtol(strTagValue);
	}
	else
	{
		g_pszPpScriptReturn[0] = '0';
		g_pszPpScriptReturn[1] = 0;
	}

	return g_pszPpScriptReturn;
}

long script_SetDeviceAttrL(CTScriptSingleVM *pXvm, const char* pszAttrID, long nValue)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pTemplate = NULL;

	pTemplate = pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pApp->FindEngineThread((CPpTemplate*)pTemplate);
	long nAddr = 0;

	CString strTagValue;
	CString strAttrID;
	strAttrID = pszAttrID;
	strTagValue.Format(_T("%d"), nValue);

	return pThread->SetDeviceAttribute(strAttrID, strTagValue);
}

long script_SetDeviceAttrStr(CTScriptSingleVM *pXvm, const char* pszAttrID, const char *pszValue)
{
	CPpEngineBaseApp* pApp = g_pTheEngineApp;
	CBaseObject *pObj = PPS_GetPpScript(pXvm);;
	CBaseObject *pTemplate = NULL;

	pTemplate = pObj->GetAncestor(PPCLASSID_PPTEMPLATE);
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pApp->FindEngineThread((CPpTemplate*)pTemplate);
	long nAddr = 0;

	CString strTagValue(pszValue);
	CString strAttrID;
	strAttrID = pszAttrID;

	return pThread->SetDeviceAttribute(strAttrID, strTagValue);
}


//获取通讯模式
long script_GetCmmMode(CTScriptSingleVM *pXvm)   
{
	return 0;
}


//获取通讯的端口
long script_GetPort(CTScriptSingleVM *pXvm, const char *pszCmmMode)  
{
	return 0;
}

long script_SetPort(CTScriptSingleVM *pXvm, const char *pszTcpOrUdp, long nPort)  
{
	CDeviceCmmConfig *pCmmConfig = script_GetDeviceCmmConfig(pXvm);

	if (pCmmConfig == NULL)
	{
		return 0;
	}

	if (stricmp(pszTcpOrUdp, NET_MODE_TCP) == 0)
	{
		CCmmTcpServerConfig *pTcpServer = (CCmmTcpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_SERVER_CONFIG);

		if (pTcpServer != NULL)
		{
			pTcpServer->m_nLocalPort = nPort;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpServer:%s, %d"), pTcpServer->m_strLocalIP.GetString(), nPort);
			return 1;
		}

		CCmmTcpClientConfig *pTcpClient = (CCmmTcpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_TCP_CLIENT_CONFIG);

		if (pTcpClient != NULL)
		{
			pTcpClient->m_nRemotePort = nPort;
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("TcpServer:%s, %d"), pTcpClient->m_strRemoteIP.GetString(), nPort);
			return 1;
		}	
	}
	else if (stricmp(pszTcpOrUdp, NET_MODE_UDP) == 0)
	{
		CCmmUdpServerConfig *pUdpServer = (CCmmUdpServerConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_SERVER_CONFIG);

		if (pUdpServer != NULL)
		{
			pUdpServer->m_nLocalPort = nPort;
			return 1;
		}

		CCmmUdpClientConfig *pUdpClient = (CCmmUdpClientConfig*)pCmmConfig->GetChildByClassID(DMCLASSID_CMM_UDP_CLIENT_CONFIG);

		if (pUdpClient != NULL)
		{
			pUdpClient->m_nRemotePort = nPort;
			return 1;
		}
	}

	return 0;
}

//获取系统的参数
long script_GetSystemPara(CTScriptSingleVM *pXvm, const char* pszParaID)   
{
	return script_GetSystemPara(pXvm, CString(pszParaID));
}

//////////////////////////////////////////////////////////////////////////
//logic
long script_LAnd(long nVal1, long nVal2)
{
	return nVal1 & nVal2;
}

long script_LOr(long nVal1, long nVal2)
{
	return nVal1 | nVal2;
}

long script_LNot(long nVal)
{
	return ~nVal;
}

long script_LXor(long nVal1,long nVal2)
{
	return nVal1 ^ nVal2;
}

long script_LComplement(long nVal)
{
	if (nVal < 0)
	{
		DWORD dwVal = ((DWORD)nVal) & 0x7FFFFFFF;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7FFFFFFF;
		dwVal |= 0x80000000;
		dwVal + 1;
		return (long)dwVal;
	}
	else
	{
		return nVal;
	}
}

short script_LComplement2(short nVal)
{
	if (nVal < 0)
	{
		SHORT dwVal = ((DWORD)nVal) & 0x7FFF;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7FFF;
		dwVal |= 0x8000;
		dwVal + 1;
		return (short)dwVal;
	}
	else
	{
		return nVal;
	}
}

char script_LComplement1(char nVal)
{
	if (nVal < 0)
	{
		CHAR dwVal = ((DWORD)nVal) & 0x7F;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7F;
		dwVal |= 0x80;
		dwVal + 1;
		return (char)dwVal;
	}
	else
	{
		return nVal;
	}
}

long script_LInverse(long nVal)
{
	if (nVal < 0)
	{
		DWORD dwVal = ((DWORD)nVal) & 0x7FFFFFFF;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7FFFFFFF;
		dwVal |= 0x80000000;
		return (long)dwVal;
	}
	else
	{
		return nVal;
	}
}

short script_LInverse2(short nVal)
{
	if (nVal < 0)
	{
		SHORT dwVal = ((DWORD)nVal) & 0x7FFF;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7FFF;
		dwVal |= 0x8000;
		return (short)dwVal;
	}
	else
	{
		return nVal;
	}
}

char script_LInverse1(char nVal)
{
	if (nVal < 0)
	{
		CHAR dwVal = ((DWORD)nVal) & 0x7F;
		dwVal = ~dwVal;
		dwVal = dwVal & 0x7F;
		dwVal |= 0x80;
		return (char)dwVal;
	}
	else
	{
		return nVal;
	}
}

//////////////////////////////////////////////////////////////////////////
//bit

long script_LShift(long nVal, long nShift)
{
	return (nVal << nShift);
}

long script_RShift(long nVal, long nShift)
{
	return (nVal >> nShift);
}

long script_MkWord(long nHigh, long nLow)
{
	return ((nHigh << 16) + nLow);
}


//////////////////////////////////////////////////////////////////////////
//time
SYSTEMTIME g_tmCurrScript;

long script_GetYear()
{
	::GetLocalTime(&g_tmCurrScript);
	return g_tmCurrScript.wYear;
}

long script_GetMonth()
{
	return g_tmCurrScript.wMonth;
}

long script_GetDay()
{
	return g_tmCurrScript.wDay;
}

long script_GetHour()
{
	return g_tmCurrScript.wHour;
}

long script_GetMinute()
{
	return g_tmCurrScript.wMinute;
}

long script_GetSecond()
{
	return g_tmCurrScript.wSecond;
}

long script_GetMillionSecond()
{
	return g_tmCurrScript.wMilliseconds;
}

const char* script_GetSystemTime()
{
	::GetLocalTime(&g_tmCurrScript);

	sprintf(g_pszPpScriptReturn, "%d-%d-%d %d:%d:%d %d", g_tmCurrScript.wYear
		, g_tmCurrScript.wMonth, g_tmCurrScript.wDay
		, g_tmCurrScript.wHour, g_tmCurrScript.wMinute, g_tmCurrScript.wSecond
		, g_tmCurrScript.wMilliseconds);

	return g_pszPpScriptReturn;
}


//////////////////////////////////////////////////////////////////////////
//BCD/HEX
long script_BcdToHex(long nVal)
{
	long nValue =           nVal & 0x00000000F;
	nValue += 10       * (( nVal & 0x000000F0 ) >> 4);
	nValue += 100      * (( nVal & 0x00000F00 ) >> 8);
	nValue += 1000     * (( nVal & 0x00000F00 ) >> 12);
	nValue += 10000    * (( nVal & 0x000F0000 ) >> 16);
	nValue += 100000   * (( nVal & 0x00F00000 ) >> 20);
	nValue += 1000000  * (( nVal & 0x00F00000 ) >> 24);
	nValue += 10000000 * (( nVal & 0x0F000000 ) >> 28);
	//nValue += ( nVal & 0x000000F0 ) >> 4;

	return nValue;
}

long script_HexToBcd(long nVal)
{
	long nRet = nVal % 10;
	nVal /= 10;
	nRet += (nVal % 10) << 4;

	nVal /= 10;
	nRet += (nVal % 10) << 8;

	nVal /= 10;
	nRet += (nVal % 10) << 12;

	nVal /= 10;
	nRet += (nVal % 10) << 16;

	nVal /= 10;
	nRet += (nVal % 10) << 20;

	return nRet;
}

const char* script_StrBcdToHex(const char*)
{
	return NULL;
}

const char* script_StrHexToBcd(const char*)
{
	return NULL;
}


//////////////////////////////////////////////////////////////////////////
//timer
void script_KillTimer(const char *pszTimerID)
{
	
}

void script_ResetTimer(const char *pszTimerID)
{

}

void script_SetTimerLong(const char *pszTimerID, long nMs)
{

}


long script_GetBitInLong(long nValue, long nBitIndex)
{
	long n = 1;
	n = n << nBitIndex;
	n = nValue & n;
	n = n >> nBitIndex;

	return n;
}

//双点
long script_GetBitInLong2(long nValue, long nBitIndex)
{
	long n = 3;
	nBitIndex = nBitIndex*2;
	n = n << nBitIndex;
	n = nValue & n;
	n = n >> nBitIndex;

	return n;
}

long script_SetBitInLong(long nValue, long nBitIndex)
{
	long n = 1;
	n = n << nBitIndex;
	n = nValue | n;

	return n;
}

long script_ClearBitInLong(long nValue, long nBitIndex)
{
	long n = 1;
	n = n << nBitIndex;
	n = ~n;
	n = nValue & n;

	return n;
}


long script_GetBitInLong16(long nValue, long nBitIndex)
{
	if (nBitIndex > 15)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                   , g_sLangTxt_ParaBoundsGet.GetString()/*L"GetBitInLong16参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_GetBitInLong(nValue, nBitIndex);
}

long script_Get2BitInLong16(long nValue, long nBitIndex)
{
	if (nBitIndex > 8)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("GetBitInLong8参数nBitIndex=%d越界"), nBitIndex);
		return nValue;
	}

	return script_GetBitInLong2(nValue, nBitIndex);
}

long script_SetBitInLong16(long nValue, long nBitIndex)
{
	if (nBitIndex > 15)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                 , g_sLangTxt_ParaBoundsSet.GetString()/*L"SetBitInLong16参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_SetBitInLong(nValue, nBitIndex);
}

long script_ClearBitInLong16(long nValue, long nBitIndex)
{
	if (nBitIndex > 15)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsClear.GetString()/*L"ClearBitInLong16参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_ClearBitInLong(nValue, nBitIndex);
}

long script_GetBitInLong32(long nValue, long nBitIndex)
{
	if (nBitIndex > 31)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsGet2.GetString()/*L"GetBitInLong32参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_GetBitInLong(nValue, nBitIndex);
}

long script_SetBitInLong32(long nValue, long nBitIndex)
{
	if (nBitIndex > 31)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsSet2.GetString()/*L"SetBitInLong32参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_SetBitInLong(nValue, nBitIndex);
}

long script_ClearBitInLong32(long nValue, long nBitIndex)
{
	if (nBitIndex > 31)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsClear2.GetString()/*L"ClearBitInLong32参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_ClearBitInLong(nValue, nBitIndex);
}


long script_GetBitInLong8(long nValue, long nBitIndex)
{
	if (nBitIndex > 7)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsGet3.GetString()/*L"GetBitInLong8参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_GetBitInLong(nValue, nBitIndex);
}

long script_SetBitInLong8(long nValue, long nBitIndex)
{
	if (nBitIndex > 7)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsSet3.GetString()/*L"SetBitInLong8参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_SetBitInLong(nValue, nBitIndex);
}

long script_ClearBitInLong8(long nValue, long nBitIndex)
{
	if (nBitIndex > 7)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsClear3.GetString()/*L"ClearBitInLong8参数nBitIndex=%d越界"*/, nBitIndex);
		return nValue;
	}

	return script_ClearBitInLong(nValue, nBitIndex);
}

long script_GetBitRangeInLong8(long nValue, long nBitStart, long nBitEnd)
{
	if (nBitStart >= nBitEnd || nBitEnd > 8)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_ParaBoundsGet4.GetString()/*L"script_GetBitRangeInLong8参数nBitEnd=%d越界"*/, nBitEnd);
		return nValue;
	}

	long n = 0;
	for (int i = nBitStart; i <= nBitEnd; i++)
	{
		n |= (1 << (i - 1));
	}

	n = nValue & n;
	n = n >> (nBitStart - 1);
	return n;
}

extern long g_nSttLogServerDebugInfor;

void script_LogPrint(const char *pszVariableID,long nValue)
{
	if (g_nSttLogServerDebugInfor)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("\"%s\" = %d")
			, pszVariableID,nValue);
	}
}

void script_ShowMsg(const char *pszMsg)
{
	if (g_nSttLogServerDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, CString(pszMsg));
	}
}

//范围内的随机数
double script_RandInRange(float fMinVal, float fMaxValue)
{
	float fRange = fMaxValue - fMinVal;

	long nRand = rand();
	nRand = nRand %20000;;
	float fRate = nRand / 20000.0f;

	float fValue = fMinVal + fRange * fRate;;
	return fValue;
}

long script_FloatToLong(float fValue)
{
	long nVal = fValue;
	float fDot = fValue - nVal;
	fDot *= 100;
	long nDot = fDot;

	if (nDot >= 49)
	{
		nVal += 1;
	}

	return nVal;
}

//获取指定数位的数值
long script_GetFloatDigit(float fValue, long nDigit)
{
	long nValue = (long)fValue;
	long nRet = 0;

	if (nDigit >= 0)
	{
		while (nDigit > 0)
		{
			nValue = nValue / 10;
			nDigit--;
		}

		nRet = nValue % 10;
	}
	else
	{
		float fValue2 = fValue - nValue;
		
		while (nDigit < 0)
		{
			fValue2 = fValue2 * 10;
			nDigit++;
		}

		nValue = (long)fValue2;
		nRet = nValue % 10;
	}

	return nRet;
}

//时间转换函数
void Convert_UTC_To_BCD(SYSTEMTIME* lpTimeBCD, UINT UTCTime)
{
	UINT  EvenYearSec=0, LeapYearSec=0, YearSec=0;
	UINT  BigMonthSec=0, SmallMonthSec=0, FebruarySec=0;
	UINT	  wYear=0, wMinute=0, wSecond=0;
	BYTE  wMonth=0,wDay=0,wHour=0;
	UINT   byLeapYear=0, YearLoop=0, byDaysMonth=0, i=0;
	long  MonthSec[12];
	long  IntergerSecond=0;
	double msBase=1,val=0;

	IntergerSecond = UTCTime;

	/*Regard of the time-zone*/
	//IntergerSecond += 8 * 60 * 60;

	/* Calculate the Year */
	EvenYearSec = 365 * 24 * 60 * 60;
	LeapYearSec = 366 * 24 * 60 * 60;

	YearLoop = (UINT)( IntergerSecond / ( 3 * EvenYearSec + LeapYearSec ) );
	IntergerSecond %= ( 3 * EvenYearSec + LeapYearSec );
	wYear = 1970 + 4 * YearLoop;

	if( ( 3 * EvenYearSec + LeapYearSec ) > IntergerSecond )
	{
		if( ( 2 * EvenYearSec + LeapYearSec ) <= IntergerSecond )
		{
			wYear += 3; 
			IntergerSecond -= ( 2 * EvenYearSec + LeapYearSec );
		}
		if( ( 2 * EvenYearSec ) <= IntergerSecond )
		{
			wYear += 2;
			byLeapYear = 1;
			IntergerSecond -= ( 2 * EvenYearSec );
		}
		if( EvenYearSec <= IntergerSecond )
		{
			wYear += 1;
			IntergerSecond -= EvenYearSec;
		}
	}
	lpTimeBCD->wYear = wYear;

	/* Calculate the Month */
	BigMonthSec = 31 * 24 * 60 * 60;
	SmallMonthSec = 30 * 24 * 60 * 60;
	if( byLeapYear ){
		FebruarySec = 29 * 24 * 60 * 60;
		YearSec = LeapYearSec;
	}
	else{
		FebruarySec = 28 * 24 * 60 * 60;
		YearSec = EvenYearSec;
	}
	for(i=1; i<=12; i++)
	{
		if( i==2 )
		{
			MonthSec[i-1] = FebruarySec;
			continue;
		}
		else if( i==4 || i==6 || i==9 || i==11 )
		{
			MonthSec[i-1] = SmallMonthSec;
			continue;
		}
		else
		{
			MonthSec[i-1] = BigMonthSec;
			continue;
		}
	}
	for(i=0; i<12; i++)
	{
		IntergerSecond -= MonthSec[i]; 
		if( IntergerSecond < 0 )
		{
			IntergerSecond += MonthSec[i];
			wMonth = i + 1;
			break;
		}
	}
	lpTimeBCD->wMonth = wMonth;

	/* Calculate the Day */
	for(i=1; i<=31; i++)
	{
		IntergerSecond -= 24 * 60 * 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 24 * 60 * 60;
			wDay = i;
			break;
		}
	}
	lpTimeBCD->wDay = wDay;

	/* Calculate the Hour */
	for(i=0; i<=24; i++)
	{
		IntergerSecond -= 60 * 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 60 * 60;
			wHour = i;
			break;
		}
	}
	lpTimeBCD->wHour = wHour;

	/* Calculate the Minute */
	for(i=0; i<=60; i++)
	{
		IntergerSecond -= 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 60;
			wMinute = i;
			break;
		}
	}
	lpTimeBCD->wMinute = wMinute;

	/* Evaluate the Second */
	lpTimeBCD->wSecond = IntergerSecond;

	lpTimeBCD->wMilliseconds = 0;
}

const char* script_GetTimeStr1970(CTScriptSingleVM *pXvm, long nSeconds)
{
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("nSeconds=%d"), nSeconds);
	//nSeconds = nSeconds - 28800;
	char *pszReturn = pXvm->GetChReurn();
	SYSTEMTIME tmSys;

	Convert_UTC_To_BCD(&tmSys, nSeconds);
	sprintf(pszReturn, "%d-%d-%d %d:%d:%d", tmSys.wYear, tmSys.wMonth, tmSys.wDay
		, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);

	return pszReturn;
}

#include "../../../Module/GpsPcTime/GpsPcTime.h"

long script_GetTimeLong1970(const char *pszTime)
{
	CGpsPcTime oTime;
	CString strTime;
	strTime = pszTime;
	oTime.FromString(strTime);

	struct tm   tmTime;
	ZeroMemory(&tmTime, sizeof(tmTime));
	tmTime.tm_year = oTime.m_wYear - 1900;
	tmTime.tm_mon = oTime.m_wMonth - 1;
	tmTime.tm_mday = oTime.m_wDay;
	tmTime.tm_hour = oTime.m_wHour;
	tmTime.tm_min = oTime.m_wMinute;
	tmTime.tm_sec = oTime.m_wSecond;

	long nTime = mktime(&tmTime);

	if (nTime == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetTimeLong1970(%s) error......", pszTime);
	}
	else
	{
		//8小时时差
		nTime += 28800;
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetTimeLong1970(%s) = %d ......", pszTime, nTime);
	}

	return nTime;
}

//2023-1-31  lijunqing
const char* script_GetTimeStr1970_ms(CTScriptSingleVM *pXvm, __int64 n64Ms)
{
	char *pszReturn = pXvm->GetChReurn();
	SYSTEMTIME tmSys;
	__int64 nSeconds = n64Ms / 1000;
	long nMsLeft = n64Ms - nSeconds * 1000;

	Convert_UTC_To_BCD(&tmSys, nSeconds);
	sprintf(pszReturn, "%d-%d-%d %d:%d:%d %d", tmSys.wYear, tmSys.wMonth, tmSys.wDay
		, tmSys.wHour, tmSys.wMinute, tmSys.wSecond, nMsLeft);

	return pszReturn;
}

__int64 script_GetTimeLong1970_ms(const char *pszTime)
{
	CGpsPcTime oTime;
	CString strTime;
	strTime = pszTime;
	oTime.FromString(strTime);

	struct tm   tmTime;
	ZeroMemory(&tmTime, sizeof(tmTime));
	tmTime.tm_year = oTime.m_wYear - 1900;
	tmTime.tm_mon = oTime.m_wMonth - 1;
	tmTime.tm_mday = oTime.m_wDay;
	tmTime.tm_hour = oTime.m_wHour;
	tmTime.tm_min = oTime.m_wMinute;
	tmTime.tm_sec = oTime.m_wSecond;

	long nTime = mktime(&tmTime);
	__int64 n64Ms = 0;

	if (nTime == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetTimeLong1970(%s) error......", pszTime);
	}
	else
	{
		//8小时时差
		nTime += 28800;
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetTimeLong1970(%s) = %d ......", pszTime, nTime);
		n64Ms = nTime;
		n64Ms *= 1000;
		n64Ms += oTime.m_wMilliseconds;
	}

	return n64Ms;
}

void script_Sleep(long time)
{
	Sleep(time);
}
