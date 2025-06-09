#include "stdafx.h"
#include "EngineToPxFactory.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CEngineToPxFactory* g_pEngineToPxFactory = NULL;
long g_nEngineToPxFactoryRef = 0;

CEngineToPxFactory::CEngineToPxFactory()
{
	
}

CEngineToPxFactory::~CEngineToPxFactory()
{

}

CEngineToPxFactory *CEngineToPxFactory::Create()
{
	g_nEngineToPxFactoryRef++;

	if (g_nEngineToPxFactoryRef == 1)
	{
		g_pEngineToPxFactory = new CEngineToPxFactory;
	}

	return g_pEngineToPxFactory;
}

void CEngineToPxFactory::Release()
{
	g_nEngineToPxFactoryRef--;

	if (g_nEngineToPxFactoryRef == 0)
	{
		delete g_pEngineToPxFactory;
		g_pEngineToPxFactory = NULL;
	}
}

void CEngineToPxFactory::RegisterEngineToPx(const CString &strPxProtoID, PFN_CREATE_ENGINE_TO_PX* pFunCreate)
{
	CEngineToPxCreator* pEngineToPxCreator = NULL;
	pEngineToPxCreator = new CEngineToPxCreator(strPxProtoID, pFunCreate);
	g_pEngineToPxFactory->AddNewChild(pEngineToPxCreator);
}

CIotEngineToPxBase* CEngineToPxFactory::CreateEngineToPxByPxProtoID(const CString &strPxProtoID, CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd)
{
	CString strEngineToPxID = GetEngineToPxID(strPxProtoID);

	CEngineToPxCreator* pEngineToPxCreator = (CEngineToPxCreator*)FindByID(strEngineToPxID);

	if (pEngineToPxCreator != NULL)
	{
		return pEngineToPxCreator->Create(pIotEngineProtocolServer, pCmd);
	}

	return NULL;
}

/////////////////////////////////////////

CIotEngineToPxBase* Px_CreateEngineToPxByPxProtoID(const CString &strPxProtoID, CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd)
{
	CIotEngineToPxBase* pNew = NULL;

	if (g_pEngineToPxFactory != NULL)
	{
		pNew = g_pEngineToPxFactory->CreateEngineToPxByPxProtoID(strPxProtoID, pIotEngineProtocolServer, pCmd);
	}

	return pNew;
}

CString GetEngineToPxID(const CString &strPxProtoID)
{
	CString strRet = ParseFilePostfix(strPxProtoID);

	if (strRet.IsEmpty())
	{
		strRet = strPxProtoID;
		strRet.MakeUpper();
	}
	else
	{
		strRet.MakeUpper();
	}

	return strRet;
}

