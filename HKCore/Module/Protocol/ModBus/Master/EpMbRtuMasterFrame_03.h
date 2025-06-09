//EpMbRtuMasterFrame_03.h  
#ifndef _EpMbRtuMasterFrame_03_H__
#define _EpMbRtuMasterFrame_03_H__

#include "EpMbRtuMasterFrameBase.h"

class CEpMbRtuMasterFrame_03 : public CEpFrameBase
{
public:
	CEpMbRtuMasterFrame_03();
	virtual ~CEpMbRtuMasterFrame_03();

// Ù–‘
public:
	
public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_MBRTUMASTER_TFRAME_03;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	
protected:
	virtual DWORD ParseCode(PEPBUFFERPOS pBufferPos);
	virtual DWORD ProduceCode(PEPBUFFERPOS pBufferPos);
};


#endif //_EpMbRtuMasterFrame_03_H__