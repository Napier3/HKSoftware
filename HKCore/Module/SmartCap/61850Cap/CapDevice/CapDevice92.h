//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDevice92.h  CCapDevice92

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

#define  CAP_COMP_CNT        80
#define  TEST_CNT_NO_PPS  4000

class CCapDevice92 : public CCapDeviceSmvBase
{
public:
	CCapDevice92();
	virtual ~CCapDevice92();

	CString m_strSVID;
	long m_nConfRev;
	long m_nSmpSynch;

	//同步计算
	double m_oFirstCW_RcdDatas[255][800];//第一维是通道号，第二维是点数,首周波测试的录波数据
	long m_nFirstCW_Index;//首周波测试Index标记
	double m_dVariable_Fft[CAP_FFT_CAL_POINTS    +   10];
	double m_dVariable_FftPoint[256][CAP_COMP_CNT    +  10];//第一维是通道号，第二维是采样点数；

    int         m_nChnelCnt;
	long m_nFFTIndex ;
	long  m_nFFTState ;// 增加：State机变量：初始状态=0；记录波形数据状态=1；记录完毕=2；

	//zhouhj 2024.3.8 移入基类
//	long  m_nFFTStatePhaseDelt ;// 增加：State机变量：初始状态=0；记录波形数据状态=1；记录完毕=2；
//	long m_nFFTIndexPhaseDelt ;//进行角差计算的当前赋值采样点Index,从报文整秒后第一个点开始计数,直到大于1200点开始进行FFT计算
//	long			m_nFFTStatePhaseDeltCount;


	long m_nFFTIndexComp ;
	long  m_nFFTStateComp ;// 增加：State机变量：初始状态=0；记录波形数据状态=1；记录完毕=2；

	//整秒时的相位值
	double   m_fPhaseForPhase[256];//zhouhj 2024.3.29 该成员变量与m_fPhaseForPhaseDelta重复,后续建议删除
	double   m_fResponseTime;
	double   m_fResponseError;
	double   m_fZeroDelta;//获取采样计数器归0点,接收报文多余的时间差,即从装置发出报文到接收方收到报文之间的时间差(单位:微妙)
//	double   m_fDCValue[256];//在常规计算时,已计算直流分量此处无需重复计算  20220817 zhouhj



	long  m_nFFTStateCount;
	long  m_nFFTStateCountComp;

	double m_fPhase;
	double m_fMag;
	double m_fFreq;
	double m_dTimeDelay;
	CString m_strTimeDelay;

	long m_nTimeOffset;
//	__int64 m_n64Time;  移入基类,名称改为m_nFirstRcdPointTime记录第一个采样点的绝对时标
	long m_nSmpleCount;
	CString m_strComtradeFile;
	CString m_strSvSynChID;
	double m_dSvSynChCoef;


//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE92;};

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);
	virtual void ClearAnalysisResultErrors();
	virtual void SetDeviceChMaps();//20230710 zhouhj 设置通道映射 
	virtual void analysis92(PEPCAPPARSEDATAS pDatas);

	void GetFirstCWDatas(EPCAPPARSEDATAS* pParseDatas);
	BOOL IsFirstCW_FirstData(EPCAPPARSEDATAS* pParseDatas);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void Reset(); //开始抓包，复位之前的状态
	//2020-6-25  mym  提取smptCnt==0的值；
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();
	//自动计算离散度区间值
	void CalDiscretInterval();

	BOOL TimeDelayCalFinish();
	BOOL ComplexCalFinish();
	long GetFirstCW_ChDatasIndex(long nChIndex);

	virtual void UpdateErrorTypeNum();//更新异常类型数量

protected:
	void AnalysisData_DelayTime(PEPCAPPARSEDATAS pDatas);
	void AnalysisData_Complex(PEPCAPPARSEDATAS pDatas);
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	void FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo);

	void WriteRcdFile(double *pdLong, long nWriteCount);
	void WriteRcdFile_Comtrade(double *pdLong, long nWriteCount);
};

void cap_WriteRcdFile_Txt(double *pdLong, long nWriteCount, const CString &strName=_T(""));

