// FrameBaseList.h: interface for the CFrameBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_FrameBaseList_H__)
#define _FrameBaseList_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameBase.h"


class CFrameBaseList : public CExBaseList  
{
public:
	CFrameBaseList();
	virtual ~CFrameBaseList();

public:
	//基本方法
	virtual void Init() {}
	virtual UINT GetClassID() {	return STPROTOCOLCLASSID_FRAMELIST;	}

	//编辑
	virtual BOOL IsEqual(CExBaseObject* pObj)	{ return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj)	{ return 0; }
	virtual CExBaseObject* Clone()	{ return NULL; }

	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos);
	virtual CFrameBase* Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);

	CFrameBase* FindByClassID(UINT nClassID);
	CFrameBase* FindByOwnClassID(UINT nClassID);
};

#endif // !defined(_FrameBaseList_H__)
