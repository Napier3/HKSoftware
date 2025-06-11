#pragma once

#include "ExBaseList.h"
#include "PpGlobalDefine.h"
#include "../../../Module/BaseClass/StringSerializeBuffer.h"

#include "../../../Module/XVM/XvmScriptBuilder.h"

class CPpScript :	public CExBaseList
{
public:
	CPpScript(CString strXmlKey);
	virtual ~CPpScript(void);

public:
	CString m_strXmlKey;          //XML文件的关键字,保存xml的element关键字
	CString m_strScript;
	CString m_strSyntax;
	
	//脚本的返回值定义
	DWORD m_dwReturnType;//返回值的类型
	DWORD m_dwReturn;
	CString m_strReturn;
	double m_dReturn;

	//CString m_strFuncName;
	char m_pszFuncName[SCRIPT_FUNC_NAME_MAXLEN];

public://执行
	long Run(/*const CString &strVariables=L"", CBbVariables *pVariables=NULL*/);
	long Compile(const CString &strVariables=_T(""));
	BOOL HasReturn();
	BOOL IsReturnValueTrue();

public:
	virtual UINT GetClassID() {  return PPCLASSID_PPSCRIPT;    };
	virtual BSTR GetXmlElementKey()  {  return m_strXmlKey.AllocSysString();   };

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};

//const char* scipt_SerializeAllScript(CExBaseList *pList, CExBaseObject *pDevice);

class CPpXvmScriptBuilder : public CXvmScriptBuilder
{
public:
	CPpXvmScriptBuilder();
	virtual ~CPpXvmScriptBuilder();

protected:
	virtual BOOL IsScript(CExBaseObject *p)	{		return p->GetClassID() == PPCLASSID_PPSCRIPT;		}
	virtual void SerializeScript(CExBaseObject *p, long &nScriptIndex);
	virtual void SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex);

	virtual void SerializeScript(CExBaseList *pList, long &nScriptIndex);
	virtual void SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex);

};

extern 	CPpXvmScriptBuilder g_oPpXvmScriptBuilder;

// CStringSerializeBuffer* xvm_script_StringSerializeBuffer();
// void xvm_script_ResetBuffer();
// long xvm_script_GetBufferLength();
// const char* xvm_script_SerializeScript(CPpScript *ppScript, long &nScriptIndex);
// const char* xvm_script_SerializeScript(CExBaseList *pList, long &nScriptIndex);
// 
// void xvm_script_SerializeScriptFunc(CPpScript *ppScript, long &nScriptIndex);
// void xvm_script_SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex);
