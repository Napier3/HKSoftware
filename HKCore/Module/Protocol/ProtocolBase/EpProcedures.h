// EpProcedures.h: interface for the CEpProcedures class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROCEDURES_H__)
#define _EPPROCEDURES_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpProcedure.h"


class CEpProcedures : public CExBaseList  
{
public:
	CEpProcedures();
	virtual ~CEpProcedures();

public:
	//��������
	virtual void Init() {}
	virtual UINT GetClassID()		{ return EPCLASSID_PROCEDURES; }

	//�༭
	virtual long IsEqual(CExBaseObject* pObj)	{ return 0;}
	virtual long Copy(CExBaseObject* pDesObj)	{ return 0;}
	virtual CExBaseObject* Clone()				{ return NULL;}
};

#endif // !defined(_EPPROCEDURES_H__)
