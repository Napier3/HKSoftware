// MemBuffer_Long.h: interface for the CMemBuffer_Long class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBUFFER_Long_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_)
#define AFX_MEMBUFFER_Long_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MemBufferDef.h"


class CMemBuffer_Long  : public CMemBufferInterface
{
public:	
	CMemBuffer_Long();
	virtual ~CMemBuffer_Long();
	CString m_strBufferID;   //�������ı�ʾ������ϵͳ�У��˱�ʾΨһ

	virtual UINT GetClassID()    {    return MEMCLASSID_USHORT;     }
	
	DWORD m_dwFreqZeroPosition[MAX_FREQ_ZERO_POS_BUFFER];
	UINT  m_nFreqZeroPosCount;
	UINT m_nChIndex;
	
	//�������Ѿ�������������������Դ��ڻ��泤�ȵĴ�С fdp add 2010.4.15
	__int64 m_n64BeginPos;
	__int64 m_n64EndPos;
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//��ʼ��
	virtual void Init();
	void SetBufferLength(long lBufferLen);

	//�ڴ��ͷ�
	void FreeBuffer();

	//�ڴ濽��
	long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_Long *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(long *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(long *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);
	long AddValue(long *pValue);
	long AddValue(long nValue);

	void SetValue(long nValue, long nPos)
	{
		ASSERT ( (0 <= nPos) && (nPos < m_nBufferLength) );
		m_pBuffer[nPos] = nValue;
	}
	void SetPosition(long nPos, long nDataCount)
	{
		m_nDataFillBeginPos = nPos;
		m_nDataLength = nDataCount;
	}

	
	//�������
	void AttachBuffer(CMemBuffer_Long *pBuffer);
	void AttachBuffer(long *pBuffer, long lLen);
	void DettachBuffer();

	void SetChanIndex(long nIndex)	{	m_nChIndex = nIndex;	}
	//������ز����Ļ�ȡ
	virtual long GetDataLength()                       {    return m_nDataLength;                      }
	virtual long GetDataFillBeginPosition()            {    return m_nDataFillBeginPos;                }
	long* GetDataFillBeginBuffer()   {    return m_pBuffer + m_nDataFillBeginPos;    }
	virtual long GetBufferLength()                     {    return m_nBufferLength;                    }
	long* GetBuffer()                {    return m_pBuffer;                          }
	BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < m_nBufferLength); }
	virtual void OffsetDataFillBeginPosition(long nLen);
	void SetCoefValue(double dCoefValue)       {    m_dCoefValue = dCoefValue;     }
	double* GetCoefValueRef()                  {    return &m_dCoefValue;          }
	double  GetCoefValue()                     {    return m_dCoefValue;           }
	
	//��Ϊ���������һ������������п��ܸı䣬����������Ǹı����һ�����ݵ�
	void ModifyLastValue(short nOffSet);
protected:
	long m_nBufferLength;	
	long m_nDataFillBeginPos;
	long m_nDataLength;
	long *m_pBuffer;
	double m_dCoefValue;

	BOOL m_bBufferAttach;
};

typedef CMemBuffer_Long CMemBuffer_UShort;

#endif // !defined(AFX_MEMBUFFER_Long_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_)
