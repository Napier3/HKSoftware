//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChBase.cpp  CCapDeviceChBase


#include "stdafx.h"
#include "CapDeviceChBase.h"

CCapDeviceChBase::CCapDeviceChBase()
{
	//初始化属性
	m_nSelect = 1;
	m_nChType = 0;
	m_nLength = 0;

	//初始化成员变量
	m_pCapRecord = NULL;
}

CCapDeviceChBase::~CCapDeviceChBase()
{
}
