//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWindowList.cpp  CUIWindowList


#include "stdafx.h"
#include "UIWindowList.h"
#include "UIWndListPool.h"

CUIWindowList::CUIWindowList()
{
	//初始化属性

	//初始化成员变量
	m_pUIWndListPool = NULL;
}

CUIWindowList::~CUIWindowList()
{
	
}

long CUIWindowList::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkColorFromKey, oNode, m_crBkColorFrom);
	xml_GetAttibuteValue_Color(pXmlKeys->m_strBkColorToKey, oNode, m_crBkColorTo);
	xml_GetAttibuteValue(pXmlKeys->m_strBkBmpFileKey, oNode, m_strBkBmpFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);

	return 0;
}

long CUIWindowList::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue_Color(pXmlKeys->m_strBkColorFromKey, oElement, m_crBkColorFrom);
	xml_SetAttributeValue_Color(pXmlKeys->m_strBkColorToKey, oElement, m_crBkColorTo);
	xml_SetAttributeValue(pXmlKeys->m_strBkBmpFileKey, oElement, m_strBkBmpFile);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);

	return 0;
}

long CUIWindowList::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeCalLen(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeCalLen(oBinaryBuffer, m_strBkBmpFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeRead(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeRead(oBinaryBuffer, m_strBkBmpFile);
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_crBkColorFrom);
		BinarySerializeWrite(oBinaryBuffer, m_crBkColorTo);
		BinarySerializeWrite(oBinaryBuffer, m_strBkBmpFile);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}

	return 0;
}

void CUIWindowList::InitAfterRead()
{
	CUIWindowBase::InitAfterRead();
}

BOOL CUIWindowList::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWindowList *p = (CUIWindowList*)pObj;

	return TRUE;
}

BOOL CUIWindowList::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWindowList *p = (CUIWindowList*)pDest;

	return TRUE;
}

CBaseObject* CUIWindowList::Clone()
{
	CUIWindowList *p = new CUIWindowList();
	Copy(p);
	return p;
}

BOOL CUIWindowList::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CUIWindowList::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	pNew = CUIWindowBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWindowList::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	pNew = CUIWindowBase::CreateNewChild(nClassID);

	return pNew;
}



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CUIWndTabList::CUIWndTabList()
{
	m_pCurrUIWnd = NULL;
}

CUIWndTabList::~CUIWndTabList()
{
	Release();
}

void CUIWndTabList::Release()
{
	m_pCurrUIWnd = NULL;
	RemoveAll();
}

void CUIWndTabList::AddUIWindow(CUIWindowBase *pUIWnd)
{
	POS pos = GetHeadPosition();
	CUIWindowBase *pTemp = NULL;

	if (pos == NULL)
	{
		AddTail(pUIWnd);
		return;
	}

	BOOL bInsert = FALSE;

	while (pos != NULL)
	{
		pTemp = (CUIWindowBase*)GetAt(pos);

		if (pTemp->m_nTabOrder >= pUIWnd->m_nTabOrder)
		{
			InsertBefore(pos, pUIWnd);
			bInsert = TRUE;
			break;
		}

		GetNext(pos);
	}

	if (!bInsert)
	{
		AddTail(pUIWnd);
	}
}

CUIWindowBase* CUIWndTabList::OnTabOrder()
{
	if (m_pCurrUIWnd == NULL)
	{
		m_pCurrUIWnd = (CUIWindowBase*)GetHead();

		if (m_pCurrUIWnd != NULL)
		{
			m_pCurrUIWnd->SetUIWndFocus();
		}

		return m_pCurrUIWnd;
	}

	CUIWindowBase *pUIWnd = NULL;
	pUIWnd = (CUIWindowBase*)GetTail();

	if (pUIWnd == m_pCurrUIWnd)
	{
		m_pCurrUIWnd = (CUIWindowBase*)GetHead();

		if (m_pCurrUIWnd != NULL)
		{
			m_pCurrUIWnd->SetUIWndFocus();
		}

		return m_pCurrUIWnd;
	}

	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pUIWnd = (CUIWindowBase*)GetNext(pos);

		if (pUIWnd == m_pCurrUIWnd)
		{
			m_pCurrUIWnd = (CUIWindowBase*)GetAt(pos);
			break;
		}
	}

	if (m_pCurrUIWnd != NULL)
	{
		m_pCurrUIWnd->SetUIWndFocus();
	}

	return m_pCurrUIWnd;
}


