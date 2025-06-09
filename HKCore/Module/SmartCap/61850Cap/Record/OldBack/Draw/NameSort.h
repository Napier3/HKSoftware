// NameSort.h: interface for the CNameSortObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NAMESORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_)
#define AFX_NAMESORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DrawAnalogVariable.h"
#include "DrawBinaryVariable.h"
#include "DrawBaseList.h"
#define Name_Sort 0
#define Para_Sort 1

class CNameSortObject  
{
public:
	CDrawVariable* m_pDrawVaraible;
	CRect m_rcName;
	CRect m_rcClip;
	UINT m_nType;
	
public:
	virtual void SetNameRect(const CRect &rcName)					{	m_rcName = rcName;								}
	virtual BOOL IsNameSortObject()									 {	return TRUE;									}
	CNameSortObject(CDrawVariable* pVariable ,UINT nType = Name_Sort);

public:
	CNameSortObject();
	virtual ~CNameSortObject();
};

class CNameSortGroup: public CNameSortObject, public CTLinkList<CNameSortObject> 
{
public:
	CNameSortGroup();
	virtual ~CNameSortGroup();
	
	virtual BOOL IsNameSortObject()									{	return FALSE;									}
	virtual void AddToTail(CNameSortGroup *pGroup);		
	virtual void AddToTail(CNameSortObject *pData);	

	void CalNameGroupRect();
	void AdjustGroupRectByClip(const CRect &rcClip);
	void AdjustVariablesNameRect();
};


class CNameSortMngr: public CNameSortGroup
{
public:
	CNameSortMngr(CDrawBaseList *pDrawVariables, const CRect &rcClip ,UINT nType = Name_Sort);

public:
	CNameSortMngr();
	virtual ~CNameSortMngr();

private:
	BOOL IsNameRectIntersect(CNameSortObject *p1, CNameSortObject *p2);
	BOOL SortByNameRect();
	BOOL SortByNameRect(POS posFirst);
	CNameSortGroup* CreateGroup(CNameSortObject* pFirst,CNameSortObject* pCurr);
	CRect  m_rcClip;
};

#endif // !defined(AFX_NAMESORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_)
