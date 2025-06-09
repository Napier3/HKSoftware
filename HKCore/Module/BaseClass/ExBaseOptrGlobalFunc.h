#pragma once

#include "ExBaseOptrInterface.h"
#include "DBOptrBaseDefine.h"	//add by yyj at 20200416

typedef CExBaseObject* LP_DB_INSERT_BASE_FUNC(CExBaseObject *pNewObj
											  , CExBaseList *pCurrList
											  , CExBaseCtrlOptrInterface *pCtrlOptr);
typedef BOOL LP_DB_MODIFY_BASE_FUNC(CExBaseObject *pTempObj
									, CExBaseObject *pCurrEditObj
									, CExBaseList *pCurrList
									, CExBaseCtrlOptrInterface *pCtrlOptr
									, BOOL bPkUpdate);

CExBaseObject* DB_Insert_Base_Func(CExBaseObject *pNewObj, CExBaseList *pCurrList
								   , CExBaseCtrlOptrInterface *pCtrlOptr);
BOOL DB_Edit_Base_Func(CExBaseObject *pTempObj, CExBaseObject *pCurrEditObj
						 , CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr, BOOL bPkUpdate);

/*
**T1:���϶��󣬴��������ĸ�������;
**T2:����������ݶ����࣬�Ӷ�����;
**pNewObj:Ҫ�����ĵ�ǰ����
**pCurrList:�����������ڵ�����
**pCtrlOptr:���϶���pCurrList��ʾ�Ľ�������ؼ�����
*/

template <class T1, class T2>
inline CExBaseObject* DB_Insert_Base(CExBaseObject *pNewObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	T1 tempList;
	tempList.AddTail(pNewObj);

	//Optr_InsertData����������ɹ�����������pNewObj�������½���һ���µ�T2����
	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_InsertData(tempList);

	if (bRes)
	{
		CExBaseObject *pNew = (CExBaseObject *)tempList.GetHead();//->Clone();  //lijunqing 2019-4-11
		pCurrList->AddNewChild(pNew);		//���¶�����뱾�ؿ⸸����
		tempList.RemoveHead();

		//�ڱ���в����¶���
		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_InsertData(pNew);
		}

		return pNew;
	}
	else
	{
		return NULL;
	}
}


template <class T1, class T2>
inline BOOL DB_Insert_Base_Own(CExBaseObject *pNewObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	CExBaseObject *pNew = (CExBaseObject*)pNewObj->CloneEx(TRUE, FALSE);
	T1 tempList;
	tempList.AddTail(pNew);

	//Optr_InsertData����������ɹ�����������pNewObj�������½���һ���µ�T2����
	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_InsertData(tempList);

	if (bRes)
	{
		pNew = (CExBaseObject *)tempList.GetHead();
		pNew->CopyOwn(pNewObj);  //ʹ��CopyOwn���ǿ�����������ļ������������Ҫ�������ݿ��ļ������·��
		pNewObj->DB_InitNameAttrs();

		if (pCurrList != NULL)
		{
			pCurrList->AddNewChild(pNewObj);	//���¶�����뱾�ؿ⸸����
		}

		//�ڱ���в����¶���
		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_InsertData(pNewObj);
		}
	}

	return bRes;
}

#ifndef _PSX_IDE_QT_
template <class T1, class T2, class TDlg>
inline CExBaseObject* DB_Insert_Base_Dlg(CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	TDlg dlg;
	CExBaseObject *pRet = NULL;
	T2* pNewObj = new T2;
	pNewObj->SetParent(pCurrList);
	dlg.SetEditObj(pNewObj, NULL, pCurrList);
	dlg.m_pExBaseCtrlOptr = pCtrlOptr;
	dlg.m_pDB_Insert_Base_Func = DB_Insert_Base_Func;

	if (dlg.DoModal()==IDOK)
	{
		pRet = dlg.m_pRetData;
	}

	delete pNewObj;
	return pRet;
}
#endif

