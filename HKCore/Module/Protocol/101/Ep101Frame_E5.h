//Ep101Frame_E5.h  
#ifndef _Ep101Frame_E5_H__
#define _Ep101Frame_E5_H__

#include "EpGlobalDefine_101.h"
#include "..\ProtocolBase\EpFrameBase.h"

class CEp101Frame_E5 : public CEpFrameBase
{
public:
	CEp101Frame_E5(void);
	~CEp101Frame_E5(void);
	
//  Ù–‘
public:


public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_E5;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CBaseObject* Clone()  { return NULL; }

	virtual DWORD ParseOwn(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
};


#endif //_Ep101Frame_E5_H__