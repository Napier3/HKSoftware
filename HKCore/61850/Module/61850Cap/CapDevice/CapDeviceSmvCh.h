//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvCh.h  CCapDeviceSmvCh

#pragma once

#include "CapDeviceChBase.h"

#include <math.h>

#define CAPDEVICE_CHTYPE_U   0
#define CAPDEVICE_CHTYPE_I   1



class CCapDeviceSmvCh : public CCapDeviceChBase
{
public:
	CCapDeviceSmvCh();
	virtual ~CCapDeviceSmvCh();


	//UINT m_nChType;// 电压=0；电流=1
	UINT m_nChRateIndex;
	double m_fChRate;

//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_SMVCH;};

//私有成员变量
private:
	

//私有成员变量访问方法
public:
	void SetChRateString(const CString &strRate);
	void SetChRateIndex(long nIndex);

	CString GetChType()
	{
		if (m_nChType == CAPDEVICE_CHTYPE_U)
		{
			return _T("电压");
		}
		else
		{
			return _T("电流");
		}
	}
	void SetChType(const CString &strType)
	{
		if (strType == _T("电压") )
		{
			m_nChType = CAPDEVICE_CHTYPE_U;
		}
		else
		{
			m_nChType = CAPDEVICE_CHTYPE_I;
		}
	}
};

CString st_GetCapDeviceChRateString(long nIndex);
float st_GetCapDeviceChRate(long nIndex);
long st_GetCapDeviceChRateIndex(const CString &strID);
void st_AddCapDeviceChRateTo(CComboBox *pComboBox);

