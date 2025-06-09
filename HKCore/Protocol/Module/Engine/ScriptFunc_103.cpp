#include "StdAfx.h"
#include "ScriptFunc_103.h"
#include "ScriptFunc_Engine.h"

#include "PpDevBaseApp.h"
#include "BbData.h"
#include "../XLanguageResourcePp.h"
#include "PpEngineDataMngrCntr.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


long script_GetMEA(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	long nValue = script_GetBbCurrValue(pXvm, nIndex, nBytes);

	if ((nValue & 0x8000) != 0)
	{// 溢出
		nValue = (~nValue) + 1;
		return -1*((nValue & 0x7FFF)>>3);
	}
	else
	{// 不溢出
		return nValue>>3;
	}
}

long script_CalMEA(long nValue)
{
	long nMea = 0;

	if (nValue < 0)
	{
		nMea = -nValue;
		nMea = nMea << 3;
		nMea &= 0x7FFF;
		nMea -= 1;
		nMea = ~nMea;
		nMea |= 0x8000;
	}
	else
	{
		nMea = (nValue << 3);
	}

	return nMea;
}

const char* script_GetCP32Time2a(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	//CPpDevBaseApp* pApp = g_thePpDevBaseApp;
	char *pszReturn = pXvm->GetChReurn();
	//ZeroMemory(pXvm->m_chReturn, LUA_RETURN_STRING_LEN);
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	BOOL bTrue = FALSE;

	if (pByteBlock != NULL)
	{
		if (pByteBlock->m_pBuffer != NULL)
		{
			long nLength = pByteBlock->GetByteBlockLength();
			if (nIndex>=0 && nBytes == 4 && (nIndex+nBytes) <= nLength)
			{
				long nMilliseconds, nSeconds, nMinutes, nIV, nHours, nSU;
				nMilliseconds = MAKEWORD(pByteBlock->m_pBuffer[nIndex], pByteBlock->m_pBuffer[nIndex+1]);
				nSeconds = nMilliseconds/1000;
				nMilliseconds = nMilliseconds%1000;
				nMinutes = pByteBlock->m_pBuffer[nIndex+2] & 0x3F;
				nIV = (pByteBlock->m_pBuffer[nIndex+2] & 0x80)==0?0:1;
				nHours = pByteBlock->m_pBuffer[nIndex+3] & 0x1F;
				nSU = (pByteBlock->m_pBuffer[nIndex+3] & 0x80)==0?0:1;
			
				if (nIV == 0)
				{// 数据有效
					CString strTime;
					strTime.Format(_T("%.2d:%.2d:%.2d.%.3d"), nHours, nMinutes, nSeconds, nMilliseconds);
					CString_to_char(strTime, pszReturn);
					bTrue = TRUE;
				}
			}
		}
	}	

	if (!bTrue)
	{
		strcpy(pszReturn, "0:0:0.0");
	}

	return pszReturn;
}

const char* script_GetCP24Time2a(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	char *pszReturn = pXvm->GetChReurn();
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if (pByteBlock != NULL)
	{
		long nLength = pByteBlock->GetByteBlockLength();
		if (nIndex>=0 && nBytes == 3 && (nIndex+nBytes) <= nLength)
		{
			long nMilliseconds, nSeconds, nMinutes, nIV;
			nMilliseconds = MAKEWORD(pByteBlock->m_pBuffer[nIndex], pByteBlock->m_pBuffer[nIndex+1]);
			nSeconds = nMilliseconds/1000;
			nMilliseconds = nMilliseconds%1000;
			nMinutes = pByteBlock->m_pBuffer[nIndex+2] & 0xFC;
			nMinutes = nMinutes>>2;
			nIV = (pByteBlock->m_pBuffer[nIndex+2] & 1)==0?0:1;

			if (nIV == 0)
			{// 数据有效
				CString strTime;
				strTime.Format(_T("%.2d.%.3d"), nMinutes, nMilliseconds);
				CString_to_char(strTime, pszReturn);
			}
		}
	}	
	return pszReturn;
}

