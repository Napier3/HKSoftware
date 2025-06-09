#pragma once

#include "ExBaseList.h"



class CXMDIChildWndExList : public CExBaseList
{
protected:
	class CMDIChildWndExObj : public CExBaseObject
	{
	public:
		CMDIChildWndExObj()
		{
			m_pMdiChildWndRef = NULL;
			m_pObjectRef = NULL;
		};

		CMDIChildWndExObj(CMDIChildWndEx *pWndRef, CExBaseObject *pObjRef)
		{
			m_pMdiChildWndRef = pWndRef;
			m_pObjectRef = pObjRef;
		};

		virtual ~CMDIChildWndExObj(){}

		CMDIChildWndEx *m_pMdiChildWndRef;
		CExBaseObject  *m_pObjectRef;
	};

public:
	CXMDIChildWndExList();
	virtual ~CXMDIChildWndExList();

	CMDIChildWndEx* FindMDIChildWndEx(CExBaseObject *pObj);
	CExBaseObject* FindMDIChildWndEx(CMDIChildWndEx *pWnd);

	void AddNewWndObjRef(CMDIChildWndEx *pWndRef, CExBaseObject *pObjRef);
	void CloseFrame(CMDIChildWndEx *pWndRef);
};	

