#pragma once
#include "EngineToPxCreator.h"


class CEngineToPxFactory : public CExBaseList
{
public:
	CEngineToPxFactory(void);
	virtual ~CEngineToPxFactory(void);

	static CEngineToPxFactory *Create();
	static void Release();

public:
	static void RegisterEngineToPx(const CString &strPxProtoID, PFN_CREATE_ENGINE_TO_PX* pFunCreate);

public:
	virtual CIotEngineToPxBase* CreateEngineToPxByPxProtoID(const CString &strPxProtoID, CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd);
};

extern CEngineToPxFactory* g_pEngineToPxFactory;
extern long g_nEngineToPxFactoryRef;

CIotEngineToPxBase* Px_CreateEngineToPxByPxProtoID(const CString &strPxProtoID, CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd);
CString GetEngineToPxID(const CString &strPxProtoID);

