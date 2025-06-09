//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

