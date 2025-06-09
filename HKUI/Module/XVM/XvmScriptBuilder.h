#pragma once

#include "../baseclass/exbaselist.h"
#include "../BaseClass/StringSerializeBuffer.h"

#define SCRIPT_FUNC_NAME_MAXLEN   20

class CXvmScriptBuilder
{
public:
	CXvmScriptBuilder();
	virtual ~CXvmScriptBuilder();
	
public:
	void xvm_script_ResetBuffer();
	CStringSerializeBuffer* xvm_script_StringSerializeBuffer();
	const char* xvm_script_SerializeScript(CExBaseObject *p, long &nScriptIndex);
	long xvm_script_GetBufferLength();
	void xvm_script_SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex);

protected:
	virtual BOOL IsScript(CExBaseObject *p) = 0;
	virtual void SerializeScript(CExBaseObject *p, long &nScriptIndex) = 0;
	virtual void SerializeScriptFunc(CExBaseObject *p, long &nScriptIndex) = 0;
	
	virtual void SerializeScript(CExBaseList *pList, long &nScriptIndex);
	virtual void SerializeScriptFunc(CExBaseList *pList, long &nScriptIndex);
};
