#include "stdafx.h"
#include "GuideBookDevGlobalDefine.h"

BOOL GbUI_HasSameChildGrid(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2)//只用来判断表格标题是否相同
{
	if (pGbNode1 == NULL || pGbNode2 == NULL)
	{
		return FALSE;
	}

	if (pGbNode2->GetClassID() == GBCLASSID_SAFETY)
	{
		return FALSE;
	}

	if (pGbNode2->GetClassID() == pGbNode1->GetClassID())
	{
		return TRUE;
	}

	return FALSE;
}
 
BOOL GbUI_HasSameChildOptrBar(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2)
{
	return GbUI_HasSameChildGrid(pGbNode1, pGbNode2);
}

//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit)
//{
//	ASSERT(pItem != NULL);
//	CExBaseList* pParent = (CExBaseList*)pItem->GetParent();
//	ASSERT(pParent != NULL);
//	
//	pWnd->UpdateData(TRUE);
//	CString strInputID;
//	pEdit->GetWindowText(strInputID);
//	
//	CString strInfo;
//	if(strInputID.IsEmpty())
//	{
//		strInfo.Format(_T("%s 的ID不能为空"),pItem->m_strID);
//		pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//		pEdit->SetWindowText(pItem->m_strID);
//
//		return FALSE;
//	}
//
//	if(pItem->m_strID != strInputID)
//	{
//		if(pParent->FindByID(strInputID) != NULL)
//		{
//			CString strInfo;
//			strInfo.Format(_T("ID为 %s 的对象已经存在"),strInputID);
//			pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//			pEdit->SetWindowText(pItem->m_strID);
//
//			return FALSE;
//		}
//	}
//	
//	return TRUE;
//}
//
//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputID)
//{
//	ASSERT(pItem != NULL);
//	CExBaseList* pParent = (CExBaseList*)pItem->GetParent();
//	ASSERT(pParent != NULL);
//
//	CString strInfo;
//	if(strInputID.IsEmpty())
//	{
//		strInfo.Format(_T("%s 的ID不能为空"),pItem->m_strID);
//		pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//
//		return FALSE;
//	}
//
//	if(pItem->m_strID != strInputID)
//	{
//		if(pParent->FindByID(strInputID) != NULL)
//		{
//			CString strInfo;
//			strInfo.Format(_T("ID为 %s 的对象已经存在"),strInputID);
//			pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//
//			return FALSE;
//		}
//	}
//
//	pItem->m_strID = strInputID;
//
//	return TRUE;
//}
//
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit)
//{
//	ASSERT(pItem != NULL);
//	CExBaseList* pParent = (CExBaseList*)pItem->GetParent();
//	ASSERT(pParent != NULL);
//
//	pWnd->UpdateData(TRUE);
//	CString strInputName;
//	pEdit->GetWindowText(strInputName);
//	
//	CString strInfo;
//	if(strInputName.IsEmpty())
//	{
//		strInfo.Format(_T("%s 的名称不能为空"),pItem->m_strName);
//		pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//		pEdit->SetWindowText(pItem->m_strName);
//
//		return FALSE;
//	}
//
//	if(pItem->m_strName != strInputName)
//	{
//		if(pParent->FindByName(strInputName) != NULL)
//		{
//			CString strInfo;
//			strInfo.Format(_T("名称为 %s 的对象已经存在"),strInputName);
//			pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//			pEdit->SetWindowText(pItem->m_strName);
//
//			return FALSE;
//		}
//	}
//
//	return TRUE;
//}
//
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputName)
//{
//	ASSERT(pItem != NULL);
//	CExBaseList* pParent = (CExBaseList*)pItem->GetParent();
//	ASSERT(pParent != NULL);
//
//	CString strInfo;
//	if(strInputName.IsEmpty())
//	{
//		strInfo.Format(_T("%s 的名称不能为空"),pItem->m_strName);
//		pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//
//		return FALSE;
//	}
//
//	if(pItem->m_strName != strInputName)
//	{
//		if(pParent->FindByName(strInputName) != NULL)
//		{
//			CString strInfo;
//			strInfo.Format(_T("名称为 %s 的对象已经存在"),strInputName);
//			pWnd->MessageBox(strInfo,_T("错误"),MB_OK | MB_ICONWARNING);
//
//			return FALSE;
//		}
//	}
//
//	pItem->m_strName = strInputName;
//
//	return TRUE;
//}

BOOL Gb_AvoidSameIDName(CExBaseList* pParent,CExBaseObject* pObj)
{
	CString strName = pObj->m_strName;
	CString strID = pObj->m_strID;
	CString strNewName = strName;

	int nIndex = 1;
	while(pParent->FindByName(strNewName) != NULL)
	{
		strNewName.Format(_T("%s%d"),strName,nIndex++);
	}
	pObj->m_strName = strNewName;

	nIndex = 1;
	CString strNewID = strID;
	while (pParent->FindByID(strNewID) != NULL)
	{
		strNewID.Format(_T("%s%d"),strID,nIndex++);
	}
	pObj->m_strID = strNewID;

	return TRUE;
}

BOOL GBUI_NodeCanDelete(CExBaseObject* pObj)
{
	if(pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();
	BOOL bFlag = TRUE;

	if(nClassID == GBCLASSID_ANALOGS || nClassID == GBCLASSID_SETS || nClassID == GBCLASSID_CTRLWORDS 
	|| nClassID == GBCLASSID_SOFTSWITCHS || nClassID == GBCLASSID_BINARYINS || nClassID == GBCLASSID_BINARYOUTS || nClassID == GBCLASSID_SOES
	|| nClassID == GBCLASSID_DEVICE_SYSPARAS || nClassID == GBCLASSID_DEVICE_TESTPARAS || nClassID == GBCLASSID_JOBGUIDE || nClassID == GBCLASSID_GUIDEBOOK
	//|| nClassID == GBCLASSID_CPUS
	|| nClassID == GBCLASSID_GBTDATAINTERFACES || nClassID == CHARCLASSID_CCHARACTERISTICS || nClassID == GBCLASSID_GBTDATAS)
	{
		bFlag = FALSE;
	}

	return bFlag;
}

BOOL GBUI_UpdateJobGuidePaste(CExBaseObject* pCurSel,CExBaseObject* pCopyObj)
{
	BOOL bFlag = FALSE;

	UINT nClassID = pCopyObj->GetClassID();
	switch(nClassID)
	{
	case GBCLASSID_SAFETY:
		if(pCurSel->GetClassID() == GBCLASSID_JOBGUIDE || pCurSel->GetClassID() == GBCLASSID_ITEMS)
		{
			return TRUE;
		}
		break;
	case GBCLASSID_MSG:
		if(pCurSel->GetClassID() == GBCLASSID_SAFETY)
		{
			return TRUE;
		}
		break;
	case GBCLASSID_ITEMS:
		if(pCurSel->GetClassID() == GBCLASSID_JOBGUIDE)
		{
			return TRUE;
		}
		break;
	default:
		return FALSE;
	}

	return bFlag;
}

//lijq 2020-03-03  调试监视作业指导书节点显示的时间
BOOL g_bLogGbNodeShowTimeLong = FALSE;

