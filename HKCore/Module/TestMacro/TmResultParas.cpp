//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmResultParas.cpp  CTmResultParas


#include "stdafx.h"
#include "TmResultParas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmResultParas::CTmResultParas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTmResultParas::~CTmResultParas()
{
}

CBaseObject* CTmResultParas::Clone()
{
	CTmResultParas *p = new CTmResultParas();
	Copy(p);
	return p;
}

BOOL CTmResultParas::CanPaste(UINT nClassID)
{
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
CTmSearchResultParas::CTmSearchResultParas()
{
	//��ʼ������

	//��ʼ����Ա����
}

CTmSearchResultParas::~CTmSearchResultParas()
{
}

CBaseObject* CTmSearchResultParas::Clone()
{
	CTmSearchResultParas *p = new CTmSearchResultParas();
	Copy(p);
	return p;
}

BOOL CTmSearchResultParas::CanPaste(UINT nClassID)
{
	return FALSE;
}

