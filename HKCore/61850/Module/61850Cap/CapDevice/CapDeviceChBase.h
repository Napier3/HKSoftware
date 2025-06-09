//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceChBase.h  CCapDeviceChBase

#pragma once

#include "CapDeviceGlobal.h"

class CCapRecordInterface
{
public:
	virtual void CapRecord(WORD wValue) = 0;
	virtual void CapRecord(long wValue) = 0;
	virtual void CapRecord(float fValue) = 0;
	virtual void CapRecord(double dValue) = 0;
	virtual void CapRecord(WORD wValue, long nPos) = 0;
	virtual void CapRecord(long wValue, long nPos) = 0;
	virtual void CapRecord(float fValue, long nPos) = 0;
	virtual void CapRecord(double dValue, long nPos) = 0;
	virtual void SetPosition(long nPos, long nDataCount) = 0;
};


class CCapDeviceChBase : public CExBaseObject
{
public:
	CCapDeviceChBase();
	virtual ~CCapDeviceChBase();

	long m_nSelect;
	UINT m_nChType;
	UINT m_nLength;

private:
	CCapRecordInterface *m_pCapRecord;

//���غ���
public:
	void SetSelect(long nSelect)		
	{	
		m_nSelect = nSelect;	
// 		if (nSelect == 0)
// 		{
// 			m_pCapRecord = NULL;
// 		}
	}
	long GetSelect()					{	return m_nSelect;		}
	void AttachCapRecord(CCapRecordInterface *pRecord)	{	m_pCapRecord = pRecord;	}

	void CapRecord(long wValue)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->CapRecord(wValue);
		}
	}
	void CapRecord(long wValue, long nPos)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->CapRecord(wValue, nPos);
		}
	}

	void SetPosition(long nPos, long nDataCount)
	{
		if (m_pCapRecord != NULL)
		{
			m_pCapRecord->SetPosition(nPos, nDataCount);
		}
	}
};

