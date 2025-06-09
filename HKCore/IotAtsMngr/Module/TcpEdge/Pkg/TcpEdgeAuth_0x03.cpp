//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgeAuth_0x03.cpp  CTcpEdgeAuth_0x03


#include "stdafx.h"
#include "TcpEdgeAuth_0x03.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgeAuth_0x03::CTcpEdgeAuth_0x03()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgeAuth_0x03::~CTcpEdgeAuth_0x03()
{
}

void CTcpEdgeAuth_0x03::ParseAuthASDUPkg(BYTE *pByte)
{

	if( pByte[0] != 0x03 )
	{
		return;
	}

	//���������
	char* pTempRand = new char[8];
	BYTE* pByteRand = new BYTE[8];
	for( int i=0; i<8; i++)
	{
		pByteRand[i] = pByte[i+65];
	}
	memcpy(pTempRand, pByteRand, 8);
	if(pTempRand != NULL)
	{
		m_strRandNum = pTempRand;
	}
	delete pTempRand;
	pTempRand = NULL;
	delete pByteRand;
	pByteRand = NULL;

	//����ǩ�����ֵ
	char* pTempSig = new char[64];
	BYTE* pByteSig = new BYTE[64];

	for( int i=0; i<8; i++)
	{
		pByteSig[i] = pByte[i+73];
	}
	memcpy(pTempSig, pByteSig, 64);
	if(pTempSig != NULL)
	{
		m_strSignature = pTempSig;
	}
	delete pTempSig;
	pTempSig = NULL;
	delete pByteSig;
	pByteSig = NULL;
}