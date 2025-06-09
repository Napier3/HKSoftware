#include "CapDeviceRcdCh.h"


CCapDeviceRcdCh::CCapDeviceRcdCh()
{
	m_fChRate = 0.001f;
	m_nChType = CAPDEVICE_CHTYPE_U;
	m_dPrimValue = 100.00f;
	m_dSecondValue = 1.00f;
	m_nEType = 1;
	m_fSwitchVolt = 5;
	m_nMeasGear = 1;
	m_dClampRate = 1000;
	m_nChAngType = 1;
	m_dwComtradeChData = 0;
}


CCapDeviceRcdCh::~CCapDeviceRcdCh()
{
}

CString CCapDeviceRcdCh::GetModuleName()
{
	CExBaseObject *pParent = (CExBaseObject*)GetParent();

	if (pParent == NULL)
	{
		return "";
	}

	return pParent->m_strName;
}
