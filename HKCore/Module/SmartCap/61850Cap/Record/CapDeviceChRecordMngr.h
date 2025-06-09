//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CapDeviceChRecordMngr.h  CCapDeviceChRecordMngr

#pragma once

#include "../CapDevice/CapDeviceSmvCh.h"
#include "../CapDevice/CapDeviceBase.h"
#include "../CapDevice/CapDeviceGooseCh.h"
#include "../../../Record/RtMemBuffer/MemBuffer.h"
#include "../../../Record/MR1200BaseApp.h"
#include "../../../Record/RecordTest/RecordTestCalThread.h"

//ץ��ͨ��¼�����ݶ������ڼ�¼�ͱ��沨������
//m_pRecfChΪ̽��ͨ����������
class CCapDeviceChRecord : public CCapRecordInterface , public CExBaseObject
{
public:
	CCapDeviceChRecord();
	virtual ~CCapDeviceChRecord();

	CMemBuffer_Long* GetRecordBuffer()	{	return &m_oBufferUShort;	}
	COLORREF m_crColor;
	CCapDeviceChBase *m_pRecfCh; //̽��ͨ����������
	CExBaseObject *m_pRcdCalVarRef; //���μ���ͨ������

	long m_nMinValue;
	long m_nMaxValue;

public:
	virtual double GetRange();
	virtual void CapRecord(WORD wValue);
	virtual void CapRecord(long nValue);
	virtual void CapRecord(float fValue);
	virtual void CapRecord(double dValue);
	virtual void CapRecord(long wValue, long nPos);

	virtual void CapRecord(WORD wValue, long nPos){}
	virtual void CapRecord(float fValue, long nPos){}
	virtual void CapRecord(double dValue, long nPos){}

	void SetPosition(long nPos, long nDataCount)	{		m_oBufferUShort.SetPosition(nPos, nDataCount);	}
	virtual UINT GetClassID()	{		ASSERT (m_pRecfCh != NULL);		return m_pRecfCh->GetClassID();	}
	CString GetName();

	void SetHdIndex(long nIndex)	{	m_oBufferUShort.m_nHdIndex = nIndex;	}
	long GetHdIndex()	{	return m_oBufferUShort.m_nHdIndex;	}
	void SetChIndex(long nIndex)	{	m_oBufferUShort.m_nChIndex = nIndex;	}
	long GetChIndex()	{	return m_oBufferUShort.m_nChIndex;	}

protected:
	CMemBuffer_Long m_oBufferUShort;
};

class CCapDeviceSmvChRecord : public CCapDeviceChRecord
{
public:
	CCapDeviceSmvChRecord();
	virtual ~CCapDeviceSmvChRecord();

	virtual double GetRange();
	double GetChRateVal();
	double* GetChRate();
	UINT GetChType();

private:
	double m_fChRate;
};

class CCapDeviceGooseChRecord : public CCapDeviceChRecord
{
public:
	CCapDeviceGooseChRecord();
	virtual ~CCapDeviceGooseChRecord();
};


//Ŀǰû�п��ǲ�ͬ���ƿ鲨������ʱ��ͬ�������⣬�����Ҫ�޸�
//�����ͬ���ƿ�ͬ��ץ�����������ݵ�ʱ���ǲ�һ���ģ�������������ֻ�AT02
class CCapDeviceChRecordMngr : public CExBaseList
{
public:
	CCapDeviceChRecordMngr();
	virtual ~CCapDeviceChRecordMngr();

	CCapDeviceChRecord* FindByCh(CCapDeviceChBase *pCh);
	void RecordDevice(CCapDeviceBase *pCapDevice);
	void InitRecordTest(); //��ʼ¼��֮ǰ����ʼ��¼��

	//���һ��ͨ������¼ͨ������
	void ChangeChRecordState(CCapDeviceChBase *pCh, long nState);
	CCapDeviceChRecord* AddRecordCh(CCapDeviceChBase *pCh);
	CCapDeviceChRecord* RemoveRecord(CCapDeviceChBase *pCh);
	void AdjustRecordChRange();

	void BeginCap(BOOL bClearDevices=TRUE);
	void UpdateAllRefRtVariable();//����ȫ��ͨ���Ĳο���  20221214 zhouhj

	//2022-5-3  lijunqing
	void ClearCap();

private:
	CExBaseList m_listRemove;

public:
	//CCapDeviceBase *m_pRecordDevice;
	CRecordTest *m_pRecordTest;  

protected:
	CRtSingleVariable* InitAnalogVariable(CCapDeviceSmvChRecord *pAnalog, long &nIndex);
	CRtBinaryVariable* InitBinaryVariable(CCapDeviceGooseChRecord *pBinary, long& nIndex);
	BOOL IsChRecordCreated(CCapDeviceChRecord *pChRecord);

	void InitVariablePhaseID(CRtSingleVariable *pVariable);
};

//////////////////////////////////////////////////////////////////////////
//

inline double CCapDeviceChRecord::GetRange()
{
    double dRange1 = abs(m_nMinValue);
    double dRange2 = abs(m_nMaxValue);

    if (dRange1 > dRange2)
    {
        return dRange1;
    }
    else
    {
        return dRange2;
    }
}

inline void CCapDeviceChRecord::CapRecord(WORD wValue)
{
	m_oBufferUShort.AddValue(wValue);
}

inline void CCapDeviceChRecord::CapRecord(long nValue)
{
	m_oBufferUShort.AddValue(nValue);
}

inline void CCapDeviceChRecord::CapRecord(float fValue)
{

}

inline void CCapDeviceChRecord::CapRecord(double dValue)
{

}

inline void CCapDeviceChRecord::CapRecord(long wValue, long nPos)
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


inline double CCapDeviceSmvChRecord::GetChRateVal()
{
	if(m_pRecfCh == NULL)
	{	
		return m_fChRate;
	}
	else
	{
		return ((CCapDeviceSmvCh*)m_pRecfCh)->m_fChRate;
	}
}

inline double* CCapDeviceSmvChRecord::GetChRate()
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

inline UINT CCapDeviceSmvChRecord::GetChType()
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
