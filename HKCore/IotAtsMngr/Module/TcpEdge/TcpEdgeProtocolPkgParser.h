/**
 *@file
 *\brief ����Э�������
 */

#ifndef TCPEDGEPROTOCOLPKGPARSER_H
#define TCPEDGEPROTOCOLPKGPARSER_H

#include "Pkg/TcpEdgePkg.h"

class CTcpEdgeProtocolPkgParser
{
private:
	CJSON* m_pJson;
public:
	CTcpEdgeProtocolPkgParser();
	virtual ~CTcpEdgeProtocolPkgParser();

public:
	/**
	 *@brief Э���������
	 */ 
	CTcpEdgePkg* Parser(const CString& strFromDeviceID, char* pBuf);
};

#endif