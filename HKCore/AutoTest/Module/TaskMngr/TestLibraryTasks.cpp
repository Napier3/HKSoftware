#include "stdafx.h"
#include "TestLibraryTasks.h"
#include "../AutoTestXMLRWKeys.h"
#include "..\TCtrlCntrConfig.h"

#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CTestLibraryTasks *CTestLibraryTasks::g_pTestLibraryTasks = NULL;
long               CTestLibraryTasks::g_nTestLibraryTasks = 0;

CTestLibraryTasks* CTestLibraryTasks::Create()
{
	g_nTestLibraryTasks++;

	if (g_nTestLibraryTasks == 1)
	{
		g_pTestLibraryTasks = new CTestLibraryTasks();
		g_pTestLibraryTasks->Open();
	}

	return g_pTestLibraryTasks;
}

void CTestLibraryTasks::Release()
{
	g_nTestLibraryTasks--;

	if (g_nTestLibraryTasks == 0)
	{
		delete g_pTestLibraryTasks;
		g_pTestLibraryTasks = NULL;
	}
}

void CTestLibraryTasks::AddTestTask(CTestTask *pTestTask)
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->AddNewChild(pTestTask);
}

void CTestLibraryTasks::AddTestProject(CTestProject *pTestProject)
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->AddNewChild(pTestProject);
}

void CTestLibraryTasks::DeleteXTest(CExBaseObject *pXTest)
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->Delete(pXTest);
}

void CTestLibraryTasks::DeleteXTests(CExBaseList *pXTestList)
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	POS pos = pXTestList->GetHeadPosition();
	CExBaseObject *pXTest = NULL;

	while(pos != NULL)
	{
		pXTest = (CExBaseObject *)pXTestList->GetNext(pos);
		g_pTestLibraryTasks->Delete(pXTest);
	}
}

void CTestLibraryTasks::DeleteAllXTest()
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->DeleteAll();
}

void CTestLibraryTasks::SaveLib()
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->Save();
}

void CTestLibraryTasks::OpenLib()
{
	ASSERT (g_pTestLibraryTasks != NULL);

	if (g_pTestLibraryTasks == NULL)
	{
		return;
	}

	g_pTestLibraryTasks->DeleteAll();
	g_pTestLibraryTasks->Open();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CTestLibraryTasks::CTestLibraryTasks()
{

}

CTestLibraryTasks::~CTestLibraryTasks()
{

}

void CTestLibraryTasks::Init()
{

}


long CTestLibraryTasks::InitAfterSerialize()
{
	return 0;
}

UINT CTestLibraryTasks::GetClassID()
{
	return 0;
}

BSTR CTestLibraryTasks::GetXmlElementKey()
{
	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey;
}

long CTestLibraryTasks::IsEqual(CExBaseObject* pObj)
{
	CTestLibraryTasks *pTestTasks = (CTestLibraryTasks*)pObj;

	if(pObj == NULL)
		return 0;

	long nCount1 = pTestTasks->GetCount();
	long nCount2 = GetCount();

	if(nCount1 == nCount2)
	{
		for(long i=0;i<nCount1;i++)
		{
			CTestTask* pTestTask1 = (CTestTask*)pTestTasks->GetAtIndex(i);
			CTestTask* pTestTask2 = (CTestTask*)GetAtIndex(i);
			if(!pTestTask1->IsEqual(pTestTask2))
				return 0;
		}
		return 1;
	}

	return 0;
}

long CTestLibraryTasks::Copy(CExBaseObject* pDesObj)
{
	if(pDesObj != NULL)
	{
		CTestLibraryTasks* pTemp = (CTestLibraryTasks*)pDesObj;

		long nCount = GetCount();
		for(long i=0;i<nCount;i++)
		{
			CTestTask* pTask1 = (CTestTask*)GetAtIndex(i);
			CTestTask* pTask2 = (CTestTask*)pTask1->Clone();
			pTemp->AddTail(pTask2);
		}
	}

	return 0;
}

CExBaseObject* CTestLibraryTasks::Clone()
{
	CTestLibraryTasks* pNew = new CTestLibraryTasks;
	Copy(pNew);

	return pNew;
}

CExBaseObject* CTestLibraryTasks::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskKey)
	{
		CTestTask* pTestTask = new CTestTask;
		return pTestTask;
	}

	if(strClassID == CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strProjectKey)
	{
		CTestProject* pTestProject = new CTestProject;
		return pTestProject;
	}

	return NULL;
}

CExBaseObject* CTestLibraryTasks::CreateNewChild(long nClassID)
{
	return NULL;
}

