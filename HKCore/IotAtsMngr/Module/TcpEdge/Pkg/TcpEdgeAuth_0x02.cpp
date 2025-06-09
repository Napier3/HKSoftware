//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgeAuth_0x02.cpp  CTcpEdgeAuth_0x02


#include "stdafx.h"
#include "TcpEdgeAuth_0x02.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgeAuth_0x02::CTcpEdgeAuth_0x02()
{
	//初始化属性
	for(int i = 0; i<145; i++)
	{
		m_bytePkg[i] = (BYTE)"0";
	}
	//初始化成员变量
}

CTcpEdgeAuth_0x02::~CTcpEdgeAuth_0x02()
{
}

BYTE* CTcpEdgeAuth_0x02::CreateAuthPkg(const char* pMasterStationName, BYTE* pRandNum1, BYTE* pRandNum2, BYTE* pSignature)
{

	m_bytePkg[0] = 0x02;
	
	QString strName = pMasterStationName;
	QByteArray bytesName = strName.toUtf8();
	for(int i= 0; i< bytesName.size(); i++)
	{
		m_bytePkg[i + 1] = bytesName.at(i);
	}

	for (int i = bytesName.size(); i < 64; i++)
	{
		m_bytePkg[i + 1] = 0;
	}

	for(int i=0; i<8; i++)
	{
		m_bytePkg[i+65] = pRandNum1[i];
	}

	for(int i=0; i<8; i++)
	{
		m_bytePkg[i+73] = pRandNum2[i];
	}

	for(int i=0; i<64; i++)
	{
		m_bytePkg[i+81] = pSignature[i];
	}

	return m_bytePkg;
}

//lmy，20230830修改参数类型，在改显示报文部分时，发现原本的随机数2生成填充的不太对，故而修改
void CTcpEdgeAuth_0x02::CreateRandNum2(char *pszRandNum2)
{
	int num;
	for(int i = 0; i < 8;i++ ) 
	{
		num = rand() % 10;
		pszRandNum2[i] = num + '0';
	}
}

