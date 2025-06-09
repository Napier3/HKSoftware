#include "stdafx.h"
#include "ExBaseOptrGlobalFunc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CExBaseObject* DB_Insert_Base_Func(CExBaseObject *pNewObj, CExBaseList *pCurrList
								   , CExBaseCtrlOptrInterface *pCtrlOptr)
{
	CExBaseList *pNewParent = (CExBaseList*)pCurrList->CloneEx(FALSE, FALSE);
	CExBaseObject *pNewTemp  = (CExBaseObject*)pNewObj->CloneEx(TRUE, FALSE);
	pNewParent->AddTail(pNewTemp);
	CExBaseObject *pNewRet = NULL;

	//Optr_InsertData函数，如果成功，则销毁了pNewObj，并且新建了一个新的T2对象
	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_InsertData(*pNewParent);

	if (bRes)
	{
		pNewRet = (CExBaseObject *)pNewParent->GetHead();//->Clone();  //lijunqing 2019-4-11
		pCurrList->AddNewChild(pNewRet);		//将新对象插入本地库父对象
		pNewParent->RemoveHead();

		//在表格中插入新对象
		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_InsertData(pNewRet);
		}
	}

	delete pNewParent;
	return pNewRet;
}

BOOL DB_Edit_Base_Func(CExBaseObject *pTempObj, CExBaseObject *pCurrEditObj
						 , CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr, BOOL bPkUpdate)
{
	CExBaseList *pNewParent = (CExBaseList*)pCurrList->CloneEx(FALSE, FALSE);
	CExBaseObject *pNewTemp  = NULL;
	BOOL bRes = FALSE;

	if (bPkUpdate)
	{
		pNewTemp  = (CExBaseObject*)pCurrEditObj->CloneEx(TRUE, FALSE);
		pNewParent->AddTail(pNewTemp);
		bRes = g_pExBaseDataOptrBaseApp->Optr_DeleteData(*pNewParent, QUERY_TABLE_OWN);
		pNewParent->DeleteAll();

		pNewTemp  = (CExBaseObject*)pTempObj->CloneEx(TRUE, FALSE);
		pNewParent->AddTail(pNewTemp);
		bRes = g_pExBaseDataOptrBaseApp->Optr_InsertData(*pNewParent);

		if (bRes)
		{
			pNewTemp = pNewParent->GetHead();
		}
	}
	else
	{
		pNewTemp  = (CExBaseObject*)pTempObj->CloneEx(TRUE, FALSE);
		pNewParent->AddTail(pNewTemp);
		bRes = g_pExBaseDataOptrBaseApp->Optr_UpdateData(*pNewParent);
	}

	if (bRes)
	{
		pNewTemp->CopyOwn(pCurrEditObj);

		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_UpdateData(pCurrEditObj);
		}
	}

	delete pNewParent;
	return bRes;
}
// 
// CExBaseObject *FindByNameEx(CExBaseList *pList, const CString &strName, UINT nClassID)
// {
// 	CExBaseObject* pTemp = NULL;
// 	CExBaseObject* pFind = NULL;
// 
// 	POS pos = pList->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pTemp = pList->GetNext(pos);
// 
// 		if (pTemp->m_strName == strName && pTemp->GetClassID() == nClassID)
// 		{
// 			pFind = pTemp;
// 			break;
// 		}
// 	}
// 
// 	return pFind;
// }
#ifndef _PSX_IDE_QT_			//add by yyj at 20200416 begin
CExBase_EditDlgBase::CExBase_EditDlgBase(UINT nIDD, CWnd* pParent /*=NULL*/)
: CDialog(nIDD, pParent)
{
	m_pRefData = NULL;
	m_pCurrData = NULL;
	m_pParent = NULL;
	m_pDB_Insert_Base_Func = NULL;
	m_pDB_Edit_Base_Func = NULL;
	m_pRetData = NULL;
	m_pExBaseCtrlOptr = NULL;
}

CExBase_EditDlgBase::~CExBase_EditDlgBase()
{
}

void CExBase_EditDlgBase::SetEditObj(CExBaseObject* pEditObj, CExBaseObject *pRefObject, CExBaseList *pParentList)
{
	//确保调试模式下，当pParentList==NULL的时候，能够告警
	ASSERT (pParentList != NULL);

	m_pCurrData =pEditObj;
	m_pRefData = pRefObject;

	if (pParentList == NULL)
	{
		if (pRefObject != NULL)
		{
			m_pParent = (CExBaseList *)pRefObject->GetParent();
		}
	}
	else
	{
		m_pParent = pParentList;	
	}
}

BOOL CExBase_EditDlgBase::ValidateData()
{
	GetEditData();

	if (m_pRefData == NULL)
	{
		return ValidateData_New();
	}
	else
	{
		return ValidateData_Edit();
	}
}

BOOL CExBase_EditDlgBase::ValidateData_New()
{
	CExBaseObject *p = NULL;

	p = (CExBaseObject*)m_pParent->FindByName(m_pCurrData->m_strName);

	return (p == NULL);
}

