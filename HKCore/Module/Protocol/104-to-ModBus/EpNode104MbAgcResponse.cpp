// EpNode104MbAgcResponse.cpp: implementation of the CEpNode104MbAgcResponse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpNode104MbAgcResponse.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpNode104MbAgcResponse::CEpNode104MbAgcResponse(long nType)
{
	m_dwFrameID = EPCLASSID_101_FRAME_68_ASDU67;
	m_nTypeID = EPNODE_TYPE_RESPONSE;
	
	m_pMbNode = AddNode(EPCLASSID_MBRTUMASTER_TFRAME_03, _T(""));
}

CEpNode104MbAgcResponse::~CEpNode104MbAgcResponse()
{

}


void CEpNode104MbAgcResponse::CreateResponseNodes()
{
	
	
}

void CEpNode104MbAgcResponse::CreateProcessNodes()
{

}

void CEpNode104MbAgcResponse::CreateJumpsNodes()
{

}

void CEpNode104MbAgcResponse::CreateTimers()
{

}

CEpNode104MbAgcResponse* CEpNode104MbAgcResponse::RunJumps(CEpFrameBase *pPkgDetail)
{
	CEp101Frame_68_Asdu67 *pAsdu67 = (CEp101Frame_68_Asdu67*)pPkgDetail;
	
	
// 	//执行初始化脚本
// 	RunInitScript(pPkgDetail);
// 
// 	if (m_pJumps == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CEpNode104MbAgcResponse *pNode = m_pJumps->RunJumps(pPkgDetail);
// 
// 	//执行结束脚本
// 	RunEndScript(pPkgDetail);

	return NULL;
}

void CEpNode104MbAgcResponse::RunInitScript(CEpFrameBase *pFrame)
{

}

void CEpNode104MbAgcResponse::RunEndScript(CEpFrameBase *pFrame)
{

}

void CEpNode104MbAgcResponse::RunNodeScript(CEpFrameBase *pFrame)
{

}

