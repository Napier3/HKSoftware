//91Frame.h  
#ifndef _91Frame_H__
#define _91Frame_H__

#include "SmvFrameBase.h"

class C91Frame : public CSmvFrameBase
{
public:
	C91Frame();
	virtual ~C91Frame();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAME91;    }

	virtual BOOL IsEqual(CExBaseObject* pObj) { return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
};


#endif //_91Frame_H__