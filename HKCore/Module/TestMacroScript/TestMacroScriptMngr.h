//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroScriptMngr.h  CTestMacroScriptMngr

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TestMacroScript.h"
#include "../TestMacro/TestMacros.h"

class CTestMacroScriptMngr : public CExBaseList
{
public:
	CTestMacroScriptMngr();
	virtual ~CTestMacroScriptMngr();

	CString m_strScriptFile;

//���غ���
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTESTMACROSCRIPTMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTestMacroScriptMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

