#pragma  once

#include "TestTask.h"

c
//////////////////////////////////////////////////////////////////////////
//CTestTasks
class CTestTasks : public CExBaseList
{
public:
	CTestTasks();
	virtual ~CTestTasks();

	CString m_strTasksFile;

	CDvmDataset *m_pTestApp;   //被测装置的属性
	CExBaseList m_listCmmCfgChannel;
	CString m_strPpEngineProgID;

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();

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
	virtual long XmlWriteChildren(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);	

	//工作区
	BOOL SaveTasksFile(const CString &strFile);
	BOOL OpenTasksFile(const CString &strFile);

public:
	BOOL HasTestTask();
	long SelectAllTestTask(CExBaseList &listTask);
	void InitAllCmdCfgChannels();

	void SavePoProjectFile();
};
