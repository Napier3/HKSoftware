//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ScriptFuncs.h  CScriptFuncs

#pragma once

#include "ScriptFuncGlobal.h"


#include "ScriptFunc.h"

class CScriptFuncs : public CExBaseList
{
public:
	CScriptFuncs();
	virtual ~CScriptFuncs();

	BOOL OpenConfigFile(const CString &strFile);

//���غ���
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNCS;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

class  CScriptFuncsList : public CExBaseList
{
protected:
	CScriptFuncsList();
	virtual ~CScriptFuncsList();

	static CScriptFuncsList *g_pScriptFuncsList;
	static long g_nScriptFuncsList;

public:
	static void Create();
	static void Release();
	static CScriptFuncs* OpenFile(const CString &strFile);

};

