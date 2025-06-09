// GlobalApi.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GlobalApi.h"
#include "FileApi.h"

#ifndef _PSX_IDE_QT_
#include "VC/GlobalApi_VC.cpp"
#else
#include "QT/GlobalApi_QT.cpp"
#endif


BOOL IsStringNumber(const char* pszString)
{
    BOOL bIsReal = TRUE;
    long nDotCount = 0;
    long nSignalCount = 0;
    long nIndex = 0;
    long nIsE = 0;

    ASSERT(pszString != NULL);
    long nLen = strlen(pszString);

    for(nIndex=0; nIndex < nLen; ++nIndex)
    {
        if( !( (pszString[nIndex] >= '0') && (pszString[nIndex] <= '9') ) )
        {
            if( (pszString[nIndex] == '-' || pszString[nIndex] == '+') )
            {
                nSignalCount++;
            }
            else if (pszString[nIndex] == '.')
            {
                nDotCount++;
            }
            else if (pszString[nIndex] == 'E'|| pszString[nIndex] == 'e')
            {
                nIsE++;
            }
            else if (pszString[nIndex] == ' ')
            {
            }
            else
            {
                bIsReal = FALSE;
                break;
            }
        }
    }

    if (nIsE > 0)
    {
        if (nSignalCount > 2 || nDotCount > 1 )
        {//?§Ø??????????§³?????????
            bIsReal = FALSE;
        }
    }
    else
    {
        if (nSignalCount > 1 || nDotCount > 1 )
        {//?§Ø??????????§³?????????
            bIsReal = FALSE;
        }
    }

    return bIsReal;
}

BOOL IsStringNumber(CString &strString)
{
    BOOL bIsReal = TRUE;
    long nDotCount = 0;
    long nSignalCount = 0;
    long nIndex = 0;
    long nIsE = 0;

    long nLen = strString.GetLength();
    TCHAR ch;

    for(nIndex=0; nIndex < nLen; ++nIndex)
    {
        ch = strString.GetAt(nIndex);

        if( !( (ch >= '0') && (ch <= '9') ) )
        {
            if( (ch == '-' || ch == '+') )
            {
                nSignalCount++;
            }
            else if (ch == '.')
            {
                nDotCount++;
            }
            else if (ch == 'E'|| ch == 'e')
            {
                nIsE++;
            }
            else if (ch == ' ')
            {
            }
            else
            {
                bIsReal = FALSE;
                break;
            }
        }
    }

    if (nIsE > 0)
    {
        if (nSignalCount > 2 || nDotCount > 1 )
        {//?§Ø??????????§³?????????
            bIsReal = FALSE;
        }
    }
    else
    {
        if (nSignalCount > 1 || nDotCount > 1 )
        {//?§Ø??????????§³?????????
            bIsReal = FALSE;
        }
    }

    return bIsReal;
}


BOOL IsStringNumber(const wchar_t *pszString)
{
    BOOL bIsReal = TRUE;
    long nDotCount = 0;
    long nSignalCount = 0;
    long nIndex = 0;

    ASSERT(pszString != NULL);
    long nLen = wcslen(pszString);

    for(nIndex=0; nIndex < nLen; ++nIndex)
    {
        if( !( (pszString[nIndex] >= '0') && (pszString[nIndex] <= '9') ) )
        {
            if( (nIndex == 0) && (pszString[nIndex] == '-' || pszString[nIndex] == '+') )
            {
                nSignalCount++;
            }
            else if (pszString[nIndex] == '.')
            {
                nDotCount++;
             }
            else
            {
                bIsReal = FALSE;
                break;
            }
        }
    }

    if (nSignalCount > 1 || nDotCount > 1 )
    {//?§Ø??????????§³?????????
        bIsReal = FALSE;
    }

    return bIsReal;
}


