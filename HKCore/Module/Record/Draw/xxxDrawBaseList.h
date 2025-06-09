// DrawBaseList.h: interface for the CDrawBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_)
#define AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
// #include "..\..\..\MODULE\BASECLASS\LinkList.h"
// #include "..\..\..\MODULE\BASECLASS\BaseList.h"

// typedef CLinkedList<CDrawBase> CDrawBaseObjectList;

class CDrawBaseList  : public CExBaseList
{
public:
// 	virtual long GetCount()											{   return m_listChild.GetCount();					}
// 	virtual CDrawBase* GetAt(int nIndex)							{   return m_listChild.GetAt(nIndex);				}
// 	virtual void* AddTail(CDrawBase *pData)							{   return m_listChild.AddNode(pData);				}
// 	virtual void* AddHead(CDrawBase *pData)							{   return m_listChild.AddHead(pData);				}
// 	virtual void* InsertBefore(void *pos, CDrawBase *pData)			{   return m_listChild.InsertBefore(pos, pData);    }
// 	virtual void* InsertAfter(void *pos, CDrawBase *pData)			{   return m_listChild.InsertAfter(pos, pData);     }
// 	virtual void RemoveAll()										{   m_listChild.RemoveAll();						}
// 	virtual CDrawBase* RemoveAt(int nIndex)							{   return m_listChild.RemoveAt(nIndex);			}
// 	virtual CDrawBase* RemoveAt(void *pos)							{   return m_listChild.RemoveAt(pos);				}
// 	virtual void DeleteAll()										{   m_listChild.DeleteAll();						}
// 	virtual void DeleteAt(int nIndex)								{   m_listChild.DeleteAt(nIndex);					}
// 	virtual void DeleteHead()										{   m_listChild.DeleteHead();						}
// 	virtual void DeleteTail()										{   m_listChild.DeleteTail();						}
// 	virtual CDrawBase* FindByName(const char* pstrName)				{   return m_listChild.FindByName(pstrName);		}
// 	virtual CDrawBase* FindByID(const char* pstrID)					{   return m_listChild.FindByID(pstrID);			}
// 	virtual CDrawBase* GetHead()									{   return m_listChild.GetHead();					}
// 	virtual CDrawBase* GetTail()									{   return m_listChild.GetTail();					}
// 	virtual void* GetHeadPosition()									{   return m_listChild.GetHeadPosition();			}
// 	virtual void* GetTailPosition()									{   return m_listChild.GetTailPosition();			}
// 	virtual CDrawBase* GetNext(void* &pos)							{   return m_listChild.GetNext(pos);				}
// 	virtual CDrawBase* GetAt(void *pos)								{   return m_listChild.GetAt(pos);					}
// 	virtual void* FindByIndex(int nIndex)							{   return m_listChild.FindByIndex(nIndex);			}
	virtual UINT GetClassID()										{	return DRAWCLASSID_BASELIST;					}
	virtual CDrawBase* GetNextByObj(CDrawBase* pData);
	virtual CDrawBase* GetPrevByObj(CDrawBase* pData);
	
public:
	CDrawBaseList();
	virtual ~CDrawBaseList();
};

#endif // !defined(AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_)
