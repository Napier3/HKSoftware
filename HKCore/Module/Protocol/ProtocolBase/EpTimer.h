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
	//��������
	virtual void Init()	{}
	virtual UINT GetClassID()		{ return EPCLASSID_TIMER; }

	//�༭
	virtual long IsEqual(CExBaseObject* pObj) {	return 0;}
	virtual long Copy(CExBaseObject* pDesObj) {	return 0;}
	virtual CExBaseObject* Clone()			  {	return NULL;  }

//////////////////////////////////////////////////////////////////////////
//timerʱ��ִ�д���
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
