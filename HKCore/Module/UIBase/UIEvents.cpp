//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIEvents.cpp  CUIEvents


#include "stdafx.h"
#include "UIEvents.h"

CUIEvents::CUIEvents()
{
	//初始化属性

	//初始化成员变量
	m_pEvent_OnArrowUp = NULL;
	m_pEvent_OnArrowDown = NULL;
	m_pEvent_OnArrowLeft = NULL;
	m_pEvent_OnArrowRight = NULL;
	m_pEvent_OnSetFoucus = NULL;
	m_pEvent_OnKillFoucus = NULL;
	m_pEvent_OnEditChanged = NULL;
	m_pEvent_OnSelChanged = NULL;
	m_pEvent_OnDropDown = NULL;
	m_pEvent_OnClick = NULL;
	m_pEvent_OnDbClick = NULL;
	m_pEvent_OnShow = NULL;
	m_pEvent_OnHide = NULL;
	m_pEvent_OnCheck = NULL;
	m_pEvent_OnPreLoad = NULL;
	m_pEvent_OnLoad = NULL;
	m_pEvent_OnUnload = NULL;
	m_pEvent_OnPreCreate = NULL;
	m_pEvent_OnCreate = NULL;
}

CUIEvents::~CUIEvents()
{
}

long CUIEvents::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIEvents::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIEvents::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CUIEvents::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseList listEvent;
	CExBaseList listTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != UICLASSID_CUIEVENT)
		{
			listTemp.AddTail(p);
		}
		else 
		{
			if (SetEvent((CUIEvent*)p))
			{
				listEvent.AddTail(p);
			}
			else
			{
				listTemp.AddTail(p);
			}
		}
	}

	RemoveAll();
	Append(listEvent);
	listEvent.RemoveAll();
	listTemp.DeleteAll();
}

BOOL CUIEvents::SetEvent(CUIEvent *pEvent)
{
	if (pEvent->m_strID == g_strEventID_OnArrowUp)
	{
		m_pEvent_OnArrowUp = pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnArrowDown)
	{
		m_pEvent_OnArrowDown = pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnArrowLeft)
	{
		m_pEvent_OnArrowLeft= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnArrowRight)
	{
		m_pEvent_OnArrowRight= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnSetFoucus)
	{
		m_pEvent_OnSetFoucus= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnKillFoucus)
	{
		m_pEvent_OnKillFoucus= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnEditChanged)
	{
		m_pEvent_OnEditChanged= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnSelChanged)
	{
		m_pEvent_OnSelChanged= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnDropDown)
	{
		m_pEvent_OnDropDown= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnClick)
	{
		m_pEvent_OnClick= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnDbClick)
	{
		m_pEvent_OnDbClick= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnShow)
	{
		m_pEvent_OnShow= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnHide)
	{
		m_pEvent_OnHide= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnCheck)
	{
		m_pEvent_OnCheck= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnPreLoad)
	{
		m_pEvent_OnPreLoad= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnLoad)
	{
		m_pEvent_OnLoad= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnUnload)
	{
		m_pEvent_OnUnload= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnPreCreate)
	{
		m_pEvent_OnPreCreate= pEvent;
	}
	else if (pEvent->m_strID == g_strEventID_OnCreate)
	{
		m_pEvent_OnCreate= pEvent;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIEvents::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIEvents *p = (CUIEvents*)pObj;

	return TRUE;
}

BOOL CUIEvents::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIEvents *p = (CUIEvents*)pDest;

	return TRUE;
}

CBaseObject* CUIEvents::Clone()
{
	CUIEvents *p = new CUIEvents();
	Copy(p);
	return p;
}

BOOL CUIEvents::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIEVENT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIEvents::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	//if (strClassID == pXmlKeys->m_strCUIEventKey)
	{
		pNew = new CUIEvent();
		pNew->m_strID = strClassID;
		pNew->m_strName = strClassID;
	}

	return pNew;
}

CExBaseObject* CUIEvents::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIEVENT)
	{
		pNew = new CUIEvent();
	}

	return pNew;
}

void CUIEvents::Event_OnArrowUp()
{
	if (m_pEvent_OnArrowUp != NULL)
	{
		m_pEvent_OnArrowUp->Run();
	}
}

void CUIEvents::Event_OnArrowDown()
{
	if (m_pEvent_OnArrowDown != NULL)
	{
		m_pEvent_OnArrowDown->Run();
	}
}

void CUIEvents::Event_OnArrowLeft()
{
	if (m_pEvent_OnArrowLeft != NULL)
	{
		m_pEvent_OnArrowLeft->Run();
	}
}

void CUIEvents::Event_OnArrowRight()
{
	if (m_pEvent_OnArrowRight != NULL)
	{
		m_pEvent_OnArrowRight->Run();
	}
}

void CUIEvents::Event_OnSetFoucus()
{
	if (m_pEvent_OnSetFoucus != NULL)
	{
		m_pEvent_OnSetFoucus->Run();
	}
}

void CUIEvents::Event_OnKillFoucus()
{
	if (m_pEvent_OnKillFoucus != NULL)
	{
		m_pEvent_OnKillFoucus->Run();
	}
}

void CUIEvents::Event_OnEditChanged()
{
	if (m_pEvent_OnEditChanged != NULL)
	{
		m_pEvent_OnEditChanged->Run();
	}
}

void CUIEvents::Event_OnSelChanged()
{
	if (m_pEvent_OnSelChanged != NULL)
	{
		m_pEvent_OnSelChanged->Run();
	}
}

void CUIEvents::Event_OnDropDown()
{
	if (m_pEvent_OnDropDown != NULL)
	{
		m_pEvent_OnDropDown->Run();
	}
}

void CUIEvents::Event_OnClick()
{
	if (m_pEvent_OnClick != NULL)
	{
		m_pEvent_OnClick->Run();
	}
}

void CUIEvents::Event_OnDbClick()
{
	if (m_pEvent_OnDbClick != NULL)
	{
		m_pEvent_OnDbClick->Run();
	}
}

void CUIEvents::Event_OnShow()
{
	if (m_pEvent_OnShow != NULL)
	{
		m_pEvent_OnShow->Run();
	}
}

void CUIEvents::Event_OnHide()
{
	if (m_pEvent_OnHide != NULL)
	{
		m_pEvent_OnHide->Run();
	}
}

void CUIEvents::Event_OnCheck()
{
	if (m_pEvent_OnCheck != NULL)
	{
		m_pEvent_OnCheck->Run();
	}
}

void CUIEvents::Event_OnPreLoad()
{
	if (m_pEvent_OnPreLoad != NULL)
	{
		m_pEvent_OnPreLoad->Run();
	}
}

void CUIEvents::Event_OnLoad()
{
	if (m_pEvent_OnLoad != NULL)
	{
		m_pEvent_OnLoad->Run();
	}
}

void CUIEvents::Event_OnUnload()
{
	if (m_pEvent_OnUnload != NULL)
	{
		m_pEvent_OnUnload->Run();
	}
}

void CUIEvents::Event_OnPreCreate()
{
	if (m_pEvent_OnPreCreate != NULL)
	{
		m_pEvent_OnPreCreate->Run();
	}
}

void CUIEvents::Event_OnCreate()
{
	if (m_pEvent_OnCreate != NULL)
	{
		m_pEvent_OnCreate->Run();
	}
}

