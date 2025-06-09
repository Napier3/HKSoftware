//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDevice92.h  CCapDevice92

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceSmvBase.h"

class CCapDevice92 : public CCapDeviceSmvBase
{
public:
	CCapDevice92();
	virtual ~CCapDevice92();


	CString m_strSVID;
	long m_nConfRev;
	long m_nSmpSynch;
	
//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICE92;};

//私有成员变量
private:

//私有成员变量访问方法
public:

};

