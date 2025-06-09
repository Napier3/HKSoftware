//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CapDeviceChRecordMngr.h  CCapDeviceChRecordMngr

#pragma once

#include "..\CapDevice\CapDeviceSmvCh.h"
#include "..\CapDevice\CapDeviceBase.h"
#include "..\CapDevice\CapDeviceGooseCh.h"
#include "..\MemBuffer\MemBuffer_Long.h"


class CCapDeviceChRecord : public CCapRecordInterface , public CExBaseObject
{
public:
	CCapDeviceChRecord();
	virtual ~CCapDeviceChRecord();

	CMemBuffer_UShort* GetRecordBuffer()	{	return &m_oBufferUShort;	}
	COLORREF m_crColor;
	CCapDeviceChBase *m_pRecfCh;

	long m_nMinValue;
	long m_nMaxValue;

public:
	virtual void CapRecord(WORD wValue);
	virtual void CapRecord(long wValue);
	virtual void CapRecord(float fValue);
	virtual void CapRecord(double dValue);

	virtual void CapRecord(long wValue, long nPos)
	{
		m_oBufferUShort.SetValue(wValue, nPos);
		
		if (wValue > m_nMaxValue)
		{
			m_nMaxValue = wValue;
		}

		if (wValue < m_nMinValue)
		{
			m_nMinValue = wValue;
		}
	}

	virtual void CapRecord(WORD wValue, long nPos){}
	virtual void CapRecord(float fValue, long nPos){}
	virtual void CapRecord(double dValue, long nPos){}

	void SetPosition(long nPos, long nDataCount)
	{
		m_oBufferUShort.SetPosition(nPos, nDataCount);
	}

	virtual UINT GetClassID()
	{
		ASSERT (m_pRecfCh != NULL);
		return m_pRecfCh->GetClassID();
	}

	CString GetName()
	{
		if(m_pRecfCh == NULL)
		{
			return _T("");
		}
		else
		{
			return m_pRecfCh->m_strName;
		}
	}

protected:
	CMemBuffer_UShort m_oBufferUShort;
};

class CCapDeviceSmvChRecord : public CCapDeviceChRecord
{
public:
	CCapDeviceSmvChRecord();
	virtual ~CCapDeviceSmvChRecord();


	double* GetChRate()
	{
		if(m_pRecfCh == NULL)
		{
			return &m_fChRate;
		}
		else
		{
			return &((CCapDeviceSmvCh*)m_pRecfCh)->m_fChRate;
		}
	}

	UINT GetChType()
	{
		if(m_pRecfCh == NULL)
		{
			return CAPDEVICE_CHTYPE_U;
		}
		else
		{
			return ((CCapDeviceSmvCh*)m_pRecfCh)->m_nChType;
		}
	}

private:
	double m_fChRate;
};

class CCapDeviceGooseChRecord : public CCapDeviceChRecord
{
public:
	CCapDeviceGooseChRecord();
	virtual ~CCapDeviceGooseChRecord();
};


class CCapDeviceChRecordMngr : public CExBaseList
{
public:
	CCapDeviceChRecordMngr();
	virtual ~CCapDeviceChRecordMngr();

	CCapDeviceChRecord* FindByCh(CCapDeviceChBase *pCh);

	CCapDeviceChRecord* AddRecordCh(CCapDeviceChBase *pCh);
	CCapDeviceChRecord* RemoveRecord(CCapDeviceChBase *pCh);
	CCapDeviceBase *m_pRecordDevice;

	void BeginCap(BOOL bClearDevices=TRUE);
private:
	CExBaseList m_listRemove;
};

