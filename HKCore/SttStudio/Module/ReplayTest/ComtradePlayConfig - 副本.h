#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
// #include "SttComtradeGroup.h"  //2021-11-2  lijunqing
#include "SttModuleChComtradeBind.h"
#include "../../../Module/Record/Comtrade/ComtradeMngr.h"
#include "../../../Module/Record/Comtrade/ComtradeRateData.h"
#ifdef _PSX_IDE_QT_
#include "../SttTest/Common/tmt_replay_test.h"
#endif

#define COMTRADE_CONFIG_KEY_Module	_T("MODULE")
#define COMTRADE_CONFIG_KEY_U		_T("U")
#define COMTRADE_CONFIG_KEY_I		_T("I")
#define COMTRADE_CONFIG_KEY_A		_T("A")
#define COMTRADE_CONFIG_KEY_B		_T("B")
#define COMTRADE_CONFIG_KEY_K		_T("K")
#define COMTRADE_CONFIG_KEY_MomentaryVal	_T("MomentaryVal")

#define CMTRD_FLUSH_TYPE_NoFlush			0
#define CMTRD_FLUSH_TYPE_FlushOneCh			1
#define CMTRD_FLUSH_TYPE_FlushAll			2
#define CMTRD_FLUSH_TYPE_FlushUModule		3
#define CMTRD_FLUSH_TYPE_FlushIModule		4

#define BIG_COMTRADE_REPLAY_CH_MAX_NUM                                                64  //20220519 进行大数据回放同时最大勾选的硬件通道数量 暂定12

//数字量模块通道映射第几组
#define DIGITAL_CH_MAP_FRIST_GROUP		0		
#define DIGITAL_CH_MAP_SECOND_GROUP		1

class CComtradePlayConfig : public CDataGroup
{
public:
	CComtradePlayConfig(void);
	virtual ~CComtradePlayConfig(void);

	long m_nStartCycleNum;	//起始循环周波数，无触发才有效
	long m_nTrigAfterMode;	//条件触发后模式：1循环播放完后切换，0：立即切换

	double m_fSampleFreq;
	long m_nTriggerType;	//触发条件
#ifdef _PSX_IDE_QT_
	tmt_time	    m_tGps;
#endif
// 	long m_nTrigTimeS;		//触发时间
// 	long m_nTrigTimeNS;
	float m_fPTRatio[2];	//PT变比参数
	float m_fCTRatio[2];	//CT变比参数

#ifdef _PSX_IDE_QT_
	tmt_BinaryConfig m_oBinaryConfig;	//开关量配置
	tmt_replay_WaveEditPara m_oWaveEditParas;//2023-12-21 wuxinyi 波形编辑配置参数
#endif
	//CSttComtradeGroup *m_pChMapConfig;	//通道映射配置，包括回放数据缓存
	CSttModulesComtradeBind m_oSttModulesComtradeBind;	//通道映射配置，包括回放数据缓存
	long m_nReplayBufFlush;//回放缓存刷新标记,0:不刷新，1：单通道刷新，2：所有通道刷新

// 	BOOL m_bUseBinaryModule;//主板开出模块是否使用
	CSttModuleComtradeBind * GetBinaryModule();//获取主板开出量模块指针接口

public:
	long GetTotalChannelNum();
	long GetTotalUChannelNum();
	long GetTotalIChannelNum();
	//根据配置参数、缓存大小计算缓存中能存的最大点数,分配回放用数据缓存
	void InitReplayBuf(long nABBufLen);
	//清空回放缓存数据
	void ResetReplayBuf();

	//更新回放缓存数据后调用，用于界面显示
//	void GetWeekChMaxValue(double &fUMax,double &fIMax,int nRealModuleIndex);//弱信号中每个模块应分开显示最大值电压电流
	void GetDigitalChMaxValue(double &fUMax,double &fIMax);
#ifdef _PSX_IDE_QT_
	void GetReplayChMaxValue(double &fUMax,double &fIMax,int nModuleType = REPLAY_MODULE_TYPE_ANALOG);
#endif
	void CalcReplayChMaxValue();
	void CalcReplayChMaxValue(int nModuleIndex,int nChIndex);
	bool CalDigitalChMaxValue(CSttModuleChComtradeBind *pCh, int nChannelGroupIndex);//实际数字模块通道输出最大值
	bool VaildDigitalChMaxValue(CSttModuleComtradeBind *pModule);
	bool VaildDigitalChMaxValue();

	bool VaildWeekChMaxValue(); //弱信号输出值验证

	int GetFT3MaxCodeValue(int nChannelGroupIndex, CSttModuleChComtradeBind *pCh);//获取最大码值
	bool HasFT3ChMap();//输出报文类型为FT3（柔直/普通）,是否有映射到数字量前两组数据

	//变比变化后，更新最大值
	void CalcReplayChUMaxValue();
	void CalcReplayChIMaxValue();

	//获取当前回放缓存中点数
	long GetReplayBufPoints();

	//获取指定时间点各通道瞬时值
	void GetReplayBufFixedMomentaryVal(double fStartTime,double fFixTime,double fSampleFreq);

	//是否有循环数据
	BOOL HasLoopData();

#ifdef _PSX_IDE_QT_
	//由配置对象生成tmt结构体
	void GenerateReplayTestParas(tmt_ReplayParas &oReplayParas,long nSampleFreq);
	void GenerateReplayConfigFromTMT(tmt_ReplayParas *pReplayParas,BOOL bUpdateChMapConfig);
#endif

	long GetTotalChs_SelectedModule();
	void GetTotalChs_SelectedModule(float ***pppdChValue);//获取跟节点下，所有模块的所有通道 ，通道未选择时赋值为空
	//void GetTotalChs_SelectedModule(CExBaseList &oModuleChsRef);//2024-02-22 wuxinyi 由于新增开出量模块，该函数暂时注释

	//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTCMTRDPLAYCFG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmtrdCfgDefineXmlRWKeys::CSttCmtrdReplayCfgKey();     }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	BOOL Open(const CString &strFile, double &fSampleFreq);
	BOOL Save(const CString &strFile, double fSampleFreq);
	void InitDefault(BOOL bInitNotModuleParas = TRUE);//传参标识是否初始化非模块参数(开入、触发方式等)
};

