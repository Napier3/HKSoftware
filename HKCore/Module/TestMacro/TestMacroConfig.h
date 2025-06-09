//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroConfig.h  CTestMacroConfig

#pragma once

#include "TestMacroGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CTestMacroConfig
class CTestMacroConfig : public CExBaseObject
{
public:
	CTestMacroConfig();
	virtual ~CTestMacroConfig();


	CString  m_strIecConfigFile;
	CString  m_strType;

//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacroConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

//////////////////////////////////////////////////////////////////////////
//CTestMacroConfigs
class CTestMacroConfigs : public CExBaseList
{
public:
	CTestMacroConfigs();
	virtual ~CTestMacroConfigs();


	CString  m_strActiveMacroTest;
	CString  m_strType;
//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROCONFIGS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacroConfigsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

