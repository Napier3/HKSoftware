//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDevice91.h  CCapDevice91

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

class CCapDevice91 : public CCapDeviceSmvBase
{
public:
	CCapDevice91();
	virtual ~CCapDevice91();


//	long  m_nPriority;
	DWORD  m_dwVID;
	DWORD  m_dwVersion;
	DWORD  m_dwDataSet;
	DWORD  m_dwLNName;
	DWORD  m_dwLDName;

	DWORD  m_dwINomPh;
	DWORD  m_dwUNomPh;
	DWORD  m_dwINomNeutral;
	DWORD  m_dwDelayTime;
	
	DWORD  m_dwStateWord;
	DWORD  m_dwSmpCnt;
	
//重载函数
public:
	//基本方法
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE91;};

//私有成员变量
private:

//私有成员变量访问方法
public:
};

