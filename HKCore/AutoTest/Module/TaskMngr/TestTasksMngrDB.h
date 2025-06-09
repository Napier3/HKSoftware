#pragma once

#include "TestTasksMngr.h"
#include "TestTasksMngrExcel.h"

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrDB
class CTestTasksMngrGroup : public CExBaseList
{
public:
	CTestTasksMngrGroup();
	virtual ~CTestTasksMngrGroup();

	CString m_strTasksMngrDBFile;
public:
	//��������
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID()	{		return CLASSID_TESTTASKMNGRSGROUP;	}

	//���л�
	virtual BSTR GetXmlElementKey()	{		return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsGroupKey;	}

	//�༭
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	
	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

public:
	CTestTasksMngr* AddTaskMngrsFile(const CString &strFile);
	//BOOL SaveTasksFile(const CString &strFile);

};



//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrDB
class CTestTasksMngrDB : public CTestTasksMngrGroup
{
public:
	static CTestTasksMngrDB* g_pTestTasksMngrDB;
	static long g_nTestTasksMngrDBRef;

	static CTestTasksMngrDB* Create();
	static void Release();
	static CTestTasksMngrDB* GetTestTasksMngrDB();
	static CTestTasksMngr* InsertTaskMngrFile(CTestTasksMngrGroup *pGroup, const CString &strFile);
	static CTestTasksMngr* GetActiveTasksMngr();
	static CString GetActiveTasksMngrID();
	static void SetActiveTasksMngr(CTestTasksMngr *pTasksMngr);
	static void DeleteTasksMngr(CTestTasksMngr *pTasksMngr);
	static void Save();


private:
	CTestTasksMngrDB();
	virtual ~CTestTasksMngrDB();

	CString m_strTasksMngrDBFile;
	CString m_strActiveTasksMngr;
	CTestTasksMngr *m_pActiveTasksMngr;

private:
	//��������
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID()	{		return CLASSID_TESTTASKMNGRSDB;	}

	//���л�
	virtual BSTR GetXmlElementKey()	{		return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strTaskMngrsDBKey;	}

	//�༭
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

private:
	BOOL In_AddTaskMngrsFile(const CString &strFile);
	BOOL In_SaveTasksFile(const CString &strFile);

	CString GetDBFile();
	void OpenDBFile();
	void SaveDBFile();
};
