#include "StdAfx.h"
#include "PpScript.h"
#include "PpDevBaseApp.h"
#include "PpEngineDataMngrCntr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// #include "lua.h"

CPpScript::CPpScript(CString strXmlKey)
{
	 m_strXmlKey=strXmlKey;
	 m_strScript="";
	 m_strSyntax="";
	 m_dwReturn = 1;
	 ZeroMemory(m_pszFuncName, SCRIPT_FUNC_NAME_MAXLEN);
}

CPpScript::~CPpScript(void)
{
    //m_strXmlKey.ReleaseBuffer();
}

//<![CDATA[
//]]>

long CPpScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

// 	MSXML2::IXMLDOMCDATASectionPtr oCDTA =  oNode->GetfirstChild();
// 
// 	if (oCDTA != NULL)
// 	{
// 		m_strScript = (char*)oCDTA->Getxml();
// 		long nLen = m_strScript.GetLength();
// 		m_strScript = m_strScript.Mid(9, nLen-12);
// 		
// 		//m_strScript = (char*)oCDTA->Gettext();
// 		//m_strScript.Trim();
// 	}
// 	else
// 	{
// 		m_strScript = (char*)oNode->Gettext();
// 		m_strScript.Trim();
// 
// 	}
	oNode.xml_GetCDATA(m_strScript);
	
	return 0;
}

long CPpScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	try {
// 		MSXML2::IXMLDOMNodePtr oNode;
// 
// 		oNode = oXMLDoc->createCDATASection(L"");
// 		ASSERT( oNode != NULL);
// 		oElement->appendChild(oNode);
// 
// 		oNode->put_text((_bstr_t)m_strScript);
		oElement.xml_SetCDATA(oXMLDoc, m_strScript);
	} 
	catch(...)
	{

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CPpScript::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	if (m_strXmlKey != ((CPpScript*)pObj)->m_strXmlKey)
	{
		return FALSE;
	}

	if (m_strScript != ((CPpScript*)pObj)->m_strScript)
	{
		return FALSE;
	}

	if (m_strSyntax != ((CPpScript*)pObj)->m_strSyntax)
	{
		return FALSE;
	}

	return CExBaseList::IsEqualOwn(pObj);
}

CBaseObject* CPpScript::Clone()
{
	CPpScript* pNew = new CPpScript(_T(""));
	Copy(pNew);
	return pNew;
}

BOOL CPpScript::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	((CPpScript*)pDest)->m_strXmlKey = m_strXmlKey;
	((CPpScript*)pDest)->m_strScript = m_strScript;
	((CPpScript*)pDest)->m_strSyntax = m_strSyntax;
	strcpy(((CPpScript*)pDest)->m_pszFuncName, m_pszFuncName);

	return CExBaseList::CopyOwn(pDest);
}

long CPpScript::Run(/*const CString &strVariables, CBbVariables *pVariables*/)
{
	//清空返回值类型
	m_dwReturnType = OPERAND_TYPE_NULL;

	//执行脚本
	//pApp->RunScript(this, strVariables, pVariables);
	CPpEngineData *pEngineData = (CPpEngineData *)GetAncestor(PPCLASSID_PPENGINEDATA);
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return 1;
	}

	pEngineData->RunScript(this);

	return m_dwReturn;
}

long CPpScript::Compile(const CString &strVariables)
{
	m_dwReturnType = 0;

	//执行脚本
	//pApp->RunScript(this, strVariables, pVariables);
	CPpEngineData *pEngineData = (CPpEngineData *)GetAncestor(PPCLASSID_PPENGINEDATA);
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return 1;
	}

	m_dwReturn = pEngineData->CompileScript(this);

	return m_dwReturn;
}

BOOL CPpScript::HasReturn()
{
	return (m_dwReturnType == OPERAND_TYPE_INT || m_dwReturnType == OPERAND_TYPE_STRING || m_dwReturnType == OPERAND_TYPE_FLOAT);
}

BOOL CPpScript::IsReturnValueTrue()
{
	if (m_dwReturnType == OPERAND_TYPE_INT)
	{
		return m_dwReturn > 0;
	}
	else if (m_dwReturnType == OPERAND_TYPE_FLOAT)
	{
		return m_dReturn > 0.9;
	}
	else if (m_dwReturnType == OPERAND_TYPE_STRING)
	{
		return m_dwReturn > 0;
	}
	else
	{
		return FALSE;
	}
}

//////////////////////////////////////////////////////////////////////////
//
extern CStringSerializeBuffer g_oBinaryBuffer;
CPpXvmScriptBuilder g_oPpXvmScriptBuilder;

CPpXvmScriptBuilder::CPpXvmScriptBuilder()
{

}
CPpXvmScriptBuilder::~CPpXvmScriptBuilder()
{

}

void CPpXvmScriptBuilder::SerializeScript(CExBaseObject *p, long &nScriptIndex)
{
	CPpScript *ppScript = (CPpScript*)p;

	if (ppScript->m_strScript.GetLength() < 6)
	{
		ppScript->m_pszFuncName[0] = 0;
		return;// g_oBinaryBuffer.GetBuffer();
	}

	sprintf(ppScript->m_pszFuncName, "func%d", nScriptIndex);
	g_oBinaryBuffer << ("func ");
	g_oBinaryBuffer << ppScript->m_pszFuncName;
	g_oBinaryBuffer << ("()\r\n{\r\n");

	g_oBinaryBuffer.Append_ASCII(ppScript->m_strScript);

	//if (ppScript->m_strScript.Find(_T("return ")) < 0)
	{
		g_oBinaryBuffer << ("\r\nreturn 1;");
	}

	g_oBinaryBuffer << ("\r\n}\r\n\r\n");
	nScriptIndex++;

	return;// g_oBinaryBuffer.GetBuffer();
}

void CPpXvmScriptBuilder::SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex)
{
	CPpScript *ppScript = (CPpScript*)p;

	if (ppScript->m_strScript.GetLength() < 6)
	{
		ppScript->m_pszFuncName[0] = 0;
		return;
	}

	sprintf(ppScript->m_pszFuncName, "func%d", nScriptIndex);

	nScriptIndex++;
}


void CPpXvmScriptBuilder::SerializeScript(CExBaseList *pList, long &nScriptIndex)
{
	if (pList->GetClassID() == PPCLASSID_BBVARIABLES)
	{
		return;
	}

	CXvmScriptBuilder::SerializeScript(pList, nScriptIndex);
}

void CPpXvmScriptBuilder::SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex)
{
	if (pList->GetClassID() == PPCLASSID_BBVARIABLES)
	{
		return;
	}

	CXvmScriptBuilder::SerializeScriptFunc(pList, nScriptIndex);
}

