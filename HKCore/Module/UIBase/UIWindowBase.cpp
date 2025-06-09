//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWindowBase.cpp  CUIWindowBase


#include "stdafx.h"
#include "UIWindowBase.h"
#include "UIWndLayer.h"


UINT  CUIWindowBase::g_nWindowID = 6001;
CUIWindowBase *CUIWindowBase::g_pUIWndFocus = NULL;

CUIWindowBase::CUIWindowBase()
{
	//初始化属性
	m_nTabOrder = 0;
	m_nTop = 0;
	m_nLeft = 0;
	m_nWidth = 0;
	m_nHeight = 0;
	m_nShow = 0;
	m_nEnable = 0;
	m_nSysTimerID = 0;
	m_nSysOptrID = 0;
	m_nFrmSize = 0;

	m_nWndState  = WNDSTATE_ANAY;

	//初始化成员变量
	m_pFont = NULL;
	m_pText = NULL;
	m_pMsgEvents = NULL;

	m_pWindow = NULL;

	m_bOver = m_bSelected = m_bTracking = m_bFocus = FALSE;

	m_nTransparent = 0;
	m_crTransMaskColor = RGB(255,0,0);     //失效的颜色

}

CUIWindowBase::~CUIWindowBase()
{
	
}

long CUIWindowBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strTabOrderKey, oNode, m_nTabOrder);
	xml_GetAttibuteValue(pXmlKeys->m_strTopKey, oNode, m_nTop);
	xml_GetAttibuteValue(pXmlKeys->m_strLeftKey, oNode, m_nLeft);
	xml_GetAttibuteValue(pXmlKeys->m_strWidthKey, oNode, m_nWidth);
	xml_GetAttibuteValue(pXmlKeys->m_strHeightKey, oNode, m_nHeight);
	xml_GetAttibuteValue(pXmlKeys->m_strAccelMsgKey, oNode, m_strAccelMsg);
	xml_GetAttibuteValue(pXmlKeys->m_strShowKey, oNode, m_nShow);
	xml_GetAttibuteValue(pXmlKeys->m_strEnableKey, oNode, m_nEnable);
	xml_GetAttibuteValue(pXmlKeys->m_strSysTimerIDKey, oNode, m_nSysTimerID);
	xml_GetAttibuteValue(pXmlKeys->m_strSysOptrIDKey, oNode, m_nSysOptrID);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkColorKey, oNode, m_crBkColor);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strForeColorKey, oNode, m_crForeColor);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strFrmTopLeftColorKey, oNode, m_crFrmTopLeftColor);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strFrmRightBottomColorKey, oNode, m_crFrmRightBottomColor);
	xml_GetAttibuteValue(pXmlKeys->m_strFrmSizeKey, oNode, m_nFrmSize);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkActiveColorKey, oNode, m_crBkActiveColor);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkDisableColorKey,oNode,m_crBkDisableColor);

	xml_GetAttibuteValue(pXmlKeys->m_strTransparentKey, oNode, m_nTransparent);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkDisableColorKey,oNode,m_crBkDisableColor);

	return 0;
}

long CUIWindowBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue_Color(pXmlKeys->m_strBkActiveColorKey, oElement, m_crBkActiveColor);
	xml_SetAttributeValue_Color(pXmlKeys->m_strDisableColorKey,oElement,m_crBkDisableColor);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strTabOrderKey, oElement, m_nTabOrder);
	xml_SetAttributeValue(pXmlKeys->m_strTopKey, oElement, m_nTop);
	xml_SetAttributeValue(pXmlKeys->m_strLeftKey, oElement, m_nLeft);
	xml_SetAttributeValue(pXmlKeys->m_strWidthKey, oElement, m_nWidth);
	xml_SetAttributeValue(pXmlKeys->m_strHeightKey, oElement, m_nHeight);
	xml_SetAttributeValue(pXmlKeys->m_strAccelMsgKey, oElement, m_strAccelMsg);
	xml_SetAttributeValue(pXmlKeys->m_strShowKey, oElement, m_nShow);
	xml_SetAttributeValue(pXmlKeys->m_strEnableKey, oElement, m_nEnable);
	xml_SetAttributeValue(pXmlKeys->m_strSysTimerIDKey, oElement, m_nSysTimerID);
	xml_SetAttributeValue(pXmlKeys->m_strSysOptrIDKey, oElement, m_nSysOptrID);
	xml_SetAttributeValue_Color(pXmlKeys->m_strBkColorKey, oElement, m_crBkColor);
	xml_SetAttributeValue_Color(pXmlKeys->m_strForeColorKey, oElement, m_crForeColor);
	xml_SetAttributeValue_Color(pXmlKeys->m_strFrmTopLeftColorKey, oElement, m_crFrmTopLeftColor);
	xml_SetAttributeValue_Color(pXmlKeys->m_strFrmRightBottomColorKey, oElement, m_crFrmRightBottomColor);
	xml_SetAttributeValue(pXmlKeys->m_strFrmSizeKey, oElement, m_nFrmSize);
	
	xml_SetAttributeValue_Color(pXmlKeys->m_strBkDisableColorKey, oElement, m_crBkDisableColor);
	xml_SetAttributeValue(pXmlKeys->m_strTransparentKey, oElement, m_nTransparent);

	return 0;
}

