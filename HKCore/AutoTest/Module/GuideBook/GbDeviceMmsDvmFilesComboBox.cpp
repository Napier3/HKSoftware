#include "StdAfx.h"
#include "GbDeviceMmsDvmFilesComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CTLinkListEx<CGbDeviceMmsDvmFilesComboBox>  g_listCoboBox; 

CFilterTextMngr* CGbDeviceMmsDvmFilesComboBox::g_pFilterTextMngr = NULL;
long CGbDeviceMmsDvmFilesComboBox::g_nFilterTextMngrRef = 0;


CGbDeviceMmsDvmFilesComboBox::CGbDeviceMmsDvmFilesComboBox(void)
{

}

CGbDeviceMmsDvmFilesComboBox::~CGbDeviceMmsDvmFilesComboBox(void)
{
	g_listCoboBox.Remove(this);
	g_nFilterTextMngrRef--;

	if (g_nFilterTextMngrRef == 0)
	{
		delete g_pFilterTextMngr;
		g_pFilterTextMngr = NULL;
	}
}

void CGbDeviceMmsDvmFilesComboBox::InitGbDeviceMmsDvmFiles(const CString &strFile)
{
	g_nFilterTextMngrRef++;

	if (g_pFilterTextMngr == NULL)
	{
		g_pFilterTextMngr = new CFilterTextMngr();
		CString strPath;
		strPath = _P_GetConfigPath();

		if (strFile.GetLength() < 5)
		{
			strPath += _T("GbDeviceMmsDvmFiles.xml");
		}

		g_pFilterTextMngr->OpenXmlFile(strPath);
	}

	g_listCoboBox.AddTail(this);
	InitFilterText(g_pFilterTextMngr);
	SetCurSel(0);
}

void CGbDeviceMmsDvmFilesComboBox::BringCurrToTop()
{
	CExBaseObject *pSel = GetCurrSelObject();

	if (pSel != NULL)
	{
		g_pFilterTextMngr->BringToHead(pSel);
		g_pFilterTextMngr->SaveXmlFile();
	}
}

void CGbDeviceMmsDvmFilesComboBox::OnRbtnDelete()
{
	long nIndex = GetCurSel();

	if (nIndex == CB_ERR)
	{
		return ;
	}

	CFilterText *pSel = (CFilterText *)GetItemDataPtr(nIndex);

	if (pSel == NULL)
	{
		return ;
	}

	CGbDeviceMmsDvmFilesComboBox *pComboBox = NULL;
	POS pos = g_listCoboBox.GetHeadPosition();

	while (pos != NULL)
	{
		pComboBox = g_listCoboBox.GetNext(pos);
		pComboBox->DeleteObject(pSel);
	}
	
	m_pList->Delete(pSel);
	SaveFilterText();
}

void CGbDeviceMmsDvmFilesComboBox::AddFilterText(CFilterText *pText)
{
	CGbDeviceMmsDvmFilesComboBox *pComboBox = NULL;
	POS pos = g_listCoboBox.GetHeadPosition();

	while (pos != NULL)
	{
		pComboBox = g_listCoboBox.GetNext(pos);
		pComboBox->AddObj(pText);
	}
}


CFilterText* CGbDeviceMmsDvmFilesComboBox::AddFilterText(CString &strFilterText)
{
	return CFilterTextComboBox::AddFilterText(strFilterText);
// 	CFilterText *pNew = NULL;
// 
// 	if (m_pList->FindByID(strFilterText) == NULL)
// 	{
// 		CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
// 		CFilterText *pNew = pFilterTextMngr->AddText(strFilterText);
// 		AddFilterText(pNew);
// 		SaveFilterText();
// 	}
// 
// 	return pNew;
}


void CGbDeviceMmsDvmFilesComboBox::GetAddString(CString &strText)
{
	if (m_strPrevfixText.GetLength() > 0)
	{
		GetRelativePathTo(strText, m_strPrevfixText, strText);
		//strText = strText.Mid(m_strPrevfixText.GetLength());
	}
}

CString CGbDeviceMmsDvmFilesComboBox::GetAddString2(const CString &strText)
{
	if (m_strPrevfixText.GetLength() > 0)
	{
		CString strRet = strText;
		GetRelativePathTo(m_strPrevfixText, strText, strRet);
		return strRet;
	}
	else
	{
		return strText;
	}
}


CFilterText* CGbDeviceMmsDvmFilesComboBox::PopOpenDvmDlg(CString &strPath, CWnd *pParentWnd, const CString &strCaption)
{
	CString strFilePath = strPath;

	if (strFilePath.GetLength() < 3)
	{
		strFilePath = _P_GetLibraryPath();
		strFilePath += _T("*.xml");
	}

	CFilterText *pFilterText = NULL;

	if (pParentWnd == NULL)
	{
		pParentWnd = GetParent();
	}

	BOOL bRet = ats_GetDeviceModeleFiles(strFilePath, pParentWnd, strCaption);

	if ( bRet )
	{
		CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
		long nCount = pFilterTextMngr->GetCount();
		pFilterText = pFilterTextMngr->AddText(strFilePath);
		long nCount2 = pFilterTextMngr->GetCount();

		pFilterTextMngr->BringToHead(pFilterText);

		if (nCount2 != nCount)
		{
			pFilterTextMngr->SaveXmlFile();
			AddFilterText(pFilterText);
		}
		else
		{
			BringCurrToTop();
		}

		SelectFilterText(pFilterText);
		strPath = strFilePath;
	}

	return pFilterText;
}

//2021-1-8  lijunqing
BOOL CGbDeviceMmsDvmFilesComboBox::DeleteCurrSelObject()
{
	if (CExBaseListComboBox::DeleteCurrSelObject())
	{
		CFilterTextMngr *pFilterTextMngr = (CFilterTextMngr*)m_pList;
		pFilterTextMngr->SaveXmlFile();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

