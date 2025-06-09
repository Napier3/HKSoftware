#include "stdafx.h"
#include "CapMath.h"

#include <COMPLEX>
using namespace std;

#define FFT_PTCOUNT 4096
#define FFT_PI 3.1415926535897932384626433832795


// 将十六进制数值转化为十进制数值
// INT32 Hex2Dec(const BYTE* start, INT32 len)
// {
// 	INT32 result=0;
// 	for (INT32 i=0;i<len;++i)
// 	{
// 		result+=start[i]<<(8*(len-1-i));
// 	}
// 	return result;
// }

class CStaticFFTData
{
public:
	CStaticFFTData()
	{
		m_nOldFFTPTCount = 0;
		ZeroMemory(m_win,sizeof(m_win));
		ZeroMemory(m_rev,sizeof(m_rev));
	}

	void InitFFTData(int nPoints)
	{
		if(nPoints == m_nOldFFTPTCount)
			return;

		ASSERT(nPoints <= FFT_PTCOUNT);

		int i, j, k;

		// 生成窗函数表Hanning窗
		for(i = 0; i < nPoints; ++i)
		{
			m_win[i] = 0.5 - 0.5 * cos(2 * FFT_PI * i / nPoints);
		}

		// 生成倒序表
		k = nPoints >> 1;
		m_rev[0] = 0;
		for(j = 1; k > 0; j <<= 1, k >>= 1)
		{
			for(i = 0; i < j; ++i)
			{
				m_rev[i + j] = m_rev[i] + k;
			}
		}

		m_nOldFFTPTCount = nPoints;
	}

//***************************************************************************
//*	函数名:	FFT
//*	功能:	该函数用来实现基2 快速傅里叶变换
//*	返回值:	无
//*	参数:	pre:	输入为指向时域实部数组的指针, 输出为指向频域实部的数组的指针
//*			pim:	输入为指向时域虚部数组的指针, 输出为指向频域虚部的数组的指针
//*			pwin:	指向窗函数数组的指针
//*			prev:	指向倒序表数组的指针
//*			n:	变换点数, 若n不为2的整数次幂, 自动取靠前的2的整数次幂的数据
//*	备注:	窗函数表由外部取得
//***************************************************************************
	void FFT(double *pre, double *pim, double *pwin, int *prev, int n)
	{
		int i, j, k;										//循环变量
		double a;											//中间变量
		int n2;												//群数
		double tha;											//单位角

		int w;
		int i2, j2, k2, k0, kj, kd, wd;
		double wr, wi, yr, yi;

		//调整n为2的整数次幂
		for(i = 0; (1 << i) <= n; ++i);
		n = 1 << (i - 1);
		n2 = n >> 1;
		tha = -2 * FFT_PI / n;
		//加窗, 窗类型由pwin决定
		for(i = 0; i < n; ++i)
		{
			pre[i] *= pwin[i];
		}
		//倒序
		for(i = 0; i < n; ++i)
		{
			if((j = prev[i]) > i)
			{
				a = pre[i];
				pre[i] = pre[j];
				pre[j] = a;
			}
		}
		//蝶形算法
		for(j2 = n2; j2 >= 1; j2 >>= 1)
		{
			i2 = kd = n2 / j2;								//群内蝶形个数, 蝶形内距
			kj = i2 << 1;									//群间距
			wd = j2;										//W 增量
			w = k0 = 0;										//W 起点, 群起点
			for(i = 0; i < i2; ++i, ++k0, w += wd)
			{
				k = k0;
				wr = cos(tha *w);							//Wi
				wi = sin(tha *w);
				for(j = 0; j < j2; ++j, k += kj)			//群循环j---
				{
					k2 = k + kd;							//有相同的Wi
					yr = pre[k2] * wr - pim[k2] * wi;		//y = x[k2] * Wi
					yi = pre[k2] * wi + pim[k2] * wr;
					pre[k2] = pre[k] - yr;					//x[k2] = x[k] - y
					pim[k2] = pim[k] - yi;
					pre[k] = pre[k] + yr;					//x[k] = x[k] - y
					pim[k] = pim[k] + yi;	
				}
			}
		}
	}

