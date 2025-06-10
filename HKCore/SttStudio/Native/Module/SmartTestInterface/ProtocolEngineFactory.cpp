#include "stdafx.h"
#include"ProtocolEngineFactory.h"

#include "../../../Module/TestMacro/TestMacrosFileMngr.h"
#include "../SttGlobalDef.h"

CProtocolEngineFactory* CProtocolEngineFactory::g_pProtocolEngineFactory = NULL;
long CProtocolEngineFactory::g_nProtocolEngineFactory = 0;

CProtocolEngineFactory::CProtocolEngineFactory()
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	m_pPpeEngineCreator = new CPpeEngineCreator;
#endif
	
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	m_pSttProtocolEngineCreator  = new CPpsttEngineCreator;
#endif
}

CProtocolEngineFactory::~CProtocolEngineFactory(void)
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	delete m_pPpeEngineCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	delete m_pSttProtocolEngineCreator;
#endif
}

CProtocolEngineFactory* CProtocolEngineFactory::Create()
{
	g_nProtocolEngineFactory++;

	if (g_nProtocolEngineFactory == 1)
	{
		g_pProtocolEngineFactory = new CProtocolEngineFactory();
	}

	return g_pProtocolEngineFactory;
}

void CProtocolEngineFactory::Release()
{
	g_nProtocolEngineFactory--;

	if (g_nProtocolEngineFactory == 0)
	{
		delete g_pProtocolEngineFactory;
		g_pProtocolEngineFactory = NULL;
	}
}

BOOL CProtocolEngineFactory::HasPpEngine()
{
	BOOL b1 = TRUE, b2=TRUE;

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	b1 = g_pProtocolEngineFactory->m_pSttProtocolEngineCreator->HasPpEngine();
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	b2 = g_pProtocolEngineFactory->m_pPpeEngineCreator->HasPpEngine();
#endif

	return b1 || b2;
}

CProtocolEngineInterface* CProtocolEngineFactory::GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID)
{
	if (g_pProtocolEngineFactory == NULL)
	{
		return NULL;
	}

	return g_pProtocolEngineFactory->In_GetProtocolEngine(strEngineMode, strPpEngineProgID);
}


void CProtocolEngineFactory::ReleasePpEngine(const CString &strProgID)
{
	if (g_pProtocolEngineFactory == NULL)
	{
		return ;
	}

	g_pProtocolEngineFactory->In_ReleasePpEngine(strProgID);
}

void CProtocolEngineFactory::ReleasePpEngine()
{
	if (g_pProtocolEngineFactory == NULL)
	{
		return ;
	}

	g_pProtocolEngineFactory->In_ReleasePpEngine();
}

void CProtocolEngineFactory::StopProtocolParseForReadSoe(BOOL bStop)
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	g_pProtocolEngineFactory->m_pSttProtocolEngineCreator->StopProtocolParseForReadSoe(bStop);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	g_pProtocolEngineFactory->m_pPpeEngineCreator->StopProtocolParseForReadSoe(bStop);
#endif
}

void CProtocolEngineFactory::InitPpEngineShowSpyWnd()
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	g_pProtocolEngineFactory->m_pSttProtocolEngineCreator->InitPpEngineShowSpyWnd();
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	g_pProtocolEngineFactory->m_pPpeEngineCreator->InitPpEngineShowSpyWnd();
#endif
}

void CProtocolEngineFactory::AttatchLogWnd(unsigned long hLogWnd)
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	g_pProtocolEngineFactory->m_pSttProtocolEngineCreator->m_hLogWnd = hLogWnd;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	g_pProtocolEngineFactory->m_pPpeEngineCreator->m_hLogWnd = hLogWnd;
#endif
}


//2023-8-19  lijunqing 兼容各种通信模式
CProtocolEngineInterface* CProtocolEngineFactory::In_GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID)
{
	if (strEngineMode == STT_CMD_PARA_EngineMode_STT  || strPpEngineProgID == STT_CMD_PARA_EngineMode_STT)
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#endif
	}

	if (strEngineMode == STT_CMD_PARA_EngineMode_MQTT || strPpEngineProgID == STT_CMD_PARA_EngineMode_MQTT)
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#endif
	}


	if (strPpEngineProgID.GetLength() < 4)
	{//异常情况下，如果为空，则默认使用STT
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#else
		return NULL;
#endif
	}

	//方式2：如果包含STT.
	if (strPpEngineProgID.Left(4) == _T("STT."))
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#else
		return NULL;
#endif
	}

	//方式3：如果包含MQTT.
	if (strPpEngineProgID.Left(5) == _T("MQTT."))
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#else
		return NULL;
#endif
	}

	//已经排除了  "STT."    "MQTT."
	//方式4：如果EngineProgID中包含“.”，则默认为COM模式
	if (strPpEngineProgID.Find('.') > 0)
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
		return m_pPpeEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#else
		return NULL;
#endif
	}

	//方式5：如果EngineProgID为PpEngine、MmsEngine、CmsEngine，默认为STT模式
	if (strPpEngineProgID == STT_IOT_PP_TYPE_PpEngine 
		|| strPpEngineProgID == STT_IOT_PP_TYPE_MmsEngine
		|| strPpEngineProgID == STT_IOT_PP_TYPE_CmsEngine)
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#else
		return NULL;
#endif
	}

	//方式6：兼容三种模式
	if (g_strSttEngine_PXI == strPpEngineProgID   //_T("PpEngine");
		|| g_strSttEngine_IOT == strPpEngineProgID  // _T("PpSttIotEngine");
		|| g_strSttEngine_MQTT == strPpEngineProgID)  //_T("PpSttMqttEngine");
	{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
		return m_pSttProtocolEngineCreator->GetProtocolEngine(strEngineMode, strPpEngineProgID);
#endif
	}

	return NULL;
}

void CProtocolEngineFactory::In_ReleasePpEngine(const CString &strProgID)
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	return m_pSttProtocolEngineCreator->ReleasePpEngine(strProgID);
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	return m_pPpeEngineCreator->ReleasePpEngine(strProgID);
#endif
}

void CProtocolEngineFactory::In_ReleasePpEngine()
{
#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	return m_pSttProtocolEngineCreator->ReleasePpEngine();
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	return m_pPpeEngineCreator->ReleasePpEngine();
#endif
}
