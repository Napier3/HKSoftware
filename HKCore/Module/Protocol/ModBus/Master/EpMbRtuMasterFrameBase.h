//EpMbRtuMasterFrameBase.h  
#ifndef _EpMbRtuMasterFrameBase_H__
#define _EpMbRtuMasterFrameBase_H__

#include "..\..\ProtocolBase\EpFrameBase.h"

class CEpMbRtuMasterFrameBase : public CEpFrameBase
{
public:
	CEpMbRtuMasterFrameBase();
	virtual ~CEpMbRtuMasterFrameBase();

// Ù–‘
public:
	CEpByteBlockType *m_pType;

public:
	virtual DWORD OnInitScript() { return 0;}
	virtual DWORD OnEndScript()	{ return 0;}

	virtual void Init()	{}
	virtual UINT GetClassID() {        return EPCLASSID_101_TFRAME_10;    }

	virtual long IsEqual(CExBaseObject* pObj) { return 0; }
	virtual long Copy(CExBaseObject* pDesObj) { return 0; }
	virtual CExBaseObject* Clone()  { return NULL; }

	virtual DWORD Parse(PEPBUFFERPOS pBufferPos);
	virtual BOOL Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);
	
protected:
	virtual DWORD ParseCode(PEPBUFFERPOS pBufferPos);
	virtual DWORD ProduceCode(PEPBUFFERPOS pBufferPos);

	CEpByteBlockType* AddNewTypeByteBlock(long nLen, long nIndex, BYTE byteValue);
};


#endif //_EpMbRtuMasterFrameBase_H__