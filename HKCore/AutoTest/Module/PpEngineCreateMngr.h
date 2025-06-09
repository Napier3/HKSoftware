#pragma once

// #include "..\..\Module\TestMacro\TestMacroInterface.h"
#include "../../Module/Interface/ProtocolEngineInterface.h"
// #include "GuideBook\GbDataTypeMngr.h"
// #include "GuideBook\GbParaTypeMngr.h"
#include "GuideBook/PpEngineDataType.h"

//通讯命令处理消息，通过接口指定给通讯引擎
// #define	WM_COMM_COMMAND		(WM_USER+1001)
// #define WM_ENGINE_SYSTEM_MSG           (WM_USER + 1112)

//////////////////////////////////////////////////////////////////////////
//CPpEngineCreate
class CPpEngineCreate : public CExBaseObject
{
public:
	CPpEngineCreate();
	virtual ~CPpEngineCreate();

	PpEngine::IPpEnginePtr m_pPpEngine;

	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	void ReleasePpEngine();
	void ReleaseAllDevice();

	void ShowSpyWnd();
	void StopProtocolParseForReadSoe(BOOL bStop);
	BOOL HasPpEngine();
	void ConfigEngine();
	long AttatchLogWnd(unsigned long hWnd);

public:
	unsigned long m_hLogWnd;

};

class CPpEngineCreateMngr : public CExBaseList
{
public:
	CPpEngineCreateMngr();
	virtual ~CPpEngineCreateMngr();

	PpEngine::IPpEnginePtr GetPpEngine(const CString &strProgID);
	void ReleasePpEngine();
	void ReleasePpEngine(const CString &strProgID);
	void StopProtocolParseForReadSoe(BOOL bStop);
	void ConfigEngine();

	BOOL HasPpEngine();

public:
	unsigned long m_hLogWnd;
};
