//Ep101Frame_68_Asdu00.h  
#ifndef _Ep101Frame_68_Asdu00_H__
#define _Ep101Frame_68_Asdu00_H__

#include "Ep101Frame_68.h"
#include "Ep101Frame_68_AsduBase.h"

class CEp101Frame_68_Asdu00 : public CEp101Frame_68_AsduBase
{
public:
	CEp101Frame_68_Asdu00(CEpFrameBase *pHead, CEpFrameBase *pTail);
	virtual ~CEp101Frame_68_Asdu00();

public:

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_TFRAME_EMPTY;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep101Frame_68_Asdu00_H__