//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndComboBox.cpp  CUIWndComboBox


#include "stdafx.h"
#include "UIWndListBox.h"

CUIWndListBox::CUIWndListBox()
{
	
}

CUIWndListBox::~CUIWndListBox()
{
}

long CUIWndListBox::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndListBox::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CUIWndListBox::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
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

void CUIWndListBox::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == UICLASSID_CUIBASEITEMS)
		{
			m_pItems = (CUIBaseItems *)p;
		}
	}

	if (m_pItems == NULL)
	{
		m_pItems = (CUIBaseItems*)AddNewChild(new CUIBaseItems());
	}

	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndListBox::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndListBox *p = (CUIWndListBox*)pObj;


	return TRUE;
}

BOOL CUIWndListBox::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndListBox *p = (CUIWndListBox*)pDest;

	return TRUE;
}

CBaseObject* CUIWndListBox::Clone()
{
	CUIWndListBox *p = new CUIWndListBox();
    CUIWindowBase::Copy(p);
	return p;
}

BOOL CUIWndListBox::CanPaste(UINT nClassID)
{
	if (nClassID == UICLASSID_CUIBASEITEMS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIWndListBox::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	

	if (strClassID == pXmlKeys->m_strCUIBaseItemsKey)
	{
		pNew = new CUIBaseItems();
	}

	return pNew;
}

CExBaseObject* CUIWndListBox::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == UICLASSID_CUIBASEITEMS)
	{
		pNew = new CUIBaseItems();
	}

	return pNew;
}

BOOL CUIWndListBox::UICreate(CWnd *pParent)
{
	if ( m_pWindow != NULL )
	{
		LOG_WriteLawString("recreate button");
	}

	CRect rect = GetWndPosition();
	rect.bottom += 100;
	BOOL status = FALSE;

	status = Create(
			WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,
			rect,
			pParent,
			GenerateWindowID());
	
	if ( !status )
	{
		return FALSE;
	}


	CUIBaseFont *pUIFont = GetUIBaseFont();      //获取当前的Font

	if (pUIFont != NULL)
	{
		CFont *pFont = pUIFont->GetFont();
		SetFont(pFont);
	}

	InsertDatas();

	ShowWindow(SW_SHOW);

	m_pWindow = this;

	return TRUE;
}

BOOL CUIWndListBox::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}

void CUIWndListBox::InsertDatas()
{
	int nCount = m_pItems->GetCount();

	for(int nIndex= 0; nIndex < nCount ; nIndex ++)
	{
		CUIBaseItem  *pItem = (CUIBaseItem *)m_pItems->GetAt(nIndex);
		CString data = pItem->GetText();
		this->AddString(data);
	}
}