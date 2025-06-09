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
	//��ʼ��ϵͳ·��
	_P_InitSystemPath();

	return 1;
}

/*
	�ͷŲ��Ի�������Ӧ�ó����ExitInstance�е���
	һ��Ҫ��ExitInstance�е��ã�����Ӧ�ó�������ͷŻ���˳�����⵼�´���
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("������Լ����ʧ��"));
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
	//�رս���
#ifdef _use_TerminateProgram
	TerminateProgram(_T("ppengine.exe"));
	TerminateProgram(_T("ppmmsengine.exe"));
#endif

}
