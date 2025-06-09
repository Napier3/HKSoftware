//StGooseFrame.h  
#ifndef _StGooseFrame_H__
#define _StGooseFrame_H__

#include "61850FrameBase.h"

class CStGooseFrame : public C61850FrameBase
{
public:
	CStGooseFrame();
	virtual ~CStGooseFrame();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAMEGS;    }

	virtual BOOL IsEqual(CExBaseObject* pObj) { return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual long ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual long ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
};


#endif //_StGooseFrame_H__