long CUIWindowBase::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strID);
		BinarySerializeCalLen(oBinaryBuffer, m_nTabOrder);
		BinarySerializeCalLen(oBinaryBuffer, m_nTop);
		BinarySerializeCalLen(oBinaryBuffer, m_nLeft);
		BinarySerializeCalLen(oBinaryBuffer, m_nWidth);
		BinarySerializeCalLen(oBinaryBuffer, m_nHeight);
		BinarySerializeCalLen(oBinaryBuffer, m_strAccelMsg);
		BinarySerializeCalLen(oBinaryBuffer, m_nShow);
		BinarySerializeCalLen(oBinaryBuffer, m_nEnable);
		BinarySerializeCalLen(oBinaryBuffer, m_nSysTimerID);
		BinarySerializeCalLen(oBinaryBuffer, m_nSysOptrID);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crForeColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crFrmTopLeftColor);
		BinarySerializeCalLen(oBinaryBuffer, m_crFrmRightBottomColor);
		BinarySerializeCalLen(oBinaryBuffer, m_nFrmSize);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strID);
		BinarySerializeRead(oBinaryBuffer, m_nTabOrder);
		BinarySerializeRead(oBinaryBuffer, m_nTop);
		BinarySerializeRead(oBinaryBuffer, m_nLeft);
		BinarySerializeRead(oBinaryBuffer, m_nWidth);
		BinarySerializeRead(oBinaryBuffer, m_nHeight);
		BinarySerializeRead(oBinaryBuffer, m_strAccelMsg);
		BinarySerializeRead(oBinaryBuffer, m_nShow);
		BinarySerializeRead(oBinaryBuffer, m_nEnable);
		BinarySerializeRead(oBinaryBuffer, m_nSysTimerID);
		BinarySerializeRead(oBinaryBuffer, m_nSysOptrID);
		BinarySerializeRead(oBinaryBuffer, m_crBkColor);
		BinarySerializeRead(oBinaryBuffer, m_crForeColor);
		BinarySerializeRead(oBinaryBuffer, m_crFrmTopLeftColor);
		BinarySerializeRead(oBinaryBuffer, m_crFrmRightBottomColor);
		BinarySerializeRead(oBinaryBuffer, m_nFrmSize);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strID);
		BinarySerializeWrite(oBinaryBuffer, m_nTabOrder);
		BinarySerializeWrite(oBinaryBuffer, m_nTop);
		BinarySerializeWrite(oBinaryBuffer, m_nLeft);
		BinarySerializeWrite(oBinaryBuffer, m_nWidth);
		BinarySerializeWrite(oBinaryBuffer, m_nHeight);
		BinarySerializeWrite(oBinaryBuffer, m_strAccelMsg);
		BinarySerializeWrite(oBinaryBuffer, m_nShow);
		BinarySerializeWrite(oBinaryBuffer, m_nEnable);
		BinarySerializeWrite(oBinaryBuffer, m_nSysTimerID);
		BinarySerializeWrite(oBinaryBuffer, m_nSysOptrID);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColor);
		BinarySerializeWrite(oBinaryBuffer, m_crForeColor);
		BinarySerializeWrite(oBinaryBuffer, m_crFrmTopLeftColor);
		BinarySerializeWrite(oBinaryBuffer, m_crFrmRightBottomColor);
		BinarySerializeWrite(oBinaryBuffer, m_nFrmSize);
	}
	return 0;
}

void CUIWindowBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == UICLASSID_CUIBASEFONT)
		{
			m_pFont = (CUIBaseFont*)p;
		}
		else if (nClassID == UICLASSID_CUIWINDOWTEXT)
		{
			m_pText = (CUIWindowText*)p;
		}
		else if (nClassID == UICLASSID_CUIEVENTS)
		{
			m_pMsgEvents = (CUIEvents*)p;
		}
	}

	if (m_pFont == NULL)
	{
		m_pFont = (CUIBaseFont*)AddNewChild(new CUIBaseFont());
	}

	if (m_pText == NULL)
	{
		m_pText = (CUIWindowText*)AddNewChild(new CUIWindowText());
	}

	if (m_pMsgEvents == NULL)
	{
		m_pMsgEvents = (CUIEvents*)AddNewChild(new CUIEvents());
	}
}

BOOL CUIWindowBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CUIWindowBase *p = (CUIWindowBase*)pObj;

	if(m_strID != p->m_strID)
	{
		return FALSE;
	}

	if(m_nTabOrder != p->m_nTabOrder)
	{
		return FALSE;
	}

	if(m_nTop != p->m_nTop)
	{
		return FALSE;
	}

	if(m_nLeft != p->m_nLeft)
	{
		return FALSE;
	}

	if(m_nWidth != p->m_nWidth)
	{
		return FALSE;
	}

	if(m_nHeight != p->m_nHeight)
	{
		return FALSE;
	}

	if(m_strAccelMsg != p->m_strAccelMsg)
	{
		return FALSE;
	}

	if(m_nShow != p->m_nShow)
	{
		return FALSE;
	}

	if(m_nEnable != p->m_nEnable)
	{
		return FALSE;
	}

	if(m_nSysTimerID != p->m_nSysTimerID)
	{
		return FALSE;
	}

	if(m_nSysOptrID != p->m_nSysOptrID)
	{
		return FALSE;
	}

	if(m_crBkColor != p->m_crBkColor)
	{
		return FALSE;
	}

	if(m_crForeColor != p->m_crForeColor)
	{
		return FALSE;
	}

	if(m_crFrmTopLeftColor != p->m_crFrmTopLeftColor)
	{
		return FALSE;
	}

	if(m_crFrmRightBottomColor != p->m_crFrmRightBottomColor)
	{
		return FALSE;
	}

	if(m_nFrmSize != p->m_nFrmSize)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWindowBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase *p = (CUIWindowBase*)pDest;

	p->m_strID = m_strID;
	p->m_nTabOrder = m_nTabOrder;
	p->m_nTop = m_nTop;
	p->m_nLeft = m_nLeft;
	p->m_nWidth = m_nWidth;
	p->m_nHeight = m_nHeight;
	p->m_strAccelMsg = m_strAccelMsg;
	p->m_nShow = m_nShow;
	p->m_nEnable = m_nEnable;
	p->m_nSysTimerID = m_nSysTimerID;
	p->m_nSysOptrID = m_nSysOptrID;
	p->m_crBkColor = m_crBkColor;
	p->m_crForeColor = m_crForeColor;
	p->m_crFrmTopLeftColor = m_crFrmTopLeftColor;
	p->m_crFrmRightBottomColor = m_crFrmRightBottomColor;
	p->m_nFrmSize = m_nFrmSize;
	return TRUE;
}

CBaseObject* CUIWindowBase::Clone()
{
	CUIWindowBase *p = new CUIWindowBase();
	Copy(p);
	return p;
}

CExBaseObject* CUIWindowBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIEventsKey)
	{
		pNew = new CUIEvents();
	}
	else if (strClassID == pXmlKeys->m_strCUIBaseFontKey)
	{
		pNew = new CUIBaseFont();
	}
	else if (strClassID == pXmlKeys->m_strCUIWindowTextKey)
	{
		pNew = new CUIWindowText();
	}

	return pNew;
}

CExBaseObject* CUIWindowBase::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIEVENTS)
	{
		pNew = new CUIEvents();
	}
	else if (nClassID == UICLASSID_CUIBASEFONT)
	{
		pNew = new CUIBaseFont();
	}
	else if (nClassID == UICLASSID_CUIWINDOWTEXT)
	{
		pNew = new CUIWindowText();
	}

	return pNew;
}

//////////////////////////////////////////////////////////////////////////
BOOL CUIWindowBase::IsWindowBase()
{
	return UI_IsUIWndClass(this);
}

BOOL CUIWindowBase::IsWindowList()
{
	return UI_IsUIWndListClassID(this);
}

