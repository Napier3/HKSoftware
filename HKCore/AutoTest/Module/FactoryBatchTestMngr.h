#pragma once

/*
	功能描述：工作区管理
	相关文件：FactoryBatchTestMngr.xml
*/
#include "../../Module/BaseClass/ExBaseList.h"
#include "TaskMngr/TestTask.h"

#define  WM_FACBATCHTEST  (WM_USER + 2313)

#define FacBatchTestMsg_Item      0
#define FacBatchTestMsg_Project   1
#define FacBatchTestMsg_Attr_IdxDv            2
#define FacBatchTestMsg_Attr_TestErr       3
#define FacBatchTestMsg_Attr_ShowDatas     4
#define FacBatchTestMsg_Attr_UpdateDatas  5

class CFactoryBatchTestMngr : public CExBaseList
{
private:
	CFactoryBatchTestMngr();
	virtual ~CFactoryBatchTestMngr();

	static CFactoryBatchTestMngr* g_pFactoryBatchTestMngr;
	static long g_nFactoryBatchTestMngrRef;
	CString GetFactoryBatchTestMngrFile();
	CTestTasks *m_pCurrTestTasks;
	long m_nCurrTestTaskCount;
	CWnd *m_pMsgRcvWnd;
	CExBaseObject *m_pMainTestControl;

	BOOL m_bModifiedFlag;
public:
	static CFactoryBatchTestMngr* Create();
	static void Release();
	CFactoryBatchTestMngr* GetFactoryBatchTestMngr();

public:
	//基本方法
	virtual BOOL Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID();
	//串行化
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	//工作区
	long Save();
	long Open();

	//2021-3-14  lijunqing  
	virtual void SetModifiedFlagOwn(BOOL bModified=TRUE)	{	m_bModifiedFlag = bModified;	}

public:
	static CTestTasks* InitCurrTestTasks();
	static CTestTasks* GetCurrTestTasks();
	static CTestProject* FindProjectByPrjIndex(CTestProject *pProject);
	static CTestProject* FindProjectByPrjIndex(long nProjectIndex);
	static void SetCurrTestTasks(CTestTasks *pTestTasks);
	static long GetCurrCount();
	static BOOL HasTestTasks();
	static void AttachMsgRcvWnd(CWnd *pWnd);
	static void PostFacBatchTestMsg(WPARAM wParam, LPARAM lParam);
	static void AttachMainTestControl(CExBaseObject *pTestControl);
	static CExBaseObject* GetMainTestControl();

	//2021-3-14  lijunqing  
	static void BatchTestChanged();
	static void SaveBatchTest();
};

