// EpTimer.h: interface for the CEpTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPTIMER_H__)
#define _EPTIMER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"

class CEpNode;

class CEpTimer : public CExBaseObject  
{
public:
	CEpTimer();
	virtual ~CEpTimer();

public:
	long m_nType;
	long m_nTimeLong;
	CEpNode* m_pJumpToNode;

public:
	//基本方法
	virtual void Init()	{}
	virtual UINT GetClassID()		{ return EPCLASSID_TIMER; }

	//编辑
	virtual long IsEqual(CExBaseObject* pObj) {	return 0;}
	virtual long Copy(CExBaseObject* pDesObj) {	return 0;}
	virtual CExBaseObject* Clone()			  {	return NULL;  }

//////////////////////////////////////////////////////////////////////////
//timer时钟执行代码
private:
	DWORD m_dwTimerBegin;
	BOOL m_bTimerBegin;

public:
	void BeginTimer(DWORD dwCurrTick);
	void ResetTimer(DWORD dwCurrTick);
	void KillTimer();
	BOOL IsTimeOut(DWORD dwCurrTick);

};

#endif // !defined(_EPTIMER_H__)