BOOL CUIWindowBase::IsAncestorPageShow()
{
	CBaseObject *pPage = NULL;
	pPage = GetAncestor(UICLASSID_CUIWNDPAGE);
	ASSERT (pPage != NULL);

	if (pPage != NULL)
	{
		return (((CUIWindowBase*)pPage)->m_nShow == 1);
	}
	else
	{
		return FALSE;
	}
}


//窗口方法
void CUIWindowBase::Show()
{
	Show(m_nShow);
}

BOOL CUIWindowBase::Show(long nShow)
{
	if (nShow == 1)
	{
		m_nWndState |= WNDSTATE_VISIBLE;
	}
	else
	{
		m_nWndState &= ~WNDSTATE_VISIBLE;
	}

	m_nShow = nShow;
	BOOL bChange = FALSE;

	if(m_pWindow != NULL)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			if (nShow == 1)
			{
				if (!m_pWindow->IsWindowVisible())
				{
					bChange = TRUE;
					m_pWindow->ShowWindow(SW_SHOW);
					m_pWindow->BringWindowToTop();
					m_pWindow->Invalidate(TRUE);
					m_pWindow->SetFocus();
				}

//				{
//				}
			}
			else
			{
				//if (m_pWindow->IsWindowVisible())
				{
					m_pWindow->ShowWindow(SW_HIDE);
					bChange = TRUE;
				}
			}
		}
	}

// 	if (m_pMsgEvents != NULL)
// 	{
// 		if (nShow == 1)
// 		{
// 			CUIEvent *pMsgImp = (CUIEvent*)m_pMsgEvents->FindByID(g_pszKeyOnUIMessage_Show);
// 
// 			if (pMsgImp != NULL)
// 			{
// 				pMsgImp->Run();
// 			}
// 		}
// 		else
// 		{
// 			CUIEvent *pMsgImp = (CUIEvent*)m_pMsgEvents->FindByID(g_pszKeyOnUIMessage_Hide);
// 
// 			if (pMsgImp != NULL)
// 			{
// 				pMsgImp->Run();
// 			}
// 		}
// 	}

	return bChange;
}

void CUIWindowBase::ShowChildren(long nShow)
{
	
}

BOOL CUIWindowBase::IsShow()
{
	BOOL bShow = FALSE;

	if(m_pWindow != NULL)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			bShow = m_pWindow->IsWindowVisible();
		}
	}

	return bShow;
}


void CUIWindowBase::Enable(long nEnable, BOOL bEnableWindow)
{
	if (nEnable == 1)
	{
		m_nWndState |= WNDSTATE_ENABLE;
	}
	else
	{
		m_nWndState &= ~WNDSTATE_ENABLE;
	}

	if (m_pWindow != NULL)
	{
		if (::IsWindow(m_pWindow->m_hWnd) && bEnableWindow)
		{
			m_pWindow->EnableWindow(nEnable);
			m_pWindow->Invalidate(FALSE);
		}		
	}
}

BOOL CUIWindowBase::IsEnable()
{
	BOOL bIsEnable = FALSE;
	long nState = m_nWndState & WNDSTATE_ENABLE;

	if (nState == 0)
	{
		bIsEnable = FALSE;
	}
	else
	{
		bIsEnable = TRUE;
	}

	return bIsEnable;
}


void CUIWindowBase::SetUIWndFocus(long xOff, long yOff)
{
	if (m_pWindow != NULL)
	{
// 		if (::IsWindow(m_pWindow->m_hWnd))
// 		{
// 			m_pWindow->SetFocus();
// 		}

		CRect rc;
		m_pWindow->GetWindowRect(&rc);
		DWORD x = rc.left + xOff;
		DWORD y = rc.top + yOff;
		SetCursorPos(x, y);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
	}
}

void CUIWindowBase::ReDrawWnd()
{

}

void CUIWindowBase::SetWndText(CString strWndText)
{
#ifdef _LANGUAGEMNGR_USE__
	ParseLanguageString(strWndText);
#endif

	if (m_pText != NULL)
	{
		m_pText->m_strText = strWndText;
	}

	if (m_pWindow != NULL)
	{
		if (::IsWindow(m_pWindow->m_hWnd))
		{
			m_pWindow->SetWindowText(strWndText);
		}
	}
}

CString CUIWindowBase::GetWndText()
{
	ASSERT (m_pText != NULL);

	if (m_pText == NULL)
	{
		return _T("");
	}
	else
	{
		return m_pText->m_strText;
	}
}

