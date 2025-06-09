// DataAttrComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "DataAttrComboBox.h"


// CDataAttrComboBox

IMPLEMENT_DYNAMIC(CDataAttrComboBox, CComboBox)

CDataAttrComboBox::CDataAttrComboBox()
{
	m_pCommCmdStrcutAttrs = NULL;
}

CDataAttrComboBox::~CDataAttrComboBox()
{
}


BEGIN_MESSAGE_MAP(CDataAttrComboBox, CComboBox)
END_MESSAGE_MAP()



// CDataAttrComboBox 消息处理程序

void CDataAttrComboBox::InitDataAttrIDComboBox()
{
	long nItem = AddString(g_sLangTxt_AttrID_Value);//_T("数值(value)"));
	SetItemDataPtr(nItem, (void*)(&g_strDataAttrID_Value));

	nItem = AddString(g_sLangTxt_AttrID_Name);//_T("名称(name)"));
	SetItemDataPtr(nItem, (void*)(&g_strDataAttrID_Name));
	SetCurSel(0);
}


CString CDataAttrComboBox::GetDataAttrID()
{
	long nSel = GetCurSel();

	if (nSel == CB_ERR)
	{
		return g_strDataAttrID_Value;
	}

	if (nSel >= 2)
	{
		CCommCmdStrcutAttr *pAttr = (CCommCmdStrcutAttr*)GetItemDataPtr(nSel);
		ASSERT (pAttr != NULL);
		return pAttr->m_strID;
	}
	else
	{
		CString *pString = (CString*)GetItemDataPtr(nSel);
		return  *pString;
	}

}

void CDataAttrComboBox::InitCommCmdDataAttrs(const CString &strDataType)
{
	if (strDataType == m_strCurrDataType)
	{
		return;
	}

	if (strDataType == _T("struct"))
	{
		ASSERT (m_pCommCmdStrcutAttrs != NULL);
		POS pos = m_pCommCmdStrcutAttrs->GetHeadPosition();
		CCommCmdStrcutAttr *pAttr = NULL;
		long nIndex = 0;

		while (pos != NULL)
		{
			pAttr = (CCommCmdStrcutAttr *)m_pCommCmdStrcutAttrs->GetNext(pos);
			nIndex = AddString(pAttr->m_strName);
			SetItemDataPtr(nIndex, pAttr);
		}
	}
	else
	{
		int nRet = DeleteString(2);

		while (nRet >= 2)
		{
			nRet = DeleteString(2);
		}
	}

	m_strCurrDataType = strDataType;
}

