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

//���Ļ��࣬���졢������ƥ�䱨��
class CEpFrameGroup : public CExBaseList  
{
public:
	CEpFrameGroup();
	virtual ~CEpFrameGroup();

//����
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

	//����
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
