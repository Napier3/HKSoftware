#include "stdafx.h"
#include "PpEngineCreateMngr.h"
#include "XLanguageResourceAts.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern BOOL g_bShowTestWndTop;

//////////////////////////////////////////////////////////////////////////
//
CPpEngineCreate::CPpEngineCreate()
{
	m_pPpEngine = NULL;
}

CPpEngineCreate::~CPpEngineCreate()
{

}

PpEngine::IPpEnginePtr CPpEngineCreate::GetPpEngine(const CString &strProgID)
{
	if (m_pPpEngine != NULL)
	{
		return m_pPpEngine;
	}

	if (strProgID == g_strPpEngineProgID_None)
	{
		return m_pPpEngine;
	}

	m_pPpEngine.CreateInstance( strProgID );

	if (m_pPpEngine == NULL)
	{
#ifndef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_CrtPrtlEgnFail/*_T("创建规约引擎[%s]失败")*/, strProgID);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("创建规约引擎[%s]失败"), strProgID);
#endif
	}
	else
	{
		m_pPpEngine.ShowSpyWnd(g_bShowTestWndTop);
		
		try
		{
			m_pPpEngine.AttatchLogWnd(m_hLogWnd);
		}
		catch (...)
		{
			
		}
	}

	return m_pPpEngine;
}

void CPpEngineCreate::ReleasePpEngine()
{
	if (m_pPpEngine != NULL)
	{
		try
		{
			m_pPpEngine = NULL;
		}
		catch (...)
		{
#ifndef NOT_USE_XLANGUAGE
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_RlsPrtlEgnFail/*_T("释放规约引擎[%s]失败")*/, m_strID);
#else
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("释放规约引擎[%s]失败"), m_strID);
#endif	
		}
	}
}

void CPpEngineCreate::ReleaseAllDevice()
{
	if (m_pPpEngine != NULL)
	{
		try
		{
			m_pPpEngine.ReleaseAllDevice();
		}
		catch (...)
		{
#ifndef NOT_USE_XLANGUAGE
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_RlsPrtlEgnFail/*_T("释放规约引擎[%s]失败")*/, m_strID);
#else
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("释放规约引擎[%s]失败"), m_strID);
#endif	
		}
	}
}

void CPpEngineCreate::ShowSpyWnd()
{
	if (m_pPpEngine != NULL)
	{
		m_pPpEngine.ShowSpyWnd(g_bShowTestWndTop);
	}
}

void CPpEngineCreate::StopProtocolParseForReadSoe(BOOL bStop)
{
	try
	{
		if (m_pPpEngine != NULL)
		{
			m_pPpEngine.SetProtocolParse(bStop);
		}
	}
	catch (...)
	{
		
	}
}

void CPpEngineCreate::ConfigEngine()
{

}


long CPpEngineCreate::AttatchLogWnd(unsigned long hWnd)
{
	try
	{
		if (m_pPpEngine != NULL)
		{
			m_pPpEngine.AttatchLogWnd(hWnd);
		}
	}
	catch (...)
	{
		
	}

	return 0;
}

BOOL CPpEngineCreate::HasPpEngine()
{
	return (m_pPpEngine != NULL);
}

//////////////////////////////////////////////////////////////////////////
//CPpEngineCreateMngr
CPpEngineCreateMngr::CPpEngineCreateMngr()
{
	m_hLogWnd = 0;
}

CPpEngineCreateMngr::~CPpEngineCreateMngr()
{
	
}

PpEngine::IPpEnginePtr CPpEngineCreateMngr::GetPpEngine(const CString &strProgID)
{
	CPpEngineCreate *pFind = (CPpEngineCreate*)FindByID(strProgID);

	if (pFind == NULL)
	{
		pFind = new CPpEngineCreate();
		pFind->m_hLogWnd = m_hLogWnd;
		pFind->m_strName = strProgID;
		pFind->m_strID = strProgID;
		AddNewChild(pFind);
	}

	return pFind->GetPpEngine(strProgID);
}

void CPpEngineCreateMngr::StopProtocolParseForReadSoe(BOOL bStop)
{
	POS pos = GetHeadPosition();
	CPpEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)GetNext(pos);
		p->StopProtocolParseForReadSoe(bStop);
	}
}

void CPpEngineCreateMngr::ConfigEngine()
{
	POS pos = GetHeadPosition();
	CPpEngineCreate *p = NULL;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)GetNext(pos);
		p->ConfigEngine();
	}
}

void CPpEngineCreateMngr::ReleasePpEngine()
{
	POS pos = GetHeadPosition();
	CPpEngineCreate *p = NULL;


	while (pos != NULL)
	{
		p = (CPpEngineCreate *)GetNext(pos);
		p->ReleaseAllDevice();
		p->ReleasePpEngine();
	}
}

void CPpEngineCreateMngr::ReleasePpEngine(const CString &strProgID)
{
	CPpEngineCreate *pFind = (CPpEngineCreate*)FindByID(strProgID);

	if (pFind != NULL)
	{
		pFind->ReleasePpEngine();
	}
}

BOOL CPpEngineCreateMngr::HasPpEngine()
{
	POS pos = GetHeadPosition();
	CPpEngineCreate *p = NULL;
	BOOL bHas = FALSE;

	while (pos != NULL)
	{
		p = (CPpEngineCreate *)GetNext(pos);
		bHas = p->HasPpEngine();

		if (bHas)
		{
			break;
		}
	}

	return bHas;
}
