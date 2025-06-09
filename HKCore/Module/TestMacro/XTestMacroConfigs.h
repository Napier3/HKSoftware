//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroConfigs.h  CTestMacroConfigs

#pragma once

#include "TestMacroConfig.h"

class CTestMacroConfigs : public CExBaseList
{
public:
	static long g_nTestMacroConfigsRef;
	static CTestMacroConfigs* g_pTestMacroConfigs;
	static CTestMacroConfigs* Create();
	static void Release();

	static CString g_strDefaultIecConfigFile;

private:
	CTestMacroConfigs();
	virtual ~CTestMacroConfigs();


	CString  m_strActiveMacroTest;
	CTestMacroConfig *m_pActiveMacroTest;

	static CString g_strDefaultMacroTestEngineProgID;

//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROCONFIGS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacroConfigsKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CTestMacroConfig* FindByIecFile(const CString &strFile);

public:
	static CString GetActiveMcroTestEngineProgID();
	static CString GetAcriveMacroIecFile();
};

