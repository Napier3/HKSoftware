//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmSysParas.cpp  CTmSysParas


#include "stdafx.h"
#include "TmSysParas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmSysParas::CTmSysParas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTmSysParas::~CTmSysParas()
{
}

CBaseObject* CTmSysParas::Clone()
{
	CTmSysParas *p = new CTmSysParas();
	Copy(p);
	return p;
}

BOOL CTmSysParas::CanPaste(UINT nClassID)
{
	return FALSE;
}

