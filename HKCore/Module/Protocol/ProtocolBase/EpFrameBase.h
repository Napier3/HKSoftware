// EpFrameBase.h: interface for the CEpFrameBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPFRAMEBASE_H__)
#define _EPFRAMEBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\EpGlobalDefine.h"
#include <math.h>
#include "..\MemBuffer\CycleMemBuffer.h"

#include "..\ByteBlock\EpByteBlocks.h"
#include "..\ByteBlock\EpByteBlockControl.h"
#include "..\ByteBlock\EpByteBlockCOT.h"
#include "..\ByteBlock\EpByteBlockData.h"
#include "..\ByteBlock\EpByteBlockEnd.h"
#include "..\ByteBlock\EpByteBlockLength.h"
#include "..\ByteBlock\EpByteBlockStart.h"
#include "..\ByteBlock\EpByteBlockType.h"
#include "..\ByteBlock\EpByteBlockVSQ.h"
#include "..\ByteBlock\EpByteBlockSIQ.h"

#include "..\CmmChannel\EpCmmGlobalDefine.h"

class CEpCmmChannel;

//报文基类，制造、解析、匹配报文
class CEpFrameBase : public CExBaseList  
{
public:
	CEpFrameBase();
	virtual ~CEpFrameBase();

//属性
public:
	SYSTEMTIME m_tm;//规约报文发送或者接受的时间
	DWORD m_dwTickCount;
	DWORD m_nBeginTime;
	long m_nTimeoutLong;
	long m_nLength;
	CExBaseObject *m_pFrameGroup;
	DWORD m_dwState;
	CCycleMemBuffer *m_pBuffer;
	DWORD m_dwNetCmmMode;
	BOOL m_bLock;
	BOOL m_bUsed;
	CExBaseObject *m_pChannel;
	CExBaseObject *m_pEpProcedure;
	long m_nPkgNum;
	CWinThread *m_pEngineThread;
//	DWORD m_dwRecord;
	CString m_strChCmmMode;

public:
	void CopyBuffer(BYTE *pRcvBuffer,long nLen);
	void GetFrameBufferPos(PEPBUFFERPOS pBufferPos);
	void FreeBuffer();

	//执行
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	//基本方法
	virtual UINT GetClassID() {        return EPCLASSID_FRAME;    }
	virtual BOOL IsParseFrame();
	virtual BOOL IsProduceFrame();
	
	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);

	//解析
	//字节块的解析  具体的解析在派生类中执行解析
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)		{  return 0;  }

	//字节块的匹配  主要用于匹配解析帧，返回值：0-匹配失败，1-匹配成功
	virtual BOOL Match(PEPBUFFERPOS pBufferPos)     {  return FALSE;  }

	//字节块的制造,返回报文长度
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos)    {  return 0;  }

	////获取校验和，nLen报文总长度
	BYTE GetCheckSum(BYTE *byBuffer,int nLen);

	void Lock(BOOL bLock=TRUE)	{	m_bLock = bLock;	}
	BOOL HasSended()			{	return (m_dwState == EPFRAME_STATE_SEND);	}
	BOOL IsLock()				{	return m_bLock;		}
	void InitSend(CExBaseObject *pEpProcedure, CEpCmmChannel *pChannel);
	void SetUsed(BOOL bUsed=TRUE)	{	m_bUsed = bUsed;	}
	BOOL IsUsed()					{	return m_bUsed;		}
	virtual void Send();
	BOOL IsTimeout();
	void SetBeginTime();
	void SetChannel(CEpCmmChannel *pChannel);

	virtual void AppendToDetail(CExBaseList *pList);
	void InitFrameNum();

public:
	virtual CEpByteBlock* AddNewByteBlock(CExBaseList *pDetailList, const CString &strID, long nLen, long nIndex);
	//virtual CEpByteBlockData* AddNewDataByteBlock(const CString &strID, long nLen, long nIndex);
	virtual void SetSendState(DWORD dwState)	{	m_dwState = dwState;	}
	
	void InitTime();
	void LogAndRecordProtocol();

	BOOL IsChModeMultiCast()	{	return m_dwNetCmmMode = ID_NET_CMM_MODE_MULTICAST;	}
	BOOL IsChModeToPoint()		{	return m_dwNetCmmMode = ID_NET_CMM_MODE_TOPOINT;	}
	BOOL IsChModeBroadCast()	{	return m_dwNetCmmMode = ID_NET_CMM_MODE_BROADCAST;	}

};

class CEpFrameDetail : public CEpFrameBase
{
public:
	CEpFrameDetail();
	virtual ~CEpFrameDetail();

public:
	DWORD m_dwFrameClassID;

public:
	void InitDetail(CEpFrameBase *pFrame);

public:
	virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, DWORD dwParam=0);

};

CEpFrameBase* Ep_FindFrameByID(DWORD dwClassID, CExBaseObject *pCurr);

#endif // !defined(_EPFRAMEBASE_H__)
