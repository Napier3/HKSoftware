//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgeAuth_0x02.h  CTcpEdgeAuth_0x02

#pragma once
#include "TcpEdgePkgBase.h"

class CTcpEdgeAuth_0x02: public CTcpEdgePkgBase
{
public:
	CTcpEdgeAuth_0x02();
	virtual ~CTcpEdgeAuth_0x02();

public:
	BYTE m_bytePkg[145];
	BYTE* CreateAuthPkg(const char* pMasterStationName, BYTE* pRandNum1, BYTE* pRandNum2, BYTE* pSignature);

	void CreateRandNum2(char *pszRandNum2);

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

