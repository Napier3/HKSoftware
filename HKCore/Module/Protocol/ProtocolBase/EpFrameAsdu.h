// EpFrameAsdu.h: interface for the CEpFrameAsdu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPFRAMEASDU_H__)
#define _EPFRAMEASDU_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"
#include "..\ByteBlock\EpByteBlockDataSet.h"
#include "..\ByteBlock\EpByteBlockTime.h"
#include "..\ByteBlock\EpByteBlockQDS.h"
#include "..\ByteBlock\EpByteBlockFloat.h"
#include "..\ByteBlock\EpByteBlockQOS.h"
#include "..\ByteBlock\EpByteBlockQOI.h"

//报文基类，制造、解析、匹配报文
class CEpFrameAsdu : public CEpFrameBase
{
public:
	CEpFrameAsdu(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CEpFrameAsdu();

	void SetHeadAndTail(CEpFrameBase *pHead, CEpFrameBase *pTail);

private:
	CEpFrameAsdu(){}

//属性
public:
	CEpFrameBase *m_pHead;  //报文头
	CEpFrameBase *m_pTail;  //报文尾

	CEpByteBlockDataSet *m_pBbDataSet;

public:
	virtual void AppendToDetail(CExBaseList *pList);

	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual CEpByteBlockDataSet* InitBbDataSet(CExBaseList *pDetailList);
	virtual void InitBbDataSet()		{	m_pBbDataSet = NULL;	}
	CEpByteBlockData* AddDataToDataSet(long nIndex);

	virtual CEpByteBlock* AddNewByteBlockToDataSet(const CString &strID, long nLen, long nIndex);
	virtual CEpByteBlock* AddNewAddrByteBlockToDataSet(const CString &strID, long nLen, long nIndex);
	virtual CEpByteBlock* AddNewTimeByteBlockToDataSet(const CString &strID, long nLen, long nIndex, EPTIME64 &tm);
	virtual CEpByteBlock* AddNewQDSByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail);
	virtual CEpByteBlock* AddNewFloatByteBlockToDataSet(const CString &strID, long nLen, long nIndex, float fValue, BOOL bAddDetail);
	virtual CEpByteBlock* AddNewQOSByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail);
	virtual CEpByteBlock* AddNewQOIByteBlockToDataSet(const CString &strID, long nLen, long nIndex, BYTE byteValue, BOOL bAddDetail);
};

#endif // !defined(_EPFRAMEASDU_H__)
