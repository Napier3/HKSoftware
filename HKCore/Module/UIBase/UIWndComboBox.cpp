//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndComboBox.cpp  CUIWndComboBox


#include "stdafx.h"
#include "UIWndComboBox.h"

CUIWndComboBox::CUIWndComboBox()
{
	//初始化属性
	m_nCurrIndex = 0;
	m_nSort = 0;

	//初始化成员变量
	m_pDatas = NULL;
	m_nIndex = 0;
}

CUIWndComboBox::~CUIWndComboBox()
{
}

long CUIWndComboBox::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlReadOwn(oNode, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCurrIndexKey, oNode, m_nCurrIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strSortKey, oNode, m_nSort);
	xml_GetAttibuteValue(pXmlKeys->m_strSourceKey, oNode, m_strSource);
	return 0;
}

long CUIWndComboBox::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CUIWindowBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCurrIndexKey, oElement, m_nCurrIndex);
	xml_SetAttributeValue(pXmlKeys->m_strSortKey, oElement, m_nSort);
	xml_SetAttributeValue(pXmlKeys->m_strSourceKey, oElement, m_strSource);
	return 0;
}

long CUIWndComboBox::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CUIWindowBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_nSort);
		BinarySerializeCalLen(oBinaryBuffer, m_strSource);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nCurrIndex);
		BinarySerializeRead(oBinaryBuffer, m_nSort);
		BinarySerializeRead(oBinaryBuffer, m_strSource);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nCurrIndex);
		BinarySerializeWrite(oBinaryBuffer, m_nSort);
		BinarySerializeWrite(oBinaryBuffer, m_strSource);
	}
	return 0;
}

void CUIWndComboBox::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CSHORTDATAS)
		{
			m_pDatas = (CShortDatas*)p;
		}
	}

	if (m_pDatas == NULL)
	{
		m_pDatas = (CShortDatas*)AddNewChild(new CShortDatas());
	}

	CUIWindowBase::InitAfterRead();
}

BOOL CUIWndComboBox::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CUIWindowBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CUIWndComboBox *p = (CUIWndComboBox*)pObj;

	if(m_nCurrIndex != p->m_nCurrIndex)
	{
		return FALSE;
	}

	if(m_nSort != p->m_nSort)
	{
		return FALSE;
	}

	if(m_strSource != p->m_strSource)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CUIWndComboBox::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CUIWindowBase::CopyOwn(pDest);

	CUIWndComboBox *p = (CUIWndComboBox*)pDest;

	p->m_nCurrIndex = m_nCurrIndex;
	p->m_nSort = m_nSort;
	p->m_strSource = m_strSource;
	return TRUE;
}

CBaseObject* CUIWndComboBox::Clone()
{
	CUIWndComboBox *p = new CUIWndComboBox();
    CUIWindowBase::Copy(p);
	return p;
}

BOOL CUIWndComboBox::CanPaste(UINT nClassID)
{
	if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CUIWndComboBox::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUIBaseXmlRWKeys *pXmlKeys = (CUIBaseXmlRWKeys*)pXmlRWKeys;
	

	if (strClassID == pXmlKeys->m_strCShortDatasKey)
	{
		pNew = new CShortDatas();
	}

	return pNew;
}

CExBaseObject* CUIWndComboBox::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		pNew = new CShortDatas();
	}

	return pNew;
}

BOOL CUIWndComboBox::UICreate(CWnd *pParent)
{
	if ( m_pWindow != NULL )
	{
		LOG_WriteLawString("recreate button");
	}

	CRect rect = GetWndPosition();
	rect.bottom += 100;
	BOOL status = FALSE;

	if (m_nSort)
	{
		status = Create(
			WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST|CBS_SORT,
			rect,
			pParent,
			GenerateWindowID());
	}
	else
	{
		status = Create(
			WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST,
			rect,
			pParent,
			GenerateWindowID());
	}
	if ( !status )
	{
		return FALSE;
	}

	m_nIndex = m_pDatas->GetCount();

	if (m_nCurrIndex >= m_nIndex) 
	{
		m_nCurrIndex = 0;
	}

	for(int nIndex = 0; nIndex < m_nIndex ; nIndex ++)
	{
		CExBaseObject  *pData = m_pDatas->GetAt(nIndex);
		CString strData = pData->m_strName;
		this->AddString(strData);
	}

	SetCurSel(m_nCurrIndex);

	CUIBaseFont *pUIFont = GetUIBaseFont();      //获取当前的Font

	if (pUIFont != NULL)
	{
		CFont *pFont = pUIFont->GetFont();
		SetFont(pFont);
	}

	ShowWindow(SW_SHOW);

	m_pWindow = this;

	return TRUE;
}

BOOL CUIWndComboBox::Destroy()
{
	if (m_pWindow != NULL)
	{
		DestroyWindow();
		m_pWindow = NULL;
	}

	return TRUE;
}