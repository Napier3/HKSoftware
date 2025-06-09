#include "stdafx.h"
#include "EngineToPxCreator.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CEngineToPxCreator::CEngineToPxCreator(const CString &strPxProtoID, PFN_CREATE_ENGINE_TO_PX* pFunCreate)
{
	m_strID = strPxProtoID;
	m_pFunCreate = pFunCreate;
}

CEngineToPxCreator::~CEngineToPxCreator()
{

}

CIotEngineToPxBase* CEngineToPxCreator::Create(CMqttEngineBase_Stt *pIotEngineProtocolServer, CSttCmdBase *pCmd)
{
	return m_pFunCreate(pIotEngineProtocolServer, pCmd);
}

