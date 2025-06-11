#pragma once

//2022-12-02  lijunqing  
#include "../../../Assist/SttAssistGlobalApi.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"

#define STT_IEC_RECORD_TIMER_DEFAULT_VALUE              0.5f

#define STT_MUTEST_CHSSET_MODIFY_TYPE_NO                              0  //没有参数改变
#define STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc                1  //只修改了变比,准确级,描述,选择状态
#define STT_MUTEST_CHSSET_MODIFY_TYPE_ChTypeMap                       2  //修改了通道类型和通道映射

class CSttIecRecordCbInterface :public CSttWndAssistInterface  //2022-12-02 lijunqing 测试助手相关的接口
{
public:
	CSttIecRecordCbInterface(void);
	virtual ~CSttIecRecordCbInterface(void);

	void SetMUTestMode(bool bMUTestMode){m_bMUTestMode = bMUTestMode;}
	bool IsMUTestMode(){return m_bMUTestMode;}

	virtual void BtnBack(){}//返回按钮功能
	virtual void InitIecRecordCb(const CString &strIecFunc){}//用于区分录波存储模式还是非存储模式
	virtual void SetSelectedCbs(CExBaseList *pSelectedCbs){}
	virtual void Ats_IecRecord(BOOL bIsFromIecfgFile){}
//	virtual void Connect_UpdateMUTimeAccurRlt(BOOL bCoonect){}
	virtual void SetEnable_BtnBack(bool bEnable){}
	virtual void UpdateSVDatasetsPowerVector(){}
//	virtual void UpdateCapDevice(CCapDeviceBase *pCapDevice){}
	virtual void ExecIecFunc(){}//执行当前测试功能
	virtual bool IsTabUI_Mode(){return false;}//返回当前控制块界面显示方式是否为tab显示方式
	virtual void Update_IecRcdTimer();

	//更新写文件的大小和时间
	virtual void UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize);

	//更新首周波测试特性图
	virtual void UpdateFirstCirclePlot(long nChSetModifyType);

	CDvmData *m_pSVDelayData;
	float m_fIecRcdTimer;
	CExBaseList *m_pSelectedCbs;
	BOOL m_bStopTimerUpdate;//停止定时器的更新,在IEC配置修改后,需要立即停止定时器的更新,防止引用的IEC配置链表对象已被析构
protected:
	bool m_bMUTestMode;//20220822 合并单元测试模式
};

extern CSttIecRecordCbInterface *g_pSttIecRecordCbWidget;