template <class T1, class T2>
inline BOOL DB_Edit_Base(CExBaseObject *pTempObj, CExBaseObject *pCurrEditObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	T1 tempList;
	tempList.AddTail(pTempObj);

	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_UpdateData(tempList);

	if (bRes)
	{
		pTempObj->CopyOwn(pCurrEditObj);

		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_UpdateData(pCurrEditObj);
		}

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#ifndef _PSX_IDE_QT_
template <class T1, class T2, class TDlg>
inline BOOL DB_Edit_Base_Dlg(CExBaseObject *pCurrEditObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	T2 *pTempNew = new T2;
	pTempNew->SetParent(pCurrList);
	pCurrEditObj->CopyOwn(pTempNew);
	BOOL bRet = FALSE;

	TDlg dlg;
	dlg.SetEditObj(pTempNew, pCurrEditObj, pCurrList);
	dlg.m_pExBaseCtrlOptr = pCtrlOptr;
	dlg.m_pDB_Edit_Base_Func = DB_Edit_Base_Func;

	if (dlg.DoModal()==IDOK)
	{//dlg.GetEditData();  ��OnOK�����е���
		bRet = TRUE;
	}

	delete pTempNew;
	return bRet;
}
#endif

template <class T1, class T2>
inline BOOL DB_Edit_Base_Own(CExBaseObject *pCurrEditObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	T1 tempList;
	T2 *pNew = (T2*)pCurrEditObj->CloneEx();
	tempList.AddTail(pNew);
	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_UpdateData(tempList);

	if (bRes)
	{
		pNew->CopyOwn(pCurrEditObj);
		pCurrEditObj->DB_InitNameAttrs();

		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_UpdateData(pCurrEditObj);
		}
	}

	return bRes;
}


template <class T1, class T2>
inline BOOL DB_Delete_Base(CExBaseObject *pObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pCtrlOptr)
{
	T1 tempList;
	tempList.AddTail(pObj);
	BOOL bRes = g_pExBaseDataOptrBaseApp->Optr_DeleteData(tempList, QUERY_TABLE_OWN);

	if (bRes)
	{
		if (pCtrlOptr != NULL)
		{
			pCtrlOptr->Optr_DeleteData(pObj);
			pCtrlOptr->Optr_UpdateDataIndex();
		}

		if (pCurrList != NULL)
		{
			pCurrList->Delete(pObj);
		}
	}

	tempList.RemoveAll();

	return bRes;
}

