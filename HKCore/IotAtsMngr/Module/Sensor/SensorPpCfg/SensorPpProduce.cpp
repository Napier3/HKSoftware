//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SensorPpProduce.cpp  CSensorPpProduce


#include "stdafx.h"
#include "SensorPpProduce.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSensorPpProduce::CSensorPpProduce()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSensorPpProduce::~CSensorPpProduce()
{
}

CBaseObject* CSensorPpProduce::Clone()
{
	CSensorPpProduce *p = new CSensorPpProduce();
	Copy(p);
	return p;
}

CBaseObject* CSensorPpProduce::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSensorPpProduce *p = new CSensorPpProduce();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}