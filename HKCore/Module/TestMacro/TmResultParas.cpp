//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性

	//初始化成员变量
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
	//初始化属性

	//初始化成员变量
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

