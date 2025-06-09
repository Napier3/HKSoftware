//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FuncResults.cpp  CFuncResults


#include "stdafx.h"
#include "FuncResults.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CFuncResults::CFuncResults()
{
	//初始化属性

	//初始化成员变量
}

CFuncResults::~CFuncResults()
{
}

CBaseObject* CFuncResults::Clone()
{
	CFuncResults *p = new CFuncResults();
	Copy(p);
	return p;
}

