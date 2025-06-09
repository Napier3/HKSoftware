//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceGooseCh.h  CCapDeviceGooseCh

#pragma once

#include "CapDeviceChBase.h"

#include <math.h>


inline CString st_GetGooseChType(UINT nType, long nLen)
{
	switch (nType)
	{
	case 0x83://单点
		return _T("单点");
		break;
	case 0x84://双点
		if (nLen == 2)
		{
			return _T("双点");
		}
		else
		{
			return _T("品质");
		}
		break;
	case 0x85://枚举
		return _T("枚举");
		break;
	case 0x86://UINT
		return _T("UINT");
		break;
	case 0x91://时间
		return _T("时间");
		break;
	case 0x87://浮点
		return _T("浮点");
		break;
	default:
		return _T("单点");
		break;
	}

	return _T("单点");
}



class CCapDeviceGooseCh : public CCapDeviceChBase
{
public:
	CCapDeviceGooseCh();
	virtual ~CCapDeviceGooseCh();


	//UINT m_nChType;
	CString m_strChTypeName;

//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_GOOSECH;};

//私有成员变量
private:
	

//私有成员变量访问方法
public:
	void InitChTypeName()
	{
		m_strChTypeName = st_GetGooseChType(m_nChType, m_nLength);
	}

};