CString CTestLibraryTasks::GetTestLibraryTasksFile()
{
	CString strFile;

	strFile = CTCtrlCntrConfig::GetWorkSpacePath();
	strFile += g_strTCtrlCntrTaskMngrFile;

	return strFile;
}

BOOL CTestLibraryTasks::Open()
{
	ASSERT (CAutoTestXMLRWKeys::g_pAutoTestRWKeys != NULL);
	CString strFile = GetTestLibraryTasksFile();
	BOOL bTrue = FALSE;

	bTrue = OpenXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrKey, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);
	
	if (!bTrue)
	{
		bTrue = Save();
	}

	return bTrue;
}

BOOL CTestLibraryTasks::Save()
{
	CString strFile = GetTestLibraryTasksFile();

	SaveXmlFile(strFile, CAutoTestXMLRWKeys::g_pAutoTestRWKeys);

	return TRUE;
}


//WriteXml
long CTestLibraryTasks::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);

		BSTR pszElementKey = pObj->GetXmlElementKey();
		ASSERT(pszElementKey != NULL);

		if (pszElementKey == NULL)
		{
			return -1;
		}

#ifdef _UNICODE
		if (lstrlen(pszElementKey) == 0)
		{
			return -1;
		}
#else
		if (wcslen(pszElementKey) == 0)
		{
			return -1;
		}
#endif

		CXmlRWElementBase *pElement = oXMLDoc.CreateElement(pszElementKey,&oElement);

		pObj->XmlWriteOwn(oXMLDoc, *pElement, pXmlRWKeys);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////

CTestTaskLibListCtrl::CTestTaskLibListCtrl()
{

}

CTestTaskLibListCtrl::~CTestTaskLibListCtrl()
{

}

#define  TASKLIST_COL_INDEX      0
#define  TASKLIST_COL_STATE      1
#define  TASKLIST_COL_FILENAME   2
#define  TASKLIST_COL_FILESIZE   3
#define  TASKLIST_COL_FILETIME   4
#define  TASKLIST_COL_REPORTFILENAME 5
#define  TASKLIST_COL_REPORTFILESIZE 6

void CTestTaskLibListCtrl::InitCollumns()
{
	InsertColumn(TASKLIST_COL_INDEX,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,50);
	InsertColumn(TASKLIST_COL_STATE,g_sLangTxt_Status/*_T("状态")*/,LVCFMT_LEFT,80);

	InsertColumn(TASKLIST_COL_FILENAME,g_sLangTxt_TestRecordFile/*_T("测试记录文件")*/,LVCFMT_LEFT,350);
	InsertColumn(TASKLIST_COL_FILESIZE,g_sLangTxt_RecordFile/*_T("记录文件大小")*/,LVCFMT_LEFT,100);
	InsertColumn(TASKLIST_COL_FILETIME,g_sLangTxt_LastAccessedTimes/*_T("最后访问时间")*/,LVCFMT_LEFT,120);

	InsertColumn(TASKLIST_COL_REPORTFILENAME,g_sLangTxt_ReportFile/*_T("报告文件")*/,LVCFMT_LEFT,350);
	InsertColumn(TASKLIST_COL_REPORTFILESIZE,g_sLangTxt_ReportFileSize/*_T("报告文件大小")*/,LVCFMT_LEFT,100);
}

BOOL CTestTaskLibListCtrl::CanAdd(CExBaseObject *pObj)
{
	if (pObj->GetClassID() == CLASSID_TESTTASK)
	{
		return TRUE;
	}
	else if (pObj->GetClassID() == CLASSID_TESTPROJECT)
	{
		return TRUE;
	}
	else
	{
		return TRUE;
	}
}


void CTestTaskLibListCtrl::PopupMenu(CWnd* pWnd, CPoint point)
{
	CExBaseObject *pSel = (CExBaseObject*)GetSelectObject();
	CMenu menu;		
	menu.CreatePopupMenu();
	CWnd *pParentWnd = GetParent();

	if (pSel != NULL)
	{
		menu.AppendMenu(MF_STRING,ID_PROJECT_NEW,g_sLangTxt_NewTask/*_T("新任务")*/);
		menu.AppendMenu(MF_STRING,ID_PROJECT_DELETE,g_sLangTxt_Delete/*_T("删除")*/);
	}
	else
	{
		menu.AppendMenu(MF_STRING,ID_PROJECT_NEW,g_sLangTxt_NewTask/*_T("新任务")*/);
	}

	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pParentWnd);	
}



void CTestTaskLibListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	if (pObj->GetClassID() == CLASSID_TESTTASK)
	{
		UpdateListCtrl_Task((CTestTask*)pObj, nIndex);
	}
	else if (pObj->GetClassID() == CLASSID_TESTPROJECT)
	{
		UpdateListCtrl_Project((CTestProject*)pObj, nIndex);
	}
	else
	{
		ASSERT (FALSE);
	}

	SetItemData(nIndex, (DWORD)pObj);
}