void CUIWindowList::ShowChildren(long nShow)
{
	if (m_pUIWndListPool != NULL)
	{
		return;
	}

	POS pos = GetHeadPosition();
	CUIWindowBase *pWnd = NULL;

	while (pos != NULL)
	{
		pWnd = (CUIWindowBase*)GetNext(pos);

		if (UI_IsUIWndClass(pWnd))
		{
			pWnd->Show(nShow);
		}
	}
}



//创建/销毁方法
BOOL CUIWindowList::UICreate(CWnd *pParent)
{
	if (m_strBkBmpFile.GetLength() >= 4)
	{
		m_pDibBackBitmap = new CDib();
		CString strFile;
		strFile = _P_GetSource_Bitmap_Path();
		strFile += m_strBkBmpFile;

		if (! m_pDibBackBitmap->Load(strFile) )
		{
			delete m_pDibBackBitmap;
			m_pDibBackBitmap = NULL;
		}
	}

	BOOL bNeedCenterWnd = FALSE;
	m_pUIWndListPool = new CUIWndListPool();
	m_pUIWndListPool->SetType(m_strType);
	m_pUIWndListPool->SetDibBackBitmap(m_pDibBackBitmap);
	m_pUIWndListPool->m_crBkColorTo = m_crBkColorTo;
	m_pUIWndListPool->m_crBkColorFrom = m_crBkColorFrom;
	m_pUIWndListPool->CreatePool(pParent, bNeedCenterWnd);
	m_pWindow = m_pUIWndListPool;
	m_pWindow->MoveWindow(m_nLeft, m_nTop, m_nWidth, m_nHeight, TRUE);
		
	if (bNeedCenterWnd)
	{
		m_pWindow->CenterWindow();
	}

	if (m_nShow == 1)
	{
		m_pUIWndListPool->ShowWindow(SW_SHOW);
	}

	UICreateChildren(m_pWindow);
	Show(m_nShow);

	return TRUE;
}


BOOL CUIWindowList::UICreateChildren(CWnd *pParent)
{
	if (pParent == NULL)
	{
		pParent = m_pWindow;
	}

	POS pos = GetHeadPosition();
	CUIWindowBase *pWnd = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (UI_IsUIWndListClassID(nClassID))
		{
			((CUIWindowBase*)p)->UICreate(pParent);
		}
		else if (UI_IsUIWndClassID(nClassID))
		{
			((CUIWindowBase*)p)->UICreate(pParent);
		}
	}

	return TRUE;
}

BOOL CUIWindowList::Destroy()
{
	if (m_pUIWndListPool != NULL)
	{
		m_pUIWndListPool->DestroyWindow();
		delete m_pUIWndListPool;
		m_pUIWndListPool = NULL;
		m_pWindow = NULL;
	}

	if (m_pDibBackBitmap != NULL)
	{
		delete m_pDibBackBitmap;
		m_pDibBackBitmap = NULL;
	}

	DestroyChildren();

	return TRUE;
}

BOOL CUIWindowList::DestroyChildren()
{
	POS pos = GetHeadPosition();
	CUIWindowBase *pWnd = NULL;
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (UI_IsUIWndListClassID(nClassID))
		{
			((CUIWindowBase*)p)->Destroy();
		}
		else if (UI_IsUIWndClassID(nClassID))
		{
			((CUIWindowBase*)p)->Destroy();
		}
		else
		{
		}

		delete p;
	}

	RemoveAll();

	return TRUE;
}

void CUIWindowList::CreateBkBitmap()
{
	
}

