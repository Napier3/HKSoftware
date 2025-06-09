//BinRcdFrame.h
#ifndef _BinRcdFrame_H__
#define _BinRcdFrame_H__

#include "61850FrameBase.h"

class CBinRcdFrame : public C61850FrameBase
{
public:
    CBinRcdFrame();
    virtual ~CBinRcdFrame();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAMEBINARY;    }

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
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual long ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual long ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
};


#endif //_BinRcdFrame_H__