CUIBaseFont* CUIWindowBase::GetUIBaseFont()
{
	if (m_pFont != NULL)
	{
		return m_pFont;
	}

	CUIBaseFont *pFind = NULL;
	CUIWindowBase *pParent = (CUIWindowBase*)GetParent();

	while (pParent != NULL)
	{
		if (pParent->m_pFont != NULL)
		{
			pFind = pParent->m_pFont;
			break;
		}

		pParent = (CUIWindowBase*)GetParent();
	}

	if (pFind == NULL)
	{
		pFind = &CUIBaseFont::g_oUIBaseFont;
	}

	return pFind;
}



//窗口的位置大小
void CUIWindowBase::SetWndHeight(long nHeight)
{

}

void CUIWindowBase::SetWndWidth(long nWidth)
{

}

void CUIWindowBase::SetWndWidthHeight(long nWidth, long nHeight)
{

}

void CUIWindowBase::SetWndLeft(long nLeft)
{

}

void CUIWindowBase::SetWndTop(long nTop)
{

}

void CUIWindowBase::SetWndRight(long nRight)
{

}

void CUIWindowBase::SetWndBottom(long nBottom)
{

}

void CUIWindowBase::SetWndPosition(long nLeft, long nTop, long nRight, long nBottom)
{

}

void CUIWindowBase::SetWndPosition(CRect rcPos)
{

}

void CUIWindowBase::SetWndSize(long nWidth, long nHeight)
{
	
}

CRect CUIWindowBase::GetWndPosition()
{
	CRect rcWnd;
	rcWnd = CRect(m_nLeft, m_nTop, m_nLeft+GetWndWidth(), m_nTop + GetWndHeight());

	if (IsWindowBase())
	{
		CUIWndLayer *pLayer = (CUIWndLayer*)GetParent();

		if (!pLayer->IsWindowType())
		{
			CRect rcLayer = pLayer->GetWndPosition();
			rcWnd.left += rcLayer.left;
			rcWnd.top  += rcLayer.top;
			rcWnd.right += rcLayer.left;
			rcWnd.bottom  += rcLayer.top;
		}
	}

	return rcWnd;
}


//创建/销毁方法
BOOL CUIWindowBase::UICreate(CWnd *pParent)
{
	ASSERT (FALSE);
	return FALSE;
}

BOOL CUIWindowBase::Destroy()
{

	return TRUE;
}

BOOL CUIWindowBase::DestroyChildren()
{
	ASSERT (FALSE);

	return TRUE;
}

long CUIWindowBase::ExecWndCmd(const char *pszCmd, const char *pszPara)
{
	CString strCmd, strPara;
	strCmd = pszCmd;
	strPara = pszPara;
	strCmd.MakeLower();
	strPara.MakeLower();

	return ExecWndCmd(strCmd, strPara);
}

long CUIWindowBase::ExecWndCmd(const CString &strCmd, const CString &strPara)
{
	return 0;
}

long CUIWindowBase::GetWndAttr(const CString &strAttrID, CString &strAttrValue)
{
	return -1;
}

long CUIWindowBase::SetWndAttr(const CString &strAttrID, const CString &strAttrValue)
{
	return -1;
}

//////////////////////////////////////////////////////////////////////////
//消息处理
void CUIWindowBase::Event_OnArrowUp()
{
	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnArrowUp();
	}
}

void CUIWindowBase::Event_OnArrowDown()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnArrowDown();
	}
}

void CUIWindowBase::Event_OnArrowLeft()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnArrowLeft();
	}
}

void CUIWindowBase::Event_OnArrowRight()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnArrowRight();
	}
}

void CUIWindowBase::Event_OnSetFoucus()
{
	//ASSERT (m_pMsgEvents != NULL);
	m_bFocus = TRUE;
	m_pWindow->Invalidate(TRUE);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnSetFoucus();
	}
}

void CUIWindowBase::Event_OnKillFoucus()
{
	m_bFocus = FALSE;
	m_pWindow->Invalidate(TRUE);
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnKillFoucus();
	}
}

void CUIWindowBase::Event_OnEditChanged()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnEditChanged();
	}
}

void CUIWindowBase::Event_OnSelChanged()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnSelChanged();
	}
}

void CUIWindowBase::Event_OnDropDown()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnDropDown();
	}
}

void CUIWindowBase::Event_OnClick()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnClick();
	}
}

