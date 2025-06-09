//PMData.h

#if !defined PMDATA_H_
#define PMDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CHData.h"
#include "../TestControl.h"

#define PNUM_CH 16//11

struct stPMOutData
{
	double fFreq;	//频率
	double fAnlg[PNUM_CH];	//幅值
	double fPhase[PNUM_CH];//相位

	unsigned char nFD[PNUM_CH];	//档位：自动换档=0，1~n代表从最大开始的档位

	unsigned char nU4Mode;	//U4模式，变化后会影响到输出通道转换

	//调试时的附加输出量
	double fFPoint;	//频率修正
	double fALP[PNUM_CH];	//零漂修正
};

struct stPMAdjData
{
};

class CPMData
{
// Construction
public:
	CPMData();
	~CPMData();

public:

	static CTestControl* m_pTestControl;

	////////////////////////	输出	/////////////////////////
	CCHData	m_PMData[PNUM_CH];

	unsigned char nU4Mode;	//U4模式，变化后会影响到输出通道转换
	
	//调试时的附加输出量
	double fFPoint;	//频率修正
	
	
	//输出量
	stPMOutData	m_stPMOutData;
	stPMOutData	m_stPMOutDataOld;

	BOOL	m_bVarChanged;

	void InitOutData();
	BOOL IsOutDataChanged();
	void UpdateOutDataOld();
	
	//下传输出量的其他变量
	unsigned char m_nAutoSetFD[PNUM_CH];
	unsigned char m_nFDSet[PNUM_CH];
	double m_fFDMax[PNUM_CH];
	
	void CheckFDChg();

	////////////////////////	测量	/////////////////////////
	unsigned int m_iSampleMode;

	////////////////////////	修正	/////////////////////////
public:
	double m_fTmp[5];
	unsigned char m_nCurTmpZone[5];


	/////////////////////////////////////////////////////
public:
	//输出
//	CCHData	m_PMData[PNUM_CH];

	double m_fFreqMax;				//频率最大值
	double m_fFreqMin;				//频率最小值
	double m_fPhaseMax;				//相位最大值
	double m_fPhaseMin;				//相位最小值

	unsigned char m_nHarmMax;		//谐波次数最大值

	long  m_lCmpstF;  //频率修正参数 = 41841;
	
	//输出和输入控制
//	unsigned int m_iSampleMode;     //直流测量方式
	unsigned int m_iSampleMode2;     //直流测量分档
	unsigned int m_iU4Mode;    //换档控制量
	unsigned int m_iInputStatus;    //开入
	unsigned int m_iAlarmStatus;    //报警
	unsigned int m_iOutStatus;      //开出
	unsigned int m_iDSPState;
	
	//温度测量和修正有关
	unsigned char m_nRom[6][9];    //温度传感器ID，5组 
//	double	m_fTmp[5];    //5个温度传感器测量温度值
	
	//开出量试验
	unsigned char m_nState_S[4];   //开出量状态
	double m_ftime_S[5];  //开出量翻转时刻和输出时间

	/////////////////////////////////////////////////////
public:
	void InitData();
	unsigned char m_nVarChanged;

	//判断输出数据变化
	unsigned char IsOutDataChanged2();
	
	//参数备份
	void UpdateOutDataOld2();
	
	//以下是特殊的处理：
	//档位变化
	void UpdateFDChg();
};

#endif