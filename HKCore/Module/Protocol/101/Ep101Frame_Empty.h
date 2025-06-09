//CEp101Frame_68_Empty.h  
#ifndef _Ep101Frame_Empty_H__
#define _Ep101Frame_Empty_H__

#include "EpFrameBase.h"

class CEp101Frame_68_Empty : public CEpFrameBase
{
public:
	CCEp101Frame_68_Empty(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CCEp101Frame_68_Empty();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_TFRAME_EMPTY;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_CEp101Frame_68_Empty_H__