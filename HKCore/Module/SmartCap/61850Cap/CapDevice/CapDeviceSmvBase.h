//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvBase.h  CCapDeviceSmvBase

#pragma once

#include "CapDeviceBase.h"
#include "CapDeviceSmvCh.h"

//2020-07-25  lijunqing
#define STT_CAP_RCD_SMV_DATA_MAX_COUNT           400
#define STT_CAP_RCD_SMV_DISCRET_MAX_COUNT          7

#define FFT_STATE_CAL_DELAY_TIME_CYCLES            3

#define CAPDEV_SMV_FFTStatePhaseDelt_Init          0//初始状态 
#define CAPDEV_SMV_FFTStatePhaseDelt_Rcd           1//录波状态 
#define CAPDEV_SMV_FFTStatePhaseDelt_Finished      3//录波结束状态 


class CCapDeviceSmvBase : public CCapDeviceBase
{
public:
	CCapDeviceSmvBase();
	virtual ~CCapDeviceSmvBase();


	long  m_nSampleRate;
	long  m_nAsduNum;
	long m_nRefChIndex;//20221213 zhouhj 参考通道索引  
	long m_nDisCretNum[STT_CAP_RCD_SMV_DISCRET_MAX_COUNT];//20231019 dxy 用于统计离散度分布情况

	CString m_strDataSet;				//数据集定义

	//2020-07-25  lijunqing  用于记录和保存输出波形文件的临时数据
	double m_dSttCapRcdData[STT_CAP_RCD_SMV_DATA_MAX_COUNT];
//重载函数
public:
	BOOL PhaseDeltaCalFinish();
	virtual void Reset(); 
	long  m_nFFTStatePhaseDelt ;// 增加：State机变量：初始状态=0；记录波形数据状态=1；记录完毕=2；
	long m_nFFTIndexPhaseDelt ;//进行角差计算的当前赋值采样点Index,从报文整秒后第一个点开始计数,直到大于1200点开始进行FFT计算
	long  m_nFFTStatePhaseDeltCount;
	//第一维是通道号，第二维是采样点数；默认第一个通道为采样延时,存储第二个通道开始所有通道最大1200个采样点的数据值,浮点
	double m_dVariable_FftPhaseDeltPoint[256][CAP_FFT_CAL_POINTS    +  10];
	//第一维是通道号，第二维是采样点数；默认第一个通道为采样延时,存储第二个通道开始所有通道最大1200个采样点的数据值,整型
	//该成员变量在最新代码逻辑中实际未用到在ADMU处理时,不再为其赋值
	long m_nVariable_FftPhaseDeltPoint[256][CAP_FFT_CAL_POINTS    +  10];
	//对于9-2报文同步法时.标记为整秒时的相位值,可用于后续计算角差
	//对于ADMU接收模拟量过零点时间数据时,标记为当前第一个点的相位值
	double   m_fPhaseForPhaseDelta[256];
	double   m_fChs_Freq[256];//zhouhj 20220818 记录全部通道频率
	DWORD m_dwTimeDelayForRes;//延时通道；//默认第一个通道为延时通道,记录延时通道值
	__int64 m_nFirstRcdPointTime;  //记录第一个采样点的绝对时标
	DWORD m_dwTimeDelay ;

	long m_nChType[STCAPPARSE_DATA_MAX_COUNT];//2023.7.10zhouhj  增加冗余用于双AD不一致处理
	long m_nChAngType[STCAPPARSE_DATA_MAX_COUNT];//2023.7.10zhouhj 

	int m_nCurrTimeDataCh;//上送的模拟量通道对应的电压电流类别及软件资源Index
	__int64 m_nCurrAnalogZeroTime;  //记录第一个采样点时,最新的上送模拟量通道对应的绝对时间

protected:
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	virtual void UpdateErrorTypeNum();//更新异常类型数量

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceSmvCh();	}
	virtual void GetOriginalDatas(PEPCAPPARSEDATAS* pParseDatas){}
	virtual void SetDeviceChMaps();//20230710 zhouhj 设置通道映射 
	virtual void analysis92(PEPCAPPARSEDATAS pDatas);
	CCapDeviceSmvCh* GetRefCh();
	virtual void GetSttCapParas(CDataGroup *pSttParas);

	virtual void InitNameAndID(long nTypeCount);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);
};

