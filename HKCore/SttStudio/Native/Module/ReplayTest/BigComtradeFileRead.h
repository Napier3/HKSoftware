#ifndef _CBigComtradeFileRead_H_
#define _CBigComtradeFileRead_H_

#include "../../../Module/Record/Comtrade/ComtradeMngr.h"

#ifndef USE_Debug_BIG_ComtradeRead_Mode
#include "ComtradePlayConfig.h"
#endif

#include "ComtradeBufMngr.h"
#include "../../../Module/MemBuffer/BufferBase.h"

#define CMTRD_UPDATE_RAWTOREPLAY_ALL    0X000000F
#define CMTRD_UPDATE_RAWTOREPLAY_U		0X0000001
#define CMTRD_UPDATE_RAWTOREPLAY_I		0X0000002

#ifndef _Stt_Cmtrd_Save_File_
#define FILE_READBUF_SIZE	20*1024*1024		//读文件缓存大小20M
#else
#define FILE_READBUF_SIZE	20*1024*1024
#endif

#define USE_InsertComtradeFile_Mode   //插值后数据使用文件方式；不定义此时，数据转换时，实时插值

class CBigComtradeFileRead
{
public:
	CBigComtradeFileRead();
	virtual ~CBigComtradeFileRead();

#ifdef USE_InsertComtradeFile_Mode
	CRcdComtradeFile* GetInsertComtradeFile(){return m_pInsertComtradeFile;}
#endif

	CRcdComtradeFile m_oSrcComtradeFile;	//解析到各个通道的原始数据
	double m_dInsertFreq;					//插值后频率K3，实际播放频率，如50KHz
	double m_fReplayStartTime;				//回放用通道数据缓存中起始时间，用于回放波形绘图
	double m_fRawStartTime;					//m_pFileReadBuffer起始时间，用于原始波形绘图

	//cfg文件中采样点信息
	float* m_pdSamRate; //不同的采样率
	long* m_pnDataPoints;//不同采样率下的采样点数
	long m_nSamAmount;//采样率的数量
	BOOL m_bAnalysisFinish;					//解析文件数据结束, zhouhj 2023.8.17 便于与CComtradeSendSocket关联
private:

#ifdef USE_InsertComtradeFile_Mode
	CRcdComtradeFile *m_pInsertComtradeFile;//按标准采样率 ,插值之后的ComtradeFile
#else
	long m_nInsertTotalPoints;//当前读取段的，经过插值计算后的总采样点数
	double m_dInsertOffsetTime;//分成多段后，插值前后的offset时间
#endif

#ifndef USE_Debug_BIG_ComtradeRead_Mode
	CComtradePlayConfig *m_pComtradePlayConfigRef;//界面配置对象,包含回放用通道数据缓存m_pReplayBuf
#endif

	CFile m_oFileRead;
	BOOL m_bIsBinaryMode;//true文件为binary模式，false为ascii模式
	CBufferBase m_oASII_ModeBuffer;
//	BOOL m_bHasOpenDataFile;//文件是否已经被打开的标识

	BYTE *m_pFileReadBuffer;				//从文件读取的缓冲区 20M
	long m_nReplayBuffMaxLenth; //ReplayBuffMax中每次最大的缓存大小 如20M  用于据此 结合当前测试仪实际通道数 计算实际需要读取data文件的大小
	long m_nFileReadBufLen;					//读缓存大小  单次读取最大缓存大小
//	double m_dInsertOffsetTime;//为Src数据第一个点到插值后数据第一个点的时间差
	long m_nReadBufDataLen;					//m_pFileReadBuffer数据长度
//	long m_nReadBufReadPos;

	BOOL m_bReadFileFinish;					//读文件结束

	long m_nCurSrcBeginPointIndex;//回放用通道数据缓存1中起始索引，用于计算时间，当前m_oBigComtradeFile中起始点相对于实际Comtrade文件起始点的Index索引
	long m_nCurInsertBeginPointIndex;//当前插值段开始点在总的波形里的点号索引
	long m_nCurSrcIntervalPoints;//当前解析的所有点数
	long m_nCurIntervalDeliverPos;//开始测试后，当前段传递的位置

	long m_nTotalPointsNum;//data文件中的总的采样点数量
	BOOL m_bAutoGenChABMap;//是否自动生成A\B通道映射(单机软件采用自动生成,自动测试通过界面参数配置生成)

public:
	void SetAutoGenChABMap(BOOL bAutoGenChABMap){m_bAutoGenChABMap = bAutoGenChABMap;}
	BOOL GetAutoGenChABMap(){return m_bAutoGenChABMap;}
	BOOL GenerateComtradeChDataFromDataFile(BOOL bSeekToBegin,BOOL bResetCoef = TRUE);//循环读取BigComtrade文件
	//读完cfg文件后，初始化A\B\K映射关系
	void InitChMapConfig();
	void RefreshChMapConfig();//无需初始化A\B\K映射关系
	void UpdateChMapConfig();//用于更新CSttModuleChComtradeBind对象内使用的通道映射配置
//	BOOL IsAnalogFinished(){return m_bAnalysisFinish;}
	void GenerateComtradeChDatas(BOOL bSeekToBegin);
	void ClearComtradeCfgFile();//20230815-wxy-清空
	long GetTotalPointsNum();

protected:
	//初始化读文件缓存
	void InitFileReadBuf(long nOnceReadFileLen);



