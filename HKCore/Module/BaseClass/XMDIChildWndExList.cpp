// ExBaseListComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "XMDIChildWndExList.h"


//////////////////////////////////////////////////////////////////////////
// CXMDIChildWndExList


CXMDIChildWndExList::CXMDIChildWndExList()
{

}

CXMDIChildWndExList::~CXMDIChildWndExList()
{
}

CMDIChildWndEx* CXMDIChildWndExList::FindMDIChildWndEx(CExBaseObject *pObj)
{
	POS pos = GetHeadPosition();
	CMDIChildWndExObj *p = NULL;
	CMDIChildWndExObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CMDIChildWndExObj *)GetNext(pos);

		if (p->m_pObjectRef == pObj)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_pMdiChildWndRef;
	}
}

CExBaseObject* CXMDIChildWndExList::FindMDIChildWndEx(CMDIChildWndEx *pWnd)
{
	POS pos = GetHeadPosition();
	CMDIChildWndExObj *p = NULL;
	CMDIChildWndExObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CMDIChildWndExObj *)GetNext(pos);

		if (p->m_pMdiChildWndRef == pWnd)
		{
			pFind = p;
			break;
		}
	}

	if (pFind == NULL)
	{
		return NULL;
	}
	else
	{
		return pFind->m_pObjectRef;
	}
}

void CXMDIChildWndExList::AddNewWndObjRef(CMDIChildWndEx *pWndRef, CExBaseObject *pObjRef)
{
	CMDIChildWndEx *pFind = FindMDIChildWndEx(pObjRef);

	if (pFind != NULL)
	{
		return;
	}

	CMDIChildWndExObj *p = new CMDIChildWndExObj(pWndRef, pObjRef);
	AddNewChild(p);

}

void CXMDIChildWndExList::CloseFrame(CMDIChildWndEx *pWndRef)
{
	POS pos = GetHeadPosition();
	CMDIChildWndExObj *p = NULL;
	CMDIChildWndExObj *pFind = NULL;

	while (pos != NULL)
	{
		p = (CMDIChildWndExObj *)GetNext(pos);

		if (p->m_pMdiChildWndRef == pWndRef)
		{
			pFind = p;
			break;
		}
	}

	if (pFind != NULL)
	{
		Delete(pFind);
	}
}

