#pragma once

#include "TestTask.h"

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngr
class CTestTasksMngr : public CExBaseList
{
public:
	CTestTasksMngr();
	virtual ~CTestTasksMngr();

	CString m_strTasksMngrSrcFile;
	CString m_strTasksMngrFile;
	BOOL m_bXmlWriteChildren;

	CString m_strPpEngineProgID;
	CString m_strTestTemplateFile;
	CString m_strPpTemplateFile;
	CString m_strDeviceFile;

	CExBaseList m_listFinish;
	CExBaseList m_listDeviceAttrs;
	long m_nVersion;

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID()	{		return CLASSID_TESTTASKMNGRS;	}

	//串行化
	virtual BSTR GetXmlElementKey()	{		return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsKey;	}

	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

public:
	CString GetTaskMngrsFile();
	BOOL OpenTaskMngrsFile();
	BOOL OpenTaskMngrsFile(const CString &strFile);
	BOOL SaveTasksFile();
	BOOL SaveTasksFile(const CString &strFile);

	long SelectAllDeviceAttrs(CExBaseList &listDvmAttrs, BOOL bIncludeDataset=TRUE, BOOL bIncludeTasks=FALSE);
	void AddToFinish(CDvmDataset *pDeviceAttr);

	long GetSelDeviceAttrsCount();
};