void CUIWindowBase::Event_OnDbClick()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnDbClick();
	}
}

void CUIWindowBase::Event_OnShow()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnShow();
	}
}

void CUIWindowBase::Event_OnHide()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnHide();
	}
}

void CUIWindowBase::Event_OnCheck()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnCheck();
	}
}


void CUIWindowBase::Event_OnPreLoad()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnPreLoad();
	}
}

void CUIWindowBase::Event_OnLoad()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnLoad();
	}
}

void CUIWindowBase::Event_OnUnload()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnUnload();
	}
}

void CUIWindowBase::Event_OnPreCreate()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnPreCreate();
	}
}

void CUIWindowBase::Event_OnCreate()
{
	//ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnCreate();
	}
}



void CUIWindowBase::UI_OnClicked() 
{
	Event_OnClick();
}

void CUIWindowBase::UI_OnDoubleclicked() 
{
	Event_OnDbClick();
}

void CUIWindowBase::UI_OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!IsEnable())
	{
		return;
	}

	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		ASSERT (m_pWindow != NULL);
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_pWindow->m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}

	//CButton::OnMouseMove(nFlags, point);
}

LRESULT CUIWindowBase::UI_OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (!IsEnable())
	{
		return 0;
	}

	ASSERT (m_pWindow != NULL);
	m_bOver = FALSE;
	m_bTracking = FALSE;
	m_bSelected = FALSE;
	m_pWindow->InvalidateRect(NULL, FALSE);
	return 0;
}

void CUIWindowBase::RedrawParentRect()
{
	if (m_pWindow == NULL)
	{
		return;
	}

	CWnd *pParentWnd = (CWnd*)m_pWindow->GetParent();

	if (pParentWnd != NULL)
	{
		if (::IsWindow(pParentWnd->m_hWnd))
		{
			pParentWnd->InvalidateRect(GetWndPosition(), TRUE);
// 			pParentWnd->InvalidateRect(GetWndPosition(), TRUE);
		}
	}
}

LRESULT CUIWindowBase::UI_OnMouseHover(WPARAM wParam, LPARAM lParam)
{
	if (!IsEnable())
	{
		return 0;
	}

	ASSERT (m_pWindow != NULL);
	m_bOver = TRUE;
	m_bSelected = FALSE;
	m_pWindow->InvalidateRect(NULL);

	return 0;
}

void CUIWindowBase::UI_KillFoucus()
{
	if (!m_bFocus)
	{
		return;
	}

	m_bFocus = FALSE;

	if (m_pWindow != NULL)
	{
		m_pWindow->Invalidate();
	}

	Event_OnKillFoucus();
}

void CUIWindowBase::UI_OnLButtonDown(UINT nFlags, CPoint point)
{
	if (!IsEnable())
	{
		return;
	}

	if (g_pUIWndFocus != NULL && g_pUIWndFocus != this)
	{
		g_pUIWndFocus->UI_KillFoucus();
	}

	if (g_pUIWndFocus != this)
	{
		g_pUIWndFocus = this;
		g_pUIWndFocus->Event_OnSetFoucus();
	}

	m_bSelected = TRUE;
}

void CUIWindowBase::UI_OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!IsEnable())
	{
		return;
	}

	m_bSelected = FALSE;
	m_pWindow->InvalidateRect(NULL);
}

//绘制按钮的底色
void CUIWindowBase::DoGradientFill(CDC *pDC, CRect* rect)
{
	if (m_bOver)
	{
		if (m_bFocus)
		{
			GradientFill(pDC, rect, RGB(255, 255, 255), RGB(240,240,240), FALSE);
		}
		else
		{
			GradientFill(pDC, rect, RGB(255, 255, 255), RGB(240,240,230), FALSE);
		}
	}
	else
	{
		if (m_bFocus)
		{
			GradientFill(pDC, rect, RGB(255, 255, 255), m_crBkColor, FALSE);
		}
		else
		{
			GradientFill(pDC, rect, RGB(255, 255, 255), m_crBkColor, FALSE);
		}
	}
}

static char g_pszUIBaseBitmapPath[MAX_PATH];

void _P_InitSource_Bitmap_Path()
{
	strcpy(g_pszUIBaseBitmapPath, _P_GetResourcePath());
	strcat(g_pszUIBaseBitmapPath, "Bitmap\\");
}

const char* _P_GetSource_Bitmap_Path()
{
	return g_pszUIBaseBitmapPath;
}

