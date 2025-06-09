//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceSmvCh.cpp  CCapDeviceSmvCh


#include "stdafx.h"
#include "CapDeviceSmvCh.h"

CCapDeviceSmvCh::CCapDeviceSmvCh()
{
	//初始化属性
	m_nChType = CAPDEVICE_CHTYPE_U;// 电压=0；电流=1
	m_nChRateIndex = 0;
	m_fChRate = 1;
	SetChRateIndex(0);

	//初始化成员变量
}

CCapDeviceSmvCh::~CCapDeviceSmvCh()
{
}

void CCapDeviceSmvCh::SetChRateString(const CString &strRate)
{
	m_nChRateIndex = st_GetCapDeviceChRateIndex(strRate);
	m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
	m_fChRate = 1 / m_fChRate;
}

void CCapDeviceSmvCh::SetChRateIndex(long nIndex)
{
	m_nChRateIndex = nIndex;
	m_fChRate = st_GetCapDeviceChRate(m_nChRateIndex);
	m_fChRate = 1 / m_fChRate;
}

//////////////////////////////////////////////////////////////////////////
//
#define CAPDEVICE_CHREATE_MAX  7

static const CString g_strCapDeviceChRate[CAPDEVICE_CHREATE_MAX] = 
{
	_T("1 / 1"),
	_T("1000 / 1"),
	_T("100 / 1"),
	_T("0x01CF / 1"),
	_T("0x01CF / 5"),
	_T("0x2D41 / 10"),
	_T("0x2D41 / 57.735")
};

static const float g_fCapDeviceChRate[CAPDEVICE_CHREATE_MAX] = 
{
	1.0f, //_T("1 / 1"),
	1000.0f, //_T("1000 / 1"),
	100.0f, //_T("100 / 1");
	463.0f,//_T("0x01CF / 1"),
	92.6f,//_T("0x01CF / 5"),
	1158.5f,//_T("0x2D41 / 10"),
	200.6582f//_T("0x2D41 / 57.735")
};

CString st_GetCapDeviceChRateString(long nIndex)
{
	if (0 <= nIndex && nIndex < CAPDEVICE_CHREATE_MAX)
	{
		return g_strCapDeviceChRate[nIndex];
	}
	else
	{
		return g_strCapDeviceChRate[0];
	}
}


float st_GetCapDeviceChRate(long nIndex)
{
	if (0 <= nIndex && nIndex < CAPDEVICE_CHREATE_MAX)
	{
		return g_fCapDeviceChRate[nIndex];
	}
	else
	{
		return g_fCapDeviceChRate[0];
	}
}

long st_GetCapDeviceChRateIndex(const CString &strID)
{
	long nIndex = 0;
	
	for (nIndex=0; nIndex<CAPDEVICE_CHREATE_MAX; nIndex++)
	{
		if (strID == g_strCapDeviceChRate[nIndex])
		{
			return nIndex;
		}
	}

	return 0;
}

void st_AddCapDeviceChRateTo(CComboBox *pComboBox)
{
	long nIndex = 0;
	pComboBox->ResetContent();

	for (nIndex=0; nIndex<CAPDEVICE_CHREATE_MAX; nIndex++)
	{
		long nItem = pComboBox->AddString(g_strCapDeviceChRate[nIndex]);
		pComboBox->SetItemData(nItem, nIndex);
	}
}


