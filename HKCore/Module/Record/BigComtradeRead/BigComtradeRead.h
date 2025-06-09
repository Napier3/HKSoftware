#pragma once

#include "../Comtrade/ComtradeMngr.h"

#define BIG_COMTRADE_BINARY_READ_LENGTH                                      20*1024*1024

class CBigComtradeRead
{
public:
	CBigComtradeRead(void);
	virtual ~CBigComtradeRead(void);

public:
	long CalMaxDataBufPointNum();
	BOOL OpenBigComtradeFile(const CString &strComtradeFile);
	BOOL GenerateComtradeChDataFromDataFile();

protected:
	long ReadBigDataFile(const CString& strComtradeFile);
	long ReadBigDataAsBINARYMode(const CString& strComtradeFile);
	long ReadBigDataAsASIIMode(const CString& strComtradeFile);
	void BufferClear();
	void SetTotalSmpRates();
	long GetCurReadPointsNum();


public:
	CRcdComtradeFile m_oBigComtradeFile;////解析到各个通道的原始数据
	double m_nInsertFreq;//插值后频率K3，实际播放采样率，如50K

private:
	CFile m_oFileRead;//ComtradeData文件
	BOOL m_bHasOpenDataFile;

	BYTE *m_pFileReadBuffer;  //从文件读取的缓冲区 20M
	long m_nCurTotalByteLength;

	long m_nFileReadLength;//每次从文件读取的大小

	//原始通道数据中，电压电流最大值
	float m_fUMax;  
	float m_fUMin;
	float m_fIMax;  
	float m_fIMin;

	BOOL m_bReadFileFinish;	//读文件结束
	BOOL m_bAnalysisFinish;	//解析文件数据结束
	long m_nCurBeginPointIndex;//回放用通道数据缓存1中起始索引，用于计算时间，当前m_oBigComtradeFile中起始点相对于实际Comtrade文件起始点的Index索引
	long m_nCurPointNum;//当前解析的所有点数

	float* m_pdSamRate; //不同的采样率
	long* m_pnDataPoints;//不同采样率下的采样点数
	long m_nSamAmount;//采样率的数量
	long m_nTotalPointsNum;//data文件中的总的采样点数量
};
