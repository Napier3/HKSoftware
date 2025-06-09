#include "stdafx.h"
#include "EdgeMqttEngineBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CEdgeMqttEngineBase::CEdgeMqttEngineBase()
:CMqttEngineBase()
{

}

CEdgeMqttEngineBase::~CEdgeMqttEngineBase()
{

}

void CEdgeMqttEngineBase::BufToCmd(CExBaseObject *pCmdBase,char *pBuf,long nLen,const CString &strFormat)
{
	CEdgeCmd *pEdgeCmd = (CEdgeCmd *)pCmdBase;

	if (strFormat == EDGE_DATA_FORMAT_JSON)
	{
		pEdgeCmd->PraseCmdBuf(pBuf,nLen,NULL,EDGE_DATA_FORMAT_JSON);
	}
	else
	{
		//XML
		SetXmlBufferLen(nLen * 2);
		pEdgeCmd->PraseCmdBuf(pBuf,nLen,m_pszXmlBuffer,EDGE_DATA_FORMAT_XML);
	}
}