BOOL CExBase_EditDlgBase::ValidateData_Edit()
{
	POS pos = m_pParent->GetHeadPosition();
	CExBaseObject *p = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		p = m_pParent->GetNext(pos);

		if (p->m_strName == m_pCurrData->m_strName)
		{
			if (p == m_pRefData)
			{
				continue;
			}
			else
			{
				bTrue = FALSE;
				break;
			}
		}
	}

	return bTrue;
}

BOOL CExBase_EditDlgBase::ValidateExBaseObjectNameAndPk_New(const CString &strName)
{
	CString strMsg;
	BOOL bTrue = DB_ValidateExBaseObjectNameAndPk_New(m_pCurrData, strName, strMsg);

	if (!bTrue)
	{
		MessageBox( strMsg,_T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}

	return bTrue;
}

BOOL CExBase_EditDlgBase::ValidateExBaseObjectNameAndPk_Edit(const CString &strName)
{
	CString strMsg;
	BOOL bTrue = DB_ValidateExBaseObjectNameAndPk_Edit(m_pCurrData, m_pRefData, strName, strMsg);

	if (!bTrue)
	{
		MessageBox( strMsg,_T("提示"), MB_OK | MB_ICONEXCLAMATION);
	}

	return bTrue;
}

BOOL CExBase_EditDlgBase::IsPkValueChanged()
{
	ASSERT (m_pRefData != NULL);
	CXDb_PKeyValue oPkVal1, oPkVal2;
	m_pCurrData->Db_GetPkeyValue(oPkVal1);
	m_pRefData->Db_GetPkeyValue(oPkVal2);

	if (oPkVal1 == oPkVal2)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

void CExBase_EditDlgBase::OnOK()
{
	if (!ValidateData())
	{
		return;
	}

	if (IsNewMode())
	{//新建模式

		if (m_pDB_Insert_Base_Func != NULL)
		{
			m_pRetData = m_pDB_Insert_Base_Func(m_pCurrData, m_pParent, m_pExBaseCtrlOptr);

			if (m_pRetData == NULL)
			{
				return;
			}
		}

		CDialog::OnOK();
	}
	else
	{
		if (m_pRefData->IsEqualOwn(m_pCurrData))
		{//编辑模式下，如果两个数据对象完全相同，则不处理
			CDialog::OnCancel();
			return;
		}

		if (m_pDB_Edit_Base_Func != NULL)
		{
			BOOL bRet = m_pDB_Edit_Base_Func(m_pCurrData,m_pRefData
												, m_pParent, m_pExBaseCtrlOptr
												, IsPkValueChanged());

			if (bRet == FALSE)
			{
				return;
			}
		}

		CDialog::OnOK();
	}
}
#endif					//add by yyj at 20200416 end
//////////////////////////////////////////////////////////////////////////
//
BOOL Db_Validate_New_MsgBox(CExBaseList *pParent, CExBaseObject *pCurrObj, CWnd *pParentWnd, BOOL bValidateName, BOOL bValidateID)
{
	if (pParentWnd == NULL)
	{
		pParentWnd = CWnd::GetDesktopWindow();
	}

	if (!pParent->ValidateForNew(pCurrObj, bValidateName, bValidateID))
	{
		CString strMsg;
		strMsg.Format(_T("新建的对象【%s】与现有的对象存在冲突"),pCurrObj->m_strName);
		pParentWnd->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL Db_Validate_New_MsgBox(CExBaseList *pParent, CExBaseObject *pRefData, CExBaseObject *pCurrObj, CWnd *pParentWnd, BOOL bValidateName, BOOL bValidateID)
{
	if (pParentWnd == NULL)
	{
		pParentWnd = CWnd::GetDesktopWindow();
	}

	if (!pParent->ValidateForNew(pCurrObj, bValidateName, bValidateID))
	{
		CString strMsg;
		strMsg.Format(_T("新建的对象【%s】与现有的对象存在冲突"),pCurrObj->m_strName);
		pParentWnd->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


void Db_Validate_Edit_MsgBox(CExBaseObject *pCurrObj, CWnd *pParentWnd)
{
	if (pParentWnd == NULL)
	{
		pParentWnd = CWnd::GetDesktopWindow();
	}

	CString strMsg;
	strMsg.Format(_T("编辑的对象【%s】与现有的对象存在冲突"),pCurrObj->m_strName);
	pParentWnd->MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONEXCLAMATION);
}


BOOL Db_Validate_Edit_MsgBox(CExBaseList *pParent, CExBaseObject *pCurrObj, CWnd *pParentWnd, BOOL bValidateName, BOOL bValidateID)
{
	if (!pParent->ValidateForEdit(pCurrObj, bValidateName, bValidateID))
	{
		Db_Validate_Edit_MsgBox(pCurrObj, pParentWnd);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

BOOL Db_Validate_Edit_MsgBox(CExBaseList *pParent, CExBaseObject *pRefData, CExBaseObject *pCurrObj, CWnd *pParentWnd, BOOL bValidateName, BOOL bValidateID)
{
	if (!pParent->ValidateForEdit(pRefData, pCurrObj, bValidateName, bValidateID))
	{
		Db_Validate_Edit_MsgBox(pCurrObj, pParentWnd);
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
