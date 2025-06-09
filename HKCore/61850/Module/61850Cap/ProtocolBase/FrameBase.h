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

//属性
public:
	__int64 m_tm;//规约报文发送或者接受的时间
	long m_nLength;
	CFrameMemBuffer *m_pBuffer;
	long m_nChCount;
	long m_nMaxChCount;

public:
	void CopyBuffer(BYTE *pRcvBuffer,long nLen);
	void GetFrameBufferPos(PEPBUFFERPOS pBufferPos);
	void FreeBuffer();

	//执行
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	//基本方法
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAME;    }
	virtual BOOL IsParseFrame();
	virtual BOOL IsProduceFrame();
	
	//编辑
	virtual BOOL IsEqual(CExBaseObject* pObj);
	virtual BOOL Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone()	{ return NULL; }

	//解析
	//字节块的解析  具体的解析在派生类中执行解析
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList)		{  return 0;  }
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos)		{  return 0;  }

	//字节块的匹配  主要用于匹配解析帧，返回值：0-匹配失败，1-匹配成功
	virtual BOOL Match(PEPBUFFERPOS pBufferPos)     {  return FALSE;  }

	//字节块的制造,返回报文长度
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos)    {  return 0;  }

	////获取校验和，nLen报文总长度
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
