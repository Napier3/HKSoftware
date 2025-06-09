// RecordGlobalDefine.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RecordGlobalDefine.h"
#include "RtTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL g_bCarry_For_AttrCalUsePoints = TRUE;
double g_dFixFreqCalValue = 50.0f;

//采样率
//系统用到的修正系数
unsigned short g_pChannelFIFOIndex[MAX_MR1200_CHANNELS];
UINT g_nFIFOUnitSize = 0;

//计算数据是否添加入缓存，录波实时计算时，需要根据需要将计算出来的参数数据
//保存到参数数据缓存中，在分析时，不需要将参数数据保存到缓存中
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
DWORD g_dwOscillographRefreshTime = 500;  //200;    //窗口刷新时间
DWORD g_dwOscillographMaxTime     = 3000;
DWORD g_dwOscillographMinTime     = 7;



//////////////////////////////////////////////////////////////////////////
//系统分析配置
// void ClearMR1200SysAnalyseMngr(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
// {
// 	oMR1200SysAnalyseMngr.nDrawObjectCount   = 0;
// }



void InitMR1200SysAnalyseMngr(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr)
{
	memset(&oMR1200SysAnalyseMngr,0,sizeof(MR1200SYSANALYSEMNGR));
	oMR1200SysAnalyseMngr.dLastTimeLen = 3;
	oMR1200SysAnalyseMngr.ptTrigCursor = CPoint(100,100);
	oMR1200SysAnalyseMngr.bShowMidLine = TRUE;
	
	InitHarmHistogram(oMR1200SysAnalyseMngr.oHarmHistogram);
// 	InitSysAnalyseMngr_AttrSpy(&oMR1200SysAnalyseMngr.oAttrSpy);
// 	InitSysAnalyseMngr_AttrDefault(&oMR1200SysAnalyseMngr.oAttrDefault);
}


//初始化的算法变化，考虑每个模拟量最小高50，开关量通道高8，所以
//就是用 1 / ( nAnalogs*6 + nBinarys)来计算比例
void InitSysAnalyseMngrDrawControl(PRECORDDRAWOBJECTCONTROL pDrawControl, long nAnalogs, long nBinarys)
{
	//ASSERT (nAnalogs > 0);
	//ASSERT (nBinarys >= 0);

	if (nAnalogs < 0)
	{
		nAnalogs = 0;
	}

	if (nBinarys < 0)
	{
		nBinarys = 0;
	}

	long nChs = nAnalogs + nBinarys;
	//ASSERT (nChs > 0);

	if (nChs == 0)
	{
		return;
	}

	int iIndex = nBinarys + nAnalogs;
	PRECORDDRAWOBJECTCONTROL p = pDrawControl;
	long i = 0;

	double dRatio = 1;
	nChs = nAnalogs * ANALOG_BINARY_HEIGHT_RATE + nBinarys;
	dRatio /= nChs;
	double dAnalogRatio = dRatio * ANALOG_BINARY_HEIGHT_RATE;
	double dPos = dAnalogRatio/2;

	for(i = 0; i < nAnalogs; i++)
	{
		p->dCenter = dPos;
		dPos += dAnalogRatio;
		p++;
	}

	dPos -= dAnalogRatio/2;
	dPos += dRatio/2;

	for(i = 0; i < nBinarys; i++)
	{
		p->dCenter = dPos;
		dPos += dRatio;
		p++;
	}
}

void InitMR1200SysAnalyseMngrDrawControl(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr, long nAnalogs, long nBinarys)
{
	PRECORDDRAWOBJECTCONTROL p = oMR1200SysAnalyseMngr.oDrawControl;
	InitSysAnalyseMngrDrawControl(p, nAnalogs, nBinarys);
}


DWORD rcd_CalCyclePoints(DWORD dwSampRate, double dFreq)
{
	return rcd_CalCyclePoints(dwSampRate, dFreq, g_bCarry_For_AttrCalUsePoints);
}

DWORD rcd_CalCyclePoints(DWORD dwSampRate, double dFreq, bool bCarry)
{
	double dCyclePoints = dwSampRate / dFreq;
	return rcd_CalCyclePoints(dCyclePoints, bCarry);
}

DWORD rcd_CalCyclePoints(double dCyclePoints, bool bCarry)
{
	long nVal = (long)dCyclePoints;
	double dTemp = dCyclePoints - nVal;

	if (dTemp > 0.999)
	{
		nVal = nVal + 1;
	}
	else
	{
		if (bCarry)
		{
			if (dTemp > 0.5)
			{
				nVal = nVal + 1;
			}
		}
	}

	return nVal;
}
