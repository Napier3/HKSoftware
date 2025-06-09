// ParaSort.h: interface for the CParaSortObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ParaSORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_)
#define AFX_ParaSORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DrawAnalogVariable.h"
#include "DrawBaseList.h"

class CParaSortObject  
{
public:
	CDrawAnalogVariable* m_pDrawVaraible;
	CRect m_rcPara;
	CRect m_rcClip;
	
public:
	virtual void SetParaRect(const CRect &rcPara)					{	m_rcPara = rcPara;								}
	virtual BOOL IsParaSortObject()									 {	return TRUE;									}
	CParaSortObject(CDrawAnalogVariable* pVariable);

public:
	CParaSortObject();
	virtual ~CParaSortObject();
};


class CParaSortGroup: public CParaSortObject, public CTLinkList<CParaSortObject> 
{
public:
	virtual void AddToTail(CParaSortGroup *pGroup);		
	virtual void AddToTail(CParaSortObject *pData);	
	
	void CalParaGroupRect();
	void AdjustGroupRectByClip(const CRect &rcClip);
	void AdjustVariablesParaRect();

public:
	CParaSortGroup();
	virtual ~CParaSortGroup();
};


class CParaSortMngr: public CParaSortGroup
{
public:
	CParaSortMngr(CDrawBaseList *pDrawVariables, const CRect &rcClip );

public:
	CParaSortMngr();
	virtual ~CParaSortMngr();

private:
	BOOL IsParaRectIntersect(CParaSortObject *p1, CParaSortObject *p2);
	BOOL SortByParaRect();
	BOOL SortByParaRect(POS posFirst);
	CParaSortGroup* CreateGroup(CParaSortObject* pFirst,CParaSortObject* pCurr);
	CRect  m_rcClip;
};

#endif // !defined(AFX_ParaSORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_)