	//***************************************************************************
	//*	函数名:	SpectrumAnalyze
	//*	功能:	对傅里叶变换后频域数组进行频谱修正及分析
	//*	返回值:	无
	//*	参数:	pre:	输入参数, 傅里叶变换频域实部数组
	//*			pim:	输入参数, 傅里叶变换频域虚部数组
	//*			WP:	输出参数, 分析结果
	//*			Fs:	采样频率
	//*			N:	采样点数, 与FD元素个数匹配
	//*	备注:	WavePara为波形参数结构体, 定义了F, A, P.
	//***************************************************************************
	void SpectrumAnalyze(double *pre, double *pim, double Fs, int N,
		double& _Mag, double& _Ang, double& _Fre)
	{
		double maxModu = 0.0;
		int maxN = 0;
		int k = 0;
		double delta;										//maxN+delta对应主瓣
		double modulo;										//频域模
		//首先找到频域数组模最大者(注意: 前N/2有效), 主瓣必定与模最大的谱线相邻
		for(int i = 0; i < N / 2; ++i)
		{
			modulo = sqrt(pre[i]*pre[i] + pim[i]*pim[i]);
			if(maxModu < modulo)
			{
				maxModu = modulo;
				maxN = i;
			}
		}
		if(0 == maxN)										//直流
		{
			_Fre = 0.0;
			_Mag = 2 * maxModu / N;
			_Ang = 0.0;

			return;
		}
		//计算主瓣与K的偏移量
		double y1 = sqrt(pre[maxN-1] * pre[maxN-1] + pim[maxN-1] * pim[maxN-1]);
		double y2 = sqrt(pre[maxN+1] * pre[maxN+1] + pim[maxN+1] * pim[maxN+1]);
		double v;
		if(y1 > y2)
		{
			v = y1 / maxModu;
			delta = (2 - v) / (1 + v);
			delta -= 1;
		}
		else
		{
			v = maxModu / y2;
			delta = (2 - v) / (1 + v);
		}


		//频率
		_Fre = (maxN + delta) * Fs / N;

		//幅值
		_Mag = 4 * FFT_PI * delta * (1 - delta * delta)
			* abs(complex<double>(pre[maxN], pim[maxN])) / sin(FFT_PI * delta) / N;

		//相位
		_Ang = arg(complex<double>(pre[maxN], pim[maxN])) - delta * FFT_PI;
	}

	void CalcFFT(double *pPoints, int nCount, double Fs, 
		double& Mag, double& Ang, double& Fre)
	{
		nCount = min(nCount,FFT_PTCOUNT);
		InitFFTData(nCount);
		double temp[FFT_PTCOUNT];
		ZeroMemory(temp,sizeof(temp));
		FFT(pPoints, temp, m_win, m_rev, nCount);
		SpectrumAnalyze(pPoints, temp, Fs, nCount, Mag, Ang, Fre);
		Ang *= 180.0 / FFT_PI;
	}
public:
	double m_win[FFT_PTCOUNT];   //窗函数表
	int m_rev[FFT_PTCOUNT];     //倒序表
	int m_nOldFFTPTCount;
};

CStaticFFTData theStaticFFTData;

void AfxCalcFFT(double* pSrcPoints, int nPoints, double SampleRate,
	double& Mag, double& Ang, double& Fre)
{
	theStaticFFTData.CalcFFT(pSrcPoints, nPoints, SampleRate, Mag, Ang, Fre);
	Mag /= 1.414159265;
}

double AfxFormatAngle(double prvAng)
{
	if(fabs(prvAng)<=180)return prvAng;
	int iph = (int)prvAng;
	double tail = prvAng - iph;
	prvAng = iph%180 + tail;
	if((iph/180)%2!=0)prvAng +=(prvAng>0)?(-180):180;	
	return prvAng;	
}

void AfxFormatAngle(double *dAng)
{
	while (*dAng < 0)
	{
		*dAng += 360;
	}

	while (*dAng > 360)
	{
		*dAng -= 360;
	}

	if (*dAng > 180)
	{
		*dAng -= 360;
	}
}

