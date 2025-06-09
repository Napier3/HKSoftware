#pragma once
#include "CapDeviceSmvCh.h"
class CCapDeviceRcdCh : public CCapDeviceSmvCh
{
public:
	CCapDeviceRcdCh();
	virtual ~CCapDeviceRcdCh();
	CString GetModuleName();

	long m_nEType;//记录类型 0-无效，1-电压，2-电流，3-有源开关量，4-无源开关量
	float m_fSwitchVolt;//有源开关量翻转阈值
	long m_nMeasGear;//采集档位
	float m_dClampRate;//夹钳比率
//	CString m_strRcdChName;  //通道存录波文件使用的名称
	double m_dPrimValue; //一次侧值
	double m_dSecondValue; //二次侧值

	DWORD m_dwComtradeChData;  //2024.9.23 zhangyq Comtrade文件对应指针

	virtual UINT GetClassID(){ return CPDCLASSID_RCDCH; };
};

