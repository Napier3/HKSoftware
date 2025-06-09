//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGoose.h  CCapDeviceGoose

#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "CapDeviceGooseCh.h"

class CCapDeviceGoose : public CCapDeviceBase
{
public:
	CCapDeviceGoose();
	virtual ~CCapDeviceGoose();

	long  m_dwVID;
	long  m_dwVersion;
	CString  m_strGooseId;
	CString  m_strDataSet;
	CString  m_strDataSetDesc;
	CString  m_strgocbRef;
	CString  m_strgocbIED;
	long  m_nTest;
	long  m_dwTimeAllowToAlive;
	long m_dwStNum;
	long m_dwSqNum;
	long m_dwNdsCom;
	double m_dTime;
	
//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICEGOOSE;};

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CCapDeviceChBase* CreateChannel()		{	return new CCapDeviceGooseCh();	}

};

