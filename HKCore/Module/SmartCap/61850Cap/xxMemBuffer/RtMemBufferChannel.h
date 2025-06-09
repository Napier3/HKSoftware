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
	
#define  RTCH_TYPE_NORMAL    0 //ģ��Ϳ��صĵ�ͨ��
#define  RTCH_TYPE_COMPLEX   1
#define  RTCH_TYPE_GPS       2
	
public:
	//��ʼ�����
	void Init(const CString &strChannelID, BOOL bUseRecordBuf, const CString &strRecordBufID, BOOL bUseSpyBuf, const CString &strSpyBufID);
	void Init();//��������������
	void SetMemBufferLength(long nRecordBufferLen, long nSpyMemBufferLen);
	void SetSpyMemBufferLength(long nBufferLen);
	void SetRecordMemBufferLength(long nBufferLen);
	void InitDataPos()	;//��ʼ����������
	//�ͷŻ���
	void FreeRecordBuffer();
	void FreeSpyBuffer();	


	//�������
	void AttachSpyMemBuffer(CMemBuffer_UnsignedShort* pMemBuffer);
	void AttachRecordMemBuffer(CMemBuffer_UnsignedShort* pMemBuffer);

	//��û���,��2��Ϊ���ݻ������,���ӵ�Ϊ����������
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
