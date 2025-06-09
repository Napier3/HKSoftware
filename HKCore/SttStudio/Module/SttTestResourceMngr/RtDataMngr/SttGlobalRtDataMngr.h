#pragma once
#include "SttMacroChannelsAsync.h"
#include "../TestResource/SttTestResourceBase.h"
#include "../../SttCmd/SttChMaps.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttRtDataChangeEvent//矢量图、时间特性图等的虚基类
{
public:
	CSttRtDataChangeEvent(){}
	virtual ~CSttRtDataChangeEvent(){}
	virtual void OnRtDataChanged() = 0;//抽象虚函数,实现收到实时数据后的处理
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CSttGlobalRtDataMngr
{
public:
	CSttGlobalRtDataMngr();
	virtual ~CSttGlobalRtDataMngr();
public:
	long m_nMode;// 1:异步模式;2: 同步模式
	CSttMacroChannelsAsync*m_pMacroChannelsMngr;//异步模式实际资源对象
	CSttMacroChannels *m_pMacroChannels;//同步模式实际资源对象
	CSttBinChlMngr m_oBinChlMngr;//开关量历史数据对象

	CSttRtDataChangeEvent *m_pEventToVector;	//矢量图
	CSttRtDataChangeEvent *m_pEventToProgress;	//幅值时序图

	//定义其他更新的事件接受对象，例如：序分量、功率图等
	//2021-6-1  yangyijun
	CSttRtDataChangeEvent *m_pEventToPower;		//功率图
	CSttRtDataChangeEvent *m_pEventToLineVolt;	//线电压
	CSttRtDataChangeEvent *m_pEventToSequence;  //序分量

	int m_nRtDataFlag;	//标识当前是否正在处理接收实时数据
	int m_bAutoMode;	//自动模式 2021-6-25 yyj
	//这个后续再考虑是否用这个标志
public:
	void InitSoftResource(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);//初始化软件资源
	void InitGroup();//初始化所有通道分组
	void AddMacroChValues(CSttParas *pParas);//engine程序调用该函数
	//界面参数更新，只更新实时数据，不更新历史数据
	//下面函数参数1为数组指针,参数2为通道类型，参数3为数组个数
	void SetMacroChValues(tmt_RtDataCh *pRtVector, long nChannelType, long nCount);
	//下述函数,为设置单个界面参数函数
	void SetMacroChValue(tmt_RtDataCh *pRtVector, long nChannelType, long nChIndex);
	void SetMacroChValue(double dMag, double dAng, long nChannelType, long nChIndex);
	void SetMacroChValue(tmt_RtDataCh *pRtVector, const CString &strChID);
	void SetMacroChValue(double dMag, double dAng, const CString &strChID);
	void SetMacroChMagValue(double dMag, const CString &strChID);
	void SetMacroChAngValue(double dAng, const CString &strChID);
//	void RegisterRtDataChangeRcv(CSttRtDataChangeEvent * pEventRcv);//注册需要更新显示的矢量图、时间特性图等, 【此函数是在初始化中调用的】
	void FireRtDataChangeEvent();//在更新完全局唯一对象中实时数据值后，调用此函数遍历m_listRtDataChangeRcv链表，分别调用矢量图等的OnRtDataChanged()函数

	void ClearHisDatas();//清除全部历史数据,在开始测试时，需要将历史数据清空

	void SetAutoMode(bool bAuto){	m_bAutoMode = bAuto;	}
	bool IsAutoMode(){	return m_bAutoMode; }
protected:
	void InitSoftResource_Sync(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);
	void InitSoftResource_Async(CSttTestResourceBase *pTestRerouce,CSttChMaps *pChMaps);
};


/*
//这个类定义成全局对象，根据m_nMode 值的不同来决定如何使用。
m_nMode = 1；异步模式，需要三份软件资源，用m_pMacroChannelsMngr;
m_nMode = 2；同步模式，用MacroChannels;表示的是一份数据，就不用Mngr了，直接用m_pMacroChannels。
当数据从engine 过来了，调用AddMacroChValues，同时调用具体图形更新接口实现更新绘图FireRtDataChangeEvent();触发事件，把数据改变， 改变了缓冲区。*/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//CSttGlobalRtDataMngr g_oSttGlobalRtDataMngr;//全局唯一对象,处理实时接收数据

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
