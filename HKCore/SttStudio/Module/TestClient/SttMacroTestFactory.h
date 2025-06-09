#pragma once

#include "SttMacroTestInterface.h"

class CSttMacroTestFactory
{
public:
	static CSttMacroTestFactory* Create();
	static void Release();
	
private:
	CSttMacroTestFactory();
	virtual ~CSttMacroTestFactory();
	
	static long g_nMacroTestFactoryRef;
	static CSttMacroTestFactory *g_pMacroTestFactory;

public:
	static CMacroTestEngineInterface* CreateMacroTestEngine(const CString &strMacroTestEngineProgID);
	static void FreeMacroTestEngine(CMacroTestEngineInterface *pMacroTestEngine);
	
	
};