const char* script_GetCP56Time2a(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	char *pszReturn = pXvm->GetChReurn();
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	strcpy(pszReturn, "0-0-0 0:0:0.0");

	if (pByteBlock != NULL)
	{
		long nLength = pByteBlock->GetByteBlockLength();
		if (nIndex>=0 && nBytes == 7 && (nIndex+nBytes) <= nLength)
		{
			long nMilliseconds = 0, nSeconds = 0, nMinutes = 0, nIV = 0, nHours = 0, nSU = 0, nDayOfMonth = 0, nDayOfWeek = 0, nMonths = 0, nYears = 0;
		
			if (pByteBlock->m_pBuffer != NULL)
			{
				nMilliseconds = MAKEWORD(pByteBlock->m_pBuffer[nIndex], pByteBlock->m_pBuffer[nIndex+1]);
				nSeconds = nMilliseconds/1000;
				nMilliseconds = nMilliseconds%1000;
				nMinutes = pByteBlock->m_pBuffer[nIndex+2] & 0x3F;
				nIV = (pByteBlock->m_pBuffer[nIndex+2] & 0x80)==0?0:1;
				nHours = pByteBlock->m_pBuffer[nIndex+3] & 0x1F;
				nSU = (pByteBlock->m_pBuffer[nIndex+3] & 0x80)==0?0:1;
				nDayOfMonth = pByteBlock->m_pBuffer[nIndex+4] & 0x1F;
				nDayOfWeek = (pByteBlock->m_pBuffer[nIndex+4] & 0xE0)>>5;
				nMonths = pByteBlock->m_pBuffer[nIndex+5] & 0x0F;
				nYears = pByteBlock->m_pBuffer[nIndex+6]+2000;
			}

			if (nIV == 0)
			{// 数据有效
				CString strTime;
				strTime.Format(_T("%d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d"), nYears, nMonths, nDayOfMonth, nHours, nMinutes, nSeconds, nMilliseconds);
				CString_to_char(strTime, pszReturn);
			}
		}
	}	

	return pszReturn;
}

//设置当前ByteBlock的缓冲数据  nIndex为索引值，从1开始编号
/*
year=GetYear()-2000;    month=GetMonth();    
day=GetDay();
hour=GetHour();      minute=GetMinute();    
second=GetSecond();      ms=GetMSecond();
ms=ms+second*1000;
nVal=GetBindDataL("value")+1;
nSIN = 0;

SetBbValLong(0, nVal, 1);
SetBbValLong(1, ms, 2);
SetBbValLong(3, minute, 1);
SetBbValLong(4, hour, 1);
SetBbValLong(5, day, 1);
SetBbValLong(6, month, 1);
SetBbValLong(7, year, 1);
SetBbValLong(8, nSIN, 1);
*/
void script_SetBbCurrValueCP56Time2a(long nIndex, BYTE *pBuffer, SYSTEMTIME &tm)
{
	long nS = tm.wMilliseconds + tm.wSecond * 1000;

	//秒＋毫秒
	memcpy(pBuffer, &nS, 2);
	pBuffer+=2;

	//分
	*pBuffer = (BYTE)tm.wMinute;
	pBuffer++;

	//时
	*pBuffer = (BYTE)tm.wHour;
	pBuffer++;

	//日
	*pBuffer = (BYTE)tm.wDay;
	pBuffer++;

	//月
	*pBuffer = (BYTE)tm.wMonth;
	pBuffer++;

	//年
	*pBuffer = (BYTE)tm.wYear-2000;
	pBuffer++;
}
void script_SetBbCurrValueCP56Time2a(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+7) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				SYSTEMTIME tm;
				::GetLocalTime(&tm);
				script_SetBbCurrValueCP56Time2a(nIndex, pByteBlock->m_pBuffer, tm);
				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataBufferError.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex);
	}
}

