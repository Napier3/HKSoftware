//92Frame.h  
#ifndef _92Frame_H__
#define _92Frame_H__

#include "SmvFrameBase.h"

class C92Frame : public CSmvFrameBase
{
public:
	C92Frame();
	virtual ~C92Frame();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAME92;    }

	virtual BOOL IsEqual(CExBaseObject* pObj) { return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual long ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual long ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
};


#endif //_92Frame_H__