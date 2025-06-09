//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvCh.h  CCapDeviceSmvCh

#pragma once

#include "CapDeviceChBase.h"

#include <math.h>

class CCapDeviceSmvCh : public CCapDeviceChBase
{
public:
	CCapDeviceSmvCh();
	virtual ~CCapDeviceSmvCh();


	//UINT m_nChType;// 电压=0；电流=1；时间=2
	UINT m_nChRateIndex;
	double m_fChRate;

	//yyj
	DWORD m_wValue;		//9-1通道原始值
	DWORD m_dwValue;	//9-2通道原始值
	DWORD m_dwQuality;	//9-2通道品质

	float m_fValue;		//计算值
	long m_nAccurLevel;//zhouhj 准确级
	long m_nChAngType;//20221210 zhouhj 通道相别,包含组号，以电流通道为例0-Ia1 1-Ib1 2-Ic1 3-I01 4-Ia2

//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_SMVCH;};
	virtual void InitChannel(CIecCfgDataChBase *pIecCfgDataCh);
	virtual void InitChannelAttrs(CDvmData *pChData);


//私有成员变量
private:
	

//私有成员变量访问方法
public:
	void SetChRateString(const CString &strRate);
	void SetChRateIndex(long nIndex);
	void UpdateChDescByChTypeChAng();//202212121 zhouhj  根据通道类型、通道相别自动生成通道描述

	CString GetChType()
	{
		if (m_nChType == CAPDEVICE_CHTYPE_U)
		{
			return _T("电压");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_I)
		{
			return _T("电流");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_T)
		{
			return _T("时间");
		}
		else if (m_nChType == CAPDEVICE_CHTYPE_B)
		{
			return _T("状态值");
		}
		else
		{
			return _T("其它");
		}
	}
	void SetChType(const CString &strType)
	{
		if (strType == _T("电压") || strType == _T("Vol"))
		{
			m_nChType = CAPDEVICE_CHTYPE_U;
		}
		else if (strType == _T("电流") || strType == _T("Curr") || strType == _T("CurrMeasure"))
		{
			m_nChType = CAPDEVICE_CHTYPE_I;
		}
		else if (strType == _T("时间") || strType == _T("UTCTime"))
		{
			m_nChType = CAPDEVICE_CHTYPE_T;
		}
		//chenling 2024.6.4 否则long m_nChType[STCAPPARSE_DATA_MAX_COUNT]绑定不对
		else if (strType == _T("其它") || strType == _T("other")) 
		{
			m_nChType = CAPDEVICE_CHTYPE_N;
		}
		else if (strType == _T("状态值") ||strType == _T("StateValue"))
		{
			m_nChType = CAPDEVICE_CHTYPE_B;
		}
		

//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("(CCapDeviceSmvCh)%s;%s;%d;%s"),m_strID.GetString(),m_strName.GetString(),m_nChType,strType.GetString());
	}

public:
	void WriteRcdFile_Comtrade(double *pdLong, long nCount, const CString &strComtradeFile);
	virtual void UpdateChTypeAndLength(WORD wChType,WORD wLength);
	virtual void InitAfterSetChType();
};

CString st_GetCapDeviceChRateString(long nIndex);
float st_GetCapDeviceChRate(long nIndex);
long st_GetCapDeviceChRateIndex(const CString &strID);
void st_AddCapDeviceChRateTo(CComboBox *pComboBox);
float st_GetCapDeviceSVRate(CExBaseObject* pSmvCh,BOOL bDCFT3 = FALSE);//zhouhj 2023.11.24 参数2标记是否为柔直FT3模式

