//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndLayer.cpp  CUIWndLayer


#include "stdafx.h"
#include "UIWndLayer.h"

CUIWndLayer::CUIWndLayer()
{
	//初始化属性
	m_nShowChildren = 1;
	m_nBringToTop = 0;
	m_nBorder = 0;

	//初始化成员变量
	m_pDibBackBitmap = NULL;
}

CUIWndLayer::~CUIWndLayer()
{
	Destroy();
}

long CUIWndLayer::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strShowChildrenKey, oNode, m_nShowChildren);
	xml_GetAttibuteValue(pXmlKeys->m_strBringToTopKey, oNode, m_nBringToTop);
	xml_GetAttibuteValue(pXmlKeys->m_strBorderKey, oNode, m_nBorder);

	return 0;
}

long CUIWndLayer::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strShowChildrenKey, oElement, m_nShowChildren);
	xml_SetAttributeValue(pXmlKeys->m_strBringToTopKey, oElement, m_nBringToTop);
	xml_SetAttributeValue(pXmlKeys->m_strBorderKey, oElement, m_nBorder);
	return 0;
}

long CUIWndLayer::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowList::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nShowChildren);
		BinarySerializeCalLen(oBinaryBuffer, m_nBringToTop);
		BinarySerializeCalLen(oBinaryBuffer, m_nBorder);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nShowChildren);
		BinarySerializeRead(oBinaryBuffer, m_nBringToTop);
		BinarySerializeRead(oBinaryBuffer, m_nBorder);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nShowChildren);
		BinarySerializeWrite(oBinaryBuffer, m_nBringToTop);
		BinarySerializeWrite(oBinaryBuffer, m_nBorder);
	}

	return 0;
}

void CUIWndLayer::InitAfterRead()
{
	CUIWindowList::InitAfterRead();

	if (m_strType == _T("window"))
	{
		m_dwLayerType = LAYERTYPE_WINDOW;
		return;
	}

	if (m_strType == _T("group"))
	{
		m_dwLayerType = LAYERTYPE_GROUP;
		return;
	}
}

BOOL CUIWndLayer::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowList::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndLayer *p = (CUIWndLayer*)pObj;

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

	if(m_nBorder != p->m_nBorder)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndLayer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowList::CopyOwn(pDest);

	CUIWndLayer *p = (CUIWndLayer*)pDest;

	p->m_nShowChildren = m_nShowChildren;
	p->m_nBringToTop = m_nBringToTop;
	p->m_nBorder = m_nBorder;
	return TRUE;
}

CBaseObject* CUIWndLayer::Clone()
{
	CUIWndLayer *p = new CUIWndLayer();
	Copy(p);
	return p;
}

BOOL CUIWndLayer::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIWNDBITMAP)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDBUTTON)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDCHECKBOX)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDCOMBOBOX)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDLISTBOX)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDDATETIMECTRL)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDEDIT)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDLISTCTRL)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDSTATICTEXT)
	{
		return TRUE;
	}

	if (nClassID == UICLASSID_CUIWNDTIME)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIWndLayer::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCUIWndBitmapKey)
	{
		pNew = new CUIWndBitmap();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndButtonKey)
	{
		pNew = new CUIWndButton();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndCheckBoxKey)
	{
		pNew = new CUIWndCheckBox();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndListBoxKey)
	{
		pNew = new CUIWndListBox();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndComboBoxKey)
	{
		pNew = new CUIWndComboBox();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndDateTimeCtrlKey)
	{
		pNew = new CUIWndDateTimeCtrl();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndListCtrlKey)
	{
		pNew = new CUIWndListControl();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndEditKey)
	{
		pNew = new CUIWndEdit();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndStaticTextKey)
	{
		pNew = new CUIWndStaticText();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndTimeKey)
	{
		pNew = new CUIWndTime();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndFileMngrKey)
	{
		pNew = new CUIWndFileMngr();
	}
	else if (strClassID == pXmlKeys->m_strCUIWndRegisterKey)
	{
		pNew = new CUIWndRegister();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	pNew = CUIWindowList::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	return pNew;
}

CExBaseObject* CUIWndLayer::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIWNDBITMAP)
	{
		pNew = new CUIWndBitmap();
	}
	else if (nClassID == UICLASSID_CUIWNDBUTTON)
	{
		pNew = new CUIWndButton();
	}
	else if (nClassID == UICLASSID_CUIWNDCHECKBOX)
	{
		pNew = new CUIWndCheckBox();
	}
	else if (nClassID == UICLASSID_CUIWNDCOMBOBOX)
	{
		pNew = new CUIWndComboBox();
	}
	else if (nClassID == UICLASSID_CUIWNDLISTBOX)
	{
		pNew = new CUIWndListBox();
	}
	else if (nClassID == UICLASSID_CUIWNDLISTCTRL)
	{
		pNew = new CUIWndListControl();
	}
	else if (nClassID == UICLASSID_CUIWNDDATETIMECTRL)
	{
		pNew = new CUIWndDateTimeCtrl();
	}
	else if (nClassID == UICLASSID_CUIWNDEDIT)
	{
		pNew = new CUIWndEdit();
	}
	else if (nClassID == UICLASSID_CUIWNDSTATICTEXT)
	{
		pNew = new CUIWndStaticText();
	}
	else if (nClassID == UICLASSID_CUIWNDTIME)
	{
		pNew = new CUIWndTime();
	}
	else if (nClassID == UICLASSID_CUIWNDFILEMNGR)
	{
		pNew = new CUIWndFileMngr();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	pNew = CUIWindowList::CreateNewChild(nClassID);

	return pNew;
}

//////////////////////////////////////////////////////////////////////////

CUIWindowBase* CUIWndLayer::FindWindowByID(LPCTSTR pszWindowID)
{
	CString strWindID;
	strWindID = pszWindowID;
	return FindWindowByID(strWindID);
}

CUIWindowBase* CUIWndLayer::FindWindowByID(CString &strstrWindowID)
{
	return (CUIWindowBase*)FindByID(strstrWindowID);
}



//创建/销毁方法
BOOL CUIWndLayer::UICreate(CWnd *pParent)
{
	if (m_strType == _T("group"))
	{
		UICreateChildren(pParent);
	}
	else
	{
		CUIWindowList::UICreate(pParent);
	}

	Show(m_nShow);

	return TRUE;
}

BOOL CUIWndLayer::Show(long nShow)
{
	BOOL bChange = CUIWindowBase::Show(nShow);

	ShowChildren(nShow);

	if ((m_pWindow != NULL) && bChange && (m_nShow == 1))
	{
		m_pWindow->BringWindowToTop();
		m_pWindow->Invalidate();
		m_pWindow->SetFocus();
	}

	return bChange;
}


BOOL CUIWndLayer::IsWindowType()
{
	return m_dwLayerType == LAYERTYPE_WINDOW;
}

BOOL CUIWndLayer::IsGroupType()
{
	return m_dwLayerType == LAYERTYPE_GROUP;
}

