// RtMemBufferChannel.h: interface for the CRtMemBufferChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTMEMBUFFERCHANNEL_H__C4421880_18FD_4BD9_8084_BEECBF3BA868__INCLUDED_)
#define AFX_RTMEMBUFFERCHANNEL_H__C4421880_18FD_4BD9_8084_BEECBF3BA868__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "MemBuffer_UnsignedShort.h"
#include "MemBufferDef.h"
#include "MemBuffer.h"

class CRtMemBufferChannel  : public CExBaseObject
{
public:
	CRtMemBufferChannel();
	virtual ~CRtMemBufferChannel();

	virtual UINT GetClassID()    {    return MEMCLASSID_CHANNEL;     }
	UINT  m_nID;
	
#define  RTCH_TYPE_NORMAL    0 //模拟和开关的单通道
#define  RTCH_TYPE_COMPLEX   1
#define  RTCH_TYPE_GPS       2
	
public:
	//初始化相关
	void Init(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	void Init();//创建缓存管理对象
	void SetMemBufferLength(long nRecordBufferLen, long nSpyMemBufferLen);
	void SetSpyMemBufferLength(long nBufferLen);
	void SetRecordMemBufferLength(long nBufferLen);
	void InitDataPos()	;//初始化数据索引
	//释放缓存
	void FreeRecordBuffer();
	void FreeSpyBuffer();	

	//缓存数据拷贝
	long CopySpyMemBufferToRecordBuffer(long nGap = 1);

	//缓存关联
	void AttachSpyMemBuffer(CMemBuffer_UShort* pMemBuffer);
	void AttachRecordMemBuffer(CMemBuffer_UShort* pMemBuffer);

	//获得缓存,加2的为数据缓存对象,不加的为缓存管理对象
	unsigned short* GetSpyMemBuffer2() ;
	long* GetSpyMemBuffer2_long() ;
	CMemBufferInterface* GetSpyMemBuffer() ; 
	unsigned short* GetRecordMemBuffer2();
	long* GetRecordMemBuffer2_long();
	CMemBufferInterface* GetRecordMemBuffer();


#ifdef COMPLEXVARIABLE_USE_FLOAT
	float* GetLSpyMemBuffer2()                {   return m_pLSpyMemBuffer == NULL ? NULL : m_pLSpyMemBuffer->GetBuffer_float(); }
	CMemBuffer_Float* GetLSpyMemBuffer()      {   return m_pLSpyMemBuffer;       }
	float* GetLRecordMemBuffer2()             {   return m_pLRecordMemBuffer == NULL  ? NULL : m_pLRecordMemBuffer->GetBuffer_float();  }
	CMemBuffer_Float* GetLRecordMemBuffer()   {   return m_pLRecordMemBuffer;    }
#else
	long* GetLSpyMemBuffer2()                 {   return m_pLSpyMemBuffer == NULL ? NULL : m_pLSpyMemBuffer->GetBuffer(); }
	CMemBuffer_Long* GetLSpyMemBuffer()       {   return m_pLSpyMemBuffer;       }
	long* GetLRecordMemBuffer2()              {   return m_pLRecordMemBuffer == NULL  ? NULL : m_pLRecordMemBuffer->GetBuffer();  }
	CMemBuffer_Long* GetLRecordMemBuffer()    {   return m_pLRecordMemBuffer;    }
#endif
	
	long GetRecordDataLength()
	{
		if (m_pRecordMemBuffer != NULL)
		{
			return m_pRecordMemBuffer->GetDataLength();
		}

		if (m_pLRecordMemBuffer != NULL)
		{
			return m_pLRecordMemBuffer->GetDataLength();
		}

		return -1;
	}
	
	CExBaseObject* FindByBufferID(const CString &pszBufferID)
	{
		if (m_pSpyMemBuffer != NULL)
		{
			if (_stricmp(pszBufferID.GetString(), m_pSpyMemBuffer->m_strBufferID.GetString()) == 0)
			{
				return m_pSpyMemBuffer;
			}
		}
		
		if (m_pRecordMemBuffer != NULL)
		{
			if (_stricmp(pszBufferID.GetString(), m_pRecordMemBuffer->m_strBufferID.GetString()) == 0)
			{
				return m_pRecordMemBuffer;
			}
		}
		
		if (m_pLSpyMemBuffer != NULL)
		{
			if (_stricmp(pszBufferID.GetString(), m_pLSpyMemBuffer->m_strBufferID.GetString()) == 0)
			{
				return m_pLSpyMemBuffer;
			}
		}
		
		if (m_pLRecordMemBuffer != NULL)
		{
			if (_stricmp(pszBufferID.GetString(), m_pLRecordMemBuffer->m_strBufferID.GetString()) == 0)
			{
				return m_pLRecordMemBuffer;
			}
		}
		
		return NULL;
	}

	void BuildComplexBufferScript()
	{
		if (m_pLSpyMemBuffer != NULL)
		{
			if (m_pLSpyMemBuffer->m_pScript != NULL)
			{
				m_pLSpyMemBuffer->m_pScript->BuildExpression();
			}
		}
	}
	void BuildExpNodeCoef()
	{
		if (m_pLSpyMemBuffer != NULL)
		{
			if (m_pLSpyMemBuffer->m_pScript != NULL)
			{
				m_pLSpyMemBuffer->m_pScript->BuildExpNodeCoef();
			}
		}
	}
	
	void SetRtChTypeNormal()     {    m_nChannelType = RTCH_TYPE_NORMAL;                }
	void SetRtChTypeComplex()    {    m_nChannelType = RTCH_TYPE_COMPLEX;               }
	void SetRtChTypeGPS()        {    m_nChannelType = RTCH_TYPE_GPS;                   }
	BOOL IsRtChTypeNormal()      {    return (m_nChannelType == RTCH_TYPE_NORMAL);      }
	BOOL IsRtChTypeComplex()     {    return (m_nChannelType == RTCH_TYPE_COMPLEX);     }
	BOOL IsRtChTypeGPS()         {    return (m_nChannelType == RTCH_TYPE_GPS);         }

private:
	CMemBufferInterface   *m_pRecordMemBuffer;
	CMemBufferInterface   *m_pSpyMemBuffer;
	
#ifdef COMPLEXVARIABLE_USE_FLOAT
	CMemBuffer_Float     *m_pLRecordMemBuffer;
	CComplexBuffer_Float *m_pLSpyMemBuffer;
#else
	CMemBuffer_Long     *m_pLRecordMemBuffer;
	CComplexBuffer_Long *m_pLSpyMemBuffer;
#endif

	long m_nSpyMemBufferCopyBeginPos;
	long m_nChannelType;
	
	BOOL m_bUseRecordBuffer;
	BOOL m_bUseSpyBuffer;

public:
	void SetUseRecordBuffer(BOOL bUse = TRUE)  {     m_bUseRecordBuffer = bUse;   }
	void SetUseSpyBuffer(BOOL bUse = TRUE)     {     m_bUseSpyBuffer = bUse;      }
	BOOL IsUseRecordBuffer()                   {     return m_bUseRecordBuffer;   }
	BOOL IsUseSpyBuffer()                      {     return m_bUseSpyBuffer;      }
	void SetChIndex(UINT &nChIndex);
};

#endif // !defined(AFX_RTMEMBUFFERCHANNEL_H__C4421880_18FD_4BD9_8084_BEECBF3BA868__INCLUDED_)
