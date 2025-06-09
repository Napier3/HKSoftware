// EpTimers.h: interface for the CEpTimers class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPTIMERS_H__)
#define _EPTIMERS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpTimer.h"


class CEpTimers : public CExBaseList  
{
public:
	CEpTimers();
	virtual ~CEpTimers();

public:


public:
	//基本方法
	virtual void Init() {}
	virtual UINT GetClassID()		{ return EPCLASSID_TIMERS; }

	//编辑
	virtual long IsEqual(CExBaseObject* pObj)	{ return 0;}
	virtual long Copy(CExBaseObject* pDesObj)	{ return 0;}
	virtual CExBaseObject* Clone()				{ return NULL;}

public:
	void BeginTimer();
	void ResetTimer();
	void KillTimer();
	CEpNode* RunTimer(DWORD dwCurrTick);
};

#endif // !defined(_EPTIMERS_H__)
