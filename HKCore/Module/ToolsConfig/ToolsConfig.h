//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ToolsConfig.h  CToolsConfig

#pragma once

#include "ToolsConfigGlobal.h"
#include "ToolObject.h"


class CToolsConfig : public CExBaseList
{
public:
	CToolsConfig();
	virtual ~CToolsConfig();

public:
	long m_nUserServer;
	long m_nUse_TASKTEST;
	long m_nUse_SDVMPP;
	long m_nUseMDVMGRP;
	long m_nUse_ReportPane;
	long m_nUseAppSelConfig;

	CString m_strName_TEST_PROJECT_EX;

//���غ���
public:
	virtual UINT GetClassID() {    return TCFCLASSID_CTOOLSCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CToolsConfigXmlRWKeys::CToolsConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	long GetCount_cmd();
	long GetCount_exe();
	CToolObject* FindToolObject(UINT nCmdID);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void OpenToolsConfig();
	void SaveToolsConfig();
	BOOL IsOnlySdvSppTest();
};

