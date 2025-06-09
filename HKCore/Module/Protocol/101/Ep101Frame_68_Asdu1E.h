//Ep101Frame_68_Asdu1E.h  
#ifndef _Ep101Frame_68_Asdu1E_H__
#define _Ep101Frame_68_Asdu1E_H__

#include "Ep101Frame_68.h"
#include "Ep101Frame_68_AsduBase.h"

class CEp101Frame_68_Asdu1E : public CEp101Frame_68_AsduBase
{
public:
	CEp101Frame_68_Asdu1E(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CEp101Frame_68_Asdu1E();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_FRAME_68_ASDU1E;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep101Frame_68_Asdu1E_H__