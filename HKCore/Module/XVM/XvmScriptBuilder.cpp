#include "StdAfx.h"
#include "XvmScriptBuilder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CStringSerializeBuffer g_oBinaryBuffer;

class _CXvmScriptBuilder_CBinarySerialBufferCreate
{
public:
	_CXvmScriptBuilder_CBinarySerialBufferCreate()
	{
		g_oBinaryBuffer.SetBufferLength(4194304);   //4M
		g_oBinaryBuffer.AllocBuffer(0);
	}

	virtual ~_CXvmScriptBuilder_CBinarySerialBufferCreate()
	{
		
	}
};

_CXvmScriptBuilder_CBinarySerialBufferCreate g_oXvmScriptBuilder_CBinarySerialBufferCreate;


CXvmScriptBuilder::CXvmScriptBuilder()
{
	
}


CXvmScriptBuilder::~CXvmScriptBuilder()
{
	
}



//////////////////////////////////////////////////////////////////////////
//
CStringSerializeBuffer* CXvmScriptBuilder::xvm_script_StringSerializeBuffer()
{
	return &g_oBinaryBuffer;
}

void CXvmScriptBuilder::xvm_script_ResetBuffer()
{
	g_oBinaryBuffer.ResetBufferPointer();
}

long CXvmScriptBuilder::xvm_script_GetBufferLength()
{
	return g_oBinaryBuffer.Tell();
}

/*
const char* CXvmScriptBuilder::xvm_script_SerializeScript(CPpScript *ppScript, long &nScriptIndex)
{
	if (ppScript->m_strScript.GetLength() < 6)
	{
		ppScript->m_pszFuncName[0] = 0;
		return g_oBinaryBuffer.GetBuffer();
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

	return g_oBinaryBuffer.GetBuffer();
}
*/

const char* CXvmScriptBuilder::xvm_script_SerializeScript(CExBaseObject *p, long &nScriptIndex)
{
	if (p->IsBaseList())
	{
		SerializeScript((CExBaseList*)p, nScriptIndex);
	}
	else
	{
		SerializeScript(p, nScriptIndex);
	}

	return g_oBinaryBuffer.GetBuffer();
}

/*
void CXvmScriptBuilder::xvm_script_SerializeScriptFunc(CPpScript *ppScript, long &nScriptIndex)
{
	if (ppScript->m_strScript.GetLength() < 6)
	{
		ppScript->m_pszFuncName[0] = 0;
		return;
	}

	sprintf(ppScript->m_pszFuncName, "func%d", nScriptIndex);

	nScriptIndex++;
}
*/

void CXvmScriptBuilder::xvm_script_SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex)
{
	SerializeScriptFunc((CExBaseList*)p, nScriptIndex);
}

void CXvmScriptBuilder::SerializeScript(CExBaseList *pList, long &nScriptIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		
		//if (nClassID == PPCLASSID_PPSCRIPT)
		if (IsScript(p))
		{	
			SerializeScript(p, nScriptIndex);
		}
		else if (p->IsBaseList())
		{
			SerializeScript((CExBaseList*)p, nScriptIndex);
		}
	}	
}

void CXvmScriptBuilder::SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		
		//if (nClassID == PPCLASSID_PPSCRIPT)
		if (IsScript(p))
		{	
			SerializeScriptFunc(p, nScriptIndex);
		}
		else if (p->IsBaseList())
		{
			SerializeScriptFunc((CExBaseList*)p, nScriptIndex);
		}
	}	
}

