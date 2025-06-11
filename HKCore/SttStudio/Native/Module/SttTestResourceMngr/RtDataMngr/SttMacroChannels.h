#pragma once
#include "../../SttTest/Common/tmt_rtdata_def.h"
#include "../../SttCmd/SttParas.h"
#include "../../SttCmd/SttChMap.h"
#include "../../../../Module/MemBuffer/TCycleMemBuffer.h"

#define STT_RT_DATA_MODE_NONE                                             0
#define STT_RT_DATA_MODE_ASYN                                             1
#define STT_RT_DATA_MODE_SYN                                              2

#define STT_MACRO_CH_TYPE_VOL                                             0
#define STT_MACRO_CH_TYPE_CUR                                             1

#define STT_HISDATA_MEMBUFFER_MAX_NUM	                             	8000   //历史数据循环缓存最大长度

#define STT_MACRO_ID_FAULT_CH_VOL											"Uf"
#define STT_MACRO_ID_FAULT_CH_CUR											"If"//新增故障通道



typedef CTCycleMemBuffer<tmt_RtDataCh> CCycleMemBuffer_rtdata;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSttMacroChannel :public CExBaseObject
{
public:
	CSttMacroChannel(void);
	virtual ~CSttMacroChannel(void);

public:
	long m_nChannelType;  //表示通道类型，比如电压、电流等，这个统一考虑
	CSttChMap *m_pHdMaps;//该软件资源关联的全部硬件资源通道
	tmt_rtdata_ch m_oRtDataCh;  //这里头暂时定结构体，实时数据

	CCycleMemBuffer_float m_oHisMagBuf;		//历史数据幅值
	CCycleMemBuffer_rtdata m_oHisDataBuf;	//历史数据		//yyj add 2021-08-25

	CString m_strHisTitle;
	float *m_pfHisMagMax;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CMacroChGroup :public CExBaseList
{
public:
	CMacroChGroup(void);
	virtual ~CMacroChGroup(void);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttMacroChannels :public CExBaseList
{
public:
	CSttMacroChannels(void);
	virtual ~CSttMacroChannels(void);

public:
	CCycleMemBuffer_double m_oHisTimesBuf;  ////历史数据的绝对时间
	CCycleMemBuffer_double m_oHisRealTimesBuf;//历史数据的相对时间
	//这里头的数组为历史数据绝对时刻；
	CExBaseList m_oListGroups;//该链表中为全部分组,此处为索引方式，实际通道不在CMacroChGroup中删除

	void InitGroup();//初始化所有通道分组
	void ClearAllChs();
	void ClearHisDatas();
	CSttMacroChannel* AddNewCh(const CString &strName,const CString &strID,CSttChMap *pHdMaps);

	CExBaseList m_oVolChListRef;//全部电压通道资源索引
	CExBaseList m_oCurChListRef;//全部电流通道资源索引
	CSttMacroChannel m_oUfCh;//zhouhj 2023.12.20 新增用于故障电压、故障电流通道
	CSttMacroChannel m_oIfCh;

protected:
	void ClearGroups();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttBinChlMngr :public CExBaseList
{
public:
	CSttBinChlMngr(void);
	virtual ~CSttBinChlMngr(void);

public:
	CCycleMemBuffer_double m_oHisTimesBuf;  ////历史数据的绝对时间
	CCycleMemBuffer_double m_oHisRealTimesBuf;//历史数据的相对时间

	//默认8通道开入、开出历史数据
	CCycleMemBuffer_BYTE m_arrHisBinInBuf[MAX_BINARYIN_COUNT];
	CCycleMemBuffer_BYTE m_arrHisBinOutBuf[MAX_BINARYOUT_COUNT];

	//扩展开关量历史数据
	CCycleMemBuffer_BYTE m_arrHisBinInExBuf[MAX_ExBINARY_COUNT];
	CCycleMemBuffer_BYTE m_arrHisBinOutExBuf[MAX_ExBINARY_COUNT];
};