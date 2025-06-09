// EpFrameBases.h: interface for the CEpFrameBases class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPFRAMEBASES_H__)
#define _EPFRAMEBASES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"

//���Ĺ������
#define  CLASSID_PACKAGES_BASECLASS			(CLASSID_LISTCLASS + 0x00010000)//��Լ֡�������


class CEpFrameBases : public CExBaseList  
{
public:
	CEpFrameBases();
	virtual ~CEpFrameBases();

public:
	//��������
	virtual void Init() {}
	virtual UINT GetClassID() {	return EPCLASSID_FRAMES;	}

	//�༭
	virtual long IsEqual(CExBaseObject* pObj)	{ return 0; }
	virtual long Copy(CExBaseObject* pDesObj)	{ return 0; }
	virtual CBaseObject* Clone()	{ return NULL; }

	CEpFrameBase* FindByClassID(UINT nClassID);
	CEpFrameBase* FindByOwnClassID(UINT nClassID);
};

#endif // !defined(_EPFRAMEBASES_H__)
