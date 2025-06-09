//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.h  CSttParas

#pragma once

#include "SttCmtrdCfgDefineGlobal.h"
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/Record/RtMemBuffer/MemBuffer_Float.h"
#include "../../../Module/Record/Comtrade/ComtradeMngr.h"
#include "../../Module/AdjustTool/SttAdjDevice.h"
#include "../../Module/AdjustTool/SttAdjModule.h"

#ifndef REPLAY_DIGITAL_MODULE_CH_NUM
#define REPLAY_DIGITAL_MODULE_CH_NUM	12	
#endif


#ifndef STT_REPLAY_WEEK_MODULE_CH_EeType_VOL
#define STT_REPLAY_WEEK_MODULE_CH_EeType_VOL		"Voltage"
#endif

#ifndef STT_REPLAY_WEEK_MODULE_CH_EeType_Curr
#define STT_REPLAY_WEEK_MODULE_CH_EeType_Curr		"Current"
#endif

class CSttModuleChComtradeBind : public CExBaseObject
{//可以描述模块、通道
public:
	CSttModuleChComtradeBind();
	virtual ~CSttModuleChComtradeBind();

public:
	CDataGroup *m_pHdChRef;  //关联的校准对象的硬件通道对象
	double m_fMaxAbs;	//最大绝对值
	double m_fMomentaryVal;	//最大绝对值
	//zhouhj 2023.9.11 此处与下面的m_nChA_Index有一定重复,统一用下面的
//	long m_nComtradeChID_A, m_nComtradeChID_B;//录波文件中的ChID,电压电流统一编号
	CString m_strComtradeChID_A, m_strComtradeChID_B;
	double m_dCoefA, m_dCoefB, m_dK;
	long m_nChA_Index,m_nChB_Index;//新增通道Index,对应界面下拉框,0代表不选择,后续对应第几个电压/电流通道(电压电流单独编号,即对应第几个电压/电流通道)
	long m_nChSelected;

	CComtradeAnalogData *m_pCh_A, *m_pCh_B;//此处关联的是原始波形里的通道，而不是插值后的!!!!!!
	
	CComplexMemBuffer_Float *m_pReplayBuf;//回放通道缓存

	//临时绘图变量
	double m_dCoefValue;
	double m_dZeroValue;
	
public:
	double CalcChannelMaxValue();
	BOOL IsChannelSelected();

	//初始化通道回放缓存
	void InitChReplayBuf(long nMaxPoints);

	void InitCh_A(CComtradeAnalogData *pAnalogData);
	void InitCh_B(CComtradeAnalogData *pAnalogData);

	//清空通道回放缓存
	void ResetChReplayBuf();

	//如果描述模块
	BOOL IsModuleType_U();//	{	return stt_adj_HdChDef_Is_Voltage(m_pHdChRef);}
	BOOL IsModuleType_I();//	{	return stt_adj_HdChDef_Is_Current(m_pHdChRef);}
	virtual BOOL IsModuleType_B(){		return FALSE;	}//wuxinyi 2024.1.29 开关量
	virtual BOOL IsModuleType_W(){		return FALSE;	}//wuxinyi 2024.7.2  弱信号


	long GetMaxPoints();//获取当前通道总点数
// 	long GetValue_DataA();//zhouhj 2023.9.11 删除此处两个函数,其获取的
// 	long GetValue_DataB();

	double GetValue_DataK();
	CString GetUnit();
	CString GetModuleChPhase();//zhouhj 20211104 获取该通道在该模块中的相别
	int GetIndexByID(CString ChStrID);//通过ID获取通道序号

	CString GetEleTypeString();//获取电气类型
	int GetEleTypeIndex();
	void SetEleType(int nEleType);
	float GetChDCMaxValue();//获取直流最大值
};

