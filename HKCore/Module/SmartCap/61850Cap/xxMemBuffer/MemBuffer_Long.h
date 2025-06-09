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
	CString m_strBufferID;   //缓冲区的标示，整个系统中，此标示唯一

	virtual UINT GetClassID()    {    return MEMCLASSID_USHORT;     }
	
	DWORD m_dwFreqZeroPosition[MAX_FREQ_ZERO_POS_BUFFER];
	UINT  m_nFreqZeroPosCount;
	UINT m_nChIndex;
	
	//缓存中已经放入的数据数量，可以大于缓存长度的大小 fdp add 2010.4.15
	__int64 m_n64BeginPos;
	__int64 m_n64EndPos;
public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//初始化
	virtual void Init();
	void SetBufferLength(long lBufferLen);

	//内存释放
	void FreeBuffer();

	//内存拷贝
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

	
	//缓存关联
	void AttachBuffer(CMemBuffer_Long *pBuffer);
	void AttachBuffer(long *pBuffer, long lLen);
	void DettachBuffer();

	void SetChanIndex(long nIndex)	{	m_nChIndex = nIndex;	}
	//缓存相关参数的获取
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
	
	//因为缓存中最后一个填入的数据有可能改变，这个函数就是改变最后一个数据的
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