	void InitSrcAnalogsBeginAng_SpecialSmpRate();//初始化特殊采样频率的初始相位 主要包含每个周波1个或两个采样点的情况

	BOOL GenerateComtradeChDataFromDataFile_BinaryMode(BOOL bSeekToBegin);//循环读取BigComtrade文件
	BOOL GenerateComtradeChDataFromDataFile_ASIIMode(BOOL bSeekToBegin);//循环读取BigComtrade文件

	//根据m_pFileReadBuffer缓存剩余数据，读文件填充满,并解析到AnalogData中，更新m_fRawStartTime,m_bReadFileFinish
	BOOL ReadBigComtradeDataFile(const CString &strComtradeFile);

	BOOL ReadBigDataAsBINARYMode(const CString& strComtradeFile);
	BOOL ReadBigDataAsASIIMode(const CString& strComtradeFile);

	long GetCurReadComtradePointsNum(double dInsertOffsetTime);//本次读取Comtrde文件的点数

	//由AnalogData原始数据填充满ReplayBuf
	BOOL GenerateReplayBufFromRawData(UINT nUpdateMask = CMTRD_UPDATE_RAWTOREPLAY_ALL);

	//由回放缓存ReplayBuf填充AB缓存
	BOOL GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf);

	//根据配置参数，定位文件读数据，并解析到AnalogData中
	BOOL ReadLoopRawDataFile();

	void CloseReadFile();
	//原始数据、回放数据清空
	void ResetDataBuf();

	void ClearTotalBuff();//清除所有缓存，包括读取的m_pFileReadBuffer，以及采样率 不同采样率下的总点数
	void SetBigFileTotalSmpRates();//设置整个文件的采样率到成员变量中
	void SetCurIntervalSmpRates();

	double CalCurRawStartTime();
	long CalSrcMaxSmpRateIntervalPoints();//计算源文件中，在最大采样率下，需要读取的总采样点数，保证ReplayBuff填满的情况下
	double CalInsertOffsetTime();

public:
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	void AttachComtradePlayConfig(CComtradePlayConfig *pConfig){	m_pComtradePlayConfigRef = pConfig;	}
#endif
	
	BOOL IsAnalysisFinish()	{	return m_bAnalysisFinish;	}
	BOOL OpenComtradeFile(const CString &strComtradeFile,long nOnceReadFileLen,BOOL bInitDefault=TRUE);
	BOOL CheckComtradeFile(const CString &strComtradeFile);

	//读Comtrade文件，计算并初始化缓存
	BOOL OpenBigComtradeCfgFile(const CString &strComtradeFile,long nOnceReadFileLen);

	//定位文件，一次性填充LoopBuf数据
	BOOL GenerateLoopBuf();

	//填充ABBuf数据
	BOOL GenerateABBuf(int nIndex);	

	//开始测试之前，初始化Loop\A\B缓存
	void BeginGenerateComtradeBuf(BOOL bResetCoef = TRUE);//2024-2-2 wuxinyi 修改由于在刷新硬件配置时会重置m_dCoefValue 导致连接测试仪时波形编辑之后波形图出错。

	//变比变化后，更新ReplayBuf和最大值
	void OnPTChanged();
	void OnCTChanged();

	//界面(A-B)/K和是否勾选改变，对应ReplayBuf也要更新，更新完再重新计算最大值，更新最大值
#ifndef USE_Debug_BIG_ComtradeRead_Mode
	BOOL UpdateChReplayBuf(CSttModuleChComtradeBind *pCh,CSttModuleComtradeBind *pModule,BOOL bSave=FALSE);
	BOOL UpdateChReplayBuf(int nModuleIndex,int nChIndex/*,BOOL bFromStart=FALSE*/);
#endif

	//2024-02-27 wuxinyi 更新开出量通道
	BOOL UpdateBinaryChReplayBuf(CSttModuleComtradeBind *pModule);

//2024-01-08 wuxinyi 波形编辑相关接口
public:
	BOOL InsertCyclePointsByRelTime(double dBeginTime, double dEndTime, double dInsertTime, int nCycleIndex);//插入
	BOOL DeletePointsByRelTime(double dBeginTime, double dEndTime);//删除
	BOOL InsertCyclePointsByPoint(long nBeginPoint, long nEndPoint, long nInserPoint, int nCycleIndex);//插入	
	BOOL InsertNormalCyclePoints(double dVolValue,double dCurrentValue,double dTime_Second);
	

};


#endif