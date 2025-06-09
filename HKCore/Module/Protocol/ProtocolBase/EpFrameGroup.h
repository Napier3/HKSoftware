// EpFrameGroup.h: interface for the CEpFrameGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPFRAMEGROUP_H__)
#define _EPFRAMEGROUP_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"
#include "..\BaseClass\ExBaseList.h"
#include "EpFrameAsdu.h"

//报文基类，制造、解析、匹配报文
class CEpFrameGroup : public CExBaseList  
{
public:
	CEpFrameGroup();
	virtual ~CEpFrameGroup();

//属性
public:

public:
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual UINT GetClassID() {        return EPCLASSID_FRAME_GROUP;    }	
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);
	virtual CEpFrameBase* Match(PEPBUFFERPOS pBufferPos);
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos);

	virtual void AddFrameAsdu(CEpFrameAsdu *pAsdu);
};

class CEpFrameGroups : public CExBaseList  
{
public:
	CEpFrameGroups();
	virtual ~CEpFrameGroups();

	//属性
public:

public:
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	virtual UINT GetClassID() {        return EPCLASSID_FRAME_GROUPS;    }	
	virtual CEpFrameBase* Match(PEPBUFFERPOS pBufferPos);

	virtual CExBaseObject* FindByClassID(DWORD dwClassID);
}; 

#endif // !defined(_EPFRAMEGROUP_H__)
