//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	//初始化属性

	//初始化成员变量
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

