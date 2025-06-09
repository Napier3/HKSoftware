// 61850ParseFrameList.h: interface for the C61850ParseFrameList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_61850ParseFrameList_H__)
#define _61850ParseFrameList_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameBaseList.h"
#include "91Frame.h"
#include "92Frame.h"
#include "GooseFrame.h"
#include "6044Frame.h"

class C61850ParseFrameList : public CFrameBaseList  
{
public:
	C61850ParseFrameList();
	virtual ~C61850ParseFrameList();

	C6044Frame* Get6044Frame();

protected:
	C91Frame *m_p91Frame;
	C92Frame *m_p92Frame;
	CStGooseFrame *m_pGooseFrame;
	C6044Frame *m_p6044Frame;

public:
	//基本方法
	virtual void Init() {}
	virtual UINT GetClassID() {	return STPROTOCOLCLASSID_FRAMELIST;	}

	//编辑
	virtual BOOL IsEqual(CExBaseObject* pObj)	{ return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj)	{ return 0; }
	virtual CExBaseObject* Clone()	{ return NULL; }

	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual CFrameBase* ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos);

	//zhouhj 2023.11.14 解析FT3报文
	virtual CFrameBase* Parse_60044(PEPBUFFERPOS pBufferPos);

	//virtual CFrameBase* Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};

long match_61850(BYTE *pBuffer, long nLen);


#endif // !defined(_61850ParseFrameList_H__)
