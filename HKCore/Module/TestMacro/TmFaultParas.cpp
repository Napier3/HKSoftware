//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmFaultParas.cpp  CTmFaultParas


#include "stdafx.h"
#include "TmFaultParas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmFaultParas::CTmFaultParas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTmFaultParas::~CTmFaultParas()
{
}

CBaseObject* CTmFaultParas::Clone()
{
	CTmFaultParas *p = new CTmFaultParas();
	Copy(p);
	return p;
}

BOOL CTmFaultParas::CanPaste(UINT nClassID)
{
	return FALSE;
}

