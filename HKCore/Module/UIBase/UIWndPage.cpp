//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndPage.cpp  CUIWndPage


#include "stdafx.h"
#include "UIWndPage.h"
#include "UIWndListPool.h"
#include "UIWndThread.h"

CUIWndPage::CUIWndPage()
{
	//初始化属性
	m_nShowChildren = 0;
	m_nBringToTop = 0;
	m_nTabSysMsg = 0;
	m_nBorder = 0;

	//初始化成员变量
}

CUIWndPage::~CUIWndPage()
{
	Destroy();
	m_oUIWndTabList.Release();
}

long CUIWndPage::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strShowChildrenKey, oNode, m_nShowChildren);
	xml_GetAttibuteValue(pXmlKeys->m_strBringToTopKey, oNode, m_nBringToTop);
	xml_GetAttibuteValue(pXmlKeys->m_strTabSysMsgKey, oNode, m_nTabSysMsg);
	xml_GetAttibuteValue(pXmlKeys->m_strBorderKey, oNode, m_nBorder);
	return 0;
}

long CUIWndPage::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strShowChildrenKey, oElement, m_nShowChildren);
	xml_SetAttributeValue(pXmlKeys->m_strBringToTopKey, oElement, m_nBringToTop);
	xml_SetAttributeValue(pXmlKeys->m_strTabSysMsgKey, oElement, m_nTabSysMsg);
	xml_SetAttributeValue(pXmlKeys->m_strBorderKey, oElement, m_nBorder);
	return 0;
}

long CUIWndPage::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowList::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nShowChildren);
		BinarySerializeCalLen(oBinaryBuffer, m_nBringToTop);
		BinarySerializeCalLen(oBinaryBuffer, m_nTabSysMsg);
		BinarySerializeCalLen(oBinaryBuffer, m_nBorder);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nShowChildren);
		BinarySerializeRead(oBinaryBuffer, m_nBringToTop);
		BinarySerializeRead(oBinaryBuffer, m_nTabSysMsg);
		BinarySerializeRead(oBinaryBuffer, m_nBorder);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nShowChildren);
		BinarySerializeWrite(oBinaryBuffer, m_nBringToTop);
		BinarySerializeWrite(oBinaryBuffer, m_nTabSysMsg);
		BinarySerializeWrite(oBinaryBuffer, m_nBorder);
	}
	return 0;
}

void CUIWndPage::InitAfterRead()
{
	CUIWindowList::InitAfterRead();
}

BOOL CUIWndPage::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowList::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndPage *p = (CUIWndPage*)pObj;

	if(m_nShowChildren != p->m_nShowChildren)
	{
		return FALSE;
	}

	if(m_nBringToTop != p->m_nBringToTop)
	{
		return FALSE;
	}

	if(m_crBkColorFrom != p->m_crBkColorFrom)
	{
		return FALSE;
	}

	if(m_crBkColorTo != p->m_crBkColorTo)
	{
		return FALSE;
	}

	if(m_strBkBmpFile != p->m_strBkBmpFile)
	{
		return FALSE;
	}

	if(m_nTabSysMsg != p->m_nTabSysMsg)
	{
		return FALSE;
	}

	if(m_nBorder != p->m_nBorder)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndPage::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowList::CopyOwn(pDest);

	CUIWndPage *p = (CUIWndPage*)pDest;

	p->m_nShowChildren = m_nShowChildren;
	p->m_nBringToTop = m_nBringToTop;
	p->m_nTabSysMsg = m_nTabSysMsg;
	p->m_nBorder = m_nBorder;
	return TRUE;
}

CBaseObject* CUIWndPage::Clone()
{
	CUIWndPage *p = new CUIWndPage();
	Copy(p);
	return p;
}

