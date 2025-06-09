#include "stdafx.h"
#include "CapMath.h"

#include <COMPLEX>
using namespace std;

#define FFT_PTCOUNT 4096
#define FFT_PI 3.1415926535897932384626433832795


// ��ʮ��������ֵת��Ϊʮ������ֵ
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

		// ���ɴ�������Hanning��
		for(i = 0; i < nPoints; ++i)
		{
			m_win[i] = 0.5 - 0.5 * cos(2 * FFT_PI * i / nPoints);
		}

		// ���ɵ����
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
//*	������:	FFT
//*	����:	�ú�������ʵ�ֻ�2 ���ٸ���Ҷ�任
//*	����ֵ:	��
//*	����:	pre:	����Ϊָ��ʱ��ʵ�������ָ��, ���Ϊָ��Ƶ��ʵ���������ָ��
//*			pim:	����Ϊָ��ʱ���鲿�����ָ��, ���Ϊָ��Ƶ���鲿�������ָ��
//*			pwin:	ָ�򴰺��������ָ��
//*			prev:	ָ����������ָ��
//*			n:	�任����, ��n��Ϊ2����������, �Զ�ȡ��ǰ��2���������ݵ�����
//*	��ע:	�����������ⲿȡ��
//***************************************************************************
	void FFT(double *pre, double *pim, double *pwin, int *prev, int n)
	{
		int i, j, k;										//ѭ������
		double a;											//�м����
		int n2;												//Ⱥ��
		double tha;											//��λ��

		int w;
		int i2, j2, k2, k0, kj, kd, wd;
		double wr, wi, yr, yi;

		//����nΪ2����������
		for(i = 0; (1 << i) <= n; ++i);
		n = 1 << (i - 1);
		n2 = n >> 1;
		tha = -2 * FFT_PI / n;
		//�Ӵ�, ��������pwin����
		for(i = 0; i < n; ++i)
		{
			pre[i] *= pwin[i];
		}
		//����
		for(i = 0; i < n; ++i)
		{
			if((j = prev[i]) > i)
			{
				a = pre[i];
				pre[i] = pre[j];
				pre[j] = a;
			}
		}
		//�����㷨
		for(j2 = n2; j2 >= 1; j2 >>= 1)
		{
			i2 = kd = n2 / j2;								//Ⱥ�ڵ��θ���, �����ھ�
			kj = i2 << 1;									//Ⱥ���
			wd = j2;										//W ����
			w = k0 = 0;										//W ���, Ⱥ���
			for(i = 0; i < i2; ++i, ++k0, w += wd)
			{
				k = k0;
				wr = cos(tha *w);							//Wi
				wi = sin(tha *w);
				for(j = 0; j < j2; ++j, k += kj)			//Ⱥѭ��j---
				{
					k2 = k + kd;							//����ͬ��Wi
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
	//*	������:	SpectrumAnalyze
	//*	����:	�Ը���Ҷ�任��Ƶ���������Ƶ������������
	//*	����ֵ:	��
	//*	����:	pre:	�������, ����Ҷ�任Ƶ��ʵ������
	//*			pim:	�������, ����Ҷ�任Ƶ���鲿����
	//*			WP:	�������, �������
	//*			Fs:	����Ƶ��
	//*			N:	��������, ��FDԪ�ظ���ƥ��
	//*	��ע:	WaveParaΪ���β����ṹ��, ������F, A, P.
	//***************************************************************************
	void SpectrumAnalyze(double *pre, double *pim, double Fs, int N,
		double& _Mag, double& _Ang, double& _Fre)
	{
		double maxModu = 0.0;
		int maxN = 0;
		int k = 0;
		double delta;										//maxN+delta��Ӧ����
		double modulo;										//Ƶ��ģ
		//�����ҵ�Ƶ������ģ�����(ע��: ǰN/2��Ч), ����ض���ģ������������
		for(int i = 0; i < N / 2; ++i)
		{
			modulo = sqrt(pre[i]*pre[i] + pim[i]*pim[i]);
			if(maxModu < modulo)
			{
				maxModu = modulo;
				maxN = i;
			}
		}
		if(0 == maxN)										//ֱ��
		{
			_Fre = 0.0;
			_Mag = 2 * maxModu / N;
			_Ang = 0.0;

			return;
		}
		//����������K��ƫ����
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


		//Ƶ��
		_Fre = (maxN + delta) * Fs / N;

		//��ֵ
		_Mag = 4 * FFT_PI * delta * (1 - delta * delta)
			* abs(complex<double>(pre[maxN], pim[maxN])) / sin(FFT_PI * delta) / N;

		//��λ
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
	double m_win[FFT_PTCOUNT];   //��������
	int m_rev[FFT_PTCOUNT];     //�����
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

