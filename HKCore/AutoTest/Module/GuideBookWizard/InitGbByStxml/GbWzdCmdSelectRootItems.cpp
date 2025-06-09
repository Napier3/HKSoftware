#include "stdafx.h"
#include "GbWzdCmdSelectRootItems.h"
#include "..\GbWzdCmdInitGbByStxmlFile.h"
#include "..\..\XLanguageResourceAts.h"
#include "..\GuideBookWizard.h"

CGbWzdCmdSelectRootItems::CGbWzdCmdSelectRootItems()
{
	m_strName = _T("");
	m_strID = _T("");
}


CGbWzdCmdSelectRootItems::~CGbWzdCmdSelectRootItems()
{
	
}


BOOL CGbWzdCmdSelectRootItems::Execute(DWORD dwExecMode)
{
	CGbWzdCmd::Execute(dwExecMode);
	
	CTreeCtrl *pGbTree = GetGuideBookEditTreeCtrl();
	CDevice *pDevice = GetDevice();
	ASSERT (pDevice != NULL);

	if (pDevice != NULL)
	{
		pGbTree->SendMessage(WM_USER + 1055, (WPARAM)pDevice, (LPARAM)pDevice);
	}

	CFrameWnd* pFrameWnd = GetMaiFrame();
	CExBaseList *pSel = (CExBaseList*)pFrameWnd->SendMessage(WM_GBWZD_GET_FROM_FRAME, (WPARAM)this, (LPARAM)this);
	ShowGbWzdMsg(/*_T("选择测试子模板插入的位置，合法的位置为“设备”和“项目分类”")*/g_sLangTxt_SelTestSubTemInsert);

	CGbWzdCmdInitGbByStxmlFile *pGbWzdCmdInitGbByStxmlFile = (CGbWzdCmdInitGbByStxmlFile*)GetAncestor(GBWZDCLASSID_INITGBBYSTXML);
	ASSERT (pGbWzdCmdInitGbByStxmlFile != NULL);

	if (pGbWzdCmdInitGbByStxmlFile->OnGbNodeSelChange(pSel))
	{
		BOOL bEnable = pGbWzdCmdInitGbByStxmlFile->GetRootItems() != NULL;
		GetGbWzdWnd()->PostMessage(WM_EXEC_GBWZD_NEXT_ENABLE, bEnable ,bEnable);
	}

	//自动拼接模板  shaol  2019.04.24
	if  (CGuideBookWizard::IsGbWzdAuto() && CGuideBookWizard::IsGbWzdAuto_Auto())
	{
		CFrameWnd *pFrameWnd = GetMaiFrame();
		pFrameWnd->PostMessage(WM_EXEC_GBWZD_EXEC_NEXT, 0, 0);
	}

	return TRUE;
}

void CGbWzdCmdSelectRootItems::GetCmdInfor(CString &strText)
{
	CGbWzdCmdInitGbByStxmlFile *p = (CGbWzdCmdInitGbByStxmlFile*)GetAncestor(GBWZDCLASSID_INITGBBYSTXML);
	ASSERT (p != NULL);
	strText.Format(/*_T("%s: 选择测试子模板插入的位置")*/g_sLangTxt_SelTestSubTemInsert2, p->m_strName);
	//CGbWzdCmd::GetCmdInfor(strText);
}

BOOL CGbWzdCmdSelectRootItems::IsCmdFinish()
{
	m_nCmdExecState = GBWZDCMD_STATE_FINISH;
	return TRUE;
}


long CGbWzdCmdSelectRootItems::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	return 0;
}

long CGbWzdCmdSelectRootItems::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

long CGbWzdCmdSelectRootItems::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return 0;
}

BSTR CGbWzdCmdSelectRootItems::GetXmlElementKey()
{
	return CGbWzdToolXmlRWKeys::CGbWzdCmdSelectRootItemsKey();
}


BOOL CGbWzdCmdSelectRootItems::IsEqual(CBaseObject* pObj)
{
	return TRUE;
}

BOOL CGbWzdCmdSelectRootItems::CopyOwn(CBaseObject* pDesObj)
{
	return TRUE;
}

CBaseObject* CGbWzdCmdSelectRootItems::Clone()
{
	CGbWzdCmdSelectRootItems *pNew = new CGbWzdCmdSelectRootItems();
	Copy(pNew);
	return pNew;
}