void script_SetBbCurrValueCP56Time2aEx(CTScriptSingleVM *pXvm, long nIndex, const char *pszDateTime)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+7) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				if (strcmp(pszDateTime, "0") == 0)
				{
					memset(pByteBlock->m_pBuffer + nIndex, 0, 7);
					return;
				}

				CString strTime;
				strTime = pszDateTime;
				CGpsPcTime oGpsTime;
				oGpsTime.FromString(strTime);
				SYSTEMTIME tm;
				oGpsTime.GetSysTime(tm);
			
				/*COleDateTime oTime;
				CString strMilliseconds = _T("0");
				strTime.Replace(_T("\""), _T(""));
				int nIndex = strTime.ReverseFind('.');
				if (nIndex != -1)
				{
					strMilliseconds = strTime.Right(strTime.GetLength() - 1 - nIndex);
					strTime = strTime.Left(nIndex);
				}
				oTime.ParseDateTime(strTime);
				oTime.GetAsSystemTime(tm);
				tm.wMilliseconds = _ttoi(strMilliseconds);*/
				script_SetBbCurrValueCP56Time2a(nIndex, pByteBlock->m_pBuffer, tm);
				bTrue = TRUE;
			}
		}
	}
	
}

void script_SetBbCurrValue48TimeMs(long nIndex, BYTE *pBuffer, __int64 n64Ms)
{
	//1
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;

	//2
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;

	//3
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;

	//4
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;

	//5
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;

	//6
	*pBuffer = n64Ms & 0xFF;
	n64Ms = n64Ms >> 8;
	pBuffer++;
}

void script_SetBbCurrValue48TimeMs(CTScriptSingleVM *pXvm, long nIndex, const char *pszDateTime)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+6) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				if (strcmp(pszDateTime, "0") == 0)
				{
					memset(pByteBlock->m_pBuffer + nIndex, 0, 7);
					return;
				}

				CString strTime;
				strTime = pszDateTime;
				CGpsPcTime oGpsTime;

				if (strTime.GetLength() > 10)
				{
					oGpsTime.FromString(strTime);
				}
			
				__int64 n64Ms = oGpsTime.GetTime_Int64();
				n64Ms *= 1000;
				n64Ms += oGpsTime.m_wMilliseconds;
				script_SetBbCurrValue48TimeMs(nIndex, pByteBlock->m_pBuffer, n64Ms);
				bTrue = TRUE;
			}
		}
	}
}

void script_SetBbCurrValueCP32Time2a(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+4) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				SYSTEMTIME tm;
				::GetLocalTime(&tm);
				long nS = tm.wMilliseconds + tm.wSecond * 1000;
				BYTE *pBuffer = pByteBlock->m_pBuffer + nIndex;

				//秒＋毫秒
				memcpy(pBuffer, &nS, 2);
				pBuffer+=2;

				//分
				*pBuffer = (BYTE)tm.wMinute;
				pBuffer++;

				//时
				*pBuffer = (BYTE)tm.wHour;
				pBuffer++;

				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
            , g_sLangTxt_DataBufferError.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex);
	}
}
      
void script_SetBbCurrValueCP24Time2a(CTScriptSingleVM *pXvm, long nIndex)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if(pByteBlock == NULL)
	{
		return;
	}

	BOOL bTrue = FALSE;
	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex >= 0 && nIndex < nLength)
	{
		if ((nIndex+3) <= nLength)
		{
			if (pByteBlock->m_pBuffer != NULL)
			{
				SYSTEMTIME tm;
				::GetLocalTime(&tm);
				long nS = tm.wMilliseconds;
				BYTE *pBuffer = pByteBlock->m_pBuffer + nIndex;

				//秒＋毫秒
				memcpy(pBuffer, &nS, 2);
				pBuffer+=2;

				//分
				BYTE nMinute =  (BYTE)tm.wMinute;
				nMinute *=4;
				*pBuffer = nMinute;
				pBuffer++;

				bTrue = TRUE;
			}
		}
	}

	if (!bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_DataBufferError.GetString()/*L"字节块[%s]数据缓冲错误：nIndex=%d"*/
            , pByteBlock->m_strID.GetString(), nIndex);
	}
}

