// StGlobalDefine.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordGlobalDefine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//系统用到的修正系数
double g_pZeroValue[MAX_STRECORD_CHANNELS];//校准零值，单位是V或A
double g_pCoefValue[MAX_STRECORD_CHANNELS];
long g_pChannelFIFOIndex[MAX_STRECORD_CHANNELS];
UINT g_nFIFOUnitSize = 0;
long g_nSampleGap = 1;
DWORD g_dwSampleRate        = STRECORD_SAMPLE_RATE;
DWORD STRECORD_DFT_CAL_LEN    = 2000;


DWORD g_dwRtFilterDataLenPrev = 6;
DWORD g_dwRtFilterDataLenNext = 6;
DWORD g_dwRtFilterDataLenLen  = 13;
long sgc_unSampleGap[9]	= {1, 2, 4, 5, 10, 20, 25, 50, 100};
void _InitUibGenZeroCofValue()
{
	long nIndex = 0;

	for (nIndex=0; nIndex<MAX_STRECORD_CHANNELS; nIndex++)
	{
		g_pZeroValue[nIndex] = 0;
		g_pCoefValue[nIndex] = 0.050;
		g_pChannelFIFOIndex[nIndex] = nIndex;
	}
}

void Ep_InitCTimeByRtTime(RTTIME &rtTime, CTime &tm)
{
	SYSTEMTIME tmSys;
	tmSys.wYear = rtTime.wYear;
	tmSys.wMonth = rtTime.wMonth;
	tmSys.wDay = rtTime.wDay;
	tmSys.wHour = rtTime.wHour;
	tmSys.wMinute = rtTime.wMinute;
	tmSys.wSecond = rtTime.wSecond;
	tmSys.wMilliseconds = rtTime.wMilliseconds;

	tm = tmSys;
}

void Ep_InitEndCTimeByRtTime(RTTIME &rtTime, DWORD dwLen, CTime &tm)
{
	Ep_InitCTimeByRtTime(rtTime, tm);
	double dSeconds = dwLen;
	dSeconds = dSeconds / (2 * g_dwSampleRate);
	tm += (DWORD)dSeconds;
}


//计算数据是否添加入缓存
BOOL g_bAddDataToBuffer = TRUE;
WORD g_wBufferState     = 0;

//////////////////////////////////////////////////////////////////////////
//系统配置
//////////////////////////////////////////////////////////////////////////
//工频
DWORD g_nFrequencyNom = 50;


//示波窗口    //单位ms
UINT  g_nOscillographTimeID       = 3001; 
DWORD g_dwOscillographTimeWndLong = 3000;    //窗口长度
DWORD g_dwOscillographRefreshTime = 200;    //窗口刷新时间
DWORD g_dwOscillographMaxTime     = 30000;
DWORD g_dwOscillographMinTime     = 200;

//参数监视    //单位ms
UINT  g_nParaSpyTimeID       = 3002;    //参数监视时钟
DWORD g_dwParaSpyTimeWndLong = 600000;  //参数监视窗口长度
DWORD g_dwParaSpyRefreshTime = 2000;    //参数监视窗口刷新时间

//录波数据的起始终止位置
// DWORD g_dwRecordDataBeginPos = 0;
// DWORD g_dwRecordDataEndPos = 0;


//////////////////////////////////////////////////////////////////////////
//系统分析配置
void ClearStSysAnalyseMngr()
{
	g_oStSysAnalyseMngr.nDrawVarCount   = 0;
}

void InitStSysAnalyseMngr()
{
	DRAWVAR *pDrawVar = g_oStSysAnalyseMngr.oDrawVars;
	DRAWVAR *pEnd = pDrawVar + MAX_DRAW_VARIABLE;
	g_oStSysAnalyseMngr.dLastTimeLen = 0.5;

	while (pDrawVar < pEnd)
	{
		pDrawVar->dRange = 10;
		pDrawVar++;
	}
}

void ValidateStSysAnalyseMngrDrawVar(BOOL &bNeedInitPos)
{
	bNeedInitPos = FALSE;

	PDRAWVAR pDrawVars = g_oStSysAnalyseMngr.oDrawVars;
	long nUseCount = 0;
	long nShowCount = 0;

	PDRAWVAR p = pDrawVars;
	PDRAWVAR pEnd = pDrawVars + MAX_DRAW_VARIABLE;

	while (p < pEnd)
	{
		if (p->nShow > 0)
		{
			nShowCount++;
		}

		if (p->nUse > 0)
		{
			nUseCount++;
		}

		p++;
	}

	if (nUseCount == 0)
	{
		p = pDrawVars;

		while (p < pEnd)
		{
			p->nUse = 1;
			p++;
		}
	}

	if (nShowCount == 0)
	{
		bNeedInitPos = TRUE;
		p = pDrawVars;

		while (p < pEnd)
		{
			if (p->nUse == 1)
			{
				p->nShow = 1;
			}

			p++;
		}
	}
}

// long ChangeBinaryDataToAlgorism(CString strData)
// {
// 	long nData = 0;
// 	long nLen = strData.GetLength();
// 	
// 	for (long nIndex = 0; nIndex < nLen ; nIndex++)
// 	{
// 		CString str = strData.GetAt(nLen - 1 - nIndex);
// 		long nValue = atoi(str);
// 		nValue <<= nIndex;
// 		nData += nValue;
// 	}
// 	
// 	return nData;
// }

StSYSANALYSEMNGR g_oStSysAnalyseMngr;    