class CSttModuleBinaryChComtradeBind : public CExBaseObject
{
public:
	CSttModuleBinaryChComtradeBind();
	virtual ~CSttModuleBinaryChComtradeBind();

public:
	CComtradeBinaryData *m_pBinaryCh;
	CString m_strComtradeBinaryCh;	//开关量通道
	long m_nBinaryCh_Index;			//下拉框选择通道
	long m_nChState;				//0-断开 1-闭合 

public:
	virtual BOOL IsModuleType_B(){		return TRUE;	}//开关量
	void InitBinaryCh(CComtradeBinaryData *pBinaryData);//初始化开关量通道

};


class CSttModuleComtradeBind : public CExBaseList
{
public:
	CSttModuleComtradeBind();
	virtual ~CSttModuleComtradeBind();
	//zhouhj 2023.8.14 按照结构体内模块顺序创建的ID,该ID格式Format(_T("Module%ld"),nModuleIndex);nModuleIndex从0开始编号
	//m_strID规则Format(_T("%s%d"), strModuleType.GetString(), nModuleIndex);strModuleType为硬件信息插件ID,nModuleIndex从1开始编号
	CString m_strModuleID;
	long m_nModulePos;

	BOOL IsModuleSelected();
	double CalcChMaxValueByIndex(long nChIndex);
	double GetModuleMaxValue_U();
	double GetModuleMaxValue_I();
	void ScalingModuleMaxValue(float fK);
	void InitModuleReplayBuf(long nMaxPoints);
	void ResetModuleReplayBuf();

	long GetCount_U();
	long GetCount_I();
	long GetCount_B();

public:
	//开出量
	CComplexMemBuffer_Float *m_pReplayBufBinary1;//回放通道缓存 低位
	CComplexMemBuffer_Float *m_pReplayBufBinary2;//回放通道缓存 高位
	void InitReplayBufBinary(long nLength);//初始开出量回放通道缓存
	void ResetReplayBufBinaryBuf(/*long nLength*/);//设置开出量回访缓存长度

	//弱信号
	float m_fPTRatio[2];	//PT变比参数
	float m_fCTRatio[2];	//CT变比参数
	BOOL IsWeekChTypeChg();
	void SetWeekChTypeChg(long nWeekChTypeChg);

public:
	BOOL IsDigitalTypeModule();
	BOOL IsBinaryTypeModule();//是否为开出量模块
	BOOL IsAnalogTypeModule();
	BOOL IsWeekTypeModule();

private:
	long  m_nWeekChTypeChg;//通道电气类型可变；1:可变,0:不可变

};


class CSttModulesComtradeBind : public CExBaseList
{
public:
	CSttModulesComtradeBind();
	virtual ~CSttModulesComtradeBind();
	
public:
	CSttAdjDevice *m_pSttAdjDevice;	
	void InitBySttAdjDevice(CSttAdjDevice *pAdjDevice);
	void InitBinaryModule();

	long m_nChMaxPoints;
	CSttModuleComtradeBind *m_pBinaryModuleComtradeBind;//主板开出量模块
	int m_nUseBinaryModule;//主板开出模块是否使用--下发使用
	int m_nUseBinaryModuleWidget;//主板开出模块界面是否使用
	BOOL IsBinaryModuleSelected();//主板开出是否使用

	void InitModuleReplayBuf(long nChMaxPoints);
	long GetDataLength();
	long GetModuleCount();//20231101 wxy 获取模块总数
	CSttModuleComtradeBind* FindByModuleID(const CString &strModuleID);
	CSttModuleComtradeBind * GetBinaryModule();//获得主板开出量指针接口

	int GetAnalogModuleCount();
	int GetDigitalModuleCount();
	int GetWeekModuleCount();

	void InitAllMoudleCount();

	int m_nHasAnalog;
	int m_nHasDigital;
	int m_nHasWeek;
	void SetSystemOutputType(int nHasAnalog, int nHasDigital, int nHasWeek);

private:
	int m_nDigitalModuleCount;
	int m_nAnalogModuleCount;
	int m_nWeekModuleCount;

};
