//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgeAuth_0x03.h  CTcpEdgeAuth_0x03

#pragma once

#include "TcpEdgePkgBase.h"


class CTcpEdgeAuth_0x03 : public CTcpEdgePkgBase
{
public:
	CTcpEdgeAuth_0x03();
	virtual ~CTcpEdgeAuth_0x03();


protected:
	CString m_strRandNum;
	CString m_strSignature;


public:
	void ParseAuthASDUPkg(BYTE *pByte);

	CString GetRandNum()      {  return m_strRandNum;      }
	CString GetSignature()    {  return m_strSignature;    }

};

