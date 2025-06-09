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

	CDvmDataset *m_pTestApp;   //����װ�õ�����
	CExBaseList m_listCmmCfgChannel;
	CString m_strPpEngineProgID;

public:
	//��������
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID();
	//���л�
	virtual BSTR GetXmlElementKey();

	//�༭
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	//WriteXml
	virtual long XmlWriteChildren(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);	

	//������
	BOOL SaveTasksFile(const CString &strFile);
	BOOL OpenTasksFile(const CString &strFile);

public:
	BOOL HasTestTask();
	long SelectAllTestTask(CExBaseList &listTask);
	void InitAllCmdCfgChannels();

	void SavePoProjectFile();
};
