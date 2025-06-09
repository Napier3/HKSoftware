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

typedef CTLinkList<CNameSortObject> CNameSortObjectList;

class CNameSortGroup: public CNameSortObject, public CNameSortObjectList
{
public:
	virtual BOOL IsNameSortObject()									{	return FALSE;									}
// 	virtual long GetCount()											{   return GetCount();					}
// 	virtual CNameSortObject* GetAt(int nIndex)						{   return GetAt(nIndex);				}
// 	
// 	virtual void* InsertBefore(POS pos , CNameSortObject *pData)	{   return InsertBefore(pos, pData);    }
// 	virtual void* InsertAfter(POS pos , CNameSortObject *pData)	{   return InsertAfter(pos, pData);     }
// 	virtual void RemoveAll()										{   RemoveAll();						}
// 	virtual CNameSortObject* RemoveAt(int nIndex)					{   return RemoveAt(nIndex);			}
// 	virtual CNameSortObject* RemoveAt(POS pos )					{   return RemoveAt(pos);				}
// 	virtual void DeleteAll()										{   DeleteAll();						}
// 	virtual void DeleteAt(int nIndex)								{   DeleteAt(nIndex);					}
// 	virtual void DeleteHead()										{   DeleteHead();						}
// 	virtual void DeleteTail()										{   DeleteTail();						}
// 	virtual CNameSortObject* GetHead()								{   return GetHead();					}
// 	virtual CNameSortObject* GetTail()								{   return GetTail();					}
// 	virtual void* GetHeadPosition()									{   return GetHeadPosition();			}
// 	virtual void* GetTailPosition()									{   return GetTailPosition();			}
// 	virtual CNameSortObject* GetNext(void* &pos)					{   return GetNext(pos);				}
// 	virtual CNameSortObject* GetAt(POS pos )						{   return GetAt(pos);					}
	virtual void AddTail(CNameSortGroup *pGroup);		
	virtual void AddTail(CNameSortObject *pData);	
	
	void CalNameGroupRect();
	void AdjustGroupRectByClip(const CRect &rcClip);
	void AdjustVariablesNameRect();
public:
	CNameSortGroup();
	virtual ~CNameSortGroup();
};


class CNameSortMngr: public CNameSortGroup
{
public:
	CNameSortMngr(CXDrawElements *pDrawVariables, const CRect &rcClip ,UINT nType = Name_Sort);

public:
	CNameSortMngr();
	virtual ~CNameSortMngr();

private:
	BOOL IsNameRectIntersect(CNameSortObject *p1, CNameSortObject *p2);
	BOOL SortByNameRect();
	BOOL SortByNameRect(POS  posFirst);
	CNameSortGroup* CreateGroup(CNameSortObject* pFirst,CNameSortObject* pCurr);
	CRect  m_rcClip;
};

#endif // !defined(AFX_NAMESORT_H__A56B852F_49EF_4B82_B60B_343106BD9320__INCLUDED_)
