/**
 *@file
 *\brief 报文协议解析器
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
	 *@brief 协议解析函数
	 */ 
	CTcpEdgePkg* Parser(const CString& strFromDeviceID, char* pBuf);
};

#endif