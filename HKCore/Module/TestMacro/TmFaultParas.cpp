//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性

	//初始化成员变量
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

