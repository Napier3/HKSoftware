//Ep104Frame_68_S.h  
#ifndef _Ep104Frame_68_S_H__
#define _Ep104Frame_68_S_H__

#include "EpGlobalDefine_101.h"
#include "..\ProtocolBase\EpFrameBase.h"

class CEp104Frame_68_S : public CEpFrameBase
{
public:
	CEp104Frame_68_S(void);
	~CEp104Frame_68_S(void);
	
//  Ù–‘
public:


public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_104_TFRAME_68_S;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep104Frame_68_S_H__