BOOL CUIWndPage::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWndPage::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	
	if (strClassID == CUIBaseXmlRWKeys::CUIWndLayerKey())
	{
		pNew = new CUIWndLayer();
		return pNew;
	}

	pNew = CUIWindowList::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndPage::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == UICLASSID_CUIWNDLAYER)
	{
		pNew = new CUIWndLayer();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	pNew = CUIWindowList::CreateNewChild(nClassID);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////

BOOL CUIWndPage::LoadPage()
{
	if (m_pWindow != NULL)
	{
		return TRUE;
	}

	BOOL bTrue = ReadPageFromFile(m_strPageFile);

	CWnd *pMainWnd = CUIWndThread::Get_ProcMainWnd();//AfxGetMainWnd();

// 	if (pMainWnd != NULL)
// 	{
// 	}
// 	else
	{
		pMainWnd = CWnd::GetDesktopWindow();
	}

	UICreate(pMainWnd);

	return bTrue;
}

void CUIWndPage::ClosePage()
{
//	ASSERT (m_pMsgEvents != NULL);

	if (m_pMsgEvents != NULL)
	{
		m_pMsgEvents->Event_OnUnload();
	}
}

BOOL CUIWndPage::ReadPageFromFile(const CString &strPageFile)
{
	CString strFile;
	strFile = _P_GetResourcePath();
	strFile += m_strPageFile;
	OpenXmlFile(strFile, CUIBaseXmlRWKeys::CUIWndPageKey(), CUIBaseXmlRWKeys::g_pXmlKeys);

	Event_OnLoad();

	return TRUE;
}


long CUIWndPage::GetPageWidth()
{
	return m_nWidth;
}

void CUIWndPage::SetPageWidth(long nWidth)
{
	
}

long CUIWndPage::GetPageHeight()
{
	return m_nHeight;
}

void CUIWndPage::SetPageHeight(long nHeight)
{
	
}

void CUIWndPage::SetPagePosition(long nLeft, long nTop, long nRight, long nBottom)
{
	
}

void CUIWndPage::SetPageSize(long nWidth, long nHeight)
{

}

CUIWndLayer* CUIWndPage::FindLayerByID(LPCTSTR pszLayerID)
{
	CString strLayerID;
	strLayerID = pszLayerID;
	return FindLayerByID(strLayerID);
}

CUIWndLayer* CUIWndPage::FindLayerByID(const CString &strLayerID)
{
	CUIWndLayer *pLayer = (CUIWndLayer*)FindByID(strLayerID);
	return pLayer;
}

CUIWindowBase* CUIWndPage::FindWindowByID(LPCTSTR pszWindowID)
{
	CString strWindowID;
	strWindowID = pszWindowID;
	return FindWindowByID(strWindowID);
}

CUIWindowBase* CUIWndPage::FindWindowByID(const CString &strWindowID)
{
	CUIWindowBase *pWindow = NULL;
	CUIWndLayer *pLayer = NULL; 
	CUIWindowBase *pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == UICLASSID_CUIWNDLAYER)
		{
			pLayer = (CUIWndLayer *)p;

			if (pLayer->m_strID == strWindowID)
			{
				pFind = pLayer;
				break;
			}

			pWindow = pLayer->FindWindowByID(strWindowID);

			if (pWindow != NULL)
			{
				pFind = pWindow;
				break;
			}
		}
	}

	return pFind;
}


//////////////////////////////////////////////////////////////////////////
//

void CUIWndPage::AddUITabWnd(CUIWindowList *pUIWndList)
{
	POS pos = pUIWndList->GetHeadPosition();
	CUIWindowBase *pUIWnd = NULL;

	while (pos != NULL)
	{
		pUIWnd = (CUIWindowBase*)GetNext(pos);

		if (UI_IsUIWndListClassID(pUIWnd))
		{
			AddUITabWnd(pUIWnd);
		}
	}

}

void CUIWndPage::AddUITabWnd(CUIWindowBase *pUIWnd)
{
	if (pUIWnd->IsWindowBase())
	{
		if (pUIWnd->m_nTabOrder > 0)
		{
			m_oUIWndTabList.AddUIWindow(pUIWnd);
		}
	}
	else
	{
		if (UI_IsUIWndListClassID(pUIWnd))
		{
			AddUITabWnd((CUIWindowList*)pUIWnd);
		}
	}
}

//创建/销毁方法
BOOL CUIWndPage::UICreate(CWnd *pParent)
{
	Event_OnPreCreate();

	CUIWindowList::UICreate(pParent);
	
	m_bHasCreated = TRUE;
	
	Event_OnCreate();

	//在一个新的page创建时,先将m_oUIWndTabList清空,然后添加当前page的有Tab值的窗口
	m_oUIWndTabList.Release();
	AddUITabWnd(this);

	m_pUIWndListPool->SetWindowText(m_strName);

	return TRUE;
}

BOOL CUIWndPage::Destroy()
{
	ClosePage();

	m_oUIWndTabList.Release();

	m_bHasCreated = FALSE;
	m_pWindow = NULL;
	m_bInClosedState = FALSE;

	CUIWindowList::Destroy();

	return TRUE;
}

