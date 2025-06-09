#include "stdafx.h"
#include "GbItemReplaceTool.h"
#include "..\GuideBook\MacroTest.h"
#include "XItemReplaceSelectDlg.h"

//////////////////////////////////////////////////////////////////////////
CGbItemReplaceTool::CGbItemReplaceTool()
{
	m_pParentWnd = NULL;
}


CGbItemReplaceTool::~CGbItemReplaceTool()
{
	
}


BOOL CGbItemReplaceTool::UpdateMacroTestParaData(CGbItemBase *pMacroTest, CShortData  *pData, const CString &strMacroID, BOOL bShowLog)
{
	m_pGbCurrItem = pMacroTest;
	m_pReplaceRootItems = NULL;
	m_pGbSrcObj = pData;

	SelectReplaceRootItems();

	if (m_pReplaceRootItems == NULL)
	{
		return FALSE;
	}
	
	UpdateMacroTestParaData((CExBaseList*)m_pReplaceRootItems, pData, strMacroID, bShowLog);

	return TRUE;
}

void CGbItemReplaceTool::UpdateMacroTestParaData(CExBaseList *pItems, const CShortData  *pData, const CString &strMacroID, BOOL bShowLog)
{

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CExBaseObject*)pItems->GetNext(pos);
		nClassID = pItem->GetClassID() ;

		if (nClassID ==GBCLASSID_MACROTEST)
		{
			( (CMacroTest*)pItem)->UpdateMacroTestParaData(pData, strMacroID, bShowLog);
		}
		else if (nClassID ==GBCLASSID_ITEMS)
		{
			if (m_nMode == GBITEMREPLACE_MODE_ALL_CHILDREN)
			{
				UpdateMacroTestParaData((CExBaseList*)pItem, pData, strMacroID, bShowLog);
			}
		}
	}
}

BOOL CGbItemReplaceTool::UpdateScript(CGbItemBase *pGbItem, CScriptText  *pScript, const CString &strItemID, BOOL bShowLog)
{
	m_bUseSameID = strItemID.GetLength() > 0;
	m_strItemID = strItemID;

	m_pGbCurrItem = pGbItem;
	m_pReplaceRootItems = NULL;
	m_pGbSrcObj = pScript;

	SelectReplaceRootItems();

	if (m_pReplaceRootItems == NULL)
	{
		return FALSE;
	}

	UpdateScript((CExBaseList*)m_pReplaceRootItems, pScript, pGbItem->GetClassID(), pScript->GetClassID(), bShowLog);

	return TRUE;
}

BOOL CGbItemReplaceTool::UpdateDsvScript(CGbItemBase *pGbItem, CDsvScript  *pDsvScript, const CString &strCommCmdID, const CString &strNameHas, BOOL bShowLog)
{
	m_bUseSameID = strCommCmdID.GetLength() > 0;
	m_strItemID = strCommCmdID;

	m_pGbCurrItem = pGbItem;
	m_pReplaceRootItems = NULL;
	m_pGbSrcObj = pDsvScript;

	SelectReplaceRootItems();

	if (m_pReplaceRootItems == NULL)
	{
		return FALSE;
	}

	UpdateDsvScript((CExBaseList*)m_pReplaceRootItems, pDsvScript, strNameHas, bShowLog);

	return TRUE;
}


void CGbItemReplaceTool::SelectReplaceRootItems()
{
	CWnd *pParentWnd = m_pParentWnd;

	if (pParentWnd == NULL)
	{
		pParentWnd = CWnd::GetDesktopWindow();
	}

	CXItemReplaceSelectDlg dlg(pParentWnd);
	dlg.m_pTestItem = (CGbItemBase*)m_pGbCurrItem;//->GetParent();
	
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	m_pReplaceRootItems = (CItems*)dlg.m_pCurrSelObj;
	m_nMode = dlg.m_nMode;

	if (m_pReplaceRootItems != NULL)
	{
		if (m_pReplaceRootItems->GetClassID() == GBCLASSID_ITEMS || m_pReplaceRootItems->GetClassID() == GBCLASSID_DEVICE)
		{
		}
		else
		{
			m_pReplaceRootItems = NULL;
		}
	}
}

void CGbItemReplaceTool::UpdateScript(CExBaseList *pList, CScriptText  *pScript, UINT nClassItem, UINT nScriptClassID, BOOL bShowLog)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pItem = (CExBaseObject*)pList->GetNext(pos);
		nClassID = pItem->GetClassID() ;

		if (nClassID ==nClassItem)
		{
			if (m_bUseSameID)
			{
				if (m_strItemID == pItem->m_strID)
				{
					( (CGbItemBase*)pItem)->ReplaceSrciptText(pScript, nScriptClassID, m_pGbCurrItem, bShowLog);
				}
			}
			else
			{
				( (CGbItemBase*)pItem)->ReplaceSrciptText(pScript, nScriptClassID, m_pGbCurrItem, bShowLog);
			}
		}
		else if (nClassID ==GBCLASSID_ITEMS)
		{
			if (m_nMode == GBITEMREPLACE_MODE_ALL_CHILDREN)
			{
				UpdateScript((CExBaseList*)pItem, pScript, nClassItem, nScriptClassID, bShowLog);
			}
		}
	}
}

void CGbItemReplaceTool::UpdateDsvScript(CExBaseList *pList, CDsvScript  *pDsvScript, const CString &strNameHas, BOOL bShowLog)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *pItem = NULL;
	UINT nClassID = 0;
	CCommCmd *pCommCmd = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject*)pList->GetNext(pos);
		nClassID = pItem->GetClassID() ;

		if (nClassID == GBCLASSID_COMMCMD)
		{
			pCommCmd = (CCommCmd *)pItem;
			
			if (pCommCmd->m_strCommCmdID == m_strItemID)
			{
				if (strNameHas.GetLength() > 0)
				{
					if (pCommCmd->m_strName.Find(strNameHas) >= 0)
					{
						pCommCmd->ReplaceDsvScript(pDsvScript);
					}
				}
				else
				{
					pCommCmd->ReplaceDsvScript(pDsvScript);
				}
			}
		}
		else if (nClassID ==GBCLASSID_ITEMS || nClassID == GBCLASSID_MACROTEST)
		{
			if (m_nMode == GBITEMREPLACE_MODE_ALL_CHILDREN)
			{
				UpdateDsvScript((CExBaseList*)pItem, pDsvScript, strNameHas, bShowLog);
			}
		}
	}
}

