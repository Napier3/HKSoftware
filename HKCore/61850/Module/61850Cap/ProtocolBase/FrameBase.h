// FrameBase.h: interface for the CFrameBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_StFRAMEBASE_H__)
#define _StFRAMEBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "ProtocolGlobalDef.h"
#include "ByteBlock.h"
#include "FrameMemBuffer.h"
#include "FrameDetail.h"

class CFrameBase : public CExBaseList  
{
public:
	CFrameBase();
	virtual ~CFrameBase();

//����
public:
	__int64 m_tm;//��Լ���ķ��ͻ��߽��ܵ�ʱ��
	long m_nLength;
	CFrameMemBuffer *m_pBuffer;
	long m_nChCount;
	long m_nMaxChCount;

public:
	void CopyBuffer(BYTE *pRcvBuffer,long nLen);
	void GetFrameBufferPos(PEPBUFFERPOS pBufferPos);
	void FreeBuffer();

	//ִ��
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	//��������
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAME;    }
	virtual BOOL IsParseFrame();
	virtual BOOL IsProduceFrame();
	
	//�༭
	virtual BOOL IsEqual(CExBaseObject* pObj);
	virtual BOOL Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone()	{ return NULL; }

	//����
	//�ֽڿ�Ľ���  ����Ľ�������������ִ�н���
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)		{  return 0;  }
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos)		{  return 0;  }

	//�ֽڿ��ƥ��  ��Ҫ����ƥ�����֡������ֵ��0-ƥ��ʧ�ܣ�1-ƥ��ɹ�
	virtual BOOL Match(PEPBUFFERPOS pBufferPos)     {  return FALSE;  }

	//�ֽڿ������,���ر��ĳ���
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos)    {  return 0;  }

	////��ȡУ��ͣ�nLen�����ܳ���
	BYTE GetCheckSum(BYTE *byBuffer,int nLen);

	virtual void AppendToDetail(CExBaseList *pList);
	void InitFrameNum();

public:
	virtual CByteBlock* AddNewByteBlock(CFrameDetail *pDetailList, const CString &strID, long nLen, long nIndSt);
	
	void InitTime();
	void LogAndRecordProtocol();

	int  SetChannelCount(int nCount);
	int  GetChannelCount() {return m_nChCount;}

};


inline UINT32 Bytes2UInt(const BYTE* start, UINT32 nLen)
{
	if(nLen==2)
	{
		return UINT32(USHORT((*start)<<8) + BYTE(*(start+1)));
	}
	UINT32 val = 0;
	while (nLen--)
	{	
		val += (*start)<<8*nLen;
		start++;
	}
	return val;
}

#define CheckLengthReturn(nMax, pos, nLen) if(nLen>nMax-pos) {return FALSE;}


#endif // !defined(_StFRAMEBASE_H__)
