// MemBuffer_UnsignedShort.h: interface for the CMemBuffer_UnsignedShort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBUFFER_UNSIGNEDSHORT_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_)
#define AFX_MEMBUFFER_UNSIGNEDSHORT_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtMemBufScript.h"
#include "MemBufferDef.h"


class CMemBuffer_UnsignedShort  : public CMemBufferInterface
{
public:	
	CMemBuffer_UnsignedShort();
	virtual ~CMemBuffer_UnsignedShort();

	virtual UINT GetClassID()    {    return MEMCLASSID_USHORT;     }
	
	virtual long CopyBuffer(CMemBufferInterface *pBuffer, long &lCopyBeginPos, long lGap);

public:
	virtual BOOL ExecScript(long nPos1Begin, long nPos1End, long nPos2Begin, long nPos2End)  {    return TRUE;     }

public:
	//初始化
	virtual void Init();
	void SetBufferLength(long lBufferLen);

	//内存释放
	void FreeBuffer();

	//内存拷贝
	//long CopyBuffer(long lLen, long lGap , BOOL bOffsetBuffer, long &lPos1Begin , long &lPos1End, long &lPos2Begin, long &lPos2End);
	long CopyBuffer(CMemBuffer_UnsignedShort *pBuffer, long &lCopyBeginPos, long lGap = 1);
	long CopyBuffer(unsigned short *pBuffer, long lLen, long lGap = 1);
	long CopyBufferByPos(unsigned short *pBuffer, long lBeginPos, long lEndPos, long lGap = 1);
	long AddValue(unsigned short *pValue);
	long AddValue(unsigned short nValue);
	
	void SetValue(unsigned short nValue, long nPos)
	{
		ASSERT ( (0 <= nPos) && (nPos < m_nBufferLength) );
		m_pBuffer[nPos] = nValue;
	}

	//缓存关联
	void AttachBuffer(CMemBuffer_UnsignedShort *pBuffer);
	void AttachBuffer(unsigned short *pBuffer, long lLen);
	void DettachBuffer();

	void SetChanIndex(long nIndex)	{	m_nChIndex = nIndex;	}
	
	//缓存相关参数的获取
	unsigned short* GetDataFillBeginBuffer()   {    return m_pBuffer + m_nDataFillBeginPos;    }
	virtual unsigned short* GetBuffer()                {    return m_pBuffer;                          }
	virtual void OffsetDataFillBeginPosition(long nLen);
	
	BOOL CanAppendBuffer(long nLen)            {    return (m_nDataFillBeginPos + nLen < m_nBufferLength); }
	void SetCoefValue(double dCoefValue)       {    m_dCoefValue = dCoefValue;     }
	double* GetCoefValueRef()                  {    return &m_dCoefValue;          }
	double  GetCoefValue()                     {    return m_dCoefValue;           }
	
	//因为缓存中最后一个填入的数据有可能改变，这个函数就是改变最后一个数据的
	void ModifyLastValue(short nOffSet);
protected:
	unsigned short *m_pBuffer;
	double m_dCoefValue;

	BOOL m_bBufferAttach;
/*
#ifdef _use_global_log_
public:
	void LOG_ShowBuffer(BOOL bShowTitle = FALSE);
	void LOG_ShowBufferInfor();
#endif*/

};

#endif // !defined(AFX_MEMBUFFER_UNSIGNEDSHORT_H__3E1FA0D6_F91E_40FB_BD0F_A68A0B7F3A98__INCLUDED_)
