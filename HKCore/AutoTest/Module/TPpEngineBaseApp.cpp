#include "stdafx.h"
#include "TPpEngineBaseApp.h"
#include	"../../Module/api/GlobalConfigApi.h"
#include "../../Module/api/GloblaDrawFunctions.h"
#include "AutoTestXMLRWKeys.h"
#include "../../Module\API\SingleAppMutexApi.h"

CTPpEngineBaseApp::CTPpEngineBaseApp()
{
	
}

CTPpEngineBaseApp::~CTPpEngineBaseApp()
{
}

long CTPpEngineBaseApp::InitPpEngineBaseApp()
{
	//初始化系统路径
	_P_InitSystemPath();

	return 1;
}

/*
	释放测试环境：在应用程序的ExitInstance中调用
	一定要在ExitInstance中调用，否则应用程序会因释放环境顺序问题导致错误
*/
long CTPpEngineBaseApp::ExitTPpEngineBaseApp()
{
	try
	{
		m_pPpEngine.ReleaseAllDevice();
	}
	catch (...)
	{
		
	}

	try
	{
		m_pPpEngine = NULL;
	}
	catch (...)
	{

	}


	return 0;
}

PpEngine::IPpEnginePtr CTPpEngineBaseApp::GetPpEngine(const CString &strProgID)
{
	if (m_strPpEngineProgID == strProgID && m_pPpEngine != NULL)
	{
		return m_pPpEngine;
	}

	if (m_pPpEngine == NULL)
	{
		
	}

	if (m_pPpEngine != NULL)
	{
		ReleasePpEngine();
		m_pPpEngine = NULL;
	}

	m_pPpEngine.CreateInstance( strProgID );

	if (m_pPpEngine == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("创建规约引擎失败"));
	}
	else
	{
		m_strPpEngineProgID = strProgID;
	}

	return m_pPpEngine;
}

void CTPpEngineBaseApp::ReleasePpEngine()
{
	if (m_pPpEngine != NULL)
	{
		try
		{
			m_pPpEngine = NULL;
		}
		catch (...)
		{
		}
	}
}

void CTPpEngineBaseApp::CreatePpEngine()
{
	//关闭进程
#ifdef _use_TerminateProgram
	TerminateProgram(_T("ppengine.exe"));
	TerminateProgram(_T("ppmmsengine.exe"));
#endif

}
