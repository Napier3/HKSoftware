//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestTasksListCtrl.cpp  CTestTasksListCtrl


#include "stdafx.h"
#include "TestTasksListCtrl.h"


#define TestTasks_COL_INDEX      0
#define TestTasks_COL_NAME       1
#define TestTasks_COL_PATH       2


CTestTasksListCtrl::CTestTasksListCtrl()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTestTasksListCtrl::~CTestTasksListCtrl()
{

}


void CTestTasksListCtrl::InitCollumns()
{
	InsertColumn(TestTasks_COL_INDEX,  _T("���"),      LVCFMT_CENTER,40);
	InsertColumn(TestTasks_COL_NAME,   _T("��������"),  LVCFMT_LEFT,400);
	InsertColumn(TestTasks_COL_PATH,   _T("·��"),  LVCFMT_LEFT,500);
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
