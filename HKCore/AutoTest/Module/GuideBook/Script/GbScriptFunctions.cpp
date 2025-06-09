#include "StdAfx.h"
#include "GbScriptFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _SCRIPT_USE_XVM
#include "XScript_XVM.h"
#include "GbScriptFunctions_xvm.h"
#endif

#ifdef _SCRIPT_USE_LUA
#include "XScript_LUA.h"
#include "GbScriptFunctions_lua.h"
#endif


class CGbScriptFactory
{
public:
	CGbScriptFactory()
	{

	}

	virtual ~CGbScriptFactory()
	{
#ifdef _SCRIPT_USE_LUA
		delete m_pXScript_LUA;
#endif

#ifdef _SCRIPT_USE_XVM
		delete m_pXScript_XVM;
#endif

	}

private:
#ifdef _SCRIPT_USE_LUA
	CXScript_LUA *m_pXScript_LUA;
#endif

#ifdef _SCRIPT_USE_XVM
	CXScript_XVM *m_pXScript_XVM;
#endif

public:
	void InitScriptFactory()
	{
#ifdef _SCRIPT_USE_LUA
		if (m_pXScript_LUA == NULL)
		{
			m_pXScript_LUA  =new CXScript_LUA();
			m_pXScript_LUA->InitScript();
		}
#endif

#ifdef _SCRIPT_USE_XVM
		if (m_pXScript_XVM == NULL)
		{
			m_pXScript_XVM = new CXScript_XVM();
			m_pXScript_XVM->InitScript();
		}
#endif
	}

	CXScriptBase* GetScript(CExBaseObject *pGbObj)
	{
		if (Gb_IsScriptType_LUA(pGbObj))
		{
#ifdef _SCRIPT_USE_LUA
			return m_pXScript_LUA;
#endif
		}
		else
		{
#ifdef _SCRIPT_USE_XVM
			return m_pXScript_XVM;
#endif
		}

		return NULL;
	}

	void CloseScript()
	{
#ifdef _SCRIPT_USE_LUA
		if (m_pXScript_LUA != NULL)
		{
			m_pXScript_LUA->CloseScript();
		}
#endif

#ifdef _SCRIPT_USE_XVM
		if (m_pXScript_XVM != NULL)
		{
			m_pXScript_XVM->CloseScript();
		}
#endif
	}

	void UnLoadScript()
	{
#ifdef _SCRIPT_USE_LUA
		if (m_pXScript_LUA != NULL)
		{
			m_pXScript_LUA->Gb_UnloadScript();
		}
#endif

#ifdef _SCRIPT_USE_XVM
		if (m_pXScript_XVM != NULL)
		{
			m_pXScript_XVM->Gb_UnloadScript();
		}
#endif
	}
};

CGbScriptFactory g_oGbScriptFactory;

char g_pLuaReturnString[MAX_PATH];

BOOL Gb_InitScrpitEngine()
{
	g_oGbScriptFactory.InitScriptFactory();
	return TRUE;
}

void Gb_CloseScrpitEngine()
{
	g_oGbScriptFactory.CloseScript();
}

long Gb_RunScript(CScriptText *pScript, CString &strSyntaxError, BOOL bInitFilter)
{
	CXScriptBase *pScriptRun = g_oGbScriptFactory.GetScript(pScript);

	if (pScriptRun == NULL)
	{
		return -1;
	}

// 	if (pScript->m_strScriptText.IsEmpty())
// 	{
// 		return -1;
// 	}

	return pScriptRun->RunScript(pScript, strSyntaxError, bInitFilter);
}

long Gb_CompileScript(CScriptText *pScript, CString &strSyntaxError)
{
	CXScriptBase *pScriptRun = g_oGbScriptFactory.GetScript(pScript);

	if (pScriptRun == NULL)
	{
		return -1;
	}

	return pScriptRun->CompileScript(pScript, strSyntaxError);
}

long Gb_BuildScript_GuideBook(CGuideBook *pGuideBook)
{
	CXScriptBase *pScriptRun = g_oGbScriptFactory.GetScript(pGuideBook);

	if (pScriptRun == NULL)
	{
		return -1;
	}

	return pScriptRun->Gb_BuildScript_GuideBook(pGuideBook);
}

void Gb_UnloadScript()
{
	g_oGbScriptFactory.UnLoadScript();
}