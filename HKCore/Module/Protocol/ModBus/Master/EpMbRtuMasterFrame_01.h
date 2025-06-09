//EpMbRtuMasterFrame_01.h  
#ifndef _EpMbRtuMasterFrame_01_H__
#define _EpMbRtuMasterFrame_01_H__

#include "EpMbRtuMasterFrameBase.h"

class CEpMbRtuMasterFrame_01 : public CEpFrameBase
{
public:
	CEpMbRtuMasterFrame_01();
	virtual ~CEpMbRtuMasterFrame_01();

// Ù–‘
public:
	
public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_10;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	
protected:
	virtual DWORD ParseCode(PEPBUFFERPOS pBufferPos);
	virtual DWORD ProduceCode(PEPBUFFERPOS pBufferPos);
};


#endif //_EpMbRtuMasterFrame_01_H__