//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TestMacroScript.h  CTestMacroScript

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "TmScptData.h"

class CTestMacroScript : public CExBaseList
{
public:
	CTestMacroScript();
	virtual ~CTestMacroScript();


	CString  m_strMacroID;
	CString  m_strUIDLL;

//���غ���
public:
	virtual UINT GetClassID() {    return MCSCLASSID_CTESTMACROSCRIPT;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CTestMacroScriptKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

//˽�г�Ա����
private:
	BOOL m_bHasInit;

//˽�г�Ա�������ʷ���
public:

public:
	void InitScript(CTestMacro *pMacro);
	BOOL RunScript(CTestMacro *pMacro, CShortData *pData);
};

