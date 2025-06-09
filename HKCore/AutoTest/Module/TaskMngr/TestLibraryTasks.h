#pragma  once

#include "TestTask.h"
#include "../../../Module/BaseClass/ExBaseListListCtrl.h"

#define  TASKLIST_COL_INDEX      0
#define  TASKLIST_COL_STATE      1
#define  TASKLIST_COL_FILENAME   2
#define  TASKLIST_COL_FILESIZE   3
#define  TASKLIST_COL_FILETIME   4
#define  TASKLIST_COL_REPORTFILENAME 5
#define  TASKLIST_COL_REPORTFILESIZE 6

class CTestLibraryTasks : public CExBaseList
{
private:
	CTestLibraryTasks();
	virtual ~CTestLibraryTasks();

public:
	static CTestLibraryTasks *g_pTestLibraryTasks;
	static long               g_nTestLibraryTasks;

	static CTestLibraryTasks* Create();
	static void Release();

	static void AddTestTask(CTestTask *pTestTask);
	static void AddTestProject(CTestProject *pTestProject);
	static void DeleteXTest(CExBaseObject *pXTest);
	static void DeleteXTests(CExBaseList *pXTestList);
	static void DeleteAllXTest();
	static void SaveLib();
	static void OpenLib();

protected:
	//基本方法
	virtual void Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID();
	//串行化
	virtual BSTR GetXmlElementKey();
	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	//工作区
	BOOL Save();
	BOOL Open();

	CString GetTestLibraryTasksFile();
};

class CTestTaskLibListCtrl : public CExBaseListListCtrl
{
public:
	CTestTaskLibListCtrl();
	virtual ~CTestTaskLibListCtrl();

public:
	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void PopupMenu(CWnd* pWnd, CPoint point);

protected:
	virtual void UpdateListCtrl_Task(CTestTask *pTask, long nIndex);
	virtual void UpdateListCtrl_Project(CTestProject *pProject, long nIndex);

};


class CTestTaskListCtrl : public CExBaseListListCtrl
{
public:
	CTestTaskListCtrl();
	virtual ~CTestTaskListCtrl();

public:
	virtual void InitCollumns();
	virtual void UpdateListCtrl(CExBaseObject *pObj, long nIndex);

	virtual BOOL CanAdd(CExBaseObject *pObj);
	virtual void PopupMenu(CWnd* pWnd, CPoint point);
};

#define ID_PROJECT_TEST                 32900
#define ID_PROJECT_EDITANDTEST          32901
#define ID_PROJECT_NEW                  32902
#define ID_PROJECT_EDIT                 32903
#define ID_PROJECT_DELETE               32904
