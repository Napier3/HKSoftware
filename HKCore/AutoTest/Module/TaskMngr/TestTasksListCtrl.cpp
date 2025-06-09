//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksListCtrl.cpp  CTestTasksListCtrl


#include "stdafx.h"
#include "TestTasksListCtrl.h"


#define TestTasks_COL_INDEX      0
#define TestTasks_COL_NAME       1
#define TestTasks_COL_PATH       2


CTestTasksListCtrl::CTestTasksListCtrl()
{
	//初始化属性

	//初始化成员变量
}

CTestTasksListCtrl::~CTestTasksListCtrl()
{

}


void CTestTasksListCtrl::InitCollumns()
{
	InsertColumn(TestTasks_COL_INDEX,  _T("编号"),      LVCFMT_CENTER,40);
	InsertColumn(TestTasks_COL_NAME,   _T("任务名称"),  LVCFMT_LEFT,400);
	InsertColumn(TestTasks_COL_PATH,   _T("路径"),  LVCFMT_LEFT,500);
}

void CTestTasksListCtrl::UpdateListCtrl(CExBaseObject *pObj, long nIndex)
{
	CString strIndex;
	strIndex.Format(_T("%d"),nIndex+1);
	CXFile *pXFle = (CXFile*)pObj;

	SetItemText(nIndex,TestTasks_COL_INDEX, strIndex);
	SetItemText(nIndex,TestTasks_COL_NAME,  pXFle->m_strName);
	SetItemText(nIndex,TestTasks_COL_PATH,  pXFle->GetFolderPath(FALSE));
	
	SetItemData(nIndex, (DWORD)pObj);
}
