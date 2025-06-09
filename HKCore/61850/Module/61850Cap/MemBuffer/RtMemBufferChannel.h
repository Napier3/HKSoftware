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
#include "MemBuffer_UnsignedShort.h"

class CRtMemBufferChannel  : public CStBaseObject
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


	//缓存关联
	void AttachSpyMemBuffer(CMemBuffer_UnsignedShort* pMemBuffer);
	void AttachRecordMemBuffer(CMemBuffer_UnsignedShort* pMemBuffer);

	//获得缓存,加2的为数据缓存对象,不加的为缓存管理对象
	unsigned short* GetSpyMemBuffer2()        {   return m_pSpyMemBuffer == NULL  ? NULL : m_pSpyMemBuffer->GetBuffer();  }
	CMemBuffer_UnsignedShort* GetSpyMemBuffer()      {   return m_pSpyMemBuffer;        }
	unsigned short* GetRecordMemBuffer2()     {   return m_pRecordMemBuffer == NULL   ? NULL : m_pRecordMemBuffer->GetBuffer();   }
	CMemBuffer_UnsignedShort* GetRecordMemBuffer()   {   return m_pRecordMemBuffer;     }


	void SetRtChTypeNormal()     {    m_nChannelType = RTCH_TYPE_NORMAL;                }
	void SetRtChTypeComplex()    {    m_nChannelType = RTCH_TYPE_COMPLEX;               }
	void SetRtChTypeGPS()        {    m_nChannelType = RTCH_TYPE_GPS;                   }
	BOOL IsRtChTypeNormal()      {    return (m_nChannelType == RTCH_TYPE_NORMAL);      }
	BOOL IsRtChTypeComplex()     {    return (m_nChannelType == RTCH_TYPE_COMPLEX);     }
	BOOL IsRtChTypeGPS()         {    return (m_nChannelType == RTCH_TYPE_GPS);         }

private:
	CMemBuffer_UnsignedShort   *m_pRecordMemBuffer;
	CMemBuffer_UnsignedShort   *m_pSpyMemBuffer;
	
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
