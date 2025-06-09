//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TcpEdgeAuth_0x01.cpp  CTcpEdgeAuth_0x01


#include "stdafx.h"
#include "TcpEdgeAuth_0x01.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgeAuth_0x01::CTcpEdgeAuth_0x01()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTcpEdgeAuth_0x01::~CTcpEdgeAuth_0x01()
{
}

CString CTcpEdgeAuth_0x01::ParseAuthASDUPkg(BYTE *pByte)
{
	if( pByte[0] != 0x01 )
	{
		return "";
	}

	//������Ե��������
	char* pTempName = new char[64];
	BYTE* pByteName = new BYTE[64];
	for( int i=0; i<64; i++)
	{
		pByteName[i] = pByte[i+1];
	}

	memcpy(pTempName, pByteName, 64);
	if(pTempName != NULL)
	{
		m_strTcpEdgeName = pTempName;
	}
	delete pTempName;
	pTempName = NULL;
	delete pByteName;
	pByteName = NULL;

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

	CString strPkg;
	strPkg.Format(_T("%s%s%s%s"),(char *)pByte[0], m_strName, m_strRandNum, m_strSignature);
	return strPkg;
}