#pragma once

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
#include"PpEngine_COM.h"
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
#include "PpsttEngineCreator.h"
#endif


class CProtocolEngineFactory : public CExBaseList
{
private:
	CProtocolEngineFactory();
	virtual ~CProtocolEngineFactory(void);

	static CProtocolEngineFactory *g_pProtocolEngineFactory;
	static long g_nProtocolEngineFactory;

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_COM_
	CPpeEngineCreator *m_pPpeEngineCreator;
#endif

#ifdef _USE_SMARTTEST_INTERFACE_ENGINE_STT_
	CPpsttEngineCreator *m_pSttProtocolEngineCreator;
#endif

public:
	static CProtocolEngineFactory* Create();
	static void Release();

	static BOOL HasPpEngine();
	static CProtocolEngineInterface* GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID);
	static void ReleasePpEngine(const CString &strProgID);
	static void ReleasePpEngine();
	static void StopProtocolParseForReadSoe(BOOL bStop);
	static void InitPpEngineShowSpyWnd();
	static void AttatchLogWnd(unsigned long hLogWnd);

private:
	CProtocolEngineInterface* In_GetProtocolEngine(const CString &strEngineMode, const CString &strPpEngineProgID);
	void In_ReleasePpEngine(const CString &strProgID);
	void In_ReleasePpEngine();

};

