//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgeAuth_0x01.h  CTcpEdgeAuth_0x01

#pragma once
#include "TcpEdgePkgBase.h"


class CTcpEdgeAuth_0x01: public CTcpEdgePkgBase
{
public:
	CTcpEdgeAuth_0x01();
	virtual ~CTcpEdgeAuth_0x01();


//���غ���
public:

protected:
	CString m_strTcpEdgeName;
	CString m_strRandNum;
	CString m_strSignature;


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CString ParseAuthASDUPkg(BYTE *pByte);

	CString GetTcpEdgeName()  {  return m_strTcpEdgeName;  }
	CString GetRandNum()      {  return m_strRandNum;      }
	CString GetSignature()    {  return m_strSignature;    }
//���Ա������ʷ���
public:
};

