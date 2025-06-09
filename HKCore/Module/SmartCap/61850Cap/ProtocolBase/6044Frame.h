//6044Frame.h  
#ifndef _6044Frame_H__
#define _6044Frame_H__

#include "SmvFrameBase.h"

class C6044Frame : public CSmvFrameBase
{
public:
	C6044Frame();
	virtual ~C6044Frame();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return STPROTOCOLCLASSID_FRAME6044;    }

	virtual BOOL IsEqual(CExBaseObject* pObj) { return 0; }
	virtual BOOL Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual long ParseOwn(PEPBUFFERPOS pBufferPos, CFrameDetail *pDetailList);
	virtual DWORD ParseInfor(PEPBUFFERPOS pBufferPos, CExBaseObject *pDevice);
	virtual long ParseOwn(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
};


#endif //_6044Frame_H__