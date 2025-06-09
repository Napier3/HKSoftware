//CHData.h
#if !defined CHDATA_H_
#define CHDATA_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct stCHData
{
	//基本参数
	double m_fAnlg;					//幅值
	double m_fFreq;					//频率
	double m_fPhase;				//相位
	
	unsigned char m_nDC;			//直流（1）或交流（0）
	
	//幅值分档
	unsigned char m_nAutoSetFD;		//自动换档（1）或固定档位（0）
	unsigned char m_nFD;			//档位
	unsigned char m_nFDNum;			//档位总数
	double m_fFDMax[8];				//档位幅值最大值，从最大档开始，最后一位为零
	
	//修正参数
	double m_fCmpstLP;				//输出零漂，用于调试软件......
	double m_fCmpst[8][3];			//基本零漂、幅值、相位修正参数	//v1.03-070313
	double m_fCmpstT[15][8][3];     //不同温度下的零漂、幅值、相位修正参数	//v1.03-070313
	//（只适用于交流输出通道）
	double m_fCmpstH[50][8][2];		//不同谐波下的幅值、相位修正参数	//v1.03-070313

	//谐波参数
	double m_fAnlgH[50];			//谐波幅值
	double m_fPhaseH[50];			//谐波相位
};

class CCHData	//单通道输出参数
{
// Construction
public:
	CCHData();
	~CCHData();

	/////////////////////////////////////////////////////
public:
	stCHData m_stCHData;
	stCHData m_stCHDataOld;

	/////////////////////////////////////////////////////
public:
	//参数初始化
	void InitOutData();

	//判断输出数据变化
	unsigned char IsOutDataChanged();

	//参数备份
	void UpdateOutDataOld();

	//以下是特殊的处理：
	//档位变化
	void UpdateFDChg();
};

#endif