void CTestTaskLibListCtrl::UpdateListCtrl_Task(CTestTask *pTask, long nIndex)
{
	CString strTemp;
	SetItemText(nIndex, TASKLIST_COL_STATE, pTask->m_strTestState);
	SetItemText(nIndex, TASKLIST_COL_FILENAME, GetPathFileNameFromFilePathName(pTask->m_strLocation));

	xfile_GetFileSize(pTask->m_strLocation, strTemp);
	SetItemText(nIndex, TASKLIST_COL_FILESIZE, strTemp);
	xfile_GetModifyTime(pTask->m_strLocation, strTemp);
	SetItemText(nIndex, TASKLIST_COL_FILETIME, strTemp);

	SetItemText(nIndex, TASKLIST_COL_REPORTFILENAME, _T("---"));
	SetItemText(nIndex, TASKLIST_COL_REPORTFILESIZE, _T("---"));
}

void CTestTaskLibListCtrl::UpdateListCtrl_Project(CTestProject *pProject, long nIndex)
{
	
}


//////////////////////////////////////////////////////////////////////////

CTestTaskListCtrl::CTestTaskListCtrl()
{

}

CTestTaskListCtrl::~CTestTaskListCtrl()
{

}

#define  TASKLIST_COL_INDEX      0
#define  TASKLIST_COL_STATE      1
#define  TASKLIST_COL_FILENAME   2
#define  TASKLIST_COL_FILESIZE   3
#define  TASKLIST_COL_FILETIME   4

void CTestTaskListCtrl::InitCollumns()
{
	InsertColumn(TASKLIST_COL_INDEX,g_sLangTxt_Index/*_T("编号")*/,LVCFMT_LEFT,40);
	InsertColumn(TASKLIST_COL_STATE,g_sLangTxt_Status/*_T("状态")*/,LVCFMT_LEFT,60);
	InsertColumn(TASKLIST_COL_FILETIME,g_sLangTxt_ReportFile/*_T("报告文件")*/,LVCFMT_LEFT,200);
	InsertColumn(TASKLIST_COL_FILESIZE,g_sLangTxt_ReportFileSize/*_T("报告文件大小")*/,LVCFMT_LEFT,120);
	InsertColumn(TASKLIST_COL_FILETIME,g_sLangTxt_LastAccessedTimes/*_T("最后访问时间")*/,LVCFMT_LEFT,120);
}

BOOL CTestTaskListCtrl::CanAdd(CExBaseObject *pObj)
{
	if (pObj->GetClassID() == CLASSID_TESTPROJECT)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CTestTaskListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CTestProject *pProject = (CTestProject*)pObj;
	CString strTemp;
	SetItemText(nIndex, 1, pProject->GetTestStateDesc());

	CString strLocation = pProject->tsk_GetLocation();
	SetItemText(nIndex, 2, GetPathFileNameFromFilePathName(strLocation));
	xfile_GetFileSize(strLocation, strTemp);
	SetItemText(nIndex, 3, strTemp);
	xfile_GetModifyTime(strLocation, strTemp);
	SetItemText(nIndex, 4, strTemp);

	SetItemData(nIndex, (DWORD)pObj);
}



void CTestTaskListCtrl::PopupMenu(CWnd* pWnd, CPoint point)
{
	CTestProject *pTestProject = (CTestProject*)GetSelectObject();
	CMenu menu;		
	menu.CreatePopupMenu();
	CWnd *pParentWnd = GetParent();

	if (pTestProject != NULL)
	{
		menu.AppendMenu(MF_STRING,ID_PROJECT_TEST,g_sLangTxt_EnterTask/*_T("进入测试")*/);
		//menu.AppendMenu(MF_STRING,ID_PROJECT_EDITANDTEST,_T("编辑-测试"));
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_PROJECT_NEW,g_sLangTxt_NewReport/*_T("新报告")*/);
		menu.AppendMenu(MF_STRING,ID_PROJECT_EDIT,g_sLangTxt_Modify/*_T("修改")*/);
		menu.AppendMenu(MF_STRING,ID_PROJECT_DELETE,g_sLangTxt_Delete/*_T("删除")*/);
	}
	else
	{
		menu.AppendMenu(MF_STRING,ID_PROJECT_NEW,g_sLangTxt_NewReport/*_T("新报告")*/);
	}

	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pParentWnd);	
	// 	//资源回收
	// 	HMENU hmenu=menu.Detach();	
	// 	menu.DestroyMenu();
}

