//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

