#include "stdafx.h"
#include "TcpEdgeGlobalDef.h"
#include "TcpEdgeProtocolPkgParser.h"

CTcpEdgeProtocolPkgParser::CTcpEdgeProtocolPkgParser()
{
	m_pJson = NULL;
}

CTcpEdgeProtocolPkgParser::~CTcpEdgeProtocolPkgParser()
{
	if(m_pJson)
	{
		CJSON_Delete(m_pJson);
		m_pJson = NULL;
	}
}

CTcpEdgePkg* CTcpEdgeProtocolPkgParser::Parser(const CString& strFromDeviceID, char* pBuf)
{
	if(m_pJson)
	{
		CJSON_Delete(m_pJson);
		m_pJson = NULL;
	}

	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	pPkg->m_strName = strFromDeviceID;
	m_pJson = pPkg->Parser(pBuf);

	return pPkg;
}

