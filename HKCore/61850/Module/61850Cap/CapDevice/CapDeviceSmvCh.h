//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


	//UINT m_nChType;// ��ѹ=0������=1
	UINT m_nChRateIndex;
	double m_fChRate;

//���غ���
public:
	virtual UINT GetClassID(){return CPDCLASSID_SMVCH;};

//˽�г�Ա����
private:
	

//˽�г�Ա�������ʷ���
public:
	void SetChRateString(const CString &strRate);
	void SetChRateIndex(long nIndex);

	CString GetChType()
	{
		if (m_nChType == CAPDEVICE_CHTYPE_U)
		{
			return _T("��ѹ");
		}
		else
		{
			return _T("����");
		}
	}
	void SetChType(const CString &strType)
	{
		if (strType == _T("��ѹ") )
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

