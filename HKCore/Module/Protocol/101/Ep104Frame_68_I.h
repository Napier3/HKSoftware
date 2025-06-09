//Ep104Frame_68_I.h  
#ifndef _Ep104Frame_68_I_H__
#define _Ep104Frame_68_I_H__

#include "EpGlobalDefine_101.h"
#include "..\ProtocolBase\EpFrameBase.h"

class CEp104Frame_68_I : public CEpFrameBase
{
public:
	CEp104Frame_68_I(void);
	~CEp104Frame_68_I(void);
	
//  Ù–‘
public:


public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_104_TFRAME_68_I;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep104Frame_68_I_H__