float script_GetIEEE754(CTScriptSingleVM *pXvm, long nIndex)
{
	char *pszReturn = pXvm->GetChReurn();
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	float fReturn = 0.0f;


	if (pByteBlock != NULL)
	{
		long nLength = pByteBlock->GetByteBlockLength();
		if ( ((nLength - nIndex) >= 4) && (pByteBlock->m_pBuffer != NULL) )
		{
			unsigned char tmp_char[4];
			tmp_char[0]=pByteBlock->m_pBuffer[nIndex];
			tmp_char[1]=pByteBlock->m_pBuffer[nIndex+1];
			tmp_char[2]=pByteBlock->m_pBuffer[nIndex+2];
			tmp_char[3]=pByteBlock->m_pBuffer[nIndex+3];
			fReturn = *((float *)tmp_char);
		}
	}

	return fReturn;
}

void script_SetIEEE754(CTScriptSingleVM *pXvm, long nIndex, float fValue)
{
	char *pszReturn = pXvm->GetChReurn();
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	long nLength = pByteBlock->GetByteBlockLength();
	
	//if ((nLength-nIndex) == 4)
	if ( ((nLength - nIndex) >= 4) && (pByteBlock->m_pBuffer != NULL) )
	{
		unsigned char *pValue = (unsigned char*)(&fValue);
		pByteBlock->m_pBuffer[nIndex]=*(pValue++);
		pByteBlock->m_pBuffer[nIndex+1]=*(pValue++);
		pByteBlock->m_pBuffer[nIndex+2]=*(pValue++);
		pByteBlock->m_pBuffer[nIndex+3]=*(pValue++);
	}
	
}

const char* script_GetASCII(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	char *pszReturn = pXvm->GetChReurn();
	pszReturn[0] = 0;
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	
	if (pByteBlock != NULL)
	{
		long nLength = pByteBlock->GetByteBlockLength();
		for (long nIndexEx=nIndex; nIndexEx<nLength; nIndexEx++)
		{
			pszReturn[nIndexEx-nIndex]=pByteBlock->m_pBuffer[nIndexEx];
		}
	}

	return pszReturn;
}

//2018-5-30  集成PM
const char* script_GetXujiTime(CTScriptSingleVM *pXvm, long nIndex,long nBytes)
{
	char *pszReturn = pXvm->GetChReurn();
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	pszReturn[0] = 0;

	if (pByteBlock != NULL)
	{
		long nLength = pByteBlock->GetByteBlockLength();
		if (nIndex>=0 && nBytes == 7 && (nIndex+nBytes) <= nLength)
		{
			long nMilliseconds, nSeconds, nMinutes,/* nIV, */nHours, /*nSU, */nDayOfMonth, /*nDayOfWeek, */nMonths, nYears;
			//nMilliseconds = pByteBlock->m_pBuffer[nIndex+6]*256 + pByteBlock->m_pBuffer[nIndex+7];
			//nSeconds = pByteBlock->m_pBuffer[nIndex+5];
			int nMillisecondsHigh = (pByteBlock->m_pBuffer[nIndex+5] & 0xC0)/64;
			nSeconds = (pByteBlock->m_pBuffer[nIndex+5] & 0x3F);
			nMilliseconds = pByteBlock->m_pBuffer[nIndex+6] + nMillisecondsHigh*256;
			nMinutes = pByteBlock->m_pBuffer[nIndex+4];
			nHours = pByteBlock->m_pBuffer[nIndex+3];
			nDayOfMonth = pByteBlock->m_pBuffer[nIndex+2];
			nMonths = pByteBlock->m_pBuffer[nIndex+1];
			nYears = pByteBlock->m_pBuffer[nIndex];
			CString strTime;
			strTime.Format(_T("%d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d"), nYears, nMonths, nDayOfMonth, nHours, nMinutes, nSeconds, nMilliseconds);
			CString_to_char(strTime, pszReturn);
			//}
		}
	}	

	return pszReturn;
}
