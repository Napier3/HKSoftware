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

//������
//ϵͳ�õ�������ϵ��
unsigned short g_pChannelFIFOIndex[MAX_MR1200_CHANNELS];
UINT g_nFIFOUnitSize = 0;

//���������Ƿ�����뻺�棬¼��ʵʱ����ʱ����Ҫ������Ҫ����������Ĳ�������
//���浽�������ݻ����У��ڷ���ʱ������Ҫ���������ݱ��浽������
BOOL g_bAddDataToBuffer = TRUE;

WORD g_wBufferState     = 0;

//////////////////////////////////////////////////////////////////////////
//ϵͳ����
//////////////////////////////////////////////////////////////////////////
//��Ƶ
DWORD g_nFrequencyNom = 50;

//ʾ������    //��λms
UINT  g_nOscillographTimeID       = 3001; 
DWORD g_dwOscillographTimeWndLong = 3000;    //���ڳ���
DWORD g_dwOscillographRefreshTime = 500;  //200;    //����ˢ��ʱ��
DWORD g_dwOscillographMaxTime     = 3000;
DWORD g_dwOscillographMinTime     = 7;



//////////////////////////////////////////////////////////////////////////
//ϵͳ��������
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


//��ʼ�����㷨�仯������ÿ��ģ������С��50��������ͨ����8������
//������ 1 / ( nAnalogs*6 + nBinarys)���������
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