#ifndef _PSX_IDE_QT_			//add by yyj at 20200416 begin
class CExBase_EditDlgBase : public CDialog
{
public:
	CExBase_EditDlgBase(UINT nIDD, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExBase_EditDlgBase();

	CExBaseList *m_pParent; //��ǰ�༭����ĸ�����
	CExBaseObject *m_pCurrData; //��ǰ�༭�Ķ��󣬼���ʱ���ݶ���
	CExBaseObject *m_pRefData;  //��ǰ�༭��������ö��󣬼�Դ���ݶ���
	CExBaseCtrlOptrInterface *m_pExBaseCtrlOptr;   //��������Ľ����������

	LP_DB_INSERT_BASE_FUNC* m_pDB_Insert_Base_Func;
	LP_DB_MODIFY_BASE_FUNC* m_pDB_Edit_Base_Func;
	CExBaseObject *m_pRetData;

	BOOL IsNewMode()	{	return (m_pRefData == NULL);	}
	BOOL IsEditMode()		{	return (m_pRefData != NULL);		}
	BOOL IsPkValueChanged();

public:
	virtual void AttacthExBaseCtrlOptrInterface(CExBaseCtrlOptrInterface *pCtrlOptr)	{	m_pExBaseCtrlOptr = pCtrlOptr;	}	
	virtual void SetEditObj(CExBaseObject* pEditObj, CExBaseObject *pRefObject, CExBaseList *pParentList);
	virtual CExBaseObject* GetEditData()	{	ASSERT (FALSE);	return NULL;	}
	virtual void ShowEditData(){};

	virtual BOOL ValidateData();
	virtual BOOL ValidateData_New();
	virtual BOOL ValidateData_Edit();
	virtual BOOL ValidateExBaseObjectNameAndPk_New(const CString &strName);
	virtual BOOL ValidateExBaseObjectNameAndPk_Edit(const CString &strName);

	virtual void OnOK();
};
#endif					//add by yyj at 20200416 end

#if 0
//////////////////////////////////////////
template <class T1, class T2>
inline BOOL DBFileOptr(CExBaseObject *pNewObj, CExBaseList *pCurrList
						 , CExBaseListGrid *pCurrGrid
						 , CString &strRemoteFile, CString &strLocalFile
						 , const CString &strRelPath, int nType)
{
	BOOL bRet = FALSE;
	CString strFileName;

	if (!strRelPath.IsEmpty())
	{//��Ҫ�ϴ��ļ��������ļ��ֶ�strRemoteFile
		strFileName = GetFileNameFromFilePath(strLocalFile);
		strRemoteFile = strRelPath + strFileName;		
	}

	if(nType == DB_FILEOPTR_INSERT)
	{
		bRet = DBInsertOwn<T1,T2>(pNewObj,pCurrList,pCurrGrid);
	}
	else
	{
		bRet = DBEditOwn<T1,T2>(pNewObj,pCurrList,pCurrGrid);
	}
	
	if(!bRet)
	{
		return FALSE;
	}

	if (!strRelPath.IsEmpty())
	{//��Ҫ�ϴ��ļ�
		g_pExBaseDataOptrBaseApp->UploadFile(strRemoteFile, strLocalFile);
	}

	return TRUE;
}
template <class T1, class T2>
inline BOOL DBInsertFile(CExBaseObject *pNewObj, CExBaseList *pCurrList
								   , CExBaseListGrid *pCurrGrid,CString &strRemoteFile
								   ,CString &strLocalFile)
{
	T1 tempList;
	tempList.AddTail(pNewObj);

	CString strRelPath = _T("");
	BOOL bRes = g_pExBaseDataOptrBaseApp->OAMngrClient_BeginUploadOptr(tempList,strRelPath);
	
	if (!bRes)
	{
		tempList.RemoveAll();
		return FALSE;
	}

	UINT nClassID = pNewObj->GetClassID();
	if (nClassID == OACLASSID_COA_PRJCONTRACT)
	{
		bRes = DBContractFileOptr((COA_PrjContract *)pNewObj,(COA_PrjContracts *)pCurrList
									,pCurrGrid,strRelPath,DB_FILEOPTR_INSERT);	
	}	
	else
	{
		bRes = DBFileOptr<T1,T2>(pNewObj,pCurrList,pCurrGrid,strRemoteFile,strLocalFile
									,strRelPath,DB_FILEOPTR_INSERT);
	}

	tempList.RemoveAll();
	return bRes;
}

template <class T1, class T2, class TDlg>
inline BOOL DBInsertFile_Dlg(CExBaseList *pCurrList, CExBaseListGrid *pCurrGrid)
{
	TDlg dlg;
	T2* pNewObj = new T2;
	dlg.SetEditObj(pNewObj, NULL, pCurrList);

	BOOL bRet = FALSE;
	if (dlg.DoModal()==IDOK)
	{
		CString strLocalFile,strInfo;

		int nClassID = ((CExBaseObject*)pNewObj)->GetClassID();
		switch(nClassID)
		{
		case OACLASSID_COA_PRJPROBLEM:
			{
				strLocalFile = ((COA_PrjProblem*)pNewObj)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ�����½�ʧ��!");

				bRet = DBInsertFile<T1, T2>(pNewObj, pCurrList ,pCurrGrid, ((COA_PrjProblem*)pNewObj)->m_strFile_PrjProblem, strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJREQUIREMENT:
			{
				strLocalFile = ((COA_PrjRequirement*)pNewObj)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ�����½�ʧ��!");

				bRet = DBInsertFile<T1, T2>(pNewObj, pCurrList ,pCurrGrid, ((COA_PrjRequirement*)pNewObj)->m_strFile_Task_Require, strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJRSLT:
			{
				strLocalFile = ((COA_PrjRslt*)pNewObj)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ�ɹ��½�ʧ��!");

				bRet = DBInsertFile<T1, T2>(pNewObj, pCurrList ,pCurrGrid, ((COA_PrjRslt*)pNewObj)->m_strFile_PrjRslt, strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJCONTRACT:
			{
				strLocalFile = ((COA_PrjContract*)pNewObj)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ��ͬ�½�ʧ��!");

				bRet = DBInsertFile<T1, T2>(pNewObj, pCurrList ,pCurrGrid, ((COA_PrjContract*)pNewObj)->m_strFile_Attachment, strLocalFile);

				break;
			}
		case OACLASSID_COA_TASKDOC:
			{
				strLocalFile = ((COA_TaskDoc*)pNewObj)->m_strFile_LocalPath;
				strInfo = _T("�����ĵ��½�ʧ��!");

				bRet = DBInsertFile<T1, T2>(pNewObj, pCurrList ,pCurrGrid, ((COA_TaskDoc*)pNewObj)->m_strPath, strLocalFile);

				break;
			}
		default:
			break;
		}

		if (!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
		}
	}
	else
	{
		delete pNewObj;
	}

	return bRet;
}

template <class T1, class T2>
inline BOOL DBEditFile(CExBaseObject *pCurrEditObj
						 , CExBaseList *pCurrList, CExBaseListGrid *pCurrGrid
						 ,CString &strRemoteFile ,CString &strLocalFile)							  
{
	T1 tempList;
	tempList.AddTail(pCurrEditObj);

	CString strRelPath = _T("");
	CString strFileName;
	BOOL bRes = g_pExBaseDataOptrBaseApp->OAMngrClient_BeginUploadOptr(tempList,strRelPath);
	if (!bRes)
	{
		tempList.RemoveAll();
		return FALSE;
	}

	UINT nClassID = pCurrEditObj->GetClassID();
	if (nClassID == OACLASSID_COA_PRJCONTRACT)
	{
		bRes = DBContractFileOptr((COA_PrjContract *)pCurrEditObj,(COA_PrjContracts *)pCurrList
			,pCurrGrid,strRelPath,DB_FILEOPTR_MODIFY);
	}
	else
	{
		bRes = DBFileOptr<T1,T2>(pCurrEditObj,pCurrList,pCurrGrid,strRemoteFile,strLocalFile
			,strRelPath,DB_FILEOPTR_MODIFY);
	}

	tempList.RemoveAll();
	return bRes;
}

template <class T1, class T2, class TDlg>
inline BOOL DBEditFile_Dlg(CExBaseObject *pCurrEditObj, CExBaseList *pCurrList, CExBaseListGrid *pCurrGrid)
{
	TDlg dlg;
	T2* pTempNew = new T2;
	pCurrEditObj->CopyOwn(pTempNew);

	dlg.SetEditObj(pTempNew, pCurrEditObj, pCurrList);

	BOOL bRet = FALSE;
	if (dlg.DoModal()==IDOK)
	{
		CString strLocalFile,strInfo;

		int nClassID = ((CExBaseObject*)pTempNew)->GetClassID();
		switch(nClassID)
		{
		case OACLASSID_COA_PRJPROBLEM:
			{
				strLocalFile = ((COA_PrjProblem*)pTempNew)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ������Ϣ�޸�ʧ��!");

				bRet = DBEditFile<T1,T2>(pTempNew,pCurrList,pCurrGrid,((COA_PrjProblem*)pTempNew)->m_strFile_PrjProblem,strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJREQUIREMENT:
			{
				strLocalFile = ((COA_PrjRequirement*)pTempNew)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ������Ϣ�޸�ʧ��!");

				bRet = DBEditFile<T1,T2>(pTempNew,pCurrList,pCurrGrid,((COA_PrjRequirement*)pTempNew)->m_strFile_Task_Require,strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJRSLT:
			{
				strLocalFile = ((COA_PrjRslt*)pTempNew)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ�ɹ���Ϣ�޸�ʧ��!");

				bRet = DBEditFile<T1,T2>(pTempNew,pCurrList,pCurrGrid,((COA_PrjRslt*)pTempNew)->m_strFile_PrjRslt,strLocalFile);

				break;
			}
		case OACLASSID_COA_PRJCONTRACT:
			{
				strLocalFile = ((COA_PrjContract*)pTempNew)->m_strFile_LocalPath;
				strInfo = _T("��Ŀ��ͬ��Ϣ�޸�ʧ��!");

				bRet = DBEditFile<T1,T2>(pTempNew,pCurrList,pCurrGrid,((COA_PrjContract*)pTempNew)->m_strFile_Attachment,strLocalFile);

				break;
			}
		case OACLASSID_COA_TASKDOC:
			{
				strLocalFile = ((COA_TaskDoc*)pTempNew)->m_strFile_LocalPath;
				strInfo = _T("�����ĵ���Ϣ�޸�ʧ��!");

				bRet = DBEditFile<T1,T2>(pTempNew,pCurrList,pCurrGrid,((COA_TaskDoc*)pTempNew)->m_strPath,strLocalFile);

				break;
			}
		default:
			break;
		}

		if (bRet)
		{
			pTempNew->CopyOwn(pCurrEditObj);
			pCurrGrid->UpdateData(pCurrEditObj);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,strInfo);
		}
	}
	else
	{
		delete pTempNew;
	}

	return bRet;
}

template  <class T1, class T2>
inline BOOL DB_Delete_For_MsgBox(CExBaseObject *pCurrDelObj, CExBaseList *pCurrList, CExBaseCtrlOptrInterface *pBaseCtrlOptr, BOOL bChildrenMustEmpty=FALSE)
{
	CString strMsg;
	CWnd *pMainFrame = AfxGetMainWnd();

	if (bChildrenMustEmpty)
	{
		if (pCurrDelObj->IsBaseList())
		{
			if (((CExBaseList*)pCurrDelObj)->GetCount() > 0)
			{
				strMsg.Format(_T("����%s�������Ӷ��󣬲���ɾ����"),pCurrDelObj->m_strName);
				pMainFrame->MessageBox(strMsg,_T("��ʾ"), MB_OK|MB_ICONEXCLAMATION);
				return FALSE;
			}
		}
	}

	strMsg.Format(_T("ȷʵҪɾ����%s����"),pCurrDelObj->m_strName);
	int nRet = pMainFrame->MessageBox(strMsg,_T("��ʾ"), MB_YESNO|MB_ICONQUESTION);

	if(nRet == IDYES)
	{
		return DB_Delete_Base<T1,T2>(pCurrDelObj, pCurrList, pBaseCtrlOptr);
	}
	else
	{
		return FALSE;
	}
}
#endif

BOOL Db_Validate_New_MsgBox(CExBaseList *pParent, CExBaseObject *pCurrObj, CWnd *pParentWnd=NULL, BOOL bValidateName=TRUE, BOOL bValidateID=FALSE);
BOOL Db_Validate_Edit_MsgBox(CExBaseList *pParent, CExBaseObject *pCurrObj, CWnd *pParentWnd=NULL, BOOL bValidateName=TRUE, BOOL bValidateID=FALSE);
BOOL Db_Validate_Edit_MsgBox(CExBaseList *pParent, CExBaseObject *pRefData, CExBaseObject *pCurrObj, CWnd *pParentWnd=NULL, BOOL bValidateName=TRUE, BOOL bValidateID=FALSE);
