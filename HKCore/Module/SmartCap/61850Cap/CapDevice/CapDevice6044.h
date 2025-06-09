#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

#define  CAP_COMP_CNT        80
#define  TEST_CNT_NO_PPS  4000
#define STT_60044_PKG_MAX_LENGTH           1000

class CCapDevice6044 : public CCapDeviceSmvBase
{
public:
	CCapDevice6044();
	virtual ~CCapDevice6044();

	long m_nSmpRate;//采样率
	long m_nPkgLenth;//单帧报文总长度
	double m_dBaudRate;//波特率
	BOOL m_bDC_FT3;//标记为是否柔直FT3
	long m_nDelayTimeChIndex;//延时通道Index用于快速获取延时通道数据值
	BOOL m_bHasDelayTimeCh;//标记是否包含延时通道
	CString m_strSTMode;//ST口模式   0-None 1-FT3  2-PPS      3-BCode
	long m_nFt3_CrcType;// 20240811 suyang 新增FT3 CRC类型 0-标准16字节校验，1-报文末尾校验，2-第一个数据块14字节校验

	long m_nChByteLenth[STCAPPARSE_DATA_MAX_COUNT];//通道字节长度,用于报文解析使用
//	long m_nDebugIntervalTime;//间隔时间
	long m_nStateValueChangedCount; //变位次数


//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE6044;};

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas);
	virtual void ClearAnalysisResultErrors();
	virtual void analysis6044(PEPCAPPARSEDATAS pDatas);
//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual void Reset(); //开始抓包，复位之前的状态
	//2020-6-25  mym  提取smptCnt==0的值；
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);
	virtual BOOL IsDataRcvOverTime();
	virtual void GetSttCapParas(CDataGroup *pSttParas);
	virtual void InitNameAndID(long nTypeCount);
	virtual BOOL Compare(PEPCAPBUFFERITEM pItemData);

	long GetByteChValue(BYTE* pBuferHead,long &nCurrPos,long &nHasCrcLenth,long nChLenth,long nFT3CrcType);
	BOOL TimeDelayCalFinish();
	void UseFirstCircleDataRepeat_Debug(long nChs);
	long GetPkgHeadTimeNs();//获取报文头ns时间

	//2023/12/11 wangjunsheng 用于解析FT3原始报文数据
	char m_szPkgDatas[STT_60044_PKG_MAX_LENGTH];
	long m_nPkgDatasLenth;
protected:
	void FindMax_Value(double * pValue,  int nValueCnt, int &nMaxNo);
	//zhouhj 2024.3.11 计算角差比差
	virtual void AnalysisData_PhaseDelt(PEPCAPPARSEDATAS pDatas);
	virtual void AnalysisStateValueChangedCount(PEPCAPPARSEDATAS pDatas);//chenling 2024.5.30计算开出变位次数
};


