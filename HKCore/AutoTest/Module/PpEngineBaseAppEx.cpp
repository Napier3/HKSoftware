#include "stdafx.h"
#include "PpEngineBaseAppEx.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//
CPpEngineBaseAppEx *g_thePpEngineApp = NULL;

CPpEngineBaseAppEx::CPpEngineBaseAppEx()
{
	srand(time(0));

	g_thePpEngineApp = this;
	m_pXTestMsgWnd = NULL;
}

CPpEngineBaseAppEx::~CPpEngineBaseAppEx()
{

}

long CPpEngineBaseAppEx::InitTCtrlBaseApp()
{
	CreateAllEngine();

	return 1;
}


/*
	释放测试环境：在应用程序的ExitInstance中调用
	一定要在ExitInstance中调用，否则应用程序会因释放环境顺序问题导致错误
*/
long CPpEngineBaseAppEx::ExitPpEngineBaseAppEx()
{
	ReleasePpEngine();

	return 0;
}

#ifdef _use_ppengine_exception
BOOL CPpEngineBaseAppEx::IsPpMmsEngineException()
{
	int nCpuUsage = m_oSysExeCpuUsage.get_cpu_usage();

	if (nCpuUsage > 50)
	{
		m_nPpMmsEngineCpuCounts++;
	}

	if (m_nPpMmsEngineCpuCounts > 3)
	{
		m_nPpMmsEngineCpuCounts = 0;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
#endif

PpEngine::IPpEnginePtr CPpEngineBaseAppEx::GetPpEngine(const CString &strProgID)
{
	PpEngine::IPpEnginePtr oEngine = m_oPpEngineCreateMngr.GetPpEngine(strProgID);

#ifdef _use_ppengine_exception
	if (strProgID == g_strPpEngineProgIDMms)
	{
		m_oSysExeCpuUsage.setpid(g_strPpMmsEngineExeName);
		m_oSysExeCpuUsage.get_cpu_usage();
	}
#endif

	return oEngine;
}

BOOL CPpEngineBaseAppEx::HasPpEngine()
{
	return m_oPpEngineCreateMngr.HasPpEngine();
}

void CPpEngineBaseAppEx::ReleasePpEngine()
{
	m_oPpEngineCreateMngr.ReleasePpEngine();
}

void CPpEngineBaseAppEx::ReleasePpEngine(const CString &strProgID)
{
	m_oPpEngineCreateMngr.ReleasePpEngine(strProgID);
}

void CPpEngineBaseAppEx::CreatePpEngine()
{
	//关闭进程
#ifdef _use_TerminateProgram
	TerminateProgram(g_strPpEngineExeName);
	TerminateProgram(g_strPpMmsEngineExeName);
#endif

	//开启通讯引擎程序
	// 	try
	// 	{
	// 		PpEngine::IPpEnginePtr pEngine = GetPpEngine();
	// 	}
	// 	catch(...)
	// 	{
	// 	}
}

void CPpEngineBaseAppEx::CreateAllEngine()
{
	//CreateMacroTestEngine();
	CreatePpEngine();
}

void CPpEngineBaseAppEx::InitPpEngineShowSpyWnd()
{
	POS pos = m_oPpEngineCreateMngr.GetHeadPosition();
	CPpEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)m_oPpEngineCreateMngr.GetNext(pos);
		p->ShowSpyWnd();
	}
}


void CPpEngineBaseAppEx::StopProtocolParseForReadSoe(BOOL bStop)
{
	m_oPpEngineCreateMngr.StopProtocolParseForReadSoe(bStop);
}
