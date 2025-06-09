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
    virtual BOOL IsEqual(CExBaseObject* pObj)
    {
#ifdef _PSX_IDE_QT_
        (void)pObj;
#endif
        return 0;
    }

    virtual BOOL Copy(CExBaseObject* pDesObj)
    {
#ifdef _PSX_IDE_QT_
        (void)pDesObj;
#endif
        return 0;
    }

	virtual CExBaseObject* Clone()	{ return NULL; }

	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual CFrameBase* Parse(PEPBUFFERPOS pBufferPos);
	//zhouhj 2023.11.14 解析FT3报文
	virtual CFrameBase* Parse_60044(PEPBUFFERPOS pBufferPos);
	//xuzt 2023.11.14 解析开入量报文
	virtual CFrameBase* Parse_Binary(PEPBUFFERPOS pBufferPos);
	virtual CFrameBase* Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);

	CFrameBase* FindByClassID(UINT nClassID);
	CFrameBase* FindByOwnClassID(UINT nClassID);
};

#endif // !defined(_FrameBaseList_H__)
