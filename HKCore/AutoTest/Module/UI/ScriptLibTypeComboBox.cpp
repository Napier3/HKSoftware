#include "StdAfx.h"
#include "ScriptLibTypeComboBox.h"
#include "..\GuideBook\GuideBook.h"
#include "..\XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CScriptLibTypeComboBox::CScriptLibTypeComboBox(void)
{
	m_pGuideBook = NULL;
}

CScriptLibTypeComboBox::~CScriptLibTypeComboBox(void)
{
}

void CScriptLibTypeComboBox::InitComboBox(CExBaseObject *pItem)
{
	if (pItem == NULL)
	{
		m_pGuideBook = NULL;
		return;
	}

	LONG nClassID = pItem->GetClassID();

	CExBaseObject *pGuideBook = NULL;

	if ( GBCLASSID_GUIDEBOOK == nClassID )
	{
		pGuideBook = pItem;
	}
	else
	{
		pGuideBook = (CExBaseObject*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	}

	if (m_pGuideBook == pGuideBook)
	{
		return;
	}

	m_pGuideBook = pGuideBook;
	ResetContent();

	long nIndex = AddString(/*_T("外部脚本库文件")*/g_sLangTxt_ExterScript);
	SetItemData(nIndex, 0);
	nIndex = AddString(/*_T("模板内部脚本库")*/g_sLangTxt_InterScript);
	SetItemData(nIndex, 1);
	SetCurSel(1);
}

CExBaseObject* CScriptLibTypeComboBox::GetScriptLib()
{
	long nSel = GetCurSel();
// 	ASSERT( m_pGuideBook != NULL);

	if (m_pGuideBook == NULL)
	{
		return NULL;
	}

	nSel = GetItemData(nSel);
	CGuideBook *pGuideBook = (CGuideBook*)m_pGuideBook;

	if (nSel == 0)
	{
		return pGuideBook->m_pScriptLibGlobal;
	}
	else
	{
		return pGuideBook->m_pScriptLibLocal;
	}
}
