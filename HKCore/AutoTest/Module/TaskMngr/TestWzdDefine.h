#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "TestProject.h"
#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "TestGlobalDefine.h"

class CTestWzdDefine : public CExBaseList
{
public:
	CTestWzdDefine(void);
	virtual ~CTestWzdDefine(void);

public:
	CString m_strMacroFile;
	CString m_strPpEngineProgID;

	CTestMacrosFile *m_pTestMacrosFile;
	CTestGlobalDefine m_oTestGlobalDefine;
	CTestTypes m_oTestTypes;
	CDvmDataset *m_pTestApp;

public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();
	virtual UINT GetClassID()	{		return CLASSID_TESTWZDDEFINE;	}
	//串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCTestWzdDefineKey;	}

	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long CopyOwn(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

protected:
	CString m_strTemplateFile;
	CString m_strDeviceFile;
	CString m_strPpTemplateFile;

public:
	CDvmDataset* GetTestApp();
	CTestTypes* GetTestTypes();

	CString GetTemplateFile();
	CString GetDeviceFile();
	CString GetPpTemplateFile();

};

//////////////////////////////////////////////////////////////////////////
//CTestWzdDefines
class CTestWzdDefines : public CExBaseList
{
public:
	CTestWzdDefines();
	virtual ~CTestWzdDefines();


public:
	//基本方法
	virtual void Init();
	virtual void InitAfterRead();

	virtual UINT GetClassID()	{		return CLASSID_TESTWZDDEFINES;	}

	//串行化
	virtual BSTR GetXmlElementKey(){	return CAutoTestXMLRWKeys::g_pAutoTestRWKeys->m_strCTestWzdDefinesKey;}

	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

public:

};