//2021-5-30  lijunqig
BOOL IsStringInteger(const char* pszString)
{
	long nIndex = 0;

	ASSERT(pszString != NULL);
	long nLen = strlen(pszString);

	if( (pszString[0] == '-' || pszString[0] == '+') )
	{
		nIndex++;
	}

	for(; nIndex < nLen; ++nIndex)
	{
		if( !( (pszString[nIndex] >= '0') && (pszString[nIndex] <= '9') ) )
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL IsStringInteger(CString &strString)
{
	long nIndex = 0;

	long nLen = strString.GetLength();
	TCHAR ch;

	ch = strString.GetAt(0);

	if( (ch == '-' || ch == '+') )
	{
		nIndex++;
	}

	for(; nIndex < nLen; ++nIndex)
	{
		ch = strString.GetAt(nIndex);

		if( !( (ch >= '0') && (ch <= '9') ) )
		{
			return FALSE;
		}
	}

	return TRUE;
}


BOOL ChopIsStringFloat(char* pszFloatString, long &nDoPOS)
{
    BOOL bIsReal = TRUE;
    long nDotCount = 0;
    long nSignalCount = 0;
    long nIndex = 0;

    nDoPOS = -1;
    ASSERT(pszFloatString != NULL);
    long nLen = strlen(pszFloatString);

    for(nIndex=0; nIndex < nLen; ++nIndex)
    {
        if( !( (pszFloatString[nIndex] >= '0') && (pszFloatString[nIndex] <= '9') ) )
        {
            if( (nIndex == 0) && (pszFloatString[nIndex] == '-' || pszFloatString[nIndex] == '+') )
            {
                nSignalCount++;
            }
            else if (pszFloatString[nIndex] == '.')
            {
                nDotCount++;
                nDoPOS = nIndex;
            }
            else
            {
                bIsReal = FALSE;
            }
        }
    }

    if (nSignalCount > 1 || nDotCount > 1 )
    {//?§Ø??????????§³?????????
        bIsReal = FALSE;
    }

    return bIsReal;
}

char* ChopFloatString(char* pszFloatString, long nDecimal)
{
    BOOL bIsReal = TRUE;
    long nIndex = 0;
    long nDoPOS = -1;

    ASSERT(pszFloatString != NULL);
    long nLen = strlen(pszFloatString);

    bIsReal = ChopIsStringFloat(pszFloatString, nDoPOS);

    if (bIsReal)
    {
        if (nDoPOS == -1)
        {
            if (nDecimal > 0)
            {
                nDoPOS = nLen;
                pszFloatString[nDoPOS] = '.';

                for (nIndex=1; nIndex<=nDecimal; nIndex++)
                {
                    pszFloatString[nDoPOS+nIndex] = '0';
                }

                pszFloatString[nDoPOS+nIndex] = 0;
            }
        }
        else
        {
            //????§³????¦Ë??
            if (nDecimal >= 0)
            {
                nLen = strlen(pszFloatString);

                if(nDecimal+nDoPOS > nLen)
                {
                    for (nIndex=nLen-1; nIndex<nDecimal+nDoPOS; nIndex++)
                    {
                        pszFloatString[nIndex] = '0';
                    }

                    pszFloatString[nIndex+1] = '\0';
                    nLen = nDecimal+nDoPOS;
                }

                nIndex = nDoPOS + nDecimal;

                if (pszFloatString[nIndex+1] >= '5')
                {
                    for (; nIndex>=0; nIndex--)
                    {
                        if (pszFloatString[nIndex] == '.')
                        {
                            nIndex--;

                            if (nIndex == -1)
                            {
                                break;
                            }
                        }

                        if (pszFloatString[nIndex] >= '9')
                        {
                            pszFloatString[nIndex] = '0';
                        }
                        else
                        {
                            pszFloatString[nIndex]++;
                            break;
                        }
                    }

                    if (nIndex == -1)
                    {
                        char *pTemp = pszFloatString + nLen;
                        *(pTemp + 1) = 0;
                        *(pTemp + 2) = 0;
                        while (pTemp >= pszFloatString)
                        {
                            *(pTemp+1) = *pTemp;
                            pTemp--;
                        }

                        pszFloatString[0] = '1';
                        pszFloatString[nDoPOS+nDecimal+2] = 0;
                    }
                    else
                    {
                        pszFloatString[nDoPOS+nDecimal+1] = 0;
                    }
                }
                else
                {
                    pszFloatString[nDoPOS+nDecimal+1] = 0;
                }
            }
            else
            {
                for (nIndex=nLen-1; nIndex>nDoPOS; nIndex--)
                {//?????0
                    if(pszFloatString[nIndex] !='0')
                        break;

                    if( (pszFloatString[nIndex]=='0') && (pszFloatString[nIndex-1] != '0') )
                    {
                        if(pszFloatString[nIndex-1]=='.')
                        {
                            if (nDecimal == -1)
                            {
                                pszFloatString[nIndex-1] = 0;
                            }
                        }
                        else
                        {
                            pszFloatString[nIndex]=0;
                        }

                        break;
                    }
                    else
                    {
                        pszFloatString[nIndex]=0;
                    }
                }
            }
        }
    }

    nLen = strlen(pszFloatString);

    if (pszFloatString[nLen-1] == '.')
    {
        pszFloatString[nLen-1] = 0;
    }

    return pszFloatString;
}

#define _CHOP_FLOAT_STRING_MAX_LEN 20
void ChopFloatString(CString &strValue, long nDecimal)
{
    if (strValue.GetLength() >= _CHOP_FLOAT_STRING_MAX_LEN-2)
    {
        return;
    }

    char pszResultKeyBuff[_CHOP_FLOAT_STRING_MAX_LEN*2+4];
    CString_to_char(strValue, pszResultKeyBuff);

    //???????????
    if (IsStringNumber(pszResultKeyBuff))
    {
        ChopFloatString(pszResultKeyBuff, nDecimal);
        strValue = pszResultKeyBuff;
    }
}


//////////////////////////////////////////////////////////////////////////
long GetRGBColor(const CString &strRGBColor,COLORREF crDefColor)
{
    char *pBuffer = NULL;

    CString_to_char(strRGBColor, &pBuffer);
    COLORREF cr = GetRGBColor(pBuffer, crDefColor);
    delete pBuffer;
    return cr;
}

long GetRGBColor(const char *pszRGBColor,COLORREF crDefColor)
{
    COLORREF cr = crDefColor;
    if (strlen(pszRGBColor) < 4)
    {
        return crDefColor;
    }

    if ( ! ((pszRGBColor[0] == 'r' || pszRGBColor[0] == 'R')
        && (pszRGBColor[1] == 'g' || pszRGBColor[1] == 'G')
        && (pszRGBColor[2] == 'b' || pszRGBColor[2] == 'B') ) )
    {
        return crDefColor;
    }

    const char *pTemp = NULL;
    const char *pR=NULL,*pG=NULL,*pB=NULL;
    pTemp = pszRGBColor+4;
    pR = pTemp;
    while (*pTemp != 0)
    {
        if (*pTemp == ',')
        {
            if (pG == NULL)
            {
                pG = pTemp+1;
            }
            else
            {
                pB = pTemp+1;
            }
        }
        pTemp++;
    }
    if (pG == NULL || pB == NULL)
    {
        return crDefColor;
    }

    cr = atol(pB);
    cr = cr * 256 + atol(pG);
    cr = cr * 256 + atol(pR);
    return cr;
}

void GetRGBColor(COLORREF crColor,char *pszRGBColor)
{
    sprintf(pszRGBColor,"RGB(%d,%d,%d)",crColor & 0x0ff,(crColor >> 8) & 0x0ff
        ,(crColor >> 16) & 0x0ff);
}

void ChangeSecondsToSystemTime(long nSeconds, SYSTEMTIME &tmSys)
{
    memset(&tmSys, 0, sizeof(SYSTEMTIME));

    tmSys.wSecond = nSeconds % 60;
    nSeconds /= 60;
    tmSys.wMinute = nSeconds % 60;
    nSeconds /= 60;
    tmSys.wHour = (WORD)nSeconds;
}

void ChangeMSecondsToSystemTime(double dMSeconds, SYSTEMTIME &tmSys)
{
    memset(&tmSys, 0, sizeof(SYSTEMTIME));

    double dTime = dMSeconds;
    long nTemp = (long)dTime;

    tmSys.wMilliseconds = nTemp % 1000;

    dTime /= 1000;
    nTemp = (long)dTime;
    tmSys.wSecond = nTemp % 60;

    dTime /= 60;
    nTemp = (long)dTime;
    tmSys.wMinute = nTemp % 60;

    dTime /= 60;
    tmSys.wHour = (WORD)dTime;
}

void ChangeSecondsToSystemTime(double dSeconds, SYSTEMTIME &tmSys)
{
    memset(&tmSys, 0, sizeof(SYSTEMTIME));

    double dTime = dSeconds;
    long nTemp = (long)dTime;
	double dMs = dTime - nTemp;

    tmSys.wMilliseconds = dMs * 1000;

    nTemp = (long)dTime;
    tmSys.wSecond = nTemp % 60;

    dTime /= 60;
    nTemp = (long)dTime;
    tmSys.wMinute = nTemp % 60;

    dTime /= 60;
    tmSys.wHour = (WORD)dTime;
}

void TransSecondsToSystemTime(long nSeconds, CString &strTime)
{
    SYSTEMTIME tmSys;
    ChangeSecondsToSystemTime(nSeconds, tmSys);
    strTime.Format(_T("%d:%d:%d"), tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
}

void TransMSecondsToSystemTime(double dMSeconds, CString &strTime)
{
    SYSTEMTIME tmSys;
    ChangeMSecondsToSystemTime(dMSeconds, tmSys);
    strTime.Format(_T("%d:%d:%d:%d"), tmSys.wHour, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
}

void TransSecondsToSystemTime(double dSeconds, CString &strTime, BOOL bChop)
{
    SYSTEMTIME tmSys;
    ChangeSecondsToSystemTime(dSeconds, tmSys);

	if (bChop)
	{
		if (tmSys.wHour > 0)
		{
			strTime.Format(_T("%d:%d:%d.%d"), tmSys.wHour, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
		}
		else if (tmSys.wMinute > 0)
		{
			strTime.Format(_T("%d:%d.%d"), tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
		}
		else
		{
			strTime.Format(_T("%d.%d"), tmSys.wSecond, tmSys.wMilliseconds);
		}
	}
	else
	{
		strTime.Format(_T("%d:%d:%d:%d"), tmSys.wHour, tmSys.wMinute, tmSys.wSecond, tmSys.wMilliseconds);
	}
}

void GetCurrSystemtimeString(CString &strTime)
{
    SYSTEMTIME tm;
    ::GetLocalTime(&tm);

#ifdef _UNICODE
    strTime.Format(L"%d-%d-%d %d:%d:%d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
#else
    strTime.Format(_T("%d-%d-%d %d:%d:%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
#endif
}

void GetCurrSystemtimeString2(CString &strTime, BOOL bAddColon)
{
    SYSTEMTIME tm;
    ::GetLocalTime(&tm);

    if (bAddColon)
    {
        strTime.Format(_T("%d-%d-%d %d:%d:%d %d: "), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
    }
    else
    {
        strTime.Format(_T("%d-%d-%d %d:%d:%d %d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
    }
}

void GetCurrSystemtimeString2(char *pszTime, BOOL bAddColon)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	if (bAddColon)
	{
		sprintf(pszTime, "%d-%d-%d %d:%d:%d %d: ", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	}
	else
	{
		sprintf(pszTime, "%d-%d-%d %d:%d:%d %d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	}
}

void GetCurrSystemtimeString2_Short(char *pszTime, BOOL bAddColon)
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);

	if (bAddColon)
	{
		sprintf(pszTime, "%02d:%02d:%02d %03d: ", tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	}
	else
	{
		sprintf(pszTime, "%02d:%02d:%02d %03d",tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	}
}

unsigned short CalArrayCrc(unsigned short u16length, char *ptr)
{
    unsigned short  i;
    unsigned short  u16crc;
    u16crc = 0;

    for(i=0; i<u16length; i++)
        u16crc = CalSingleCharCrc(u16crc, *ptr++);
    return(u16crc);
}

unsigned short CalSingleCharCrc(unsigned short u16crc, char input)
{
    char i;
    char temp;
    temp = input;

    for ( i = 0 ; i < 8 ; i ++ )
    {
        if (( temp & 0x80 ) == 0x80 )
        {
            if (( u16crc & 0x8000 ) == 0 )
            {
                u16crc ^= 0x0810 ;
                u16crc = u16crc<<1 ;
                u16crc = u16crc|0x0001 ;
            }
            else
            {
                u16crc = u16crc<<1 ;
                u16crc = u16crc&0xfffe ;
            }
        }
        else
        {
            if (( u16crc & 0x8000 ) != 0 )
            {
                u16crc ^= 0x0810 ;
                u16crc = u16crc<<1 ;
                u16crc = u16crc|0x00001 ;
            }
            else
            {
                u16crc = u16crc<<1 ;
                u16crc = u16crc&0xfffe ;
            }
        }
        temp = temp<<1 ;
    }
    return(u16crc&0xffff);
}
